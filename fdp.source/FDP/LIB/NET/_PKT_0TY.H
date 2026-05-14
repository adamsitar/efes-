   {$IFDEF DATA_BIN}

     { Povodne kdovanie pokryva intervaly

         -  100 - 1500      spravy LPS
         - 2100 - 2200      spravy AFTN
         - 9000 -           diagnostika
         - 9900 - 9999      spravy MET
         - >50000           spravy pre RDP
     }

     const   spr0_SPR           = 72;
             ack0_SPR           = 73;

             spr0_SPR_LAM       = 74;
             ack0_SPR_LAM       = 75;


             spr0_DATAlo        = 100;
             spr0_DATAhi        = 9899;

             {$IFDEF FPLC_L}
              spr0_cFPL         = 118;
              ack0_cFPL         = 119;
             {$ELSE}
              spr0_cFPL         = 102;
              ack0_cFPL         = 103;
             {$ENDIF}

             spr0_mFPL          = 120;       { plany a potvrdenia }
             ack0_mFPL          = 121;

             {spr0_REQ_ACT       = 200;
             spr0_REQ_MES       = 202;
             spr0_REQ_EST       = 204;}


             spr0_ZAM           = 310;
             ack0_ZAM           = 311;


             spr0_PRZ           = 350;
             ack0_PRZ           = 351;

             spr0_PRN           = 352;
             ack0_PRN           = 353;

             spr0_PRN_VLIS      = 500;
             ack0_PRN_VLIS      = 501;

             spr0_PRS           = 360;
             ack0_PRS           = 361;


             spr0_DVZ           = 370;
             ack0_DVZ           = 371;

             spr0_QGO           = 380;
             ack0_QGO           = 381;


             {spr0_RPL           = 1100;
             ack0_RPL           = 1101;}

             spr0_PLN           = 1200;
             ack0_PLN           = 1201;

             spr0_FPL4          = 1300;
             ack0_FPL4          = 1301;



      {const  spr0_AFTN_SEND     = 2100;

             spr0_AFTN_NEW      = 2102;
             spr0_AFTN_PRD      = 2104;
             spr0_AFTN_ED       = 2106;
             spr0_AFTN_DEL      = 2108;

             spr0_AFTN_ERR      = 2120;
             spr0_AFTN_ERR_ED   = 2122;
             spr0_AFTN_ERR_DEL  = 2124;

             spr0_AFTN_TLG      = 2130;

             spr0_AFTN_PLN      = 2140;

             spr0_AFTN_DEL_ITEM  = 2150;
             spr0_AFTN_DEL_ITEMS = 2152;}


      const  spr_METEORlo       = 9900;
             spr_METEORhi       = 9911;

             spr0_SYN           = 9900;
             ack0_SYN           = 9901;
             spr0_MET           = 9910;
             ack0_MET           = 9911;
             spr0_MRL           = 9912;
             ack0_MRL           = 9913;


      const  spr0_RDPlo         = 50000;
             spr0_RDPhi         = 50302;

             spr0_SECTOR_PASSWORD = 50000;

             spr0_RDP_cFPL      = 50210;
             ack0_RDP_cFPL      = spr0_RDP_cFPL + 1;

             spr0_RDP_mFPL      = 50212;
             ack0_RDP_mFPL      = spr0_RDP_mFPL + 1;

             spr0_RDP_EST_DEL   = 50222;
             ack0_RDP_EST_DEL   = spr0_RDP_EST_DEL + 1;

             spr0_RDP_PRS       = 50300;
             ack0_RDP_PRS       = spr0_RDP_PRS + 1;

             spr0_RDPNX_PRS     = 50304;
             ack0_RDPNX_PRS     = 50305;
             spr0_PRS_FDA       = spr0_RDPNX_PRS;


             spr0_RDP_PRS_DEL   = 50302;
             ack0_RDP_PRS_DEL   = spr0_RDP_PRS_DEL + 1;


             spr0_RDP_ZAM       = 50310;
             ack0_RDP_ZAM       = spr0_RDP_ZAM + 1;

             spr0_RDP_ZAM_DEL   = 50312;
             ack0_RDP_ZAM_DEL   = spr0_RDP_ZAM_DEL + 1;


             spr0_RDP_A         = 50214;
             ack0_RDP_A         = spr0_RDP_A + 1;

             spr0_RDP_UA        = 50216;
             ack0_RDP_UA        = spr0_RDP_UA + 1;

             spr0_RDP_H         = 50218;
             ack0_RDP_H         = spr0_RDP_H + 1;

             spr0_RDP_UH        = 50220;
             ack0_RDP_UH        = spr0_RDP_UH + 1;
   {$ENDIF}