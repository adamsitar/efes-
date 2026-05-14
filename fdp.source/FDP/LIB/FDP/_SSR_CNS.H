    const { rozsahy spracovanych udajov
          }
           kod_rbs_SSR = 4;   set_rbs_SSR : TCharSet = ['0'..'7'];
           kod_uvd_BN  = 5;   set_uvd_BN  : TCharSet = ['0'..'9'];

    const { chybove hlasenia
          }
           a_SSR              = 'SSR';         { typ chyb pre alokaciu SSR }

           err_ssr_invalid    = 1;
           err_ssr_octal      = 2;
           err_ssr_number     = 3;

           err_ssr_not_cfg    = 10;
           err_ssr_is_used    = 20;
           err_ssr_time_out   = 21;
           err_ssr_noavaible  = 30;
           ask_ssr_none       = 40;

           tit_ssr_used_codes = 'Used ssr codes';


    {$IFDEF SSR_MANAGEMENT}

     const { indentifikatory ini subora
           }
            SSR_CFG              = 'SSR.INI';

            cfg_SSR_CODE         = 'SSR CODE';
            cfg_SSR_MIL          = 'SSR MIL';
            cfg_SSR_NEXT_USE     = 'SSR NEXT USE';
            cfg_BOARD_NUMBER     = 'BOARD NUMBER';
            cfg_BOARD_NUMBER_MIL = 'BOARD NUMBER MIL';


     const { nastavenie programu
           }
            SSR_NEXT_USE       : word = 120;    { zatem nebudet dejstvovat }
            SSR_NEXT_USE_lo    =   0;
            SSR_NEXT_USE_hi    = 240;
            SSR_NEXT_USE_KEEP  : bool = true;   { dodrziavat limit pre nasledujuce pouzitie kodu ssr }

            (*SSR_LIST           : bool = true;   { ponuknut vsetky mozne kody }
            SSR_ASSIGN         : bool = false;  { vkladat automaticky ? }
            SSR_NOT_CFG        : bool = false;  { mozu byt zadane nekonfigurovane kody ? }*)


     const { zaznam v db
           }
            fn_db__ssr_     = pathDB+'ssr'+'.';
            fn_db__ssr      = fn_db__ssr_+extDB;
            fn_db__ssr_err  = fn_db__ssr_+extERR;

            dbattr_SSR      = DBbin;
            db_SSR_RIADKOV  = 1;

     const  is_SSR_ERR : bool = false;

    {$ENDIF}