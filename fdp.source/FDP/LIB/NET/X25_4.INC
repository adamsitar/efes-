{$IFDEF X25_BUFFER}

  {$IFDEF _X25}
    {
      PutPacketToOutputQueue
    }
    function  T_X25net.PutPacketToOutputQueue(PACKET : X25_OUTPUT_BUFFER): bool;
       var    pom : PX25_OUTPUT_BUFFER;
       begin
         PutPacketToOutputQueue:= memavail > sizeof(X25_OUTPUT_BUFFER);
         if memavail < sizeof(X25_OUTPUT_BUFFER) then Exit;
         if output_top = nil then
            begin
              output_ptr:= new(PX25_OUTPUT_BUFFER);
              output_ptr^:= PACKET;
              output_ptr^.next:= nil;
              output_top:= output_ptr
            end
         else begin
                pom:= new(PX25_OUTPUT_BUFFER);
                pom^:= PACKET;
                pom^.next:= nil;
                output_ptr^.next:= pom;
                output_ptr:= pom
            end;

       end; { PutPacketToOutputQueue }


    {
      GetPacketFromOutputQueue
    }
    function  T_X25net.GetPacketFromOutputQueue(var PACKET : X25_OUTPUT_BUFFER): bool;
       var    temp : PX25_OUTPUT_BUFFER;
       begin
         GetPacketFromOutputQueue:= output_top <> nil;
         if output_top = nil then Exit;
         temp:= output_top;
         PACKET:= temp^;
         output_top:= output_top^.next;
         dispose(temp)
       end; { GetPacketFromOutputQueue }
  {$ENDIF}

{$ENDIF}