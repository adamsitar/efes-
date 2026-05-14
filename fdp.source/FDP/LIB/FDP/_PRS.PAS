(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.9                                              *)
(* (c) Ales Kosice 1993,99  (ab)                                     *)
(* Priestory                                                         *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}

{ Pretoze plan moze presahovat do nasledujuceho dna (len na 24 hodin...),
  pri inicializacii sa musi prezriet i predchadzajuci den.

  Kontrole na podanie planu nepodliehaju plany s poznamkou
  obsahujucou test a cislo.
}


unit _PRS;


interface


    uses  TypeDef, DB,
          AStream,
          {$I unit_gr.h},
          {$I unit_oop.h}, Lists,
          {$I unit_net.h},
          {$I unit_map.h},
          _L4_def, _MTK_2, _L4_func, _FDP_def, _FPL_def,
          FDP_edit, 
          _PLAN, _STRIP;


    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € PRIESTORY                   €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    {$IFDEF PRS}
      {$I _PRS.doc}
      { I _PRS_cnst.h}
      {$I _PRS_title.h}
      {$I _PRS_mnu.h}
      {$I _PRS_plan.h}          { ziadosti pre AMC o pridelenie priestoru }
      {$I _PRS_functions.h}
      {$I _oPRS.h}

      function  _handle_event_PRS (var _Event: TEvent; O: PObject; PRS: pointer): bool;
    {$ENDIF}


implementation

uses  BIOS, _Check, DOS, IO,
      keyb, mouse, str0, sets, mess, utime, math, sort, prnt, msg, mem,
      Vypocty, Archiv,
      FIR_def, Body,
      FDP_scrl, FDP_msg, form_SYS,
      FDP_func, FDP_fun2,
      _NOTAM {$IFDEF FUA} ,_FUA {$ENDIF}
      {$IFDEF ARCHIVE_DAR},     DAR_arch  {$ENDIF}
      {$IFDEF STATISTIKA} ,     STA_def   {$ENDIF}
      ;


{$IFDEF PRS}

{ spracovanie planov o vyuzitia vzdusneho priestoru
  na 24 hodinovy casovy interval
}
 const  p_prs_dbscroller : PScrollDB_FDP = nil;

        cnst_prs_change       = cnst_disk + cnst_sended {$IFDEF AMC} + cnst_dec + cnst_acc {$ENDIF}; {cnst_act_plan;}
        cnst_prs_planned      = cnst_requested + cnst_dec + cnst_acc;

        find_and_process_data = true;        { docasna premenna }


 procedure  add_PRS(PRS: PPRS); far; forward;

 {$I _PRS_frm.h}

 {$I _PRS_plan.cod}

 {$I _PRS_plan.vyp}
 {$I _PRS_1.vyp}       { stav }
 {$I _PRS_5.vyp}

 {$I _PRS_.inc}
 {$I _PRS_plan.inc}    { okrem odosielania/opakovania spravy o zruseni priestoru ku RDP }
 {$I _PRS_plan.drw}
 {$I _PRS_plan.prn}

 {$I _PRS2.inc}        { zakladne spracovanie }

 {$IFDEF PROCESS_PRS}
   function  formular_PRS(PRSi: PPRS; _uloz,_arch: bool; _src: fdp_src; _stat,_tit: string): bool; forward;

   {$I _PRS3.inc}      { spracovanie dat : oprava,zrusenie,aktivovanie,prerusenie,pokracovanie,ukoncenie }
   {$I _PRS_plan.frm}
   {$I _PRS_rpl.inc}   { prehlady RPL                          }
 {$ENDIF}

 {$I _PRS4a.inc}       { handlery pre spracovanie v prehlade   }
 {$I _PRS4.inc}        { prehlad planov podla roznych kriterii }
 {$I _PRS5.inc}        { proposed..actived; objekt, ako vzdy   }
 {$I _PRS10.inc}

 {$I _PRS_send.inc}    { odoslanie }
 {$I _PRS_net.inc}     { prijem    }
 {$I _PRS_functions.inc}


 {$I _PRS_handle.inc}
 { I _PRS_archiv.inc}


var  SaveExit : pointer;

procedure done_PRS;
    begin
      ExitProc:= SaveExit;
     {$IFDEF FUA}
      {done_FUA;}
     {$ENDIF}
    end;

procedure init_PRS;
    begin

      SaveExit:= ExitProc;
      ExitProc:= @done_PRS;

      write('Initialize ASM... ');
      clear_form(@form_key_prs,size_key_prs,nil);
      {$IFDEF PROCESS_PRS}
       clear_form(@frm_PRS,SIZE_frm_PRS,nil);
      {$ENDIF}
      polomer_PRS:= Limit(read_cfg_word(SYSTEMcfg,cfg_polomer_PRS,polomer_PRS),3,30, 0);
      writeln('Done.');

      {$IFDEF FUA}
       {init_FUA;}
      {$ENDIF}

      {kontrola_archivu;}
    end;

begin
  init_PRS;
{$ENDIF}
end.