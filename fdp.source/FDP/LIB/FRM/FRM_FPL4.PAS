(*-------------------------------------------------------------------*)
(* LETVIS FDP - Formulare pre EDD                                    *)
(* (c) Ales Kosice 1994  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}

{$X+,I-,S-,P-}

{ Tieto formulare su v oddelenom module,
  pretoze pri ich spracovani dochadza
  ku vzajomnym odkazom jednotlivych modulov.
  Ziaduce odstranit pri prechode na inu platfromu.
}

{$I comp_FP4.h}

unit frm_FPL4;


interface

    uses  TypeDef,
          sets, keyb, {$I unit_gr.h},
          {$I unit_oop.h}, Lists,
          FIR_def, Bod_def, Body, ZemSur, LDM,
          NET_def, _L4_def, _MTK_2, _FDP_def, _FPL_def,
          _PLAN,
          {$IFDEF TLG}  _TLG, frm_TLG, {$ENDIF}
          {$IFDEF FPL4} _FPL4,_FPLC,   {$ENDIF}
          {$IFDEF RPL}  _RPL,          {$ENDIF}
          FDP_edit;



    {$IFDEF FPL4}
     {$I _FPL4_ftitle.h}
     {$I _FPL4_fo.h}
    {$ENDIF}

    {$IFDEF FORMULAR_FPL4}
     {$I _FPL4_f4.h}

     function  formular_FPL4 (_FPLi   : PFPL4;
                              _src    : fdp_src;
                              _stat   : string;
                              _novy   : bool;

                              _tit    : string;
                              _check  : pointer;
                              _hlpXXX : Pchar
                             ): bool;

     function  formular_FPL4_ (FPL: PFPL4; tit: string; novy: bool): bool; far;

     procedure  _display_decoded_FPL4 (FPL: PFPL4; check: bool; var res: string; var ires: int);

     {$IFDEF TLG}
      procedure  formular_ALR (_FPLi: PFPL4);
     {$ENDIF}
    {$ENDIF}

    {$IFDEF PROCESS_RPL}
     {$I _RPL_f4.h}

     function  formular_RPL_ (RPL: PRPL; tit: string; novy: bool): bool; far;
    {$ENDIF}


implementation

uses mem, mouse, str0, math, mess, utime, msg,
     Crt, DOS, BIOS, IO, DB,
     Kody, _NET,
     Vypocty, Archiv,
     {$I unit_map.h},
     {$IFDEF EXTERNAL_NET} _EXT_def,_EXT,_L4444, {$ENDIF}
     FDP_msg, FDP_scrl,
     _L4_func, FDP_func, FDP_fun2, FDP_fun3,
     frm_FPL,
     STA_def, _SSR, form_SYS;


{$IFDEF FPL4}
 {$I _FPL4_fo.frm}
{$ENDIF}

{$IFDEF FORMULAR_FPL4}
 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € FPL4                €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 {$I _FPL4_f4.frm}
 {$I _FPL4_f.frm}

 {$IFDEF TLG}
  {$I _frm_ALR.inc}
 {$ENDIF}

{$ENDIF}


{$IFDEF PROCESS_RPL}
 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € RPL                 €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 {$I _RPL_plan.frm}
{$ENDIF}


begin
 {$IFDEF FORMULAR_FPL4}
  clear_form(@form_FPL4,size_FPL4alr,@set_NXT);
  p_form_FPL4:= @formular_FPL4_;
 {$ENDIF}

 {$IFDEF PROCESS_RPL}
  clear_form(@form_RPL,size_RPLfrm,@set_NXT);
  p_form_RPL:= @formular_RPL_;
 {$ENDIF}
end.
