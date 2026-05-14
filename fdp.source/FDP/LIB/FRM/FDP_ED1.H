          {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                      €
           € TFDP_form            €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }

     type   PFDP_AForm0 = ^TFDP_AForm0;
            TFDP_AForm0 = object(TAForm)

              novy      : bool;

              {get_orig  : PFunc_p;}

              p_is_data,
              p_chg_data : PPLAN_zmeneny;
              data_size : word;
              adr_orig,
              adr_data  : pointer;

              rec       : Pplan_rec;

              is_rqst       : bool;      { spracovava sa ako poziadavka ? }
              p_handle_rqst : pointer;   { ext funckica per spracovanie poziadavky }
              rqst_res      : Trqst;     { vysledok spracovania }

              beeping   : bool;
              PBFunc    : pointer;       { funkcia podmienky ukoncenia pipania }
              beep_par  : pointer;       { parameter funkcie }


              constructor Init(_Owner: PGroup;  var _x,_y, _mode: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _itemd: PForms; _items: byte;
                               _bg,_text, _abg,_atext: byte;

                               _dole: byte;      { kam spinace umiestnit }
                               _tit : byte;              { vypisovat title pre item ked, tak a ako ? }
                               _inc_dx,_inc_dy : int;    { len ak title = 1 (bude sa vypisovat dole) }
                               _init_buttons   : pointer;

                               _dx_h, _dy_h: int;
                               _htext, _hbg: byte;

                               _adr_var  : pointer;
                               _adr_data : pointer;    { data pre kontrolu, ci dany plan este neexistuje }

                               _rec : Pplan_rec;

                               _novy : bool;

                               _data_size : word;
                               _code_key  : PSFunc_p;
                               _read_orig : PIFunc_sp;
                               _is_data,
                               _chg_data : PPLAN_zmeneny;

                               _init_form, _check_func, _done_form: pointer;

                               _image_form: pointer;
                               _handle_event: pointer;

                               _hlpXXX: Pchar;

                               _copy,_clear,_pole_en: bool
                              );

              destructor  Done; virtual;

              procedure   InitApp2; virtual;
              procedure   Idle (var _Event: TEvent); virtual;

              procedure   update_formular; virtual;

              function    plan_uz_bol_podany (data: pointer): bool; virtual;
              function    check_data_not_chg (var _Event: TEvent): bool; virtual;
              function    call_check_func (var _Event: TEvent): bool; virtual;
              function    check_formular: bool; virtual;

              function    _it_i(_ind: int): string;
              procedure   read_pole(ip: int; var it: pchar); virtual;

              procedure   handle_rqst(_rqst_res: Trqst); virtual;
              procedure   HandleEvent(var _Event: TEvent); virtual;

              procedure   spracovany_plan(plan: pointer); virtual;
            end;
