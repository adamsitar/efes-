     const  SPR_LINE  = MTK_2_LINE;

     const  db_SPR0_RIADKOV  = 3;

            db_SPR_LTL       = DB_znakov div SPR_LINE;   { Lines (of mess...) To Lines (DB...) }
            db_SPR_RIADKOV   = 1 + (max_SPR_r_hi+1) div db_SPR_LTL + 1;

            db_SPR_data      = 0;
            db_SPR_text      = 1;
            db_SPR_ine       = db_SPR_RIADKOV-1;

            dbchg_SPR  : bool  = false;
            dbattr_SPR = {$IFDEF DB_BIN} DBtxt {$ELSE} DBtxt {$ENDIF}; { Este nie je spraveny prevod pola "text" do bin }


     type   PSPR = ^DSPR;
            DSPR  = record
              typ  : Thead_ICAO;
              prty : string[kod_MTK_2_PRTY];

              ods  : TNETadr;           { adresa odosielatela }
              adr  : pchar;             { TNETadr-s; }

              text : pchar;             { array [0..RDKV_SPR-1] of }

              cis  : word;
              dap  : TDatum;            { datum podania }
              daz  : TDatum;            { zobrazenia    }
              acs  : Tspr_acc;          { prevzatie... na odoslanej alebo vlastnej }

              {$IFDEF NET}
               rec : Tplan_rec;
               acc : array[0..maxNODEs-1] of Tspr_acc;
               { zisla by sa tu i premenna, kde by sa zapisovali casy zobrazenia spravy "daz" }
              {$ENDIF}
            end;


     const  MAX_SPRs = 300;

     type   PSPRs = ^TSPRs;
            TSPRs = array[0..MAX_PTRs-1] of PSPR;
