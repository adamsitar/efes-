{ ---------------
  send
  ---------------
}

{ - potvrdenie prijmu subora sa uklada do subora obsahujuceho
    len strukturu Tplan_rec;
  - subor ma nazov podla odosielaneho subora
    s nahradenym extensnom na 'net'
  - pre subory s rozsirenim 'net' sa potvrdenie nezapisuje
}

 type   Pdb_rec = ^Tdb_rec;
        Tdb_rec = record
          rec : Tplan_rec;
          fn  : string;
        end;


 const  db_rec_riadkov = 1;
        db_rec_data    = 0;


 procedure codeDB_rec(rec: Pdb_rec; buff: PDB_buff; desc: PDB_head); far;
     begin
       str_toDBstr(init_str(@rec^.rec,sizeof(rec^.rec)),buff^[db_rec_data]);
     end;

 procedure decodeDB_rec(buff: PDB_buff; rec: Pdb_rec; desc: PDB_head); far;
     var   s : string;
     begin
       s:= DBstr_to_str(buff^[db_rec_data]);
       if rec<>nil then move(s[1], rec^.rec, minimum(sizeof(rec^.rec),length(s)))
     end;

 function codekey_rec(rec: Pdb_rec): string; far;
    begin
      codekey_rec:= rec^.fn
    end;


 function read_file_rec (fr: string; isrecdb: bool; var rec: Tplan_rec): bool;
    var   fn  : string;
          P   : PathStr;
          D   : DirStr;
          N   : NameStr;
          E   : ExtStr;
          db  : PDB;
          dbr : Tdb_rec;
          f   : file;
          pos : word;
    begin
      read_file_rec:= false;
      fillchar(rec,sizeof(rec),0);

      FSplit(fr, D,N,E);
      fn:= D+N+'.'+extNET;
      if (fn=fr) or (Exists(fn)<>0) then Exit;

      if isrecdb then
         begin
           dbr.fn:= {D+}N+E;
           dbr.rec:= rec;
           db:= New(PDB,Init(fn,DB_RWClose,db_rec_riadkov,@codeDB_rec,@decodeDB_rec,@codekey_rec,nil,DBbin));
           if db^.najdi(@dbr,true,nil)>-1 then rec:= dbr.rec;
           Dispose(db,Done);
           read_file_rec:= pos>-1
         end
      else begin
             assign(f,fn); reset(f,1);
             blockread(f,rec,sizeof(rec),pos);
             close(f);
             read_file_rec:= sizeof(rec)=pos
           end
    end;


 function write_file_rec (fr: string; isrecdb: bool; rec: Tplan_rec): bool;
    var   fn  : string;
          P   : PathStr;
          D   : DirStr;
          N   : NameStr;
          E   : ExtStr;
          db  : PDB;
          dbr : Tdb_rec;
          f   : file;
          pos : word;
    begin
      write_file_rec:= false;
      FSplit(fr, D, N, E);
      fn:= D+N+'.'+extNET;
      if (fn=fr) then Exit;

      if isrecdb then
         begin
           dbr.fn:= {D+}N+E;
           dbr.rec:= rec;
           db:= New(PDB,Init(fn,DB_RWClose,db_rec_riadkov,@codeDB_rec,@decodeDB_rec,@codekey_rec,nil,DBbin));
           db^.oprav(@dbr);
           Dispose(db,Done);
           write_file_rec:= true
         end
      else begin
             assign(f,fn); rewrite(f,1);
             blockwrite(f,rec,sizeof(rec),pos);
             close(f);
             write_file_rec:= true
           end
    end;


 procedure file_rec (nd: int; fn: string; isrecdb: bool; what: char; clear: bool);
     var   rec : Tplan_rec;
     begin
       if clear then fillchar(rec,sizeof(rec),0) else read_file_rec (fn,isrecdb,rec);
       if clear or rec_pkt (nd,rec,what) then write_file_rec (fn,isrecdb,rec)
     end;


{ - odoslanie subora;
  - suboru sa predradi jeho meno zacinajuce byte s dlzkou mena
    a konciace znakom NULL zapocitanym do dlzky mena
}
 function  TNET.send_file (adr      : TNETadr;
                           typ      : word;

                           fn       : string;
                           id       : PNETpkt_head;

                           info     : string;
                           flag     : word;    { i ked nie je spojenie [udp?] }

                           ispath,isext : bool;
                           isrec,isrecdb : bool;
                           isbmode : bool
                          ): int;

    var   pkt : TNETpkt;
          nd  : int;

          D   : DirStr;
          N   : string;
          E   : ExtStr;

          dlz,pos : TNETdlz;

          f    : file;
          numr : word;

          data : PNET0pkt_data;
          rec  : Tplan_rec;

          p : pchar;
          i : word;
          ires : int;

    begin
      send_file:= netNOT_SENDED;
      if Exists(fn)<>0 then Exit;

      nd:= is_NETadr(adr);
      if {$IFDEF BACKUP}
             (isbmode and SERVERstatus and (nd<>SERVERnode))
          or
         {$ENDIF}
             (not is_to_nd(nd, info,nil,nil,nil))
          or (FExists(fn)<>0) then
             Exit;

      if ispath then N:= fn
      else begin
             FSplit(fn,D,N,E);
             if isext and (E<>'') then N:= N+E
           end;

     { aktualizacia povodneho rec
     }
      {if isrec and (nd>-1) and read_file_rec (fn,rec) then rec[nd]:= no_ack;}
      if isrec then file_rec (nd,fn,isrecdb,no_ack,false);

     { zakodovanie paketu
     }
      ires:= netRES_OK;
      fillchar(pkt,sizeof(pkt),0);
      net_pkt_head (pkt, typ, adr);
      {N:= N+NULL;}
      dlz:= 1+length(N) + _filesize(fn);

      new(data);
      {$IFDEF NOEMS}
       if (dlz<high(TNETdlz)) and new_NETpkt_data(nil,dlz,pkt.pkt) then
      {$ELSE}
       pkt.pkt.bufe:= New(PstreamBuffer,Init(1,length(fn)+1));
       if (pkt.pkt.bufe<>nil) and (pkt.pkt.bufe^.is) then
      {$ENDIF}
          begin
            pos:= 1+length(N);
            {$IFDEF NOEMS}
             move(N[0],pkt.pkt.data^[0],1+length(N));
            {$ELSE}
             pkt.pkt.bufe^.add_to_buffer(N[0],1+length(N));
            {$ENDIF}

            assign(f,fn); reset (f,1);
            repeat
              blockread (f,data^,sizeof(data^)-1,numr);
              if (numr>0) then
                 begin
                  {$IFDEF NOEMS}
                   if pos+numr <= dlz then
                      begin
                        move(data^,pkt.pkt.data^[pos],numr);
                        pos:= pos+numr
                      end;
                  {$ELSE}
                   pkt.pkt.bufe^.add_to_buffer (data^,numr);
                  {$ENDIF}
                 end;
            until (numr=0) or (numr<sizeof(data^)-1);
            close (f);
          end
      else ires:= netNOT_BUFFER;

      if ires=netRES_OK then
         begin
           net_pkt_data (pkt, 0,nil);
           send_file:= NETsend_pkt (pkt,flag,true,fn,id,false);
         end;

      send_file:= ires;
      disp_NETpkt(@pkt);
      dispose(data);
    end;


 function TNET.distribute_file
                       (tp      : Tnd_typ_set;
                        sw      : Tnd_sw_set;
                        nd      : Tnd_nd_set;
                        typ     : word;

                        fn      : string;
                        info    : string;
                        flag    : word;    { i ked nie je spojenie [udp?] }

                        ispath,isext : bool;
                        isrec,isrecdb : bool;
                        isbmode : bool
                       ): bool;

    var   send_to : TBplan_rec;
          rec     : Tplan_rec;
          i,pocet : int;

    begin
      distribute_file:= false;

      if (FExists(fn)<>0) then Exit;

     { nacitanie povodneho rec, aby mohlo byt urcene,
       na ktore smery bude sprava odoslana
     }
      if isrec then read_file_rec (fn,isrecdb,rec);

     { zistenie smerov, kam odosielat
     }
       fillchar(send_to,sizeof(send_to),0);
       pocet:= 0;
       for i:= 0 to NODEpoc-1 do
         begin
           send_to[i]:= ( {$IFDEF BACKUP}
                           { len na hlavny server, ak pracuje;
                             alebo ak nie, tak i na ostatnie
                           }
                               ((not SERVERstatus) or (i=SERVERnode))
                           and
                          {$ENDIF}

                          { ak z tohto smeru nebola prijata iformacia a patri tam
                          }
                               ((not isrec) or (not (rec[i] in [is_rec,no_send])))
                          and  is_nd_type (i, tp,sw,nd)
                          and  is_to_nd   (i, info,nil,nil,nil)
                        );
           if send_to[i] then inc(pocet)
         end;

       distribute_file:= pocet<>0;
       if pocet=0 then Exit;

     { odoslanie rovnako kodovanej spravy na rozne smery
     }
       for i:= 0 to NODEpoc-1 do
         if send_to[i] then
            begin
              send_file (NODEs^[i].desc.adr,
                         typ, fn, nil,
                         info,flag,
                         ispath,isext,
                         isrec,isrecdb,
                         isbmode
                        )
            end;
    end;



{ ---------------
  receive
  ---------------

 to uz neplati :
  - prijaty subor sa ulozi s rovnamym menom ako obsahuje sprava,
    ale rozsirenie je nahradene za 'tmp';
  - volajuca fcia zabezpeci spracovanie 'tmp' subora;

 ale teraz toto : subor sa ulozi, az ked je spracovany cely

}

 function  NETreceived_file_name (fn: string): string;
    var    D : DirStr;
           N : NameStr;
           E : ExtStr;
    begin
      FSplit(fn,D,N,E);
      {if length(E)=EXT+1 then E[EXT+1]:= net_FILE_EXT
      else E:= E+net_FILE_EXT;}
      NETreceived_file_name:= D+N+extTMP
    end;


 function  TNET.receive_file (var pkt : TNETpkt;
                              var fn,fr : string;  { meno posielaneho a prijateho (docasneho) subora }
                              p_fn   : PSFunc_s;   { fcia pre urcenie mena }
                              isname : bool;       { prijima sa uplne meno ? }
                              isnl   : bool;
                              isrec,isrecdb : bool
                             ): string;

    var    data : pchars;
           dlz, numm,numr,numc : word;
           s : string;
           f : file;
           rece : Tplan_rec;
           pos,zac,i : word;
           err,isf,isb : bool;

           D : DirStr;
           N : NameStr;
           E : ExtStr;

    begin
      receive_file:= '';

      {data:= nil; dlz:= 0;}
      pos:= 0; fn:= ''; fr:= '';
      err:= false;
      isf:= false;
      isb:= (pkt.pkt.bufe<>nil) and (pkt.pkt.bufe^.is);

      if isb then numm:= pkt.pkt.bufe^.size
      else numm:= pkt.pkt.dlz;

      numr:= 0;
      while {(pos<=pkt.head.poc) and} (numr<numm) and (not err) do
        begin

          if isb then err:= not pkt.pkt.bufe^.read_buffer_int (numr,size_of_NETdata, data,dlz, false)
          else if (pkt.pkt.data<>nil) then
                  begin
                    err:= not AllocCopyMem(pointer(data),pkt.pkt.dlz,pkt.pkt.data);
                    dlz:= pkt.pkt.dlz
                  end
          else err:= true;
          if err then break;

          zac:= 0;
          if pos=0 then
             begin
             { odfiltrovanie a ziskanie mena subora
             }
               move(data^[0],fn[0],1+ord(data^[0]));

               fn:= cut_(fn);
               zac:= 1+length(fn);
               if p_fn<>nil then fr:= TSFunc_s(p_fn)(fn)
               else if isname then fr:= fn
               else fr:= NETreceived_file_name(fn);

               assign (f,fr);
               rewrite (f,1);
               close (f);
               isf:= FExists(fr)=0;
               if isf then rewrite (f,1)
               else err:= true;
             end;

          if not err then
             begin
               if isnl then pNL__to_NL(@data^[zac],dlz-zac);
               blockwrite(f, data^[zac], dlz-(zac),numc)
             end;

          DeallocMem(pointer(data),dlz); { alokovane v read_buffer_int }
          inc(numr,dlz);
          inc(pos)
        end;

      if isf then
         begin
           close(f);
           if isrec then file_rec (is_NETadr(pkt.ods),fr,isrecdb,is_rec,false);
         end;

      if (pos>=pkt.head.poc) then receive_file:= fr
      {else if (fr<>'') then delfile(fr)}
    end;


{ ---------------
  volane funkcie
  ---------------
}

 function NETsend_file (adr      : TNETadr;
                        typ      : word;

                        fn       : string;

                        info     : string;
                        flag     : word;    { i ked nie je spojenie [udp?] }

                        ispath,isext : bool;
                        isrec,isrecdb : bool;
                        isbmode : bool
                       ): int;
    begin
      if NET<>nil then NETsend_file:= NET^.send_file(adr,typ,fn,nil,info,flag,ispath,isext,isrec,isrecdb,isbmode)
    end;


 function NETdistribute_file
                       (tp      : Tnd_typ_set;
                        sw      : Tnd_sw_set;
                        nd      : Tnd_nd_set;
                        typ     : word;

                        fn      : string;
                        info    : string;
                        flag    : word;    { i ked nie je spojenie [udp?] }

                        ispath,isext : bool;
                        isrec,isrecdb : bool;
                        isbmode : bool
                       ): bool;
    begin
      if NET<>nil then NET^.distribute_file(tp,sw,nd, typ, fn,info,flag, ispath,isext,isrec,isrecdb,isbmode)
    end;


 function  NETreceive_file (var pkt : TNETpkt;
                            var fn,fr : string;  { meno posielaneho a prijateho (docasneho) subora }
                            p_fn   : PSFunc_s;   { fcia pre urcenie mena }
                            isname : bool;       { spracovava sa uplne meno ? }
                            isnl   : bool;
                            isrec,isrecdb : bool
                           ): string;
    begin
      if NET<>nil then NETreceive_file:= NET^.receive_file(pkt, fn,fr, p_fn, isname,isnl,isrec,isrecdb)
    end;
