    const
          { farby cielov        }
            cl_cFPL   = 64;
            cl_mFPL   = 192;
            cl_oFPL   = 128;

          { farby tratii        }
            cl_trat_cFPL = yellow;
            cl_trat_mFPL = green;
            cl_trat_oFPL = cyan;

            cl_zobraz_trat_FPL = yellow;


    const   TRG_color  : array[low(TTRG_stat)..high(TTRG_stat)] of byte =
                        {$IFDEF RDP_ACCEPT} {$IFDEF CZ} (60, 61);
                                            {$ELSE}     (60, 61);
                        {$ENDIF}
                        {$ELSE}                         (yellow, yellow);
                        {$ENDIF}


    {$IFDEF MAPY}
      const ds_HISTORY     = 2000;
            dx_ZOBRAZ_TRAT : int = {$IFDEF UKBB} 400 {$ELSE} 500 {$ENDIF};
            dy_ZOBRAZ_TRAT : int = 300;
    {$ENDIF}