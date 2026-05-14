{ ---------------------------------------------------------------- }
{  INICIALIZACIA a ODHLASENIE                                      }
{ ---------------------------------------------------------------- }


procedure IPX_init;
    var   i,b,d,e : int;
    begin
      write('Initializing IPX...  ');
      nd_buff := New(PBuffer,Init(nd_buff_size, sizeof(TIPXdpkt), false));
      rtr_buff:= New(PBuffer,Init(rtr_buff_size,sizeof(TIPXdpkt), false));

     {$IFDEF BROADCAST}
       brd_buff:= New(PBuffer,Init(brd_buff_size,sizeof(TNETBpkt), false));
       New(inp_brd_buff);
     {$ENDIF}

     {$IFDEF DEBUG_IPX};
       New(IPXinbuff);
     {$ENDIF}


      IPX_initialized:= true;

    { inicializacia socketov a obsluznych rutin ------------------ }
      GetSocketTable(IPXnode);
      for b:= 0 to maxIPX_NODEs-1 do with ECB[0,b] do
          begin
            EsrAdr  := nil;
            Compl   := 0;
            InUse   := 0;
            Socket  := CSocket[0,b];
            Adresa  := IPXnodes[b]^.Adr;
            BufCount:= 1;
            BufAdr  := @IPXBuf[0,b];
            BufSize := sizeof(TNETpkt)+30;
          end;

      for b:=0 to maxIPX_NODEs-1 do with ECB[1,b] do
          begin
            case b of
              0: EsrAdr:= Ptr(Seg(PrijInt0),Ofs(PrijInt0));
              1: EsrAdr:= Ptr(Seg(PrijInt1),Ofs(PrijInt1));
              2: EsrAdr:= Ptr(Seg(PrijInt2),Ofs(PrijInt2));
              3: EsrAdr:= Ptr(Seg(PrijInt3),Ofs(PrijInt3));
              4: EsrAdr:= Ptr(Seg(PrijInt4),Ofs(PrijInt4));
              5: EsrAdr:= Ptr(Seg(PrijInt5),Ofs(PrijInt5));
              6: EsrAdr:= Ptr(Seg(PrijInt6),Ofs(PrijInt6));
              7: EsrAdr:= Ptr(Seg(PrijInt7),Ofs(PrijInt7));
              8: EsrAdr:= Ptr(Seg(PrijInt8),Ofs(PrijInt8));
              9: EsrAdr:= Ptr(Seg(PrijInt9),Ofs(PrijInt9));
            end;
            Compl   := 0;
            InUse   := 0;
            Socket  := CSocket[1,b];
            Adresa  := IPXnodes[b]^.Adr;
            BufCount:= 1;
            BufAdr  := @IPXBuf[1,b];
            BufSize := sizeof(TNETpkt)+30;
          end;

    { otvorenie socketov ----------------------------------------- }
      GetSocketTable(IPXnode);
      for d:= 0 to 1 do
          begin
            for e:= 0 to maxIPX_NODEs-1 do SocketOpen[d,e]:= false;
            for e:= 0 to maxIPX_NODEs-1 do
                if (e<>IPXnode) and (IPXnodes[e]^.Connected) then
                   begin
                     b:= OpenSocket(d,e);
                     if b=$FE then RunError('Socket Table is Full.');
                     SocketOpen[d,e]:= true;
                   end
          end;

      {$IFDEF BROADCAST}
        {$IFDEF ARCHIVE_DAR}
          if (save_RLI<>nil) then ListenIPX(0);
        {$ELSE}
          ListenIPX(0);
        {$ENDIF}
      {$ENDIF}
      for i:= {$IFDEF BROADCAST} 1 {$ELSE} 1 {$ENDIF} to maxIPX_NODEs-1 do with IPXnodes[i]^ do
          if (i<>IPXnode) and Connected then
             begin
               ListenIPX(i);
               MessIPX(i,ipxVYZVA);
               next_test:= (sec+5+i) mod 60
             end;

      writeln('Done. IPX initialized.');
      Delay(2000)
    end; { IPX_init }


procedure IPX_done;
    var   i,j: byte;
    begin

      if IPX_installed and IPX_initialized then
         begin
           for i:= 0 to 1 do
               for j:= 0 to maxIPX_NODEs-1 do
                   if IPXnodes[j]^.Connected then CloseSocket(i,j)
         end;

      {$IFDEF BROADCAST}
        if inp_brd_buff<>nil then Dispose(inp_brd_buff);
        if brd_buff<>nil then Dispose(brd_buff,Done);
      {$ENDIF}
      if rtr_buff<>nil then Dispose(rtr_buff,Done);
      if nd_buff<>nil  then Dispose(nd_buff,Done);
      {$IFDEF DEBUG_IPX};
        if IPXinbuff<>nil then Dispose(IPXinbuff);
      {$ENDIF}

      for i:= 0 to maxIPX_NODEs-1 do Dispose(IPXnodes[i],Done);

      ExitProc:= SaveExit
    end;
