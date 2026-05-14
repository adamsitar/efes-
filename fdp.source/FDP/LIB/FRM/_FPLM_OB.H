     {$IFDEF FDP_OPL}
       type  T_TRAT4 = record
                 FPL : PDmFPL;
                 TRAT_PRED, OB, SPEC, TRAT_PO : string
             end;
       function   formular_OB(var Trat: T_TRAT4; vojensky_plan  : bool;
                              x,y: int; _tit: string; _info, _hlpXXX: Pchar
                             ): bool;
     {$ENDIF}
