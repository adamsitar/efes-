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


    const (*tab_FPL4prea : bool = {$IFDEF DEBUG} true {$ELSE} false {$ENDIF};*)
          tab_FPL4prop : bool = true;
          tab_FPL4coor : bool = true;


          {$IFDEF PROCESS_FPL4}
    var     {FPL4prea,}FPL4prop : PScrollApp_FDP;
            FPL4coor : PScrollApp;

            {_tab_FPL4prea,}
            _tab_FPL4prop,
            _tab_FPL4coor  : bool;
          {$ENDIF}


    type  P_FDAmmi = ^O_FDAmmi;
          O_FDAmmi = object(TAppGui)

            constructor Init (_Owner: PApp
                              {$IFDEF DATA_WRITTEN_IN_APP};
                                AppDataObject : PPObject;
                                _cl_SEND,_cl_REC: byte
                              {$ENDIF}
                             );

            procedure   Draw; virtual;
            procedure   Idle (var _Event: TEvent); virtual;
            procedure   HandleEvent (var _Event: TEvent); virtual;

            procedure   ReInit (x,y,dx,dy: int); virtual;
          end;


implementation

uses  mouse, keyb, math,
      _L4_def, _FDP_def,
      {$I unit_net.h},
      {$I unit_fdp.h}
      Hodiny, Status, MapyDef;

{$I mmi_fpl4.inc}
{$I mmi_fda.inc}

end.