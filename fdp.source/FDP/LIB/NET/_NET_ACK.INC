{ ------------------------------
  spracovanie potvrdeni paketu
  ------------------------------

  Generovanie a odoslanie potvrdenia :

  a) Ak potvrdzujem len cislom spravy, staci hned generovat potvrdenie s typ+1
     a rovnakym cislom. Vtedy sa musi pamatat cislo paketu s odoslanou spravou,
     aby bolo mozne spracovat potvrdenie.

  b) Ak potvrdzujem kodovanou spravou, ma to vyhodu, ze si nemusim pamatat cislo
     odoslaneho paketu na dany smer. Nevyhodou je, ze musi byt volana identicka
     fcia pre dekodovanie dat a kodovanie potvrdenia.

  c) Ak chcem cakat na dorucenie potvrdenie o sprave, najlepsie sa to spravi
     cez vynulovanie priznaku v procedure decode_pkt

  Preco nedekodujem a nespracujem data v tejto slucke ?
  Bolo by to velmo jednoduche, vsak ?
  V externej funkcii pre zaradenie dat moze dojst ku zdrzaniu (save, send,
  warning) a to mi pozdrzi potvrdenia pre dalsie pakety.

  Spravy a kodovane potvrdenia prejdu cez read raz, nekodovane zostavaju,
  az kym nie su precitane...
}



{ jadro pre spracovanie potvrdenia : dekodovanie, spracovanie

procedure TNET._decode_ack_pkt(const pkt: TNETpkt;
                               size_item: word; disp_item: PProc_p;
                               process: PProc_ps
                              );
    var   data : pointer;
          key  : string;
    begin
      if (process<>nil) then
         begin
           GetMem(data,size_item); FillChar(data^,size_item,0);
           key[0]:= chr(Minimum(sizeof(key)-1,pkt.pkt.dlz));
           move(pkt.pkt.data^,key[1],ord(key[0]));
           Tproc_ps(process)(data,key);
           if (disp_item<>nil) then TProc_p(disp_item)(data);
           FreeMem(data,size_item)
         end
    end;
}
 procedure TNET.decode_app_ack_pkt(var pkt: TNETpkt);
     begin
     end;


 function  TNET.read_ack_pkt: bool;
     var   ack : TNETpkt;
           i   : int;
     begin
       read_ack_pkt:= true;
       if s_ack then Exit;

       s_ack:= true;
       i:= 0;
       while (i<=top) do
         if is_ack_pkt(buff^[i]^) and pkt_for_this_node(buff^[i]^) then
            begin
              move(buff^[i]^,ack,sizeof(TNETpkt));      { prehodenie a odmazanie musia ostat }
              fillchar(buff^[i]^,sizeof(buff^[i]^),0);  { pocitaju s tym nasledujuce algoritmy }
              indicate_net(1);
              Del(i);
              t_ack:= ack.head.typ;      { zatial nevyuzite }
              decode_app_ack_pkt(ack);   { v prikaze je volany Main0, tak uz netreba }
              disp_NETpkt(@ack);
              indicate_net(-1);
              t_ack:= 0;
              break
            end
         else inc(i);
       is_ack:= is_ack and (i<=top);     { nastavi sa az po neuspesnom prechode }
       read_ack_pkt:= false;
       s_ack:= false
     end;


{ spracovanie prijatych potvrdeni
}
 procedure TNET.read_net_buff_ack;
     begin
       if is_data then read_ack_pkt;
     end; { read_net_buff_ack }


{ spracovanie povrdeni :
  - nacita z buffera do pola "rec"
    vsetky potvrdenia danej spravy
    podla ich typu a kluca
  - ack uz bolo z buff odmazane
}
 procedure TNET.read_ack_pkts (ack: PNETpkt; var key: string; var rec: Tplan_rec; var fdp: bool);
     var   i,nd : int;
           typ  : TNETtyp;
           s  : string;
           is : bool;
     begin
       fillchar(rec,sizeof(rec),0);
       fdp:= false;

       typ:= ack^.head.typ;
       decode_msg (ack^,@key);
       if key='' then Exit;
       nd:= is_NETadr(ack^.ods);
       if nd>-1 then
          begin
            rec_pkt (nd,rec,net_def.is_ack);
            fdp:= fdp or (not (NODEs^[nd].desc.typ in [RDP0,RDP0NX,RDP,MON]))
          end;

       i:= 0;
       while (i<=top) do
         begin
           is:= false;
           ack:= buff^[i];
           if (ack^.head.typ=typ) and pkt_for_this_node(ack^) then
              begin
                 decode_msg (ack^,@s);
                 if key=s then
                    begin
                      is:= true;
                      nd:= is_NETadr(ack^.ods);
                      if nd>-1 then
                         begin
                           rec_pkt (nd,rec,net_def.is_ack);
                           fdp:= fdp or (not (NODEs^[nd].desc.typ in [RDP0,RDP0NX,RDP,MON]))
                         end;
                      Del(i)
                    end
              end;
           if not is then inc(i);
         end;
     end;
