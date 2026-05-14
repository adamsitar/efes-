    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € METEOR                      €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }


    const dx_SYN  = 527;
          dx_SYN_ = 597;
          dy_SYN  = 72;

          dx_MET  = 470;
          dy_MET  = 52;

          pis_SYN_: bool = false;


    const dbchg_SYN : bool = false;
          {dbchg_MET : bool = false;}
          db_SYN_RIADKOV  = 1;
          db_MET_RIADKOV  = 1;

          dbattr_SYN = {$IFDEF DB_BIN} DBtxt{DBbin} {$ELSE} DBtxt {$ENDIF};


    type  MeteorSynop = record       { SYNOP,SYRED - hodinove spravy }
	    ident   : word;          { kod stanice }
	    let     : string[4];     { nazov - rozkodovany kod LZIB  }
            nazov   : pchar;{32}     { pulny nazev Bracislava }

	    qnh     : string[6];     { tlak QNH - [hPa]  <0..nedefinovan  }
            qnh_    : char;          { N - normal
                                       E - nebezpecna 1
                                       F -  -//-      2
                                       G -  -//-      3
                                       H -  -//-      4
                                     }
	    qfe     : string[6];     { tlak QFE - [hPa]  <0..nedefinovan  }
	    qfe_    : char;
	    qmu     : string[5];     { teplota [st.C ] <-99..nedefinovana }
            qmu_    : char;          { N - morm, E - nizka, F - vysoka }
	    qan_qnt : string[9];     { smer vetra a narazy }      	  { vitr - smer [stupne] -1..variable <-1..nedefinovan }
            qan_qnt_: char;          { N - norm, E- nebezp }
	    qba     : string[3];     { dohlednost [km] <0 nedefinovana }
            qba_    : char;          { N
                                       E - nizka
                                     }
	    n       : string[3];     { celkova oblacnost v osminach <0 nedefinovana }
            n_      : char;          { N
                                     }
	    qbb     : pchar;{24}     { popis vrstev oblacnosti, napr. 2/1200 3/1600 }
            qbb_    : char;          { N
                                       E - nebezpecna nizka oblacnost
                                       F - cumulus
                                     }
	    stav    : pchar;{35}     { text stavu pocasi }
            stav_   : char;          { N
                                       E - hmly,opar (zlta)
                                       F - zrazky    (zelena)
                                       G - burky     (cervena)
                                     }
            date    : Tdate;
            time    : Ttime

            {$IFDEF NET};
             rec    : Tplan_rec     { len pre StrRLP }
            {$ENDIF}
          end;


    type  MeteoMetar = record     { Metar -> }
	    ident : word;
	    let   : string[4];

	    nazov : pchar;{32}
	    line1 : pchar;{76}    { radek zpravy c.1 - max 76 }
	    line2 : pchar;{76}    { radek zpravy c.2 }

            date  : Tdate;
            time  : Ttime

            {$IFDEF NET};
             rec  : Tplan_rec     { len pre StrRLP }
            {$ENDIF}
          end;



    const  MAX_SYNs = 300;
           MAX_METs = 300;

    type   TSYN  = MeteorSynop;
           PSYN  = ^TSYN;
           PSYNs = ^TSYNs;
           TSYNs = array[0..MAX_SYNs-1] of PSYN;

           TMET  = MeteoMetar;
           PMET  = ^TMET;
           PMETs = ^TMETs;
           TMETs = array[0..MAX_METs-1] of PMET;
