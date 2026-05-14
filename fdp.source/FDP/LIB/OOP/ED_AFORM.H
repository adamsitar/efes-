          { --------------------------------------------- }
          { TAForm - abstract                             }
          { --------------------------------------------- }
            { pre ukoncenie musi nastavit: SetCommand(_Event,cmCancel) }
     type   TProc_pvE = procedure(P: PObject; var E: TEvent);

     {$IFDEF SERVER}
       const  _dx_AForm: bool = true;
     {$ENDIF}

     type   PAForm = ^TAForm;
            TAForm = object(TBox)

              pole_en  : bool;        { dovolene spracovavat blizke polozky ako stranku }
              pole_cr  : bool;        { enter }
              pole_set : pcharset;    { / }
              Ltitle   : bool;

            { procedury }
              p_init_buttons : pointer; { inicializuje dalsie spinace }
              p_image_form   : pointer; { TProciiii  - vykresli tvar formulara   }

              p_handle_event : pointer; { vonkajsia procedura pre spracovanie prikazov buttonov }

            { butony }
              btList : PbtList;       { ponuka moznych poloziek }
              bt_y, off_x,off_y : int;           { posledny butonik vpravo }

            { farbicky }
              bg,text : byte;

            { parametre pre help }
              l_h        : byte;      { najvacsia dlzka vysvetlivky     }
              dx_h,dy_h  : int;
              htext, hbg : byte;      { atributy aktualnej polozky      }
              nbg        : byte;      { pozadie needitovatelnej polozky }


            { parametre pre riadenie chodu }
              preskoc   : byte;   { = 1 -> prejde z poslednej na prvu polozku a opacne }

              constructor Init(_Owner: PGroup;  var _x,_y, _mode: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _itemd: PForms; _items: byte;
                               _bg,_text, _abg,_atext: byte;

                               _dole: byte;              { kam spinace umiestnit }
                               _tit : byte;              { vypisovat title pre item ked, tak a ako ? }
                               _inc_dx,_inc_dy : int;    { len ak title = 1 (bude sa vypisovat dole) }
                               _init_buttons   : pointer;

                               _dx_h, _dy_h: int;
                               _htext, _hbg: byte;

                               _adr_var: pointer;
                               _init_form, _check_func, _done_form: pointer;

                               _image_form: pointer;
                               _handle_event: pointer;   { @Self,_Event }

                               _copy,_clear,_pole_en : bool;

                               _hlpXXX: Pchar
                              );

              procedure   form_init(var x,y: int; dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _tit : byte;  _inc_dx,_inc_dy: int
                                   ); virtual;

              procedure   init_buttons (x,y: int); virtual;
              procedure   draw_buttons; virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   Draw; virtual;

              {protected}
              procedure   Write; virtual;
              function    WriteItem(_ind: int): int; virtual;
              procedure   UpDateItem(_ind: int; s: string);

              function    is_poley_(prev,nxt: int): bool;
              function    is_poley (prev,nxt: int): bool;
              function    is_polex_(prev,nxt: int): bool;
              function    is_polex (prev,nxt: int): bool;

              procedure   init_pole(ip: int; it: pchar);
              procedure   read_pole(ip: int; var it: pchar); virtual;

              procedure   odsun_text; virtual;
              procedure   vloz_text(s: string); virtual;
              procedure   prisun_text(_ind: int);

              function    AcceptedKey(key: char): bool; virtual;
              procedure   WriteKey(key: char); virtual;

              function    call_check_func(var _Event: TEvent): bool; virtual;

              {protected}
              procedure   Next(di: integer);  virtual;
              procedure   MoveRight(di: int); virtual;
              procedure   MoveLeft(di: int);  virtual;

              procedure   item_clicked(var _Event: TEvent); virtual;


              function    Ask(_pos: int; _title: string; _mess: string): TAnswer;
            end;
