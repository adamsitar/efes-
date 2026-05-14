    const {$IFDEF DEBUG} max_PRS = 100;
          {$ELSE}        max_PRS = 500;
          {$ENDIF}


    type   POPRS = ^TOPRS;
           TOPRS = object(O_STRIP)

             constructor Init({$IFDEF EDD} {$IFDEF TABLET_PRS}
                               _adrBOARD : PPObject; _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
                              {$ENDIF} {$ENDIF}
                              nic: pointer
                             );

             function   get_flag (p: pointer; group: byte): byte; virtual;
             procedure  set_flag (p: pointer; group,flag: byte); virtual;

             function   get_poz (p: pointer): Tpoz; virtual;
             {$IFDEF NET}
              function  get_rec (p: pointer): Pplan_rec; virtual;
             {$ENDIF}

             {$IFDEF MAPY}
              function  get_id_map(p: pointer; count: int; var naz: string): bool; virtual;
              procedure _zobraz_plan_na_mape(p: pointer; PIS: bool); virtual;
             {$ENDIF}

             {$IFDEF TABLET_PRS}
              function  ETO(ind: int): real; virtual;
              function  ETD(ind: int): real; virtual;
              function  ETA(ind: int): real; virtual;
              function  FL (ind: int): real; virtual;
             {$ENDIF}


             { --------------------
                spracovanie planov
               --------------------
             }
             function  nacitanie_zo_vcera(limit_add : real): bool; virtual;
           end;


    const  PRSs : POPRS = nil;
