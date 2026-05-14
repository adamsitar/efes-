          { --------------------------------------------- }
          { TScroller                                     }
          { --------------------------------------------- }
    type    Tproc_i3b   = procedure(i, x,y: int; b: bool);
            TProc_pi2b  = procedure(p: pointer; x,y: int; b: bool);
            TProc_pi3b  = procedure(p: pointer; i, x,y: int; b: bool);
            Tproc_p2i2b = procedure(p1,p2: pointer; x,y: int; b: bool);


    type  { Typ Vypis poloziek       }
            p_PScroller = ^PScroller;
            PScroller   = ^TScroller;
            TScroller   = object(TGroup)

              sb  : PScrollBar;        { scroll bar                     }

              p_item_list : pointer;   { procedura pre vypis polozky    }

              arr_adr     : Pptrs;     { adresa pola pointerov          }
              is_ptr_arr  : bool;
              adr_arr_adr : pointer;   { ak sa pri zmene alokuje nove pole   }

              p_top_adr   : pointer;        { adresa int top v poli items         }
              p_top_chg   : pointer;        { ukazovatel na bool premennu o zmene }
              p_arr_chg   : p_tick_counter; { ukazovatel na premennu o zmene dat <>0 or <>last_tick_counter }
              arr_chg     : tick_counter;

              p_arr_init  : pbool;     { nastaveny semafor -> inicializuje sa pole, nezobrazuje sa kazda zmena }
              p_arr_check : pbool;     { nastaveny semafor -> prepocitava sa pole, nezobrazuje sa kazda zmena  }

              lo,                      { index prvej a poslednej polozky v okne }
              hi,                      { podla ich indexov v originalnom poli   }
              top,                     { pocet poloziek                         }
              pos         : int;       { pozicia vo vypise v <0,top>            }

              smer        : bool;      { smer vypisu: true = zhora dole         }

              za_posl_en  : bool;      { vypis moze byt i za poslednou polozkou }
              pos_en      : bool;      { povoleny vyber polozky ?          }
              stranka_en  : bool;      { rolovanie vypisu len po strankach }
              prepis_en   : bool;      { povolenie kontroly na prepis ineho objektu }
              sort_en     : bool;      { povolene triedenie poloziek       }
              item_en     : bool;      { povoleny vypis polozky            }

              top_prev    : int;       { predchadzajuci ...                }
              pos_prev    : int;       { predchadzajuca ...                }
              lo_prev     : int;
              hi_prev     : int;

              item_dx     : int;
              item_dy     : int;       { vyska polozky pre vypis           }
              bg          : byte;      { pozadie vypisu                    }

              sam         : bool;      { kreslit sb oddelene ?             }
              vpravo      : bool;      { sb vpravo                         }
              on          : TbtStat;   { ako nakreslit ?                   }

              dxi,dyi       : int;     { posun item oproti hrane           }
              dxioff,dyioff : byte;    { -//- , napravenie chyby pri vypise textu }
              medzera       : int;

              maska_is_clicked : byte;
              click_and_handle : bool; { pri jednom kliknuti pos a handle }
              pos_chg_and_list : bool; { pri zmene pos prepise zoznam     }

              finded_and_processed_data : bool; { ak scroller neotvori okno,
                                                  pretoze podla vstupneho filtra
                                                  boli nacitane jedinecne data
                                                 }


              public { predefinovane }
              constructor Init(_Owner: PGroup; _page: int;
                               x,y, _item_dx,_item_dy: int;
                               _dxi,_dyi, _medzera: int; _bg: byte;
                               _pos_en, _sam : bool;
                               _p_item_list : pointer;

                               _arr_adr   : pointer;
                               _top_adr   : pointer;
                               _top_chg   : pointer;
                               _p_arr_chg : p_tick_counter  { ukazovatel na premennu o zmene dat <>0 or <>last_tick_counter }
                              );

              procedure   Draw; virtual;
              procedure   Idle(var _Event: TEvent); virtual;  { dotatocna kontrola pre GetEvent }
              procedure   Prekreslenie; virtual;

              procedure   handle_scroller (var _Event: TEvent); virtual;
              procedure   HandleEvent (var _Event: TEvent); virtual;

            { Funkcia pre vypis poloziek tymto objektom a inym objektom. }
              procedure   mark_pos;
              procedure   List;  virtual;
              procedure   Scroll;  virtual;

              procedure   draw_inside; virtual;
            { Funkcie pre vypis poloziek inym objektom, nie tymto ! }
              procedure   redraw(ind: int); {virtual;}
              procedure   erase (ind: int); {virtual;}

              procedure   redraw_p  (p: pointer); {virtual;}
              procedure   erase_p   (p: pointer); {virtual;}

              function    get_pos_xy(_pos: int; var x,y: int): bool;

            { protected } { moze predefinat odvodena trieda                                }
              function    get_scroller_size  (_item_dx: int; var _dxi: int): word; virtual;
              function    get_scroller_height(_page: int; _item_dy: int; var _dyi: int; _medzera: int): word; virtual;
              procedure   reinit_(x,y, _page: int);
              procedure   sb_left;

              procedure   item_list_proc (i, x,y: int; b: bool); virtual;
              procedure   item_list      (i, x,y: int; b: bool); virtual;
              procedure   item_list_pos  (posi: int);
              procedure   item_erase (i: int); virtual;

              function    get_x: int; virtual; { vratia poziciu pre vypis item }
              function    get_yi(i: int): int; virtual;

              function    is_initialized: bool; virtual;
              function    is_checked: bool; virtual;
              function    _is_changed: bool; virtual;    { kontroluje, ci sa zmenil top }
              function    is_changed: bool; virtual;     { kontroluje, ci sa zmenil top }
              function    get_top   : int;  virtual;     { kontroluje ako sa zmenil top }

              procedure   new_data; virtual;         { alokovanie novych dat      }
              procedure   disp_data; virtual;        { odalokovanie dat           }

              procedure   renew;
              function    is_to_renew(ind: int): bool; virtual;

              function    get_p_ind(p: pointer): int; virtual;
              function    get_ind(i: int): int; virtual;
              function    get_ind_in_list(i: int): int; virtual;
            end;
