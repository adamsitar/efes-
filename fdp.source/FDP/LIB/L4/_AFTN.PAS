{ -------------------------------------------------
  AFTN interface pre LETVIS/FDP
  pre spracovanie sprav zo siete AFTN
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתתתתתת
  (c) ALES 1996,99
 תתתתתתתתתתתתתתתתתתת
}

{$DEFINE EXTERNAL_NET}

{$I comp.h}

unit _AFTN;


interface


    uses   typedef,
           keyb, io, coms,
           {$I unit_gr.h},
           {$I unit_net.h},
           Arrays, {$I unit_oop.h},
           _L4_def, _MTK_2,
           _EXT_def, _EXT, _L4444, _L4_FDP;


    {$I _AFTN_cnst.h}
    {$I _AFTN_title.h}
    {$I _AFTN_func.h}
    {$I _AFTN_object.h}

    const  DEV_AFTN : P_AFTN = nil;


implementation

uses  DOS, BIOS, _Check,
      mem, str0, mess, math, sets, utime, prnt, msg,
      FIR_def, Bod_def,
      FDP_msg, _FDP_def, _FPL_def, _FPL4,
      Archiv, form_SYS;


{$I _TLG4.inc}

{$I _AFTN_editor.inc}      { editor         }
{$I _AFTN_object.inc}      { TObject        }
{$I _AFTN_net.inc}         { synchronizacia }
{$I _AFTN_check.inc}       { check          }

{$I _AFTN_.inc}            { inicializacia                     }
{$I _AFTN_receive_pkt.inc} { pkt: save, read, receive, process }
{$I _AFTN_decode_pkt.inc}  { pkt: decode_data                  }
{$I _AFTN_send_pkt.inc}    { pkt: vysielanie                   }
{$I _AFTN_error_pkt.inc}   { error, alert                      }
{$I _AFTN_tlg.inc}         { tlg: spracovanie, fn...           }

{$I _AFTN_test.inc}        { debug }


{$IFDEF CONNECT_TO_AFTN}
begin
  p_proc_send_TLG:= @send_to_AFTN;
{$ENDIF}
end.
