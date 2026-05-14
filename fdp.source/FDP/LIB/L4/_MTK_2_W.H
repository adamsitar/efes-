         { ----------------------------
            Zakazane slova v telegrame
           ............................
         }
    const  MTK_2_DIS_WORDs = 4;
           MTK_2_DIS_WORD  : array[0..MTK_2_DIS_WORDs-1] of pchar =
                             ('ZCZC','+:+:','NNNN',',,,,');


         { ----------
            Kody
           ..........
         }
    const  MTK_CFM        = 'CFM';   { potvrdenie }
           MTK_CH         = 'CH';    { previerka  }
           MTK_COR        = 'COR';   { oprava     }
           MTK_DUPE       = 'DUPE';  { opakovane  }
           MTK_LR         = 'LR';    { posledne prijate   }
           MTK_LS         = 'LS';    { posledne odovzdane }
           MTK_MIS        = 'MIS';   { chyba              }
           MTK_MSR        = 'MSR';   { chybne zaslane     }
           MTK_QTA        = 'QTA';   { anulovane  }
           MTK_RPT        = 'RPT';   { opakujte   }
           MTK_R          = 'R';     { prijate    }
           MTK_SVC        = 'SVC';   { sluzobne   }
           MTK_NR         = 'NR';    { cislo      }
           MTK_STP        = 'STP';   { bodka      }

           MTK_CFM_R      = 'ñîå';   { potvrdenie }
           MTK_CH_R       = 'ëç';    { previerka  }
           MTK_COR_R      = 'ëéê';   { oprava     }
           MTK_DUPE_R     = 'ÑìèÖ';  { opakovane  }
           MTK_LR_R       = 'ãê';    { posledne prijate   }
           MTK_LS_R       = 'ãë';    { posledne odovzdane }
           MTK_MIS_R      = 'åàë';   { chyyba             }
           MTK_MSR_R      = 'åëê';   { chybne zaslane     }
           MTK_QTA_R      = 'ôíÄ';   { anulovane  }
           MTK_RPT_R      = 'êèí';   { opakujte   }
           MTK_R_R        = 'ê';     { prijate    }
           MTK_SVC_R      = 'ëÜñ';   { sluzobne   }
           MTK_NR_R       = 'çê';    { cislo      }
           MTK_STP_R      = 'íóä';   { bodka      }
