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


unit frm_FPL;


interface


     uses  TypeDef,
           sets, keyb, {$I unit_gr.h},
           {$I unit_oop.h}, Lists,
           FIR_def, Bod_def, Body, ZemSur, LDM,
           NET_def, _L4_def, _MTK_2, _FDP_def, _FPL_def,
           _PLAN, _FPL,
           _FPL4, {$IFDEF FPL0} _FPLC, _FPLM, _FPLMv, {$ENDIF}
           FDP_edit;


    {$IFDEF FPL0}

     { I _rtemnu.h}

     {$I _FPLc_ftitle.h}
     {$I _FPLc_fo.h}

     function   formular_cFPL_(p: pointer; tit: string): bool; far;
     function   formular_cFPL (FPLi  : PDcFPL;
                               _src  : fdp_src;
                               _novy : bool;

                               _tit  : string;
                               _pos  : int;
                               _ssr,_viewer,_copy_data : bool
                              ): bool; far;


     {$IFNDEF FPLM_DISABLED}
      {$I _FPLm_fo.h}

      function   formular_mFPL_(p: pointer; tit: string): bool; far;
      function   formular_mFPL (FPLi    : PDmFPL;
                                _src    : fdp_src;
                                _stat   : string;
                                _novy   : bool;

                                _tit    : string;
                                _pos    : byte;
                                _check  : pointer;
                                _hlpXXX : Pchar
                               ): bool; far;

      procedure  _display_decoded_FPLM (FPL: PFPLM; check: bool; var res: string; var ires: int);

      {$I _FPLm_ob.h}
     {$ENDIF}

    {$ENDIF}



implementation

uses mem, mouse, str0, math, mess, utime, msg,
     Crt, DOS, BIOS, IO, DB,
     Kody, _NET,
     Vypocty, Archiv,
     {$I unit_map.h},
     FDP_msg, FDP_scrl,
     _L4_func, FDP_func, FDP_fun2, FDP_fun3,
     STA_def, _SSR, form_SYS;


{$IFDEF FPL0}
 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € cFPL                €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 { IFDEF FDP_EDD}
   {$I _FPLc1.frm}
   {$I _FPLc2.frm}
   {$I _FPLc.frm}
   {$I _FPLc0.frm}
 { ENDIF}

 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € mFPL                €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 {$IFNDEF FPLM_DISABLED}
  {$I _FPLm_f0.frm}       { objekt pre formular     }
  {$I _FPLm_f1.frm}       { externe funkcie objektu }
  {$I _FPLm_f2.frm}       { kontrola spravnosti     }
  {$I _FPLm_f.frm}        { volanie formulara       }
 {$ENDIF}

 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € OB                  €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 {$IFDEF FDP_OPL}
   {$I OB.frm}
 {$ENDIF}

{$ENDIF}


{$IFDEF FPL0}
begin
  clear_form(@Form_cFPL,SIZE_frm_cFPL,nil);
  {IFDEF FPLC_L} p_info_FPLc:= info_cFPL; {ENDIF}
  if ENABLE_FPLC then p_form_FPLC:= @formular_cFPL_;

 {$IFNDEF FPLM_DISABLED}
  clear_form(@Form_mFPL,SIZE_frm_mFPL,nil);
  {p_info_FPLm:= info_mFPL;}
 {$ENDIF}
{$ENDIF}
end.
