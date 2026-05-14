    const   kod_STS  = 4;        { HOSP,A   }
            kod_REG  = 10;       { obmedzenie, u ktoreho nemam istotu }
            kod_FLO  = 3;


    const   ZZZZ = 'ZZZZ';
            AFIL = 'AFIL';       { Plan podany za letu }


          { ICAO identifikatory v poli 18
          }
    const   rmk_DATE = 'DATE';   { datum }
            rmk_DATA = 'DATA';

            rmk_EET  = 'EET';

            rmk_TYP  = 'TYP';

            rmk_COM  = 'COM';    { dolezite udaje o spojovacich prostriedkoch }
            rmk_NAV  = 'NAV';    {                  navigacnom vybaveni       }
            rmk_DAT  = 'DAT';    { datova linka }
            rmk_PER  = 'PER';    { udaje o vykonoch lietadla }

            rmk_RIF  = 'RIF';    { udaje ku zmenemu letisku }
            rmk_DEP  = 'DEP';    { ak je _13 ZZZZ alebo AFIL                 }
            rmk_DEST = 'DEST';   { letisko urcenia, ak je v 16 uvedene ZZZZ  }
            rmk_ALTN = 'ALTN';   { nahradne letisko, ak je v 16 uvedene ZZZZ }
            rmk_RALT = 'RALT';   { nazov nahradneho letiska, letisk pre trat }

            rmk_REG  = 'REG';    { poznavacia znacka lietadla, ak je ina ako identifikacia v _7 }
            rmk_SEL  = 'SEL';    { SELCAL code }
            rmk_OPR  = 'OPR';    { meno prevadzkovatela, ak nie je zrejme z pola 7, 'F' navyse index pilota }

            rmk_STS  = 'STS';    { dovod poskytnutia prednosti LPS, napr STS/HOSP }

            rmk_RMK  = 'RMK';    { ..., cislo alebo heslo ulohy UKOL, MNM...         }


          { ICAO identifikatory v poli 19
          }
            rmk_UTC  = 'UTC';
            rmk_PNT  = 'PNT';
            rmk_KIND = 'KIND';

            rmk_SSR  = 'SSR';


          { FDP identifikatory pre pole doplnene LETVISom
          }
            rmk_RPL    = 'RPL';
            rmk_PLN    = 'PLN';
            rmk_FPL    = 'FPL';
            rmk_FDA    = 'FDA';

            rmk_FDP    = 'FDP';
            rmk_SRC    = 'SRC';

          { MIL identifikatory v poliach 18,19 doplnene LETVISom
            Zvlastne identifikatory za icao_NXT,
            napr. "RMK/UKOL02 RMK/MNM2120 RMK/PLTSIMR"
          }
            rmk_INX_   = 'I';                              { Oznacenie indexu pilota pri zadani identifikacie vojenskeho letu }
            rmk_UKL    = {$IFDEF SLOVAK}  'UKL'; {$ENDIF}  { UKL/08 03 - ulohy, skratka este z federalu }
                         {$IFDEF CZECH}   'UKL'; {$ENDIF}
                         {$IFDEF ENGLISH} 'TSK'; {$ENDIF}

            rmk_AREA   = 'AREA';   { AREA/R13 R12a - priznak, ze let ma planovanu cinnost v priestoroch... }

            rmk_ACT    = 'ACT';  { ACT/... popis vykonavanej cinnosti }
            rmk_ACTgnd = 'GND';  { cinnost pozemeneho vojska v malych vyskach }
            rmk_ACTair = 'AIR';  { cinnost vo vyskach pre lietanie }

            rmk_NAME   = {$IFDEF SLOVAK}  'NAZOV'; {$ENDIF} { ak nazov priestoru nie je publikovany v AIP }
                         {$IFDEF CZECH}   'NAZEV'; {$ENDIF} { napr. pre strelnice pozemneho vojska }
                         {$IFDEF ENGLISH} 'NAME';  {$ENDIF}

            rmk_TIME   = 'TIME';
            rmk_ALT    = 'ALT';

            rmk_PLAN   = 'PLAN';
            rmk_BRK    = 'BREAK';
            rmk_END    = 'END';

            rmk_NOLAM  = 'NOLAM';
            rmk_TEST   = 'TEST';

            rmk_NIL    = 'NIL';
            rmk_0      : string = '0';

            rmk_IN     = 'IN';
            rmk_EXI    = 'EXI';



    const { identifikatory cfg suborov }

            idMIL    = 'MIL';


    function   _item_l4   (p18,item: pchar): pchar;

    function   _item_18_p (p18: pchar; sITEM: string; ind: int; var p0,pn: pchar): string;
    function   _item_18_  (p18: pchar; ITEM: string; ind: int): string;
    function   _item_18_i (p18: pchar; ITEM: string; ind,pos: int): string;
    function   _item_18_a (p18: pchar; ITEM: string): string;
    function   _item_18   (p18: pchar; ITEM: string; ind: int): string;


    procedure  _inc_18     (var _18: pchar; it: string; smer: byte);
    procedure  _dec_18     (var _18: pchar; ITEM: string);
    procedure  _update_18  (var _18: pchar; ITEM: string; smer: byte);
