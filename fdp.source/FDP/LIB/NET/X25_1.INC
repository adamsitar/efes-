{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                        €
€  INIT, DONE                                            €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor T_X25net.Init;
      var   net_error : s16bit;
      begin
       {$IFDEF _X25}
         inherited Init;
       {$ENDIF}
       {$IFDEF X25_BUFFER}
         input_ptr := nil; input_top := nil;
         output_ptr:= nil; output_top:= nil;
       {$ELSE}
         in_buff := nil;
         {out_buff:= nil;}
       {$ENDIF}

        p_enabled_SVC := nil;
        p_receive_pkt := nil;
        p_archive_operation := nil;

        INITIALIZED:= false;
        CONNECTED:= false; QUE_FULL:= false;
        CONNECT   { pripojenie sa do siete }
      end; { Init }


destructor T_X25net.Done;
     begin
       DISCONNECT;                              { Udàl† taky CLOSE_SVCs, v°® vole ? }
       {$IFDEF X25_BUFFER}
         if output_top <> nil then dispose(output_ptr);
         if input_top  <> nil then dispose(input_ptr);
       {$ELSE}
         if in_buff <>nil then begin Dispose(in_buff,Done); in_buff:= nil end;
         {if out_buff<>nil then begin Dispose(out_buff,Done); out_buff:= nil end;}
       {$ENDIF}
       {$IFDEF _X25}
         inherited Done
       {$ENDIF}
     end; { Done }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                        €
€  CONNECT, DISCONNECT                                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{
 ˙
}
function T_X25net.CONNECT: bool;
   var   net_error : s16bit;
   begin
    {$IFDEF _X25}
     {$IFNDEF _X25_NOINIT}
       net_error:= _GO(0);
       INITIALIZED:= net_error=0;
       if not INITIALIZED then RunError('Cannot initialize X25 board.');
       {$IFDEF DEBUG} Delay(1000) {$ELSE} Delay(5000) {$ENDIF};
       CONNECTED:= RESET_BOARD;
       CONNECT:= (net_error = 0) and CONNECTED;
       if X25node>-1 then X25nodes^.NODE^[X25node]^.OPEN:= true
     {$ELSE}
       INITIALIZED:= true;
       CONNECTED:= true;
       CONNECT:= true;
     {$ENDIF}
    {$ELSE}
      INITIALIZED:= false;
      CONNECTED:= false;
      CONNECT:= false
    {$ENDIF}
   end;

{
 ˙
}
procedure T_X25net.DISCONNECT;
    var   i,net_error : s16bit;
    begin
     {$IFDEF _X25} {$IFNDEF _X25_NOINIT}
      for i:= 0 to X25nodes^.top do CLOSE_CHANNEL(X25nodes^.NODE^[i]^.CHAN,nil,0,0);
      if (X25node>-1) then X25nodes^.NODE^[X25node]^.OPEN:= false; { indikacia, ze som odpojeny zo siete X.25 }
      net_error:= _END(0);                                         { odpojenie sa zo siete }
      CONNECTED:= false
     {$ENDIF} {$ENDIF}
    end; { DISCONNECT }

{
 ˙ RESET_BOARD, vymaze vsetky pakety z karty az po paket od siete X.25 L3S_SIGNAL cause:207
}
function   T_X25net.RESET_BOARD: bool;
   {$IFDEF _X25}
    var    DDESC       : DATA_DESC;
           ddesc_data  : X25_PACKET_ARRAY;
           PACKET      : X25_INPUT_BUFFER;
           net_error   : s16bit;
           start_ticks : long;
           _err        : bool;
    label  X;
   {$ENDIF}
    begin
      RESET_BOARD:= false;
      _err:= false;
     {$IFDEF _X25} {$IFNDEF _X25_NOINIT}
       fillchar(PACKET,sizeof(PACKET),0);
       start_ticks:= getticks;
       while (PACKET.packet<>L3S_SIGNAL) and (PACKET.cause<>LINE_RESTART) do
         begin
           net_error:= _GCMD(@DDESC);
           if net_error=0 then
              begin
                DDESC.line:= 0;
                DDESC.data:= @ddesc_data;
                DDESC.info.length:= sizeof(ddesc_data);
                net_error:= _READCH(@DDESC);
                if net_error = 0 then
                  begin
                    PACKET.line  := DDESC.line;
                    PACKET.chan  := DDESC.chan;
                    PACKET.size  := minimum(DDESC.info.length,sizeof(PACKET.size));
                    PACKET.packet:= DDESC.info.packet_type;
                    PACKET.QMD   := DDESC.info.qmd_bits;
                    PACKET.cause := DDESC.info.cause;
                    PACKET.diag  := DDESC.info.diag;
                    move(DDESC.data^,PACKET.data,PACKET.size)
                  end
               end;
           if (PACKET.packet=L3S_SIGNAL) and (PACKET.cause in [LINK_ERROR,CRASH]) then
              RunError('Cannot to initialize X25 link.');
           if TimeOut(start_ticks, getticks, X25_INIT_TIME_OUT) then { or (PACKET.packet=0) and (PACKET.cause=0) }
              begin
               {$IFDEF _X25_CONNECT_TIME_OUT}
                 RunError ('X25 connect timeout. Check driver or modem.')
               {$ELSE}
                 MessError('X25 connect timeout. Not connected yet', true,_err);
               {$ENDIF}
                goto X
              end
         end;
       if _err then writeln;
       RESET_BOARD:= true;
       X: receive_SERVICE(PACKET)
     {$ENDIF} {$ENDIF}
    end; { RESET_BOARD }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                        €
€  OTVORENIE/Z... KANALOV (SVC)                          €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{
 ˙OPEN_CHANNEL

   -  =0 -> spojenie nebolo vytvorene
     <>0 -> vracia cislo kanalu na ktorom bolo vytvorene spojenie
     =-1 -> uz je otvoreny kanal ale este nepotvrdil spojenie
}

function  T_X25net.OPEN_CHANNEL(_to,_from : TX25name; user_data: Pbytes; user_len: U16BIT): S16BIT;
   {$IFDEF _X25}
    var   DDESC      : DATA_DESC;
          CDESC      : CALL_DESC;
          ddesc_data : X25_PACKET_ARRAY;
          CHANNEL    : s16bit;
          net_error  : s16bit;
   {$ENDIF}
    begin
     {$IFDEF _X25}
      OPEN_CHANNEL:= -1;  { priznak, ze kanal je prave otvarany }
      if is_open_X25channel(_to,CHANNEL) then OPEN_CHANNEL:= CHANNEL  { Zistit, ci je s danou stanicou otvoreny kanal }
      else if CHANNEL<>0 then  { uz bol bol vyslany CALL_REQ ale este neprisiel CALL_ACC }
      else begin
             FillChar(DDESC,sizeof(DDESC),0);
             DDESC.data:= @ddesc_data;

             FillChar(CDESC,sizeof(CDESC),0);
             CDESC.calld_len:= length(_to);   _X25name_to_adr(_to,   CDESC.calld_adr);
             CDESC.callg_len:= length(_from); _X25name_to_adr(_from, CDESC.callg_adr);
             if (user_data<>nil) and (user_len>0) then
                begin
                  CDESC.usr_len:= Minimum(user_len,sizeof(CDESC.usr_data));
                  Move(user_data^,CDESC.usr_data,CDESC.usr_len)
                end;
             DDESC.info.length:= CONV_TO_CPKT(CDESC,ddesc_data); { Convert the CDESC structure to CCITT format }

             net_error:= _OPEN(@DDESC);
             if net_error<>0 then OPEN_CHANNEL:= 0
             else begin
                    set_chan(_to,DDESC.chan);
                    OPEN_CHANNEL:= DDESC.chan
                  end
         end
     {$ELSE}
      OPEN_CHANNEL:= 0
     {$ENDIF}
   end; { OPEN_CHANNEL }

{
 ˙ Logicky zapisa zrusenia zaznamu o spojeni, zaznam do struktury X25modes...
}
function T_X25net.NULL_CHANNEL(CHANNEL : S16BIT): bool;
  var    i : int;
  begin
   {$IFDEF _X25}
    i:= 0; while (i<=X25nodes^.top) and (X25nodes^.NODE^[i]^.CHAN<>CHANNEL) do inc(i);
    NULL_CHANNEL:= i<=X25nodes^.top;
    if i>X25nodes^.top then Exit;

    X25nodes^.NODE^[i]^.CHAN:= 0;
    X25nodes^.NODE^[i]^.OPEN:= false;
    X25nodes^.NODE^[i]^.STATUS:= 0
   {$ELSE}
    NULL_CHANNEL:= false
   {$ENDIF}
  end; { NULL_CHANNEL }


{ ˙ CLOSE_CHANNEL - uzatvori kanal - vysle CLEAR RESET
}
procedure  T_X25net.CLOSE_CHANNEL(CHANNEL: S16BIT; user_data: Pbytes; user_len: U16BIT; cause: U8BIT);
   {$IFDEF _X25}
    var     DDESC      : DATA_DESC;
            CDESC      : CALL_DESC;
            ddesc_data : X25_PACKET_ARRAY;
            net_error  : s16bit;
   {$ENDIF}
   begin
    {$IFDEF _X25}
     if CHANNEL=0 then Exit;

     FillChar(DDESC,sizeof(DDESC),0);
     DDESC.line:= 0;
     DDESC.chan:= CHANNEL;
     DDESC.data:= @ddesc_data;
     DDESC.info.cause:= cause;
     if (user_data<>nil) and (user_len>0) then
        begin
          FillChar(CDESC,sizeof(CDESC),0);
          CDESC.usr_len:= Minimum(user_len,sizeof(CDESC.usr_data));
          Move(user_data^,CDESC.usr_data,CDESC.usr_len);
          DDESC.info.length:= CONV_TO_CPKT(CDESC,ddesc_data)
        end
     else DDESC.info.length:= 0;
     net_error:= _CLOSE(@DDESC); { zrusenie spojenia so stanicou na kanali CHANNEL     }
     NULL_CHANNEL(CHANNEL)       { nastavenie hodnoty 0 v struc. X25nodes^.NODE^.CHAN  }
    {$ENDIF}
   end; { CLOSE_CHANNEL }

{ ˙
}
procedure  T_X25net.OPEN_SVCs;
    var    i : int;
    begin
     {$IFDEF _X25}
      for i:= 0 to nodesX25-1 do
        with X25nodes^.NODE^[i]^ do
          begin
            if (ADR = X25nodes^.NODE^[X25node]^.ADR) or (CHAN <> 0) then continue;
            CHAN:= OPEN_CHANNEL(ADR,X25nodes^.NODE^[X25node]^.ADR, nil,0);
            if CHAN = -1 then CHAN:= 0
          end
     {$ENDIF}
    end; { OPEN_SVCs }

{ ˙

procedure  T_X25net.CLOSE_SVCs;
    var    DDESC      : DATA_DESC;
           ddesc_data : X25_PACKET_ARRAY;
           net_error  : s16bit;
           i          : int;
    begin
      for i:= 0 to nodesX25_-1 do
        if (X25nodes^.NODE^[i]^.CHAN <> 0) then
           begin
             CLOSE_CHANNEL(X25nodes^.NODE^[i]^.CHAN)
           end
    end;  CLOSE_SVCs }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                        €
€  ODOSLANIE/PRIJATIE DAT                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{ ˙ pater, ze _to,_from musa buc spravne !
}
function  T_X25net.send_DATA(_to,_from: TX25name; size: word; buff: pointer{; _send: bool}): int;
   {$IFDEF _X25}
    var    PACKET  : X25_OUTPUT_BUFFER;
           CHANNEL : s16bit;
   {$ENDIF}
   begin
     {$IFDEF _X25}
       if (not is_open_X25channel(_to,CHANNEL)) and (CHANNEL=0) then
          begin
            CHANNEL:= OPEN_CHANNEL(_to,_from, nil,0);
            if (CHANNEL=0) then
               begin
                 send_DATA:= x25NOT_CALL;
                 Exit
               end
            else if (CHANNEL=-1) then
                 begin
                   send_DATA:= x25NOT_CONNECTED;
                   Exit
                 end
          end;

       PACKET.chan := CHANNEL;
       PACKET.adr  := _to;
       PACKET.next := nil;
       PACKET.ticks:= GetTicks;
       PACKET.size := Minimum(size,sizeof(PACKET.data));
       Move(buff^,PACKET.data,size);

       {$IFDEF X25_BUFFER}
         if    ({_send and} send_PACKET(PACKET))
            or ({(not _send) and} PutPacketToOutputQueue(PACKET))
               then send_DATA:= x25RES_OK
         else send_DATA:= x25RES_FAIL
       {$ELSE}
         if send_PACKET(PACKET) then send_DATA:= x25RES_OK
         else send_DATA:= x25RES_FAIL
       {$ENDIF}

     {$ELSE}
       send_DATA:= x25RES_OK
     {$ENDIF}
   end;

{
 ˙ odosle paket do karty
}
function  T_X25net.send_PACKET(PACKET : X25_OUTPUT_BUFFER): bool;
   {$IFDEF _X25}
    var    DDESC     : DATA_DESC;
           CHANNEL   : s16bit;
           net_error : s16bit;
   {$ENDIF}
   begin
    {$IFDEF _X25}
     send_PACKET:= false;

     if PACKET.chan=0 then
        begin
          if is_open_X25channel(PACKET.adr,CHANNEL) then PACKET.chan:= CHANNEL;
          if (PACKET.chan=0) and (TimeOut(PACKET.ticks,GetTicks,X25_RESEND_TIME_OUT)) then Exit;
          {$IFDEF X25_BUFFER}
            send_PACKET:= PutPacketToOutputQueue(PACKET);
          {$ENDIF}
          Exit
        end;

     FillChar(DDESC,sizeof(DATA_DESC),0);
     DDESC.chan:= PACKET.chan;
     DDESC.data:= @PACKET.data;
     DDESC.info.length:= PACKET.size;

     net_error:= EWOULDBLOCK;         { Pozor ! slucka, vole }
     while net_error = EWOULDBLOCK do { Pokial nebolo uspesne vysielanie, tak vysle znova }
       begin
         net_error:= _WRITE(@DDESC)
       end;

     send_PACKET:= net_error=0
    {$ELSE}
     send_PACKET:= true
    {$ENDIF}
   end; { send_PACKET }

{
 ˙ vysiela neodoslane pakety, ktore cakali na otvorenie kanala
}
procedure T_X25net.send_PACKETs;
   {$IFDEF _X25}
    var   PACKET : X25_OUTPUT_BUFFER;
          res    : bool;
   {$ENDIF}
    begin
     {$IFDEF _X25} {$IFDEF X25_BUFFER}
      if (GetPacketFromOutputQueue(PACKET)) then res:= send_PACKET(PACKET)
     {$ENDIF} {$ENDIF}
    end;


{ ------------------
   read_PACKET
  ------------------

 ˙ Funkcia precita pkt z X.25 karty, ak tam je
      output :  =0 -> data su v input^ strukture
               <>0 -> Receive_Packet=net_error
}

function  T_X25net.is_PACKET: bool;
   {$IFDEF _X25}
    var    DDESC : DATA_DESC;
   {$ENDIF}
   begin
    {$IFDEF _X25}
     is_PACKET:= _GCMD(@DDESC)=0
    {$ELSE}
     is_PACKET:= false
    {$ENDIF}
   end;


function  T_X25net.read_PACKET(var PACKET: X25_INPUT_BUFFER): bool;
   {$IFDEF _X25}
    var    DDESC      : DATA_DESC;
           ddesc_data : X25_PACKET_ARRAY;
           net_error  : s16bit;
   {$ENDIF}
   begin
     read_PACKET:= false;

    {$IFDEF _X25}
      net_error:= _GCMD(@DDESC);
      if net_error <> 0 then Exit;

      DDESC.line:= 0;
      DDESC.data:= @ddesc_data;
      DDESC.info.length:= SizeOf(ddesc_data);

      net_error:= _READCH(@DDESC);
      if net_error = 0 then
         begin
           FillChar(PACKET,SizeOf(PACKET),0);
           PACKET.line   := DDESC.line;
           PACKET.chan   := DDESC.chan;
           PACKET.packet := DDESC.info.packet_type;
           PACKET.QMD    := DDESC.info.qmd_bits;
           PACKET.cause  := DDESC.info.cause;
           PACKET.diag   := DDESC.info.diag;
           PACKET.size   := Minimum(DDESC.info.length,sizeof(PACKET.data));
           Move(DDESC.data^,PACKET.data,PACKET.size);

           case PACKET.packet of
             CALL_REQUEST : receive_CALL(PACKET);   { poziadavka na nadviazanie spojenia }
             DATA         : read_PACKET:= receive_PACKET(PACKET);
            {INTERUPT     : read_PACKET:= receive_PACKET(PACKET);}
             else           receive_SERVICE(PACKET)
           end
         end
      else if X25_archive and (p_archive_operation<>nil) then
              begin
                TProc_s(p_archive_operation)('X25 read packet error : '+cstr(net_error,2){+init_str()});
              end
    {$ENDIF}
   end; { read_PACKET }


{
˙ Rozhodne, akym sposobom bude paket spracovany,
  ak je adresa odosielatela typu LETVIS, pusti ho na dalsie spracovanie,
  inak ho tlaci do externej fcie
}
function T_X25net.receive_PACKET(var PACKET: X25_INPUT_BUFFER): bool;
   var   i : int;
   begin
    {$IFDEF _X25}
     receive_PACKET:= true;
     if (p_receive_pkt<>nil) and (X25nodes<>nil) then with X25nodes^ do
        begin
          i:= isX25chan(PACKET.CHAN,2);
          if i>=0 then
             begin
               TProc_receive_pkt_X25(p_receive_pkt)(NODE^[i]^.adr,@PACKET.data,PACKET.size);
               receive_PACKET:= false
             end
          else if X25_archive and (p_archive_operation<>nil) then
                  begin
                    TProc_s(p_archive_operation)('X25 unknown sender : '+cstr(PACKET.CHAN,1)
                                                 +' '+init_str(@PACKET,sizeof(PACKET))
                                                );
                  end
        end
    {$ELSE}
     receive_PACKET:= false
    {$ENDIF}
   end;



{ ------------------
  ˙˙˙ receive_CALL
  ------------------
}
function  T_X25net.receive_CALL(PACKET : X25_INPUT_BUFFER): S16BIT;
  {$IFDEF _X25}
   var    CDESC      : CALL_DESC;
          DDESC      : DATA_DESC;
          ddesc_data : X25_PACKET_ARRAY;
          CHANNEL    : S16BIT;
          net_error  : S16BIT;
          adr        : TX25name;

          s: string;
          i: int;
  {$ENDIF}
  begin
   {$IFDEF _X25}
     receive_CALL:= BAD_REGISTRATION;
     if (PACKET.chan=0) then Exit;

     s:= ''; for i:= 0 to PACKET.size-1 do s:= s+chr(PACKET.data[i]);
     if p_archive_operation<>nil then TProc_s(p_archive_operation)('X25 Call received   : '+s);
     CONV_FROM_CPKT(PACKET.data,PACKET.size, CDESC);
     s:= ''; for i:= 0 to CDESC.calld_len-1 do s:= s+chr(CDESC.calld_adr[i]);
     if p_archive_operation<>nil then TProc_s(p_archive_operation)('X25 called address  : '+s);
     _X25adr_to_name(CDESC.callg_adr,CDESC.callg_len, adr);
     if p_archive_operation<>nil then TProc_s(p_archive_operation)('X25 calling address : '+adr);
     s:= ''; for i:= 0 to CDESC.usr_len-1 do s:= s+chr(CDESC.usr_data[i]);
     if p_archive_operation<>nil then TProc_s(p_archive_operation)('X25 user data...    : '+s);

    { .... ak je s volajucou stanicou otvoreny uz iny kanal, treba ho zavriet... }
     if (not is_open_X25channel(adr,CHANNEL)) and (CHANNEL<>0) then
        begin
          if p_archive_operation<>nil then TProc_s(p_archive_operation)('X25 closing channel  : '+cstr(CHANNEL,2));
          CLOSE_CHANNEL(CHANNEL,nil,0,0);
        end;

    { povolene je nadviazat spojenie len so stanicami uvedenymi v cfg }
     if (isX25adr(adr,0)=-1) then
        begin
          if p_archive_operation<>nil then TProc_s(p_archive_operation)('X25 calling address is not configured...');
          Exit
        end
     else if (isX25adr(adr,2)>-1) then
             begin
               if     (p_enabled_SVC<>nil)
                  and (not (TBFunc_enabled_SVC_X25(p_enabled_SVC)(adr, @CDESC.usr_data,CDESC.usr_len))) then
                      begin
                       {if p_archive_operation<>nil then TProc_s(p_archive_operation)('NOT CONFGIGURED SVC...');}
                       { odoslanie CLEAR_RESET }
                        if p_archive_operation<>nil then
                           TProc_s(p_archive_operation)('X25 not configured svc, closing channel...');
                        CLOSE_CHANNEL(PACKET.chan,nil,0,NO_CHANNEL_AVAIL);
                        Exit
                      end
             end;

     DDESC.line:= 0;
     DDESC.chan:= PACKET.chan;
     DDESC.data:= @ddesc_data;
     CDESC.fac_len:= 0;
     CDESC.usr_len:= 0;
     DDESC.info.length:= CONV_TO_CPKT(CDESC, ddesc_data);

     net_error:= _ACPT(@DDESC);
     if net_error=0 then set_open(adr,DDESC.chan)
     else set_not_open(adr);
     receive_CALL:= net_error
   {$ELSE}
     receive_CALL:= netBAD_ADDR
   {$ENDIF}
  end; { receive_CALL }

{
  ------------------
   receive_SERVICE
  ------------------
}

function  T_X25net.receive_SERVICE(PACKET : X25_INPUT_BUFFER): S16BIT;
   {$IFDEF _X25}
    var    CDESC  : CALL_DESC;
           POLE   : X25_PACKET_ARRAY;
           adresa : TX25name;
           uk     : s16bit;
           s      : string[1];
   {$ENDIF}
   begin
    {$IFDEF _X25}
     if X25_archive and (p_archive_operation<>nil) then
        begin
          TProc_s(p_archive_operation)('X25 service packet : '+init_str(@PACKET,sizeof(PACKET)));
        end;

     case PACKET.packet of
        L3S_SIGNAL     : begin { L3S signal len od karty }
                           receive_SERVICE:= PACKET.cause;
                           if (X25node>-1) then
                              if PACKET.cause in [CRASH,DISCONNECTED,LINK_ERRor,LINK_ERR_CTL,LINK_ERR_TXCLK] then
                                 X25nodes^.NODE^[X25node]^.OPEN:= false
                              else X25nodes^.NODE^[X25node]^.OPEN:= true;
                           if PACKET.cause in [TX_QUE_NOT_FULL,LINE_RESTART] then QUE_FULL:= false
                         end;

        L3S_ERROR      : begin
                           receive_SERVICE:= PACKET.cause;
                         end;

        CALL_ACCEPTED  : begin
                          {#1 transformacia CCITT --> CALL_DESC}
                          CONV_FROM_CPKT(PACKET.data,PACKET.size,CDESC);
                          {#2 zistit adresu odkial prisiel packet}
                          _X25adr_to_name(CDESC.calld_adr,CDESC.calld_len, adresa);
                          {#3 do struc. X25nodes zapisat cislo otvoreneho kanala}
                          set_open(adresa,PACKET.chan)
                         end;

        CLEAR_REQUEST  : begin
                           if p_archive_operation<>nil then
                              TProc_s(p_archive_operation)('Clear request received, closing '+cstr(PACKET.chan,2)+'...');
                           CLOSE_CHANNEL(PACKET.chan,nil,0,0);
                         end;

        CLEAR_CONFIRM  : begin
                           NULL_CHANNEL(PACKET.chan);
                         end;

        DIAGNOSTIC     : begin
                           CONV_FROM_CPKT(PACKET.data,PACKET.size,CDESC);
                         end;

        RESET_REQUEST  : begin
                           {sound(1200); delay(200); nosound;}
                         end;
        else begin
               {sound(2500); delay(200); nosound}
             end
      end
     {$ENDIF}
   end; { receive_SERVICE }
