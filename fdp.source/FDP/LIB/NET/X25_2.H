     type  P_X25net  = ^T_X25net;
           T_X25net  = object

            {$IFDEF _X25}
             {$IFDEF AdCOM2} (T_AdCOM) {$ENDIF}
            {$ENDIF}

              INITIALIZED : bool;
              CONNECTED   : bool;                 { indikacia pripojenia do siete X.25     }
              QUE_FULL    : bool;

              {$IFDEF X25_BUFFER}
               input_ptr  : PX25_INPUT_BUFFER;    { vstupny buffer pre paket               }
               input_top  : PX25_INPUT_BUFFER;    { smernik na prvy paket vo vstup.fronte  }
               output_ptr : PX25_OUTPUT_BUFFER;   { vystupny buffer pre vys.paket          }
               output_top : PX25_OUTPUT_BUFFER;   { smernik na prvy paket vo vystup.fronte }
              {$ELSE}
               in_buff    : PBuffer;
               {out_buff   : PBuffer;}
              {$ENDIF}

              p_enabled_SVC : pointer; { TBFunc_enabled_SVC_X25 - ext fcia pre ENABLED_CHANNEL  }
              p_receive_pkt : pointer; { TProc_receive_pkt_X25  - ext fcia pre prevzatie paketu }
              p_archive_operation : PProc_s;


              constructor Init;
              destructor  Done;  virtual;

              public
              function    CONNECT : bool;
              procedure   DISCONNECT;
              function    RESET_BOARD: bool;

              public
              function    OPEN_CHANNEL  (_to,_from : TX25name; user_data: Pbytes; user_len: U16BIT): S16BIT;
              procedure   CLOSE_CHANNEL (CHANNEL : S16BIT; user_data: Pbytes; user_len: U16BIT; cause: U8BIT);
              function    NULL_CHANNEL  (CHANNEL : S16BIT): bool;

              procedure   OPEN_SVCs;
              {procedure  CLOSE_SVCs;}

              function    is_PACKET: bool;
              function    read_PACKET    (var PACKET : X25_INPUT_BUFFER): bool;
              function    receive_PACKET (var PACKET : X25_INPUT_BUFFER): bool;

              function    send_DATA      (_to,_from: TX25name; size: word; buff: pointer): int;
              function    send_PACKET    (PACKET : X25_OUTPUT_BUFFER): bool;
              procedure   send_PACKETs;


              private
              function    receive_CALL    (PACKET : X25_INPUT_BUFFER): S16BIT;
              function    receive_SERVICE (PACKET : X25_INPUT_BUFFER): S16BIT;

             {$IFDEF _X25} {$IFDEF X25_BUFFER}
              function    PutPacketToOutputQueue  (PACKET : X25_OUTPUT_BUFFER): bool;
              function    GetPacketFromOutputQueue(var PACKET : X25_OUTPUT_BUFFER): bool;
             {$ENDIF} {$ENDIF}
           end;
