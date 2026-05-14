(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 1.0                                              *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(* Definicie povelov pre aplikaciu OPL                               *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit CM;


interface


    uses    TypeDef;


          {
          ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
          €                       €
          € FDP                   €
          €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
          }

    const   cmSECTOR_CHG          = 5200;

            {$I cm_plan.h}    {  6000 -  9999 }
            {$I cm_l4.h}      { 10000 - 14999 }
            {$I cm_data.h}    { 15000 - 39999 }
            {$I cm_ext.h}     { 40000 - 49999 }
            {$I cm_gui.h}     { 50000 - 55999 }


implementation

end.