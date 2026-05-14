(*-------------------------------------------------------------------*)
(* FDP_scrl                                                          *)
(* 1995,99                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit FDP_scrl;


interface


    uses  TypeDef,
          _Check, DOS, IO,
          {$I unit_gr.h},
          Arrays, AStream,
          Events, Objects, Views, Button, Scroll;


    {$I FDP_scrl.h}
    {$I FDP_sc_title.h}


    function scroll_DB_FDP (    _title        : string;   { hlavicka }

                                _find_and_process_data,
                                _find_cnl_data,
                                _msg_not_processed : bool;
                                _finded_data  : pint;

                           { a) parametre pre pole }
                                _items        : int;      { maximum overdrive }
                                _item_size    : word;     { velkost polozky }

                                _new_item     : pointer;  { Tproc_p2 - alokacia polozky }
                                _format_item  : pointer;  { Tproc_p - formatovanie }
                                _disp_item    : pointer;  { Tproc_pl dealokacia, moze byt nil }
                                _eq_items     : pointer;

                                _kluc         : string;
                                _p_read       : PIFunc_sp;

                                _p_filter     : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                                _p_kluc       : PBFunc_p2;   { porovnanie identifikacnych udajov }
                                _p_stav       : PBFunc_p2;   { porovnanie inych udajov }
                                _p_datadb     : PBFunc_p2;   { kontrola pripustnosti nacitania }
                                _p_dataext    : PBFunc_p2;   { kontrola pripustnosti zaradenia }

                                _vzostupne    : bool;
                                _sort_item    : pointer;     { Tproc_p2 - zotriedenie zoznamu      }
                                _comp_item    : pointer;     { alebo priama funkcia pre porovnanie }

                                _handler_type : TScrollAct_handler_type;
                                _handler      : pointer;  { @TBfunc_i  }
                                _handler_par  : pointer;  { adresa objektu dat alebo parametrov }

                                _init_buttons   : pointer;
                                _handle_buttons : pointer;
                                _handler_data   : pointer;

                                _print        : pointer;
                                _send         : pointer;

                           { b) parametre pre DBF  }
                                _FN          : string;
                                _FNfunc      : pointer;  { Fcia pre FN, @TSfunc_pi   }
                                _FNfunc_p    : pointer;  { parameter p pre TSFunc_pi }
                                _riadkov     : byte;
                                _DATAdecode  : pointer;
                                _DBchg       : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                           { c) parametre pre ScrollWin }
                                _item_dx,_item_dy: int;  { velkost polozky }
                                _item_list    : pointer; { vypis polozky }

                                _info,_hlpXXX : Pchar;

                           { d) parameter pre program
                           }
                                p_dbscroller : pPScrollDB_FDP

                           ): bool;


    procedure sc_menu_xy(sc: PScroller; var x,y: int; dx,dy: int);


implementation

uses  bios, mem, keyb, utime, str0, prnt, mouse, math, sort, sets, DB,
      CMs, CM, Dialog, help_def, Help,
      Msg, FDP_msg, _FDP_def,
      Archiv;


{$I fdp_sc1.inc}
{$I fdp_sc2.inc}

procedure sc_menu_xy(sc: PScroller; var x,y: int; dx,dy: int);
    begin
      if (sc<>nil) and (not sc^.finded_and_processed_data) then
          begin
            sc^.get_pos_xy(sc^.pos, x,y);
            inc(x,dx);
            inc(y,dy)
          end
      else begin
             x:= initX;
             y:= initY
           end;
    end;

end.