           { doplnit i dalsie polozky: typ handlera, parametre DB...
           }

    type    PPLAN  = ^TPLAN;
            TPLAN  = object(TArray)

             { tieto premenne nahradi predefinovanie typu pre plan na objekt
             } p_eq         : pointer;    { TBfunc_p2 -> porovnanie }
               p_id         : pointer;    { TSFunc_p  -> vrati identifikaciu  }
               p_chg        : pointer;    { TBfunc_p2 -> bol zmeneny ? }

               p_poz        : pointer;    { TPozFunc_pvb-> vypocet pozicie    }
               p_est        : pointer;    { TBFunc_p;  -> is_to_add           }
               p_codekey    : pointer;


             { parametre pre DB
             } p_save       : pointer;    { P_p         -> ulozenie planu     }

               p_nameDB,
               p_decodeDB   : pointer;
               riadkovDB    : byte;

               fn_dir       : string[80];
               fn_ext       : string[3];  { predpokladam FDP konvenciu pri pridelovani mien }

               add_pos        : TPozs;    { mnozina povolenych stavov }

               p_act          : pointer;  { RFunc_p vrati cas preaktivacie pre plany daneho typu }
               p_limit_ad3    : pint;     { horma hranica  }
               next_addTime   : real;     { najblizsi cas preaktivacie dalsieho planu }

               denny_subor     : bool;
               den_nacitania   : byte;
               preaktivovanie  : bool;     { povolenie automatickeho nacitania }
               preaktivujesa   : bool;
               tit_preactivate : string;

               {p_limit_act,}
               p_limit_add,               { pocet minut pred planovanou aktivaciou, ked sa plan zaradi medzi ostatnie }
               p_limit_cnl,               { pocet -//- po planovanom ukonceni, ked sa plan odmaze spomedzi preaktivovanych }
               p_limit_del    : pint;     { pocet -//- po planovanom ukonceni, ked sa plan odmaze spomedzi aktivnych }
               last_addTime   : real;     { cas posledneho prehladania subora planov }

               last_limit_add,
               last_limit_del,
               last_limit_cnl : int;


             { sektor
             } p_is_in_S   : pointer;  { TBFunc_p : patri do sektoru ? }
               hidding     : bool;


             { zobrazenie
             } item_list      : pointer;
               item_medzera,item_dxi,item_dyi,item_bg : byte;
               item_dx,item_dy : int;
               get_item_dx, get_item_dy : pointer;

               {$IFDEF MAPY}
                is_map     : bool;     { natahuje sa automaticky plan ako mapa na planzet ? }
                {p_id_map  : pointer;}
                p_GrOb     : pointer;  { Tproc_p2 }
                tit_GrOb   : string;
                cl_trat    : byte;
                p_kresli   : pointer;  { TProc_p   -> zobrazenie trate    }
                typ_mapy   : word;     { planovany+GRPprty_act_=aktivny   }
                map_wrng   : bool;
               {$ENDIF}


             { viewer-y
             } p_viewer       : PScrollInd;
               viewer         : PScrollInd;
               p_comp         : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
               p_handler_type : TScrollAct_handler_type;
               p_handler      : pointer;
               p_zobraz       : pointer;  { TBFunc_ps -> zobrazenie planu             }


             { tlac
             } p_PRN          : pbool;    { @bool -> povolenie tlace         }
               p_print        : pointer;  {       -> tlac                    }

               hlpXXX         : Pchar;


             { rozoslanie
             } p_distribute   : pointer;  { TNET_distribute_rdp_pkt  }
               p_send         : pointer;  { TNET_send_pkt }
               p_message      : pointer;  { TNET_message_pkt }


             { spracovanie
             } p_spracuj      : pointer;  { TProc_p   -> spracovanie planu po prijme  }
               p_formular     : pointer;  { TBFunc_ps -> oprava                       }


             { vypoctove premenne
             } s_loadDB   : bool;
               s_pocitam  : bool;

               {lst_chg    : tick_counter;  pole bolo aktualizovane }

               rozoslat,tlacit,vypisovat : bool;



             { inicializacia
             }

               constructor Init(_items,_data_size : word;

                                _new_item,
                                _format_item,
                                _disp_item : pointer;

                                _eq,
                                _id,
                                _chg,
                                _poz,
                                _est{,
                                _act} : pointer;

                                _distribute : pointer;  { TNET_distribute_rdp_pkt  }
                                _send       : pointer;  { TNET_send_pkt }

                                _item_list  : pointer;
                                _item_dx,_item_dy : int;
                                _get_item_dx,_get_item_dy : pointer;
                                _p_viewer : PScrollInd;
                                {$IFDEF MAPY}
                                  _p_kresli : pointer;
                                {$ENDIF}

                                var _p_PRN  : bool;
                                _p_print    : pointer;

                                _save       : pointer;
                                _zobraz     : pointer;
                                _formular   : pointer;
                                _p_comp     : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
                                _p_handler  : pointer;

                                {_fn_ext : string; }
                                _p_nameDB, _p_decodeDB : pointer;
                                _riadkovDB : byte;
                                _p_codekey : pointer;

                                {_limit_act,} _limit_add, _limit_cnl, _limit_del : pint;
                                _preaktivovanie : bool;

                                _hlpXXX    : Pchar
                               );

               destructor  Done; virtual;

               procedure   check(zmena: bool); virtual;

               procedure   inicializacia_udajov(zac: bool); virtual;


             { predefinovane odvodene funkcie
               pre zaradenie/zrusenie udajov
               ako preaktivovaneho planu
             }
               procedure  plan_added (p: pointer); virtual;            { bol zaradeny plan }
               function   plan_add (p: pointer; _ires: pint; _poz: ppoz): int; virtual;
               function   Add (p: pointer): int; virtual;              { zaradi a vypise }

               function   Eq (ind: int; p: pointer): bool; virtual;

               procedure  plan_deleted; virtual;             { bol zaradeny plan }
               procedure  Del (ind: int); virtual;           { zmaze a Del     }


               function   eq_plan  (pi, p: pointer): bool; virtual;
               function   chg_plan (pi, p: pointer): bool; virtual;

               function   find     (p: pointer): int;
               function   find_id  (id: string): int;
               function   find_key (key: string): int;

               function   sort: bool; virtual;


             { zaradenie/spracovanie - na rdp,sektor/tlaciaren...
             }
               function   is_plan    (p: pointer): bool; virtual;
               function   is_to_chg  (p1,p2: pointer): bool; virtual;

               function   is_to_add  (p: pointer; var poz: TPoz): bool; virtual;  { je pre- alebo aktivny ? }
               function   is_to_addS (p: pointer): bool; virtual;                 { patri na sektor         }
               function   is_to_addP (p: pointer): bool; virtual;                 { vytlacit prijaty plan   }



             { vypis/odmazenie
             }
               function   vypis_plan(ind: int; _sort,_novy: bool): bool; virtual;
               procedure  zmaz_plan (ind: int; _zrus: bool); virtual;

              {$IFDEF MAPY}
               { definuje sa jednoznacny kluc pre indentifikaciu planu medzi mapami,
                 lebo nazov mapy (napr priestor) moze byt pouzity viacnasobne...
               }
                function  get_id_map   (p: pointer; count: int; var map_naz: string): bool; virtual;
                function  _zapni_mapu  (p: pointer; map_naz: string; p_NewOb: pointer; PIS: bool): PMapData;

                procedure _nenajdena_mapa_pre_plan (p: pointer; naz,msg: string); virtual;
                procedure _zobraz_plan_na_mape (p: pointer; PIS: bool); virtual;
                procedure zobraz_plan_na_mape  (p: pointer); virtual;
                procedure _zmaz_plan_na_mape   (p: pointer; _del: bool; PIS: bool); virtual;
                procedure zmaz_plan_na_mape    (p: pointer; _del: bool); virtual;

                procedure vykresli_plan_na_mape (p: pointer);
              {$ENDIF}


             { -------------------------------------------------
                precitanie, nastavenie a spracovanie parametrov
               -------------------------------------------------
             }
               function   get_cor     (p: pointer): int; virtual;
               procedure  set_cor     (p: pointer; cor: int); virtual;
               procedure  cl_cor      (p: pointer); virtual;

               function   get_flag    (p: pointer; group: byte): byte; virtual;
               procedure  set_flag    (p: pointer; group,flag: byte); virtual;

               function   get_id  (p: pointer): string;
               function   get_key (p: pointer): string;
               function   get_poz (p: pointer): Tpoz; virtual;

               function   get_priznak (p: pointer): byte; virtual;
               procedure  set_priznak (p: pointer; przn: byte; save: bool); virtual;

              {$IFDEF PRN}
                function  get_printed (p: pointer): bool; virtual;
                procedure set_printed (p: pointer; was: bool); virtual;

                function  tlac_en: bool;
                function  tlac (p: pointer; vzdy: bool): bool; virtual;
              {$ENDIF}

              {$IFDEF SECTORS}
                function  get_on_sector  (p: pointer): bool; virtual;
                procedure set_on_sector  (p: pointer; _on_sector: bool); virtual;

                function  urc_platnostS  (p: pointer): bool; virtual;
              {$ENDIF}

              {$IFDEF EDD}
                function  nmb_on_board: int;

                function  get_on_board (p: pointer): bool; virtual;
                procedure set_on_board (p: pointer; _on_board: bool); virtual;

                function  is_to_board  (i: int): bool; virtual;
                procedure put_on_board (p: pointer; _vis : bool);
              {$ENDIF}

              {$IFDEF NET}
        {A}     function  get_rec (p: pointer): Pplan_rec; virtual;
              {$ENDIF}


             { --------------------
                spracovanie planov
               --------------------
             }

             { nastavenie platnosti
             }
               function   stav_planu   (p: pointer; cas: real; var zmena: bool): Tpoz; virtual;
               function   urc_platnost (p: pointer; var zmena: bool; kresli: bool): Tpoz; virtual;

               function   zmenene_parametre_platnosti: bool; virtual;

               function   spolocna_preaktivacia: bool; virtual;
               function   cas_pre_preaktivaciu_planov: bool; virtual;
               function   cas_pre_preaktivaciu_planu: bool; virtual;

               procedure  preaktivovanie_planov; virtual;

               function   nastavenie_platnosti(zmena: bool): bool; virtual;
               function   zmena_platnosti(z0,z1: Tpoz): bool; virtual;

               procedure  spracovanie_planov; virtual;


             { abstraktne funkcie pre spracovanie
             }
               procedure  uloz    (p: pointer); virtual;
               procedure  posli   (p: pointer; adr: TNETadr; wait: bool); virtual;
               procedure  rozosli (p: pointer; p_add: pbool); virtual;
               procedure  sprava  (p: pointer; typ: TNETtyp; adr: TNETadr); virtual;

               procedure  spracuj (p: pointer); virtual;
               procedure  zobraz  (p: pointer); virtual;
               procedure  plan    (p: pointer); virtual;
               procedure  oprav   (p: pointer; tit: string); virtual;

               procedure  plan_zruseny (p: pointer); virtual;
               function   zrus    (p: pointer; _ask: bool): bool;


             { --------------------------------
               uzivatelske spracovanie planov
               --------------------------------
             }
               function   Inicializacia (nd      : int;      { cislo uzla }
                                         info    : string;   { typ informacie odosielanej na uzol }
                                         filter  : pointer   { @TBfunc_pi - poslat plan na tento smer ? (sektor) }
                                        ): bool;

               procedure  Oprava      (tit: string);
               procedure  Zrusenie    (tit: string);
               procedure  Spracovanie (tit: string;
                                       _data_filter : pointer; _filter : pointer;
                                       _handler_type : TScrollAct_handler_type;
                                       _handler : pointer; _handler_par : pointer;
                                       _print {$IFDEF MATCA}, _send {$ENDIF}: pointer;
                                       _hlpXXX : Pchar
                                      );
               procedure  Vypis (tit: string{; handler : pointer; hlpXXX: pchar}); {$IFNDEF EDD} virtual; {$ENDIF}


               function   nacitanie_zo_vcera(limit_add : real): bool; virtual;
               function   nacitanie_na_zajtra(limit_add : real): bool; virtual;
               procedure  nacitanie_planov(fn,title: string);
               procedure  nacitanie_platnych_planov(title: string); virtual;
               procedure  LoadDB (FN: string; _rozosli,_append: bool; title: string);

             end;


        function  zobrazeny_plan  (p: byte): bool;

        function  nacitaj_plan    (PLAN: PPLAN; p: pointer): bool; far;
        function  preaktivuj_plan (PLAN: PPLAN; p: pointer): bool; far;
