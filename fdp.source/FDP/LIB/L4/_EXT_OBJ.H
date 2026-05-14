    type   PO_EXT = ^O_EXT;
           O_EXT  = object(O_EXT_ibuff)

             src_type : fdp_src;
             dst_set  : set_fdp_src;
             is_4444  : bool;

             NODE_THIS       : string;       { pseudomeno uzla, napr "MI" }
             NODE_REMOTE     : string;       { pseudomeno uzla, napr "PR" }


             CISLO_SPRAVY    : word;
             CISLO_SPRAVYcfg : string[12];
             CISLO_SPRAVY24h : bool;
             EXT_HEADER_ADR  : bool;


            { buffery
            }
             pbuff_size    : word;
             pbuff         : PDynamic2;      { buffer paketov ocakavajucich spracovanie }

             {$IFDEF SYNCHRONIZE_EXT}
              is_ireg      : bool;
              ireg_size    : word;
              ireg         : PDynamic2;      { pre evidenciu poslednych prijatych sprav }
             {$ENDIF}


            { prijem/odoslanie
            }
             Ts_,Tr_       : real;           { Posledne casy odoslania/prijmu    }
             TsTimeOut     : real;           { Heartbeaty sa vysielaju po...     }
             TrTimeOut     : real;           { Po vyprsani casu sa odpoji...     }

             isTrTimeOut   : bool;           { pomocna premmenna }

             HeartBeat     : string;

             p_master_line : pbool;


            { spracovanie spravy
            }
             p_heads_EXT   : Pheads_ICAO;
             heads_EXT     : word;

             is_ERR        : bool;
             is_ERS        : bool;

             {cis_ALR      : long;
             cis_ERR       : long;
             cis_ERS       : long;}


            { nastavenie sposobu prace
            }
             archive_all_en    : bool;         { nahravanie vsetkych prijatych paketov }
             process_all_adr   : bool;         { spracovanie - // -  prijatych adries  }
             process_all_msg   : bool;         { spracovanie - // -  prijatych sprav   }
             process_err_en    : bool;         { programatorske povolenie spracovania chyb v danom objekte }
             write_in_nl_en    : bool;         { sprava sa na obrazovku vypisuje po riadkoch }
             uncomplete_pkt_en : bool;


            { archivacne premenne
            }
             p_scroll_data : PPOScrollStream;

             p_wr,                           { ukazovatele na logicke premenne }
             p_arch,                         { pre vypis, archivaciu prijatych }
             p_utc,                          { a udaj o case spracovania       }
             p_nl          : pointer;

             cl_s,cl_r     : byte;           { farba odosielanych a prijatych dat }


            { archivacia
            }
             pathSTREAM,                     { cesta ku archivacnemu suboru    }
             pathERR       : string[80];     {       ku chybovemu suboru       }
             fn_ext        : string[3];
             ArchDays      : word;


            { potvrdzovanie
            }
             p_heads_LAM          : Pheads_ICAO;
             heads_LAM            : word;
             LAM_pred_spracovanim : bool;
             LAM_TimeOut          : real;
             EXTack               : POEXTack;


            { synchronizacia
            }
             spr_send_ext,
             spr_new,spr_prd,spr_ed,spr_del,
             spr_err,spr_err_ed,spr_err_del,
             spr_items_del,spr_item_del : TNETtyp;

             sync_info : pchar;
             coor_info : pchar;


            { pomocne a vypoctovie premennie
            }
             {pkt_cis       : int;             citac odoslanych dat mod 1000   }
             {en_start_of_data : bool;         povolenie nastavit
                                             }
            { IFDEF DEBUG}
              testing_fn        : string;
              testing_txt_file  : bool;
              testing_one_msg   : bool;
              test_last_pos     : long;
            { ENDIF}


            { editor sprav
            }
             ed_riadkov,ed_znakov, ed_velkost_strany: int;


            { parametre spracovania
            }
             okamzite_spracovanie : bool;
             send_VFR_FPL  : bool;           { posielaju sa VFR plany ku XXX ?   }
             FL_from_alt   : word;           { od tejto hodnory sa vyska pre XXX
                                               koduje vo feetoch
                                             }

             public

             constructor  Init(_Owner   : PObject;
                               _p_power : pbool;
                               _cfg_FN  : string;

                              { nastavenia : potvrdenia, linka
                              }
                               _lam: int; _async : bool;

                              { spracovavany paket
                              }
                               _ipkt_size,_ibuff_size: word; _is_ibuff0: bool;
                               _pbuff_size: word;

                              { synchronizacia/zalohovanie
                              }
                               _spr_send_ext,
                               _spr_new,_spr_prd,_spr_ed,_spr_del,
                               _spr_err,_spr_err_ed,_spr_err_del,
                               _spr_items_del,_spr_item_del : TNETtyp;
                               _sync_info,_coor_info : pchar;

                              { spracovane spravy
                              }
                               _p_heads_EXT : Pheads_ICAO; _heads_EXT : word;
                               _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

                              { archivacne premenne
                              }
                               _p_wr, _p_arch, _p_utc{, _p_nl} : pointer;
                               _cl_s, _cl_r : byte;
                               _pathSTREAM,_pathERR, _ext : string
                              );

             destructor   Done; virtual;


           { inicializacne funkcie
           }
             function     read_cfg(_cfg_FN: string): bool; virtual;

             procedure    initialize_NODES; virtual;
             procedure    initialize_STATUS(_draw: bool); virtual;
             procedure    initialize_ERR(_draw: bool);


           { predefinovanie TObject-u
           }
             function     streamFN: string; virtual;


           { תתתתתתתתתתתתתתתתתתתתתתת }
           { hlavna slucka           }
           { תתתתתתתתתתתתתתתתתתתתתתת }

             procedure    HandleEvent (var _Event: TEvent); virtual;

             procedure    check0; virtual;
             procedure    check;  virtual;

             function     manage_connection: bool; virtual;
             function     manage_archiv: bool; virtual;
             function     manage_alert: bool;  virtual;
             function     manage_error: bool;  virtual;


           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
           { prijem a spracovanie EXTERNA LINKA  }
           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }

             function     is_master_line: bool; virtual;
             function     is_distribute_pkt: bool; virtual;
             function     is_receive_pkt: bool; virtual;


             function     is_pkt_for_node (from: string; data: pchars; size: word): bool; virtual;
             function     is_system_pkt   (data: pchars; size: word; res: string): bool; virtual;

             public
             function     get_pkt_size (pkt: pointer): word; virtual;
             function     get_pkt_data (pkt: pointer): pointer; virtual;
             function     get_pkt_comprimed_size (pkt: pointer): word; virtual;

             function     read_inp_buff: bool; virtual;
             function     ibuff_read: bool;
             function     check_pkt_frame(data: pchars; size: word; var res: string): bool; virtual;
             function     receive_pkt (src: TPKT_SRC; from: string;
                                       data: pchars; size: word;
                                       var res: string;
                                       distribute: bool
                                      ): bool; virtual;

             procedure    ibuff_flush;
             function     pbuff_read: bool;

             function     process_pkt (src: TPKT_SRC;
                                       data: pchars; size: word;
                                       var header: string;
                                       var res: string;
                                       res_send: bool
                                      ): bool; virtual;

             function     process_data(src: TPKT_SRC;
                                       data: pchars; size: word;
                                       var header: string;
                                       var resh,resd: string
                                      ): bool; virtual;


             function     _scroller_enabled: bool;

             procedure    _archive_pkt (data: pchars; size: word; prompt, message: string; is___: bool);
                                       {$IFDEF DEBUG} virtual; {$ENDIF}
             procedure    _writeln_pkt (data: pchars; size: word; prompt, message: string; cl: byte; is___: bool);
                                       {$IFDEF DEBUG} virtual; {$ENDIF}
             procedure    writeln_pkt  (data: pchars; size: word; prompt, message: string; cl: byte; is___,is_nl: bool);
                                       {$IFDEF DEBUG} virtual; {$ENDIF}
             procedure    print_pkt    (data: pchars; size: word; title: string); virtual;

             function     _read_txt_file (fn: string; is_msg: bool; var ms: string; var mp: pchar): bool;
             function     _save_txt_file (fn: string; ms: string; data: pchars; size: long; prepis: bool): bool;



           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
           { synchronizacia a spracovanie NET    }
           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }

             procedure    _delete_pkt_in_buff (data: pchars; size: word; key: string);
             procedure    delete_pkt (data: pchars; size: word; tit,fn: string; spr: TNETtyp; from: TNETadr;
                                      distribute,code_data: bool
                                     );

            {$IFDEF SYNCHRONIZE_EXT}

             procedure    distribute_pkt  (data: pchars; size: word; tit,fn: string;
                                           typ: TNETtyp; from: TNETadr;
                                           code_data: bool
                                          );

             procedure    error_pkt       (data: pchars; size: word; tit,fn: string; edit: bool);

             procedure    update_pkt      (data: pchars; size: word; tit,fn: string; spr: TNETtyp; from: TNETadr
                                          );



             function     decode_NETpkt           (var pkt: TNETpkt): bool; virtual;

             procedure    decode_pkt_spr_send_ext (var pkt: TNETpkt);

             procedure    decode_pkt_spr_new      (var pkt: TNETpkt);
             procedure    decode_pkt_spr_prd      (var pkt: TNETpkt);

             procedure    decode_pkt_spr_del      (var pkt: TNETpkt);

             procedure    process_pkt_spr_ed      (var data: TSYNC_EXTpkt); virtual;
             procedure    decode_pkt_spr_ed       (var pkt: TNETpkt);

             procedure    decode_pkt_spr_err      (var pkt: TNETpkt);

             procedure    decode_pkt_spr_items_del(var pkt: TNETpkt); virtual;
             function     node_initialize_files   (nd: int): bool; virtual;

           {$ENDIF}



           { תתתתתתתתתתתתתתתתתתתתתתת }
           { dekodovanie dat         }
           { תתתתתתתתתתתתתתתתתתתתתתת }

             function     decode_pkt   (data: pchars; size: word;
                                        var res: string
                                       ): bool; virtual;


             function     decode_frame (data: pchars; size: word;
                                        var zac,kon: word;
                                        var res: string
                                       ): bool; virtual;


             function     decode_HeartBeat (data: pchars; size: word): bool; virtual;


             function     _code_header   (head,adr,ods,cislo: string;
                                          header_data: string;
                                          data: pchars;
                                          var header: string
                                         ): string; virtual;

             function     _decode_header (header: string;
                                          var head,adr,ods,cislo: string;
                                          var header_data: string;
                                          res: pstring
                                         ): bool; virtual;


             function     decode_header (data: pchars; size: word;
                                         zac,kon: word;
                                         var header: string;
                                         var res: string;
                                         decode: bool
                                        ): bool; virtual;


             function     decode_head  (header: string;
                                        var head: string;
                                        var res: string
                                       ): bool; virtual;


             function     enabled_head (src: TPKT_SRC;
                                        data: pchars; size: word;
                                        head: string;
                                        var res: string
                                       ): bool;  virtual;


             function     decode_adr   (header: string;
                                        var res: string
                                       ): bool;  virtual;


             function     decode_data  (data: pchars; size: word;
                                        header: string;
                                        var head: string;
                                        var res: string
                                       ): bool; virtual;


             function     _decode_LAM  (data: pchars; size: word;
                                        var header: string;
                                        var lam,ods,key: string;
                                        var typ: TNETtyp;
                                        var res: string
                                       ): bool; virtual;

             function     decode_LAM   (data: pchars; size: word;
                                        var header: string;
                                        var res: string
                                       ): bool;


             function     _icao_head_type (head: string; var res: string): int;


           { תתתתתתתתתתתתתתתתתתתתתתת }
           { vysielanie a potvrdenie }
           { תתתתתתתתתתתתתתתתתתתתתתת }

             function     _send_pkt    (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
             function     _send_npkt   (typ: byte; adr: string; data: pchars; size: word): bool;
             function     send_pkt     (typ: byte; adr: string; data: pchars; size: word): bool; virtual;

             procedure    _send_data   (typh: byte;
                                        adr,header: string;
                                        data: pchars; size: word;
                                        key: string; typd: TNETtyp
                                       );
             procedure    send_data    (adr : string;
                                        head,cislo,header_data : string;
                                        data: pchars; size: word;
                                        key: string; typ: TNETtyp
                                       ); virtual;

             function     _LAM_data    (header: string): string; virtual;
             function     _is_to_LAM   (data: pchars; size: word; header: string): bool; virtual;
             procedure    send_LAM     (data: pchars; size: word; header: string); virtual;
             procedure    LAM_received_pkt (data: pchars; size: word); virtual;


             function     timeout_uzla  (adr: string): real; virtual;
             procedure    ocakavany_LAM (header,adr,key: string; typ: TNETtyp); {$IFDEF DEBUG} virtual; {$ENDIF}
             procedure    prijaty_LAM   (id,adr: string; var key: string; var typ: TNETtyp);
             procedure    neprijaty_LAM (id,adr,head,key: string; var res: string); virtual;
             procedure    manage_LAM;


           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }  { implementacie nasledujucuch  }
           { identifikacia, chyby, vystraha            }  { dvoch metod su byt aplikacne }
           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }  { zavisle                      }

             function     _key_data   (data: pchars; size: word): string; virtual;

             function     _fn_data    (data: pchars; size: word): string; virtual;
             function     _path_data  (data: pchars; size: word): string; virtual;

             function     _fn_ERR     (data: pchars; size: word; ext: string): string; virtual;
             function     _fn_ERRmask (ext: string): string; virtual;

             procedure    _save_ERR   (data: pchars; size: word; msg: string;
                                       _fn_ext: string; var is_pkt: bool;
                                       delete,distribute : bool
                                      );

             procedure    process_ERR_HEAD (src: TPKT_SRC;
                                            data: pchars; size: word;
                                            res: string
                                           ); virtual;

             procedure    process_ERR_DATA (src: TPKT_SRC;
                                            data: pchars; size: word; res: string;
                                            err_save,err_show,distribute: bool
                                           );  virtual;

             function     read_ALR : bool;
             function     _read_ERR   (_ext : string;
                                       _init_buttons,_handle_buttons : pointer;
                                       _hlpXXX : pchar;
                                       var is_pkt : bool
                                      ): bool;
             {procedure    process_ALR (data: pchars; size: word; head: string); virtual;}


           { תתתתתתתתתתתתתתתתתתתתתתת }
           { spravy                  }
           { תתתתתתתתתתתתתתתתתתתתתתת }


           { תתתתתתתתתתתתתתתתתתתתתתת
              kontrola, testovanie
             תתתתתתתתתתתתתתתתתתתתתתת
           }
             procedure _send_test (head,fn: string);

             procedure _process_char (soc: char); virtual;
             procedure _process_data (data: pchars; size: word); virtual;
             function  _process_file (src: TPKT_SRC; var fn: string; demo : bool;
                                      soc: char; off: int; one_msg: bool;
                                      var last_pos: long
                                     ): bool;

             procedure _process_test (data: pbytes; dlz: int); virtual;

             procedure test_file (fn: string; soc: char; off: int); virtual;
             procedure demo_file (soc: char; off: int);


           { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              koordinacia medzi roznymi systemami FDP
             תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
           }
             procedure  _send_co_ordinate_message(src: fdp_src; dst: set_fdp_src;
                                                  typ: TNETtyp; head: Thead_ICAO;
                                                  zmeneny: bool;
                                                  var plan
                                                 ); virtual;

             procedure  send_co_ordinate_message (src: fdp_src; dst: set_fdp_src;
                                                  typ: TNETtyp; head: Thead_ICAO;
                                                  zmeneny: bool;
                                                  var plan
                                                 ); virtual;
           end;
