(*----------------------------------------------------------------------*)
(* LETVIS FDP - SERVER 1.0                                           *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(* Menu pre OPL                                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit Menu;


interface

    uses  TypeDef, Menus;

    var   FDAmenu : PBarMenu;


    function  FDAmenu_init: PBarMenu;


implementation

uses  BIOS, SVGA, DOS, keyb, msg, mess, mouse, utime, graph_h, prnt, str0,
      CMs, CM, Views, help_def, Help, Button, Dialog, Scroll, Edit, Report, Lists, App,
      Hodiny,
      {$I unit_map.h},
      NET_utc, NET_def,
      _L4_def,_FDP_def,_FPL_def,
      FDP_msg, _PLAN, _STRIP, _SSR,
      {$I unit_fdp.h}
      {$I unit_fdf.h}
      {$I unit_ext.h},
      FDP_ap, FDP_fun2,
      ALES, GUI;


{$IFDEF UKBB_ACC}
  {$DEFINE EXT_OPTIONS}
{$ENDIF}

const tit_FDA = 'FDP~/~FDA';

const  ZOZNAMY       = ' FPLs/FLIGHTs T~A~BLES ';
procedure mnuZOZNAMY_init(MMenu: PSubmenu); far; forward;

{$I _fdp.mnu}
{$I _zoznamy.mnu}

{$IFDEF UKBB_ACC}
  {$I acc_bb.mnu}
{$ENDIF}

{$IFDEF UKBB_PRN}
  {$I ukbb_prn.mnu}
{$ENDIF}

end.