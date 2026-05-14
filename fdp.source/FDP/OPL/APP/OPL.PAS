(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.9                                              *)
(* (c) Ales Kosice 1993,99 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}


program OPL;

   uses  {$IFDEF _OVR}
          ovr,
         {$ENDIF}
          TypeDef,
          str0, utime, mess,
          Crt, BIOS, _Check, DOS, COMs, IO, SVGA, _COM,
          {$I unit_ext.h},

          App, Ap {$IFDEF DEMO}, Demo {$ENDIF};

         {$IFDEF _OVR}
          {$I units.ovl}
          {$I oop.ovl}
          {$I net.ovl}
          {$I fdp.ovl}
          {$I ext.ovl}
         {$ENDIF}


{IFDEF CONNECT_TO_COM}
  {$I ext_async.inc}
{ENDIF}

{$IFDEF COM}
  {$I _com.int}
{$ENDIF}


begin
  {$IFDEF COM}
   COM_initialize(@ReadCOM);
   SetIntVec(INT_COM[COMi],@ReadCOM);
  {$ENDIF}
  OPLapp:= New(POPLapp,Init);
  init_COMs;
  OPLapp^.Run(MainEvent);
  Dispose(OPLapp,Done)
end.