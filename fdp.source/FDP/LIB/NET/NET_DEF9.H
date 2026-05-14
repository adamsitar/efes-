     const { chybove kody - NET }
            netOVERFLOW        = -1;

            netRES_OK          = 0;
            netADDR_OK         = 1;
            netACK_OK          = 2;
            netTIME_OUT        = 3;

            netNOT_INITIALIZED = 4;
            netBAD_ADDR        = 5;
            netSELF_ADDR       = 6;
            netNOT_TrasaOK     = 7;
            netNOT_SEND        = 8;
            netBRIDGE_MIS      = 9;

            netNOT_SENDED      = 11;
            netNOT_BUFFER      = 18;
            netERROR           = 19;


     const { chybove kody - IPX }
            ipxRES_OK          = 20;

            ipxNOT_INITIALIZED = 24;   { neinicializovana }
            ipxNOT_CONNECTED   = 25;   { nepripojeny uzol }
            ipxBAD_ADDR        = 26;

            ipxNOT_TrasaOK     = 27;
            ipxNOT_SendOK      = 28;
            ipxNOT_SENDed      = 29;

            ipxNOT_BridgeOK    = 30;


     const { chybove kody - X25 }
            x25RES_OK          = 40;

            x25RES_FAIL        = 43;
            x25NOT_INITIALIZED = 44;   { neinicializovana }
            x25NOT_CONNECTED   = 45;
            x25BAD_ADDR        = 46;

            x25NOT_CALL        = 47;
            x25NOT_CLOSED      = 48;
            x25BAD_OPEN        = 49;

            x25BRIDGE_NOT_CONNECTED = 50;


     const { chybove kody - RTR }
            rtrBAD_ADDR        = 66;
            netADDR_DUPL       = 70;


     const { posun kodov pri komunikacii TCP_IP cez modul NET }
            net_TCP_IP         = 100;
