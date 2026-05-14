    type    Tdraw_trgt      = procedure(plan: pointer; x,y: int; var sur: Tsur; maz: bool);
            TPozFunc_prvb   = function (plan: pointer; cas: real; var zmena: bool): Tpoz;
            TProc_ps        = procedure(plan: pointer; s: string);

    type    PindPLAN = ^TindPLAN;
            TindPLAN = record
              iPLAN : PPLAN;    { smernik na pole TPLAN }
              ind   : int       { index v poli iFPL     }
            end;

    const   MAX_indPLAN = MAX_ARRAY_SIZE div SizeOf(PindPLAN);

    type    PAindPLAN = ^TAindPLAN;
            TAindPLAN = array[0..MAX_indPLAN-1] of PindPLAN;
