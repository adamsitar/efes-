(*----------------------------------------------------------------------*)
(* LETVIS FDP - SERVER 1.0                                           *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(* Menu pre OPL                                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

{$IFDEF DEBUG} { DEFINE NOMENU} {$ENDIF}

unit Menu;


interface

    uses  TypeDef, Menus;


    var   SERVERmenu : PBarMenu;

    function  SERVERmenu_init: PBarMenu;


implementation

uses  BIOS, SVGA, DOS, keyb, mess, msg, mouse, utime, graph_h, prnt, str0,
      CMs, CM, Views, help_def, Help, Button, Dialog, Scroll, Edit, Lists, Report, App,
      Hodiny, 
      {$I unit_map.h},
      NET_utc, {$I unit_net.h}, {$IFDEF UDP} pctcp, {$ENDIF}
      _L4_def,_FDP_def,_FPL_def,
      FDP_msg, _PLAN, _STRIP,
      {$I unit_fdp.h}
      {$I unit_fdf.h}
      {$I unit_ext.h},
      FDP_ap, FDP_fun2,
      ALES;


const INST        = '~ ~FDP/S';
      mnu_SERVER  = '~S~ERVER';
      tit_SERVER  = 'LETVIS FDP/SERVER' ;

function SERVERmenu_init_: PBarMenu; forward;


{ IFNDEF NOMENU}

{$IFDEF LZIB_ACC}
  {$DEFINE EXT_ONOFF}

  {$I acc_sk.mnu}
{$ENDIF}

{$IFDEF LZIB_MACC}
  {$DEFINE EXT_ONOFF}
  {$DEFINE EXT_COM}

  {$I macc_sk.mnu}
{$ENDIF}

{$IFDEF LZIB_UVS}
  {$I uvs_sk.mnu}
{$ENDIF}

{$IFDEF LKPR_MACC}
  {$DEFINE EXT_ONOFF}
  {$DEFINE EXT_COM}
  {$DEFINE EXT_OPTIONS}

  {$I macc_cz.mnu}
{$ENDIF}


{$IFDEF UKBB_PRN}
  { I ukbb_prn.mnu}
{$ENDIF}

{ ENDIF}

{$I _fdp.mnu}


function SERVERmenu_init_: PBarMenu;

   var   RPLmenu      : PSubMenu;
         FPL4menu     : PSubMenu;
         FPLMmenu     : PSubMenu;
         QGOmenu      : PSubMenu;
         PRSmenu      : PSubMenu;
         TLGmenu      : PSubMenu;
         SPRmenu      : PSubMenu;

         STREAMmenu   : PSubMenu;
         DATAmenu     : PSubMenu;

         OPTIONsmenu  : PSubMenu;
         MMImenu      : PSubMenu;

         SYSTEMmenu   : PSubMenu;

   begin

     SERVERmenu:= New(PBarMenu);
     SERVERmenu_init_:= SERVERmenu;

    {$IFNDEF NOMENU}

     STREAMmenu:=  SubMenu(mnu_STREAM,  WinMenu(tit_STREAM,nil,nil),nil);
     STREAMmenu^.PMenu_init:= @mnuSTREAM_init;

     {$IFDEF PROCESS_RPL}
      RPLmenu:= SubMenu(mnu_RPL, WinMenu(tit_RPL, hlpmnuRPL,nil),nil);
      RPLmenu^.PMenu_init:= @mnuRPL_init;
     {$ENDIF}

     {$IFDEF PROCESS_FPL4}
      FPL4menu:= SubMenu(mnu_FPL4, WinMenu(tit_FPL4, hlpmnuFPL4,nil),nil);
      FPL4menu^.PMenu_init:= @mnuFPL4_init;
     {$ENDIF}

     {$IFDEF PROCESS_FPLM}
      FPLMmenu:= SubMenu(mnu_FPLM, WinMenu(tit_FPLM, hlpmnuFPLM,nil),nil);
      FPLMmenu^.PMenu_init:= @mnuFPLM_init;
     {$ENDIF}

     {$IFDEF PROCESS_QGO}
      QGOmenu:= SubMenu(mnu_QGO, WinMenu(tit_QGO, hlpmnuQGO,nil),nil);
      QGOmenu^.PMenu_init:= @mnuQGO_init;
     {$ENDIF}

     {$IFDEF PROCESS_PRS}
      PRSmenu:= SubMenu(mnu_PRS, WinMenu(tit_PRS, hlpmnuPRS,nil),nil);
      PRSmenu^.PMenu_init:= @mnuPRS_init;
     {$ENDIF}

     {$IFDEF TLG}
      TLGmenu:= SubMenu(mnu_TLG, WinMenu(tit_TLG, hlpmnuTLG,nil),nil);
      TLGmenu^.PMenu_init:= @mnuTLG_init;
     {$ENDIF}

     {$IFDEF SPR}
      SPRmenu:= SubMenu(mnu_SPR, WinMenu(tit_SPR, hlpmnuSPR, nil),nil);
      SPRmenu^.PMenu_init:= @mnuSPR_init;
     {$ENDIF}

     DATAmenu:= SubMenu(mnu_UDAJE,  WinMenu(tit_UDAJE,nil,nil),nil);
     DATAmenu^.PMenu_init:= @mnuPREHLAD_init;

     OPTIONSmenu:= SubMenu(mnu_OPT,  WinMenu(tit_OPT, nil,nil),nil);
     OPTIONSmenu^.PMenu_init:= @mnuOPTIONS_init;

     MMImenu:= SubMenu (mnu_MMI,WinMenu(tit_MMI, hlpmnuSYSTEM,nil),nil);
     MMImenu^.PMenu_init:= @mnuMMI_init;

     SYSTEMmenu:= SubMenu (mnu_SYSTEM, WinMenu(tit_SYSTEM,hlpmnuSYSTEM,nil),nil);
     SYSTEMmenu^.PMenu_init:= @mnuSYSTEM_init;

    {$ENDIF}

     SERVERmenu^.Init('',

       Item2(INST, kbCtrlF1, cmAbout,

       {$IFNDEF NOMENU}
        SubMenuInitialized(STREAMmenu,

        {$IFDEF PROCESS_RPL}
         SubMenuInitialized(RPLmenu,
        {$ENDIF}

        {$IFDEF PROCESS_FPL4}
         SubMenuInitialized(FPL4menu,
        {$ENDIF}

        {$IFDEF PROCESS_FPLM}
         SubMenuInitialized(FPLMmenu,
        {$ENDIF}

        {$IFDEF PROCESS_QGO}
         SubMenuInitialized(QGOmenu,
        {$ENDIF}

        {$IFDEF PROCESS_PRS}
         SubMenuInitialized(PRSmenu,
        {$ENDIF}

        {$IFDEF TLG}
         SubMenuInitialized(TLGmenu,
        {$ENDIF}

        {$IFDEF SPR}
         SubMenuInitialized(SPRmenu,
        {$ENDIF}

        SubMenuInitialized(DATAmenu,

        SubMenuInitialized(OPTIONSmenu,
        SubMenuInitialized(MMImenu,
        SubMenuInitialized(SYSTEMmenu,
       {$ENDIF}

        nil)
            {$IFNDEF NOMENU}
             )
             {$IFDEF PROCESS_RPL}  ) {$ENDIF}
             {$IFDEF PROCESS_FPL4} ) {$ENDIF}
             {$IFDEF PROCESS_FPLM} ) {$ENDIF}
             {$IFDEF PROCESS_QGO}  ) {$ENDIF}
             {$IFDEF PROCESS_PRS}  ) {$ENDIF}
             {$IFDEF SPR}          ) {$ENDIF}
             {$IFDEF TLG}          ) {$ENDIF}
             ) ) ) )
            {$ENDIF}
        );
   end;

end.
