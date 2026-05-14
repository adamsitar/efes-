   { Nastavenie parametrov pre spracovnanie sektorov
   }
    const  S_DISPLAY        : bool = {$IFDEF SECTORS} true {$ELSE} false {$ENDIF};
           S_PRINT          : bool = {$IFDEF SECTORS} true {$ELSE} false {$ENDIF};
           S_ARCHIV         : bool = true; { Z archivu sa natahuju len stripy patriace na sektor }
           S_D_IN_THROUGH   : bool = true;
           S_P_IN_THROUGH   : bool = true;
           S_ROUTE          : bool = {$IFDEF SECTORS} true {$ELSE} false {$ENDIF};
           S_IN             : bool = {$IFDEF SECTORS} true {$ELSE} false {$ENDIF};

           S_IN_KM          : int  = 5;
           S_IN_KM_lo       = 0;
           S_IN_KM_hi       = 100;

           S_EST_LIMIT      : int  = 10;
           S_EST_LIMIT_lo   = 1;
           S_EST_LIMIT_hi   = 30;

           S_DEL_LIMIT      : int  = 5;
           S_DEL_LIMIT_lo   = 1;
           S_DEL_LIMIT_hi   = 20;

           S_TOUCH          : bool = false;

           S_INP_POINT_TIME : bool = false;
           S_OUT_POINT_TIME : bool = false;

           {S_P_EST_LIMIT    : int  = 10;
           S_P_EST_LIMIT_lo = 1;
           S_P_EST_LIMIT_hi = 30;}


   { Nastavenie priznakov spracovnia sektorov
   }
    const  s_th   = 1;  { prelieta cez sektor }
           s_is   = 2;  { patri na sektor     }
           s_on   = 4;  { priznak, ze plan je zobrazeny } { ak zmenim prirority, zmena masky... }
           s_prn  = 8;  { -//-                vytlaceny }
           s_hide = 16; { potlacene zobrazenie }
           s_err  = 32;


    const  sp_fli       = $40;
           sp_abi       = $80;

    const  max_przn_fpl = 2;

           p_others     = 0;
           p_fli        = max_przn_fpl-1;

    type   Tprzn_fpl = array [0..max_przn_fpl-1] of byte;

