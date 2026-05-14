     const  max_znakov_e  = 80;
            max_riadkov_e = 65;


     function   size_strany_editora(riadkov,znakov: word): word;
     procedure  zmaz_stranu_editora (strana: pointer; znakov: int; r,od: int);
     function   alloc_stranu_editora(riadkov,znakov: int): pointer;
     procedure  dealloc_stranu_editora(var strana: pointer; riadkov,znakov: int);


          { --------------------------------------------- }
          { TEditor                                       }
          { --------------------------------------------- }
     type   PEditors = ^TEditors;
            TEditors = object(TScrollWin)

              win_en          : bool;  { dovolene samostatne okno ? }

              viewer          : bool;
              upcas           : bool;
              title           : pchar;

            { editovana strana }
              strana          : pointer;
              riadkov, znakov : int;
              stl,rdk         : int;    { 0 znamena predchazajucu polohu   }
              ins             : bool;   { je/nie ins                       }

              alloc           : bool;
              corr_res        : bool;

              bga,cla,
              bge,cle,                  { pre odpamateanie farebneho odlisenia }
              bgv,clv         : byte;   { pri editovani/prehliadani, ak bgw<>clw }

            { procedury - popis pri implementacii modulu }
              write_txt  : pointer;     { TSFunc_pis - funkcia, ktora zapise i-ty riadok }
              read_txt   : pointer;     { TSFunc_pis - funkcia, ktora vrati i-ty riadok  }

              text_adr   : pointer;     { spracovavana premenna              }
              p_text_adr : pointer;     { adresa -  -//- : odvodi sa         }
              text_len,                 { dlzka vstupnych dat                }
              p_text_len,
              text_size  : word;        { velkost buffera vstupnych dat      }

              is_pchar   : bool;        { text_adr^ je pchar, volanim read_from_editor }
              disp_pchar : bool;        { sa odalokuje, ak je text_disp odalokuje sa na konci }

              odd_rdk,                  { oddelovac riadkov pri nacitani do editora  }
              odd_slv    : TCharSet;    { oddelovac slov                             }
              odd_rdkr   : string[2];   {                                 z editora  }

              check_func : pointer;     { TBFunc_p3(@Self,handler_owner,text_adr) - kontrolna funkcia proc }

              is_chg     : bool;        { zmeneny obsah ? }
              tmp        : string;      { docasny subor   }

              handler_end_state : pointer; { TBFunc_p3 - ukonci potvrdenie editaciu ? }

             {$IFDEF A36YKA}
              btA36 : PDialogButton;
             {$ENDIF}


              constructor Init(_Owner : PGroup;
                               var _x,_y, _mode: int; _cmXXXX: word;
                               _title  : string;

                               _win_en : bool;           { dovolene samostatne okno ? }
                               _viewer : bool;

                               _strana : pointer; _riadkov,_znakov, _velkost_strany: int;
                               _tmp    : string;

                               _write_txt    : pointer;  { fcia pre zapis do riadkov          }
                               _read_txt     : pointer;  { fcia pre citanie/zapis do riadkov  }
                               var _text_adr : pointer;  { smernik na spracovavanu premennu   }
                               _text_len,                { dlzka vstupnych dat                }
                               _text_size  : word;       { velkost buffera vstupnych dat      }

                               _is_pchar   : bool;       { text_adr je @pchar, volanim read_from_editor       }
                               _disp_pchar : bool;       { sa odalokuje, ak disp_disp odalokuje sa i na konci }

                               _odd_rdk,_odd_slv : TCharSet; _odd_rdkr: string;

                               _check_func : pointer;    { TBFunc_p3(@Self,handler_owner,text_adr) }

                               _dxb,_dyb       : int;
                               _init_buttons,

                               _handle_buttons : pointer;
                               _handler_owner  : PObject;
                               _handler_data   : pointer;

                               _bge,_cle, _bga,_cla, _bgv,_clv : byte;
                               _hlpXXX : Pchar
                              );

              destructor  Done; virtual;

              procedure   init_win(_title: string; x,y, dx,dy: int;
                                   _kbHot: char; _cmXXXX: word
                                  ); virtual;

              procedure   Run(var _Event: TEvent); virtual;

              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   handle_buttons(var _Event: TEvent); virtual;

              function    handle_end_state: bool; virtual;
              function    EndState(var _Event: TEvent): bool; virtual;

              procedure   draw_inside; virtual;
              procedure   new_title(_title: string);

             { fcie pre naplnenie/nacitanie pola }
              function    pocet_riadkov: int; { if -1 }

              procedure   _write_line_in_editor (i: word; s: string);
              procedure   __write_in_editor (_text_adr : pointer;  { smernik na spracovavanu premennu }
                                             _text_len : word      { dlzka vstupnych dat }
                                            ); virtual;
              procedure   _write_in_editor  (_text_adr : pointer; _text_len : word);
              procedure   write_in_editor;

              function    _read_line_from_editor (i: word): string;
              procedure   __read_from_editor; virtual;
              procedure   read_from_editor;

              procedure   print_from_editor;

              function    _call_check_func: bool; virtual;
              function    call_check_func: bool;

             { fcie pre inicializaciu/uchovanie obsahu editora
             }
              procedure   make_message; virtual;
              procedure   save_editor;
              procedure   read_editor;

              procedure   clear_item_i(i: int);
              procedure   clear_items;

             { fcie pre editor/nazvy su identicke s "otcom" TScroll }
              function    is_changed: bool; virtual;
              procedure   renew; virtual;

              procedure   item_cl   (b: bool; var co,bk: byte);
              procedure   item_list (i, x,y: int; b: bool); virtual;

              procedure   List; virtual;

             { fcie pre editor/nazvy su identicke s "otcom" Box }
              function    r_s(r,od: int; _1: bool): pchar;

              procedure   move_cursor(nstl: int; nins: bool; res: int);
             {procedure   del_line(r,od: int);}

              function    ClickedChar  (var _Event: TEvent): bool;
              function    _AcceptedKey (var _Event: TEvent): bool; virtual;
              function    AcceptedKey  (var _Event: TEvent): bool; virtual;

             { prepinanie medzi view/edit  }
              procedure   functionality(_viewer: bool);
            end;


     procedure  init_editor_bt(E: PEditors); far;

