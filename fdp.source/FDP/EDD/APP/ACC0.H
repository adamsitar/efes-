        { ------------------------------
          konfiguracie
          ------------------------------
        }

    const  cfg_TABLET      = 'tablet';

           TABLET_CFG      = cfg_TABLET+ext_ini;
           ext_tbl         = '.tbl';
           APP_TABLET_CFG  = exe+ext_tbl;
           USER_TABLET_CFG : string = exe+ext_tbl;

           SORT_CFG        = 'SORT'+ext_tbl;
           setTABLET_CFG   : Tcharset = [','];  { oddelovace }


        { ------------------------------
          predpis na zoradenie NDB
          ------------------------------
        }

    const max_stlpec  = 4;
          max_skupin  = {$IFNDEF EDD_20} 8 {$ELSE} 9 {$ENDIF}; { maximalny pocet majakov v stlpci }
          max_rdkv_   : array[false..true] of int = (max_skupin*2,max_skupin*2*2-3);


    const kod_zoznam  = 15;             { nazov skupiny stripov }


    type  TpopisSkupina = record
            NDB  : string[kod_zoznam];
            NDBs : pchar;
          end;
          TpopisStlpec  = array[0..max_skupin-1] of TpopisSkupina;
          TpopisTablet  = array[0..max_stlpec-1] of TpopisStlpec;

          PpopisSkupina = ^TpopisSkupina;
          PpopisStlpec  = ^TpopisStlpec;
          PpopisTablet  = ^TpopisTablet;



        { ------------------------------
          predpis na triedenie na NDB
          ------------------------------
        }

    type  TSORT_NDB = record
            NDB     : string[kod_zoznam];
            sort_by : Tsort_strip;
          end;

          PSORT_NDBs = ^TSORT_NDBs;
          TSORT_NDBs = array[0..max_BODY] of TSORT_NDB;
