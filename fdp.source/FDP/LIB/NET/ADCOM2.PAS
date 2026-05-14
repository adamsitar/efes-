(*-------------------------------------------------------------------*)
(* AdCOM2 - funkcie pre komunikaciu s X.25 driverom                  *)
(* (c) Ales Kosice 1993  (pdz)                                       *)
(*-------------------------------------------------------------------*)

{$X+,I-,S-,P-}

(*
   Ovladac ma chyby :

   a) Nedokaze rozoznat, ci mu odpoveda NetBIOS
      IPXu alebo X25... vid server s X25 a IPX
      bez karty a ovladaca X25...

   b) procedure T_AdCOM.CONV_FROM_CPKT(FROM_: X25_PACKET_ARRAY; LEN: U16BIT; var TO_: CALL_DESC);
      ...
         CTMP[i]  := (FROM_[count] shr 4);  {+ ord('0')}
         CTMP[i+1]:= (FROM_[count] and $F); {+ ord('0')}
      ...
      if ((TO_.calld_len + TO_.callg_len) and 1) = 1 then
         begin
           CTMP[i]:= FROM_[count] shr 4 {+ ord('0')};  {catch last one}
           {$IFNDEF LKPR_ACC} inc(count); {$ENDIF} <- inac nastavena komunikacia }
         end;
      ...
*)


unit AdCOM2;


interface


    uses  TypeDef, X25_def, NET_def;


    {$I AdCOM2_c.h}
    {$I AdCOM2_t.h}


    const SW_INTR_X25 {:  byte} = $6A;

          EXCEPTION_CALL_DESC: bool = {$IFDEF EXCEPTION_CALL_DESC} false {$ELSE} true {$ENDIF};
          cfg_EXCEPTION_CALL_DESC   = 'EXCEPTION-CALL-DESC';


    type  P_AdCOM = ^T_AdCOM;
          T_AdCOM = object

            C :  CMDINTFC;

            constructor Init;
            destructor  Done; virtual;

           {private}

           { 1. nizkourovnove fcie pre komunikaciu s NETBIOSom }

            function    _INIT   (LINES: int; INIT_PTR: P_INIT_GLOB):  word;
            function    _PVCINIT(LINE,CHAN:  S16BIT; PVCTABLE: P_PVCINIT):  word;

            function    _GO (LINE : S16BIT): word;
            function    _END(LINE : S16BIT): word;

            function    _GCMD  (DESC_PTR   : P_DATA_DESC): word;
            function    _ACPT  (CALL_PTR   : P_DATA_DESC): word;

            function    _OPEN  (CALL_PTR   : P_DATA_DESC): word;
            function    _WRITE (DATA_PTR   : P_DATA_DESC): word;
            function    _READCH(DATA_PTR   : P_DATA_DESC): word;
            function    _CLOSE (CLEAR_PTR  : P_DATA_DESC): word;

            function    _INT   (DATA_PTR   : P_DATA_DESC)  : word;
            function    _STATUS(STATUS_PTR : P_STATUS_DESC): word;

            function    _RESET (LINE,CHAN: S16BIT): word;
            function    _RESET2I: word;


            function    CONV_TO_CPKT  (FROM_ : CALL_DESC; var TO_: X25_PACKET_ARRAY):  S16BIT;
            procedure   CONV_FROM_CPKT(FROM_ : X25_PACKET_ARRAY; LEN: U16BIT; var TO_: CALL_DESC);

            {
            function    STRUC_TO_PKT  (var FROM_ : SEND_DESC; var TO_ : X25_PACKET_ARRAY): U16BIT;
            procedure   STRUC_FROM_PKT(var FROM_ : X25_PACKET_ARRAY; len: U16BIT; var TO_: SEND_DESC);

            procedure   DECODE_FACILITY(var FAC : U8BIT_109; FAC_LEN : U8BIT; FC : FACILITIES);
            function    ENCODE_FACILITY(var FC  : FACILITIES; var FAC : U8BIT_109) : U8BIT;
            }
          end;



implementation

uses Dos, math;


{$I AdCOM2_1.inc}
{$I AdCOM2_2.inc}
{$I AdCOM2_3.inc} { facilities }

end.