{ ---------------------------------------------------------------
  L4444
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

 תתתתתתתתתתתתתתתתתתתתתתתתת
  (c) ALES 1996,  Kosice
 תתתתתתתתתתתתתתתתתתתתתתתתת

  Dodatok 3 - obsah a formy sprav letovych prevadzkovych sluzieb

   - implementovane funkcie pre spracovanie sprav tykajucich sa FPL

   - spracovanie konkretnej spravy vykona funkcia "decode_XXX". Je virtualna
     preto, lebo nejaky smer moze mat upravene kodovanie sprav (vid ICAO, OPL).
     Ak spracovanie prebehlo uspesne, vrati true a na zaklade toho je odoslany LAM.
     Spravidla vola funkcie "_decode_XXX" pre naplnenie poli L4FPL
     a _process_XXX ktora spracuje dekodovanu spravu a rozhodne o jej
     LAMovani. Preto je mnoho funkcii zatial prazdnych...

   - funkcie zacinajuce podciarovnikmi "_" su virtualne, mozu alebo musia byt dodefinovane v dedicovi

#  - zatial sa z pola _22 uvazuju vsetky zmeny ako nahrada, nie ako doplnenie...


   MODUL ESTE NEFUNGUJE PRESNE PODLA Doc.4444,
   JE OVPLYVNENY ROZNYMI PROTOKLOMI,
   PODLA KTORYCH SA VYVIJAL

}


{$DEFINE EXTERNAL_NET}

{$I comp.h}


unit _L4444;


interface


    uses   TypeDef,
           Objects,
           NET_def, Kody,
           _L4_def, _FDP_def,
           _FPL4,
           _EXT_def, _EXT;


    type   PO_L4444 = ^O_L4444;
           O_L4444  = object(O_EXT)

             send_empty_l4_arr: bool;

             constructor Init ( _Owner  : PObject;
                                _p_power : pbool;
                                _cfg_FN : string;

                              { nastavenia : potvrdenia, linka
                              }
                                _lam: int; _async : bool;

                              { spracovavany paket
                              }
                                _ipkt_size, _ibuff_size: word; _is_ibuff0: bool;
                                _pbuff_size: word;

                              { synchronizacia/zalohovanie
                              }
                                _spr_send_ext,
                                _spr_new,_spr_prd,_spr_ed,_spr_del,
                                _spr_err,_spr_err_ed,_spr_err_del,
                                _spr_items_del,_spr_item_del : TNETtyp;
                                _sync_info,_coor_info : pchar;

                              { spracovavane spravy
                              }
                                _p_heads_ICAO: Pheads_ICAO; _heads_ICAO: word;
                                _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

                              { archivacne premenne
                              }
                               _p_wr, _p_arch, _p_utc : pointer;
                               _cl_s, _cl_r : byte;
                               _pathSTREAM,_pathERR, _ext : string
                              );

             function  read_cfg  (_cfg_FN: string): bool; virtual;


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              dekodovanie sprav
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              dekodovanie FPL4 a jeho spracovanie
              Funkcie pre predefinovanie, _process_XXX takmer vzdy
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }


             {function     decode_header (data: pchars; size: word;
                                         zac,kon: word;
                                         var header: string;
                                         var res: string;
                                         decode: bool
                                        ): bool; virtual;
             }

             function     enabled_head (src: TPKT_SRC;
                                        data: pchars; size: word;
                                        head: string;
                                        var res: string
                                       ): bool;  virtual;

            {$IFDEF FPL4}

            { ICAO
            }
             function    decode_ALR   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_ALR  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_ALR (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_RCF   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_RCF  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_RCF (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_SPL   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_FPL   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_FPL  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_FPL (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_CHG   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               function  _decode__22  (var FPL: DFPL4; var res: string): bool;
               procedure _decode_CHG  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_CHG (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_CNL   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_CNL  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_CNL (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_DLA   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_DLA  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_DLA (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;



            { OLDI
            }
             function    decode_ABI   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_ABI  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_ABI (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_ACT   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_ACT  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_ACT (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_PAC   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_REV   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;


            { AMA
            }
             function    decode_DEP   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_DEP  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_DEP (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_ARR   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_ARR  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_ARR (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_CPL   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_CPL  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_CPL (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;

             function    decode_EST   (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;
               procedure _decode_EST  (data: pchars; size: word; var FPL: DFPL4; var res: string); virtual;
               function  _process_EST (data: pchars; size: word; var FPL: DFPL4; var res: string): bool; virtual;



            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              kodovanie sprav FPL a odoslanie
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
            { ICAO
            }
             function    send_ALR  (var FPL: DFPL4; key: string; typ: TNETtyp; adr: string): bool; virtual;
               function  _code_ALR (var FPL: DFPL4): pchar; virtual;

             function    send_FPL  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_FPL (var FPL: DFPL4): pchar; virtual;

             function    send_CHG  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_CHG (var FPL: DFPL4): pchar; virtual;

             function    send_DLA  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_DLA (var FPL: DFPL4): pchar; virtual;

             function    send_CNL  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_CNL (var FPL: DFPL4): pchar; virtual;


            { OLDI
            }
             function    send_ACT  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_ACT (var FPL: DFPL4): pchar; virtual;


            { AMA
            }
             function    send_DEP  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_DEP (var FPL: DFPL4): pchar; virtual;

             function    send_ARR  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_ARR (var FPL: DFPL4): pchar; virtual;

             function    send_CPL  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_CPL (var FPL: DFPL4): pchar; virtual;

             function    send_EST  (var FPL: DFPL4; key: string; typ: TNETtyp): bool;  virtual;
               function  _code_EST (var FPL: DFPL4): pchar; virtual;
            { ENDIF}


            { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
              dekodovanie EET, postupnosti bodov FPL
              תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            }
             {function  _decode_FPL4 (var FPL: DFPL4; var res: string): bool;
              function  _decode_STRIP (FPL: DFPL4; var STRIP: TSTRIP; var res: string): bool;}


            {$ENDIF}
           end;


    function  code_ICAO_pkt (soh, eot, header: string;
                             data: pchars; size: word;
                             var pkt: pchars; var dlz: word
                            ): bool;


implementation

uses  BIOS, IO,
      math, str0, utime, sets, keyb,
      {$I unit_gr.h},
      Lists, Dialog,
      FIR_def, Bod_def, Body,
      FDP_msg, _FPL_def,
      _MTK_2
      {$IFDEF RPL}, _RPL  {$ENDIF}
      ;


{$I _L4_doc.inc}
{$I _L4_pkt.inc}

{$I _L4_.inc}             { cfg, process }
{$I _L4_decode_pkt.inc}   { pkt: process, decode head & data  }


{$IFDEF FPL4}
 {$I _L4_ICAO.dec}        { FPL, CHG, CHG, DLA            }
 {$I _L4_ICAO.cod}

 {$I _L4_OLDI.dec}        { ABI, ACT, PAC, REV            }
 {$I _L4_OLDI.cod}

 {$I _L4_AMA.doc}         { CPL, EST, DEP, ARR            }
 {$I _L4_AMA.cod}
 {$I _L4_AMA.dec}
{$ENDIF}
end.
