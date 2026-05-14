          {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                      €
           € TFPL4forms           €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }

     type   PFPL_form = ^TFPL_form;
            TFPL_form = object(TFDP_AForm)

             { private }
              btOB    : PButton;          { otocne body       }
              btATS   : PButton;          { trate             }
              btRTE   : PButton;          { standartne trate  }
              {btACT  : PDialogButton;      cinnost nad bodom }

              btSSR   : PDialogButton;

              o_f,
              f_7a,f_7b,f_13a,f_15c: int;

              constructor Init (_title: string; var f : Tcentr;
                                _itemd: PForms; _items: byte; _o_f: byte;

                                _init_form,           { inicializacia dat   }
                                _image_form: pointer; { vykreslenie ciar    }
                                _check_func: pointer; { kontrola regularity }

                                _hlpXXX: Pchar;       { ukazovatel na help  }

                                _adr_var : pointer;   { adresa premennej, kam nacitat data    }
                                _rec     : Pplan_rec;

                                _save_proc,           { ulozenie na disk Tproc_p(p: pointer)  }
                                _send_proc,           { odoslanie planu Tproc_p(p: pointer)   }
                                _add_proc,            { zaradenie planu                       }
                                _disp_proc : pointer;

                                _copy : bool          { vytvorit kopiu formulara ? }
                               );

              procedure   form_init (var x,y: int; dx,dy: int;
                                     _kbHot: char; _cmXXXX: word; _title: string;
                                     _tit : byte;  _inc_dx,_inc_dy: int
                                    ); virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   draw_buttons;  virtual;

              {function    process_formular (p_proc: T_proc_FPL4; var res: string; var ires: int): bool; virtual;}
              function    decode_15 (var res: string; var ires: int): bool; virtual;
            end;



     type   PFPL4form = ^TFPL4form;
            TFPL4form = object(TFPL_form)

              FPLp,FPLn  : DFPL4;
              head       : string[kod_HEAD];

              constructor Init(_head : string; 
                               _itemd: PForms; _items: byte; _o_f: byte;
                               _FPLi : PFPL4;
                               _tit: string; var f : Tcentr;
                               _arch : bool;
                               _copy : bool
                              );
              destructor  Done; virtual;

              procedure   form_init(var x,y: int; dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _tit : byte;  _inc_dx,_inc_dy: int
                                   ); virtual;

              procedure   init_formular_by_stat (_head: string); virtual;
              procedure   init_formular; virtual;
              procedure   init_formular_14 (_14a,_14b,_14c,_14d,_14e : string);
              procedure   init_formular_FPL; virtual;
              procedure   init_formular_RPL; virtual;

              function    read_formular: bool; virtual;
              function    check_formular: bool; virtual;

              function    decode_15 (var res: string; var ires: int): bool; virtual;
            end;
