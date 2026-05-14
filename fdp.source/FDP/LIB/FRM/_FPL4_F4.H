          {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                      €
           € TFPL4forms           €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }

     type   PFPL4form = ^TFPL4form;
            TFPL4form = object(T_FPL4_form)

              btRPL4   : PTextIcon;
              pos_RPL4 : int;           { pozicia buttona RPL, da sa premiestnit vo form_init }
              rpl4     : bool;

              btSSR,btSSU : PDialogButton;

              FPLp,
              FPLn  : PFPL4;

              constructor Init(var _x,_y, _mode: int; _tit : string;
                               _itemd  : PForms; _items: byte; _o_f: byte;
                               _FPLi : PFPL4;
                               _src  : fdp_src;
                               _stat : string;
                               _novy : bool
                              );
              destructor  Done; virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;

              procedure   form_init(var x,y: int; dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _tit: byte;  _inc_dx,_inc_dy: int
                                   ); virtual;

              procedure   vlozeny_text(kde: int; s: string); virtual;
              procedure   draw_buttons; virtual;

              procedure   init_formular; virtual;
              procedure   init_formular_by_stat;
              procedure   init_formular_13(_13: string);
              procedure   init_formular_14(_14: string);
              procedure   init_formular_16(_16: string);
              procedure   init_formular_17(_17: pchar);
              procedure   init_formular_by_data;

              {$IFDEF RPL}
               procedure   init_formular_RPL; virtual;
              {$ENDIF}

              function    read_formular: bool; virtual;
              function    check_formular: bool; virtual;

              function    display_decoded_data (var res: string; var ires: int): bool; virtual;
            end;
