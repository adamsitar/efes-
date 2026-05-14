     const  {_spr_acc  = '+';
            _spr_uac  = '-';}

            _spr0_spr = 'M';    { priznak, ze ide o spravu, iny znamena potvrdzovanie sprav }
            _spr0_ack = 'A';    { potvrdenie spravy M    }
            _spr0_ine = 'I';    { potvrdenie inej spravy }

     type   Tspr_acc  = (_unreceived, _cancelled, _accepted, _unprocessed);
            Tsprs_acc = array[0..maxNODEs-1] of Tspr_acc;


     const  size_SPRtlg = size_TLGaftn;
            size_SPRmsg = 10;


     const  bminiSPR   : bool = true;

            max_SPR_am : int = 1;
            max_SPR_a_lo     = 1;
            max_SPR_a_hi     = i_tlg_adrs;      { -> 1 DBriadok }

            max_SPR_rm : int = 3;
            max_SPR_r_lo     = 0;
            max_SPR_r_hi     = size_SPRtlg+1;   { -> 1 DBriadok }


     const  SPR_ACK_WAIT : bool = {$IFDEF LAN} false {$ELSE} true {$ENDIF};  { caka na potvrdenie dorucenia spravy }


     { Pomocne vypoctove premenne
     }
     const  isSPR  : bool = false;              { sprava nebola precitana }
