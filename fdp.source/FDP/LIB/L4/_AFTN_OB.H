    type   P_AFTN = ^O_AFTN;
           O_AFTN  = object(O_L4_FDP)

              ADR_I  : string[_MTK_ADR_hi];
              ADR_O  : string[_MTK_ADR_hi];

              CHNL_I : string[_MTK_CHNL];
              CHNL_O : string[_MTK_CHNL];


              ALIAS_NODE : TNETadr;


              HeartBeat_ID       : string;
              HeartBeat_PERIODE  : byte;
              HeartBeat_MIN      : byte;
              last_HeartBeat     : byte;


             { vypoctovie premennie
             }
              AFTNpkt     : PAFTNpkt;
              p_aftnEOT   : pchar;          { transformovany koniec paketu }
              kod_aftnEOT : byte;

              pathTLG     : string;         { cesta ku prijatym telegram   }
              spr_tlg     : TNETtyp;

              {sended_data : string;          prasarna }


              constructor  Init (_cfg_OB : string;
                                 { synchronizacia/zalohovanie
                                 }
                                  _sync_info,_coor_info : pchar;
                                 { spracovanie spravy
                                 }
                                  _p_heads_ICAO: Pheads_ICAO; _heads_ICAO: word
                                );
              destructor   Done; virtual;


             { inicializacne funkcie
             }
              function     read_cfg (_cfg_FN: string): bool; virtual;

              procedure    initialize_STATUS (_draw: bool); virtual;
              procedure    initialize_TLG    (_draw: bool);


             { תתתתתתתתתתתתתתתתתתתתתתת }
             {  hlavna slucka          }
             { תתתתתתתתתתתתתתתתתתתתתתת }

              procedure    HandleEvent (var _Event: TEvent); virtual;

              procedure    check; virtual;

              function     manage_connection: bool; virtual;
              function     manage_archiv: bool; virtual;
              procedure    manage_tlg; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
             { prijem a spracovanie EXTERNA LINKA  }
             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }

              function     is_pkt_for_node (from: string; data: pchars; size: word): bool; virtual;
              function     is_system_pkt   (data: pchars; size: word; res: string): bool; virtual;

              function     get_pkt_size (pkt: pointer): word; virtual;
              function     get_pkt_data (pkt: pointer): pointer; virtual;
              function     get_pkt_comprimed_size (pkt: pointer): word; virtual;


              function     process_data (src: TPKT_SRC;
                                         data: pchars; size: word;
                                         var header: string;
                                         var resh,resd: string
                                        ): bool; virtual;

              function     process_data_FPL  (src: TPKT_SRC;
                                              data: pchars; size: word;
                                              var header: string;
                                              var resh,resd: string
                                             ): bool; virtual;

              function     process_data_TLG  (src: TPKT_SRC;
                                              data: pchars; size: word;
                                              var res: string
                                             ): bool; virtual;

              function     _process_TLG (data: pchars; size: word; prty: string; distribute: bool): bool; virtual;
              function     _process_HeartBeat (data: pchars; size: word; prty: string): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
             { synchronizacia a spracovanie NET    }
             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }

             {$IFDEF SYNCHRONIZE_EXT}
              function     decode_NETpkt       (var pkt: TNETpkt): bool; virtual;
              procedure    decode_pkt_spr_tlg  (var pkt: TNETpkt);
              procedure    process_pkt_spr_ed  (var data: TSYNC_EXTpkt); virtual;
             {$ENDIF}


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
             { identifikacia, chyby, vystraha            }
             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }

              function     _key_data   (data: pchars; size: word): string; virtual;

              function     _fn_data    (data: pchars; size: word): string; virtual;
              function     _path_data  (data: pchars; size: word): string; virtual;

              function     _fn_ERR     (data: pchars; size: word; ext: string): string; virtual;
              function     _fn_ERRmask (ext: string): string; virtual;

              function     _fn_TLG     (data: pchars; size: word; prty: string): string; virtual;
              function     _fn_TLGmask (prty: string): string; virtual;

             procedure     process_ERR_HEAD (src: TPKT_SRC;
                                             data: pchars; size: word;
                                             res: string
                                            ); virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת }
             { dekodovanie dat         }
             { תתתתתתתתתתתתתתתתתתתתתתת }

              function     decode_pkt  (data: pchars; size: word;
                                        var res: string
                                       ): bool; virtual;

              function     decode_data (data: pchars; size: word;
                                        header: string;
                                        var head: string;
                                        var res: string
                                       ): bool; virtual;


              function     _prty_  (prty: string; var is_tlg_prty,is_tlg_en,is_tlg_prn : pbool): prtyTLG;
              function     is_prty (data: pchars; size: word; var res: string): string;

              function     is_pkt_to_ext_line: bool; virtual;
              procedure    _send_HeartBeat; {virtual;}


            { תתתתתתתתתתתתתתתתתתתתתתת }
            { vysielanie a potvrdenie }
            { תתתתתתתתתתתתתתתתתתתתתתת }

              function     _send_pkt    (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
              function     send_pkt     (typ: byte; adr: string; data: pchars; size: word): bool; virtual;

              procedure    send_data    (adr: string; head,cislo,header_data: string;
                                         data: pchars; size: word;
                                         key: string; typ: TNETtyp
                                        ); virtual;

              procedure    save_TLG (data: pchars; size: word; title, prty : string);

              function     _read_TLG(_ext: string; _check_func, _init_buttons,_handle_buttons : pointer; _page: int): bool;
              function     read_TLG (prty: string): bool;

              function     send_TLG (prty,adr,head: string; data: pchars; size: word): string;
              procedure    send_LAM (data: pchars; size: word; head: string); virtual;

              function     _is_to_LAM   (data: pchars; size: word; header: string): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת }
             { testovanie              }
             { תתתתתתתתתתתתתתתתתתתתתתת }

               procedure  _process_test (data: pbytes; dlz: int); virtual;

              {$IFDEF DEBUG}
               (*procedure  _archive_pkt (data: pchars; size: word; prompt, message: string; is___: bool);
                                         {$IFDEF DEBUG} virtual; {$ENDIF}
               procedure    _writeln_pkt (data: pchars; size: word; prompt, message: string; cl: byte; is___: bool);
                                         {$IFDEF DEBUG} virtual; {$ENDIF}
               procedure    writeln_pkt  (data: pchars; size: word; prompt, message: string; cl: byte; is___,is_nl: bool);
                                         {$IFDEF DEBUG} virtual; {$ENDIF}
               *)
               procedure  _test_bin_file(fn: string; skp: int);
               procedure  _test_txt_file(fn: string; ends: string; skip: byte);
              {$ENDIF}
           end;
