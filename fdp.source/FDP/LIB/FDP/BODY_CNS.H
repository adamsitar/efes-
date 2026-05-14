    const  {$IFDEF DEBUG}
             maxLKs   = 200;
             maxOBs   = 1500;
             maxRTEs  = 500;
           {$ELSE}
             maxLKs   = 300;
             maxOBs   = 1500;
             maxRTEs  = 500;
           {$ENDIF}

           minOBs     = 10;


   const   cfg_AIRBASE  = 'AIRBASE';
           przn_nadriadene_letisko = '!';

           poc_AIRBASE  : byte = 0;          { pocet vojenskych letisk, su zoradene na zaciatku LK_m }
           pos_AIRBASE  : byte = high(byte); { pozicia vlastneho letiska }
           max_AIRBASE  = {$IFDEF SK}          10
                          {$ELSE} {$IFDEF CZ}  15
                          {$ELSE}              30  {$ENDIF}
                          {$ENDIF};


   const   pos_body_KOD  = 1;
           pos_body_AFTN = 7;


           NDB_EQ : bool = false; { stotoznenie bodov, nepouziva sa uz }
