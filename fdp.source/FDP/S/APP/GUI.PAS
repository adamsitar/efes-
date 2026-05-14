(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1995,99 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}


{$I comp.h}

unit GUI;


interface

    uses  TypeDef,
          BIOS,
          {$I unit_gr.h},
          {$I unit_oop.h},
          _PLAN;


    type  P_Smmi = ^O_Smmi;
          O_Smmi = object(TAppGui)

            constructor Init (_Owner: PApp
                              {$IFDEF DATA_WRITTEN_IN_APP};
                                AppDataObject : PPObject;
                                _cl_SEND,_cl_REC: byte
                              {$ENDIF}
                             );

            procedure   Draw; virtual;
            procedure   HandleEvent (var _Event: TEvent); virtual;

            procedure   ReInit (x,y,dx,dy: int); virtual;
          end;


implementation

uses  mouse, keyb, math,
      _L4_def, _FDP_def,
      {$I unit_net.h},
      {$I unit_fdp.h}
      Hodiny, Status, MapyDef;

{$I mmi_s.inc}

end.