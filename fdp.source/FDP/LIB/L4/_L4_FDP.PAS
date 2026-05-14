{ ---------------------------------------------------------------
  L4444 - implementacia funkcii pre struktury FDP,
          (aby sa zvladli rozne datove typy pre FPLm a FPLc)

          v tomto module je zakazane menit kodovanie,
                            --------
          pretoze ho vyuzivaju dedici
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

 תתתתתתתתתתתתתתתתתתתתתתתתת
  (c) ALES 1996,  Kosice
 תתתתתתתתתתתתתתתתתתתתתתתתת
}

{$DEFINE EXTERNAL_NET}

{$I comp.h}

unit _L4_FDP;

interface


    uses   TypeDef,
           {$I unit_gr.h},
           {$I unit_oop.h},
           NET_def, Kody,
           FIR_def, Bod_def, Body, ZemSur, LDM, Vypocty,
           _L4_def, _MTK_2,
           _EXT, _L4444,
           _FDP_def, _FPL_def, _FPL,
           Archiv

           {$IFDEF FPL4}, _FPL4                {$ENDIF}
           {$IFDEF FPL0}, _FPLc, _FPLm, _FPLms {$ENDIF}
           {$IFDEF PRS},  _PRS                 {$ENDIF}
           {$IFDEF FUA},  _FUA                 {$ENDIF}
           ;


    const  cfg_error_fda             = 'SEND ERROR TO FDA';
           cfg_nolam_fda             = 'SEND NOLAM TO FDA';
           cfg_oat_exclude           = 'OAT/GAT EXCLUDE';
           cfg_exclude_uknown_points = 'EXCLUDE-UNKNOWN-POINTS';


    {$I _L4F_object.h}


implementation

uses  BIOS, IO, _check, keyb, math, str0, utime, sets,
      Lists,
      _NET,
      _L4_func;


{$I _L4F_.inc}
{$I _L4F_code_data.inc}
{$I _L4F_functions.inc}
{$I _L4F_lam.inc}
{$I _L4F_err.inc}

{$IFDEF FPL4} {$IFDEF FPL0}
 {$I _L4F_ICAO.doc}  { FPL, CHG, CHG, DLA  }
 {$I _L4F_ICAO.cod}
 {$I _L4F_ICAO.dec}

 {$I _L4F_OLDI.cod}  { ABI, ACT, PAC, REV  }

 {$I _L4F_AMA.doc}   { CPL, EST!, DEP, ARR }
 {$I _L4F_AMA.cod}
 {$I _L4F_AMA.dec}
{$ENDIF} {$ENDIF}

{$IFDEF PRS}
 {$I _L4F_ASM.cod}
{$ENDIF}


begin
  LDM_PREFIX:= MIL_POINT
end.