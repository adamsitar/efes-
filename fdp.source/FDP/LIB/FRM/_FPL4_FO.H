     type   P_FPL4_form = ^T_FPL4_form;
            T_FPL4_form = object(TFDP_AForm)

             { private
             }
              bt_pos  : int;

              btOB    : PButton;          { otocne body       }
              btATS   : PButton;          { trate             }
              btRTE   : PButton;          { standartne trate  }

              o_f, f_7a,f_7b,f_13a,f_15c: int;

              constructor Init (var _x,_y, _mode: int; _tit : string;
                                _itemd: PForms; _items: byte; _o_f: byte;            { offset }

                                _init_form,            { inicializacia dat   }
                                _image_form : pointer; { vykreslenie ciar    }
                                _check_func : pointer; { kontrola regularity }

                                _adr_var    : pointer; { adresa premennej, kam nacitat data    }
                                _adr_data   : pointer; { adresa premennej s povodnymi datami }

                                _rec  : Pplan_rec;
                                _src  : fdp_src;
                                _stat : string;

                                _novy      : bool;
                                _data_size : word;
                                _code_key  : PSFunc_p;
                                _read_orig : PIFunc_sp;
                                _is_data,
                                _chg_data  : PPLAN_zmeneny;

                                _date_proc,           { zadanie datumu TBFunc_p3(p,c,d: pointer) }
                                _save_rpl_proc,       { ulozenie rpl Tproc_p(p: pointer)    }
                                _zarad_proc,
                                _disp_proc: pointer;

                                _hlpXXX: Pchar         { ukazovatel na help  }
                               );

              procedure   form_init(var x,y: int; dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _tit : byte;  _inc_dx,_inc_dy: int
                                   ); virtual;
              procedure   draw_buttons;  virtual;

              procedure   HandleEvent (var _Event: TEvent); virtual;

              function    display_decoded_data (var res: string; var ires: int): bool; virtual;
            end;

