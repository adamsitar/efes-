{ -------------------- }
{  Init, Done          }
{ -------------------- }

constructor TIPXnode.Init(is: byte);
      var   b: byte;
      begin
        if is=0 then b:=$FF else b:= $00; FillChar(Adr,SizeOf(TEthernetAdr),b);

        Node      := is;
        Connected := false;
        pro       := X25;

        Name := '' ;
        Info := nil;

        Out_buff := nil;
        Inp_buff := nil;

       {$IFDEF IPX0}
        TrasaOK := false;
        SendOK  := true;

        test_en := false; { parameter '-' }
        tested  := false;

        to_init := 0;
        intr_semaphor := false
       {$ENDIF}
      end;

destructor TIPXnode.Done;
    begin
      if Inp_buff<>nil then Dispose(Inp_buff);
      if Out_buff<>nil then Dispose(Out_buff);
      StrDispose(Info)
    end;


{ -------------------- }
{  TimeOut, Wait       }
{ -------------------- }

{$IFDEF IPX0}

  function TIPXnode.isTimeOut: bool;
     var   T : long;
     begin
        T:= getticks;
        if TimeOut(SendTick,T,IPX__TIME_OUT) then
           begin
             isTimeOut:= true;
             TrasaOK  := false;
             SendOK   := true;
             Out_buff^.size:= 0;
             next_test:= (sec+IPX__HEARTBEAT) mod 60
           end
        else isTimeOut:= false
     end; { isTimeOut }


  procedure TIPXnode.Wait;
     begin
       while not SendOK do isTimeOut
     end; { Wait }

{$ENDIF}

(*
procedure TIPXnode.Wait;
    var   ok, time_out: bool;
    begin
      repeat
        ok:= (TrasaOK and SendOK);
        if not ok then time_out:= isTimeOut;
      until ok or time_out;
    end; { Wait }
*)


{ -------------------- }
{  Send                }
{ -------------------- }

function TIPXnode.Send(ipxSPRAVA: byte): byte;
   var   res   : byte;
         {$IFNDEF SOCKET}
         dlzka : int;
         {$ENDIF}
   begin
     if Connected {$IFNDEF SOCKET} and (ECB[0,node].InUse=0) {$ENDIF} then
        begin
         {$IFDEF IPX0}
           Wait;
           tested   := false;
           SendOK   := false;    { vysielat mozem az po nastaveni SendOK v prijimacej rutine alebo az po vyprsani TimeOut: }
           SendTick := GetTicks;
         {$ENDIF}

         {$IFDEF SOCKET}
           if ipxSPRAVA<>ipxDATA then res:= IPX_send_message(node,ipxSPRAVA)
           else res:= IPX_send_data(node,@Out_buff^.data,Out_buff^.size,0);

           if res<>0 then Send:= ipxRES_OK
           else Send:= ipxNOT_SENDed;
         {$ELSE}
           if ipxSPRAVA = ipxDATA then dlzka := Out_buff^.size
           else dlzka:= 0;

           ECB[0,node].BufSize         := 30 + dlzka;
           IPXBuf[0,node].Data         := Out_buff^.data;
           IPXBuf[0,node].PacketType   := ipxSPRAVA;

           IPXBuf[0,node].DestNet      := NulNameNet;
           IPXBuf[0,node].DestNode     := Adr;
           IPXBuf[0,node].DestSocket   := CSocket[0,node];

           SendIPX(node);
           res:= ipxRES_OK;
         {$ENDIF}

          Out_buff^.size:= 0
        end
     else res:= ipxNOT_CONNECTED;
     Send:= res
   end; { Send }

{
  vyriesit, ak size > IPX_BUFFSIZE
}
function TIPXnode.SendData(buff: pointer; size: word): byte;
   begin
     {size:= Limit(size, Low(TIPXdata), High(TIPXdata), 0);}
     Out_buff^.size:= Minimum(size,sizeof(Out_buff^.data));
     Move(buff^,Out_buff^.data,Out_buff^.size);
     SendData:= Send(ipxDATA)
   end; { SendData }


{$IFDEF IPX0}
  procedure TIPXnode.Test;
      begin
       if not (Connected and test_en) then Exit;

       {if (Connected) and (not test_en) and (not SendOK) then isTimeOut;}
        if (not SendOK) then isTimeOut
        else begin
               if {(not TrasaOK) or} (next_test = sec) then
                  if (not tested) and (Out_buff^.size=0) then
                     if SendOK then
                        begin
                          tested:= true;
                          Send(ipxTEST);
                          tested:= false;
                          next_test:= (sec+IPX__HEARTBEAT) mod 60
                        end
                     else next_test:= (sec+1) mod 60
                  else next_test:= (sec+1) mod 60  { else tested:= not(SendOK or isTimeOut) }
             end

      end; { Test }


{ -------------------- }
{  Priznaky            }
{ -------------------- }

function TIPXnode.is_intr_en: bool;
   begin
     is_intr_en:= not intr_semaphor
   end;

procedure TIPXnode.intr_sti;
   begin
     intr_semaphor:= false
   end;

procedure TIPXnode.intr_cli;
   begin
     intr_semaphor:= true
   end;

{$ENDIF}
