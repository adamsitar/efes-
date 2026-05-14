(*-------------------------------------------------------------------*)
(* LETVIS FDP - EDD                                                  *)
(* (c) Ales Kosice (ab)                                              *)
(*                                                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit Menu;


interface

    uses  TypeDef,
          {$I unit_gr.h},
          {$I unit_oop.h};


    var       EDDmenu    : PBarMenu;
              TABLET_EDD : bool;       { pomocna premenna }
    const     kb_switch_TABLET_EDD: char = 'E';

    function  EDDmenu_init: PBarMenu;


implementation

uses  BIOS, DOS, keyb, mess, msg, mouse, utime, prnt, str0,
      {$I unit_map.h},
      Lists,
      NET_utc, NET_def,
      _L4_def,_FDP_def, _FPL_def,
      FDP_msg, _PLAN, _STRIP,
      {$I unit_fdp.h} Report,
      {$I unit_fdf.h}
      {$I unit_ext.h},
      FDP_ap, FDP_fun2,
      Hodiny, ALES,
      _SSR,
      ACC_ini, ACC
     ;


 const mnu_EDD_  = '~E~DD';
       mnu_EDD   = {$IFDEF IDD} 'I~D~D' {$ELSE} 'E~D~D' {$ENDIF};

       INST =  {$IFDEF DEMO_EDD}
                 '~ ~FDP/EDD-MACC...';
               {$ENDIF}

               {$IFDEF SK}
                {$IFDEF MACC}
                  '~ ~FDP/EDD-SRLP...';
                {$ENDIF}
                {$IFDEF PVO}
                  '~ ~FDP/IDD-VS...';
                {$ENDIF}
                {$IFDEF APP}
                  '~ ~FDP/IDD-RDC...';
                {$ENDIF}
               {$ENDIF}

               {$IFDEF CZ}
                {$IFDEF LKPR_MACC}
                  '~ ~FDP/EDD-MACC...';
                {$ENDIF}

                {$IFDEF LK_LET}
                  '~ ~FDP/EDD-TWR...';
                {$ENDIF}
                {$IFDEF LK_PVO}
                  '~ ~FDP/IDD-PVO...';
                {$ENDIF}
               {$ENDIF}

               {$IFDEF UK}
                  '~ ~FDP/EDD';
               {$ENDIF}


{$I .\app\_board.mnu}
{$I ..\lib\mnu\_strips.mnu}
{$I ..\lib\mnu\_fdp.mnu}


 const  ESTETO: bool = true;

 function  EDDmenu_init : PBarMenu;

     var   STRIPmenu    : PSubMenu;
           BOARDmenu    : PSubMenu;
           PLANZETmenu  : PSubMenu;

           NAJDImenu    : PSubMenu;
           ESTmenu      : PSubMenu;
           ETOmenu      : PSubMenu;
           CNLmenu      : PSubMenu;
           {$IFDEF FPLM_PLAN}
            FPLMmenu    : PSubMenu;
           {$ENDIF}
           {$IFDEF PRS_PLAN}
            PRSmenu     : PSubMenu;
           {$ENDIF}
            SPRmenu     : PSubMenu;

           DATAmenu     : PSubMenu;
           {$IFDEF IDD}
            AIPmenu     : PSubMenu;
           {$ENDIF}

           OPTIONsmenu  : PSubMenu;
           MMImenu      : PSubMenu;
           SYSTEMmenu   : PSubMenu;

           title : string;

     begin

       EDDmenu:= New(PBarMenu);
       EDDmenu_init:= EDDmenu;


       BOARDmenu:=  {$IFDEF MAPY} SubMenu_(mnu_BOARD, @PLANZET_MAPA,false,
                    {$ELSE}       SubMenu (mnu_BOARD,
                    {$ENDIF}      WinMenu (tit_BOARD, hlpmnuBOARD,
                    nil),nil);
       BOARDmenu^.PMenu_init:= @mnuBOARD_init;

       {$IFDEF MAPY}
        PLANZETmenu:= SubMenu_ (mnu_PLANZET, @PLANZET_MAPA,true, WinMenu(tit_PLANZET,hlpmnuMMI_MAPS,nil),nil);
        PLANZETmenu^.PMenu_init:= @mnuPLANZET_init;
       {$ENDIF}

       {$IFDEF FPLM_PLAN}
        FPLMmenu:= SubMenu(mnu_FPLM, WinMenu(tit_FPLM, hlpmnuFPLM,nil),nil);
        FPLMmenu^.PMenu_init:= @mnuFPLM_init;
       {$ENDIF}

       {$IFDEF PRS_PLAN}
        PRSmenu:= SubMenu(mnu_PRS, WinMenu(tit_PRS,  hlpmnuPRS,nil),nil);
        PRSmenu^.PMenu_init:= @mnuPRS_init;
       {$ENDIF}

       {$IFNDEF FPLM_PLAN} { docasne, ale teraz to staci }
        ESTETO:= ENABLE_FPLC or ENABLE_FPLM;

        ESTmenu:= SubMenu_(mnu_EST, @ESTETO,true, WinMenu(tit_EST, hlpmnuEST,nil),nil);
        ESTmenu^.PMenu_init:= @mnuEST_init;

        ETOmenu:= SubMenu_(mnu_ETO, @ESTETO,true, WinMenu(tit_ETO, hlpmnuETO,nil),nil);
        ETOmenu^.PMenu_init:= @mnuETO_init;

        {$IFDEF CNL_FPLC}
         title:= {mnuCNL-> kvoli kolizii hot keys}'CN~L~'
        {$ELSE}
         title:= 'DE~L~'
        {$ENDIF};
        CNLmenu:= SubMenu(title, WinMenu(title, hlpmnuCNL,nil),nil);
        CNLmenu^.PMenu_init:= @mnuCNL_init;

       {$ENDIF}

       NAJDImenu:= SubMenu(mnu_NAJDI, WinMenu(tit_NAJDI,hlpmnuSEARCH,nil),nil);
       NAJDImenu^.PMenu_init:= @mnuNAJDI_init;

       {$IFDEF SPR}
        SPRmenu:= SubMenu(mnu_SPR, WinMenu(tit_SPR, hlpmnuSPR, nil),nil);
        SPRmenu^.PMenu_init:= @mnuSPR_init;
       {$ENDIF}

       DATAmenu:= SubMenu(mnu_UDAJE, WinMenu(tit_UDAJE, hlpmnuPREHLAD,nil),nil);
       DATAmenu^.PMenu_init:= @mnuPREHLAD_init;

       {$IFDEF IDD}
        AIPmenu:= SubMenu(mnu_AIP, AIP_menu,nil);
       {$ENDIF}

       MMImenu:= SubMenu (mnu_MMI,WinMenu(tit_MMI,hlpmnuMMI,nil),nil);
       MMImenu^.PMenu_init:= @mnuMMI_init;

       OPTIONSmenu:= SubMenu(mnu_OPT, WinMenu(tit_OPT,hlpmnuOPTIONS,nil),nil);
       OPTIONSmenu^.PMenu_init:= @mnuOPTIONS_init;

       SYSTEMmenu:= SubMenu (mnu_SYSTEM, WinMenu(tit_SYSTEM,hlpmnuSYSTEM,nil),nil);
       SYSTEMmenu^.PMenu_init:= @mnuSYSTEM_init;


       EDDmenu^.Init('',

               Item2(INST, kbCtrlF1, cmAbout,

               {$IFDEF MAPY}
                Switch0 (mnu_EDD_, cmEDD_TABLET, @TABLET_EDD,
               {$ENDIF}

               {$IFDEF SECTORS}
                Switch0 ('SE~C~', cmACC_SETT{cmEDD_TABLET}, @S_DISPLAY,
               {$ENDIF}

               SubMenuInitialized(STRIPs_menu_init(mnu_STRIP,tit_STRIP),

               SubMenuInitialized(BOARDmenu,

               {$IFDEF MAPY}
                SubMenuInitialized(PLANZETmenu,
               {$ENDIF}

               {$IFDEF FPLM_PLAN}
                SubMenuInitialized(FPLMmenu,
               {$ENDIF}

               {$IFDEF PRS_PLAN}
                SubMenuInitialized(PRSmenu,
               {$ENDIF}

               {$IFDEF FPL4_ACT}
                Item   ('~A~CT', cm_ACT,
               {$ENDIF}

               {$IFNDEF FPLM_PLAN} { docasne, ale teraz to staci }

                SubMenuInitialized(ESTmenu,

                SubMenuInitialized(ETOmenu,

                SubMenuInitialized(CNLmenu,

               {$ENDIF}

               SubMenuInitialized(NAJDImenu,

               {$IFDEF SPR}
                 SubMenuInitialized(SPRmenu,
               {$ENDIF}

               SubMenuInitialized(DATAmenu,

               {$IFDEF IDD}
                SubMenuInitialized(AIPmenu,
               {$ENDIF}


               SubMenuInitialized(OPTIONSmenu,

               SubMenuInitialized(MMImenu,

               SubMenuInitialized(SYSTEMmenu,

               nil) {$IFDEF MAPY} ) ) {$ENDIF}
                    {$IFDEF SECTORS} ) {$ENDIF}
                    {$IFDEF FPL4_ACT} ) {$ENDIF}
                    {$IFDEF FPLM_PLAN} )
                    {$ELSE}
                      ) )
                      {$IFNDEF CNL_FPLC_DISABLED} ) {$ENDIF}
                    {$ENDIF}
                    {$IFDEF PRS_PLAN} ) {$ENDIF}
                    {$IFDEF SPR}  ) {$ENDIF}
                    )
                    {$IFDEF IDD} ) {$ENDIF}
                    ) ) ) ) ) )
               );
     end;

end.
