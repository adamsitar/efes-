(*-------------------------------------------------------------------*)
(* LETVIS FDP - definicia dat pre siet                               *)
(* 1993,95                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ Rozne protokoly + dlhy/kratky protokol, nastavuje sa konfiguraciou,
  pre noivise fdp upravit format

  Zalohovanie SERVER a BSERVER:
   Inym (lepsim) riesenim by bolo sirenie fyzickej adresy
   aktivneho servera. Zatial neodladene.
   Teraz treba posielat i na hlavny i na zalozny server
   (najlepsie "distribute").

}

unit NET_def;


interface


     uses   TypeDef,
            IO, {$I unit_gr.h},
            AStream, Objects,
            PCTCPdef, RTR_def;


     const  NETcfg    = 'users'+ext_ini;
            NODE_INFO = true;

            net_flag_NIL  = 0;
            net_flag_SEND = 1;    { posle i ked posledna sprava nepresla }


     type   TEthernetAdr = array[0..5] of byte;     { Adresa Ethernetu }


     {$I net_def0.h}   { size of TNETdata  }
     {$I net_def1.h}   { TNETpkt, TNETBpkt }

     const  { maximalna dlzka paketu,
              je dana minimalnou dlzkou pola dat
              z prave pouzivanych protokolov
            }
            size_of_NETdata : word =   size_of_NETpkt
                                     - 2*sizeof(TNETadr)
                                     - sizeof(TNETpkt_head)
                                     - 20;

     {$I net_def3.h}   { cfg : typ stanic, odosielana inf }
     {$I net_def4.h}   { uzly                             }

     {$I net_def7.h}   { archive               }

     {$I net_def8.h}   { nastavenia globalnie  }
     {$I net_def9.h}   { kody vysledkov        }


    { --------------------------------
      parametre uzla
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
     const  no_ack   = #0 ;  { musi byt #0, fillchar(..., 0) sa nuluju premenne }
            is_ack   = '*';
            no_send  = 'N';
            is_rec   = '@';
            is_send  = '.';

     type   TPlanRec = char;

            Pplan_rec   = ^Tplan_rec;
            Tplan_rec   = array[0..maxNODEs-1] of TPlanRec;

            PBplan_rec  = ^TBplan_rec;
            TBplan_rec  = array[0..maxNODEs-1] of bool;


     function  time_out_nd (nd: int): word;


     function  is_to_nd  (nd      : int;      { cislo uzla }
                          info    : string;   { typ informacie odosielanej na uzol }
                          filter  : pointer;  { @TBfunc_pi - poslat plan na tento smer ? (sektor) }
                          data    : pointer;  { @data          }
                          initdb  : pbool
                         ): bool;

     function  is_nd_type(nd      : int;
                          typ_set : Tnd_typ_set;
                          sw_set  : Tnd_sw_set;
                          nd_set  : Tnd_nd_set
                         ): bool;


    { --------------------------------
      spracovanie pseudoadries, adries
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
     const  odd_NETadr = ' ';

     const { adresa servera
           }
            SERVERaddress  : TNETadr = '';   { adresa servera               }
            SERVERnode     : int     = -1;
            SERVERstatus   : bool = true;    { nemenit inicializaciu, je mimo BACKUP kvoli }
            SERVERtimeout  = 3;

            BACKUPaddress  : TNETadr = '';   { adresa zalozneho servera     }
            BACKUPnode     : int     = -1;
            BACKUPstatus   : bool = true;    { nemenit inicializaciu, je mimo BACKUP kvoli }

            FDAaddress     : TNETadr = '';   { adresa opravy dat, zatial len podla info riadku }
            FDAnode        : int     = -1;
            FDAnodes       : int     = 0;

           { adresy routera
           }
            ROUTERaddress  : TNETadr = '';   { txt adresa routera           }
            ROUTERadr_rtr  : TRTRadr = 0;    { rtr adresa - // -            }
            ROUTERadr_ip   : TIPadr  = 0;    { ip adresa  - // -            }

           { vlastne pseudoadresy
           }
            X25address     : TNETadr = '';   { adresa v X25 - plni readcfg  }
            LANaddress     : TNETadr = '';   { adresa v LAN - plni readcfg  }
            NETaddress     : TNETadr = '';   { spolocna adresa              }

            RTRaddress     : TNETadr = '';   { txt adresa v sieti ROUTERa   }
            RTRadr         : TRTRadr = 0;    { rtr adresa     - // -        }


            COMaddress     : TNETadr = '';

            IPaddress      : TNETadr = '';
            IPadr          : TIPadr  = 0;

            BRIDGEadr      : TNETadr = '';
            CBRIDGEadr     : TNETadr = '';
            RBRIDGEadr     : TRTRadr = 0 ;
            BRIDGEipadr    : TIPname = '';

            NODEpoc        : int =  0;
            NODEs          : PNETnodes = nil;

            NODEname       : pchar = nil;
            NODEinfo       : pchar = nil;

           { ine adresy
           }
            MONaddress      : TNETadr = '';   { txt adresa monitoringu       }
            PRNaddress      : TNETadr = '';
            STRIPPRNaddress : TNETadr = '';

            BROADCASTaddress: TNETadr = '%BROADCAST%';


     function  format_NETadr (adr: string): string;

     function  NETadr     (wan_adr,lan_adr: string): TNETadr;
     function  NETadr_lan (adr: TNETadr): TNETadr;
     function  NETadr_lan_(adr: TNETadr): TNETadr;
     function  NETadr_wan (adr: TNETadr): TNETadr;

     function  NETprotocol(adr: TNETadr): Tprotocol;
     function  NETtype    (adr: TNETadr): Tnd_typ;
     function  NETrtr_adr (adr: TNETadr): TRTRadr;

     function  NETres (res: byte): bool;
     function  NETres_(res: bool): TPlanRec;

     function  is_NETadr   (adr: TNETadr): int;
     function  is_NETname  (var adr: TNETadr): int;
     function  is_NODEname (adr: TNETadr): string;
     function  is_NETnode  (adr: TNETadr): int;

     function  self_NETadr(adr: TNETadr): TNETadr;



    { --------------------------------
      spracovanie paketu
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
     type   Tcode_NETpkt_data    = procedure (p_data: pointer; var pkt: TNETpkt);
            Pcode_NETpkt_data    = ^Tcode_NETpkt_data;

            Tdecode_NETpkt_data  = procedure (const pkt: TNETpkt; p_data: pointer);
            Pdecode_NETpkt_data  = ^Tdecode_NETpkt_data;

            Tcode_NETkey         = function (p_data: pointer): string;
            Pcode_NETkey         = ^Tcode_NETkey;

            Taccept_NETdata      = function (from: TNETadr; p_data: pointer): bool;
            Paccept_NETdata      = ^Taccept_NETdata;

            Tprocess_NETdata     = procedure (p_data: pointer);
            Pprocess_NETdata     = ^Tprocess_NETdata;


     procedure code_msg   (msg: pstring; var pkt: TNETpkt);  far;
     procedure decode_msg (const pkt: TNETpkt; msg: pstring); far;


     function  new_NETpkt_data  (data: pchars; dlz: TNETdlz; var pkt: TNETpkt_data): bool; far;
     procedure disp_NETpkt_data (var pkt: TNETpkt_data); far;

     function  flush_NETpkt_buff(var pkt: TNETpkt_data): bool;
     {function read_NETpkt      (pkt: TNETpkt_data; var data: pchars; var dlz: word): bool;}

     procedure new_NETpkt_pkt   (const pkt1: TNETpkt_data; var pkt2: TNETpkt_data); far;
     procedure disp_NETpkt_pkt  (var pkt: TNETpkt_data); far;

     procedure new_NETpkt       (pkt1,pkt2: PNETpkt); far;
     procedure disp_NETpkt      (pkt: PNETpkt); far;

     function  eq_NETpkt_       (p1,p2: TNETpkt; is_ind: bool): bool; far;

     procedure NET0pkt_NETpkt   (p0: TNET0pkt; var p: TNETpkt);
     procedure NETpkt_NET0pkt   (p: TNETpkt; var p0: TNET0pkt);

     function  is_proL (adr: TNETadr): bool;

     function  pkt_for_this_node  (const pkt: TNETpkt): bool;
     function  pkt_from_this_node (const pkt: TNETpkt): bool;

     function  rec_pkt_  (nd: int; var rec: Tplan_rec; what: char; bck: bool): bool;
     procedure rec_from_ (from: TNETadr; var rec: Tplan_rec; what: char; bck: bool);
     function  rec_pkt   (nd: int; var rec: Tplan_rec; what: char): bool;
     procedure rec_data  (from: TNETadr; var rec: Tplan_rec);
     procedure rec_copy  (src: Tplan_rec; var desc: Tplan_rec);

     {$IFDEF DATA_BIN}
      function  pkt_split (const pkt: TNETpkt_data; pos: int): word;
     {$ENDIF}


    procedure indicate_net (is: int);
    const     p_indicate_net : p_proc_indicate_process = nil;


implementation

uses BIOS,
     str0, mess, math, mem, utime,
     Kody {$IFDEF PCTCP}, PCTCP {$ENDIF};


{$I ..\L4\_L4_odd.h}

{$I _netpkt.inc}   { alloc/dealloc  }

{$I net_def1.inc}  { adresy,uzly... }
{$I net_def2.inc}  { pakety...      }
{$I net_def9.inc}

{$I sec0.inc}      { patri tento druh informacie na dany uzol ? }

 procedure indicate_net (is: int);
     begin
       if p_indicate_net<>nil then proc_indicate_process(p_indicate_net)(is)
     end;

begin
  tmout_ACK       := Limit(read_cfg_word(SYSTEMcfg,cfg_ACK_TIME_OUT ,tmout_ACK),       3,30, 0);
  tmout_CALL      := Limit(read_cfg_word(SYSTEMcfg,cfg_TEST_TIME_OUT,tmout_CALL),      tmout_ACK*2,300,0)*18;
  tmout_HEARTBEAT := Limit(read_cfg_word(SYSTEMcfg,cfg_NET__HEARTBEAT,tmout_HEARTBEAT),tmout_ACK,600,0)*18;
  tmout_HEARTBEAT_max:= tmout_HEARTBEAT;
  tmout_ACK       := tmout_ACK*18;
 {net_send_wait := Limit(read_cfg_word(SYSTEMcfg,cfg_pkt_wait,  net_send_wait), 0,5, 0);}

  NET_ACK_ALL     := read_cfg_bool(SYSTEMcfg,cfg_NET_ACK_ALL,NET_ACK_ALL);

  NODE_FILTER     := read_cfg_bool(SYSTEMcfg,cfg_NODE_FILTER,NODE_FILTER);

  INIT_TIMEOUT    := Limit(read_cfg_word(SYSTEMcfg,cfg_INIT_TIMEOUT,INIT_TIMEOUT),0,300,0);
  INIT_VYP        := read_cfg_bool(SYSTEMcfg,cfg_INIT_VYP,INIT_VYP);
  INITIALIZE_EN   := read_cfg_bool(SYSTEMcfg,cfg_INITIALIZE_EN,INITIALIZE_EN);
  _INITIALIZE_EN:= INITIALIZE_EN;
  INFO_INIT       := read_cfg_bool(SYSTEMcfg,cfg_info_INIT,info_INIT);
  {info_REROUTE   := read_cfg_bool(SYSTEMcfg,cfg_info_REROUTE,info_REROUTE) }
  WAIT_INIT_NODE  := read_cfg_bool(SYSTEMcfg,cfg_WAIT_INIT_NODE,WAIT_INIT_NODE);

  EN_RDP_ZO_SUBORA:= Limit(read_cfg_word(SYSTEMcfg,cfg_EN_RDP_ZO_SUBORA,EN_RDP_ZO_SUBORA),0,20,0);

  archive_NET_SEND := read_cfg_bool(SYSTEMcfg,cfg_archive_NET_SEND,archive_NET_SEND);
  archive_NET_REC  := read_cfg_bool(SYSTEMcfg,cfg_archive_NET_REC, archive_NET_REC);
end.
