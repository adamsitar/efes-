(*-------------------------------------------------------------------*)
(* Commands 1.0                                                      *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit CMs;


interface

    const { --------------------------------- }
          { standartne prikazy                }
          { --------------------------------- }
            cmNil       = 0;
            cmQuit      = 1;
            cmError     = 2;
            cmMenu      = 3;
            cmClose     = 4;
            cmZoom      = 5;
            cmResize    = 6;
            cmNext      = 7;
            cmPrev      = 8;

          { TDialog standard commands }
            cmOK        = 10;
            cmCancel    = 11;
            cmYes       = 12;
            cmNo        = 13;

            cmDefault   = 14;  { ak nechcem generovat ziaden prikaz a cmNil je nevhodny }
            cmSetActive = 15;

            cmHelp      = 30;
            cmHelpIndex = 31;


          { Standard messages }
            cmReceivedFocus     = 50;
            cmReleasedFocus     = 51;
            cmCommandSetChanged = 52;


          { TWindow messages }
            cmSelectWindow      = 53;  { zvolenie okna za aktivne }
            cmMoveWindow        = 54;  { presun okna              }
            cmGrowWindow        = 55;  { zmena velkosti okna      }


          { TScrollBar messages }
            cmScrollerChanged   = 60;  { sprava pre sb o zmene polohy             }
            cmScrollerStatus    = 61;  { ziadost o stav sc (lo,hi,top,... ) od sb }
            cmScrollBarClicked  = 62;  { zmenit polohu vypisu podla ScrollBaru    }

            cmScrollItemClicked = 63;  { item kliknuta }
            cmScrollItemEntered = 64;  { (kbEnter and pos_en }

            cmScrollEnable      = 65;


          { TMenu messages }
            cmLeftMenu          = 70;  { otvor radsej lave menu   }
            cmRightMenu         = 71;  { otvor radsej prave menu  }
            cmAltMenu           = 72;
            cmChangeActItem     = 73;  { nastavenie aktualneho riadku na stlacenu polozku }
            cmSwitchPressed     = 74;  { interna sprava o zopnuti prepinaca }
            cmRunSubMenu        = 75;
            cmMainMenuRedraw    = 79;
            cmMenuRedraw        = 80;


          { TEdit messages }
            cmEditConfirm       = 90;  { potvrdenie obsahu formulara }
            cmEditRefresh       = 91;  { prepisanie obsahu formulara }
            cmEditDelete        = 92;  { odmazanie  obsahu formulara }

            cmItemInsert        = 98;
            cmItemDelete        = 99;



    const { --------------------------------- }
          { systemove prikazy                 }
          { --------------------------------- }
            cmClock             = 101;
            cmTimeSet           = 102;


            cmAbout             = 200;
            cmAboutUpgrade      = 201;


            cmRefresh           = 205;
            cmProgramStatus     = 206;
            cmGraphModeChanged  = 207; { zmena grafickeho modu }
            cmAboutWin          = 208;

            cmConfigChanged     = 210;


            cmList              = 220;
            cmVyber             = 221;
            cmNajdi             = 222;
            cmZobraz            = 223;
            cmArchiv            = 224;
            cmPrint             = 230;
            cmEdit              = 231;
            cmSend              = 232;
            cmExport            = 233;
            cmBackup            = 234;
            cmDelete            = 235;
            cmUsed              = 236;
            cmF11               = 240;


            cmPRN_TEST          = 408;
            cmPRN_TEST1         = 409;
            cmPRN_SETUP         = 410;
            cmPRN_STATUS        = 411;
            cmPRN_ERROR         = 412;


            cmSERVER            = 500;
            cmSERVER_STATUS     = 501;
            cmSERVER_BCK        = 502;


            cmTRASY0            = 904;
            cmTRASY1            = 905;
            cmNODES_NASTAVENIE  = 906;


            cmA36YKA            = 900;
            cmDEBUG             = 999;


            cmCFG_SAVE          = 5100;
            cmCFG_SAVE_ACT      = 5101;
            cmCFG_SAVE_OTH      = 5102;

            cmCFG_READ          = 5103;

            cmCFG_SAVED         = 5105;
            cmCFG_LOADED        = 5106;

            cmCFG_DEFAULT       = 5108;
            cmCFG_USER          = 5109;
            cmCFG_USER_lo       = 5110;
            cmCFG_USER_hi       = 5160;


            cmSYSTEM_VOLBY      = 5500;
            cmSYSTEM_PREMENNE   = 5501;
            cmNASTAV_SPRACOVANIE = 5502;
            cmNASTAV_ZOBRAZENIE = 5503;


            cmSTATUS_CHG        = 5610;


            cmVSEOBECNY         = 5900;
            cmsVSEOBECNYCH      = 98;
            cmOTHER             = 5999; { ostatnie commandy }


implementation

end.