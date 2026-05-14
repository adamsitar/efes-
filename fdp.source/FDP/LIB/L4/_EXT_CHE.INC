procedure O_EXT.check0;
    begin
      if not power then Exit;

      read_inp_buff;
      ibuff_read;
      pbuff_read;

      manage_connection; { kvoli vcasnym heartbeatom }
    end;

procedure O_EXT.check;
    begin
      if (p_power<>nil) and (p_power^<>power) then power:= p_power^;
      if not power then Exit;

      manage_lam;
      manage_archiv;
      if not manage_alert then manage_error;
    end;


function  O_EXT.manage_connection: bool;
   const  lm : byte = 60;
          lh : byte = 24;
   begin
     manage_connection:= false;
     if not power then Exit;

     if (lh<>hour) or (lm<>min) then
        begin
          if CISLO_SPRAVY24h and (hour=0) and (min=0) then
             begin
               CISLO_SPRAVY:= 0;
               save_cislo(CISLO_SPRAVYcfg,CISLO_SPRAVY);
             end;
          lh:= hour;
          lm:= min;
          manage_connection:= true
        end;

     isTrTimeOut:= Tr_+TrTimeOut<=absTime;
   end;



{ b) pretoze este nie je vytvoreny autaomaticky archivny zoznam,
     do ktoreho sa vkladaju spracovane subory, objekt si ich musi
     skontrolovat sam
}
function  O_EXT.manage_archiv: bool;
   const  L_ARCH : byte = 24;
          S_ARCH : bool = false;
   begin
     if not power then Exit;

     if (not S_ARCH) and (L_ARCH<>hour) then
        begin
          S_ARCH:= true;
          L_ARCH:= hour;

          zmaz_stare_subory (pathSTREAM,allfiles,24*ArchDays);
          zmaz_stare_subory (pathSTREAM,'*.'+ext_DEL,24);
          zmaz_stare_subory (pathSTREAM,NETreceived_file_name('*.'+ext_DEL),24);

          zmaz_stare_subory (pathERR+path_NOT_PROCESSED, allfiles, 24*ArchDays);

          archivuj_subory   (pathERR,_fn_ERRmask(ext_ERR), pathERR+path_NOT_PROCESSED, false, by_hours);
          archivuj_subory   (pathERR,_fn_ERRmask(ext_ERS), pathERR+path_NOT_PROCESSED, false, by_hours);

          initialize_ERR(true);

          S_ARCH:= false;
          manage_archiv:= true
        end
     else manage_archiv:= false
   end;


function  O_EXT.manage_alert: bool;
   const  S_ALR : bool = false;
   begin
     if not power then Exit;

     manage_alert:= false;
     { d) nacitanie ALERT, ak su
     }{$IFDEF ALR}
       (*if (not semaphor_ALR) and is_ALR then
          begin
            semaphor_ALR:= true; {read_ALERT_pkt; is_ALERT_pkt:= _is_ALERT_pkt(ext);}
            {$IFDEF STATUS} btALR^.visibility(is_ALR); {$ENDIF}
            semaphor_ALR:= false
          end;
       *)
      {$ENDIF}
   end;


{ c) spracovanie chybovych sprav
}
function  O_EXT.manage_error: bool;
   const  S_ERR : bool = false;
   var    ep : type_ext_err_pkt;
   begin
     if not power then Exit;

     manage_error:= false;

    {$IFDEF ERR}
      if process_err_en and is_ERR and (not ({S_ALR or} S_ERR)) then
         begin
           S_ERR:= true;
           if icao_ERR_DISPLAY then
              begin
                _read_ERR(ext_ERR,
                        @init_icao_editor_err,@handle_icao_editor_err,
                        nil{hlp_AFTNERR}, is_ERR
                       )
              end
           else begin
                  fillchar(ep,sizeof(ep),0);
                  ep.fn:= pathERR+najstarsi_subor(pathERR,_fn_ERRmask(ext_ERR));
                  if _read_txt_file(ep.fn,true,ep.err,ep.pkt) then
                     begin
                       _save_ERR(pchars(ep.pkt),strlen(ep.pkt),ep.err, ext_ERS, is_ERS, false,true);
                       strdispose(ep.pkt);
                       ep.fn:= najmladsi_subor(pathERR,_fn_ERRmask(ext_ERR));
                       is_ERR:= ep.fn<>''
                     end
                end;
           manage_error:= true;
           S_ERR:= false
         end;
    {$ENDIF}
   end;


 function O_EXT.is_master_line: bool;
    var   bres: bool;
    begin
      if p_master_line<>nil then bres:= p_master_line^ else bres:= true;
      is_master_line:= bres;
    end;

 function O_EXT.is_distribute_pkt: bool;
    var   bres: bool;
    begin
      bres:= is_master_line;
      is_distribute_pkt:= bres;
      {$IFDEF BACKUP}
        is_distribute_pkt:= (not SERVERstatus) or (not bres)
      {$ENDIF}
    end;

 function O_EXT.is_receive_pkt: bool;
    var   bres: bool;
    begin
      bres:= is_master_line;
      is_receive_pkt:= bres;
      {$IFDEF BACKUP}
        is_receive_pkt:= (not SERVERstatus) or (not bres)
      {$ENDIF}
    end;

