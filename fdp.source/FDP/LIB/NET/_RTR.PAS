(*-------------------------------------------------------------------*)
(* LETVIS FDP - ROUTER 3.0, pokec je dole ...                        *)
(* (c) Ales Kosice 1993,95  (ab)                                     *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_RTR.h}

{ O-}

{
  Potvrdzovanie prechodu sprav by mal zabezpecit nizkourovnovy
  protokol prenosu. (IPX mi to da, od X25 zatial neviem a ROUTER
  to este nerobi. Preto sa to robi este na vyssej urovni - ackXXX ...


   Funguju tu 3 sposoby komunikacie :
   ----------------------------------

   1. RTR - cez router: prenos cez niekolko sieti

   2. RTI - imitacia komunikacie cez RTR v jednej LAN
            ( program imituje RTR )

   3. RTB - cez router a bridge prepojenie dvoch fyzicky heterogennych sieti.

            Pocitac v sieti RTR, ktory adresuje pocitac v inej sieti,
            posle zakodovany paket na adresu BRIDGE (premostujuceho
            pocitaca do inej siete, ktory je zapojeny v sieti RTR).
            Kodovanie takeho paketu je
                      - code_NETpkt_to_RTRpkt
                      - na koniec dat pripoji adresu adresata (ako RTR address)
                      - posle na dresu BRIDGE.

            BRIDGE prijem paket spr_RTB
                      - rozkoduje do NETpaketu (s uvazenim adresy na konci)
                      - posle na ziadany smer

            Pocitac v sieti s BRIDGE adresuje siet RTR.
                      - NEtpaket pride na BRIDGE
                      - zisti, ze adresa patri do RTR siete
                      - zakoduje RTB paket
                      - odosle


            Ak oznacujem uzol v sieti BRIDGE pseudoadresou, usetrim na rozsahu
            prenasanych dat, ale nemozem adresovat vsetky stanice.
             - poslednych TRTR byte je < $00 => adresa, inak je to plna adresa...

}


unit _RTR;


interface


    uses  TypeDef,
          NET_def, RTR_def, IPX_def, PCTCPdef;


    type  TRTRprotocol = (rpRTR,rpRTI,rpRTB,rpRT_);


    function  NETadr_rtr(adr: TNETadr): TRTRadr;

    function  code_NETpkt_to_RTRpkt (const Np : TNETpkt;
                                     var   Rp : TRTRpkt_bin;
                                     distribute : PBplan_rec;
                                     protocol   : TRTRprotocol;
                                     var whole  : bool
                                    ): word; far;

    function  decode_RTRpkt_to_NETpkt (const Rp : TRTRpkt_bin; var Np: TNETpkt; var err: bool): bool; far;

    {$IFDEF IPX}
     function  decode_ipxRTRpkt_to_NETpkt (const Lp: TIPXdpkt; var Np: TNETpkt): bool; far;
    {$ENDIF}

    type      Tdecode_SIMpkt = function (data: pbytes; size: word; fhost: in_name): bool;
              Pdecode_SIMpkt = ^Tdecode_SIMpkt;
    function  decode_SIMpkt (data: pbytes; size: word; fhost: in_name): bool; far;
    const     p_decode_SIMpkt : Pdecode_SIMpkt = @decode_SIMpkt;


    function  RTRsend (const Np: TNETpkt): int;
    function  RTBsend (const Np: TNETpkt): int;
    {function  RTRdistribute (const Np: TNETpkt; distribute: PBplan_rec): bool;}



implementation

uses  BIOS, IO,
      str0, mess, math, mem,
      Kody, NET_utc, _IPX {$IFDEF PCTCP}, PCTCP {, _PCTCP} {$ENDIF}
      ;

{
  Pri kodovani NETpktu do RTRpaketu nie su polozky pre
  sekvencne cislo a kod spravy. Tieto sa preto vsunu do
  datovej casti, cim zmensia velkost balika o 4 byte.
  Dalsi ubytok - kodovanim adries...
               - index/cislo paketu

  const TRTR_data_head = 1(kod) + sizeof(TNETpkt.head.typ) + sizeof(TNETpkt.head.cis)
}


{ ------------------------------------------
   NETpaket -> RTRpaket
  ------------------------------------------

  Zakodovanie do Rp podla typu spravy;
    - odhryznut adresy z paketu ...
    - parameter send urcuje na ktory uzol NODEs^[i].adr sa ma odoslat pkt,
    - vrati dlzku spravy pre ipx
    - detekuje skratenie datovej casti paketu.

  Adresy:
    - pri odoslani RTR: adr sa zada cielova adresa
                   RTI: adr adresa odosielatela (imituje router)
    -
}

{ IFDEF RTR}

  {$I rtr.inc}

  const RTR_cis: word = 0;

  {$IFDEF RTR1}  { I rtr.cod}  { snad sa uz nepouziva; ale nerusit ...  }
  {$ELSE}        {$I rtr2.cod} { ine kodovanie RTB, RT_ }
  {$ENDIF}

  {$IFDEF IPX}   {$I rtri.cod} { ipx do net pkt}          {$ENDIF}

  {$I rtr3.inc}
{ ENDIF}

 function  decode_SIMpkt (data: pbytes; size: word; fhost: in_name): bool;
    begin
      decode_SIMpkt:= false
    end;

end.
