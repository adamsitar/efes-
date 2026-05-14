    {
    ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
    Û                             Û
    Û civilny FPL                 Û
    ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
    }
    { Poznamky:

       - vyska je uvadzana v desiatkach [m], Sxxxx,
         tak je to i v subore
    }


    const  {max_bod_FPLc     = strip_max_bod;}
           max_bod_FPLC      = {$IFDEF FPLC_L} 12 {$ELSE} strip_max_bod {$ENDIF};
           {max_arch_lines   = 6;}

           db0_cFPL_RIADKOV  = {$IFDEF FPLC_L} 2 {$ELSE} 1 {$ENDIF};
           db_cFPL_RIADKOV   = 4;

           db_cFPL_data      = 0;
           db_cFPL_15_1      = 1;
           db_cFPL_15_2      = 2;
           db_cFPL_ine       = 3;

           dbchg_cFPL : bool = false;
           dbattr_FPC = {$IFDEF DB_BIN} DBbin {$ELSE} DBtxt {$ENDIF};


    type    Tc_trat  = array[0..max_bod_FPLC-1] of TOB;
            PTc_trat = ^Tc_trat;

    type    PDcFPL = ^DcFPL;
            DcFPL  = record

            { Data :
            }
              idn    : string[kod_7a];   { identifikacia            }

              ssr0   : string[kod_7c];   { ssr pred vstupom do FIR  }
              ssr    : string[kod_7c];   { SSR                      }

              _8a,_8b : char;            { pravidla a typ planu podla ICAO }

              typ    : string[kod_9];

              com_   : string[kod_10a];  { vybavenie            }
              ssr_   : string[kod_10b];


              {$IFDEF RVSM}
                _80  : char;             { typ letu, 'X' ak nie je znamy
                                           -> zatial sa neposiela
                                              je potrebne dorobit dekoder
                                         }
                _81  : string[2];        { vybavenie [EQ,NO,UN,EX,SU]
                                           spravne by to malo byt pchar;
                                           pr. -81/W/EQ Y/NO
                                           -> cast Y sa zatial neposiela
                                         }
              {$ENDIF}

              rych   : single;           { rychlost             }
              rych_  : char;             { velicina rychlosti   }

              vys    : word;             { [vysOB]              }
              vys1   : word;             { vstupna vyska na hranici do sektora }
              vys1_a : char;             { priznak tendencie vysky }
              vysO   : word;             { vyska na vystupnej hranici z riadenej oblasti }
              vysO_a : char;             { priznak tendencie vysky  }
              vysH   : word;             { cielova vyska v nasledujucej oblasti }

              start  : TAP;              { letisko startu       }
              start_ : TCas;             { cas oneskorenia      }
              prist  : TAP;              { letisko pristatia    }
              inf    : string[kod_7a+1];

             { cislo : word;                 cislo stripu       }
              date   : TDate;            { datum vstupu letu do FIRu }
              eet    : TTime;

              trat   : Tc_trat;
              bodov  : int;              { pocet bodov na trati + 1 }
	      na_bod : byte;             { bod, na ktory leti   }

             { vypoctove premenne :
             }
              stt    : string[kod_HEAD]; { musi byt "EST" alebo "CPL" }
              cor_   : byte;             { oprava : kolkokrat ?       }

              {IFDEF SECTORS}
                T1,Tn : real;            { cas vstupu na/vystupu zo sektora }
                B1,Bn : byte;            { index vstupneho/vystupneho bodu na trati }
                sec   : byte;            { priznak spracovanina : patri, zobrazenie, tlac }
              {ENDIF}

              {IFDEF RDP}                { FDP_EDD musi byt vo vsetkych prepojenych staniciach FDP }
                TRG   : TTRG_stat;
                RDP   : TRTRadr;         { accept na RDP stanici }
                LAM   : word;            { Tplan_rec }
              {ENDIF}

              {$IFDEF MAPY}
                mapa  : PMapData;
              {$ENDIF}

              {$IFDEF NET}
                rec   : Tplan_rec;
              {$ENDIF}

              przn   : Tprzn_fpl;        { priznak spracovania, prenasa sa }

              {$IFDEF PVO}
               rec_cas : TTime;          { cas prveho prijatia spravy }
              {$ENDIF}


            { vypoctove premenne, ktore sa neukladaju do db :
            }
              smer   : char;             { smer letu, urci sa podla vysky/orientacie trate }

              poz    : Tpoz;             {  }
              sur    : Tsur;

              {$IFDEF EDD}
                board : bool;
              {$ENDIF}
            end;

            DFPLC  = DcFPL;
            PFPLC  = PDcFPL;



      procedure new_cFPL   (FPL1, FPL2: PDcFPL);
      function  new_cFPL_  (FPL1: PDcFPL; var FPL2: PDcFPL): PDcFPL;

      procedure disp_cFPL  (FPL: PDcFPL); far;
      procedure disp_cFPL_ (var FPL: PFPLC);

      procedure copy_cFPL_ (FPL1, FPL2: PDcFPL; new_plan: bool);


      function  regularita_casov_na_bodoch_cFPL (FPL: PDcFPL; oprav: bool): int;

      procedure format_trat_cFPL (Trat: PTrat; max_bodov: byte;
                                  _vys: word; _vys_: char;
                                  date: Tdate; eet: TTime;
                                  var start,prist: TAP;
                                  var bodov: int; var na_bod: byte;
                                  var _poz: Tpoz
                                 );

      procedure format_cFPL_ (FPL: PDcFPL);
