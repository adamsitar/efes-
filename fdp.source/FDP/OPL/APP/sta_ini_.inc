{ -----------------------------------------
   Instancia statistiky
  -----------------------------------------
}
 {function enabled_modify_STA (date: TDate): bool; far;
    begin
      enabled_modify_STA:= (StatistikaAPP<>nil) and StatistikaAPP^.povolena_aktualizacia(date)
    end;

 constructor OStaOPL.Init(_cfg_STA,_kod_STA: string);
       begin
         inherited Init(_cfg_STA,_kod_STA);
         p_enabled_modify_STA:= @enabled_modify_STA
       end;}


 procedure OStaOPL.read_cfg(_cfg_STA: string);
     begin
       inherited read_cfg(_cfg_STA);
       hod_vypoctu_sta:= cas_PRS_zac;
     end;


 procedure OStaOPL.inicializacia_modulov;
     begin
       {iFPC,iFPM,iZAM,iPRS,iPRZ,iQGO,iDVZ,iSYN,iSPR : int;}

     { inicializacia modulov sledovanych udajov
     }
       {$IFDEF FPL0}
        {$IFDEF MACC}
          sta_FPLC:= POStatistikaFPLC(inicializuj_modul(New(POStatistikaFPLC,Init(cfg_STA))));
        {$ENDIF}
        sta_FPLM:= POStatistikaFPLM(inicializuj_modul(New(POStatistikaFPLM,Init(cfg_STA))));
       {$ENDIF}

       {$IFDEF ZAM}
        sta_ZAM:= POStatistikaZAM(inicializuj_modul(New(POStatistikaZAM,Init(cfg_STA))));
       {$ENDIF}

       {$IFDEF QGO}
       {$ENDIF}

       {$IFDEF DVZ}
       {$ENDIF}

       {$IFDEF PRZ}
       {$ENDIF}

       {$IFDEF PRS}
        sta_PRS:= POStatistikaPRS(inicializuj_modul(New(POStatistikaPRS,Init(cfg_STA))));
       {$ENDIF}

       {$IFDEF SPR}
       {$ENDIF}

       tvorba_samostatnych_modulov_statistiky:= false;
       tvorba_spolocneho_modulu_statistiky:= false;
     end;



