(*-------------------------------------------------------------------*)
(* LETVIS FDP - EDD 3.0                                              *)
(* (c) Ales Kosice 1994,95  (ab)                                     *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$D+,L+}    { local debug info so TD can source-step this module }

program EDD;


  uses  {$IFDEF _OVR} ovr, {$ENDIF}
        DOS, BIOS, Crt,
        utime, mess,
        {$IFDEF DEMO} demo, {$ENDIF}
        {$IFDEF COM}  COMs, _COM, {$ENDIF}
        App, Ap;

        {$IFDEF _OVR}
         {$I units.ovl}
         {$I net.ovl}
         {$I oop.ovl}
         {$I fdp.ovl}
         {$I ext.ovl}
        {$ENDIF}


{$IFDEF COM}
  {$I _com.int}
{$ENDIF}


begin
  {$IFDEF COM}
    COM_initialize(@ReadCOM);
    SetIntVec(INT_COM[COMi],@ReadCOM);
  {$ENDIF}
  MainApp:= New(PEDDapp,Init);
  MainApp^.Run(MainEvent);
  Dispose(MainApp,Done)
end.
