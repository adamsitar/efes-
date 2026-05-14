(*-------------------------------------------------------------------*)
(* LETVIS FDP - driver pre komunikaciu s OPL v Prahienke             *)
(* (c) Ales Kosice 1993,95,98 (ab)                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ DEFINE OPL__SAVE_STREAM}

{$X+,I-,S-,P-,F+,O+}

(*{$IFDEF OPL_EXT_ASYNC}
 {$O-}
 {$C FIXED PRELOAD PERMANENT}
{$ENDIF}
*)

{ Roman mi posiela spravu FPL namiesto CHG,DLA
}

{ Priklady sprav :

  $3
  $(ESTMI/PL699-...-NIL)9152
  $(LAMPL/MI699)0152
  #(RTZMI/PL699)
}


unit _OPL;


interface

    uses   TypeDef,
           IO, {$I unit_gr.h},
           Objects, Events,
           Arrays,
           {$I unit_net.h},
           {$IFDEF OPL_EXT_ASYNC}  COMs, {$ENDIF}
           {$IFDEF OPL_EXT_UDP}  PCTCPdef, _PCTCP, PCTCP, {$ENDIF}
           _L4_def, _FDP_def, _FPL_def,

           {$IFDEF FPL4} _FPL4,                {$ENDIF}
           {$IFDEF FPL0} _FPLc, _FPLm, _FPLms, {$ENDIF}
           {$IFDEF PRS}  _PRS,                 {$ENDIF}
           {$IFDEF RTZ}  _RTZ,                 {$ENDIF}

           _EXT, _L4444, _L4_FDP, _OPL_def;



    {$I _opl_cnst.h}
    {$I _opl_obj.h}


    const  DEV_OPL : PO_OPL = nil;


implementation

uses  BIOS, _Check, Crt,
      keyb, str0, utime, mem, math, sets, parstr, mess, msg, DB,
      App, Cm, Dialog,
      Archiv,
      Vypocty, FIR_def, LDM, Bod_def, Body, ZemSur,
      _MTK_2,
      _FPL, _L4_func;


const  fn_AUPupdated = path_OPL+'AUP-REQ'+ext_kod;

{$I _OPL_.inc}             { init... }

{$I _OPL_receive_pkt.inc}  { pkt: save, read, receive, process }
{$I _OPL_decode_pkt.inc}   { pkt: process, decode head & data  }
{$I _OPL_send_pkt.inc}     { pkt: send do EXT                  }
{$I _OPL_code.inc}         { prisposobenie strukturam FDP      }
{$I _OPL_functions.inc}
{ I _OPL_err.inc}
{$I _OPL_test_pkt.inc}     { txt_file...                       }

{$IFDEF FPL0}
 {$I _OPL_ICAO.doc}        { FPL, CHG, CNL, DLA                }
 { I _OPL_ICAO.cod}
 {$I _OPL_ICAO.dec}

 {$I _OPL_OLDI.doc}        { CLR, ABI                          }
 {$I _OPL_OLDI.dec}

 {$I _OPL_AMA.doc}         { CPL, EST                          }
 {$I _OPL_AMA.cod}
 {$I _OPL_AMA.dec}
{$ENDIF}


function code_vysOPL(vys: string): string;
   var   v,vm  : word;
         v_ : char;
   begin
     if decode_l4_vyss (vys, v,v_,nil) then
        begin
          vm:= get_altM(v_,v);
          if vys=vys_UNL then {; zakomentovane 0326 }
          else { doplnene 0326 }
               if vm > get_altM(altFL,50) then vys:= code_l4_vyss (MtoFL(vm),altFL)
          else if vm > 300 then vys:= code_l4_vyss (MtoFL(vm),altA)
          else if vm <> 0 then vys:= code_l4_vyss (MtoS(vm),altG);
        end;
     code_vysOPL:= vys;
   end;

{$IFDEF PRS}
 {$I _O_AUP.dec}           { AUP                               }
{$ENDIF}

{$IFDEF RTZ}
 {$I _O_RTZ.dec}           { RTZ                               }
{$ENDIF}

end.