(*-------------------------------------------------------------------*)
(* Help 1.0                                                          *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$DEFINE HELP_NOEMS}


unit Help;


interface


     uses   TypeDef,
            ovr, {$I unit_gr.h},
            AStream, Events, Objects, Views, Scroll,
            FIR_def, help_def;


     {$I help_o.h}

     procedure _help (key: pchar); far;
     procedure _help_index;

     function  _handle_info_p (var Ev : TEvent;
                               H : PHelp;
                               O : pointer;
                               P : pointer
                              ): bool; far;
     procedure _info   (fn,tit: string); far;
     procedure _info__ (fn,tit: string;
                        _dxm,_dym : int;
                        _dxb,_dyb : int;
                        _init_buttons,_handle_buttons,_handler_owner : pointer;
                        _SOH,_EOT,_EOH: char;
                        _hlpXXX: pchar
                       );
     procedure _infoh  (fn,tit: string;
                        _dxm,_dym : int;
                        _dxb,_dyb : int;
                        _init_buttons,_handle_buttons,_handler_owner : pointer;
                        _hlpXXX: pchar
                       ); far;
     procedure _infop  (fn,tit: string;
                        _dxm,_dym : int;
                        print,send: bool;
                        _hlpXXX: pchar
                       );


implementation

uses  dos, mem, keyb, mouse, str0, math, sets, io, msg, prnt,
      CMs, Button, Dialog, Lists;


const  help_open: int = 0;

{$I help_o.inc}
{$I help_h.inc}
{$I help_f.inc}
{$I help_i.inc}

begin
  views.p_hlp:= _help;
  init_help;
end.
