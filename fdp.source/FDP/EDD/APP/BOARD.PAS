(*-------------------------------------------------------------------*)
(* Board - tabula schvalenych stripov                                *)
(* 1992,94                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{
  Vlastnikom moze by len Owner typu PGroup, lebo sa vola PGroup(Owner)^
}


unit Board;


interface


    uses  TypeDef,
          _Check,
          {$I unit_gr.h},
          {$I unit_oop.h},
          _FDP_def, _FPL_def,
          _STRIP, _FPL;


        { ------------------------------
          polozka NDB na tabuli stripov
          ------------------------------}

    type  PStripBoard = ^TStripBoard;
          TStripBoard = object(TScroller)

            FPLs   : PAindFPL;     { pole s descriptormi na stripy }
            poc    : int;

            is_chg : bool;

            function    inView(x,y: int): bool; virtual;

            constructor Init(_Owner: PGroup; _page: int;
                             x,y, _item_dx,_item_dy: int;
                             _dxi,_dyi, _medzera: int; _bg: byte;
                             _pos_en, _sam: bool;
                             _item_list: pointer;

                             _top_adr : pointer;
                             _top_chg : pointer;
                             _p_arr_chg : p_tick_counter
                            );
            destructor  Done; virtual;

          { interface pre Data: zaradenie stripov
          }
            procedure   add(_iFPL: PSTRIP; _ind: int); virtual;
            procedure   chg(_iFPL: PSTRIP; _ind: int);
            procedure   del(_iFPL: PSTRIP; _ind: int; _zrus: bool); virtual;

            procedure   zrus(_iFPL: PSTRIP; _ind: int);
            function    find(_iFPL: PSTRIP; _ind: int): int;

            procedure   list_reinit; virtual;

            procedure   eq(var _indFPL: TindFPL; _iFPL: PSTRIP; _ind: int);
            function    list_sort: bool; virtual;
            procedure   list_disp;

          end;


implementation

uses  bios;

constructor TStripBoard.Init(_Owner: PGroup; _page: int;
                              x,y, _item_dx,_item_dy: int;
                              _dxi,_dyi, _medzera: int; _bg: byte;
                              _pos_en, _sam: bool;
                              _item_list: pointer;

                              _top_adr : pointer;
                              _top_chg : pointer;
                              _p_arr_chg : p_tick_counter
                             );
      begin
        inherited Init(_Owner, _page,
                       x,y, _item_dx,_item_dy,
                       _dxi,_dyi, _medzera, _bg,
                       _pos_en, _sam,
                       _item_list,

                       nil,_top_adr,
                       _top_chg,_p_arr_chg
                      );

        ObjectType:= obj_view_active;
        click_and_handle:= true;
        is_chg:= false;
        FPLs:= nil;
        poc:= 0;
      end;

destructor TStripBoard.Done;
     begin
       list_disp;
       inherited Done
     end;


function TStripBoard.inView(x,y: int): bool;
   begin
     inView:= (not PLANZET_MAPA) and inherited inView(x,y)
   end;


procedure TStripBoard.list_disp;
    var   i: int;
    begin
      if FPLs<>nil then
         begin
           for i:= 0 to poc-1 do Dispose(FPLs^[i]);
           freemem(FPLs,poc*SizeOf(PindFPL));
         end;
      FPLs:= nil;
      poc:= 0;
      top:= -1
    end;


{ ----------------------------------------------------------------
  data
  ----------- }

procedure TStripBoard.eq(var _indFPL: TindFPL; _iFPL: PSTRIP; _ind: int);
    begin
      _indFPL.iFPL:= _iFPL; _indFPL.ind:= _ind;
    end;

function TStripBoard.find(_iFPL: PSTRIP; _ind: int): int;
   var   res, i: int;
   begin
     res:= -1; i:= 0;
     while (res<0) and (i<=top) do
       begin
         if (FPLs^[i]^.iFPL=_iFPL) and (FPLs^[i]^.ind=_ind) then res:= i;
         inc(i)
       end;
     find:= res
   end;

function TStripBoard.list_sort: bool;
   begin
     list_sort:= false
   end;


{ ----------------------------------------------------------------
  spracovanie
  ----------- }
{
  zatial je to vyriesene takto trivialne, namiesto zoznamu smernikov,
  co nemam teraz cas ladit,
  potom ho spravit ako indexove pole i zoznam smernikov zaroven

}
procedure TStripBoard.add(_iFPL: PSTRIP; _ind: int);
    var   _FPLs : PAindFPL;
          _top,_poc, res,res2, i : int;
          bres : bool;
          {TempWinReg  : PWinReg;}
    begin
      {PGroup(Owner)^.PIS:= vypis_do_okna(x0,y0,x1,y1, TempWinReg,0); ( co ked sa okno zvacsi ? )
      if not PGroup(Owner)^.PIS then PGroup(Owner)^.PREPIS:= true;}

      res:= find(_iFPL,_ind);
      if res<>-1 then
         begin
           if PGroup(Owner)^.PIS then
              begin
                eq(FPLs^[res]^, _iFPL,_ind);
                if PGroup(Owner)^.PIS then
                   begin
                     bres:= list_sort;
                     res2:= find(_iFPL,_ind);
                     if bres or (res<>res2) then List
                     else redraw(res)
                   end
              end
         end
      else begin
             _top:= top+1; _poc:= _top+1;
             getmem (_FPLs, (_poc)*SizeOf(PindFPL));
             for i:= 0 to top do begin New(_FPLs^[i]); _FPLs^[i]^:= FPLs^[i]^; end;
             New(_FPLs^[_top]); eq(_FPLs^[_top]^, _iFPL,_ind);
             list_disp;
             FPLs:= _FPLs; top:= _top; poc:= _poc;
             is_chg:= true {list_sort or ((lo<=res) and (res<=hi))};
             if PGroup(Owner)^.PIS then list_reinit
           end;

      is_chg:= true;

      {obnov_okna(TempWinReg, true)}
    end;


procedure TStripBoard.chg(_iFPL: PSTRIP; _ind: int);
    var   res: int;
    begin
      add(_iFPL,_ind)
    end;

{
  vyradi a mozno i zrusi prvok zo zoznamu
}
procedure TStripBoard.del(_iFPL: PSTRIP; _ind: int; _zrus: bool);
    var   _FPLs  : PAindFPL;
          _top,_poc,i,res : int;
          {TempWinReg : PWinReg;}
    begin
      res:= find(_iFPL,_ind);

      {PGroup(Owner)^.PIS:= vypis_do_okna(x0,y0,x1,y1, TempWinReg,0);
      if not PGroup(Owner)^.PIS then PGroup(Owner)^.PREPIS:= true;}

      if (res>=0) and (top>=0) then
         begin
           _top:= top-1; _poc:= _top+1;
           getmem(_FPLs, (_poc)*SizeOf(PindFPL));
           for i:= 0 to res-1 do begin New(_FPLs^[i]); _FPLs^[i]^:= FPLs^[i]^; end;
           for i:= res to top-1 do begin New(_FPLs^[i]); _FPLs^[i]^:= FPLs^[i+1]^; end;
           list_disp;
           FPLs:= _FPLs; top:= _top; poc:= _poc;
           is_chg:= true {(lo<=res) and (res<=hi)};
         end;

      if _zrus then zrus(_iFPL, _ind);
      if PGroup(Owner)^.PIS then list_reinit;

      {obnov_okna(TempWinReg, true)}
    end;


procedure TStripBoard.zrus(_iFPL: PSTRIP; _ind: int);
    var   i: int;
    begin
      for i:= 0 to top do with FPLs^[i]^ do
          if (iFPL=_iFPL) and (ind>_ind) then dec(ind)
    end;


procedure TStripBoard.list_reinit;
    begin
      List
    end;

end.