{ Urci skutocnu dlzku paketu a adresu dat
}
 function O_EXT.get_pkt_size(pkt: pointer): word;
    begin
      if is_ibuff0 then get_pkt_size:= strlen(pchar(pkt))
      else get_pkt_size:= ipkt_size
    end;

 function O_EXT.get_pkt_comprimed_size(pkt: pointer): word;
    begin
      get_pkt_comprimed_size:= 0
    end;

 function O_EXT.get_pkt_data(pkt: pointer): pointer;
    begin
      get_pkt_data:= pkt
    end;


{ -------------------------------------------
   Spracovanie paketov od Externej linky
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

   - dekodovanie, archivovanie, rozoslanie
     a spracovanie (aktivny MASTER)
     alebo podrzanie (aktivny BACKUP)
   - nesmie sa zdrziavat, ani paket spracovavat
}

{ citanie z fyzickeho portu a naplnenie vstupneo buffera ibuff
}
 function  O_EXT.read_inp_buff: bool;
    begin
      read_inp_buff:= false
    end;


 function  O_EXT.check_pkt_frame(data: pchars; size: word; var res: string): bool;
    begin
      check_pkt_frame:= true
    end;


 function  O_EXT.ibuff_read: bool;

    const  S_READ : bool = false;

    var    data   : pchars;
           size   : long;
           res,s  : string;
           bres   : bool;

    begin
      ibuff_read:= false;
      if (S_READ) or (ibuff=nil) or (not ibuff^.is) or (ipkt_size>=MaxAvail) then Exit;

      {$IFDEF DEBUG}
       {s:= 'iread'; writeln_pkt(@s[1],length(s), '!','',white,false,true);}
      {$ENDIF}

      S_READ:= true;

     { Nacitanie dat zo vstupneho buffera (od vstupnej linky EXT)
     }
      if is_ibuff0 then
         begin
           bres:= ibuff^.readv(rpkt);
           data:= pchars(rpkt);
           size:= strlen(pchar(rpkt))
         end
      else begin
             bres:= ibuff^.read(rpkt);
             data:= get_pkt_data(rpkt);
             size:= get_pkt_size(rpkt)
           end;

     { Dekodovanie dat, vydanie spravy o ich prijme (archive,writeln,distribute)
       a ich ulozenie do buffera spracovanych paketov, kde cakaju na sekvence
       spracovanie, ak je stanica aktivna, alebo na to, kym nie su potvrdene,
       alebo timeoutovane, ak je stanica v zaloznom mode.
     }
      if not bres then
         begin
           S_READ:= false;
           Exit;
         end;

      Tr_:= absTime;

      res:= '';
      if not check_pkt_frame(data,size, res) then res:= err_ext_invalid_packet_frame;

      if res='' then
         begin
           {$IFDEF DEBUG} if not testing_txt_file then bres:= decode_pkt(data,size, res)
                          else bres:= true;
           {$ELSE}        bres:= decode_pkt(data,size, res);
           {$ENDIF}

           if bres then receive_pkt (src_ext, '', data,size,res, true)
           else res:= err_ext_unable_decode_packet
         end;

      if (res<>'') then
         begin
           writeln_pkt (data,size, arch_PKT_REC,'', cl_r,false,false);
           writeln_pkt (@res[1],length(res), arch_ERR,'', cl_r,false,false);
         end;

      if is_ibuff0 then StrDispose(pchar(rpkt));

      S_READ:= false;
      ibuff_read:= true
    end;


{ ----------------------------------------------
   Funkcia pre zaradenie paketu
   do buffera spracovavanych paketov;
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

   - nesmie sa zdrziavat, ani spracovavat paket
}

 function O_EXT.receive_pkt (src: TPKT_SRC; from: string;
                             data: pchars; size: word; var res: string;
                             distribute : bool
                            ): bool;

    var   key,prompt,s,head : string;
          Ip : TIREGpkt;
          Ep : TEXTpkt;

          is_sys_pkt : bool;
          i : int;

    begin
      receive_pkt:= false;
      res:= '';

      if (src=src_ext) then Tr_:= absTime;


    { registrovanie paketu kvoli zamedzeniu viacnasobneho
      spracovania paketu pri zalohovani vstupnych zdrojov,
      a vyhodenie identickeho paketu
    }
     {$IFDEF SYNCHRONIZE_EXT}
      key:= _key_data (data,size);
      if is_ireg and (ireg<>nil) and (key<>'') then
         begin
           if (src<>src_ed) then
              begin
                i:= 0;
                while (i<=ireg^.top)
                  and (   (strpas(PIREGpkt(ireg^.ap^[i])^.key)<>key)
                       or (PIREGpkt(ireg^.ap^[i])^.dlz<>size)
                      )
                do inc(i);
                if (i<=ireg^.top) then Exit {begin res:= err_ext_packet_exists; Exit end}
              end;

           if (res='') then
              begin
                make_REGpkt(key,size, Ip);
                ireg^.Add2 (@Ip);
                disp_REGpkt(@Ip)
              end;
         end;
     {$ENDIF}


    { archivovanie paketu
    }
      is_sys_pkt:= is_system_pkt(data,size,res);

      if src=src_ext then prompt:= arch_PKT_REC
      else if src=src_net then prompt:= arch_PKT_RECN
      else prompt:= arch_PKT_RECE;
      {if (src=src_ext) and (is_sys_pkt or archive_all_en) then writeln_pkt(data,size, prompt,'', cl_r,false,false);}
      if (src=src_ext) then writeln_pkt(data,size, prompt,'', cl_r,false,false);

      receive_pkt:= true;
      if (res<>'') or is_sys_pkt then Exit;

    { zaradenie paketu do bufferov sprav ocakavajucich spracovanie,
      okamzite potrvrdenie prijmu spravy, ak je to pozadovane,
      inak je sprava potvrdena az po spracovani...
    }
      if not (process_all_adr or is_pkt_for_node('', data,size)) then
         begin
           res:= err_ext_sender_address;
           Exit
         end;

      {if (src=src_ext) and (not archive_all_en) then writeln_pkt(data,size,prompt,'',cl_r,false,false);}

    {$IFDEF SYNCHRONIZE_EXT}
    { - rozoslanie prijatych paketov na ostatne stanice kvoli zalohovaniu vstupov
      - len src_ext (neviem odkial prisiel paket)
    } {if distribute then distribute_pkt(data,size,'','',spr_new,from,true);}
    {$ENDIF}

    { spracovanie : okamzite alebo zaradenie do buffera spracovanych paketov
    }
      if { IFDEF BACKUP} is_receive_pkt and { ENDIF} okamzite_spracovanie then
         begin
           process_pkt(src, data,size,head,res,true);
           res:= ''; { aby sa neopakoval vypis spravy }
         end
      else begin
             make_EXTpkt(src, data,size, key, Ep);
             if (pbuff<>nil) then pbuff^.Add(@Ep);
             disp_EXTpkt(@Ep);

            { potvrdenie paketu
            }
              { IFDEF BACKUP}
               if is_receive_pkt then
              { ENDIF}
              if (src=src_ext) and (LAM_pred_spracovanim) then LAM_received_pkt (data,size);
           end;

      {CheckProcesses;}
    end;


 procedure O_EXT.ibuff_flush;
     begin
       while ibuff_read do CheckProcesses;
     end;


{ ----------------------------------------------
   Spracovanie paketov z vyrovanavacieho buffera
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function  O_EXT.pbuff_read: bool;

    const  S_READ : bool = false;

    var    data   : pchars;
           size,i : word;
           Ep     : TEXTpkt;
           res,head,s : string;

    label  X;

    begin
      pbuff_read:= false;
      if (S_READ) or (pbuff=nil) or (not pbuff^.is_data) then Exit;

      S_READ:= true;
      { IFDEF BACKUP}
       if not is_receive_pkt then
          begin
          { V bufferi sa dlzia posledne prijate spravy, pre istotu,
            ak by master vypadol. Vtedy zostanu nespracovane spravy
            nabufferovane.
          } {if (spr_prd=0) then}
               begin
                 i:= 0; while (i<=pbuff^.top) do with TExtPkt(pbuff^.ap^[i]^) do
                 if    ((pkt.bufe=nil) and (pkt.data=nil))
                    or TimeOut(tick,getticks, 10*time_out_nd(SERVERnode)) then
                    pbuff^.Del(i)
                 else inc(i)
               end;
            goto X
          end;
      { ENDIF}

      new_EXTpkt(PEXTpkt(pbuff^.ap^[0]),@Ep);
      pbuff^.Del(0);
      if read_EXTpkt(@Ep, data,size) then
         begin
           indicate_ext(1);
           process_pkt(Ep.src, data,size,head, res, true);
           if (data<>nil) then FreeMem(data,size);
           indicate_ext(-1);
         end;
      disp_EXTpkt(@Ep);

      {CheckProcesses;}
      X: S_READ:= false;
      pbuff_read:= true
    end;
