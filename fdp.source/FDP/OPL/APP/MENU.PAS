(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 1.0                                              *)
(* (c) Ales Kosice 1993,98  (ab)                                     *)
(* Menu pre OPL                                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

{$IFDEF DEBUG} { DEFINE NOMENU} {$ENDIF}

unit Menu;


interface

    uses  TypeDef,
          Menus;


    var       OPLmenu     : PBarMenu;
    const     MENU_MACC   : bool = {$IFDEF MACC_MENU} {$IFDEF OPL_LET} false
                                                      {$ELSE}          true
                                                      {$ENDIF}
                                   {$ELSE}            false
                                   {$ENDIF};

    function  OPLmenu_init: PBarMenu;



implementation

uses  BIOS, SVGA, DOS, keyb, msg, mess, mouse, utime, graph_h, prnt, str0,
      CMs, CM, Views, help_def, Help, Button, Dialog, Scroll, Lists, Edit, Report, App,
      Hodiny,
      {$I unit_map.h},
      NET_utc, NET_def,
      _L4_def,_FDP_def,_FPL_def,
      FDP_msg, _PLAN, _STRIP, {_SSR,}
      {$I unit_fdp.h}
      {$I unit_fdf.h}
      {$I unit_ext.h},
      FDP_ap, FDP_fun2,
      ALES, GUI;


const INST        = '~ ~FDP/OPL';
      mnu_OPL     = '~O~PL';
      tit_OPL     = 'LETVIS FDP/OPL' ;

{$IFDEF EXTERNAL_NET}
 {$DEFINE EXT_ONOFF}
{$ENDIF}

{$I _zoznamy.mnu}
{$I ..\lib\mnu\_fdp.mnu}

function OPLmenu_init: PBarMenu;

   var   FPLmenu      : PSubMenu;
         KRLmenu      : PSubMenu;
         ZAMmenu      : PSubMenu;
         QGOmenu      : PSubMenu;
         DVZmenu      : PSubMenu;
         PRSmenu      : PSubMenu;
         PRZmenu      : PSubMenu;
         SPRmenu      : PSubMenu;

         DATAmenu     : PSubMenu;
         AIPmenu      : PSubMenu;

         OPTIONsmenu  : PSubMenu;
         MMImenu      : PSubMenu;
         SYSTEMmenu   : PSubMenu;

   begin

     OPLmenu:= New(PBarMenu);
     OPLmenu_init:= OPLmenu;

   {$IFNDEF NOMENU}

    {$IFDEF FPL0}
     FPLmenu:= SubMenu(mnu_FPLM, WinMenu(tit_FPLM, hlpmnuFPLM,nil),nil);
     FPLmenu^.PMenu_init:= @mnuFPLM_init;
    {$ENDIF}

    {$IFDEF KRL}
     KRLmenu:= SubMenu(mnu_KRL, WinMenu(tit_KRL, hlpmnuKRL,nil),nil);
     KRLmenu^.PMenu_init:= @mnuKRL_init;
    {$ENDIF}

    {$IFDEF ZAM}
     ZAMmenu:= SubMenu(mnu_ZAM, WinMenu(tit_ZAM, hlpmnuZAM,nil),nil);
     ZAMmenu^.PMenu_init:= @mnuZAM_init;
    {$ENDIF}

    {$IFDEF QGO}
     QGOmenu:= SubMenu(mnu_QGO, WinMenu(tit_QGO, nil{hlpmnuSNO},nil),nil);
     QGOmenu^.PMenu_init:= @mnuQGO_init;
    {$ENDIF}

    {$IFDEF DVZ}
     DVZmenu:= SubMenu(mnu_DVZ, WinMenu(tit_DVZ, hlpmnuDVZ,nil),nil);
     DVZmenu^.PMenu_init:= @mnuDVZ_init;
    {$ENDIF}

    {$IFDEF PRZ}
     PRZmenu:= SubMenu(mnu_PRZ, WinMenu(tit_PRZ,  hlpmnuPRZ,nil),nil);
     PRZmenu^.PMenu_init:= @mnuPRZ_init;
    {$ENDIF}

    {$IFDEF PRS}
     PRSmenu:= SubMenu(mnu_PRS, WinMenu(tit_PRS,  hlpmnuPRS,nil),nil);
     PRSmenu^.PMenu_init:= @mnuPRS_init;
    {$ENDIF}

    {$IFDEF SPR}
     SPRmenu:= SubMenu(mnu_SPR, WinMenu(tit_SPR, hlpmnuSPR, nil),nil);
     SPRmenu^.PMenu_init:= @mnuSPR_init;
    {$ENDIF}

     DATAmenu:= SubMenu(mnu_UDAJE, WinMenu(tit_UDAJE, hlpmnuPREHLAD,nil),nil);
     DATAmenu^.PMenu_init:= @mnuPREHLAD_init;

     AIPmenu:= SubMenu(mnu_AIP, AIP_menu,nil);
   {$ENDIF}

     MMImenu:= SubMenu (mnu_MMI,WinMenu(tit_MMI,hlpmnuMMI,nil),nil);
     MMImenu^.PMenu_init:= @mnuMMI_init;

   {$IFNDEF NOMENU}
     OPTIONSmenu:= SubMenu(mnu_OPT, WinMenu(tit_OPT,hlpmnuOPTIONS,nil),nil);
     OPTIONSmenu^.PMenu_init:= @mnuOPTIONS_init;

     is_letvis_menu:= true;
     SYSTEMmenu:= SubMenu (mnu_SYSTEM, WinMenu(tit_SYSTEM,hlpmnuSYSTEM,nil),nil);
     SYSTEMmenu^.PMenu_init:= @mnuSYSTEM_init;
   {$ENDIF}

     OPLmenu^.Init('',

         Item2  (INST, kbCtrlF1, cmAbout,

        {$IFNDEF NOMENU}

         {$IFDEF FPL0}
          SubMenuInitialized(FPLmenu,
         {$ENDIF}

         {$IFDEF KRL}
          SubMenuInitialized(KRLmenu,
         {$ENDIF}

         {$IFDEF ZAM}
          SubMenuInitialized(ZAMmenu,
         {$ENDIF}

         {$IFDEF QGO}
          SubMenuInitialized(QGOmenu,
         {$ENDIF}

         {$IFDEF DVZ}
          SubMenuInitialized(DVZmenu,
         {$ENDIF}

         {$IFDEF PRZ}
          SubMenuInitialized(PRZmenu,
         {$ENDIF}

         {$IFDEF PRS}
          SubMenuInitialized(PRSmenu,
         {$ENDIF}

         {$IFDEF SPR}
          SubMenuInitialized(SPRmenu,
         {$ENDIF}

         SubMenuInitialized(DATAmenu,

         SubMenuInitialized(AIPmenu,
       {$ENDIF}

         SubMenuInitialized(MMImenu,

       {$IFNDEF NOMENU}
         SubMenuInitialized(OPTIONSmenu,

         SubMenuInitialized(SYSTEMmenu,
       {$ENDIF}

        nil)
            {$IFNDEF NOMENU}
             {$IFDEF FPL0} ) {$ENDIF}
             {$IFDEF KRL}  ) {$ENDIF}
             {$IFDEF ZAM}  ) {$ENDIF}
             {$IFDEF QGO}  ) {$ENDIF}
             {$IFDEF DVZ}  ) {$ENDIF}
             {$IFDEF PRZ}  ) {$ENDIF}
             {$IFDEF PRS}  ) {$ENDIF}
             {$IFDEF SPR}  ) {$ENDIF}
             ) ) ) )
            {$ENDIF}
           )
        );
   end;

end.
