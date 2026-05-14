          { --------------------------------------------- }
          { TEditor                                       }
          { --------------------------------------------- }
     type   PEditor = ^TEditor;
            TEditor = object(TAForm)
              znakov, stlpec, riadok : byte;
              alloc : bool;

              constructor Init(_Owner: PGroup;  var _x,_y, _mode: int; _cmXXXX: word;
                               _title: string;
                               _itemd: PForms;
                               _items,_znakov: byte;
                               _bg,_text, _abg,_atext: byte;

                               _inc_dx,_inc_dy : int;
                               _init_buttons,
                               _adr_var,
                               _disp_proc,
                               _init_form,
                               _check_func,
                               _done_form,
                               _handle_event : pointer;

                               _copy,_clear, _pole_en : bool;

                               _hlpXXX: Pchar
                              );

              destructor  Done; virtual;

              procedure   form_init(var x,y: int; dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _tit : byte;  _inc_dx,_inc_dy: int
                                   ); virtual;

              function    AcceptedKey(key: char): bool; virtual;
              procedure   WriteKey(key: char);          virtual;

              procedure   Next(di: integer);  virtual;
              procedure   FindRightText;
              procedure   FindLeftText;
            end;
