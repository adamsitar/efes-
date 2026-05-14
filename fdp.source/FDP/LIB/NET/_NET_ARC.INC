function str_pkt_head(const pkt: TNETpkt): string;
   var   s,t  : string;
   begin
     t:= pkt.adr; if t='' then t:= 'BRD...';
     str(pkt.head.typ,s);
     s:= s + ', '+pkt.ods+'->'+t+', '; {s:= inschar(s,2*Sizeof(TNETadr)+7,' ',1);}
     str(pkt.head.cis,t); s:= s+''+t+' ';
     str(pkt.head.ind,t); s:= s+''+t+' ';
     str(pkt.head.poc,t); s:= s+''+t;
     str_pkt_head:=  s
   end;


procedure writeln_pkt(const pkt: TNETpkt; _writeln,_archive: bool; _cl: byte; _inf: str3; res: int);
    {$IFDEF DOCUMENT_NET}
     const data_size = SizeOf(TNETpkt)*2 + size_of_NETpkt;
     var   data_pkt  : pbytes;
           p,_p : int;
           s,t  : string;
           {isdata,}ishb,hb,iscas : bool;
    {$ENDIF}

    begin
      if not (_writeln or _archive) then Exit;

     {$IFDEF DOCUMENT_NET}

       with pkt.head do
         begin
           {isdata:= (writeln_NET_ACK) or ((typ>spr0_DATAlo) and (not is_ack_pkt(pkt)));}
           ishb  := (typ=spr_HEARTBEAT)  or (typ=ack_HEARTBEAT) or (typ=spr_CALL) or (typ=ack_CALL);
           hb    := ((typ=spr_HEARTBEAT) or (typ=ack_HEARTBEAT));
           iscas := (typ=spr_CAS) or (typ=ack_CAS)
         end;

       GetMem(data_pkt,data_size);

       if not NETres(res) then s:= '!'+cstr(res,1)+', '
       else s:= '';
       s:= s + str_pkt_head(pkt);
       str(pkt.pkt.dlz{:2},t); s:= s+' '+t;
       if writeln_NET_DATA and (pkt.pkt.dlz>0) then s:= s+' ; ';

       p:= Minimum(data_size-1,length(s));
       move(s[1],data_pkt^,p);

       if writeln_NET_DATA then
          begin
            _p:= Minimum(data_size-p-1,pkt.pkt.dlz);      { -1 = rezerva pre ')' }
            Move(pkt.pkt.data^,data_pkt^[p],_p); p:= p + _p;
            if pkt.pkt.dlz>0 then
               begin
                 t:= ' ';
                 move(t[1],data_pkt^[p],1);
                 inc(p)
               end
          end;

       if writeln_MEM then
          begin
            t:= ' , M='+cstr(MaxAvail,1)+','+cstr(MemAvail,1);
            if data_size-p-1>length(t) then
               begin
                 move(t[1],data_pkt^[p],length(t));
                 inc(p,length(t))
               end
          end;

       {$IFDEF WRITELN_NET}
         if     _writeln and (MainApp<>nil)
            and ((not (hb or iscas)) or ((hb or iscas) and writeln_NET_HEARTBEAT)) then
                MainApp^.writeln_(data_pkt,p, _cl, _inf,true,false);
       {$ENDIF}

       {$IFDEF ARCHIVE_NET}
         if     _archive
           and ((not (hb or iscas)) or ((hb or iscas) and archive_NET_HEARTBEAT)) then
             archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, data_pkt,p,
                           _inf,true, not writeln_NET_DATA
                          );
       {$ENDIF}

       FreeMem(data_pkt,data_size)
     {$ENDIF}
    end;

procedure writeln_mess(const pkt: TNETpkt; mess: string; _writeln,_archive: bool; _cl: byte; _inf: str3);
    begin
       mess:=  mess + ' ('+str_pkt_head(pkt)+')';

      {$IFDEF WRITELN_NET}
        if _writeln and (MainApp<>nil) then MainApp^.writeln_(@mess[1],length(mess), _cl, _inf,true,false);
      {$ENDIF}

      {$IFDEF ARCHIVE_NET}
        if _archive then
           archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, @mess[1],length(mess),
                         _inf, true, not writeln_NET_DATA
                        );
      {$ENDIF}

      _write_err_log(mess)
    end;

procedure writeln_mess0(mess: string; _writeln,_archive: bool; _cl: byte; _inf: str3; errlog: bool);
    begin
    {$IFNDEF DD_EXE}
      {$IFDEF WRITELN_NET}
        if _writeln then MainApp^.writeln_(@mess[1],length(mess), _cl,_inf,true,false);
      {$ENDIF}
      {$IFDEF ARCHIVE_NET}
        if _archive then archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, @mess[1],length(mess),_inf,true,false);
      {$ENDIF}
      if errlog then _write_err_log(mess)
    {$ENDIF}
    end;


{ IFDEF DD_EXE}
   procedure  net_pkt_test(fn: string; _h,_m: int);
       const  last_pos : long = 0;
              last_fn  : string = '';

       var    pkt   : TNETpkt;
              f     : {text;} file of char;
              w,i,k : word;
              p,r,b : pchar;
              c     : char;
              s,t   : string;
              h,m,e : byte;
              nd    : int;
       begin
         if FExists(fn)<>0 then Exit;

         if fn<>last_fn then last_pos:= 0;
         last_fn:= fn;

         Fillchar(pkt,sizeof(pkt),0);
         Assign(f,fn);
         Reset(f);
         Seek(f,last_pos);
         w:= 1000; {filesize(f);}
         getmem(p,w+1);

         while not eof(f) do
           begin

             i:= 0;
             repeat
               read(f,c);
               inc(last_pos);
               if (c=kbCR) or (c=kbLF) then break;
               p[i]:= c;
               inc(i)
             until (i>=1000);
             read(f,c);
             inc(last_pos);

             p[i]:= NULL;
             s:= strpas(p);
             {readln(f,s);}
             if (s='') or (s[1]=';') then continue;

             GetTimeStr (h,m,e, getstr(s,1,[',',';','(',ZAC_SPR]));
             if (_h<>-1) and ((TimeToSec(_h,_m,0))<TimeToSec(h,m,0)) then Break;
             if (_h=-1) or ((_h=h) and (_m=m)) then
                begin
                  fillchar(pkt,sizeof(pkt),0);

                  s:= copy(s,12,length(s)-11);
                  pkt.head.typ:= getint(s,1,[',']);
                  pkt.ods:= getstr(s,2,[',','-','>']); pkt.ods:= cut_(pkt.ods);
                  pkt.adr:= getstr(s,3,[',','-','>']); pkt.adr:= cut_(pkt.adr);

                  t:= getstr(s,3,[',']); t:= cut_(t);
                  pkt.head.cis:= getint(t,1,[' ']);
                  pkt.head.ind:= getint(t,2,[' ']);
                  pkt.head.poc:= getint(t,3,[' ']);

                  pkt.pkt.dlz:= getint(t,4,[' ']);

                  nd:= is_NETadr(pkt.ods);
                  if     {$IFDEF TEST}
                          {$IFNDEF DEBUG}
                               (pkt.head.typ>=spr0_SPR)
                           and (NETtype(pkt.ods)<>RDP)
                           and
                          {$ENDIF}
                               (not is_ack_pkt(pkt))
                           and
                         {$ENDIF}
                         pkt_for_this_node(pkt)
                       then
                         begin
                           k:= pos('; ',s);
                           if k>0 then
                              begin
                                r:= strpos(p,';');
                                r:= @r[2];
                                k:= strlen(r);
                                new_NETpkt_data (@r[0],pkt.pkt.dlz,pkt.pkt);
                                if (k<pkt.pkt.dlz) and (pkt.pkt.data<>nil) then fillchar(pkt.pkt.data^[k],pkt.pkt.dlz-k,' ')
                              end;
                           (*r:= strpos(p,'->');
                           if r<>nil then
                              begin
                                b:= strpos(r,ZAC_SPR);
                                if b=nil then b:= strpos(r,'(');
                                if b=nil then
                                   begin
                                     b:= strpos(r,'; ');
                                     if b<>nil then incptr(pointer(b),2)
                                   end;
                                {$IFDEF TEST} if b<>nil then {$ENDIF} new_NETpkt_data (@b[0],pkt.pkt.dlz,pkt.pkt);
                              end;
                           *)
                           NET^.receive_pkt(pkt);
                           {NET^.decode_app_data_pkt(pkt,false);}
                           disp_NETpkt(@pkt);
                           break
                         end;
                end
         end;
         freemem(p,w+1);
         Close(f)
       end;
{ ENDIF}


function pkt_net: long;
   begin
     pkt_net:= NET^.top+1
   end;

function pkt_tmp: long;
   begin
     pkt_tmp:= GetNmbOfFiles(pathTMP+'*'+extPKT)
   end;
