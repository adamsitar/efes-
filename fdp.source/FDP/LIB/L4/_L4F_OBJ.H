    type   PO_L4_FDP = ^O_L4_FDP;
           O_L4_FDP   = object(O_L4444)

             cfg_OB  : string[12];
             {dr_OB  : real;}

             { vypoctove premenne
             }
              spracovanie_fpl4 : bool;

              _mil_sys     : bool;   { vojensky system }

              est_alt_     : char;   { typ udaja s letovou vyskou v poli 15 EST }
              _l4444m      : bool;   { je povolena rozsirena abeceda pola 8b }
              _dct_points  : bool;   { vkladat DCT medzi body trate do CPL }
              _oat_exclude : bool;

              _exclude_uknown_points : bool;

              _error_fda   : bool;
              _nolam_fda   : bool;


             { dekodovanie sprav
             }
              poloziek_ESTc_bodov: int; { implicitne sa ocakava a kontroluje len bod v poli trate }


             constructor Init(_Owner : PObject;
                              _p_power : pbool;
                              _cfg_FN, _cfg_OB : string;

                              { nastavenia : potvrdenia, linka
                              }
                                _lam: int; _async: bool;

                              { spracovavany paket
                              }
                               _ipkt_size, _ibuff_size: word; _is_ibuff0: bool;
                               _pbuff_size: word;

                              { synchronizacia/zalohovanie
                              }
                               _spr_send_ext,
                               _spr_new,_spr_prd,_spr_ed,_spr_del,
                               _spr_err,_spr_err_ed,_spr_err_del,
                               _spr_items_del,_spr_item_del : TNETtyp;
                               _sync_info,_coor_info : pchar;

                              { spracovanie spravy
                              }
                               _p_heads_ICAO: Pheads_ICAO; _heads_ICAO: word;
                               _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

                              { archivacne premenne
                              }
                               _p_wr, _p_arch, _p_utc : pointer;
                               _cl_s, _cl_r : byte;
                               _pathSTREAM,_pathERR, _ext : string
                             );

             function   read_cfg(_cfg_FN: string): bool; virtual;


            {$IFDEF FPL4} {$IFDEF FPL0}

            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              dekodovanie sprav
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
            { ICAO
            }
               function   is_FPL4MIL (FPL: DFPL4): bool;

               function   _process_FPL  (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
                 function _decode_FPLc  (var FPL: DFPL4; var FPLc: DcFPL; var res: string): bool; virtual;
                 function _process_FPLc (var FPL: DFPL4; var res: string): bool; virtual;
                {$IFNDEF FPLM_DISABLED}
                 function _decode_FPLm  (var FPL: DFPL4; var FPLm: DmFPL; var res: string): bool; virtual;
                 function _process_FPLm (var FPL: DFPL4; var res: string): bool; virtual;
                {$ENDIF}

            { AMA
            }
               function   _process_CPL  (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

               function   _process_EST  (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
                 function _include_ESTc_bod(kod: string): bool; virtual;
                 function _decode_ESTc_bod(s: string; vys: word; vys_: char; var bod: TOBxy;
                                           poloziek: int; var res: string
                                          ): bool;
                 function _insert_FPLC_route (var _OBs: TOBxys; var _bodov: int; var FPLc: DcFPL): bool;
                 function _decode_ESTc  (var FPL: DFPL4; var FPLc: DcFPL; var res: string): bool; virtual;
                 function _process_ESTc (var FPL: DFPL4; var res: string): bool; virtual;
                {$IFNDEF FPLM_DISABLED}
                 function _decode_ESTm  (var FPL: DFPL4; var FPLm: DmFPL; var res: string): bool; virtual;
                 function _process_ESTm (var FPL: DFPL4; var res: string): bool; virtual;
                {$ENDIF}

            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              kodovanie sprav a odoslanie
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }

            { ICAO
            }
            {$IFNDEF FPLM_DISABLED}
             function   send_FPLm     (var FPLm: DmFPL): bool;
               function _code_FPLm    (var FPLm: DmFPL; var FPL: DFPL4): bool; virtual;

             function   send_CHGm     (var FPLm: DmFPL{; const FPLp: DmFPL}): bool;
               function _code_CHGm    (var FPLm: DmFPL; var FPL: DFPL4): bool; virtual;

             function   send_DLAm     (var FPLm: DmFPL): bool;
             function   send_CNLm     (var FPLm: DmFPL): bool;


            { OLDI
            }
             function   send_ACTm     (var FPLm: DmFPL): bool;
            {$ENDIF}


            { AMA
            }
             function   send_CPLc     (var FPLc: DcFPL): bool;
               function _code_CPLc    (var FPLc: DcFPL; var FPL: DFPL4): bool; virtual;
              {function  _code_CPL    (var FPL: DFPL4): pchar; virtual;}

             function   send_ESTc     (var FPLc: DcFPL): bool;
               function _code_ESTc    (var FPLc: DcFPL; var FPL: DFPL4): bool; virtual;

            {$IFNDEF FPLM_DISABLED}
             function   send_ARRm     (var FPLm: DmFPL): bool;
             function   send_ESTm     (var FPLm: DmFPL): bool;
               function  _code_ESTm   (var FPLm: DmFPL; var FPL: DFPL4): bool; virtual;
            {$ENDIF}

           {$ENDIF} {$ENDIF}

           { ASM
           }
           {$IFDEF PRS}
             function   send_PRS  (var PRS: TPRS): bool;
              function _code_PRS  (PRS: TPRS): pchar; virtual;
           {$ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               funkcie implementujuce spracovanie sprav
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
             function   _decode_bod_trate (kod: string;
                                           fn: string
                                          ): string; virtual;

             function   _code_bod_trate   (kod: string;
                                           x,y: real;       { ak su to ZemSur }
                                           fn: string       { subor a tolerancia }
                                          ): string; virtual;

            {$IFDEF FPL0}
             {$IFNDEF FPLM_DISABLED}
              procedure _process_message_FPLM (dst: set_fdp_src; head: Thead_ICAO; stat: string; FPLp,FPL: PDmFPL);
             {$ENDIF}
             procedure _process_message_FPLC (dst: set_fdp_src; head: Thead_ICAO; stat: string; FPLp,FPL: PDcFPL);
            {$ENDIF}

            {$IFDEF PRS}
             function  _is_process_PRS (PRSp,PRS: PPRS): bool; virtual;
             procedure _process_message_PRS (dst: set_fdp_src; head: Thead_ICAO; stat: string; hladany: bool; p,PRS: PPRS);
            {$ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               koordinacia medzi roznymi systemami FDP
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
             procedure _send_co_ordinate_message(src: fdp_src; dst: set_fdp_src;
                                                 typ: TNETtyp; head: Thead_ICAO;
                                                 zmeneny: bool;
                                                 var plan
                                                ); virtual;

            { Funkcii rozhodujuce o odoslani koordinacnych sprav [ku odvodenym naslednikom tohto obsego objektu]
            }
             {$IFDEF FPL0}
              {$IFNDEF FPLM_DISABLED}
               procedure  _send_message_FPLM (head: Thead_ICAO; zmeneny: bool; var FPL: DmFPL); virtual;
              {$ENDIF}
              procedure  _send_message_FPLC (head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL); virtual;
             {$ENDIF}


             {$IFDEF PRS}
              function   _is_to_send_message_PRS(zmeneny: bool; PRS: TPRS): bool; virtual;
              procedure  _send_message_PRS(head: Thead_ICAO; zmeneny: bool; var PRS: TPRS); virtual;

              {$IFDEF FUA_DATA}
               procedure  _send_message__UP(head: Thead_ICAO; zmeneny: bool; var FN: string); virtual;
               procedure  _send_message_AUP(head: Thead_ICAO; zmeneny: bool; var FN: string); virtual;
               procedure  _send_message_UUP(head: Thead_ICAO; zmeneny: bool; var FN: string); virtual;
              {$ENDIF}
             {$ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתת
               kontrola, testovanie
              תתתתתתתתתתתתתתתתתתתתתתת
            }
              function     _decode_LAM  (data: pchars; size: word;
                                         var header: string;
                                         var lam,ods,key: string;
                                         var typ: TNETtyp;
                                         var res: string
                                        ): bool; virtual;

              procedure    neprijaty_LAM (id,adr,head,key: string; var res: string); virtual;

              procedure    process_ERR_DATA (src: TPKT_SRC;
                                             data: pchars; size: word; res: string;
                                             err_save,err_show,distribute: bool
                                            ); virtual;

           end;

