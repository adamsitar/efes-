{ -------------------------------
   SPRACUJUCE FUNKCIE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

procedure TPLAN.uloz(p: pointer);
    begin
      if (p_save<>nil) then TProc_p(p_save)(p)
    end;

procedure TPLAN.plan(p: pointer);
    begin
    end;


procedure TPLAN.oprav(p: pointer; tit: string);
    begin
      if p_formular<>nil then TBFunc_ps(p_formular)(p,'')
    end;


procedure TPLAN.zobraz(p: pointer);
    begin
      if (p_zobraz<>nil) then TBFunc_ps(p_zobraz)(p,get_id(p))
    end;


procedure TPLAN.plan_zruseny(p: pointer);
    begin
    end;

function  TPLAN.zrus(p: pointer; _ask: bool): bool;
    var   i: int;
    begin
      zrus:= false;
      if     ask_zrus_plan
         and _ask
         and (Ask2(msgVERIPHY,ask_CNL+get_id(p)+'?',titNO,White,clBUTTON_COLOR,waitASK*18)<>ansAno)
             then Exit;
      if _ask then plan_zruseny(p);
      i:= find(p);
      if i<0 then Exit;
      zrus:= true;
      Del(i)
    end;


procedure TPLAN.spracuj(p: pointer);
    begin
      if (p_spracuj<>nil) then TProc_p(p_spracuj)(p)
    end;


{ -------------------------------
   VOLANE FUNKCIE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{ function TPLAN.is_for_node(p: pointer; nd: int): bool;
   begin
     is_for_node:= true
   end;
}

{
  Vyber a spracovanie FPL, aby ponukla zoznam pre vyber,
  musi byt definovana v-fcia get_idn...
}
procedure TPLAN.Oprava(tit: string);
    var   res: int;
    begin
      if top<0 then Exit;
      res:= formular_idn(@Self,tit);
      if (res>=0) and (res<=top) then oprav(ap^[res],tit)
    end;


procedure TPLAN.Zrusenie(tit: string);
    var   res: int;
    begin
      if top<0 then Exit;
      res:= formular_idn(@Self,tit);
      if (res>=0) and (res<=top) then zrus(ap^[res],true)
    end;


procedure TPLAN.Spracovanie(tit: string;
                            _data_filter : pointer; _filter : pointer;
                            _handler_type : TScrollAct_handler_type;
                            _handler : pointer; _handler_par : pointer;
                            _print {$IFDEF MATCA}, _send {$ENDIF}: pointer;
                            _hlpXXX : Pchar
                           );
    var   Ev : TEvent;
          dx : int;
          p  : pointer;
    begin

      if get_item_dx<>nil then item_dx:= TIFunc(get_item_dx);
      if get_item_dy<>nil then item_dy:= TIFunc(get_item_dy);

     {IFDEF MATCA}
       viewer:= New(PScrollInd_FDP,Init
                      (tit,

                       ap,@top,

                       nil{@is_chg},{nil}@arr_chg,@s_loadDB,

                       0, nil,nil,
                       _data_filter,_filter, p_comp,

                       _handler_type,_handler,_handler_par,
                       _print,
                       item_dx,item_dy,item_list,
                       -1,

                       _hlpXXX)
                      );
     {ELSE}(*
       p:= nil{@Self}; { nemoze byt odkaz na pole ako na viewer... }
       viewer:= New(PScrollInd,Init
                      (nil, tit,

                       ap,@top, true,

                       nil{@is_chg},{nil}@arr_chg,@s_loadDB,

                       0, nil,nil,
                       _data_filter,_filter, p_comp,

                       item_dx,item_dy,
                       item_medzera,item_dxi,item_dyi,item_bg,
                       item_list,
                       -1,
                       true,true,true,

                       0,0, nil,nil,nil,
                       _handler_type,_handler,_handler_par,

                       _hlpXXX)
                      );
     {$ENDIF}*)
      viewer^.prepis_en:= true;

     {$IFDEF MAPY}
      dx:= (MaxX-btMapydXY.x0-btMapydXY.x1 - (viewer^.win^.x1-viewer^.win^.x0)) div 2;
      viewer^.MoveRel(btMapydXY.x0+dx-viewer^.win^.x0,0);
     {$ENDIF}

      viewer^.RunLocalFunc(Ev,SCROLL_SEL);
      Dispose(viewer,Done);
      viewer:= nil;
    end;


{
 function handle_PLAN_list(var Ev: TEvent; sc: PScrollInd; FPL: pointer; iFPL: PSTRIP): bool; far;
}
procedure TPLAN.Vypis(tit: string);
    begin
      Spracovanie(tit, nil,nil,
                  p_handler_type{_TBFunc_vEp3}, p_handler, @Self,
                  p_print, {$IFDEF MATCA} nil, {$ENDIF}
                  hlpXXX
                 )
    end;