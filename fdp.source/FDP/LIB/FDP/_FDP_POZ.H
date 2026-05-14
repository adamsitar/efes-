
    type   { Zakladne stavy spracovania planu dekodovane
             do prikazov pre nalozenie s planom ...
           }

            Ppoz = ^Tpoz;
            Tpoz = (
                    poz_PLAN,            { predbezny plan/plan na dany den }

                  { poz_PREACTIVE :
                  }
                    poz_PREACTIVE,       { plan na dany den cakajuci na spracovanie }
                    poz_PROPOSED,        { navrhovany plan pred realizaciou  }
                    poz_COORDINATED,     { schvaleny/skoordinovany plan pred realizaciou }

                  { poz_ACTIVE :           aktivovany plan letu/...
                  }
                    poz_START,
                    poz_LETI,
                    poz_DALSI,
                    poz_STOJI,           { MZP,C,B     }
                    poz_MZP,
                    poz_PRIST,
                    poz_PATRAT,          { ak nie je prijata sprava o pristani }

                  { poz_CANCELED :     ukonceny
                  }
                    poz_SEDI,
                    poz_HANGAR,
                    poz_CANCELLED,       { zruseny plan ... }

                    poz_NOT_APPROVED,    { neschvaleny plan                                      }
                    poz_NOT_ACTUAL,      { neaktualny plan, mimo povoleny/planovany casovy limit }

                    poz_UNKN
                  );

            TPozs  = set of Tpoz;


    const   pozPREACT : Tpozs = [poz_PREACTIVE,poz_PROPOSED,poz_COORDINATED];

            pozACT    : Tpozs = [poz_START,
                                 poz_LETI,poz_DALSI,poz_STOJI,poz_MZP,
                                 poz_PRIST, poz_PATRAT
                                ];

            pozEST    : Tpozs = [poz_COORDINATED,
                                 poz_START,
                                 poz_LETI,poz_DALSI,poz_STOJI,poz_MZP,
                                 poz_PRIST, poz_PATRAT
                                ];

            pozFPL    : Tpozs = [poz_PREACTIVE,poz_PROPOSED,poz_COORDINATED,
                                 poz_COORDINATED,
                                 poz_START,
                                 poz_LETI,poz_DALSI,poz_STOJI,poz_MZP,
                                 poz_PRIST, poz_PATRAT,
                                 poz_SEDI
                                ];


    function  get_poz(plan_stat: string): Tpoz;


    function  _platny_plan(cas: real;
                           zr: word; zm,zd, zh,zn: byte;
                           kr: word; km,kd, kh,kn: byte;
                           stt : string;
                           pred,          { preaktivovanie planu - nacitanie }
                           nepl,          { zrusenie neaktivovaneho planu    }
                           za   : real    { zrusenie aktivovaneho planu      }
                          ): TPoz;

    function  platny_plan (cas: real;
                           zac,kon : TDatum;
                           stt : string;
                           pred,          { preaktivovanie planu - nacitanie }
                           nepl,          { zrusenie neaktivovaneho planu    }
                           za   : real    { zrusenie aktivovaneho planu      }
                          ): TPoz;
