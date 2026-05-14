 constructor TNET.Init;
       var   s: string;
       begin
         inherited Init(max_NETBuffer, sizeof(TNETpkt));
         buff:= arr;
         Owner:= nil;

         NETack:= New(PONETack,Init(@pkt_not_received));

         is_dta:= false; is_brc:= false;
         is_ack:= false; is_pkt:= false; is_reroute:= false;

         s_ack := false;   t_ack := 0;
         s_data:= false;   t_data:= 0;
         s_mess:= false;
         s_system:= false;
         s_init:= false;
         s_reroute:= false;

         semaphor_tmp_pkt_r:= false;
         semaphor_tmp_pkt_s:= false;

         s:= najmladsi_subor(pathTMP,'*'+extPKT);
         {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
          if s<>'' then cislo_tmp_packet:= scish_(delchar(s,setPism+['.']),false)+1
          else cislo_tmp_packet:= 0;
         {$IFDEF R} {$UNDEF R} {$ENDIF}
         in_file:= s<>'' {is_file}
       end;

 destructor TNET.Done;
      begin
        Dispose(NETack,Done);
        inherited Done
      end;


 function TNET.NewData (p: pointer): pointer;
    var   pkt: PNETpkt;
    begin
      pkt:= New(PNETpkt);
      new_NETpkt(PNETpkt(p),pkt);
      NewData:= pkt
    end;

 procedure TNET.DispData (var p: pointer);
    begin
      disp_NETpkt(PNETpkt(p));
      Dispose(PNETpkt(p));
      p:= nil
    end;


{ musi sa zaradit vzdy na koniec, inak by nemuselo fungovat
  potvrdzovanie a priznaky is_ack,...
}
function TNET.Add(item: pointer): int;
   var   res: int;
   begin
    {res:= find(item);
     if (res=-1) and (MaxAvail>=MIN_NET_HEAP_SIZE) then res:= inherited Add(item);
     if res=-1 then save_tmp_pkt(item);
     Add:= res}
     res:= -1;
     if (MaxAvail>=MIN_NET_HEAP_SIZE) then res:= inherited Add(item);
     if res=-1 then begin save_tmp_pkt(PNETpkt(item)^); res:= 0 end;
     Add:= res;
     Diagnose
   end;


procedure TNET.Del(ind: int);
    begin
      inherited Del(ind);
      Diagnose
    end;



{function TNET.find(pkt: PNETpacket): int;
   var   i: int;
   begin
     i:= 0;
     while     (i<=top)
           and (   (pkt^.head.typ<>buff^[i]^.head.typ)
                or (pkt^.head.cis<>buff^[i]^.head.cis)
                or (pkt^.head.dlz<>buff^[i]^.head.dlz)
                or (pkt^.head.ods<>buff^[i]^.head.ods)
                or (pkt^.head.adr<>buff^[i]^.head.adr)
               )
     do inc(i);
     if i>top then i:= -1;
     find:= i
   end;
}

{ ----------------------------
   odkladanie paketov na disk
  ----------------------------
}

 function TNET.is_file: bool;
    begin
      is_file:= Exists(pathTMP+namPKT+'*'+extPKT)=0
    end;


 procedure TNET.save_tmp_pkt(var pkt: TNETpkt);
     var   f   : file;
           FN  : string;
           res : word;
     begin
       if semaphor_tmp_pkt_s then Exit;
       {if (not ( is_system_pkt(pkt) or is_ack_pkt(pkt) )) then exit;}

       semaphor_tmp_pkt_s:= true;

       FN:= pathTMP + namPKT+inttostr(cislo_tmp_packet,znakovPKT,0)+extPKT;
       {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
       inc(cislo_tmp_packet);
       {$IFDEF R} {$UNDEF R} {$ENDIF}

       ResetIOError;
       vytvor_novy_subor(FN);
       Assign(f,FN);
       Rewrite(f,1);
       BlockWrite(f,pkt.adr[0],sizeof(pkt.adr), res);
       BlockWrite(f,pkt.ods[0],sizeof(pkt.ods), res);
       BlockWrite(f,pkt.head,  sizeof(pkt.head),res);
       flush_NETpkt_buff(pkt.pkt);
       BlockWrite(f,pkt.pkt.dlz ,sizeof(pkt.pkt.dlz),res);
       BlockWrite(f,pkt.pkt.data^,pkt.pkt.dlz,res);
       ResetIOError;
       Close(f);

       {$IFDEF ARCHIVE_NET}
         {if archive_NET_REC then}
            begin
              fn:=   'Saved tmp from '+pkt.ods+'; No.'+IntToStr(pkt.head.cis,5,0);
              archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, @fn[1],length(fn), arch_SYS, true,false);
            end;
       {$ENDIF}
       in_file:= true;
       semaphor_tmp_pkt_s:= false
     end;


 procedure TNET.read_tmp_pkt;
     var   f    : file;
           fn   : string;
           pkt  : TNETpkt;
           res  : int;
           bres : bool;
     begin
       if semaphor_tmp_pkt_s or semaphor_tmp_pkt_r then Exit;

       semaphor_tmp_pkt_r:= true;

       fn:= najstarsi_subor (pathTMP,namPKT+'*'+extPKT);
       if (fn='') then Exit;

       InfoCakaj(msgWAITING,'Reading '+fn+'.');
       Assign(f,pathTMP+fn);
       ResetIOError;
       Reset(f,1);
       fillchar(pkt,sizeof(pkt),0);
       BlockRead(f,pkt.adr[0],sizeof(pkt.adr), res);
       if res>0 then BlockRead(f,pkt.ods[0],sizeof(pkt.ods), res);
       if res>0 then BlockRead(f,pkt.head,  sizeof(pkt.head),res);
       if res>0 then BlockRead(f,pkt.pkt.dlz,sizeof(pkt.pkt.dlz),res);
       if (res>0) and (pkt.pkt.dlz>0) and (pkt.pkt.dlz<MaxAvail) and (pkt.pkt.dlz<MIN_NET_HEAP_SIZE) then
          begin
            GetMem(pkt.pkt.data,pkt.pkt.dlz);
            FillChar(pkt.pkt.data^,pkt.pkt.dlz,0);
            BlockRead(f,pkt.pkt.data^,pkt.pkt.dlz,res)
          end;
       ResetIOError;
       Close(f);
       InfoCakaj_zatvor;

       DelFile(pathTMP+fn);
       if (res>0) and (pkt.head.typ<>0) and (pkt.pkt.data<>nil) then decode_app_data_pkt(pkt,false);
       disp_NETpkt(@pkt);

       semaphor_tmp_pkt_r:= false
     end;
