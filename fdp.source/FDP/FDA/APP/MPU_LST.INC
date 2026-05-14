procedure writeln_monitoring;
    var   st : array[lo_MPUadr..hi_MPUadr] of byte;
          i  : byte;
    begin
     { odoslanie spravy ku monitoringu
     }
      for i:= lo_MPUadr to hi_MPUadr do
        if MPUs^[i].bgu<>NOBGU then st[i]:= MPUs^[i].st
        else st[i]:= NOBGU;
      NETsend_msg(spr_DIAG_BGU,MONaddress,@st,sizeof(st),false,0{net_flag_SEND})
    end;

procedure writeln_data(adr: byte);
    var   i : int;
          s,t,u : string;
    begin
      if (DEV_BGU=nil) or (adr<lo_MPUadr) or (adr>hi_MPUadr) then Exit;

      DEV_BGU^.writeln_pkt('', arch_PKT_SEND,' ',clGRd,false,false);
      t:= InsChar('',1+length(TimeToStr2(hour,min,sec,':','˙')),' ',1);
      for i:= 0 to MAX_RDK_MPU-1 do
        begin
          s[0]:= chr(minimum(sizeof(s)-1,MAX_ZNAK_MPU));
          move(MPUs^[adr].buff[i,0],s[1],length(s));
          if i<>0 then u:= t else u:= ' ';
          DEV_BGU^.writeln_pkt(s, arch_PKT_SEND,u,clGRd,i=0,false)
        end;
    end;

procedure writeln_status(adr: byte);
    var   s: string;
    begin
      writeln_monitoring;
      if (DEV_BGU=nil) or (adr<lo_MPUadr) or (adr>hi_MPUadr) then Exit;

      MPUdiagnose(adr);
      s:= 'åèì ¸'+cstr(adr,1)+' - '+BGU_MPUstat(MPUs^[adr].st)+'.';
      DEV_BGU^.writeln_pkt(s, arch_ERR,' ',red,true,false);
      s:= InsChar('',1+length(TimeToStr2(hour,min,sec,':','˙')),' ',1);
      DEV_BGU^.writeln_pkt('', arch_PKT_SEND,s,clGRd,false,false)
    end;
