{ -------------------------------------------------
  ASOC - komunikacia s ...
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתת
  (c) ALES 1998
 תתתתתתתתתתתתתתת
}

{$DEFINE EXTERNAL_NET}

{$I comp.h}


unit _ASOC;


interface

    uses   TypeDef, IO,
           {$I unit_gr.h},
           {$I unit_oop.h},
           NET_def, Kody,
           _L4_def, _MTK_2, _EXT, _L4444, _L4_FDP, _OLDI,
           _FDP_def, _FPL_def, _FPL,
           Archiv

           {$IFDEF FPL4}, _FPL4                {$ENDIF}
           {$IFDEF FPL0}, _FPLc, _FPLm, _FPLms {$ENDIF}
           {$IFDEF PRS},  _PRS                 {$ENDIF}
           {$IFDEF FUA},  _FUA                 {$ENDIF}
           ;



    {$I _AS_cnst.h}


    const  ASOC_coor_info = hd_CPL+', '+hd_EST+', '+inf_FPLC
                             { IFNDEF LZ}
                               +', '+inf_FPLM+', '+inf_FPLO
                             { ENDIF};

           power_ASOC : bool = true;


    type   PO_ASOC = ^O_ASOC;
           O_ASOC = object(O_L4_FDP)

             NODE   : int;

             ADR_I  : string[_MTK_ADR_hi];
             ADR_O  : string[_MTK_ADR_hi];

             CHNL_I : string[_MTK_CHNL];
             CHNL_O : string[_MTK_CHNL];

             IA5        : bool;
             ITA2_ASCII : bool;
             ITA2_BIN   : bool;
             ITA2_BITS  : byte;


             constructor  Init;

             function     read_cfg  (_cfg_FN: string): bool; virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               hlavna slucka
               תתתתתתתתתתתתתתתתתתתתתתת
             } procedure    HandleEvent (var _Event: TEvent); virtual;


             { תתתתתתתתתתתתתתתתתתתתתתת
               vysielanie a potvrdenie
               תתתתתתתתתתתתתתתתתתתתתתת
             } function     _send_pkt   (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
               procedure    send_data   (adr: string; head,cislo,header_data: string;
                                         data: pchars; size: word;
                                         key: string; typ: TNETtyp
                                        ); virtual;



             { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                koordinacia medzi roznymi systemami FDP
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             } {$IFDEF FPL0}
                procedure  _send_message_FPLC (head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL); virtual;

                {$IFNDEF FPLM_DISABLED}
                 function  _code_FPLm(var FPLm: DmFPL; var FPL: DFPL4): bool; virtual;
                {$ENDIF}

                function _code_ACT (var FPL: DFPL4): pchar; virtual;
               {$ENDIF}

           end;


    const  DEV_ASOC: PO_ASOC = nil;



implementation

uses  _Check, BIOS, COMS, str0, utime, math, sets, mess, keyb,
      {$IFDEF _X25} X25_def, _X25, {$ENDIF}
      _NET, Lists,
      FIR_def, Bod_def, Body, ZemSur, LDM, Vypocty,
      Msg, FDP_msg,
      _L4_func,
      _PLAN;


{$I _AS_test_pkt.inc}

{$I _AS_.inc}
{ I _AS_check.inc}          { check                             }
{ I _AS_decode_pkt.inc}     { pkt: process, decode head & data  }
{$I _AS_functions.inc}
{$I _AS_send_pkt.inc}       { pkt: send do EXT                  }

{$IFDEF FPL4} {$IFDEF FPL0}
  {$I _AS_ICAO.cod}

  { I _AS_AMA.doc}          { CPL, EST                          }
  { I _AS_AMA.dec}
  { I _AS_AMA.cod}

  {$I _AS_OLDI.cod}
{$ENDIF} {$ENDIF}


end.
