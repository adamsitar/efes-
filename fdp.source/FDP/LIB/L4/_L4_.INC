constructor O_L4444.Init
             (
               _Owner   : PObject;
               _p_power : pbool;
               _cfg_FN  : string;

             { nastavenia : potvrdenia, linka
             }
               _lam: int; _async : bool;

             { spracovavany paket
             }
               _ipkt_size, _ibuff_size: word; _is_ibuff0: bool;
               _pbuff_size: word;

             { synchronizacia/zalohovanie
             }
               _spr_send_ext,
               _spr_new,_spr_prd,_spr_ed,_spr_del,
               _spr_err,_spr_err_ed,_spr_err_del,
               _spr_items_del,_spr_item_del : TNETtyp;
               _sync_info,_coor_info : pchar;

             { spracovaven spravy
             }
               _p_heads_ICAO: Pheads_ICAO; _heads_ICAO: word;
               _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

             { archivacne premenne
             }
              _p_wr, _p_arch, _p_utc : pointer;
              _cl_s, _cl_r : byte;
              _pathSTREAM,_pathERR, _ext : string
             );
      begin
        inherited Init(_Owner,
                       _p_power,
                       _cfg_FN,

                       _lam,_async,

                       _ipkt_size,_ibuff_size,_is_ibuff0,
                       _pbuff_size,

                       _spr_send_ext,
                       _spr_new,_spr_prd,_spr_ed,_spr_del,
                       _spr_err,_spr_err_ed,_spr_err_del,
                       _spr_items_del,_spr_item_del,
                       _sync_info,_coor_info,

                       _p_heads_ICAO, _heads_ICAO,
                       _p_heads_LAM,  _heads_LAM,

                       _p_wr, _p_arch, _p_utc,
                       _cl_s, _cl_r,

                       _pathSTREAM,_pathERR, _ext
                      );

        is_4444:= true;
        send_empty_l4_arr:= false;
      end;


function O_L4444.read_cfg(_cfg_FN: string): bool;
   var   s: string;
   begin
     read_cfg:= inherited read_cfg(_cfg_FN);

     {$IFDEF FPL4}
       send_VFR_FPL:= read_cfg_bool(_cfg_FN, cfg_send_VFR_FPL, true);

       if not read_cfg_str(_cfg_FN,cfg_FL_from_alt,s) then FL_from_alt:= 0
       else FL_from_alt:= MtoFL(get_altM(getchar(delchar(s,setCisl_)),getint(s,1,setPism_)));
       if FL_from_alt=0 then FL_from_alt:= MtoFL({get_altM(' ',}alt_VFR{)});
     {$ENDIF}

     {$IFDEF RPL}
       rpl_hour := read_cfg_word(_cfg_FN,cfg_RPL_hour, rpl_hour);
       rpl_min  := read_cfg_word(_cfg_FN,cfg_RPL_min,  rpl_min);
     {$ENDIF}

     {if res<>'' then RunError(_cfg_FN+' -> item "'+res+'" is missing.');}
   end;

