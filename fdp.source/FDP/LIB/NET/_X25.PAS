(*-------------------------------------------------------------------*)
(* _X25 - funkcie pre operacie v sieti X.25                          *)
(* (c) Ales Kosice 1994  (pdz)                                       *)
(*                 1996-99  (ab)                                     *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_X25.h}
{$I comp_rtr.h}

{$X+,I-,S-,P-,R+} {$IFNDEF DEBUG} {$R-} {$ENDIF}

{ Existuju dva protokoly kodovania dat : TNET0 [0] a TNET [1],
  pretoze nemozem zmenitt najstarsi protokol, a nema ani priznaky;
  odlisuju sa len podla konfiguracie...

  Rozdelnie dlheho paketu na kratkie zabezpecuje nadradeny
  protokol NET

  Potlacene routrovanie LAN/X25...
}

unit _X25;


interface

     uses  TypeDef, Arrays, IO,

           X25_def, NET_def
           {$I _hw_X25.h};


    {$IFDEF _X25}

     type  TBFunc_enabled_SVC_X25 =

              function  (_from : TX25name; user_data: Pbytes; user_len: byte): bool;

                       { Ext fcia pre kontrolu, ci s uzlom je mozne otvorit kanal,
                         pri zmene typu funckie v objekte, pretypovat i tuto
                         - parametre musa sedec !
                       }

           TProc_receive_pkt_X25 =

              procedure(adr: TX25name; data: pointer; size: word);


                       { Ext fcia pre spracovanie paketov od inych SVC ako LETVIS,
                         pretoze X25 je navrhnuta jednoucelovo a teda zle...
                         - parametre musa sedec !
                       }


     {$I X25_1.h}      { Cfg  }
     {$I X25_2.h}      { X25  }


     const  X25_installed   : bool = false;
            X25_initialized : bool = false;
            X25_archive     : bool = false;

            X25node   : int = -1;           { cislo uzla v strukture X25nodes               }
            nodesX25_ : int = -1;           { pocet stanic v sieti X25 - vsetky konf.subory }
            X25bridge : int = -1;
            nodesX25  : int = -1;           { pocet stanic v sieti - v konf. subore X25.cfg }
            X25nodes  : PO_X25nodes = nil;  { zaznam o stave siete                          }

            X25_net   : P_X25net    = nil;  { hlavny objekt}


     procedure  X25_init;

     function   isX25name(var name: TX25name): int;
     function   isX25adr (adr: TX25name; svc: byte): int;
     function   isX25chan(chan: U16BIT; svc: byte): int;

     function   is_this_X25node(adr: TX25name): bool;
     function   is_open_X25channel(adr: TX25name; var CHAN: S16BIT): bool;

     function   X25read(var pkt: TNETpkt): bool;
     function   X25send(pkt: TNETpkt; adr: TX25name): int;
     procedure  X25sending;

    {$ENDIF}

implementation


{$IFDEF _X25}

uses Crt, Dos, BIOS,
     math, sets, str0, mess,
     RTR_def, _RTR;

var   SaveExit  : pointer;


{$I X25_0.inc}    { adresy, kanaly }
{$I X25_1.inc}    { implementacia vlastne AdCOM2-ky }

{$I X25_3.inc}    { send, read }
{$I X25_4.inc}    { nevyuzivane bufferovanie }

{$I X25_cfg.inc}  { O_X25nodes }
{$I X25_ini.inc}

{$ENDIF}

begin
 {$IFDEF _X25}
  EXCEPTION_CALL_DESC:= read_cfg_bool(SYSTEMcfg, cfg_EXCEPTION_CALL_DESC, EXCEPTION_CALL_DESC);
 { ENDIF}
  SaveExit:= ExitProc;
  ExitProc:= @X25_Done;
  X25_detect
 {$ENDIF}
end.