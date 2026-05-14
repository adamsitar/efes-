
    type   PO_CAMUS = ^O_CAMUS;
           O_CAMUS = object({$IFDEF CAMUS_OLDI} O_OLDI
                            {$ELSE}             O_L4_FDP
                            {$ENDIF}
                           )


             {$IFNDEF CAMUS_OLDI}
              CAMUSpkt : PCAMUSpkt;
             {$ENDIF}

              EXC_NDB : PPchars;
              poc_EXC_NDB : int;


              constructor  Init;
              destructor   Done; virtual;

              function     read_cfg (_cfg_FN: string): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               hlavna slucka
               תתתתתתתתתתתתתתתתתתתתתתת
             }
               procedure    HandleEvent (var _Event: TEvent); virtual;


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              prijem a spracovanie EXTERNA LINKA
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
             {$IFNDEF CAMUS_OLDI}
              function     get_pkt_size (pkt: pointer): word; virtual;
              function     get_pkt_data (pkt: pointer): pointer; virtual;
             {$ENDIF}

              function     check_pkt_frame (data: pchars; size: word; var res: string): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               dekodovanie dat
               תתתתתתתתתתתתתתתתתתתתתתת
             }
               function     decode_data  (data: pchars; size: word;
                                          header: string;
                                          var head: string;
                                          var res: string
                                         ): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               vysielanie a potvrdenie
               תתתתתתתתתתתתתתתתתתתתתתת
             }
             {$IFNDEF CAMUS_OLDI}
               function     _send_pkt    (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
               procedure    send_data    (adr: string; head,cislo,header_data: string;
                                          data: pchars; size: word;
                                          key: string; typ: TNETtyp
                                         ); virtual;
             {$ENDIF}

              function     _lam_data     (header: string): string; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               (de)kodovanie sprav ATC
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             }

             { AMA
             }
             {$IFDEF FPL4} {$IFDEF FPL0}
                procedure    _decode_CPL   (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
                function     _code_CPL     (var FPL: DFPL4): pchar; virtual;

                procedure    _decode_EST   (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
                  function   _include_ESTc_bod(kod: string): bool; virtual;
                  function   _decode_ESTc  (var FPL: DFPL4; var FPLc: DcFPL; var res: string): bool; virtual;
                function     _code_EST     (var FPL: DFPL4): pchar; virtual;
             {$ENDIF} {$ENDIF}


             { ASM
             }
              {$IFDEF PRS}
                function  _is_to_send_message_PRS (zmeneny: bool; PRS: TPRS): bool; virtual;
                function  _code_PRS  (PRS: TPRS): pchar; virtual;
              {$ENDIF}


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                funkcie implementujuce spracovanie sprav
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             }
              function   _code_bod_trate   (kod: string;
                                            x,y: real;       { ak su to ZemSur }
                                            fn: string       { subor a tolerancia }
                                           ): string; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               (de)kodovanie sprav ASM
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             }


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                koordinacia medzi roznymi systemami FDP
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             }
             {$IFDEF MATCA} {$IFDEF FPL0}
              procedure  _send_message_FPLM(head: Thead_ICAO; zmeneny: bool; var FPLm: DmFPL); virtual;
             {$ENDIF} {$ENDIF}


             {IFDEF DD_EXE
              procedure  _process_test (data: pbytes; dlz: int); virtual;
              procedure  test_file (fn: string; soc: char; off: int); virtual;
             ENDIF}
           end;


    {$I _CA_functions.h}

    const  DEV_CAMUS: PO_CAMUS = nil;

