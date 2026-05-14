{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollLst                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TScrollLst.Init(_Owner: PGroup;
                            _title: string;
                            x,y, _page : int;
                            _info, _hlpXXX: Pchar;

                            _PATH       : pointer;

                            _get_items  : pointer;    { @TIFunc_p       }
                            _init_items : pointer;    { TScrollLst_Init }
                            _get_item   : pointer;    { @TSfunc         }
                            _sort_item  : pointer;    { @Proc_pib       }
                            _sort_dir   : bool;       { smer triedenia  }

                            var _RES: string;
                            var _POS: int
                           );
      var   _Event    : TEvent;
            pocet,L,i : int;
      begin
        items:= nil; RES:= ''; _RES:= ''; _POS:= -1;
        if (_get_items=nil) or (_init_items=nil) then Exit;
        if (_info=nil) then _info:= SCROLL_SEL;
        pocet:= TIFunc_p(_get_items)(_PATH);
        if pocet<=0 then Exit;

        GetMem(items, sizeof(pchar)*pocet);
        for i:= 0 to pocet-1 do items^[i]:= nil;
        TScrollLst_Init(_init_items)(_PATH, items,pocet, _get_item,_sort_item, _sort_dir);

        L:=0; for i:= 0 to pocet-1 do L:= Maximum(L,strlen(items^[i]));
        if (x<0) or (y<0) then begin x:= initX; y:= initY end;
        inherited Init(_Owner, _title,
                       nil,nil,nil,nil,
                       x,y, Maximum(L shl 3,dx_FN),dy_FN,
                       __dxisl,__dyisl, __medzerasl, __bgsl, nil,
                       Maximum(Minimum(pocet,_page),3),
                       true,true,true,
                       0,0,nil,nil,nil,
                       kbEnter, cmOK
                      );
        if (x=initX) or (y=initY) then Centre;
        top:= pocet-1;
        RunLocalFunc(_Event,_info);

        for i:= 0 to pocet-1 do StrDispose(items^[i]);
        FreeMem(items, sizeof(pchar)*(pocet));
        items:= nil;
        _RES:= RES; if RES<>'' then _POS:= pos;
        Done
      end;


procedure TScrollLst.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if    isCommand(_Event,cmScrollItemClicked)
         or isCommand(_Event,cmScrollItemEntered)
         or isCommand(_Event,cmOK) then
         begin
           if (top>=0) and (pos>=0) then
              begin
                RES:= strpas(items^[pos]);
              end;
           SetCommand(_Event,cmClose)
         end
    end;

procedure TScrollLst.item_list(i, x,y: int; b: bool);
    const bk: array[false..true] of byte = (__bgsl,__bgsl-1);
          co: array[false..true] of byte = (clGRa,clGRd);
    begin
      if b then BGIgraph.button(x0+dxi-1,y-2{$IFDEF SPEA}+1{$ENDIF},
                                x1-dxi,y+TextHeight('H')+1{$IFDEF SPEA}+item_dy-5{$ENDIF},bk[b], btSmall,btON
                               )
      else FillWin(x0+dxi-1,y-2{$IFDEF SPEA}+1{$ENDIF},x1-dxi,y+TextHeight('H')+1{$IFDEF SPEA}+item_dy-5{$ENDIF},bk[b]);
      SetColor(co[b]); {$IFDEF SPEA} SetBkColor(bk[b]); {$ENDIF}
      OutTextXY(x,y+dy_ed+1, strpas(items^[i]))
    end;
