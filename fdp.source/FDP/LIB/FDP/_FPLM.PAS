(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1993,99 (ab)                                      *)
(* FPL                                                               *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}


{$X+,I-,S-,P-}


unit _FPLM;


interface

    uses    TypeDef,
            DB, mem, str0, sets, math, keyb, mouse, mess, msg, sort, utime,
            {$I unit_gr.h},
            {$I unit_oop.h}, Lists,
            RTR_def, NET_def,
            Bod_def, Body,
            {$I unit_map.h},
            FIR_def, _MTK_2, _L4_def, _L4_func,
            _FDP_def, _FPL_def,
            FDP_edit, FDP_scrl,
            FDP_func, FDP_fun2,
            _PLAN, _STRIP, _FPL;


    {$IFDEF FPL0}
    {$IFNDEF FPLM_DISABLED}
      { I _FPLm_cnst.h}
      {$I _FPLm_var.h}
      { I _FPLm_err.h}

      {$I _FPLm_tit.h}
      {$I _FPLm_mnu.h}
      {$I _FPLm_plan.h}

      {$I _FPLm_fr.h}

      {$I _oFPLm.h}    { trat a pozn maju do 110 znakov, vid mfpl.frm, mfpl.cod }
      {$I _oFPLo.h}
      {$I _oFPL.h}

      {$I _FPLm_func.h}
    {$ENDIF}
    {$ENDIF}


implementation

uses  DOS, BIOS, _Check, IO, Crt,
      {$IFDEF PRN} coms, prnt, {$ENDIF}
      {$IFDEF MPU} MPU,        {$ENDIF}
      ParStr,
      Kody, _NET,
      Vypocty, ZemSur, LDM,

      FDP_msg, Archiv,

      {$IFDEF FDP_OPL}      Status,   {$ENDIF}
      {$IFDEF STATISTIKA}   STA_def,  {$ENDIF}
      {$IFDEF ARCHIVE_DAR}  DAR_arch, {$ENDIF}

      Sector;


{$IFDEF FPL0}
{$IFNDEF FPLM_DISABLED}

  function _zarad_FPLm(FPL: PDmFPL; _stat: string; _send: bool; _src: fdp_src; prop: bool): bool; forward;

  {$I _FPLm_plan.cod}
  {$I _FPLm_proc.inc}  { FPLM a FPLO }
  {$I _FPLm_plan.inc}  { new,save... }

  {$I _FPLm_0.vyp}     { format }
  {$I _FPLm_1.vyp}     { stav planu }
  {$I _FPLm_2.vyp}     { priradenie identifikacie }
  {$I _FPLm_3.vyp}     { dekodovanie trate na body, cinnost v priestore }
  {$I _FPLm_4.vyp}     { zmena trate, prislusnost na sektory }
  {$I _FPLm_5.vyp}     { syntax }

  {$I _FPLm_plan.drw}
  {$I _FPLm_strip.drw}

  {$IFDEF PRN}
    {$IFDEF IER}       {$I _FPLm.ier}
    {$ELSE}            {$I _FPLm.prn}
    {$ENDIF}
  {$ENDIF}
  {$IFDEF MPU}         {$I _FPLm.mpu}
  {$ENDIF}

  {$I _oFPLm5.inc}     { object TmFPL - definovanie vojenskeho planu }
  {$I _oFPLm7.inc}     { object TmFPL - definicia abstraktnych funkcii }
  {$I _oFPLm9.inc}     { object TmFPL - check }
  {$I _oFPLm10.inc}    { objekt TmFPL - kreslenie ciela }

  {$I _oFPLo5.inc}     { object ToFPL - definovanie ineho planu }

  {$I _FPLm_send.inc}  { send...       }
  {$I _FPLm_net.inc}

  {$I _FPLm_functions.inc}  { void fc  }

{$ENDIF}
{$ENDIF}
end. { _FPL }