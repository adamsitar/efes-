(*-------------------------------------------------------------------*)
(* LETVIS FDP - typy sprav OPL                                       *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ Maximalne pouzivat kody do 10000 - kvoli prenose v sieti RTR,
  tam sa transformuju o 20000 vyssie.
  Komunikacia s RDP od 50000 bez transformacie.
}

unit  Kody;


interface

    uses  TypeDef;


    const   ZAC_SPR = #2;
            KON_SPR = #3;
            ODD_SPR = #4;

    const   setLET_1_1 = [ZAC_SPR,KON_SPR,ODD_SPR];


    {$I _pkt_0type.h}
    {$I _pkt_type.h}
    {$I _pkt_info.h}


    function  code_0type(typ: word): word;


implementation

function  code_0type(typ: word): word;
   begin
     code_0type:= typ;

     case typ of
       0              : ;

      {$IFDEF DATA_BIN}
       spr_ACCEPT     : code_0type:= spr0_RDP_A;
       spr_UNACCEPT   : code_0type:= spr0_RDP_UA;
       spr_HANDOVER   : code_0type:= spr0_RDP_H;
       spr_UNHANDOVER : code_0type:= spr0_RDP_UH;

       spr_EST_CNL    : code_0type:= spr0_RDP_EST_DEL;
       spr_PRS_CNL    : code_0type:= spr0_RDP_PRS_DEL;
      {$ENDIF}
     end
   end;

end.