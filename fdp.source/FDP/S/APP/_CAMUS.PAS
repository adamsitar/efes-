{ -------------------------------------------------
  CAMUS - komunikacia a spracovanie udajov
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתת
  (c) ALES 1996,
 תתתתתתתתתתתתתתת
}
(*{$IFNDEF CAMUS_OLDI}
  {$X+,I-,S-,P-,F+,O-}
  {$C FIXED PRELOAD PERMANENT}
{$ENDIF}*)

{$I comp.h}


unit _CAMUS;


interface


    uses   TypeDef,
           IO, {$I unit_gr.h},
           Arrays,
           {$IFDEF UDP}  PCTCPdef, _PCTCP, PCTCP, {$ENDIF}
           {$IFDEF _X25} X25_def, _X25, {$ENDIF} _NET,
           NET_def, Kody,
           {$I unit_oop.h},

           _L4_def, _FDP_def, _FPL_def,
           {$IFDEF FPL4} _FPL4,                {$ENDIF}
           {$IFDEF FPL0} _FPLc, _FPLm, _FPLms, {$ENDIF}
           {$IFDEF PRS}  _PRS,                 {$ENDIF}

           _EXT_def, _EXT, _L4444, _L4_FDP, _OLDI, _CA_def;



   {$IFDEF CONNECT_TO_CAMUS}
    {$I _CA_cnst.h}
    {$I _CA_title.h}
    {$I _CA_object.h}
   {$ENDIF}


implementation

uses  crt, _Check, BIOS, str0, utime, math, sets, coms, mem, mess,
      FIR_def, ZemSur, LDM, Bod_def, Body,
      Vypocty, Archiv,
      Msg, FDP_msg,
      _PLAN, _FPL
      {$IFDEF CONNECT_TO_OPL_EXT}
        , _OPL
      {$ENDIF}
      ;


{$IFDEF CONNECT_TO_CAMUS}

 {$I _CA_test_pkt.inc}
 {$I _CA_.inc}

 {$I _CA_receive_pkt.inc}    { pkt: save, read, receive, process }
 {$I _CA_decode_pkt.inc}     { pkt: process, decode head & data  }
 {$I _CA_send_pkt.inc}       { pkt: send do EXT                  }
 {$I _CA_code_data.inc}
 {$I _CA_functions.inc}

 {$IFDEF FPL4} {$IFDEF FPL0}
   {$I _CA_AMA.doc}          { CPL, EST }
   {$I _CA_AMA.cod}
   {$I _CA_AMA.dec}
 {$ENDIF} {$ENDIF}

 {$I _CA_ASM.cod}

{$ENDIF}

{begin
  CAMUS_init}
end.