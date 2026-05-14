(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1993,99 (ab)                                      *)
(* FPL                                                               *)
(*-------------------------------------------------------------------*)

{ Mam chybu, ak je sizeof(DcFPL)=484, dochne program (pri UKBB,IPX3)
  ------------------------------------------------------------------

  Sektorizacia pocitana na prvy a posledny bod na trati,
  ak je medzi nimi "medzera" a jeden z nich je osamoteny,
  nerata sa.

  Ak je b1 (vstupny/vystupny [podla casu]) mimo sektoru,
  a jeho vzdialenost od neho je mensia ako nastavena
  maximalna vzdialenost io bodu od hranice, priradi sa
  cas na bode.
  Ak je vzdialenost vacsia ako nastavena a druhy bod
  lezi v sektore a takejto vzdialenosti od hranice,
  nastavi sa priznak daleko.

}


{$I comp.h}
{$I comp_fdp.h}


{$X+,I-,S-,P-}


unit _FPLc;


interface


    uses    TypeDef,
            sets, {$I unit_gr.h}, DB,
            {$I unit_oop.h}, Lists,
            RTR_def, NET_def,
            {$I unit_map.h},
            FIR_def, Bod_def, Body, ZemSur,
            _L4_def, _FDP_def, _FPL_def,
            _FPL4,
            _PLAN, _STRIP, _FPL,
            FDP_edit;


    {$IFDEF FPL0}
     {$IFNDEF FPL4}
       {$I _FPLc_cnst.h}       { _L4_def }
       {$I _FPLc_plan.h}       { _FPL4   }
     {$ENDIF}

     {$I _FPLc_fr.h}

     {$I _FPLc_object.h}     { objekt pre jeho spracovanaie (dedic PLAN->STRIP->FPL->FPLc }
     {$I _FPLc_functions.h}
     { I _FPLc_process.h}
    {$ENDIF}


implementation

uses  BIOS, _Check, DOS, IO,
      mem, str0, math, keyb, mouse, mess, sort, utime, msg,

      {$IFDEF PRN} coms, prnt, {$ENDIF}
      {$IFDEF MPU} MPU,        {$ENDIF}

      Kody, _NET,
      LDM, _MTK_2,
      Vypocty, Archiv,
      FDP_msg, FDP_func,

      {$IFDEF STATISTIKA}   STA_def,  {$ENDIF}
      {$IFDEF ARCHIVE_DAR}  DAR_arch, {$ENDIF}

      _SSR, SECTOR;


{$IFDEF FPL0}
  {$I _FPLc_plan.cod}

  {$IFNDEF FPL4}
    {$I _FPLc_0p.inc}  { vo FPL4 }
    {$I _FPLc_0p.vyp}  { format - vo FPL4 }
  {$ENDIF}
  {$I _FPLc_1p.inc}

  {$I _FPLc_1p.vyp}    { stav planu }
  {$I _FPLc_3p.vyp}    { dekodovanie trate na body, cinnost v priestore }
  {$I _FPLc_4p.vyp}    { zmena trate, prislusnost na sektory }

  {$I _FPLc.drw}

  {$IFDEF PRN}
    {$IFDEF IER}       {$I _FPLc.ier}
    {$ELSE}            {$I _FPLc.prn}
    {$ENDIF}
  {$ENDIF}
  {$IFDEF MPU}         {$I _FPLc.mpu}
  {$ENDIF}

  {$I _FPLc_si.inc}    { sektorizacia    }
  {$I _FPLc_fli.inc}   { koordinacia FLI }

  {$I _oFPLc5.inc}     { objekt TcFPL - predefinovanie metod }
  {$I _oFPLc7.inc}     { objekt TcFPL - definicia abstraktnych funkcii }
  {$I _oFPLc9.inc}     { object TcFPL - check }
  {$I _oFPLc10.inc}    { objekt TcFPL - kreslenie ciela }

  {$I _FPLc_send.inc}  { send }
  {$I _FPLc_net.inc}

  {$I _FPLc_functions.inc}
  { I _FPLc_archiv.inc}


begin
  write('Initialize FPLC... ');

  ENABLE_FPLC  := read_cfg_bool(SYSTEMcfg,cfg_ENABLE_FPLC,ENABLE_FPLC) {$IFDEF DEMO} or true {$ENDIF};
  FPLC_CPL     := read_cfg_bool(SYSTEMcfg,cfg_ENABLE_CPL,FPLC_CPL);
  FPLC_CPL_SSR := read_cfg_bool(SYSTEMcfg,cfg_ENABLE_CPL,FPLC_CPL_SSR);
  FPLC_ARR     := read_cfg_bool(SYSTEMcfg,cfg_EST_ARR,FPLC_ARR);

  prehlad_arch_fn_cFPL := Limit(read_cfg_word(SYSTEMcfg,cfg_prehlad_arch_fn_cFPL,prehlad_arch_fn_cFPL), 1,24, 0);

  {kontrola_archivu;}

  writeln('Done.')
{$ENDIF}
end. { _FPL }