    type   PO_OPL = ^O_OPL;
           O_OPL = object(O_L4_FDP) { Mohol by byt objekt O_L4_FDP -> O_COM -> ... }

            { Prenosovych parametrov "O_COM"
              a buffer
            }
              OPLpkt    : POPLpkt;
             {$IFDEF OPL_EXT_UDP}
              UDPpkt    : POPLpkt;
             {$ENDIF}

            { Pomocne parametre pre dokumentovanie
              byte-to-byte
            }
              {save_stream : bool;}
              {$IFDEF OPL__SAVE_STREAM}
               stream_file : file of char;
               stream_fn   : string;
               stream_open : bool;
              {$ENDIF}
              test_int    : bool;


            { Kontrolavane hodnoty
            }
              smphr_AUP : bool;
              {$IFDEF REQUEST_AUP}
               Ts_REQUEST_AUP : TsREQ;
              {$ELSE}
               Ts_REQUEST_AUP : real;
              {$ENDIF}

              Ts_REQUEST_RTZ : real;


            { Predefinovanie objekty
            }
              constructor  Init;
              destructor   Done; virtual;

              function     read_cfg(_cfg_FN: string): bool; virtual;


            { תתתתתתתתתתתתתתתתתתתתתתת
              hlavna slucka
              תתתתתתתתתתתתתתתתתתתתתתת
            }
              procedure    HandleEvent (var _Event: TEvent); virtual;
              procedure    check; virtual;


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              prijem a spracovanie EXTERNA LINKA
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
              function     is_master_line: bool; virtual;

              function     read_inp_buff: bool; virtual;

              function     get_pkt_size (pkt: pointer): word; virtual;
              function     get_pkt_data (pkt: pointer): pointer; virtual;

              function     check_pkt_frame (data: pchars; size: word; var res: string): bool; virtual;

              {function     process_data (src: TPKT_SRC;
                                         data: pchars; size: word;
                                         var head: string;
                                         var resh,resd: string
                                        ): bool; virtual;}


            { תתתתתתתתתתתתתתתתתתתתתתת
              dekodovanie dat
              תתתתתתתתתתתתתתתתתתתתתתת
            }
              function     decode_header(data: pchars; size: word;
                                         zac,kon: word;
                                         var header: string;
                                         var res: string;
                                         decode: bool
                                        ): bool; virtual;

              function     decode_head  (header: string;
                                         var head: string;
                                         var res: string
                                        ): bool; virtual;

              function     decode_data  (data: pchars; size: word;
                                         header: string;
                                         var head: string;
                                         var res: string
                                        ): bool; virtual;

            {$IFDEF FPL0} {$IFDEF FPL4}

             { ICAO
             }
                function     _process_FPL (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
                  function   _decode_FPLc (var FPL: DFPL4; var FPLc: DcFPL; var res: string): bool; virtual;
                  function   _decode_FPLm (var FPL: DFPL4; var FPLm: DmFPL; var res: string): bool; virtual;

                function     _process_CHG (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

                function     _process_CNL (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

                function     _process_DLA (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;


             { OLDI
             }
              function       decode_CLR    (data: pchars; size: word; var FPL: DFPL4; var res: string): bool;
                function     _process_CLR  (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
                procedure    _decode_CLR   (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;

                function     _process_ABI (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;


             { AMA
             }
                procedure    _decode_CPL  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;

                procedure    _decode_EST   (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
                  function   _decode_ESTc  (var FPL: DFPL4; var FPLc: DcFPL; var res: string): bool; virtual;
                  function   _process_ESTc (var FPL: DFPL4; var res: string): bool; virtual;

            {$ENDIF} {$ENDIF}


            {$IFDEF PRS}
              function   _decode_AUPi  (data: pchars; size: word; var PRS: TPRS; var res: string): bool; virtual;
              function   decode_AUP   (data: pchars; size: word; header,head: string; var res: string): bool;

              function   _decode_ASM  (data: string; var PRS: TPRS; var res: string): bool;
              function   decode_ASM   (data: pchars; size: word; var res: string): bool;
            {$ENDIF}

            {$IFDEF RTZ}
              function   decode_RTZ  (data: pchars; size: word; var res: string): bool;
            {$ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              kodovanie sprav a odoslanie
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }

            {$IFDEF FPL0} {$IFDEF FPL4}

             { AMA
             }
                function     _code_EST     (var FPL: DFPL4): pchar; virtual;
                  function   _code_ESTc    (var FPLc: DcFPL; var FPL: DFPL4): bool; virtual;

            {$ENDIF} {$ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתת
              vysielanie a potvrdenie
              תתתתתתתתתתתתתתתתתתתתתתת
            }
              function     _send_pkt    (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
              procedure    send_data    (adr: string; head,cislo,header_data: string;
                                         data: pchars; size: word;
                                         key: string; typ: TNETtyp
                                        ); virtual;

              {function     _lam_data    (header: string): string; virtual;}
              procedure    send_LAM (data: pchars; size: word; header: string); virtual;


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               funkcie implementujuce spracovanie sprav
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
              {function   _code_bod_trate   (kod: string; x,y: real): string; virtual;}
              function     _decode_bod_trate (kod: string; fn: string): string; virtual;


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               koordinacia medzi roznymi systemami FDP
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
              {$IFDEF FPL0}
                procedure  _send_message_FPLC (head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL); virtual;
              {$ENDIF}

              {$IFDEF PRS}
               function  _is_process_PRS (PRSp,PRS: PPRS): bool; virtual;
               procedure send_request_AUP(d: PDate);
              {$ENDIF}

              {$IFDEF RTZ}
               procedure send_request_RTZ;
              {$ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתת
               kontrola, testovanie
              תתתתתתתתתתתתתתתתתתתתתתת
            }
              procedure    _process_char (soc: char); virtual;
              procedure    _process_data (data: pchars; size: word); virtual;

              procedure    check_stream_file;
              procedure    save_stream_char (soc: char);
            end;


     function code_vysOPL(vys: string): string;
