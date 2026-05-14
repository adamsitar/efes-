          { --------------------------------------------- }
          { TScrollLst                                    }
          { --------------------------------------------- }
          { zoznam poloziek adresara }

    type  TScrollLst_Init = procedure(p1,p2: pointer; i: int; p3,p4: pointer; b: bool);
          TScrollLst_Sort = procedure(p: pointer; i: int; b: bool);

          PScrollLst = ^TScrollLst;
              TScrollLst = object(TScrollWin)
                RES       : string;
                items     : PPchars;

                constructor Init(_Owner: PGroup;
                                _title: string;
                                x,y, _page : int;
                                _info, _hlpXXX: Pchar;

                                _PATH       : pointer;

                                _get_items  : pointer;    { @TIFunc_p       }
                                _init_items : pointer;    { TScrollLst_Init }
                                _get_item   : pointer;    { @TSfunc         }
                                _sort_item  : pointer;    { @Proc_pib       }
                                _sort_dir   : bool;       { smer triedenia  }

                                var _RES: string;
                                var _POS: int
                                );

                procedure   HandleEvent(var _Event: TEvent); virtual;
                procedure   item_list(i, x,y: int; b: bool); virtual;
              end;
