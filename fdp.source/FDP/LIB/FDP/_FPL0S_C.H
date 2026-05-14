           {$IFDEF EDD}
    const   PROP_ACK_cFPL    : bool = false;
            PROP_ACK_mFPL    : bool = false;
            PROP_ACK_oFPL    : bool = false;

            PRN_cFPL         : bool = {$IFDEF PRN_STRIP} true {$ELSE} false {$ENDIF};
            PRN_mFPL         : bool = false;
            PRN_oFPL         : bool = false;
           {$ENDIF}


           {$IFDEF MAPY}
    const   draw_mFPL_en     : bool = true;  { kreslenie ... }
            draw_cFPL_en     : bool = true;
            draw_oFPL_en     : bool = true;

            draw_SSR         : bool = false;
            draw_MZP         : bool = true;
            draw_PATRAT      : bool = true;
            draw_HISTORY     : bool = true;

           { pomocne }
            OBNOVENIE_CIELOV : byte = {$IFDEF DEBUG} 3 {$ELSE} 10 {$ENDIF};
            OBNOV_CIELE      : bool = false; { add,eq,chg                             }

            draw_trgt_rte    : bool = false; { zmaze sa trat letu, ak let nie je dovolene vykreslovat ? }
            draw_trgt_his    : bool = false; { zmaze sa trat letu, ak let nie je dovolene vykreslovat ? }
           {$ENDIF}


   {$IFDEF OPL}
    const   tab_mFPL         : bool = true;     { tabulka }
            tab_oFPL         : bool = true;
            tab_cFPL         : bool = true;

            tab_mFPL_abc     : bool = true;     { triedenie vojenskych podla stavu/idn }
   {$ENDIF}
