 { Funkcie pre spracovanie trate planu letu,
   asi ich nechame tak...
 }
 (*
 procedure _split_RTE(FPL: PDmFPL;

                      BOD_TRATE  : string;
                      CISLO_BODU : int;
                      SPEC_BODU  : string;

                      var TRAT: T_TRAT4
                     ); far;

     var   plan,s,b : string;
           i,p,k    : int;

     begin
       FillChar(TRAT,sizeof(TRAT),0);
       plan:= uni_str(delchar(strpas(FPL^.trat),setNL_+setNL));
       inc(CISLO_BODU); { v stringu sa spracovavaju polozky od 1..x, scroll_OB vracia 0..x-1 }

       TRAT.FPL  := FPL;
       TRAT.OB   := getstr(BOD_TRATE,1,odd_BODU);
       TRAT.SPEC := copy(BOD_TRATE,length(TRAT.OB)+1,length(BOD_TRATE)-length(TRAT.OB));

       if SPEC_BODU<>'' then
          begin
            b:= getstr(BOD_TRATE,1,odd_BODU); k:= getstritems(plan,odd_BODOV);
            i:= 1; p:= 0;
            while (i<=k) do
              begin
                s:= getstr(plan,i,odd_BODOV);
                if (pos(b,s)<>0) and (pos(SPEC_BODU,s)<>0) then inc(p);
                if (p>CISLO_BODU) then break;
                inc(i)
              end;
            if i<=k then CISLO_BODU:= i
            else CISLO_BODU:= -1
          end;

       if CISLO_BODU>-1 then
          begin
            for p:= 1 to CISLO_BODU-1 do
                TRAT.TRAT_PRED:= TRAT.TRAT_PRED + GetStr(plan,p,odd_BODOV)+ icao_NXIT;
            for p:= CISLO_BODU+1 to GetStrItems(plan,odd_BODOV) do
                TRAT.TRAT_PO:= TRAT.TRAT_PO + icao_NXIT + GetStr(plan,p,odd_BODOV)
          end
       else begin
              p:= pos(BOD_TRATE,plan);
              k:= p+Length(BOD_TRATE);
              TRAT.TRAT_PRED:= Copy(plan,1,p-1);
              TRAT.TRAT_PO  := Copy(plan,k,Length(plan)-k+1)
            end
     end;

 procedure _chg_mFPL_RTE(FPL: PDmFPL; TRAT: T_TRAT4; prist_prepocet: bool); far;
     var   RTE,_RTE,_RTEi, s : string;
           OBs : TOBxys;
           i,j : int;
     begin
       RTE:= TRAT.TRAT_PRED + TRAT.OB + TRAT.SPEC + TRAT.TRAT_PO;

       _RTE:= ''; _RTEi:= '';
       for i:= 1 to GetStrItems(RTE, odd_BODOV) do
           begin
             s:= GetStr(RTE,i,odd_BODOV)+' ';
             if length(_RTEi+s) < dlz_rdk_FPLm then _RTEi:= _RTEi+s
             else begin
                    s:= kbCRLF+s;
                    _RTEi:= ''
                  end;
             _RTE:= _RTE+s;
           end;
       if cut_(_RTE)='' then _RTE:= ' '+kbCRLF+' ';

       with FPL^ do
         begin
           StrDispose(trat);
           trat:= StrPasNew(_RTE);
           if     prist_prepocet
              and (rych<>0)
              and (Ask2(code_mFPL_7a(FPL)+' - '+tit_ETA,ask_ETA,'',White,clBUTTON_COLOR,waitASK*18)=ansAno)
                  then decode_trat(trat, start,prist, OBs,bodov, rych,rych_, vys,vys_, date, true,true, prist_prepocet)
         end
      end;


 function scroll_OB(FPL: PDmFPL;
                    var BOD_TRATE : string; var CISLO_BODU : int;
                    _items_OB,_init_OB : pointer;
                    _title : string; x,y : int; _info,_hlpXXX : Pchar
                   ): string; far;
    var   ScL  : TScrollLst;
          TRAT : string;
    begin
      TRAT:= delchar(strpas(FPL^.trat),[kbCRLF]);
      ScL.Init(nil, _title, x,y, max_page_SCROLL_DIR, _info,_hlpXXX,
               @TRAT, _items_OB, _init_OB, nil,nil,false,
               BOD_TRATE, CISLO_BODU
              );
      BOD_TRATE:= cut_(BOD_TRATE);
      scroll_OB:= BOD_TRATE
    end;
 *)


 { -----------
    MZP
   -----------
 }

 { urcenie bodu MZP, posledna polozka bez uvedeneho casu A/D
 }
 function urc_bod_MZP (FPL: PDmFPL): string;
    var   _15l : pchar;
          bod,mzp : string;
          i,r,k : int;
    begin
      _15l:= ReplChar0 (FPL^.trat, setNL+setNL_, icao_NXIT, true);

      i:= 1; mzp:= '';
      for i:= 1 to GetPStrItems(_15l,odd_BODOV) do
        begin
          bod:= mtks_rus_to_lat (uni_str(GetPStr(_15l,i,odd_BODOV)));
          if pos(fpl_MZP,bod) > 0 then
             begin
               if (mzp='') then mzp:= bod;
               if (   (pos(fpl_ARR,bod)>0) and (pos(fpl_DEP,bod)>0)
                   or (pos(fpl_DEP,bod)>0)
                  ) then mzp:= bod;

               if (pos(fpl_ARR,bod)>0) and (pos(fpl_DEP,bod)=0) then
                  begin
                  { este neodstartoval }
                    mzp:= bod;
                    break
                  end;
             end
        end;
      urc_bod_MZP:= mzp;
      strdispose(_15l)
    end;

 (*
 function _get_items_MZP(_TRAT : pstring): int; far;
    begin
      _get_items_MZP:= ma_MZP(_TRAT^)
    end;

 procedure _init_items_MZP(_TRAT : pstring; _items : PPchars; _pocet : int;
                           _get_item,_sort_item : pointer; _sort_dir : bool
                          ); far;
     var   BOD_TRATE : string;
           i,j, m    : int;
     begin
       i:= 1; j:= 0; m:= GetStrItems(_TRAT^,odd_BODOV);
       while (i<=m) and (j<_pocet) do
           begin
             BOD_TRATE:= getstr(_TRAT^,i,odd_BODOV);
             if pos(fpl_MZP,upstring(BOD_TRATE))<>0 then
                begin
                  _items^[j]:= StrPasNew(' '+BOD_TRATE+' ');
                  inc(j)
                end;
             inc(i)
           end;
     end;

 function MZP_FPL_bod(sc: PScroller; FPL: PDmFPL): bool; far;
    var   TRAT,BOD_MZP, idn,inf, stat : string;
          CISLO_BODU, i,m,x,y         : int;
          TRAT4                       : T_TRAT4;
    begin
      MZP_FPL_bod:= false;

      TRAT:= uni_str(DelChar(strpas(FPL^.trat),setNL_+setNL));
      sc_menu_xy(sc, x,y, 0,0);

    { a) zistenie poctu MZP, ak je viacej ako 1 bod -> vyber bodu }
      CISLO_BODU:= -1;
      if ma_MZP(TRAT) > 1 then
         begin
           if scroll_OB(FPL, BOD_MZP,CISLO_BODU, @_get_items_MZP, @_init_items_MZP,
                        ' Medziprist tie '+code_mFPL_7a(FPL)+' ',  x-10,y+20, nil,hlp_mFPL_MZP
                       ) = '' then exit
         end
      else begin
             for i:= 0 to GetStrItems(TRAT,odd_BODOV)-1 do
                 begin
                   BOD_MZP:= getstr(TRAT,i+1,odd_BODOV);
                   if pos(fpl_MZP,BOD_MZP)<>0 then
                      begin
                        CISLO_BODU:= i;
                        break
                      end;
                 end;
           end;
      if CISLO_BODU=-1 then Exit;

      _split_RTE(FPL, BOD_MZP,CISLO_BODU,fpl_MZP, TRAT4);
      idn:= code_mFPL_7a(FPL);
      inf:= 'Upresnenie ‡asu medziprist tia na '+TRAT4.OB+' letom '+idn+'.  (F1 - help)'+#0;
      if formular_OB(TRAT4, x-10,y+20{y+dy_mFPL- 3 shl 3},
                     ' €as medziprist tia '+idn+' na bode '+TRAT4.OB+' :',
                     @inf[1], hlp_mFPL_MZP) then
         begin
           _chg_mFPL_RTE(FPL, TRAT4, false);
           BOD_MZP:= upstring(_BOD_MZP(FPL)); {TRAT4.SPEC}

           if pos(fpl_DEP,BOD_MZP)>0 then stat:= cnst_stat_MZP_DEP
           else if pos(fpl_ARR,BOD_MZP)<>0 then stat:= cnst_stat_MZP_ARR
           else begin
                  Err2('Ch˜ba popis medziprist tia ('+fpl_ARR+') alebo ¨tartu po medziprist ti ('+fpl_DEP+').');
                  Exit
                end;
           zmen_stat_mFPL(FPL, stat, true)
         end
    end;
 *)

 function _MZP_check(form: PmFPLform; FPL: PDmFPL): bool; far;
    var   bres : bool;
          mzp,res : string;
          ires : int;
    begin
      bres:= _mFPL_check(form, FPL, true,false,false);
      if bres then
         begin
           res:= ''; ires:= -1;
           mzp:= urc_bod_MZP(FPL);
           if mzp<>'' then
              begin
              { urcenie casu na bode
              } if pos(fpl_DEP,mzp)>0 then form^.set_stat(cnst_stat_mzs)
                else if pos(fpl_ARR,mzp)>0 then form^.set_stat(cnst_stat_mzp)
                else ires:= l4_err(a_FPLM,code_FPLM_7a(FPL),i_15M,err_FPLM_chyba_bod_MZP, res)
              end
           else ires:= l4_err(a_FPLM,code_FPLM_7a(FPL),i_15M,err_FPLM_chyba_cas_MZP, res);
           if ires<>-1 then
              begin
                form^.ErrorS(ires, res);
                disp_mFPL(FPL);
                bres:= false
              end;
         end;
      _MZP_check:= bres
    end;

 function _MZP_FPL_trat(sc: PScroller; FPL: PDmFPL): bool; far;
    var   tit: string;
    begin
      if {pos(}cnst_stat_mzp=FPL^.stat{)>0} then tit:= msg_FPL_MZS else tit:= msg_FPL_MZP;
      formular_mFPL(FPL,letvis,FPL^.stat,false,tit,i_15M,@_MZP_check,hlp_mFPL_MZP);
      _MZP_FPL_trat:= false
    end;


 function _is_MZP(FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_MZP:=       __is_stat(FPL^.stat, cnst_stat_act)
                 {and (FPL^.stat<>cnst_stat_mzp) -> pre mzp }
                 {and (FPL^.stat<>cnst_stat_mzp) -> pre mzs }
                 and  (_ma_MZP(FPL^.trat)<>0)
                {$IFDEF AIRBASE}
                 {and  ma_tu_MZP(FPL)  -> moze pristavat inde ? }
                {$ENDIF}
    end;

 procedure mFPL_MZP;
     begin
       spracuj_mFPL(find_and_process_FPLM,false,
                    false,false,false,true,
                    '', @_is_MZP,
                    @_MZP_FPL_trat,_TBFunc_p2,
                    false,false,
                    msg_FPL_MZP,nil, hlp_mFPL_MZP
                   )
     end;



 { -----------
    RTE
   -----------

    - oprava pre lety patriace do podriadenosti
    - letisko : definuje cas dosiahnutia bodu
    - StrRLP  : moze opravit cely riadok trasy

 }

 (*
 function _get_items_OB(_TRAT : pstring): int; far;
    begin
      _get_items_OB:= getstritems(_TRAT^,odd_BODOV)
    end;

 procedure _init_items_OB(_TRAT : pstring; _items : PPchars; _pocet : int;
                          _get_item,_sort_item : pointer; _sort_dir : bool
                         ); far;
     var   i: int;
     begin
       for i:= 1 to _pocet do _items^[i-1]:= StrPasNew(' '+getstr(_TRAT^,i,odd_BODOV)+' ')
     end;


 function RTE_FPL_bod(sc: PScroller; FPL: PDmFPL): bool; far;
    var   bod   : string;
          CISLO_BODU  : int;
          TRAT4       : T_TRAT4;
          inf,idn     : string;
          x,y         : int;
    begin
      RTE_FPL_bod:= false;

      sc_menu_xy(sc, x,y, 0,0);
      if scroll_OB(FPL, bod,CISLO_BODU, @_get_items_OB,@_init_items_OB,
                 'Oprava '+code_FPLM_7a(FPL)+' na trati', x-10,y+20, nil,hlp_mFPL_DLA
                ) = '' then Exit;

      _split_RTE(FPL, bod,CISLO_BODU,'', TRAT4);
      idn := code_FPLM_7a(FPL);
      inf := 'Upresnenie ‡asu dosiahnutia bodu '+TRAT4.OB+' letom '+idn+'.  (F1 - help'+#0;
      if formular_OB(TRAT4, x-10,y+20, ' Oprava '+idn+' na bode '+TRAT4.OB+' :',@INF[1],hlp_mFPL_DLA) then
         begin
           _chg_mFPL_RTE(FPL, TRAT4, true);
           zmen_stat_mFPL(FPL, add_stat(FPL^.stat,FPL^.stat), true)
         end
    end;
 *)

 function _RTE_check(form: PmFPLform; FPL: PDmFPL): bool; far;
    var   bres: bool;
    begin
      bres:= _mFPL_check(form, FPL, true,false,true);
      {bolo by treba urcit, ci sa nespravilo MZP...}
      _RTE_check:= bres
    end;

 function _RTE_FPL_trat(sc: PScroller; FPL: PDmFPL): bool; far;
    var   res : bool;
    begin
      res:= formular_mFPL(FPL,letvis,FPL^.stat,false, msg_FPL_RTE,i_15M,@_RTE_check,hlp_mFPL_RTE);
      _RTE_FPL_trat:= false
    end;

 function _is_RTE(FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_RTE:= __is_stat(FPL^.stat, cnst_stat_act+cnst_stat_arr)
    end;

 procedure mFPL_RTE;
     begin
       spracuj_mFPL(find_and_process_FPLM,false,
                    false,false,false,true,
                    cnst_stat_act + cnst_mzp, @_is_RTE,
                    @_RTE_FPL_trat,_TBFunc_p2,
                    false,false,
                    msg_FPL_RTE,nil, hlp_mFPL_RTE
                   )
     end;
