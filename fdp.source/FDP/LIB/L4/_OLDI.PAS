{ -------------------------------------------------
  OLDI
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

 Implementacia FDP/S v protokole OLDI ako koncoveho zariadenia :

  - sprava sa ako DTE,
  - pripojeny len ku jednemu zdroju ( jedna dresa X.25, NSAP, send na pevnu adresu... )
  - NSAP vyhodnocuje z CALL REQUEST
  - po inicializacii je v stave Listen, caka na StartUp
  - po Tr_TimeOute sa snazi inicializovat linku StrtUp-om

  - programovany v sulade s L4444 a podla ICD CAMUS

  - doplnit rad ocakavanych LAMov a kontrolovat v check_OLDI_status

 תתתתתתתתתתתתתתת
  (c) ALES 1996,  Praha, 3-10.3., ...
 תתתתתתתתתתתתתתת
}

{$DEFINE EXTERNAL_NET}

{$I comp.h}


unit _OLDI;


interface


    uses   TypeDef,
           Arrays, IO,
           {$I unit_gr.h},
           {$I unit_oop.h},
           NET_def, X25_def {$IFDEF _X25} {$I _hw_X25.h}, _X25{$ENDIF},
           _L4_def,
           _EXT_def, _EXT, _L4444, _L4_FDP;


    {$I _OLDI_cnst.h}                 { cfg              }
    {$I _OLDI_udf.h}                  { OLDI adresacia   }
    {$I _OLDI_pkt.h}                  { kodovanie spravy }
    {$I _OLDI_events.h}               { stav spojenia    }
    {$I _OLDI_title.h}


    type   P_OLDI = ^O_OLDI;
           O_OLDI = object(O_L4_FDP {,X25})

             {$IFDEF OLDI}
              X25adr_THIS   : TX25name;       { vlastna adresa X.25    }

              X25adr_MASTER : TX25name;       { hlavna adresa X.25     }
              {$IFDEF OLDI_BACKUP}
               X25adr_BACKUP : TX25name;      { zalozna adresa X.25    }
              {$ENDIF}
              X25adr_REMOTE_: TX25name;       { aktivny vzdialeny smer }

              NSAP_THIS     : NSAP;           { vlastna OLDI adresa    }
              NSAP_REMOTE   : NSAP;           { pripojena              }
              UDF           : UserDataField;  { hlavicka z OLDI adries }

              OLDI_X25nodeA : int;
              OLDI_X25nodeB : int;
              OLDI_X25node_ : int;

              stat          : stat_OLDI;      { stav komunikacie OLDI  }

              send_StartUp  : bool;
              switch_Remote : bool;

              {title        : string;}
             {$ENDIF}


             {protected}
              function     read_cfg(_cfg_FN: string): bool; virtual;

              public
              constructor  Init(_p_power : pbool;
                                _cfg_FN, _cfg_OB : string;
                                _lam: int;
                                _pkt_size, _buff_size: word; _is_buff0: bool;
                                _sync_info,_coor_info : pchar;

                                _p_heads_ICAO: Pheads_ICAO; _heads_ICAO : word;
                                _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

                                _p_wr, _p_arch, _p_utc : pointer;
                                _cl_s, _cl_r : byte;
                                _path, _ext : string
                               );
              destructor   Done; virtual;


             {$IFDEF OLDI}
              { prijem a spracovanie
              }
              {protected}
               function     process_data (src: TPKT_SRC; data: pchars; size: word;
                                          var header: string;
                                          var resh,resd: string
                                         ): bool; virtual;

               function     extract_data (data: pchars; size: word;
                                          var C, pSTX,pSTD,pETX: word
                                         ): msSystem;

               procedure    decode_user  (data: pchars; size: word; var header: string);

              { vysielanie a potvrdenie
              }
               function     _send_pkt    (typ: byte; adr: string; data: pchars; size: word): bool; virtual;
               procedure    send_pkt_    (ms: msSystem; adr: string; data: pchars; size: word);
               procedure    send_data    (adr: string; head,cislo,header_data: string;
                                          data: pchars; size: word;
                                          key: string; typ: TNETtyp
                                         ); virtual;

               procedure    LAM_received_pkt (data: pchars; size: word); virtual;

               function     enabled_SVC (adr : TX25name; user_data: pbytes; user_len: byte): bool;
               procedure    disable_SVC;

               function     is_pkt_for_node (from: string; data: pchars; size: word): bool; virtual;

              { kontrola stavu komunikacii podla protokolu OLDI
              }
               procedure    chng_OLDI_status (_stat : stat_OLDI; _btstat: bool);
               procedure    handle_OLDI_event(_event: event_OLDI; _ps: p_stat_OLDI);


              { תתתתתתתתתתתתתתתתתתתתתתת
                hlavna slucka
                תתתתתתתתתתתתתתתתתתתתתתת
              }
               procedure    HandleEvent (var _Event: TEvent); virtual;
               procedure    check0; virtual;

               procedure    _process_test (data: pbytes; dlz: int); virtual;

             {$ENDIF}
            end;


     {$IFDEF OLDI}
      procedure _info_OLDI(x0,y0,x1,y1: int; _DEV_OLDI: P_OLDI); far;

      const  DEV_OLDI : P_OLDI = nil;
     {$ENDIF}


implementation

uses  BIOS, _Check,
      utime, mess, math, str0, sets,
      _MTK_2,
      Archiv{, Hodiny}, Status;


{$I _OLDI_pkt.inc}           { ext fcie                }
{$I _OLDI_.inc}              { init, cfg               }

{$IFDEF OLDI}
  {$I _OLDI_functions.inc}   { ext fcie                }

  {$I _OLDI_check.inc}       { check                   }
  {$I _OLDI_events.inc}      { events, state           }
  {$I _OLDI_decode_pkt.inc}  { pkt: process, decode head & data  }
  {$I _OLDI_send_pkt.inc}    { pkt: send do EXT                  }

procedure O_OLDI._process_test (data: pbytes; dlz: int);
    begin
      stat:= DATA_READY_STATE;
      save_pkt0(pchars(data),dlz);
      {_process_data(pchars(data),dlz);}
    end;

{$ENDIF}

{begin
  nastavenie do cfg suborov Xת25 }
end.