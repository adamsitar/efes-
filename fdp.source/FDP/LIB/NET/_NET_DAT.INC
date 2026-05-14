{ ----------------------------------------
   Vyslanie datovej spravy na jeden smer
  ----------------------------------------
}

{ data: pointer nahradit data: POData
}

 function ack_is_expected(ack: PNETack): bool; far;
    begin
      ack_is_expected:= not NETack^.is_ack(ack)
    end;


 function TNET.send_data (adr      : TNETadr;
                          typ      : word;

                          p_data   : pointer;
                          p_cdata  : Pcode_NETpkt_data;
                          p_ckey   : Pcode_NETkey;
                          p_rec    : Pplan_rec;

                          id       : PNETpkt_head;

                          is_filter : bool;
                          info     : string;
                          filter   : pointer;
                          wait,msg : bool;
                          flag     : word
                         ): int;

    var   pkt  : TNETpkt;
          ack  : TNETack;
          pack : PNETack;
          {ack  : PNETack;
          data : pchar;}
          key  : string;
          i,nd,res,dlz : int;
          is, isa : bool;

    begin
      send_data:= netNOT_SENDED;
      fillchar(pkt,sizeof(pkt),0);

     { priznak odoslania/potvrdenia dat
     }
      nd:= is_NETadr(adr);
      if (nd>-1) and (p_rec<>nil) then p_rec^[nd]:= no_ack;

      if     (is_filter)
         and ({$IFDEF BACKUP} {$IFNDEF BACKUP_ACTIVE_2_NET}
                (SERVERstatus and (nd<>SERVERnode)) or { hlavny server pracuje }
              {$ENDIF} {$ENDIF}
              (*{$IFDEF SLAVE}
                (BACKUPstatus  and (nd<>BACKUPnode))  or { hlavny server pracuje }
              {$ENDIF}*)
                 (typ=0)
              or (adr='')
              or (not is_to_nd(nd, info,filter,p_data,nil))
              or (p_cdata=nil)
              or (p_data=nil)
             )
            then Exit;

     { zakodovanie paketu
     }
      net_pkt_head (pkt, typ, adr);
      Tcode_NETpkt_data(p_cdata)(p_data,pkt);
      net_pkt_data (pkt, 0,nil);                                     { uz je zaplnene polo }
      if (p_ckey<>nil) then key:= Tcode_NETkey(p_ckey)(p_data)
      else key:= '';
      isa:= is_data_to_ack(pkt);
      res:= NETsend_pkt (pkt,flag,isa and (not wait), key,id,false);  { start_tick:= GetTicks; }

      if NETres(res) then
         begin
           if isa and wait and (nd>-1) then
              begin
              { zaradenie ocakavanej spravy o potvrdeni paketu
                pre spracovanie spravy o prevzati paketu
                alebo odoslani nasledujucej casti paketu
              }
                pack:= NETack^.add_pkt_ack(pkt,key,id);
                if (pack<>nil) then
                   begin
                     new_ACK(pack,@ack);
                     {if _INFO_NET_RES then}
                      if msg then Say(msgWAITING,msgSEND+': '+pkt.adr,
                                      clGRc, clBUTTON_COLOR, nil,nil, time_out_nd(nd),
                                      GetTicks, @ack_is_expected, @ack
                                     )
                      else repeat CheckProcesses until (ack_is_expected(@ack));
                     {_INFO_NET_RES:= false;}
                     { cakanie ukoncene predcasne ? }
                     if NODEs^[nd].stat.TrasaOK and (ack_is_expected(@ack)) then res:= netRES_OK
                     else res:= netTIME_OUT;
                     disp_ACK(@ack)
                   end
              end
         end
      else begin
             if msg then Err2({pkt.adr+': '+}msgWARNING,strpas(NETmsg(res)));
             {fillchar(ack,sizeof(ack),0);
             net_pck_ack(pkt^,ack^);
             NETack^.del_ack(ack,true,false);}
           end;

      lastDataHead:= pkt.head;
      disp_NETpkt(@pkt);

      send_data:= res
    end;


 function  NETsend_data ( adr      : TNETadr;
                          typ      : word;

                          p_data   : pointer;
                          p_cdata  : Pcode_NETpkt_data;
                          p_ckey   : Pcode_NETkey;
                          p_rec    : Pplan_rec;

                          is_filter  : bool;
                          info     : string;
                          filter   : pointer;
                          wait,msg : bool;
                          flag     : word
                        ): int;

    begin
      if NET<>nil then
         NETsend_data:= NET^.send_data(adr, typ,
                                       p_data,p_cdata,p_ckey,p_rec,nil,
                                       is_filter, info,filter,
                                       wait,msg,
                                       flag
                                      )
      else NETsend_data:= netNOT_INITIALIZED
    end;


{ ---------------------------------------------------
   Vyslanie datovej spravy na viac smerov "sucasne"
  ---------------------------------------------------

  Pri distribucii planu existuje jedna zvlastnost. RTR moze odoslat
  plan na viacero smerom jednym vyslanim. Ak su funkcia kodovane pre kazdy
  smer rovnako (scode_data=nil or not SECTOR_EN), mal by som usetrit LANku -
  jednym vyslanim odoslem na vsetky smery (z tejto urovne ma nezaujima
  protokol RTI).
  Funkciou NET_send_pkt odoslem na jeden smer. Preto odtial volam odoslanie
  na RTR zvlast pre a pre kazdu odoslany smer RTRa nastavim zvalst NETack.

  Distribucia sa pouziva len pri prijme a vytvoreni dat, ked este neboli
  rozoslane.
}

 function TNET.id__distributed_data
                 ( typ     : word;
                   p_data  : pointer;
                   send_to : PBplan_rec
                 ): PNETpkt_head;
    begin
      id__distributed_data:= nil;
    end;


 function TNET.distribute_data
                         ( tp      : Tnd_typ_set;
                           sw      : Tnd_sw_set;
                           nd      : Tnd_nd_set;

                           typ     : word;
                           p_data  : pointer;
                           p_cdata : Pcode_NETpkt_data;
                           p_ckey  : Pcode_NETkey;
                           p_rec   : Pplan_rec;

                           is_filter : bool;
                           info      : string;
                           filter    : pointer;
                           nd_slave  : bool;
                           nd_backup : bool;

                           flag    : word
                         ): bool;

    var   send_to : TBplan_rec;
          i,pocet : int;
          b1,b2,b3,b4 : bool;
          id: PNETpkt_head;

         (*{$IFDEF RTR}
          pkt     : TNETpkt;
          data    : pchar;
          dlz     : word;
          key     : string;
          is_rtr  : bool;
         {$ENDIF}*)

    begin
      distribute_data:= false;

      if    (*{$IFDEF BACKUP}
              ({bmode and} (SERVERstatus)) or
            {$ENDIF}*)
            (typ=0)
         or (p_cdata=nil)
         or (p_data=nil)      then Exit;

     { zistenie smerov, kam odosielat
     }
       fillchar(send_to,sizeof(send_to),0);
       pocet:= 0;
       for i:= 0 to NODEpoc-1 do
         begin
           send_to[i]:=      (not is_filter)
                         or  ( {$IFDEF BACKUP}
                                    {$IFDEF BACKUP_ACTIVE_2_NET}
                                     true
                                    {$ELSE}
                                     ((not SERVERstatus) or (i=SERVERnode))
                                    {$ENDIF}
                                and
                               {$ELSE} {$IFDEF MASTER}
                                    {$IFDEF BACKUP_ACTIVE_2_NET}
                                      ((not BACKUPstatus) or (i=BACKUPnode))
                                    {$ELSE}
                                      true
                                    {$ENDIF}
                                and
                               {$ELSE}
                                    {((i<>SERVERnode) or (BACKUPnode<0) or (not BACKUPstatus))
                                and}
                               {$ENDIF} {$ENDIF}

                                    (NODEs^[i].desc.sw<>PRN)

                               { ak z tohto smeru nebola prijata iformacia a patri tam
                               }
                               and  ((p_rec=nil) or ({(p_rec<>nil) and} (not (p_rec^[i] in [is_rec,no_send]))))
                               and  is_nd_type(i, tp,sw,nd)
                               and  is_to_nd  (i, info,filter,p_data,nil)

                               and  ((not nd_slave) or (nodes^[i].desc.nd=slave))

                             );
           if send_to[i] then inc(pocet)
         end;

       distribute_data:= pocet<>0;
       if pocet=0 then Exit;

     { odoslanie rovnako kodovanej spravy na rozne smery
     }
       id:= id__distributed_data(typ,p_data,@send_to);
       for i:= 0 to NODEpoc-1 do
         if     ( send_to[i] )
            {and (    (is_proL(pkt.adr))
                  or (not ((NODEs^[i].desc.pro=RTR) and (NODEs^[i].desc.typ=RDP)))
                )} then
            begin
              send_data (NODEs^[i].desc.adr,
                         typ, p_data,p_cdata,p_ckey,p_rec,id,
                         is_filter, info,filter, false,false,
                         flag
                        )
            end;
       if id<>nil then freemem(id,sizeof(id^));

     (*{$IFDEF RTR}
     { zoskupenie dat pre rozne uzly do jedneho paketu,
       predpoklada len kratky paket :
     }
       is_rtr:= false;
       i:= 0;
       while (i<NODEpoc) and (not is_rtr) do
         begin
           is_rtr:=     send_to[i]
                    and (not is_proL(pkt.adr))
                    and (NODEs^[i].desc.pro=RTR)
                    and (NODEs^[i].desc.typ=RDP);
           inc(i)
         end;

       if is_rtr then
          begin
            data:= TF_NETdata(p_cdata)(p_data);
            dlz:= strlen(data);
            if data=nil then Exit;

            net_pkt_data  (pkt, typ,''{NODEs^[i].desc.adr}, dlz,pchars(data));
            RTRdistribute (pkt, @send_to);
            writeln_pkt   (pkt, writeln_NET_SEND,archive_NET_SEND, cl_NET_SEND, arch_PKT_SEND);

            if is_data_to_ack(pkt) then
               for i:= 0 to NODEpoc-1 do
                  if send_to[i] and (NODEs^[i].desc.pro=RTR) and (NODEs^[i].desc.typ=RDP) then
                     begin
                       pkt^.head.adr:= NODEs^[i].desc.adr;
                       NETack^.add_ack(pkt,key)
                     end;

            disp_NETpkt(@pkt);
            strdispose(data)
         end;
     {$ENDIF}*)
    end;


 function  NETdistribute_data

                        (tp      : Tnd_typ_set;
                         sw      : Tnd_sw_set;
                         nd      : Tnd_nd_set;
                         typ     : word;

                         p_data  : pointer;
                         p_cdata : Pcode_NETpkt_data;
                         p_ckey  : Pcode_NETkey;
                         p_rec   : Pplan_rec;

                         is_filter : bool;
                         info      : string;
                         filter    : pointer;
                         slave     : bool;
                         backup    : bool;

                         flag    : word
                        ): bool;
    begin
      if NET<>nil then
         NETdistribute_data:= NET^.distribute_data
                                     (tp,sw,nd, typ,
                                      p_data,p_cdata,p_ckey,p_rec,
                                      is_filter, info,filter,
                                      slave,backup,
                                      flag
                                     )
      else NETdistribute_data:= false
    end;
