function new_NETpkt_data(data: pchars; dlz: TNETdlz; var pkt: TNETpkt_data): bool;
   begin
     new_NETpkt_data:= false;
     fillchar(pkt,sizeof(pkt),0);
     if (MaxAvail<=MIN_NET_HEAP_SIZE) or (MaxAvail<=dlz) or (dlz=0) then Exit;

     getmem(pkt.data,dlz);
     if (pkt.data<>nil) then
        begin
          pkt.dlz:= dlz;                                     {?}
          if data<>nil then move(data^,pkt.data^,pkt.dlz)
          else fillchar(pkt.data^,dlz,0)
        end;

     new_NETpkt_data:= true
   end;

procedure disp_NETpkt_data(var pkt: TNETpkt_data);
    begin
      if (pkt.data<>nil) then freemem(pkt.data,pkt.dlz);
      pkt.data:= nil;
      pkt.dlz:= 0
    end;


procedure new_NETpkt_pkt (const pkt1: TNETpkt_data; var pkt2: TNETpkt_data);
    begin
      fillchar(pkt2,sizeof(pkt2),0);
      if (pkt1.bufe<>nil) and (pkt1.bufe^.is) then
         begin
           pkt2.bufe:= New(PstreamBuffer,Init(1, pkt1.bufe^.getsize));
           if (pkt2.bufe<>nil) and (pkt2.bufe^.is) then
              begin
                pkt1.bufe^.seek(0);
                pkt2.bufe^.CopyFrom(pkt1.bufe^,pkt1.bufe^.getsize)
              end
           else begin
                  disp_NETpkt_pkt(pkt2);                           { odalokuje cely paket }
                  pkt1.bufe^.read_buffer(pkt2.data,pkt2.dlz,false) { alokuje }
                end
         end
      else new_NETpkt_data(pkt1.data,pkt1.dlz, pkt2)
    end;

procedure disp_NETpkt_pkt (var pkt: TNETpkt_data);
    begin
      disp_NETpkt_data(pkt);
      if (pkt.bufe<>nil) then Dispose(pkt.bufe,Done);
      pkt.bufe:= nil
    end;


procedure new_NETpkt(pkt1,pkt2: PNETpkt);
    begin
      fillchar (pkt2^,sizeof(pkt2^),0);
      pkt2^:= pkt1^;

      fillchar (pkt2^.pkt,sizeof(pkt2^.pkt),0);
      new_NETpkt_pkt (pkt1^.pkt,pkt2^.pkt)
    end;

procedure disp_NETpkt(pkt: PNETpkt);
    begin
      disp_NETpkt_pkt (pkt^.pkt);
      fillchar(pkt^,sizeof(pkt^),0)
    end;


function flush_NETpkt_buff(var pkt: TNETpkt_data): bool;
   begin
     flush_NETpkt_buff:= true;
     with pkt do
       if (data=nil) and (bufe<>nil) and (bufe^.is) then
          if (bufe^.getsize<MIN_NET_HEAP_SIZE) then
             begin
               if bufe^.read_buffer (data,dlz,false) then
                  begin
                    dispose(bufe,Done);
                    bufe:= nil
                  end
               else flush_NETpkt_buff:= false
             end
          else flush_NETpkt_buff:= false
   end;


{function read_NETpkt (pkt: TNETpkt_data; var data: pchars; var dlz: word): bool;
   var   res: bool;
   begin
     read_NETpkt:= false;
     data:= nil; dlz:= 0;
     if (pkt.data<>nil) and (pkt.dlz>0) then
        begin
          if (dlz<MIN_NET_HEAP_SIZE) and (dlz<MaxAvail) then
             begin
               dlz:= pkt.dlz;
               getmem(data,dlz);
               move(pkt.data^,data^,dlz);
               read_NETpkt:= true
             end
        end
     else read_NETpkt:= pkt.bufe^.read_buffer(data,dlz,false)
   end;}




{ p.head.ind/p.head.poc hovoria len o jednom pakete
}
procedure NET0pkt_NETpkt (p0: TNET0pkt; var p: TNETpkt);
    begin
      fillchar(p,sizeof(p),0);

      p.head.typ:= p0.head.typ;
      p.head.cis:= p0.head.cis;

      p.adr:= p0.head.adr;
      p.ods:= p0.head.ods;

      new_NETpkt_data(@p0.data,p0.head.dlz, p.pkt);
    end;

procedure NETpkt_NET0pkt (p: TNETpkt; var p0: TNET0pkt);
    begin
      fillchar(p0,sizeof(p0),0);

      p0.head.typ:= p.head.typ;
      p0.head.cis:= p.head.cis;
      p0.head.adr:= p.adr;
      p0.head.ods:= p.ods;

      p0.head.dlz:= minimum(p.pkt.dlz,size_of_NETpkt);
      move(p.pkt.data^,p0.data,p0.head.dlz);
    end;


function eq_NETpkt_(p1,p2: TNETpkt; is_ind: bool): bool;
   begin
     eq_NETpkt_:=      (p1.head.typ=p2.head.typ)
                   and (p1.head.cis=p2.head.cis)

                   and (p1.ods=p2.ods)
                   and (p1.adr=p2.adr)

                   and ((not is_ind) or (    (p1.head.ind=p2.head.ind)
                                         and (p1.head.poc=p2.head.poc)
                                        )
                       )
   end;



procedure code_msg (msg: pstring; var pkt: TNETpkt);
    begin
      new_NETpkt_data (@msg^[1],length(msg^), pkt.pkt)
    end;

procedure decode_msg (const pkt: TNETpkt; msg: pstring);
    begin
      msg^[0]:= chr(minimum(pkt.pkt.dlz,sizeof(msg^)-1));
      move(pkt.pkt.data^,msg^[1],ord(msg^[0]))
    end;