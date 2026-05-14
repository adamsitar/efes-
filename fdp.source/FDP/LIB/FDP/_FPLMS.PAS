(*-------------------------------------------------------------------*)
(* LETVIS FDP - Dalsie spracovanie FPL                               *)
(* (c) Ales Kosice 1993,99  (ab)                                     *)
(* Spracovanie planov                                                *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$I comp_FDP.h}
{$I comp_OPL.h}

{
  Kridla sa odosielaju len na letisko startu
}

unit _FPLMs;


interface


    uses  TypeDef,
          {$I unit_oop.h}, Lists,
          {$I unit_gr.h},
          {$I unit_net.h},
          {$I unit_map.h},
          _L4_def, _MTK_2,
          _FDP_def, _FPL_def, FDP_edit,
          FDP_scrl,
          _PLAN, _STRIP, _FPL,
          _FPL4, _FPLc, _FPLm,
          form_SYS, frm_FPL;


    {$IFDEF FPL0}
      {$I _FPL0s_func.h}

      {$IFDEF PROCESS_FPLM}  {$IFDEF OPL}
       {$I _FPLm_rq.h}
      {$ENDIF} {$ENDIF}
    {$ENDIF}


implementation

{ Aby sa plany po spracovani nahrali i do prostredia,
  zabezpeci to funkcia add_FPL volana zo spracujucich
  funkcii:  - formulara
            - zmen_stav
}

uses  BIOS, _Check, DOS, DB, IO, Crt,
      utime, str0, keyb, mouse, math, mess, sets, sort, coms, prnt,
      ParStr, Archiv, Msg, Bod_Def, Body,
      _L4_func, FDP_fun2, FDP_msg,
      Sector;


{$IFDEF FPL0}

  const     find_and_process_data = {$IFDEF SERVER} false {$ELSE} true {$ENDIF}; { docasna premenna }

  const     cnst_FPL_REQ    = {$IFDEF AIRBASE}
                               cnst_disk + cnst_sended + cnst_chg
                              {$ENDIF}
                              + cnst_prop;

            cnst_FPL_CHG    = cnst_disk + cnst_sended + cnst_chg
                              + cnst_prop + cnst_dla
                              {$IFDEF MACC}
                                + cnst_dec + cnst_acc
                              {$ENDIF}
                              ;

            cnst_FPL_DLA    =   cnst_disk + cnst_sended + cnst_chg
                              + cnst_prop + cnst_dla + cnst_acc;

            cnst_FPL_DEP    = cnst_prop + cnst_acc
                              {$IFDEF MACC}
                                + cnst_disk + cnst_sended
                                + cnst_prop + cnst_acc
                              {$ENDIF}
                              ;

            cnst_FPL_ARR    = cnst_stat_act;


 {$IFDEF FPL0}

   {$IFNDEF FPLM_DISABLED}
    procedure send_FPLs (FPLs: PmFPLs; top: pointer); far; forward;
    {$IFDEF KRL}
     procedure send_KRLs (FPLs: PmFPLs; top: pointer); far; forward;
    {$ENDIF}
   {$ENDIF}

   function  _handle_event_FPL_o_sc (var _Event: TEvent; O: PObject;
                                     FPL: pointer;
                                     iFPL: P_OFPL;
                                     sc: PScroller
                                    ): bool; far; forward;


   type  PFPL_item_filter = ^TFPL_item_filter;
         TFPL_item_filter = record
           key         : Tkey_fpl;
           data_filter : pointer;
           prev_filter : pointer;
         end;


   {$I _FPLcs_spracovanie.inc}   { filtre }

   {$IFNDEF FPLM_DISABLED}

   {$I _FPLms_spracovanie.inc}   { filtre }

   { Schvalenie ziadosti o FPL
   }
    {$IFDEF PROCESS_FPLM}  {$IFDEF OPL}
     {$I _FPLm_rq.frm}
     {$I _FPLm_twr.inc}    { FPL - letisko   }
     {$I _FPLm_acc.inc}    { FPL - stredisko }

     {$I _FPLm_req.inc}    { REQ }
    {$ENDIF} {$ENDIF}

   { Spracovanie planov
   }
    function _CNL_FPL_(sc: PScroller; FPL: PDmFPL; tit: string): bool; forward;

   {$I _FPLms2a.inc}       { CHG,CNL,SEND }

   {$IFDEF PROCESS_FPLM}   { funkcie pre spracovanie KRL/FPL }
    {$I _KRLs.inc}         { KRL     }
    {$I _FPLms2b.inc}      { DEP,ARR }
    {$I _FPLms2c.inc}      { MZP,RTE }

    {$I _FPLm_RPL.inc}     { prehlady RPL }
   {$ENDIF}


   { Prehlady planov
   }
    {$I _KRL_handle.inc}
    {$I _FPLm_handle.inc}
   {$ENDIF}
    {$I _FPLc_handle.inc}  { menu pre FPLc }
    {$I _FPLs_archiv.inc}  { EDDn    : prehlad a spracovanie ukoncenych letov }

   {$IFNDEF FPLM_DISABLED}
    {$I _KRL_prehlad.inc}  { OPL     : kridla }
    {$I _FPLs_prehlad.inc} { OPL/IDD : prehlady FPL }
   {$ENDIF}

   {$IFDEF RDP_ACCEPT}
    {$I _oFPLrdp.inc}
   {$ENDIF}

   {$I _FPLs_handle.inc}  { handle_event pre FPL : DB, iFPL, Lety  }

 {$ENDIF}

{$ENDIF}

{$UNDEF PROCESS_ARCHIV}
{$UNDEF OPL_SERVER}

  { I _FPLm_archiv.inc}
  {$I _FPLm_ini.inc}

begin
  initializacia_FPLM;
  {kontrola_archivu_FPLM;}
end. { _FPLMs }