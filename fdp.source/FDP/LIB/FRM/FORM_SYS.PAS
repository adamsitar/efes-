(*-------------------------------------------------------------------*)
(* Forms                                                             *)
(* 1994                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit form_SYS; { mensie formulare }


interface


     uses   TypeDef,
            utime, sets,
            {$I unit_gr.h},
            Scroll, Edit, Lists;


     {$I sys_tit.h}

     function   formular_DATUM_CAS(_title: string; var datum: TDatum): bool;

     function   formular_DATUM (var _plan_date: TDate; x,y: int; _tit: string): bool;

     function   formular_CAS   (var _plan_time: TTime; { premenna pre vratenie casu }
                                _hour,_min    : byte;  { inicializacia frm hodnotami }
                                x,y: int; _tit: string; _info: pchar
                               ): bool;

     procedure  formular_HODINY;



     {$I _FPLid_fr.h}   { formular pre zadanie identifikacie letu }

     procedure init_buttons_key(form: PFormular); far;

     function  formular_key_fpl(tit: string; _13a: PListDesc;
                                empty,date,all,arch: bool;
                                var key: string
                               ): bool;

     function   formular_ARR (zac,kon: TDatum;
                              var arr: TDatum;

                              sc  : PScroller;
                              tit,idn : string;

                              err_pole   : string;
                              err_kratsi : int;
                              dlhsi      : bool;
                              err_dlhsi  : int
                             ): bool;


implementation

uses  DOS, BIOS, IO,
      mouse, keyb, mess, str0, math, prnt, msg,
      Events, CMs, Dialog, help_def, Help, Button,
      _L4_def, _FDP_def, FDP_msg {, Hodiny};


{$I datum.frm}
{$I cas.frm}
{$I hodiny.frm}
{$I key_fpl.frm}
{$I arr.frm}

begin
  clear_form(@form_UTC,2,nil);
  clear_form(@form_DATUM_CAS,2,nil);
  clear_form(@form_key_fpl,size_key_fpl,nil);
end.