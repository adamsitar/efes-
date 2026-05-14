
(*-------------------------------------------------------------------*)
(* Scroll 3.0                                                        *)
(* 1993,95                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ - Ak sa pomylim v poradi arr_adr, top_adr -> moze sa pri renew prepisat pamat
  - Obmedzenie : maximalny pocet poloziek dany typom int (32767) ...
}

unit Scroll;


interface


    uses   TypeDef,
           _Check,
           DOS, BIOS, IO, DB,
           {$I unit_gr.h},
           Arrays, AStream,
           Events, Objects, Views, Button;



    {$I scroll_0.h}   { info, konstanty }

    {$I scroll_1.h}   { scrollbar }
    {$I scroll_2.h}   { scroller  }

    {$I scroll_t.h}   { typy      }

    {$I scroll_3.h}   { scrollwin }

    procedure init_sc_butt1 (sc: PScrollWin); far;
    procedure init_sc_butt2 (sc: PScrollWin); far;


    {$I scroll_4.h}   { scrollact - spracovanie zvolenej polozky }
    {$I scroll_5.h}   { scrollind - polozky su odkazovane cez index v poli }

    {$I scroll_b.h}   { scrollapp    }
    {$I scroll_c.h}   { scrollstream }

    {$I scroll_9.h}   { scrolllst }
    {$I scroll_6.h}   { scrolldir }
    {$I scroll_8.h}   { scrolldb  }

    {$I scroll_a.h}   { inso }



implementation

uses  keyb_int, keyb, mouse, mem, math, str0, sort, utime, sets,
      CMs, Msg, Dialog;


{$I scroll.inc}

{$I scroll_1.inc}  { TScrollBar }
{$I scroll_2.inc}  { TScroller  }

{$I scroll_3.inc}  { TScrollWin }
{$I scroll_4.inc}  { TScrollAct }
{$I scroll_5.inc}  { TScrollInd }

{$I scroll_b.inc}  { TScrollApp }
{$I scroll_c.inc}  { OScrollStream }


const dx_FN  = 8*NAME_EXT;
      dy_FN  = 8;
      __bgsl = clBUTTON_COLOR;
      __medzerasl = 4;
      __dxisl     = 4;
      __dyisl     = 4;

{$I scroll_9.inc}  { TScrollLST }
{$I scroll_6.inc}  { TScrollDIR }
{$I scroll_8.inc}  { TScrollDB  }

{$I scroll_a.inc}  { scroll_DB, init_dir, list_dir }


end. { Scroll }