(*-------------------------------------------------------------------*)
(* LETVIS FDP - spracovanie sprav zo siete, uz sa preraba            *)
(* (c) Ales Kosice 1993,94; 98 ab)                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}

{$X+,I-,S-,P-}

{ Doplnit potvrdzovanie sprav z viacerych smerov "rec"
}


unit _SPR;


interface

     uses   TypeDef,
            DB,
            {$I unit_gr.h},
            {$I unit_oop.h}, Report,
            {$I unit_net.h},
            _MTK_2, _L4_def, _FDP_def,
            frm_TLG;


     {$IFDEF SPR}
       { I _SPR_cnst.h}
       {$I _SPR_title.h}
       {$I _SPR_data.h}
       {$I _SPR_func.h}

       function _handle_event_SPR (var _Event: TEvent; O: PObject; SPR: pointer): bool;
     {$ENDIF}


implementation

uses  BIOS, _Check, str0, IO, mem, math, keyb, mouse, utime, mess, sets, prnt, msg,
      Body, Archiv, Lists,
      FDP_msg, FDP_scrl, FDP_edit, FDP_func,
      PCTCPdef, PCTCP
      {$IFDEF STATUS}     , Status    {$ENDIF}
      {$IFDEF STATISTIKA} , STA_def   {$ENDIF}
      ;


{$IFDEF SPR}

 const  CISLO_SPRAVY : word = 0;
        MOD_CISLA_SPRAVY    = 1000;

        SPR_kod     = pathMES+extMES+ext_kod;


 const  SPRadr_all  = '*';
        SPRadr_opl  = 'O';
        SPRadr_let  = 'L';

        SPRadr_subnet  = '_';
        SPRadr_odd     = ' ';
        set_SPRadr_odd = [';',',',SPRadr_odd];
        set_SPRadr  : TCharSet =   ['.']+set_SPRadr_odd
                                 + [repl_l4,SPRadr_subnet]
                                 + [SPRadr_all,SPRadr_opl,SPRadr_let]
                                 + ['A'..'Z','0'..'9'];


 const  dxm_SPR   = 10+MTK_2_LINE*8+10;
        dxf_SPR   = dxm_SPR;

        dy_rmk    = 4;
        {dy_SPRadr = dy_rmk+10+dy_rmk+(max_SPR_a_hi*10)+dy_rmk;
        dym_SPR   = dy_rmk+10+dy_rmk+(max_SPR_r_lo*10)+dy_rmk;
        dyf_SPR   = dym_SPR + max_SPR_r_hi*10;}

        write_acc : bool = true;


 {$I _SPR.cod}
 {$I _SPR.inc}    { save, send }
 {$I _SPR.drw}
 {$I _SPR.prn}

 {$I _SPR.frm}

 {$I _SPR2.inc}
 {$I _SPR3.inc}
 {$I _SPR4a.inc}
 {$I _SPR4.inc}

 { I _SPR_archiv.inc}
 {$I _SPR_initialize.inc}
 {$I _SPR_handle.inc}
 {$I _SPR_rec.inc}


begin
  initialize_SPR
{$ENDIF}
end.