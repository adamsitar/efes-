
     { a) Limity aktivovania planov, nazvoslovie sa ma chapat ako to_be_...;
          t.j. to_be_preactivated,...
     }
      const  dT_preactive_FPL4   : int = 120;   { prechod do stavu ocakavania na spracovania/ulozenie do pamate }
               dT_preactive_FPL4_lo    = 20;
               dT_preactive_FPL4_hi    = 1440;

             dT_propose_FPL4     : int = 30;    { minut pred EET/DEP }
               dT_propose_FPL4_lo      = 15;
               dT_propose_FPL4_hi      = 120;

             dT_coordinate_FPL4  : int = 20;    { limit pre aktivaciu planu }
               dT_coordinate_FPL4_lo   = 5;
               dT_coordinate_FPL4_hi   = 60;


             dT_unactive_FPL4    : int = 60; {'}  { neaktivovany plan :
                                                     if absTime > DateToSec(date.r,date.m,date.d)+secDAY+dT_unactived_FPLM*60
                                                     then z:= poz_HANGAR
                                                  }
               dT_unactive_FPL4_lo     = 5;       { if FPL^.prist.cas + cas_DEL_ACT_FPL*60 <= absTime then z:= poz_HANGAR; }
               dT_unactive_FPL4_hi     = 720;


             (*dT_deactive_FPL4  : int   = 10; {'}  { cas po ktorom odmaze aktivovany FPL, na ktory nebola vydana sprava ARR }
                dT_deactive_FPL4_lo    =  1;      { if FPL^.prist.cas + cas_DEL_ACT_FPL*60 <= absTime then z:= poz_HANGAR; }
                dT_deactive_FPL4_hi    = 60;*)



             cfg_dT_preactive_FPL4     = 'T-PREACTIVATE-FPL4';
             cfg_dT_propose_FPL4       = 'T-PROPOSE-FPL4';
             cfg_dT_coordinate_FPL4    = 'T-ACTIVATE-FPL4';
             cfg_dT_unactive_FPL4      = 'T-UNACTIVE-FPL4';
             cfg_dT_deactive_FPL4      = 'T-DEACTIVE-FPL4';


     { b) Spracovanie druhov sprav
     }
      const  process_ALR_to_FPL4 : bool = true;

             cfg_FPL4_PPL_ENABLE = 'PPL-FPL4';
             cfg_FPL4_CPL_ENABLE = 'CPL-FPL4';
             cfg_FPL4_MZP_ENABLE = 'MZP-FPL4';


      const  _FPL4_PPL_ENABLE    : bool = true;
             _FPL4_CPL_ENABLE    : bool = false;

             _FPL4_CHG_ENABLE    : bool = true;
             _FPL4_DLA_ENABLE    : bool = true;
             _FPL4_CNL_ENABLE    : bool = true;
             _FPL4_DEP_ENABLE    : bool = false;
             _FPL4_ARR_ENABLE    : bool = false;

             _FPL4_MZP_ENABLE    : bool = false;  { Povolenie pre spracovanie MZP }
             _FPL4_XG_ENABLE     : bool = false;  { Povolenie pre spracovanie X,G }


     { c1) Dekodovanie planov
     }
      const  _9b_CHECK_ICAO     : bool = true;     { kontrola na spravnost typu podla ICAO }
             _9b_CHECK_TSGA     : bool = false;    { nahradenie TSGA kodom podla ICAO, rozdiel negeneruje chybu      }
             _9b_CHECK_ZZZZ     : bool = true;     { nahradenie povodneho kodu ICAO kodom, rozdiel negeneruje chybu  }
             _9b_CHECK_MIL      : bool = {$IFDEF LZ} true {$ELSE} false {$ENDIF};
                                                   { nahradenie povodneho kodu ICAO kodom,
                                                     rozdiel negeneruje chybu
                                                   }
             _9c_CHECK_ICAO     : bool = true;     { kotrola na suhlas s ICAO 9c           }
             _9c_CHECK_ZZZZ     : bool = true;     { nahradenie/doplnenie 9c podla ICAO, rozdiel negeneruje chybu   }


             _10a_CHECK         : bool = true;
             _10b_CHECK         : bool = true;


             _15a_RANGE         : bool = false;
             _15b_RANGE         : bool = false;

             _15_RxR_ENABLE     : bool = true;  { [N]  povolenie urcenia bodu odbocenia ako priesecnika trati R1 a R2 }
             _15_BxR_ENABLE     : bool = true;  { [N]  najdi najblizsi bod ku trati }
             _15_BxR_KM         : bool = false; { povolenie nasledujucich dvoch testov }
             _15_XYxR           : int  = 50;    { [km] maximalna vzdialenost, pre ktoru sa uvazuje prepojenie bodu    }
             _15_XYxR_hi               = 100;   { daneho zemsur alebo smernikom ku trati                              }
             _15_BxR            : int  = 5;
             _15_BxR_hi         : int  = 50;

             _15_DCT_POINTS     : bool = true;  { kontrola na DCT medzi bodmi }
             _15_UPLNA_TRAT     : bool = false;
             _15_CHECK_FDA      : bool = true;  { povolenie, aby dekodovanu trat skontrolaval operator }

             _15_ALL_ENABLE     : bool = true;  {      vlozenie vsetkych bodov medzi dekodovanymi B1 a B2 do trate    }
             _15_IO_ENABLE      : bool = true;  { [N]  povolenie, aby zaciatok/koniec trasy bol uvadzany ako trat     }

             _16_PREPOCET_EST   : bool = false;

             _18_CHECK_IS       : bool = true;
             _18_CHECK          : bool = true;
             _18_TYPE_CHECK     : bool = true;
             _18_DAT_CHECK      : bool = true;
             _18_COM_NAV_CHECK  : bool = true;
             _18_DEP_CHECK      : bool = true;
             _18_DEST_CHECK     : bool = true;
             _18_ALTN_CHECK     : bool = true;
             _18_RALT_CHECK     : bool = true;

             _EFIL_8            : bool = true;  { povolenie z editora }
             _EFIL_9            : bool = true;
             _EFIL_10           : bool = true;
             _EFIL_15ab         : bool = true;

             _CHG__7_13         : bool = true;  { editacia poli 7 ,13 pri vydavani spravy CHG }
             _FPL_CHG__14_17    : bool = true;  { editacia poli 14,17 pri vydavani spravy FPL,CHG }
             _ACT__FIELDS       : bool = true;
             _ARR__FIELDS       : bool = false;

             _ACT_AS_EST        : bool = {$IFDEF EDD} true {$ELSE} false {$ENDIF};
             _ACT_OR_DEP        : bool = true;
             _AP_EET_EXI        : bool = true;

             _FPL4_CHG_REPORT   : bool = {$IFDEF DEBUG} true {$ELSE} true  {$ENDIF};
             _FPL4_DLA_REPORT   : bool = {$IFDEF DEBUG} true {$ELSE} true  {$ENDIF};
             _FPL4_CNL_REPORT   : bool = {$IFDEF DEBUG} true {$ELSE} true  {$ENDIF};
             _FPL4_DEP_REPORT   : bool = {$IFDEF DEBUG} true {$ELSE} true  {$ENDIF};
             _FPL4_ARR_REPORT   : bool = {$IFDEF DEBUG} true {$ELSE} false {$ENDIF};
             _FPL4_REPORT_PLAN  : bool = false;

             _FPL4_APROVED_DISPLAY  : bool = true;
             _FPL4_APROVED_CHECK    : bool = true;
             _FPL4_APROVED_BY_FDA   : bool = false;


     { c2) Pomocne vypoctove premenne petazujuce horenastavene konstanty
     }
      const  _fpl4_date_all     : bool = false; { pomocna premenna, povolujuca dekodovanie neaktualncyh planov }
             _fpl4_15_bxr_en    : bool = false;



     { d1) Spracovanie
     }
      const  find_and_process_FPL4 : bool = true;
             find_and_process_FDR  : bool = {$IFDEF DEBUG} true {$ELSE} true {$ENDIF};


     { d2) Zobrazenie
     }
      const  bminiFPL4            : bool = true;

             max_FPL4_5_r_hi       = 1;

             max_FPL4_15_rm : int  = 2;
             max_FPL4_15_r_lo      = 0;
             max_FPL4_15_r_hi      = 6;

             max_FPL4_18_rm : int  = 1;
             max_FPL4_18_r_lo      = 0;
             max_FPL4_18_r_hi      = 4;

             max_FPL4_19_r_hi      = 2;
             max_FPL4_20_r_hi      = 3;

             cfg_max_FPL4_15_r     = 'LINES OF FPL_15';
             cfg_max_FPL4_18_r     = 'LINES OF FPL_18';




      const  comp_IDN = 0;      { triedenie }
             comp_EET = 1;
             comp_INP = 2;
             comp_STT = 3;
             comp_UNS = 4;

             comp_FPL4 : byte = comp_IDN;

             {_FPL4_ord_fpl : bool  = true;}


     { Nastavenie parametrov tlace
     }
      const   prn_FPL4_ICAO   : bool = false;



     { e) Konstanty spracovania planov
     }
      const  _propose_dayFPL4  : bool = false;
             _unactive_dayFPL4 : bool = true;


      type   cm_spracovanie_FPL4   = word;

      const  cm_zarad_FPL4         =    $1;
             cm_check_FPL4_SRC     =   $20;
             cm_decode_FPL4_FDR    =   $40;    { nastavi len EXT, EDI to realizuje samostatne }
                                  {=   $80;}
             cm_check_FPL4_EET     =  $100;
             cm_rozosli_FPL4_EXT   =  $200;
             cm_rozosli_FPL4       =  $400;
             {cm_rozosli_FPL4_SLAVE =  $800;}

             cm_zarad_FPLC         = $1000;
             cm_rozosli_FPLC       = $2000;
             cm_decode_FPLC        = $4000;


            { Zmena tychto konstant moze vuist ku nespravnej
              postupnosti spracovania
            }
             cm_spracuj_FPL4_RPL   =    cm_check_FPL4_SRC
                                     or cm_zarad_FPL4
                                     or cm_rozosli_FPL4;

             cm_spracuj_FPL4_EXT_  =    cm_decode_FPL4_FDR;

             cm_spracuj_FPL4_EXT   =    cm_check_FPL4_SRC
                                     or cm_zarad_FPL4
                                     or cm_rozosli_FPL4;

             cm_spracuj_FPL4_EDI_  =    cm_decode_FPL4_FDR;

             cm_spracuj_FPL4_EDI   =    cm_check_FPL4_SRC
                                     or cm_zarad_FPL4
                                     or cm_rozosli_FPL4;

             cm_spracuj_FPL4_NET   =    cm_zarad_FPL4
                                     or cm_check_FPL4_EET     { udaje EET sa cez siet neprenasaju }
                                     or cm_rozosli_FPL4;

             cm_spracuj_FPL4_FPLC  =    cm_zarad_FPLC
                                     or cm_rozosli_FPLC;


             (*
             check_FPL4_SRC = 1;    { : bool = false; }
             check_FPL4_FDR = 4;    { : bool = true;    zaradi "add_FPL->FDR", len ak je FPL O.K. }
             check_FPL4_EST = 8;    { : bool = false; }
             *)



     { f) Nastavenie rozosielania do EXT linky, napr. AFTN
     }
      const  rozosielat_FPL4_EXT : bool = false;


      const  przn__not_eet__is_arr = 60;

             standartna_rych = 500; {[km]}
             standartna_vys  = 960; {[S]}


      const  is_ALR : bool = false;


      const  alt_VFR_rdp : bool = true; { povolenie vypisu VFR vysky ako VFR }
