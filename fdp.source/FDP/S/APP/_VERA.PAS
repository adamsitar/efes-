{ -------------------------------------------------
  ASOC - komunikacia s ...
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתת
  (c) ALES 1998
 תתתתתתתתתתתתתתת
}

{$I comp.h}


unit _VERA;


interface

    uses   TypeDef,
           Arrays,
           IO,
           NET_def, Kody,
           {$I unit_gr.h},
           {$I unit_oop.h},
           _L4_def, _FDP_def, _FPL_def,
           {$IFDEF FPL0} _FPLc, _FPLm, {$ENDIF} _FPL4,
           {$IFDEF UDP}  PCTCPdef, _PCTCP, PCTCP, {$ENDIF}
           _MTK_2, _EXT, _L4444, _L4_FDP;



    {$I _VR_cnst.h}


    const  VERA_coor_info = hd_CPL+', '+hd_EST+', '+inf_FPLC+', '+inf_FPLM+', '+inf_FPLO;
           power_VERA : bool = true;


    type   PO_VERA = ^O_VERA;
           O_VERA = object(O_L4_FDP)

             {$IFDEF UDP}
              UDPpkt  : PVERApkt;
             {$ENDIF}

             constructor  Init;
             destructor   Done; virtual;

             function     read_cfg  (_cfg_FN: string): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               hlavna slucka
               תתתתתתתתתתתתתתתתתתתתתתת
             } procedure    HandleEvent (var _Event: TEvent); virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               vysielanie a potvrdenie
               תתתתתתתתתתתתתתתתתתתתתתת
             } function     _send_pkt (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
               procedure    send_data (adr: string; head,cislo,header_data: string;
                                       data: pchars; size: word;
                                       key: string; typ: TNETtyp
                                      ); virtual;


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
               kodovanie sprav a odoslanie
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             }
             {$IFDEF FPL4} {$IFDEF FPL0}
              function _code_bod  (kod: string; h,m: byte; vys: word; vys_,vys_a: char;
                                   var vysp: word; var vysp_,vysp_a: char
                                  ): string; virtual;
             { AMA
             }
              function  _code_EST (var FPL: DFPL4): pchar; virtual;
                function _code_ESTc  (var FPLc: DcFPL; var FPL: DFPL4): bool; virtual;
                function _code_ESTm  (var FPLm: DmFPL; var FPL: DFPL4): bool; virtual;
             {$ENDIF} {$ENDIF}


             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                koordinacia medzi roznymi systemami FDP
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             } {$IFDEF FPL0}
                procedure  _send_message_FPLC (head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL); virtual;
                procedure  _send_message_FPLM (head: Thead_ICAO; zmeneny: bool; var FPL: DmFPL); virtual;
               {$ENDIF}

           end;

    const  DEV_VERA: PO_VERA = nil;


implementation

uses  _Check, BIOS, COMS, mem, str0, utime, math, sets, mess, keyb, crt,
      _NET,
      FIR_def, ZemSur, LDM, Bod_def, Body,
      Vypocty, Archiv,
      Msg, FDP_msg;


{$I _VR_.inc}
{$I _VR_functions.inc}
{$I _VR_send_pkt.inc}

{$IFDEF FPL4} {$IFDEF FPL0}
  {$I _VR_AMA.doc}
  {$I _VR_AMA.cod}
{$ENDIF} {$ENDIF}


end.
