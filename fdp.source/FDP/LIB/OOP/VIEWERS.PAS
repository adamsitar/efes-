(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1993,99  (ab)                                     *)
(*-------------------------------------------------------------------*)

{$I comp.h}


unit Viewers;


interface


    uses   Typedef,
           Objects, Events, Views, Help;


    {$I help_v.h}

    procedure HelpViewer(_fn,_title: string;
                         _p_archiv: PSFunc_s; _p_export: pointer; _d_title: bool;
                         _hlpXXX: pchar);


implementation

 uses  math,dos,bios,io,keyb,db,str0,_check,mouse,mem,msg,
       {$I unit_gr.h},
       CMs, Button, Scroll, Dialog, Menus{,
       Archiv};  { <= Toto linkovanie nie je ciste }

 {$I help_v.inc}


end.

