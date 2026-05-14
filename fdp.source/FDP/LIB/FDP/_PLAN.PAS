(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL,EDD                                              *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(* PLANy - vseovecnie vlastnosti                                     *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}

{$X+,I-,S-,P-,B-}


{ Pozn. Nova verzia by mala zohladnocvat, ci plan nebol medzicasom
        spracovany na inom pracovisku : napr. porovna sa original
        spracovaveneho planu s planom nacitanym z databazy, alebo
        sa porovnaju datum posledneho spracovania originalu
        a planu z databazy. Napr. osetrenie viacnasobneho
        spracovania.
}

unit _PLAN;


interface

    uses    TypeDef,
            _Check, bios, DB,
            {$I unit_gr.h},
            Arrays, {$I unit_oop.h},
            NET_def, Bod_def,
            {$I unit_map.h},
            _FDP_def, _FPL_def;


    const   gr_map = 1;
            fl_map = 1;   { nastavi sa, ak mapa nie je vykreslena }

    const   preaktivovanie_planu : bool = {$IFDEF SK} true  {$ELSE} false {$ENDIF};
            ask_zrus_plan        : bool = {$IFDEF CZ} false {$ELSE} true  {$ENDIF};

    {$I _plan_vypocet.h}
    {$I _plan_object.h}
    {$I _plan_type.h}

    {$I fdp_sc3.h}

    function  formular_idn   (iPLAN: pointer; _tit: string): int;
    function  formular_idn_i (iPLAN: pointer; _tit: string; var i: int): bool;


implementation

uses  IO, DOS,
      mem, sets, keyb, str0, mouse, utime, prnt, math, sort,
      Msg, FDP_msg, Lists, _L4_def,
      Archiv,
      _NET, FDP_scrl;


{$I _plan_obj.inc}   { Init,Done               }
{$I _plan_abs.inc}   { abstraktne funkcie      }
{$I _plan_add.inc}   { Add,Eq,Del              }

{$I _plan_prn.inc}   { vytlacenie ('AA')       }
{$I _plan_drw.inc}   { vypis a vykreslenie     }

{$I _plan_db.inc}          { nacitanie         }
{$I _plan_net.inc}
{$I _plan_spracovanie.inc} { spracovanie       }
{$I _plan_vypocty.inc}     { vypocty platnosti }
{$I _plan_check.inc}

{$I _plan_idn.frm}


{$I fdp_sc3.inc}

begin
  clear_form(@Form_IDN,1,nil);
end.