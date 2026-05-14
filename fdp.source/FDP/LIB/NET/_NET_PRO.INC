{ תתתתתתתתתתתתתתתתתתתתתתתת
  dekodovanie paketu
  תתתתתתתתתתתתתתתתתתתתתתתת
}

{ Spracuje paket, jeho datovu cast data
}
procedure TNET._decode_data_pkt(var pkt: TNETpkt;

                                size_item   : word;
                                p_disp_item : PProc_p;

                                p_decode_data : Pdecode_NETpkt_data;
                                p_accept      : Paccept_NETdata;
                                p_save        : Pprocess_NETdata;
                                p_process     : Pprocess_NETdata;

                                en_inf: pchar; rec: bool
                               );
    var   p  : pointer;
          nd : int;
          b  : bool;
          sz : long;
    begin
      nd:= is_NETadr(pkt.ods);
      sz:= size_item+pkt.pkt.dlz;
      if (pkt.pkt.data=nil) and (pkt.pkt.bufe<>nil) then sz:= sz+pkt.pkt.bufe^.getsize;

      if     (MaxAvail > size_item+sz)
         and (    (    (nd>-1)                                                        { definovany uzol       }
                   and ((rec       ) or (strpos(NODEs^[nd].desc.inf,nd_INF)=nil))     { nie je len informacny }
                   and ((en_inf=nil) or (strpos(NODEs^[nd].desc.inf,en_inf)<>nil))    { povolene data         }
                  )
               or (    (nd<0)
                   and (NODE_FILTER)
                   and (pkt.head.typ >= spr_DATAlo_)
                  )
             )
         and (p_decode_data<>nil) then
      else begin
             writeln_mess(pkt,tit_UALWDATA,true,true,cl_ERR,arch_ERR);
             Exit
           end;

     { zaplnenie pola dat udajmi v EMS
     }
      flush_NETpkt_buff(pkt.pkt);

     { dekodovanie paketu
     }
      GetMem(p,size_item); FillChar(p^,size_item,0);
      Tdecode_NETpkt_data(p_decode_data)(pkt,p);

     { spracovanie, moze byt podmienene
     }
      if (p_accept=nil) or Taccept_NETdata(p_accept)(pkt.ods,p) then
         begin
           if (p_save<>nil)        then Tprocess_NETdata(p_save)   (p);
           if (p_process<>nil)     then Tprocess_NETdata(p_process)(p);
           {if (p_process_pkt<>nil) then Tdecode_NETpkt_data(p_process_pkt)(pkt,p);}
         end;

      if (p_disp_item<>nil) then TProc_p(p_disp_item)(p);
      FreeMem(p,size_item)
    end;


procedure TNET.decode_app_data_pkt(var pkt: TNETpkt; _stream: bool);
    begin
      case pkt.head.typ of

        0  : ;

        spr_PRN_NET     : print_str_from_net(pkt);

        spr_PRN_NET_RES : if (pkt_prn_res<>nil) and (not pkt_prn_res^.is) then
                             begin
                               pkt_prn_res^.is:= true;
                               new_NETpkt(@pkt,@(pkt_prn_res^.pkt));
                             end;
      end;
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   spracovanie datovych paketov
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

  Nacitanie pkt a jeho spracovanie : pakety sa nacitavaju podla
  dolezitosti definovanej kodom paketu, pripadne je mozne definovat
  cas prijmu.

  Postup :

    - nacitanie (najdolezitejsieho alebo dalsieho paketu),
    - vyvolanie funkcie pre jeho spracovanie.

  Obmedzenie :

    - pretoze v externej funkcii "read_pkt_ext" moze dojst pri
      spracovavani spravy ku zdrzaniu a fcia a proces pre kontrolu
      prijmu zo siete moze znova vliezt do paketu toho isteho typu,
      mohlo by pri ich spracovavani dojst ku konfliktu, pretoze
      postup spracovania nemusi byt reentrantny (ukladanie do DB,
      sprava o datach,...)
    - preto je tu jedno nesystemove riesenie, t.j. modul NET
      vie o deleni sprav na skupiny...
    - Nie je dovolene spracovavat pakety viacnasobne spracovatelnych dat,
      ak modul prave spracovava potvrdenie, alebo nepripustit spracovanie
      dat typu "t_ack-1".
      Vid [1] a [2].

  Poznamka :

    - ak bol prijaty paket typu i/m => ulozenie do ems/docasneho subora;
      - po prijati paketu m/m jeho spracovanie a odmazanie
      - ak vyprsi timeout na dorucenie dalsieho, odmazanie
      - ak pride paket (i/m) a (i<>0) a (i-1/m nexistuje),
        nepotvrdi sa ...  riesi funkcia add_data_pkt...

}

{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   vrati index najdolezitejsej spravy
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function TNET.select_pkt_ind(_lo,_hi: long; prty: bool): int;
    var   i,ind : int;
          typ   : long;

    begin
      ind:= -1; typ:= _hi+1;

      i:= 0; while (i<=top) do
        begin
          if ((not is_ack_pkt(buff^[i]^)) and pkt_for_this_node(buff^[i]^)) then { V bufferi mozu byt i spravy pre ine uzly }
             begin
               if      (buff^[i]^.head.ind = buff^[i]^.head.poc)
                   and (buff^[i]^.head.typ >= _lo)
                   and (buff^[i]^.head.typ <= _hi)
                     { [2] and ((not s_ack) or (buff^[i]^.head.typ<>t_ack-1)} then
                  if prty then
                     begin
                     { hlada najdolezitejsiu spravu z kategorie _lo.._hi
                     }
                       if (buff^[i]^.head.typ < typ) then
                          begin
                            typ:= buff^[i]^.head.typ;
                            ind:= i
                          end
                     end
                  else begin
                         ind:= i;
                         break
                       end
             end;
          inc(i)
        end;

      select_pkt_ind:= ind
    end;


{ תתתתתתתתתתתתתתתתתתתתתתת
   spracovanie dat
  תתתתתתתתתתתתתתתתתתתתתתת
}
 procedure TNET.read_data_pkt;
     var   pkt : TNETpkt;
           i,ind : int;

     begin
       if s_data then Exit;
       s_data:= true;

      { a) kontrola na nedorucenie (timeout) nasledujuceho paketu
           z "dlhych" paketov
      }
       i:= 0;
       while (i<=top) do
         if     (buff^[i]^.head.ind < buff^[i]^.head.poc)
            and TimeOut(buff^[i]^.tick, getticks, time_out_nd(is_NETadr(buff^[i]^.adr)))
                then Del(i)
         else inc(i);


      { b) nacitanie a spracovanie najdolezitejsej spravy,
           ak predpokladame, ze priorita je dana jej typom
      }
      { [1] }
       ind:= select_pkt_ind (kod_lo,spr_DATAlo-1, true);
       if (ind<0) and (not s_ack) then ind:= select_pkt_ind (spr_DATAlo,kod_hi, true);

       if (ind>=0) then
          begin
            indicate_net(1);
            move(buff^[ind]^,pkt,sizeof(TNETpkt));
            fillchar(buff^[ind]^,sizeof(buff^[ind]^),0);
            Del(ind);
            t_data:= pkt.head.typ;
            decode_app_data_pkt(pkt,true);
            disp_NETpkt(@pkt);
            t_data:= 0;
            indicate_net(-1);
          end;
       is_pkt:= (is_pkt) and (top>=0) and (ind>=0);

       s_data:= false
     end;


{ תתתתתתתתתתתתתתתתתתתתתתת
   presmerovanie paketu
  תתתתתתתתתתתתתתתתתתתתתתת
}
 procedure TNET.reroute_pkt;
     var   i : int;
     begin
       if s_reroute then Exit;
       s_reroute:= true;

       i:= 0;
       while (i<=top) do
         if pkt_for_this_node(buff^[i]^) then inc(i)
         else begin
                NETsend_pkt(buff^[i]^,net_flag_SEND,false,'',nil,false);
                Del(i);
                Break;
              end;

       is_reroute:= is_reroute and (i<=top);
       s_reroute:= false
     end;


{ -----------------------------------
   spracovanie prijatych paketov
   alebo ich presmerovanie
  -----------------------------------
}
 procedure TNET.read_net_buff_data;
     begin
       if    (not NET_ENABLED)
          or semaphor_tmp_pkt_r
          or semaphor_tmp_pkt_s then Exit;

       if is_data then read_data_pkt;
     end; { read_net_buff_data }


 procedure TNET.read_net_reroute_pkt;
     begin
       if is_data then reroute_pkt;      { presmerovanie ...         }
     end; { read_net_buff_data }


 procedure TNET.read_net_file_data;
     var   b: bool;
     begin
      { su nejake pakety ulozene v tmp_????.pkt ?

       if (in_file) and (top < items-NETBuffer_MIESTO-1) and (data_size<maxavail) then read_tmp_pkt;
       else begin if sec=0 then in_file:= is_file end;
      }
       if    (not NET_ENABLED)
          or semaphor_tmp_pkt_r
          or semaphor_tmp_pkt_s
          or (not in_file)
          or (top>0)
          then Exit;

       b:= INITIALIZE_EN; INITIALIZE_EN:= false;
       indicate_net(1);
       read_tmp_pkt;
       indicate_net(-1);
       in_file:= is_file;
       if not in_file then cislo_tmp_packet:= 0;
       INITIALIZE_EN:= b
     end;
