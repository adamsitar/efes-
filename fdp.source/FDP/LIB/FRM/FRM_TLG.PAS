(*-------------------------------------------------------------------*)
(* LETVIS FDP - Formulare pre EDD                                    *)
(* (c) Ales Kosice 1994  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}

{$X+,I-,S-,P-}


unit frm_TLG;


interface


     uses  TypeDef,
           sets, io,
           {$I unit_gr.h},
           {$I unit_oop.h}, Lists,
           {$I unit_net.h},
           FIR_def, Bod_def, Body, ZemSur,
           _MTK_2, _L4_def, _FDP_def,
           {$IFDEF FPL4} _FPL4, {$ENDIF}
           FDP_edit;


     { Telegram ma sirku MTK_2_LINE znakov
     }

     {$I _TLG_title.h}
     {$I _TLI_fr.h}
     {$I _TLI_fo.h}
     {$I _TLG_fo.h}


     procedure  formular_TLG;

     {$IFDEF TLG}

      {$IFDEF PROCESS_FPL4}
       procedure  formular_RCF(FPL: PFPL4);
       procedure  formular_ANP(FPL: PFPL4);
       procedure  formular_FLA(FPL: PFPL4);

       {$IFDEF FLI_COORDINATION}
         function  formular_FLI(FPL: PDcFPL): bool;
       {$ENDIF}

      {$ENDIF}

      {$IFDEF TSGA}
       procedure  formular_RTS;
       procedure  formular_RTO;
       procedure  formular_RVM;
       procedure  formular_RVI;
      {$ENDIF}

     {$ENDIF}


implementation

uses mouse, keyb, str0, math, mess, utime, msg,
     Crt, DOS, BIOS, DB,
     Archiv,
     _FPL_def,
     FDP_msg, FDP_scrl,
     FDP_func, FDP_fun2,
     _TLG,
     {$IFDEF FLI_COORDINATION} _FPLC, {$ENDIF}
     form_SYS;


{$I _frm_TLi.inc}      { vseobecny telegram s hlavickou a datami }
{$I _frm_TLG.inc}


{$IFDEF TLG}

 {$IFDEF PROCESS_FPL4}
   {$I _frm_RCF.inc}
   {$I _frm_ANP.inc}
   {$I _frm_FLA.inc}
   {$I _frm_FLI.inc}
  {$ENDIF}

  {$IFDEF TSGA}
    {$I _frm_RTS.inc}
    {$I _frm_RVM.inc}
  {$ENDIF}
 {$ENDIF}


 var SaveExit : pointer;

 procedure done_TLG; far;
     begin
       disp_form(form_TLGaftn,size_TLGaftn);
       ExitProc:= SaveExit
     end;

 procedure init_TLG;
     var   i : int;
     begin
       SaveExit:= ExitProc;
       ExitProc:= @done_TLG;

       form_TLGaftn:= alloc_form (size_TLGaftn); { alokujem tento velky formular, aby sa nedrzal v DS }
       for i:= 0 to size_TLGaftn-1 do
         begin
           acpy_form(@form_TLGaftn_i[0], @form_TLGaftn^[i], 1);
           inc(form_TLGaftn^[i].dy,i*10)
         end;
       clear_form(form_TLGaftn,size_TLGaftn,nil);
     end;


begin
  init_TLG;
  clear_form (@form_TLGadr[1],size_TLGadr-1,nil);

  {$IFDEF TLG}
   {$IFDEF PROCESS_FPL4}
    clear_form (@form_RCF,size_RCF,nil);
    clear_form (@form_ANP[1],size_ANP-1,nil);
    clear_form (@form_FLA[1],size_FLA-1,nil);

    {$IFDEF FLI_COORDINATION}
     clear_form (@form_FLI[1],size_FLI-1,nil);
     p_formular_FLI:= formular_FLI;
    {$ENDIF}
   {$ENDIF}

   {$IFDEF TSGA}
    clear_form (@form_RTS[1],size_RTS-1,nil);
    clear_form (@form_RVM[1],size_RVM-1,nil);
   {$ENDIF}
  {$ENDIF}
end.