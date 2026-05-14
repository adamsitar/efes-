function NETmsg(err: word): PChar;
   begin
    {$IFDEF SLOVAK}
      case err of
         netBAD_ADDR        : NETmsg:= 'Nezn ma adresa.';
         netSELF_ADDR       : NETmsg:= 'S m sebe?.';
         netTIME_OUT        : NETmsg:= 'Spr va nebola potvrden .';
         netNOT_INITIALIZED : NETmsg:= 'Neinicializovan  sieŸ.';
         netNOT_TrasaOK     : NETmsg:= 'Stanica neodpoved .';

         netBRIDGE_MIS      : NETmsg:= 'Nedefinovanì alebo nepristupnì bridge.';
         netNOT_SENDED      : NETmsg:= 'Spr va nebola odoslan .';
         netNOT_BUFFER      : NETmsg:= 'Nedostatok pam„te pre spracovanie paketu.';

         ipxNOT_INITIALIZED : NETmsg:= 'Neinicializovan  sieŸ.';            { neinicializovana }
         ipxNOT_CONNECTED   : NETmsg:= 'Stanica nie je pripojen  v LAN.';   { nepripojeny uzol }
         ipxBAD_ADDR        : NETmsg:= 'Nezn ma adresa v LAN.';
         ipxNOT_TrasaOK     : NETmsg:= 'Stanica v LAN neodpoved .';
         ipxNOT_BridgeOK    : NETmsg:= 'Komunika‡n˜ po‡¡ta‡ neodpoved .';

         x25NOT_INITIALIZED : NETmsg:= 'Neinicializovan  sieŸ X25.';             { neinicializovana }
         x25NOT_CONNECTED   : NETmsg:= 'Stanica nie je pripojen  do X25.';
         x25BAD_ADDR        : NETmsg:= 'Nezn ma adresa v X25.';
         x25NOT_CALL        : NETmsg:= 'Spojenie X25 bolo odmietnut‚.';

         x25BRIDGE_NOT_CONNECTED : NETmsg:= 'Komunika‡n˜ po‡¡ta‡ odpojen˜.';

         rtrBAD_ADDR        : NETmsg:= 'Nezn ma adresa pre protokol routera.';
         netADDR_DUPL       : NETmsg:= 'Duplicitn  adresa.'

         else NETmsg:= 'Chyba v komunik cii.';
      end;
    {$ENDIF}

    {$IFDEF CZECH}
      case err of
         netBAD_ADDR        : NETmsg:= 'Nezn ma adresa.';
         netSELF_ADDR       : NETmsg:= 'S m sobˆ.';
         netTIME_OUT        : NETmsg:= 'Zpr va nebyla potvrzena.';
         netNOT_INITIALIZED : NETmsg:= 'Neinicializovan  s¡Ÿ.';
         netNOT_TrasaOK     : NETmsg:= 'Stanice neodpov¡d .';

         netBRIDGE_MIS      : NETmsg:= 'Nedefinovanì nebo nep©¡stupnì bridge.';
         netNOT_SENDED      : NETmsg:= 'Zpr va nebyla odeslan .';
         netNOT_BUFFER      : NETmsg:= 'Nedostatek pamˆti pro zpracov n¡ paketu.';

         ipxNOT_INITIALIZED : NETmsg:= 'Neinicializovan  s¡Ÿ.';          { neinicializovana }
         ipxNOT_CONNECTED   : NETmsg:= 'Stanice nen¡ p©ipojen  v LAN.';  { nepripojeny uzol }
         ipxBAD_ADDR        : NETmsg:= 'Nezn ma adresa v LAN.';
         ipxNOT_TrasaOK     : NETmsg:= 'Stanice v LAN neodpov¡d .';
         ipxNOT_BridgeOK    : NETmsg:= 'Komunika‡n¡ po‡¡ta‡ neodpov¡d .';

         x25NOT_INITIALIZED : NETmsg:= 'Neinicializovan  s¡Ÿ X25.';             { neinicializovana }
         x25NOT_CONNECTED   : NETmsg:= 'Stanice nen¡ p©ipojena do X25.';
         x25BAD_ADDR        : NETmsg:= 'Nezn ma adresa v X25.';
         x25NOT_CALL        : NETmsg:= 'Spojen¡ X25 bylo odm¡tnuto.';

         x25BRIDGE_NOT_CONNECTED : NETmsg:= 'Komunika‡n¡ po‡¡ta‡ odpojen.';

         rtrBAD_ADDR        : NETmsg:= 'Nezn ma pro protokol routru.';
         netADDR_DUPL       : NETmsg:= 'Duplicitn  adresa.'

         else NETmsg:= 'Chyba v komunikaci.';
      end;
    {$ENDIF}

    {$IFDEF ENGLISH}
      case err of
         netBAD_ADDR        : NETmsg:= 'Unknown address.';
         netSELF_ADDR       : NETmsg:= 'Own address.';
         netTIME_OUT        : NETmsg:= 'Message not accepted.';
         netNOT_INITIALIZED : NETmsg:= 'Network not initialized.';
         netNOT_TrasaOK     : NETmsg:= 'Workstation doesn`t respond.';

         netBRIDGE_MIS      : NETmsg:= 'Undefined or unreacheable bridge.';
         netNOT_SENDED      : NETmsg:= 'Data not sended.';
         netNOT_BUFFER      : NETmsg:= 'Not enough memory to process the packet.';

         ipxNOT_INITIALIZED : NETmsg:= 'LAN not initialized.';

         ipxNOT_CONNECTED   : NETmsg:= 'Workstation is not connected to LAN.';
         ipxBAD_ADDR        : NETmsg:= 'Unknown LAN address.';
         ipxNOT_TrasaOK     : NETmsg:= 'LAN workstation doesn`t respond.';
         ipxNOT_BridgeOK    : NETmsg:= 'Communication computer doesn`t respond.';

         x25NOT_INITIALIZED : NETmsg:= 'X25 network is not initialized.';             { neinicializovana }
         x25NOT_CONNECTED   : NETmsg:= 'Workstation is not connected to X25.';
         x25BAD_ADDR        : NETmsg:= 'Unknown X25 address.';
         x25NOT_CALL        : NETmsg:= 'X25 call was not accpeted.';

         x25BRIDGE_NOT_CONNECTED : NETmsg:= 'Communication computer disconnected.';

         rtrBAD_ADDR        : NETmsg:= 'Unknown address for router protocol.';
         netADDR_DUPL       : NETmsg:= 'Error in the adress assigning.'


         else NETmsg:= 'NET error.';
      end;
    {$ENDIF}

    {$IFDEF PCTCP}
     if (err >= net_TCP_IP) and (err <= net_TCP_IP+max_neterr_list) then NETmsg:= neterr_list[err-net_TCP_IP]
    {$ENDIF}
   end; { NETmsg }
