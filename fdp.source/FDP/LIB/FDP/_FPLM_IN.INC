(*var   SaveExit : pointer;


procedure ukoncenie;
    begin
      ExitProc:= SaveExit;

      {if lst9bMs<>nil then
         begin
           freemem(lst9bMs,poc_9bMs*sizeof(T_9bM));
           lst9bMs:= nil;
           poc_9bMs:= 0
         end;}
    end;*)

procedure initializacia_FPLM;
    var   L   : PList;
          s   : string;
          i,j : int;

    begin
      {SaveExit:= ExitProc;
      ExitProc:= @ukoncenie;}

      write('Initialize FPLM... ');

      ENABLE_FPLM:= read_cfg_bool(SYSTEMcfg,cfg_ENABLE_FPLM,ENABLE_FPLM);

      FPLM_INE   := read_cfg_bool(SYSTEMcfg,cfg_FPLM_INE,FPLM_INE);
      FPLM_INE_9 := read_cfg_bool(SYSTEMcfg,cfg_FPLM_INE_9, FPLM_INE_9);
      FPLM_INE_AP:= read_cfg_bool(SYSTEMcfg,cfg_FPLM_INE_AP,FPLM_INE_AP);

      FPLM_REGULARITA_FIR_FN:= read_cfg_str_(SYSTEMcfg,cfg_FPLM_REGULARITA_FIR_FN,FPLM_REGULARITA_FIR_FN);

      rngDEP:= Limit(read_cfg_word(SYSTEMcfg,cfg_rngDEP,rngDEP), 1,30, 0);

      {lst9bMs:= nil;
      poc_9bMs:= 0;
      L:= New(PList,Init(@fn_9bM,[],lst_cely_riadok, false,nil));
      for i:= 0 to L^.top do if (not L^.tit^[i]) and (pos(idMIL,GetPStr(L^.str^[i],2,setKomen))>0) then inc(poc_9bMs);
      if poc_9bMs>0 then
         begin
           getmem(lst9bMs,poc_9bMs*sizeof(T_9bM));
           fillchar(lst9bMs^,poc_9bMs*sizeof(T_9bM),0);
           i:= 0; j:= 0;
           while (i<=L^.top) and (j<poc_9bMs) do
             begin
               if (not L^.tit^[i]) and (pos(idMIL,GetPStr(L^.str^[i],2,setKomen))>0) then
                   begin
                     s:= GetPStr(L^.str^[i],1,setKomen);
                     lst9bMs^[j].l4 := cut_(getstr(s,2,[icao_NXIT,icao_NXT]));
                     lst9bMs^[j].mil:= cut_(getstr(s,1,[icao_NXIT]));
                     inc(j);
                   end;
               inc(i)
             end;
         end;
      Dispose(L,Done);}

      {$IFDEF PROCESS_FPLM} {$IFDEF OPL}
        pozri_pripomienky_na_FPLM (nil);
      {$ENDIF} {$ENDIF}

      {kontrola_archivu_FPLM;}
      writeln('Done.');

      {$IFDEF KRL}
       write('Initialize KRL... ');

       writeln('Done.');
      {$ENDIF}
    end;
