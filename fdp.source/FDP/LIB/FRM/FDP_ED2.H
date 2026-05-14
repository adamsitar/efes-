          {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                      €
           € TFDP_form            €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }

     const  max_form_rpls = 500;
            xp_btRPL = 1;

     type   PFDP_AForm = ^TFDP_AForm;
            TFDP_AForm = object(TFDP_AForm0)

              src        : fdp_src;
              stat       : string;

              ins_date   : bool;       { ma sa zadavat explicitne datum ?     }
              is_date    : bool;       { bol zadany datum vo formulati, takze netreba otvatat okno pre jeho vstup }
              p_is_date  : pointer;    { adresa na funkciu vracajucu, ci sa ma zadat datum }
              date_proc  : pointer;    { kontrola datumu planu TBfunc_p3, ci dany plan este neexistuje }

              save_rpl_proc : pointer; { ulozenie rpl Tproc_p(p: pointer)     }
              {$IFDEF STATISTIKA_OPL}
               statistika_proc : pointer;
              {$ENDIF}

              zarad_proc : pointer;    { zaradenie planu                      }

              rpl,                     { objavi sa ponuka rpl pre nacitanie ? }
              arch,                    { nacitavany z archivu ? }
              posli   : bool;

              btRPL   : PTextIcon;
              pos_RPL : int;           { pozicia buttona RPL, da sa premiestnit vo form_init }

              {$IFDEF ODOSLI_ULOZ}
               uloz   : bool;
               btUloz : PTextIcon;
              {$ENDIF}

              {$IFDEF SKRY_OKNA}
               skry   : bool;          { skry formular pri ukonceni editacie }
              {$ENDIF}

              command : word;
              res_ev  : TEvent;


            { parametre nacitanie/ulozenie z/do RPL
            }                          { polozky pre scroll_DB }
              tit_RPL    : string;     { hlavicka v ponuke }
              p_fn_RPL   : pointer;    { funkcia, ktora vrati nazov rpl-subora }

              item_size  : word;
              new_item   : pointer;
              format_item: pointer;
              {disp_item : uz je }

              db_riadkov : byte;
              decode_db  : pointer;

              dx_item,dy_item : int;
              draw_item  : pointer;


              {public}

              constructor Init(var _x,_y,  _mode: int;
                               _title : string;
                               _itemd : PForms; _items : byte;

                               _dole : byte;          { kam spinace umiestnit }
                               _tit  : byte;          { vypisovat title pre item ked, tak a ako ? }
                               _inc_dx,_inc_dy,       { len ak title = 1 (bude sa vypisovat dole) }
                               _dx_h, _dy_h: int;

                               _init_form,            { inicializacia dat   }
                               _image_form : pointer; { vykreslenie ciar    }
                               _check_func : pointer; { kontrola regularity }

                               _hlpXXX: Pchar;       { ukazovatel na help  }

                               _adr_var   : pointer;
                               _adr_data  : pointer; { adresa premennej s povodnymi datami }

                               _rec       : Pplan_rec;
                               _src       : fdp_src;
                               _stat      : string;

                               _novy      : bool;
                               _data_size : word;
                               _code_key  : PSFunc_p;
                               _read_orig : PIFunc_sp;
                               _is_data,
                               _chg_data  : PPLAN_zmeneny;

                               _date_proc,           { zadanie datumu TBFunc_p3(p,c,d: pointer) }
                               _save_rpl_proc,       { ulozenie rpl Tproc_p(p: pointer)      }
                               _zarad_proc,
                               _disp_proc : pointer;

                               _copy,_clear ,_pole_en : bool
                               {$IFDEF ODOSLI_ULOZ};
                                _uloz : bool         { ma sa zobrazit btUloz ? }
                               {$ENDIF}
                               {$IFDEF SKRY_OKNA};
                               _skry : bool          { skry formular pri ukonceni editacie }
                               {$ENDIF}

                               { specializovane fcie
                               }
                               {$IFDEF STATISTIKA_OPL};
                                 _statistika_proc : pointer
                               {$ENDIF}
                              );


              procedure   RPL_scroll_init
                              (_tit_RPL    : string;     { hlavicka v ponuke }
                               _p_fn_RPL   : pointer;    { funkcia, ktora vrati nazov rpl-subora }

                               _item_size  : word;
                               _new_item,
                               _format_item : pointer;

                               _db_riadkov : byte;
                               _decode_db  : pointer;

                               _dx_item,_dy_item : int;
                               _draw_item  : pointer
                              );

              procedure   init_buttons(x,y: int); virtual;
              procedure   draw_buttons; virtual;

              procedure   init_formular; virtual;
              procedure   init_formular_RPL; virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;

              procedure   DoneApp; virtual;
              function    EndState (var _Event: TEvent): bool; virtual;
              procedure   RunLocalFunc (var _Event: TEvent; Info: PChar); virtual;

              procedure   get_stat (var _stat: string; var _command: word);
              procedure   set_stat (_stat: string);

              function    check_date (var _Event: TEvent): bool; virtual;
              function    call_check_func (var _Event: TEvent): bool; virtual;

              function    decode_DATE  (it18: int; var date: TDate;  var res: string; var ires: int): bool;
              function    decode_DATUM (it18: int; var datum: Tdatum; var res: string; var ires: int): bool;
              function    assign_DATE  (var rok: word; var mes,den: byte; h,m,s: byte): bool;
            end;
