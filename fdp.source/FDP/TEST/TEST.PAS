{$I comp.h}

uses ovr, bios, typedef, math, str0,crt,
     _l4_def, _fpl4, _fpl4s, _tlg,
     _aftn, _af_tsga, fdp_ap;

         {$IFDEF _OVR}
          {$I units.ovl}
          {$I net.ovl}
          {$I oop.ovl}

          {$O _MTK_2}

          {$O _L4_def}
          {$O _L4_func}

          {$O _FDP_def}
          {$O _FPL_def}

          {$O _PLAN}
          {$O _STRIP}
          {$O _FPL}


          {$IFDEF PLN}
            {$O _PLN}
          {$ENDIF}

          {$IFDEF FPL4}
            {$O _FPL4}
            {$O _FPL4s}
          {$ENDIF}

          {$IFDEF FPL0}
            {$O _FPLC}
            {$O _FPLM}
            {$O _FPLMv}
            {$O _FPLMs}
          {$ENDIF}

          {$I ext.ovl}
         {$ENDIF}

var  A : PFDPapp;

begin
  {DEV_AFTN:= New(P_AFTN_TSGA,Init(nil));
  Dispose(DEV_AFTN,Done);}

  A:= New(PFDPapp,Init(nil,nil,nil,'1','2'));
  Dispose(A,Done);

end.
