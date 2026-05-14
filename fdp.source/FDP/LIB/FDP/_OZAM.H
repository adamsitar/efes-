    type   POZAM = ^TOZAM;
           TOZAM = object(O_STRIP)

             constructor Init({$IFDEF EDD} {$IFDEF TABLET_ZAM}
                               _adrBOARD : PPObject; _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
                              {$ENDIF} {$ENDIF}
                              nic: pointer
                             );

             function  get_poz(p: pointer): Tpoz; virtual;
             {$IFDEF NET}
              function get_rec(p: pointer): Pplan_rec; virtual;
             {$ENDIF}

            {$IFDEF PROCESS_ZAM}
             procedure Spracovanie_(tit: string; _data_filter: string;
                                    _handler_type: TScrollAct_handler_type; _handler: pointer; _handler_par : pointer;
                                    _hlpXXX: Pchar
                                   );
            {$ENDIF}

            {$IFDEF MAPY} {$IFNDEF MAPY_1.0}
              function  get_id_map(p: pointer; count: int; var naz: string): bool; virtual;
            {$ENDIF} {$ENDIF}

            {$IFDEF TABLET_ZAM}
             function  ETO (ind: int): real; virtual;
             function  ETD (ind: int): real; virtual;
             function  ETA (ind: int): real; virtual;
             function  FL  (ind: int): real; virtual;
            {$ENDIF}
           end;

    const  ZAMs : POZAM = nil;
