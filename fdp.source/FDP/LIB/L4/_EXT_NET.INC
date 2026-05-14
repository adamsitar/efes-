{ Filozofia synchronizacie spociva v tom,
  ze jedna stanica je masterom a rozosiela udaje
  na podriadene stanice.

  Algoritmus sity pre DOS.

  Pre iny OS so spravou suborov sa vyriesi nad spolocnou
  databazou. Jej zalohovanie riesi architektura client-server.

  Kvoli jedinej instalacii pre UKBB s direktivou SYNCHRONIZE_EXT
  a problemom po upgrade je povolena synchronizacia len medzi
  servermi master a slave.
}

 procedure O_EXT._delete_pkt_in_buff (data: pchars; size: word; key: string);
     var   i : int;
     begin
       if cut_(key)='' then key:= _key_data(data,size);
       if cut_(key)='' then Exit;
       i:= 0; while (i<=pbuff^.top) do
         if     (strpas(TExtPkt(pbuff^.ap^[i]^).key)=key)
           {and ((size=0) or (size=TExtPkt(pbuff^.ap^[i]^).dlz))} then
                pbuff^.Del(i)
         else inc(i)
     end;

 procedure O_EXT.delete_pkt (data: pchars; size: word; tit,fn: string;
                             spr: TNETtyp; from: TNETadr;
                             distribute,code_data: bool
                            );
     var   f   : text;
           fd  : string;

           D : DirStr;
           N : NameStr;
           E : ExtStr;

     begin
      { odmazanie paketu z radu paketov cakajucich na spracovanie
      }
       _delete_pkt_in_buff(data,size,'');

      { odmazanie odlozenej chyby
      }
       FSplit(fn, D,N,E);
       if D=pathERR then fn:= D+N+ext_all;
       if GetNmbOfFiles(fn)=0 then Exit;

       {$IFDEF SYNCHRONIZE_EXT}
        if     (distribute or is_distribute_pkt)
           and ((data<>nil) or (fn<>''))
               then distribute_pkt(data,size, tit,fn, spr,from,code_data);

        (*fd:= pathSTREAM + get_ARCHfn(0)+'.'+ext_DEL;
        vytvor_novy_subor(fd);  { aby sa nehromadili opakujuce sa spravy o odmazani  }
        Assign(f,fd);           { eviduje sa len skutocne odmazana sprava            }
        Append(f);              { ak bola v pamati, informacia o tom sa strati       }
        writeln(f,fn);
        Close(f);*)
       {$ENDIF}

       io.del(fn);

       initialize_STATUS(true)
     end;


{$IFDEF SYNCHRONIZE_EXT}

{ -----------------
   rozoslanie dat
  תתתתתתתתתתתתתתתתת
}
{ Stanice smu byt skonfigurovane len skrz
  SERVER a BSERVER
}
 procedure O_EXT.distribute_pkt (data: pchars; size: word; tit,fn: string;
                                 typ: TNETtyp; from: TNETadr;
                                 code_data: bool
                                );
     var   D   : TSYNC_EXTpkt;
           rec : Tplan_rec;

     begin
       NET_checkD;              { aby stihol dovysielat paket }

       rec_data(from,rec);
       fillchar(D,sizeof(D),0);

       if code_data and (data<>nil) then
          begin
            while (size>0) and (data^[size-1] in [' ',kbLF,kbLF_,kbCR,kbCR_]) do dec(size);
            D.data:= data;
            D.size:= size
          end;
       D.tit := tit;
       D.fn  := fn;
       if data<>nil then D.key:= _key_data(data,size);

       {$IFDEF BACKUP}
        if SERVERstatus then
           begin
             if (from<>SERVERaddress) then
                NETsend_data (SERVERaddress,typ,
                              @D,@code_SYNC_EXTpkt,@codekey_SYNC_EXTpkt,nil,
                              true,strpas(sync_info),nil, false,false, net_flag_SEND
                             )
           end
        else NETdistribute_data
                 ([FDP,FDP0NX,FDP0],[SERVER,FDA],[MASTER,SLAVE],
                  typ, @D,@code_SYNC_EXTpkt,@codekey_SYNC_EXTpkt,@rec,
                  true,strpas(sync_info),nil,false,false, net_flag_SEND
                 );
       {$ELSE}
        NETdistribute_data
            ([FDP,FDP0NX,FDP0],[BSERVER,FDA],[MASTER,SLAVE],
             typ, @D,@code_SYNC_EXTpkt,@codekey_SYNC_EXTpkt,@rec,
             true,strpas(sync_info),nil,false,false, net_flag_SEND
            );
       {$ENDIF}

       NET_checkD;  { aby stihol dovysielat paket }
     end;


 procedure O_EXT.update_pkt (data: pchars; size: word; tit,fn: string;
                             spr: TNETtyp; from: TNETadr
                            );
     begin
       if Exists(fn)<>0 then Exit;
       _save_txt_file (fn,tit,data,size,false);
       distribute_pkt (data,size,tit,fn,spr,from,true)
     end;



{ ------------------------
   spracovanie dat z NET
  תתתתתתתתתתתתתתתתתתתתתתתת

  vsetky tieto funkcie by mali byt aktivnie,
  az ked sa vyprazdni buffer sprav od ich prvotneho
  (externeho) zdroja funkciou "ibuff_flush", aby
  nepredbehlo spracovanaie synchronizacnych udajov
  od paralelneho procesu spracovanie dat od ich
  hlavneho zdroja
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function  O_EXT.decode_NETpkt(var pkt: TNETpkt): bool;
    var    res : bool;
           fn  : string;
    begin
      decode_NETpkt:= true;

      if pkt.head.typ = 0 then decode_NETpkt:= false

      else if pkt.head.typ = spr_send_ext then
              begin
                flush_NETpkt_buff (pkt.pkt);
                decode_pkt_spr_send_ext (pkt);
              end

      else if pkt.head.typ = spr_new then
              begin
                ibuff_flush;
                flush_NETpkt_buff (pkt.pkt);
                decode_pkt_spr_new (pkt);
              end

      else if pkt.head.typ = spr_prd then
              begin
                ibuff_flush;
                flush_NETpkt_buff (pkt.pkt);
                decode_pkt_spr_prd (pkt);
              end

      else if pkt.head.typ = spr_ed then
              begin
                if icao_REC_UPDATED then
                   begin
                     ibuff_flush;
                     flush_NETpkt_buff (pkt.pkt);
                     decode_pkt_spr_ed (pkt)
                   end
              end

      else if pkt.head.typ = spr_del then
              begin
                ibuff_flush;
                flush_NETpkt_buff (pkt.pkt);
                decode_pkt_spr_del (pkt);
              end


      else if    (pkt.head.typ = spr_err)
              or (pkt.head.typ = spr_err_ed) then
              begin
                if    (pkt.head.typ=spr_err)
                   or icao_REC_UPDATED
                  then
                   begin
                     ibuff_flush;
                     flush_NETpkt_buff (pkt.pkt);
                     decode_pkt_spr_err (pkt)
                   end
              end

      else if pkt.head.typ = spr_err_del then
              begin
                ibuff_flush;
                flush_NETpkt_buff (pkt.pkt);
                decode_pkt_spr_del (pkt)
              end

      else if pkt.head.typ = spr_items_del then
              begin
                ibuff_flush;
                decode_pkt_spr_items_del (pkt)
              end

      else if pkt.head.typ = spr_item_del then
              begin
                ibuff_flush;
                flush_NETpkt_buff (pkt.pkt);
                decode_pkt_spr_del (pkt)
              end

      else decode_NETpkt:= false
    end;



{ -----------------------------------------
   SEND TO NET->EXT

   odoslanie presmerovaneho paketu :
   - ak je pripojena len jedna EXT linka,
     odoslanie prostrednictvom servera
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure O_EXT.decode_pkt_spr_send_ext(var pkt: TNETpkt);
     var   data : TEXT_EXTpkt;
           res  : string;
     begin
       if not is_distribute_pkt then Exit;

       decode_EXT_EXTpkt (pkt,@data);
       send_pkt(data.typ,data.adr,data.data,data.size);
       disp_EXT_EXTpkt(@data)
     end;


{ -----------------------------------------
   RECEIVE

   prijem novej spravy :
   - porovnanie, ci takato sprava uz prisla
     (jedna z liniek mohla zlyhat),
     ak nie, jej zaradenie ako novej spravy
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure O_EXT.decode_pkt_spr_new (var pkt: TNETpkt);
     var   data : TSYNC_EXTpkt;
           res  : string;
     begin
       decode_SYNC_EXTpkt(pkt,@data);
{1510} receive_pkt(src_net, pkt.ods, data.data,data.size, res, false{is_distribute_pkt});
       disp_SYNC_EXTpkt(@data)
     end;


{ -----------------------------------------
   PROCESS

   sprava o spracovani spravy
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure O_EXT.decode_pkt_spr_prd (var pkt: TNETpkt);
     var   data : TSYNC_EXTpkt;
     begin
       decode_SYNC_EXTpkt(pkt,@data);
{1510} {if data.fn<>'' then delete_pkt (data.data, data.size, data.tit,data.fn, pkt.head.typ, pkt.ods, false,false)
       else} _delete_pkt_in_buff (data.data,data.size, data.key);
       disp_SYNC_EXTpkt(@data)
     end;


{ -----------------------------------------
   ERROR

   rozoslanie chyby alebo jej opravy v nej:
   - (pretoze ho dekoduje) len aktivny
     server alebo ostatne stanice po jej
     spracovani
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure O_EXT.error_pkt (data: pchars; size: word; tit,fn: string; edit: bool);
     begin
       if edit or is_distribute_pkt then distribute_pkt (data,size, tit,fn, spr_err, '',true)
     end;

 procedure O_EXT.decode_pkt_spr_err (var pkt: TNETpkt);
     var   data : TSYNC_EXTpkt;
     begin
       decode_SYNC_EXTpkt (pkt,@data);
       process_ERR_DATA (src_net,data.data,data.size,data.tit, true,pkt.head.typ=spr_err,false);
{1510  if is_distribute_pkt then distribute_pkt (data.data,data.size, data.tit,data.fn,pkt.head.typ,pkt.ods,true);}
       writeln_pkt (nil,0, '','', cl_r,true,false);
       Mail (@Self,cmEditRefresh, One, @data,sizeof(data));
       disp_SYNC_EXTpkt (@data)
     end;


{ ------------------------------------------------
  EDIT

  Sprava bola editovana, zanesenie oprav...
  Sprava o oprave paketu, spracuje sa, len ak
  existuje na disku, t.j. nebol medzitym odmazany
  inym pracoviskom


  Editovanu spravu spracovava stanica, ktora je v rezime
  MASTER, ako prijatu, ostatne stanice data len ulozia.
  Ak MASTER udaje spracuje, rozosle o tom spravu.

  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure O_EXT.process_pkt_spr_ed(var data : TSYNC_EXTpkt);
     var   head,res : string;
     begin
       process_pkt (src_net, data.data,data.size, head,res, false {1510 is_distribute_pkt});
     end;

 procedure O_EXT.decode_pkt_spr_ed(var pkt: TNETpkt);
     var   head,res : string;
           data : TSYNC_EXTpkt;
     begin
       decode_SYNC_EXTpkt (pkt,@data);
       if is_distribute_pkt then
          begin
            {distribute_pkt (data.data,data.size, data.tit,data.fn,spr_ed,pkt.ods,true);}
            process_pkt_spr_ed(data);
          end
       else begin
              _save_txt_file (data.fn{_fn_data(data.data,data.size)}, data.tit, data.data,data.size, false)
            end;
       Mail (@Self, cmEditRefresh, One, @data,sizeof(data));
       disp_SYNC_EXTpkt(@data)
     end;


{ -------------------------------------
  DELETE

  spracovana/odmazana [chybova] sprava
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure O_EXT.decode_pkt_spr_del(var pkt: TNETpkt);
     var   data : TSYNC_EXTpkt;
           D : DirStr;
           N : NameStr;
           E : ExtStr;

     begin
       decode_SYNC_EXTpkt (pkt,@data);
       if (data.fn<>'') then
          begin
            if pkt.head.typ = spr_err_del then
               begin
                 FSplit(data.fn,D,N,E);
                 data.fn:= D+N+ext_all
               end
          end
       else if (data.data<>nil) and (data.size<>0) then
               begin
                 if pkt.head.typ = spr_err_del then data.fn:= pathERR+_fn_ERR(data.data,data.size,ext_all)
                 else if pkt.head.typ = spr_del then data.fn:= _path_data(data.data,data.size)+_fn_data(data.data,data.size)
               end;
       if data.fn<>'' then delete_pkt (data.data, data.size, data.tit,data.fn, pkt.head.typ, pkt.ods, false,false);
       Mail (@Self, cmEditDelete, One, @data,sizeof(data));
       disp_SYNC_EXTpkt (@data);
     end;


{ ------------------------------------------------
  odoslanie suhrnu sprav a nazvov ich suborov
  o spracovanych paketoch
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

 function O_EXT.node_initialize_files (nd: int): bool;
    var   Dir : PDir;
          Files, i : int;
          f  : text;
          fn : string;
    begin
      node_initialize_files:= true;
      Exit;

      (*if    (not is_to_nd(nd,strpas(sync_info),nil,nil))
         or (GetDirFiles(pathSTREAM,'*.'+ext_DEL,Dir,Files)=0)
            then Exit;

      i:= 0;
      while (i<Files) and (NODEs^[nd].stat.TrasaOK) do
        begin
          vypnute 30.7.99

           NETsend_file (NODEs^[nd].desc.adr,
                        spr_items_del,
                        pathSTREAM+Dir^[i]^.name,
                        strpas(sync_info), net_flag_NIL,
                        true,false,true
                       );


         {
          assign(f,pathSTREAM+Dir^[i]^.name);
          reset(f);
          while (not (Eof(f))) and (NODEs^[nd].stat.TrasaOK) do
            begin
              readln(f,fn);
              if fn<>''then
                 NETsend_data (NODEs^[nd].desc.adr,spr_items_del,
                               @fn[0], @code_msg,nil,nil,
                               info,nil,true,false,
                               net_flag_NIL
                              )
            end;
          close(f);
         }
          inc(i);
        end;
      FreeDirFiles(Dir, Files);*)

      node_initialize_files:= NODEs^[nd].stat.TrasaOK
    end;


 procedure O_EXT.decode_pkt_spr_items_del (var pkt: TNETpkt);
     var   fn,fr,fd : string;
           f : text;
     begin
     (*
      { nevyhoda - caka spracovanie ostatnych sprav...
      }
       NETreceive_file (pkt, fn,fr, nil, nil,true,false,false);
       if Exists(fr)<>0 then Exit;
       {fr:= NETreceived_file_name (fn);}
       assign(f,fr); reset(f);
       while (not (Eof(f))) do
         begin
           readln(f,fd);
           delete_pkt (nil,0,'',fd,spr_item_del,pkt.ods,false,false)
         end;
       close(f);
       delfile(fr);
       {nevyhoda - vela paketov
       decode_msg (pkt.pkt, pkt.ods, fn);
       delete_pkt (nil,0,'',fn,spr_items_del,pkt.ods)}
     *)
     end;

{$ENDIF}
