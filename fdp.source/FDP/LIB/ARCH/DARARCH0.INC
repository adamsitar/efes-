{ ---------------------------------------- }
{  hlavna slucka                           }
{ ---------------------------------------- }

var  save_packet : TDARpkt;
     SaveMain    : TProc;

procedure check_DAR; far;
    var   fn    : string;
          ext   : string[4];
          pocet : int;
    const semaphor1 : bool= false;
          semaphor2 : bool= false;
    begin
      if @SaveMain<>nil then SaveMain;

      if not archive_DAR then Exit;

    { subor s nahravkou }
      if (recorded_in_hour<>hour) and (not semaphor1) then
         begin
           semaphor1:= true;
           if DAR_name<>'' then close__DAR_file(true);
         { Delay(1000); }
           recorded_in_hour:= hour;  { musi byt az za close }
           fn:= get_ARCHfn(min);
           pocet:= GetNmbOfFiles(path_DAR+fn+'.'+extDAR);
           if pocet>0 then ext:= '.D'+inttostr(sec,2,0) else ext:= '.'+extDAR;
           DAR_name:=  path_DAR + fn + ext;
           Assign (DAR_file,DAR_name);
           Rewrite(DAR_file,1);
           SaveFileHeader(DAR_file, true,0,0);
           if save_plans<>nil then Tproc(save_plans);
           semaphor1:= false
         end;

    { data do subora    }
      if (DARbuff<>nil) and (DARbuff^.is) and (not semaphor2) then
         begin
           semaphor2:= true;
           if read_DARpacket(save_packet) then
              begin
                {$IFDEF DEBUG}
                 { if writeln_DAR then
                      MainApp^.writeln_(@save_packet.data,save_packet.header.DataLength, cl_DAR, 'ú ',writeln_DAR_utc);
                 }
                {$ENDIF}
                SaveRecord(DAR_file, true, save_packet.header,save_packet.data)
              end;
           semaphor2:= false
         end;
    end;


var SaveExit: pointer;

procedure done_DAR; far;
    begin
      if DARbuff=nil then Exit;

      while DARbuff^.is do check_DAR;
      close__DAR_file(false);
      if DARbuff<>nil then dispose(DARbuff,done);
      DARbuff:= nil;

      ExitProc:= SaveExit
    end;

procedure init_DAR(_save_plans: pointer);
   var    i: int;
   begin
     save_plans:= _save_plans;
     if (DAR_buff_size=0) or (DARbuff<>nil) then Exit;

     ThisNetwork := $01;
     EDD_Node    := $09{IPXnode};
     EDD_Address := (ThisNetwork shl 8) or EDD_Node;
     ThisNetworkZeroAddress := (ThisNetwork shl 8) or $00;
     ThisNetworkBroadcastAddress := (ThisNetwork shl 8) or $FF;

     with SaveStrip do
       begin
         Tick := 0;
         FromNode := EDD_Address;
         ToNode   := ThisNetworkZeroAddress;
         DataLength := 0;
       end;

     with SaveRLI do
       begin
         Tick := 0;
         FromNode := ThisNetworkBroadcastAddress;
         ToNode   := ThisNetworkZeroAddress;
         DataLength := 0;
       end;

     DARbuff:= New(PBuffer,Init(DAR_buff_size,sizeof(TDARpkt), false));
     SaveExit:= ExitProc;
     ExitProc:= @done_DAR;

     SaveMain:= ACheckProcessesA;
     ACheckProcessesA:= check_DAR
   end;
