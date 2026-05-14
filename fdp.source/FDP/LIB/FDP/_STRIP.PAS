(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL,EDD                                              *)
(* (c) Ales Kosice 1996    (ab)                                      *)
(* PLANy - implementacia pre EDD                                     *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}
{$X+,I-,S-,P-,B-}


unit _STRIP;


interface


    uses   TypeDef,
           DB,
           Arrays, Events, Objects, Scroll,
           {$I unit_net.h},
           FIR_def, Bod_def,
           _L4_def, _FDP_def, FDP_scrl,
           _PLAN;

    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                                                          €
    € STRIP                                                    €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    {$I _strip_title.h}
    {$I _strip_cnst.h}
    {$I _strip_object.h}
    {$I _strip_func.h}       { fcie   }



implementation

uses  mem, str0, math, prnt,
      {$I unit_gr.h},
      Dialog, App, CM;

{$I _strip0.inc}  { comp_... }
{$I _strip5.inc}  { objekt   }

end.