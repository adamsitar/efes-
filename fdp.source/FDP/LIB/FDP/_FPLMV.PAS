(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1999                                              *)
(* FPLM - vypocty                                                    *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}


{$X+,I-,S-,P-}


unit _FPLMv;


interface


    uses    TypeDef,
            _L4_def, _FDP_def,
            FDP_edit,
            _FPLM;


    {$IFDEF FPL0}
     {$IFNDEF FPLM_DISABLED}
      function regularita_mFPL(FPL,FPLp: PDmFPL;
                               zmenena_trat : bool;
                               staticka,dynamicka: bool;
                               var res: string; var ires: int;
                               form: PFDP_AForm
                              ): bool;

     {$ENDIF}

    {$ENDIF}


implementation

uses  str0, io, db, bios, utime, msg,
      Bod_def, Body,
      Dialog, Lists,
      {$I unit_map.h},
      Sector
      {$IFDEF PRS}, _PRS {$ENDIF}
      ;


{$IFDEF FPL0}
 {$IFNDEF FPLM_DISABLED}
  {$I _FPLm_6.vyp}     { regularita }
 {$ENDIF}

{$ENDIF}
end. { _FPLMv }