(*-------------------------------------------------------------------*)
(* LETVIS FDP - EDD 4.0                                              *)
(* (c) Ales Kosice 1993,96 (ab)                                      *)
(* Datove definicie                                                  *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}


unit _FDP_def;


interface


    uses  TypeDef,
          IO, keyb,
          {$I unit_gr.h},
          NET_def,
          _L4_def,
          Report,
          FIR_def, _MTK_2;


    {$I _FDP_var.h}
    {$I _FDP_stt.h}     { status }
    {$I _FDP_poz.h}
    {$I _FDP_err.h}

    {$I _FDP_ak.h}      { zdroje spracovania, koordinacia }
    {$I _FDP_prc.h}
    {$I _FDP_strip.h}   { definicia stripu }

    {$I _RPL_cnst.h}
    {$I _PLN_cnst.h}
    {$I _FPL4_cnst.h}   { docasne v _FDP_def }
    {$I _FPLC_cnst.h}   { docasne v _FDP_def }
    {$I _FPLM_cnst.h}   { docasne v _FDP_def }
    {$I _FPLM_err.h}
    {$I _FPL0_cnst.h}
    {$I _FPL0s_cnst.h}  { docasne v _FDP_def }
    {$I _FPS_cnst.h}    { docasne v _FDP_def }

    {$I _ZAM_cnst.h}    { docasne v _FDP_def }
    {$I _QGO_cnst.h}    { docasne v _FDP_def }
    {$I _RTZ_cnst.h}    { docasne v _FDP_def }
    {$I _DVZ_cnst.h}    { docasne v _FDP_def }

    {$I _PRS_cnst.h}    { docasne v _FDP_def }
    {$I _FUA_cnst.h}
    {$I _FUA_err.h}

    {$I _TLG_cnst.h}
    {$I _SPR_cnst.h}

    {$I FDP_rep.h}      { docasne v _FDP_def }

    {$I _FDP_cl.h }     { nastavenie farieb }
    {$I _FDP_tit.h}     { texty }
    {$I _FDP_rec.h}
    {$I _FPL_his.h}
    {$I _FPL_typ.h}     { spolupraca s RDP }


    function _plan_pre_ (src: string; ziadne,podriadene: bool): bool;
    function _plan_pre  (src: string): bool;


implementation

uses  BIOS,
      math, utime, str0, sets, mem, msg,
      Body, FDP_msg, FDP_func;


function _plan_pre_ (src: string; ziadne,podriadene: bool): bool;
   begin
     _plan_pre_:=  {$IFDEF AIRBASE}
                        (    (ziadne and (src=''))
                          or toto_letisko (src)
                          or (podriadene and podriadene_letisko(src))
                        )
                   {$ELSE}
                     true
                   {$ENDIF}
   end;

function _plan_pre (src: string): bool;
   begin
     _plan_pre:= _plan_pre_ (src, true,true)
   end;


{$I _FDP_stt.inc}    { stat }
{$I _FDP_poz.inc}    { poz  }
{$I _FDP_rec.inc}    { rec  }
{$I _FDP_strip.inc}

{$I _FDP_ak.inc}

end.