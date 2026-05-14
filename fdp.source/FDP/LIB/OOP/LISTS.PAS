(*-------------------------------------------------------------------*)
(* LETVIS FDP - Ponuka                                               *)
(* (c) Ales Kosice 1993,95  (ab)                                     *)
(*-------------------------------------------------------------------*)
{ povolene oddelovace: ' ', ',','-' }
{
  is_in    ind : rovna sa s polozke[ind]
           -1  : existuje polozka v riadku rovnajuca sa s;  vyber - prva polozka
           -2  : rovna sa s celemu riadku ?
           -3  : nacita riadok i s komentarmi, funkcia -1

  get_item =0   : caly radek bez komentara
           >0   : vyberie poziciu
           bolo =-1, teraz -99  : poslednu polozku
           bolo <-10 teraz -101 : od pozicie i+101  sicko
}
{$I comp.h}


unit Lists;


interface


    uses   Typedef, mouse, IO,
           Mem, AStream,
           Events, Views,
           FIR_def;


    { maximum nacitatelnych poloziek je 98 }

    const  setOddel : Tcharset = [' ','(',')'{,'-'}];  { oddelovace }
           setKomen : Tcharset = [';','{'];            { komentar   }
           setTitle : Tcharset = ['"'];


    type   PList = ^TList;
           PPList = ^PList;

           PListDesc = ^TListDesc;
           TListDesc = record
             fn     : pchar;
             lo,poz : int;
             p      : PPList
           end;

           TList = object(TGroup)

             lst     : PListDesc;
             pos,poc : int;
             fname   : string;

             odd     : TcharSet;

             is_init,is_ems : bool;
             is_initialized : bool;
             is_list : bool;
             {$IFDEF NOEMS}
              strm : PPchars;
             {$ELSE}
              stre : PstreamPackedStrings;
             {$ENDIF}
             tit : Pbools;

             lo,            { index prvej a poslednej polozky v okne }
             hi  : int;     { podla ich indexov v originalnom poli   }
             top : int;     { maximalny pocet poloziek               }
             poz : int;     { pozicia vo vypise v <0,top>            }


             filter : PBFunc_s;
             sort   : bool;

             max_len : byte; { najsirsi retazec - sirka }
             b,t, ab,at, item_dy : byte;


             {Mp : TMouseChar;  uchovanie poslednej pozicie mysi  }

             constructor Init(_lst: PListDesc; _fn: string;
                              _odd: TcharSet; _pos: int;
                              _sort: bool; _filter: PBFunc_s;
                              _init: bool
                             );
             destructor  Done; virtual;

             function    alloc: bool; virtual;
             procedure   dealloc; virtual;

             {procedure  InitData; virtual;
             procedure   DoneData; virtual;

             function    is_initialized: bool;
             procedure   was_initialized (ini: bool);}

             function    read_header(line,prev: string): bool; virtual;
             function    is_to_be_run: bool; virtual;

           { aplikacne procedury, su volane z nizsie uvedenych neobjektovych funkcii }

             function    is_to_add  (s: string): bool;
             function    put (riadok,polozka: string; ind: int): bool;
             function    get (ind: int): string;

             function    get_item    (x,y: int) : string;
             function    get_line    (s: string; _pos: int; _ind: pint): string;
             function    get_comment (s: string; _ind: pint): string;
             function    is_in       (s: string): int;

             function    is_nil (i: int): bool;

             {protected}
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   Draw; virtual;

             function    InitList: bool;
             procedure   DoneList;

             procedure   List;
             procedure   item_write (i: int);
             function    data_write (i: int): string; virtual;

             {$IFDEF DEBUG}
              procedure   item_test (s: string); virtual;
             {$ENDIF}
           end;


          {$I lists.h}   { definuje pouzivajuci modul, aby nebolo potrebne robit
                           dalsi modul, napr. FDP_LIST.pas
                         }


    procedure new_ListDesc (var lst: TListDesc; fn: string);
    procedure disp_ListDesc(var lst: TListDesc);

    function  _get_item    (x,y: int ; _lst: PListDesc; _odd: TcharSet; _pos: int; _sort: bool; _filter: PBFunc_s): string;
    function  _get_item_   (x,y: int ; fn: string; _odd: TcharSet; _pos: int; _sort: bool; _filter: PBFunc_s): string;

    function  _get_line    (s: string; _lst: PListDesc; _odd: TcharSet; _pos, _rdk: int): string;
    function  _get_line_   (s,fn: string; _odd: TcharSet;  _pos, _rdk: int): string;

    function  _get_comment (s: string; _lst: PListDesc; _odd: TcharSet; _pos: int): string;
    function  _get_comment_(s,fn: string; _odd: TcharSet; _pos: int): string;

    function  _in_list     (s: string; _lst: PListDesc; _odd: TcharSet; _pos: int; _filter: PBFunc_s): bool;
    function  _in_list_    (s: string; _lst: PListDesc; _odd: TcharSet; _pos: int; _filter: PBFunc_s): int;


    const disp_ERRCODE: bool = true;

    function  _find_err    (fn: string; arrpos,arrspec: string; errpos, errspec: word; var errs: string): bool;
    function  _get_err     (fn: string; arrpos,arrspec: string; errpos, errspec: word; var errs: string): word;


implementation

uses  DOS, str0, math, sets, keyb, mess, sort,
      {$I unit_gr.h},
      CMs, help_def, Scroll;

{var   txt: text;
const test: bool = false;}

{$I list_.inc}
{$I list_object.inc}
{$I list_find.inc}
{$I list_functions.inc}

end. { Lists }
