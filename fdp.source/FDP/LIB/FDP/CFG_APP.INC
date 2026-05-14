{ -------------------------------------
   vymena konfiguracie medzi stanicami
  -------------------------------------
}

 procedure TFDPapp.get_app_config (typ : Tnd_typ; sw : Tnd_sw; nd : Tnd_nd;
                                   var data: pchars; var size: word
                                  );
     var   s: string;
     begin
       s:= ''; data:= nil; size:= 0;
       if typ in [RDP,RDP0NX] then
          begin
            s:= chr(ord(FDP))+chr(ord(RDP))+' ';

           {$IFDEF FPL0}
            s:= s + cfg_DEACTIVE_FPLC + odd_CFG_EQ + cstr(dT_deactive_FPLC,2) + '; ';
            s:= s + cfg_DEACTIVE_NOPL + odd_CFG_EQ + cstr(dT_deactive_NOPL,2) + '; ';
            s:= s + cfg_DEACTIVE_FPLM + odd_CFG_EQ + cstr(dT_deactive_FPLM,2) + '; ';
            s:= s + cfg_WARNING_FPLM  + odd_CFG_EQ + cstr(dT_arr_warn_FPLM,2) + '; ';
           {$ENDIF}

           {$IFDEF PRS}
            s:= s + cfg_PROPOSE_PRS  + odd_CFG_EQ + cstr(dt_propose_PRS, 2) + '; ';
            s:= s + cfg_DEACTIVE_PRS + odd_CFG_EQ + cstr(dT_deactive_PRS,2) + '; ';
           {$ENDIF}
          end;

       size:= length(s);
       if size>0 then
          begin
            getmem(data,size);
            move(s[1],data^,size)
          end
     end;

 procedure TFDPapp.set_app_config (const data: pchars; size: word);
     var   s : string;
           p : word;
     begin
       size:= minimum(size,sizeof(s)-1);
       s[0]:= char(size);
       move(data^,s[1],size);

       {if copy(s,1,3) = chr(ord(BSERVER))+chr(ord(EDD))+chr(ord(SLAVE)) then
          begin
          end;}

       inherited set_app_config (data,size)
     end;


 procedure TFDPApp.distribute_app_config;
     var   data : pchars;
           size : word;
           nd : int;
     begin
       for nd:= 0 to NODEpoc-1 do
         begin
           data:= nil; size:= 0;
           get_app_config (NODEs^[nd].desc.typ, NODEs^[nd].desc.sw, NODEs^[nd].desc.nd, data,size);
           if size<>0 then NETsend_msg (NODEs^[nd].desc.adr, spr_CONFIG, data,size, false,net_flag_SEND);
           FreeMem (data,size)
         end
     end;


{ ----------------------------------
   nacitanie konfiguracie programu
  ----------------------------------
}

 function  TFDPapp.ReadProgramCfg (cfg_fn: string; _dialog: bool): bool;
    begin
      ReadProgramCfg:= apReadProgramCfg (cfg_fn,_dialog);
      change_gm(GraphMode,false,false);
      archivuj_cfg(cfg_fn);
    end;

 procedure TFDPapp.SaveProgramCfg (cfg_fn: string);
     begin
       if cfg_fn='' then Exit;
       apSaveProgramCfg (cfg_fn);
       send_mail(@Self,MainApp,cmCFG_SAVED,all,@cfg_fn[1],length(cfg_fn));
     end;


{ -----------------------------------
   uzivatelska konfiguracia programu
  -----------------------------------
}
 function  TFDPapp.ReadUserCfg (_Event: TEvent): bool;
    var    cfg_fn : string;
           bres : bool;
    begin
      SaveProgramCfg(USER_CFG); { ulozenie posledneho aktivneho konfiguraku }      bres:= false;
      cfg_fn:= '';

      if isCommand(_Event,cmCFG_DEFAULT) then
         begin
           cfg_fn:= APP_CFG;
           USER_CFG:= APP_USER_CFG
         end
      else begin
             cfg_fn:= vrat_meno_uzivatela(ext_usa,_Event.Command-cmCFG_USER_lo);
             USER_CFG:= cfg_fn
           end;

      if cfg_fn<>'' then
         begin
           bres:= ReadProgramCfg (cfg_fn,true);
           {if bres then} send_mail(@Self,MainApp,cmCFG_LOADED,all,@cfg_fn[1],length(cfg_fn));
         end;

      ReadUserCfg:= bres
    end;


 procedure TFDPapp.SaveUserCfg;
     var   fn: string;
     begin
       fn:= zadaj_meno_uzivatela (exe,ext_usa);
       if fn='' then Exit;
       USER_CFG:= fn;
       SaveProgramCfg (fn);
     end;
