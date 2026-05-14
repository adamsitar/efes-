procedure IPXcfg_read;
    var   f       : Text;
          s,s1,s2 : string;
          s20     : string[20];
          s3      : string[3];
          is0     : bool;
          nd, r, i,j,k,m,o: int;
          _err : bool;

    label next;

    begin
      _err:= false;

      {$IFDEF BROADCAST}
         with IPXnodes[0]^ do
           begin
             Name:= 'BROADCAST';
             Info:= nil;
             fillchar(Adr,sizeof(Adr),$FF);
             Connected:= true;
             New(out_buff);
             New(inp_buff)
           end;
      {$ENDIF}

      {$IFDEF IPX}
        if Exists(IPXcfg)<>0 then RunError('Can not read '+IPXcfg+'.');
      {$ELSE}
        if Exists(IPXcfg)<>0 then
           {$IFDEF DEBUG}
              {$IFNDEF PCTCP}
                RunError('Can not read '+IPXcfg+'.');
              {$ELSE}
                Exit;
              {$ENDIF}
           {$ELSE}
              Exit;
           {$ENDIF}
      {$ENDIF}

      Assign(f,IPXcfg); Reset(f);
      r:= 0; {$IFDEF BROADCAST} nd:= 0; {$ELSE} nd:= -1; {$ENDIF}

      while (not Eof(f)) and (nd<maxIPX_NODEs) do
        begin
           readln(f,s); inc(r); s:= uni_str(s);
           if (s='') or (s[1]=';') then continue;
           if GetStrItems(s,[';'])<1 then RunError(IPXcfg+' -> missing parameters in line '+cstr(r,1));

          { cislo stanice }
           inc(nd); s1:= GetStr(s,2,[';']);
           s2:= cut_(GetStr(s1,2,['=']));
           if s2<>'' then
              begin
                s20:= s2;
                if s20[1] in ['A'..'F'] then s20:= '$'+s20;
                val(s20,nd,k);
                if k>0 then RunError(IPXcfg+' -> invalid index of IPX node ('+s2+').')
              end;
           if nd>=maxIPX_NODEs then RunError(IPXcfg+' -> maximum node number is '+cstr(maxIPX_NODEs-1,2));
           if (IPXnodes[nd]^.Out_Buff<>nil) or (nd=IPXnode) then RunError(IPXcfg+' -> another node '+cstr(nd,1));
           if nd>=maxIPX_NODEs then
              MessError(IPXcfg+' -> to much IPX nodes. Maximum is '+cstr(maxIPX_NODEs,1)+'.', true,_err);

          { vlastna adresa moze byt len raz }
           if pos(nd_THIS,s) > 0 then
              if IPXnode<>-1 then RunError(IPXcfg+' -> another self address.')
              else IPXnode:= nd;

          { adresa routera }
           if pos(nd_ROUTER,s) > 0 then
              if ROUTERipx<>-1 then RunError(IPXcfg+' -> another router node.')
              else begin
                     ROUTERipx:= nd;
                     IPXnodes[ROUTERipx]^.pro:= RTR;
                    {RROUTERadr:=  getint(s,2,[','])}
                   end;

          { adresa bridge }
           if pos(nd_BRIDGE,s) > 0 then
              if BRIDGEipx<>-1 then RunError(IPXcfg+' -> another bridge node.')
              else BRIDGEipx:= nd;


           with IPXnodes[nd]^ do
              begin
              { meno }
                Name:= cut_(GetStr(s,1,[';']));

              { doplnkove udaje }
                Info:= StrPasNew(DelChar(GetStr(s,3,[';']),[' ','*','@','-']));

              { adresa IPX karty }
                is0:= true; fillchar(Adr,sizeof(Adr),0);
                s20:= DelChar(GetStr(s,2,[';','=']),set_);
                m:= minimum(sizeof(Adr),Length(s20) div 2);
                o:= sizeof(Adr)-m;
                for i:= 0 to m-1 do
                    begin
                      s3:= '$'+Copy(s20,i*2+1,2);
                      Val(s3,j,k);
                      if k<>0 then RunError(IPXcfg+' -> uncorrect address format in line '+cstr(r,1));
                      IPXnodes[nd]^.Adr[i+o]:= j;
                      is0:= is0 and (j=0)
                    end;

              {$IFDEF SOCKET}
                if (not is0) then
                   for i:= 0 to maxIPX_NODEs-1 do
                     if i<>nd then
                        if IPX_adr_eq(IPXnodes[nd]^.adr,IPXnodes[i]^.adr) then
                           begin
                             RunError(IPXcfg+' -> equal Ethernet address in line '+cstr(r,1));
                           end;
              {$ENDIF}

              { povolenie komunikacie s uzlom a alokacia bufferov }
                if IPXnode<>nd then
                   begin
                     Connected:= true;
                    { buffery }
                     New(Out_Buff); fillchar(Out_Buff^,sizeof(Out_Buff^),0);
                     New(Inp_Buff); fillchar(Inp_Buff^,sizeof(Inp_Buff^),0);
                    {$IFDEF IPX0}
                    { povolenie testovania }
                      if (pos('+',GetStr(s,3,[';']))<>0) then test_en:= true
                    {$ENDIF}
                   end;
              end
        end;

      Close(f);

      if IPXnode=-1 then RunError(IPXcfg+' -> missing self address.');
      LANaddress:= IPXnodes[IPXnode]^.name;

      if _err then writeln
    end; { Read_IPXcfg }
