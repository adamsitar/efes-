 const  pkt_cislo: word = 0;

 function pkt_cis: word;
    begin
     {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
       inc(pkt_cislo);
     {$IFDEF R}  {$UNDEF R}  {$R+} {$ENDIF}
      pkt_cis:= pkt_cislo
    end;

 function net_pkt_head (var pkt: TNETpkt; typ: TNETtyp; adr: TNETadr): bool;
    begin
      fillchar(pkt,sizeof(pkt),0); { nesmie sa zrusit ! }
      make_NETadr(adr);

      pkt.head.typ:= typ;
      pkt.head.cis:= pkt_cis;

      pkt.adr:= adr;
      pkt.ods:= self_NETadr(adr);

      net_pkt_head:= true
    end;

 function net_pkt_data (var pkt: TNETpkt; pdlz: TNETdlz; data: pchars): bool;
    var   poc,dlz : long;
    begin
      if (data<>nil) and (pdlz<>0) then
         begin
         { nacitanie novych udajov do paketu
         }
           disp_NETpkt_pkt (pkt.pkt);
           new_NETpkt_data (data,pdlz, pkt.pkt);
         end;

      if (pkt.pkt.bufe<>nil) and (pkt.pkt.bufe^.is) then dlz:= pkt.pkt.bufe^.getsize
      else dlz:= pkt.pkt.dlz;
      poc:= (dlz div size_of_NETdata);
      if {(dlz>size_of_NETdata) and} (poc*size_of_NETdata<dlz) then inc(poc);
      pkt.head.poc:= {poc} N(poc-1);
      pkt.head.ind:= {1}   0;

      if (pkt.pkt.bufe<>nil) and (pkt.pkt.bufe^.is) then
         begin
         { nastavenie prveho baliku do pola "data"
         }
           disp_NETpkt_data(pkt.pkt);
           dlz:= minimum(N(pkt.pkt.bufe^.getsize),size_of_NETdata);
           pkt.pkt.bufe^.read_buffer_int(0,dlz, pkt.pkt.data,pkt.pkt.dlz, false)
         end;

      net_pkt_data:= dlz>size_of_NETdata
    end;


{ priprava potvrdenia;
  - opravit nie _data, ale code_ack: TFunc... ; data: pointer;
  - zatial nekodujem data paketu pre potvrdenie
}
 procedure net_pkt_ack (const pkt: TNETpkt; var ack: TNETpkt);
     var   key : string;
     begin
       fillchar(ack,sizeof(ack),0);

       {if (not is_ack_pkt(pkt)) and is_data_to_ack(pkt) then _key:= SF_PNETpacket(code_ack)(pkt)
       else} key:= '';

       ack.head:= pkt.head;
       ack.head.typ:= pkt.head.typ+1;    { typ_ack:= typ_spr + 1   }

       ack.adr:= pkt.ods;
       ack.ods:= self_NETadr(ack.adr)

       {dlz:=  length(key) move(_key[1],ack.data,ack.head.dlz)
        new_NETpkt_data (data,length(key),@key[1]);
       }
     end;


 function NETsend_pkt (var pkt: TNETpkt; flag: word;
                       check_ack: bool;
                       key: string;
                       id: PNETpkt_head;
                       disp: bool
                      ): int;

    var   data   : PNET0pkt_data; { nie pointer ! }
          pdata  : pchars;
          pdlz   : word;
          res,nd : int;
          is,b   : bool;
          s      : string;

    begin
      NETsend_pkt:= netNOT_SENDED;
      nd:= is_NETadr(pkt.adr);

      {$IFDEF BACKUP}

        {$IFDEF BACKUP_ACTIVE_2_NET}
        {$ELSE}
          if SERVERstatus and (nd<>SERVERnode) then Exit;
        {$ENDIF}

      {$ELSE} {$IFDEF MASTER}

        {$IFDEF BACKUP_ACTIVE_2_NET}
          if BACKUPstatus and (nd<>BACKUPnode) then Exit;
        {$ELSE}
        {$ENDIF}

      {$ELSE}

        (*{$IFDEF BACKUP_ACTIVE_2_NET}
          if BACKUPstatus and (nd=SERVERnode) then Exit;
        {$ELSE}
          if SERVERstatus and (nd=BACKUPnode) then Exit;
        {$ENDIF}*)

      {$ENDIF} {$ENDIF}


      indicate_net(1);

    { ak su data v buff (EMS pamati),
      musi by data=nil, aby sa z neho mohla odoslat prva cast paketu
    }
      is:= false;
      {if (pkt.pkt.buff<>nil) then
         begin
           is:= true;
           disp_NETpkt_data(pkt.pkt);
           pdlz:= minimum(N(pkt.pkt.buff^.getsize),size_of_NETdata);
           if not pkt.pkt.buff^.read_buffer_int (0,dlz, pkt.pkt.data,pkt.pkt.dlz, false) then Exit;
           pkt.pkt.dlz := pdlz;
           pkt.pkt.data:= @data
         end;}

    { potrebujem odoslat len "size_of_NETdata" byte;
      v poli data musi by nastavena prva cast paketu
    }
      data:= nil;
      if not is then
         begin
           is:= pkt.pkt.dlz>size_of_NETdata;
           if is then
              begin
                new(data);
                pdlz:= pkt.pkt.dlz;
                pdata:= pkt.pkt.data;

                pkt.pkt.dlz:= Minimum(pdlz,size_of_NETdata);
                move(pkt.pkt.data^,data^,pkt.pkt.dlz);
                pkt.pkt.data:= pchars(data)
              end
         end;

      case NETprotocol(pkt.adr) of
       {$IFDEF _X25}
        X25,BX25    : res:= X25_LANsend(pkt, flag);
       {$ENDIF}

       {$IFDEF RTR}
        RTR,RTI     : res:= RTRsend(pkt);
       {$ENDIF}

       {IFDEF UDP}
        RTU         : res:= UDPsend (pkt, ast_RTR_PKT,{flag}net_flag_SEND);
        UDC         : res:= UDPsend (pkt, ast_CISCO_PKT, flag);
        UDX         : res:= UDBsend (pkt, pkt.adr, flag);
        UD_         : res:= UDPsend_(pkt, pkt.adr,false, ast_CISCO_PKT,rspr_RT_, net_flag_SEND);
       {ENDIF}

       {$IFDEF TCP}
        TCP         : res:= TCPsend(pkt);
       {$ENDIF}

       {$IFDEF COM}
        COM         : res:= COMsend(pkt);
       {$ENDIF}

       else res:= netNOT_INITIALIZED
      end;
      pkt_sended(pkt);     { nastavenie priznaku -> poslal som spravu }
      NETsend_pkt:= res;   { if pkt.head.typ>100 then NET^.save_tmp_pkt(pkt);  -> len pre test }

      {$IFDEF DOCUMENT_NET}
       (*{$IFNDEF DEBUG}
        if res<>netNOT_SENDED then
       {$ENDIF}*)
           begin
             if is_ack_pkt(pkt) then b:= writeln_NET_ACK else b:= writeln_NET_SEND;
             writeln_pkt(pkt, b,true, cl_NET_SEND, arch_PKT_SEND, res)
           end
       (*{$IFNDEF DEBUG}
        else if archive_NET_SEND {and (not NETres(res)) and (res<>netNOT_SENDED)} then
           begin
             s:= strpas(NETmsg(res));
             if s<>'' then
                begin
                  s:= pkt.adr+': '+s;
                  writeln_mess0(s, writeln_NET_REC,archive_NET_REC and (NODEpoc<30), cl_NODE_OFF,arch_MESS, false);
                end
           end
       {$ENDIF}*)
      {$ENDIF};

      if is then
         begin
           pkt.pkt.dlz:= pdlz;
           pkt.pkt.data:= pdata;
         end;

      if     (not is_ack_pkt(pkt))
         {$IFNDEF DEBUG} and NETres(res) {$ENDIF}
         and (check_ack or ((pkt.head.ind=0) and (pkt.head.poc>0))) then
         begin
         { zaradenie ocakavanej spravy o potvrdeni paketu
           pre spracovanie spravy o prevzati paketu
           alebo odoslani nasledujucej casti paketu
         }
           NETack^.add_pkt_ack(pkt,key,id);
         end;

      { LEN pre ladenie potvdenia
        is:= false;
        if is then
           begin
             s:= pkt.adr;
             inc(pkt.head.typ);
             pkt.adr:= pkt.ods;
             pkt.ods:= s;
             NET^.add_ack_pkt(pkt)
           end;
      }

      if data<>nil then dispose(data);
      if disp then disp_NETpkt(@pkt);

      indicate_net(-1);
    end;


 procedure NETsend_msg (adr  : TNETadr;
                        typ  : word;

                        data : pchars;
                        dlz  : word;

                        check_ack : bool;
                        flag : word
                       );
     var   pkt: TNETpkt;
     begin
       net_pkt_head (pkt, typ, adr);
       net_pkt_data (pkt, dlz,data);
       NETsend_pkt  (pkt, flag,check_ack,'',nil,true)
     end;


 procedure NETsend_err (adr    : TNETadr;
                        level  : byte;
                        dialog : bool;
                        err    : pchars;
                        dlz    : TNETdlz
                       );
     var   data : pchars;
           size : word;
           p : pointer;
     begin
       size:= sizeof(level) + dlz + 1;
       getmem(data,size);
       level:= minimum(level,mask_ERROR_DIALOG-1);
       if dialog then level:= level or mask_ERROR_DIALOG;
       p:= pointer(data);
       move(level,pchars(p)^,sizeof(level)); incptr(p,sizeof(level));
       move(err^,pchars(p)^,dlz); incptr(p,dlz);
       data^[size-1]:= NULL;
       NETsend_msg (adr,spr_ERROR,data,size,false,net_flag_SEND);
       freemem(data,size);
     end;



 procedure NETdistribute_msg
                        (tp      : Tnd_typ_set;
                         sw      : Tnd_sw_set;
                         nd      : Tnd_nd_set;
                         typ     : word;

                         data: pchars;
                         dlz : word;

                         check_ack: bool;
                         flag: word
                        );

     var   i: int;
     begin
       for i:= 0 to NODEpoc-1 do with NODEs^[i] do
         if      ((tp=[]) or (desc.typ in tp))
             and ((sw=[]) or (desc.sw  in sw))
             and ((nd=[]) or (desc.nd  in nd))
                 then NETsend_msg (desc.adr,typ, data,dlz, check_ack,flag);
     end;
