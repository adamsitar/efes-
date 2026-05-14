constructor O_L4_FDP.Init
             (
               _Owner : PObject;
               _p_power : pbool;
               _cfg_FN, _cfg_OB : string;

             { nastavenia : potvrdenia, linka
             }
               _lam: int; _async: bool;

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
        _mil_sys:= true;

        spracovanie_fpl4:= false;

        _l4444m:= false;
        est_alt_:= altFL;
        _dct_points:= true;

        _error_fda:= false;
        _nolam_fda:= false;

        inherited Init(_Owner,
                       _p_power,
                       _cfg_FN,

                       _lam, _async,
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

        cfg_OB:= _cfg_OB;
        poloziek_ESTc_bodov:= 1;
      end;


function O_L4_FDP.read_cfg(_cfg_FN: string): bool;
    begin
      read_cfg:= inherited read_cfg(_cfg_FN);
      {dr_OB := read_cfg_real(_cfg_FN, cfg_dr_OB, 0);}
      _error_fda:= read_cfg_bool(_cfg_FN,cfg_error_fda,_error_fda);
      _nolam_fda:= read_cfg_bool(_cfg_FN,cfg_nolam_fda,_nolam_fda);
      _oat_exclude:= read_cfg_bool(_cfg_FN,cfg_oat_exclude,false);
      _exclude_uknown_points:= read_cfg_bool(_cfg_FN,cfg_exclude_uknown_points,false);
      read_cfg:= true
    end;

