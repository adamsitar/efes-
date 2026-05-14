(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.0                                              *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(* Meteor                                                            *)
(*-------------------------------------------------------------------*)
{ doplnit priznaky do sprav _, co mi posiela tomas N,E,...}

{$I comp.h}
{$I comp_fdp.h}


unit _MET;


interface


    uses   TypeDef, sets, DB,
           {$I unit_gr.h},
           {$I unit_net.h},  _rtr, PCTCPdef,pctcp,_pctcp,
           {$I unit_oop.h},
           _FDP_def;


   {$IFDEF MET}

    {$I _MET_title.h}
    {$I _MET_data.h}
    {$I _MET_func.h}

    {$I _MRL_cnst.h}

    function _handle_event_MET (var _Event: TEvent; O: PObject; MET: pointer): bool;

   {$ENDIF}


implementation

uses  BIOS, _Check, IO, DOS,
      keyb, mouse, str0, mess, utime, math, sort, prnt, msg,
      FDP_scrl, Archiv, Status;


{$IFDEF MET}

 const    p_syn_dbscroller : PScrollDB_FDP = nil;

 {$I _MET.cod}
 {$I _MET.inc}    { save, send    }
 { I _MET.vyp}
 {$I _MET.drw}
 {$I _MET.prn}

 {$I _MRL.inc}    { save, send    }

 {$I _MET2.inc}
 {$I _MET4a.inc}
 {$I _MET4.inc}

 {$I _MET_handle.inc}

 {$I _MET_rec.inc}

{$ENDIF}

end.