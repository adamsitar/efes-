          {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                      €
           € TmFPLform            €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }
     type   PmFPLform = ^TmFPLform;
            TmFPLform = object(TFDP_AForm)
              kresli: pointer;

              private
              btOB  : PDialogButton;    { voj otocne body   }
              btNDB : PDialogButton;    { civ otocne body   }
              btABC : PDialogButton;    { otocne body       }
              btACT : PDialogButton;    { cinnost nad bodom }
              btRTE : PDialogButton;    { standartne trate  }

              public

              constructor Init(var _x,_y,  _mode: int;
                               _title: string;

                               _init_form  : pointer; { inicializacia dat   }
                               _check_func : pointer; { kontrola regularity }
                               _pos        : byte;

                               _adr_var,              { adresa premennej, kam nacitat data    }
                               _adr_data   : pointer; { data pre kontrolu, ci dany plan este neexistuje }

                               _rec        : pointer;
                               _src        : fdp_src;

                               _stat       : string;
                               _novy       : bool;

                               _date_proc,           { zadanie datumu TBFunc_p3(p,c,d: pointer) }
                               _save_rpl_proc,       { ulozenie rpl Tproc_p(p: pointer)         }
                               _zarad_proc : pointer;

                               _hlpXXX: Pchar        { ukazovatel na help  }

                               {$IFDEF ODOSLI_ULOZ}; _uloz: bool {$ENDIF}
                              );

              procedure   HandleEvent(var _Event: TEvent); virtual;

              function    is_upcas(_ind: int): bool; virtual;

              procedure   init_buttons_trat (x,y: int);
              procedure   init_buttons (x,y: int); virtual;
              procedure   draw_buttons;  virtual;

              function    plan_uz_bol_podany (data: pointer): bool; virtual;
            end;


     procedure mFPL_image  (x0,y0,x1,y1: int); far;
     procedure mFPL_init   (form: PmFPLform; FPL: PDmFPL); far;
     function  mFPL_check  (form: PmFPLform; FPL: PDmFPL): bool; far;
     function  _mFPL_check (form: PmFPLform; FPL: PDmFPL; syntax,vlastne,prepocet: bool): bool; far;

     {$IFDEF MAPY}
        procedure mFPL_kresli(form: PmFPLform); far;
     {$ENDIF}
