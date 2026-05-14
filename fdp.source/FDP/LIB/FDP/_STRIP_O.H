         { ------------------- }
         { TSTRIP              }
         { ------------------- }
    type    PSTRIP  = ^O_STRIP;
            O_STRIP = object(TPLAN)

               {$IFDEF EDD}
                skupina  : string[KOD_OB+1];
                adrBOARD : PPObject;
                cmADD, cmCHG, cmDEL, cmCLR : word;

                p_strip_draw    : pointer;  { procedura pre vykreslenie stripu }
                p_strip_handler : pointer;
                p_PRN2          : pbool;
               {$ENDIF}

                constructor Init(_items,_data_size : word;

                                 _new_item,
                                 _format_item,
                                 _disp_item : pointer;

                                 _eq,
                                 _id,
                                 _chg,
                                 _poz,
                                 _est : pointer;

                                 _distribute : pointer;  { TNET_distribute_rdp_pkt  }
                                 _send       : pointer;  { TNET_send_pkt }
                                 _en_net     : bool;

                                 _item_list  : pointer;
                                 _item_dx,_item_dy : int;
                                 _get_item_dx,_get_item_dy : pointer;

                                 _p_viewer : PScrollInd;
                                 {$IFDEF MAPY}
                                  _p_kresli : pointer;
                                 {$ENDIF}

                                 {$IFDEF EDD}
                                   _adrBOARD : PPObject;
                                   _cmADD,_cmCHG,_cmDEL,_cmCLR: word;

                                   _skupina         : string;
                                   _p_strip_draw    : pointer;
                                   _p_strip_handler : pointer;
                                 {$ENDIF}

                                 var _p_PRN  : bool;
                                 _p_print    : pointer;

                                 _save       : pointer;
                                 _zobraz     : pointer;
                                 _formular   : pointer;
                                 _p_comp     : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
                                 _p_handler  : pointer;

                                 {_fn_ext : string;}
                                 _p_nameDB, _p_decodeDB : pointer;
                                 _riadkovDB : byte;
                                 _p_codekey : pointer;

                                 _limit_add, _limit_cnl, _limit_del : pint;
                                 _nacitanie : bool;

                                 _hlpXXX    : Pchar
                                );

              {$IFDEF EDD}
                {$IFDEF PRN}
                 procedure set_printed (p: pointer; was: bool); virtual;
                {$ENDIF}

                function  vypis_plan(ind: int; _sort,_novy: bool): bool; virtual;
                procedure zmaz_plan (ind: int; _zrus: bool); virtual;

                public
                procedure zarad_strip(ind: int; cmXXX: word);

                procedure strip (ind, x,y: int; b: bool); { virtual; }
                function  zarad (ind: int; is: TSpecGroups): string; virtual;
                function  zarad_inde (ind: int; is: TSpecGroups; res: string): string; virtual;
                function  smer  (ind: int): Ts_dir; virtual;

                function  NDB   (ind: int): string; virtual;
                function  ETO   (ind: int): real;   virtual;
                function  ETD   (ind: int): real;   virtual;
                function  ETA   (ind: int): real;   virtual;
                function  FL    (ind: int): real;   virtual;

                procedure LAM   (p: pointer); virtual;
              {$ENDIF}
            end;
