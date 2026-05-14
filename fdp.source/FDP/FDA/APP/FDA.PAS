(*-------------------------------------------------------------------*)
(* LETVIS FDP/S                                                      *)
(* (c) Ales Kosice 1989,95 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$IFDEF CONNECT_TO_AFTN}
  {$DEFINE CONNECT_TO_COM}
{$ENDIF}


program FDA;

   uses  {$IFDEF _OVR}
          ovr,
         {$ENDIF}
          TypeDef,
          str0, utime, mess,
          Crt, BIOS, _Check, DOS, COMs, IO, SVGA, _COM,
          {$I unit_ext.h},
          App, Ap;

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


procedure FDA_input__init;
    begin
      init_COMs;
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ FDA                                                      €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
begin
  {$IFDEF COM}
   COM_initialize(@ReadCOM);
   SetIntVec(INT_COM[COMi],@ReadCOM);
  {$ENDIF}
  MainApp:= New(PFDAapp,Init);
  FDA_input__init;
  MainApp^.Run(MainEvent);
  Dispose(MainApp,Done)
end.