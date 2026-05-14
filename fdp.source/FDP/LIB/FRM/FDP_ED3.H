          {
            ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
            €                      €
            € TREQ                 €
            €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
           }
     type   PFDP_REQ = ^TFDP_REQ ;
            TFDP_REQ = object(TFDP_AForm0)

              rqst_res    : Trqst;
              handle_rqst : pointer; { Tproc_pr }

              constructor Init(var _x,_y, _mode: int;
                               _title: string;
                               _itemd: PForms; _items: byte;

                               _tit : byte;            { vypisovat title pre item ked, tak a ako ? }
                               _inc_dx,_inc_dy,        { len ak title = 1 (bude sa vypisovat dole) }
                               _dx_h,_dy_h : int;

                               _adr_var     : pointer; { adresa premennej, kam nacitat data }
                               _adr_data    : pointer;

                               _rec         : Pplan_rec;
                               _chg_data    : PPLAN_zmeneny;

                               _init_form   : pointer; { inicializacia dat   }
                               _image_form  : pointer; { vykreslenie ciar    }
                               _check_func  : pointer; { kontrola regularity }

                               _handle_rqst : pointer; { obsluha vysledku    }
                               _disp_proc   : pointer;
                               _beep        : bool;

                               _hlpXXX      : Pchar;   { ukazovatel na help  }

                               _copy,_clear,_pole_en : bool     { vytvorit kopiu formulara ? }
                              );

              procedure   HandleEvent(var _Event: TEvent); virtual;
            end;
