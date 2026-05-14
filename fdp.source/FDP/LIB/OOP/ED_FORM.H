          { --------------------------------------------- }
          { TFormular - pouzitelny                        }
          { --------------------------------------------- }
     type   PFormular = ^TFormular;
            TFormular = object(TAForm)
              procedure   form_init(var x,y: int; dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _tit : byte;  _inc_dx,_inc_dy: int
                                   ); virtual;

              constructor Init(_Owner: PGroup;  var _x,_y, _mode: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _itemd: PForms; _items: byte;
                               _bg,_text,{_form,}_abg,_atext: byte;

                               _dole: byte;      { kam spinace umiestnit }
                               _tit : byte;      { vypisovat title pre item ked, tak a ako ? }
                               _inc_dx,_inc_dy: int;  { len ak title = 1 (bude sa vypisovat dole) }
                               _init_buttons : pointer;
                               _dx_h, _dy_h: int;
                               _htext, _hbg: byte;

                               _adr_var: pointer;
                               _init_form, _check_func, _done_form: pointer;

                               _image_form: pointer;
                               _copy,_clear, _pole_en : bool;
                               _hlpXXX: Pchar
                               );
            end;
