       const  key_fua_type       = 'TYPE';
              key_fua_ref_data   = 'REF DATA';
              key_fua_msg_ref    = 'MSG REF';
              kod_fua_msg_ref    =  3;
              key_fua_fil_time   = 'FIL TIME';
              key_fua_val_period = 'VAL PERIOD';

              key_AUP            = hd_AUP;
              key_UUP            = hd_UUP;

              off_fua            = 15;

              AUP_ini            = key_aup+ext_ini;
              UUP_ini            = key_uup+ext_ini;


      const   cfg_FUA        = 'fua.ini';

              cfg_FUA_24H_EN = 'FUA -24H';
              cas_FUA_24H_EN : bool = true;     { povolena kontrola na limit opravy 24 hodin pred schvalenim }

              cfg_FUA_1H_EN  = 'FUA -1H';       { povolena kontrola na limit 1h pred schvalenim inych ako FUA priestorov }
              cas_FUA_1H_EN  : bool = true;

              cfg_FUA_1H     = '-1H';

              cfg_LIMIT_FUA_1H = 'LIMIT FUA -1H';
              cas_FUA_1H  : word = 60;


      const   cas_PRS_zac  = 6;  {00 UTC}

              cas_AUP      = 14; {00 UTC}
              den_AUP      = -1;
              cas_AUP_AA   = 12; {00 UTC}
              cas_AUP_AMC  = 14; {00 UTC}

              cas_UUP      = 09; {00 UTC}
              den_UUP      = 0;
              cas_UUP_AA   = 07; {00 UTC}
              cas_UUP_AMC  = 09; {00 UTC}


      const   dst__UP: set_fdp_src =
                        [
                         {$IFDEF LZ} {$IFDEF OPL_SMD} {$IFDEF AMC} aftn {$ENDIF} {$ENDIF} {$ENDIF}
                        ];