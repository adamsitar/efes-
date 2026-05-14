(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1993,96 (ab)                                      *)
(* FPL                                                               *)
(*-------------------------------------------------------------------*)
{
  Definicia datovych struktur s FPL
}
{ Pre FDP_EDD by sa zmena mala FPL uskutocnovat nasledujucimi sposobmi :
  - oprava planu (S alebo EDD)
  - oprava parametrov potvrdenia planu
  - oprava parametrov pre RDP (acc)
  - pokec pre sektorizaciu v prislusnom module
}


{$I comp.h}
{$I comp_fdp.h}


{$X+,I-,S-,P-}


unit _FPL;


interface


    uses    TypeDef,
            DB, Objects, Events, Scroll,
            {$I unit_gr.h},
            {$I unit_net.h},
            Bod_def, _L4_def,
            Views, Button, help_def, Help, Menus, Dialog, App, CMs, CM,
            {$I unit_map.h},
            _FDP_def, _FPL_def,
            FDP_scrl,
            _PLAN, _STRIP;


    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                    €
    € FPL - LETOVY PLAN  €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

     {$IFDEF FPL0}
       {$I _oFPL_title.h}
       {$I _oFPL_.h}       { objekt TFPL }

       procedure alloc_EDD_STRIPmenu_items (iFPL: P_OFPL; FPL: pointer; var  smnu: TPItems; var items,nl: int; vis: bool);
       procedure alloc_STRIPmenu_items (iFPL: P_OFPL; FPL: pointer; var  smnu: TPItems; var items,nl: int; vis: bool);
       function  _handle_event_on_strip (var Ev: TEvent; FPL: pointer; iFPL: P_OFPL; dx,dy: int): bool;

       {function  decode_ack_iFPL (key: string; nd: int; iFPL: P_OFPL; p_codekey: PSFunc_p): bool; far;}
     {$ENDIF}


implementation

uses  BIOS, _Check, IO,
      mem, str0, sets, math, keyb, mouse, mess, sort, utime, msg,
      Body, Vypocty, ZemSur, LDM,

      FDP_msg, FDP_fun2,

      {$IFDEF ARCHIVE_DAR}  DAR_arch, {$ENDIF}
      {$IFDEF SECTORS}      Sector,   {$ENDIF}

      Archiv;


{$IFDEF FPL0}

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                       €
€ letovy plan - TFPL    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

  {$I _oFPLhndl.inc}   { viewer handlery pre EDD }

  {$I _oFPL5.inc}      { objekt TFPL             }

  {$I _oFPL_SSR.inc}
  {$I _oFPL_MAP.inc}   { vykreslenie cielov      }
  {$I _oFPL_SEC.inc}   { spracovanie na sektore, povodna zbuchana verzia }
  {$I _oFPL_RDP.inc}   { koordinacia s RDP       }
  {$I _oFPL_ABI.inc}   { koordinacia ABI         }

  {$I _oFPL_check.inc}
  {$I _oFPL.net}

{$ENDIF}

end. { _FPL }