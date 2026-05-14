(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL_func                                             *)
(* (c) Ales Kosice 1995  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}

{
  Funkcie pre spracovanie vojenskych planov.
  Kod letiska je jednou z klucovych poloziek pre spracovanie planu.

  Zatial sa ziskava z X25.cfg a moze byt len jeden, ciselny kod,
  kvoli kontrole na spravnost identifiklacie letu.
  Neskor definovat subor alias mien podla AIPu i prepocet pre vyssie uvedene.
}

unit FDP_fun2;


interface


     uses   TypeDef,
           {$I unit_net.h},
           {$I unit_oop.h}, Lists,
           FIR_def, _L4_def;


     {$I FDP_f2ti.h}

     const   extFLO     = '.flo';
             kod_FLO    = 3;

             cfg_FLO    = 'FLO';
             {cfg_FLO_M  = 'FLO-M';
             cfg_FLO_O  = 'FLO-O';}
             cfg_LOCKED = 'LOCKED';

             fnPrevM    : TListDesc = (fn:'mil'+extFLO; lo:0;poz:0; p:nil);


     type    Tflo_type = (civ,mil,oth);

             Pflo_desc = ^Tflo_desc;
             Tflo_desc = record
               kod : string[kod_FLO];
               typ : Tflo_type
             end;

     function  flo_call (code: string): string;
     function  flo_name (code: string): string;
     function  is_flo_mil (code: string): bool;


     procedure _info_SLNKO;
     procedure _info_TYP(_9: string; _dxm,_dym: int);

     function  AIP_menu: PWinMenu;
     function  _handle_AIP_list(var _Event: TEvent; O: PObject): bool;
     procedure _list_OPL(x,y: int);
     procedure _list_AIP(x,y: int);


implementation

uses  bios, str0, mem, math, utime, sets, io, msg, mouse, keyb,
      SVGA, BGIgraph,
      Bod_def, Body,
      form_SYS,
      _MTK_2, FDP_func, FDP_msg,
      _L4_func;


{$I _FLO.inc}

{$I FDP_f2_0.inc}  { info... }
{$I FDP_f2_1.inc}  { menu s vychodom,zapadom,... }


var  SaveExit : pointer;

procedure done_FDP_fun2;
    begin
      ExitProc:= SaveExit;
      done_FLO;
    end;

procedure init_FDP_fun2;
    begin
      SaveExit:= ExitProc;
      ExitProc:= @done_FDP_fun2;
      init_FLO;
    end;

begin
  init_FDP_fun2;
end.