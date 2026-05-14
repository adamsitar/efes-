          { --------------------------------------------- }
          { TBox - prototyp editora                       }
          { --------------------------------------------- }
     type   PBox = ^TBox;
            TBox = object(TGroup)

              viewer  : bool;

            { zabezpecenie vlastnosti okna }
              Win    : PWindow;
              btOK   : PButton;
              btCa   : PButton;
              {$IFDEF A36YKA}
               btA36 : PDialogButton;
              {$ENDIF}

            { parametre }
              itemd  : PForms;
              itemv  : PFPars;
              items  : byte;

              {arch        : bool;}
              copy_of_form : bool;       { vytvara sa kopia formulara ? }
              copy_back    : bool;       { kopiruje sa spat do originalu  ? }
              itemd_adr    : PForms;     { adresa originalu }

            { nastavenia }
              pswrd  : bool;
              upcas  : bool;
              alone  : bool;

            { procedury }
              adr_var    : pointer;  { smernik na spracovavanu premmenu }
              disp_proc  : pointer;
              adr_par    : pointer;  { odkaz na parametre pri spracovani }

              init_form  : pointer;  { inicializacia formulara proc_p2 alebo proc }
              check_func : pointer;  { kontrolna funkcia proc_p2 alebo proc }
              done_form  : pointer;  { akcia po spravnom zadani }

              init_list  : pointer;  { inicializacia zoznamu }
              clear_list : bool;     { vymazanie poloziek formulara pri inicializacii, implicitne false }
              sort_list  : bool;     { triedit ?             }
              done_list  : pointer;  { zrusenie zoznamu      }

            { premenne }
              last_kbhit : real;

              is_update  : bool;     { opatovne nacitat data obnovene externym zdrojom ? }
              is_cancel  : bool;     { vznikli dovody na zrusenie editacie ? }


              kbHot      : char;     { potvrdzovacia klavesa }

              ins        : bool;     { je/nie ins               }
              ind        : int;      { index editovanej polozky }
              prev_ind   : int;      { index predtym editovanej polozky }
              first_pos  : int;

              xp,yp      : pointer;

              clear          : bool;
              corr_res       : bool; { pom. premenna pre check_func }
              item_in_button : bool;


            { farbicky }
              abg,atext{,form}: byte;

            { umiestnenie dalsej informacie }
              dole: byte;
              tit : byte;   { 0 -> nic, 1 -> zvlastne miesto pre title, 2 -> title pred polozkou }

              public
              constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                               _kbHot: char; _cmXXXX: word;
                               _itemd: PForms; _items: byte;
                               _abg,_atext{,_form}: byte;
                               _adr_var: pointer;
                               _init_form, _check_func, _done_form: pointer;
                               _ins,_alone, _copy,_clear: bool
                              );

              procedure   form_copy; virtual;
              destructor  Done; virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   Draw; virtual;
              procedure   ReDraw;
              procedure   Centre; virtual;

              procedure   RunList(_lst: PListDesc; _pos: int; _add: bool;
                                  _filter: PBFunc_s;
                                  _gets: PSFunc_s; _getpis: PSFunc_pis
                                 );
              procedure   vlozeny_text(kde: int; s: string); virtual;


              procedure   Run(var _Event: TEvent); virtual;
              function    EndState(var _Event: TEvent): bool; virtual;

              procedure   proc__Self_adr_var(p: pointer);

              function    init_local_var: bool;
              procedure   init_formular; virtual;     { inicializacia formulara  }
              procedure   write_in_formular; virtual; { zapis don s jeho pomocou }

              function    check_formular: bool; virtual; { kontrolna funkcia }
              procedure   done_formular; virtual; { akcia po spravnom zadani }

              procedure   Write; virtual;
              function    WriteItem(_ind: int): int;    virtual;

              procedure   odsun_text;                   virtual;
              procedure   vloz_text(s: string);         virtual;

              function    EditingKey(key: char):  bool; virtual;
              function    AcceptedKey(key: char): bool; virtual;
              procedure   WriteKey(key: char);          virtual;

              {protected}
              procedure   clear_item_i(i: int);
              procedure   clear_item;
              procedure   clear_items;

              procedure   set_location(var _x,_y, _mode: int);
              procedure   item_clicked(var _Event: TEvent); virtual;

              procedure   MoveRight (di: int); virtual;
              procedure   MoveLeft  (di: int); virtual;

              procedure   GoToPos (_pos: byte); virtual;
              procedure   SetPos;

              function    is_upcas (_ind: int): bool; virtual;

              function    first_char_i(_ind: int): int;
              function    last_char_i (_ind: int): int;
              procedure   last_char;

              function    _it_(_ind: int): string;
              function    _it(_ind: int): string;
              procedure   _in(_ind: int; s: string);

              procedure   IndXY  (var _pos: int; var x,y: int; _mess: string);
              procedure   Error  (_pos: int; _mess: PChar); virtual;
              procedure   ErrorS (_pos: int; _mess: string);
            end;


          { --------------------------------------------- }
          { TSingleForm - jednoduchy editor               }
          { --------------------------------------------- }
     type   PSingleForm = ^TSingleForm;
            TSingleForm = object(TBox)
              btList : PbtList;
              r      : Tregion;

              constructor Init(_Owner: PGroup;
                               var _x,_y, _mode: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _itemd: PForm;
                               _abg,_atext: byte;
                               _dole : byte;

                               _adr_var: pointer;
                               _init_form, _check_func, _done_form: pointer;
                               _hlpXXX : Pchar;
                               _ins: bool
                               );
              procedure   Draw; virtual;

              procedure   Error (_pos: int; _mess: PChar); virtual;
            end;
