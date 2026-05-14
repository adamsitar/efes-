{$IFDEF MACC}
   type   P_StrRLP_REQ_FPL = ^T_StrRLP_REQ_FPL ;
          T_StrRLP_REQ_FPL = object(TREQ_FPL)
            FPLi: PDmFPL;

            procedure   form_init(var x,y: int; dx,dy: int;
                                  _kbHot: char; _cmXXXX: word; _title: string;
                                  _tit  : byte; _inc_dx,_inc_dy: int
                                 ); virtual;

            constructor Init(_FPLi: PDmFPL;      { pripomienka pre FPLi }
                             var _x,_y, _mode: int;
                             _title: string;
                             _itemd: PForms; _items: byte;

                             _tit : byte;        { vypisovat title pre item ked, tak a ako ? }
                             _inc_dx,_inc_dy,    { len ak title = 1 (bude sa vypisovat dole) }
                             _dx_h, _dy_h: int;

                             _adr_var   : pointer; { adresa premennej, kam nacitat data }

                             _init_form,           { inicializacia dat   }
                             _image_form: pointer; { vykreslenie ciar    }
                             _check_func: pointer; { kontrola regularity }
                             _handle_req: pointer; { obsluha vysledku    }
                             _kresli    : pointer;

                             _hlpXXX : Pchar       { ukazovatel na help  }
                            );

            procedure   LocalMain(var _Event: TEvent); virtual;
          end;
{$ENDIF}

