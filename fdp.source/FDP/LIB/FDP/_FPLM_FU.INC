{ -------------------------- }
{ spracovanie                }
{ -------------------------- }

 {$IFDEF EDD}
   procedure add_prop_FPLm(FPL: PDmFPL);

     procedure add_FPLi(FPL: PDmFPL; propFPLth,FPLth, propFPLot,FPLot: P_OFPL);
         var   i: int;
         begin
         { zurivy algoritmus, pretoze sa stalo,
           ze bol zmeneny typ letu a tym padom bol
           dvakrat v pamati - raz ako vojensky
           a druhyraz ako iny
         }
           i:= FPLot^.find(FPL);
           if i>-1 then FPLot^.Del(i)
           else if propFPLot<>nil then
                   begin
                     i:= propFPLot^.find(FPL);
                     if i>-1 then propFPLot^.Del(i)
                   end;

         { zaradenie ku navrhovanym, pokial nebol uz prebrany
         }
           if (propFPLth=nil) or (FPLth^.find(FPL)>-1) then FPLth^.add(FPL)
           else propFPLth^.add(FPL)
         end;

       begin
        {$IFDEF  FPLO}
         if is_mFPL(FPL) then add_FPLi(FPL, PROP_mFPL,mFPL, PROP_oFPL,oFPL)
         else add_FPLi(FPL, PROP_oFPL,oFPL, PROP_mFPL,mFPL)
        {$ELSE}
         PROP_mFPL^.add(FPL)
        {$ENDIF}
       end;
 {$ENDIF}


 procedure add_FPLm(FPL: PDmFPL);

   procedure add_FPLi(FPL: PDmFPL; FPLth,FPLot: P_OFPL);
       var   i: int;
       begin
       { zurivy algoritmus, pretoze sa stalo,
         ze bol zmeneny typ letu a tym padom bol
         dvakrat v pamati - raz ako vojensky
         a druhyraz ako iny
       }
         i:= FPLot^.find(FPL);
         if i>-1 then FPLot^.Del(i);

       { zaradenie ku navrhovanym, pokial nebol uz prebrany
       }
         FPLth^.add(FPL)
       end;

     begin
      {$IFDEF  FPLO}
       if is_mFPL(FPL) then add_FPLi(FPL, mFPL,oFPL)
       else add_FPLi(FPL, oFPL,mFPL)
      {$ELSE}
       mFPL^.add(FPL)
      {$ENDIF}
     end;


{ Povodna fcia...
  Vyhladanie uz existujuceho? FPLm, ak nie je najdeny, spracovanie nevrati LAM;
  Ak vrati true FPLm je naplneny a ma alokovane polia !

  Poznamka: mal som problemy s odosielanim 2hej a dalsej spravy,
            pretoze pri nacitavani celeho planu sa nevynuloval
            vektor potvrdeni ->
            find_FPL musi vektor vynulovat !
            ==============================
}

 function najdi_FPLM (FPL: DmFPL; var FPLp: DmFPL): bool;
    var   rec : Tplan_rec;
          r_ : word; m_,d_,h_ : byte;
          res : int;

    label X;

    begin
      rec:= FPL.rec;
      r_:= FPL.date.r;
      if r_=0 then init_date(FPL.date, year,month,day);
      fillchar(FPLp,sizeof(FPLp),0);

     { najprv prehlada data v pamati }
      if mFPL<>nil then
         begin
           res:= mFPL^.find(@FPL);
           if res<>-1 then begin copy_mFPL(mFPL^.ap^[res],@FPLp); goto X end
         end;

     {$IFDEF FPLO}
      if oFPL<>nil then
         begin
           res:= oFPL^.find(@FPL);
           if res<>-1 then begin copy_mFPL(oFPL^.ap^[res],@FPLp); goto X end;
         end;
     {$ENDIF}

     { potom na disku z dnesneho dna }
      res:= read_mFPL(codekey_FPLM(@FPL),@FPLp);
      if res<>-1 then goto X;

     { pripadne zo vcerajska }
      if r_<>0 then goto X;
      r_:= year; m_:= month; d_:= day; h_:= hour;
      PrevDateH(r_,m_,d_,h_);
      init_date(FPL.date, r_,m_,d_);
      res:= read_mFPL(codekey_FPLM(@FPL),@FPLp);

      X: najdi_FPLM:= res<>-1;
      FPLp.rec:= rec
    end;


{ kontroly na jednoznacnost spracovania
}
 function existuje_mFPL(FPL: PDmFPL; _zobraz: bool): bool;
    var   bres : bool;
          ans  : TAnswer;
    begin
      bres:= false;

      if      (     ((not is_KRL(FPL)) and (find_FPLM(FPL,nil{@eq_mFPL_data})<>-1))
                {$IFDEF KRL}
                 or (     is_KRL(FPL)  and (find_KRL(FPL,@eq_KRL_data)<>-1))
                {$ENDIF}
              )

        then begin
               bres:=    (not _zobraz)
                      or ( Ask2(msgWARNING,
                              inf_plan+' '+code_FPLM_7a(FPL)+'-'+FPL^.start.kod
                              + ' '+inf_na_den+' '+DateToStr2(FPL^.date.d,FPL^.date.m,0)
                              + ' '+inf_exist+' '+ask_prepisat,
                              '',White,clBUTTON_COLOR,waitASK*18
                              )
                           <> ansAno
                         )
             end;

      existuje_mFPL:= bres
    end;


 function zmeneny_mFPL(FPL: PDmFPL; _zobraz: bool): bool;
    var   FPLn: DmFPL;
          bres: bool;
    begin
      if read_mFPL(codekey_FPLM(FPL),@FPLn)>=0 then
         begin
          {$IFDEF KRL}
            if is_KRL(FPL) then bres:= not eq_KRL_data(FPL,@FPLn)
            else
          {$ENDIF}
           bres:= chg_mFPL(FPL,@FPLn);
           if bres and _zobraz then
              begin
                info_mFPL(@FPLn, tit_zmeneny_plan);
                bres:= not (Ask2(msgWARNING, tit_zmeneny_plan+' '+ask_prepisat,'',White,clBUTTON_COLOR,waitASK*18)=ansAno)
              end;
           zmeneny_mFPL:= bres;
           disp_mFPL(@FPLn)
         end
      else zmeneny_mFPL:= false
    end;


{ zaradenie spacovaneho planu
}
 function _zarad_FPLm(FPL: PDmFPL; _stat: string; _send: bool; _src: fdp_src; prop: bool): bool;

     var   zarad : bool;
           nasli,i,prev_pos : int;

    begin
      _zarad_FPLm:= false;

      {if _zmena then if zmeneny_mFPL(FPL, _zobraz) then Exit;}
      _zarad_FPLm:= true;

      FPL^.stat:= del_stat(FPL^.stat,cnst_read+cnst_chg); { aby sa neobjavovala sprava o oprave... }
      if _stat<>'' then FPL^.stat:= _stat;
      format_mFPL(FPL);

     { kvoli kontrole na zmenu, nesmie cakat,
       da sa to rozdrobit na drobne fcie,
       aby 2x nehladal v db
     }
      if _send then _odosli_mFPL(FPL,_src); 
      save_mFPL(FPL);

      {$IFDEF EDD}
        if prop then add_prop_FPLm(FPL)
        else
      {$ENDIF}

      {$IFDEF STATISTIKA_SERVER}
        if p_save_STA_FPLM<>nil then TProc_p(p_save_STA_FPLM)(FPL);
      {$ENDIF}

      if (p_fplm_dbscroller<>nil) then p_fplm_dbscroller^.data_update(FPL);

      { musi byt na konci pretoze tato funkcia moze byt volana
        po spracovani z handlera tohto objektu objektu, ktory
        moze data uvolnit z pamate a dostanem takto referenciu
        na odalokovanu pamat
      }
      add_FPLm(FPL);
    end;

 function zarad_FPLm(FPL: PDmFPL; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_FPLm:= _zarad_FPLm(FPL,_stat,_send,_src,false)
    end;
