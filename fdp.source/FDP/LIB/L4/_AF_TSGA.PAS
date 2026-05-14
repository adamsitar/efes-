{ -------------------------------------------------
  AFTN interface pre LETVIS/FDP
  pre spracovanie ICAO sprav
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתת
  (c) ALES 1996,
 תתתתתתתתתתתתתתת

 Vid poznamky ku rieseniu pod "end."

}

{$DEFINE EXTERNAL_NET}

{$I comp.h}

unit _AF_TSGA;


interface


    uses   typedef,
           keyb, io, coms,
           {$I unit_gr.h},
           {$I unit_net.h},
           Arrays, {$I unit_oop.h},
           _L4_def, _MTK_2,
           _EXT_def, _EXT, _L4444, _L4_FDP, _AFTN;


    {$I _af_ts_cnst.h}


    type   P_AFTN_TSGA = ^O_AFTN_TSGA;
           O_AFTN_TSGA = object(O_AFTN)

             soh1_PLN,soh2_PLN,eoh_PLN : string;
             semaphor_pln : bool;

             txt_TEST : string;

             constructor Init;
             function    read_cfg (_cfg_FN: string): bool; virtual;
             procedure   initialize_STATUS (_draw: bool); virtual;

             procedure   HandleEvent (var _Event: TEvent); virtual;
             procedure   check; virtual;

             function    decode_data (data: pchars; size: word;
                                      header: string;
                                      var head: string;
                                      var res: string
                                     ): bool; virtual;


            {$IFDEF SYNCHRONIZE_EXT}
             function    decode_NETpkt (var pkt: TNETpkt): bool; virtual;
             procedure   decode_pkt_spr_pln (var pkt: TNETpkt);
            {$ENDIF}

             function    _process_TLG_TEST (data: pchars; size: word): bool; virtual;
             function    process_data_TLG  (src: TPKT_SRC; data: pchars; size: word; var res: string): bool; virtual;


            { PLN
            }
            {$IFDEF PLN}
             function    _is_PLN (data: pchars; size: word; var riadkov,riadok: int; var date : TDate; var res: string): bool;
             function    _decode_PLN  (data: pchars; size: word; riadkov,riadok: int; date: TDate; var res: string): bool;
             function    _process_PLN (src: TPKT_SRC; data: pchars; size: word; var res: string): bool;

             procedure   _save_PLN (data: pchars; size: word; tit,fn: string; from: TNETadr);
             procedure   _read_PLN;

             procedure   manage_PLN;
            {$ENDIF}

           end;


implementation

uses  DOS, BIOS, _Check,
      str0, mess, math, sets, utime, prnt, msg, db,
      FIR_def, Bod_def,
      FDP_msg, _FDP_def, _FPL_def, _FPL4, _PLN,
      Archiv;


 {$I _af_ts_.inc}             { inicializacia    }
 {$I _af_ts_decode_pkt.inc}   { pkt: decode_data }
 {$I _af_ts_tlg.inc}          { telegramy        }

 {$I _af_ts_net.inc}          { synchronizacia   }

 {$I _af_ts_edit.inc}         { editacia         }
 {$I _af_ts_pln.inc}          { spracovanie pln  }


end.