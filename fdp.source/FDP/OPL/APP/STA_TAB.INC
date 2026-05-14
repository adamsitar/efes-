{ =========================================

   Vytvorenie textovej tabulky statistiky

  =========================================
}
 procedure OStaOPL.vytvor_tabulku_statistiku_za_ (date: TDate; externy: bool;
                                                  spolocny_subor: string;
                                                  datove_subory: PPChars
                                                 );
     var   f : text;
           i : int;
     begin
       {if FExists(spolocny_subor)<>IORES_OK then vytvor_novy_subor(spolocny_subor);}
       Assign(f,spolocny_subor); Rewrite(f);

       {$IFDEF MACC}
        statistika_SRLP (f, date);
        for i:= 0 to poc_AIRBASE-1 do statistika_LSRLP (f, date,i);
       {$ENDIF}
       {$IFDEF AIRBASE}
        if pos_AIRBASE<>high(pos_AIRBASE) then statistika_LSRLP (f, date,pos_AIRBASE);
       {$ENDIF}

       Close(f);
     end;

 function  OStaOPL.vytvor_externu_tabulku (fn: string): string;
    begin
    end;


{ ---------------------
  Formatovanie tabulky
  ---------------------
}
 procedure OStaOPL.zapis_odstavec (var f: text; key: string; zaciatok: bool);
     begin
       if zaciatok then key:= sta_SOH + key + sta_EOH else key:= '';
       writeln(f,key+kbNL);
     end;

 procedure OStaOPL.zapis_riadok (var f: text; riadok: string; nl: bool);
     begin
       if nl then riadok:= riadok+kbNL;
       write(f,riadok);
     end;

 procedure OStaOPL.zapis_udaje (var f: text; zac,udaj,kon: string; sirka: byte; fill: char; nl: bool);
     begin
       if sirka>0 then udaj:= inschar_(fill+udaj,sirka-3,fill,1,true);
       zapis_riadok(f, zac+udaj+kon,nl);
     end;


 procedure OStaOPL.zapis_hlavicku_pracoviska (var f: text; date: TDate; cfg_pracovisko,cfg_nazov,adr: string; sirka: int);
     var   s,t : string;
           i   : int;
     begin
       zapis_udaje (f, kbLavy2Horny2,kbVodorovny2,kbPravy2Horny2,sirka,kbVodorovny2, true);
       i:= 1; s:= '';
       repeat
         s:= __read_cfg_line(cfg_STA,cfg_pracovisko,i,2);
         if (s<>'') then
            begin
              t:= cut_(getstr(s,2,odd_cfg));
              t:= sta_doplnit_nazov_polozky (t,cfg_pracovisko,rmk_DATE,DateToStrS (date.d,date.m,date.r),false,0);
              t:= sta_doplnit_nazov_polozky (t,cfg_pracovisko,cfg_nazov,adr,false,0);
              zapis_udaje (f, kbZvisly2,t,kbZvisly2,sirka,' ', true);
            end;
         inc(i);
       until s='';
       zapis_udaje (f, kbLavy2Dolny,kbVodorovny,kbPravy2Dolny,sirka,kbVodorovny, true);
       {zapis_udaj (f, '','','',0,' ',true);}
     end;


