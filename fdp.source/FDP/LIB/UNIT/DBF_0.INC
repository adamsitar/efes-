{$IFDEF DB_DBASE}

 function code_field(f: TDBFfdesc): string;
    var   s,t : string;
          p : int;
          d : TDBFfield;
    begin
      fillchar(s,sizeof(s)-1,dbf_FILL_HEADER);
      p:= sizeof(d.name);
      move(f.name[1],s[1],minimum(p,length(f.name)));
      s[p+2]:= f.typ;
      p:=   p
          + sizeof(d.typ)
          + sizeof(d.offset) + sizeof(d.r1);
      move(f.dlz,s[p+2],sizeof(d.size));
      s[0]:= chr(sizeof(TDBFfield));
      code_field:= copy(s,1,sizeof(TDBFfield));
    end;


 procedure code_dbf_STRING(s: string; buff: PDBF_buff; var pos: int; dlz,size: int);
     var   l : int;
     begin
       if pos+dlz <= size then
          begin
            l:= minimum(length(s),dlz);
            move(s[1],buff^[pos],l)
          end;
       inc(pos,dlz);
     end;

 procedure code_dbf_CISLO(cis: long; buff: PDBF_buff; var pos: int; dlz,size: int);
     begin
       code_dbf_STRING(cstr(cis,dlz),buff,pos,dlz,size);
     end;



 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                                                          €
 € TDBF                                                     €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }

 constructor TDBF.Init(_FN      : string;
                       _RWClose : bool;

                       _polia : PDBFfdescs;
                       _poli  : byte;

                       _DATAcode   : pointer; { @TDBFcode_proc    }
                       _DATAdecode : pointer; { @TDBFdecode_proc  }
                       _kluc       : int      { pozicia pre kluc }
                      );

       var   _zac,_dlz, l1,l2, nacitanych,attr : word;
             s : string;
             i : int;

       begin
         indicate_db(1);

         FN:= _FN;
         RWClose:= _RWClose;
         zapisane:= false;
         semaphor:= false;

         DATAcode := _DATAcode;
         DATAdecode := _DATAdecode;
         kluc := _kluc;

         polia := _polia;
         poli  := _poli;

       { precitanie hlavicky a z nej parametrov
         ak sa lisia od zadanych parametrov,
         ktore su nenulove,
         zakazat zapis do db
       }
         _zac:= sizeof(TDBFfield) + 1;
         _dlz:= 1;
         if polia<>nil then
            begin
              l1:= poli;
              _zac:= _zac + l1*sizeof(TDBFfield);
              for i:= 0 to poli-1 do
                  begin
                    l1:= polia^[i].dlz;
                    _dlz:= _dlz + l1;
                  end;
            end;

         fillchar(head,sizeof(head),dbf_FILL_HEADER);
         with head do
           begin
             X:= dbf_START_OF_FILE_03;
             rok:= year mod 100;
             mes:= month;
             den:= day;
             poc:= 0;
             zac:= _zac;
             dlz:= _dlz;
           end;

         resetIOError;
         assign(DBf,FN);
         FNExist:= FExists(FN)=0;
         if (FNExist) then
            begin
              Reset(DBf,sizeof(head));
              BlockRead(DBf,head,1,nacitanych);
              Close(DBf);
            end;

         if (not RWClose) and (FNExist) then Reset(DBf,1);

         buff_size:= head.dlz;
         GetMem(buff,head.dlz);

         ResetIOError
       end;


 destructor TDBF.Done;
      begin
        if (not RWClose) and (FNExist) then Close(DBf);
        ResetIOError;
        FreeMem(buff,buff_size);

        indicate_db(-1);
      end;


 {
  ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
  €                     €
  € nizsia uroven       €
  €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 function TDBF.poloziek: long;
    begin
      poloziek:= 0;
      if (not FNExist) then Exit;

      ResetIOError;
      if (RWClose) then Reset(DBf,1);
      poloziek:= (FileSize(DBf)-1-head.zac) div (head.dlz);
      if (RWClose) then Close(DBf);
      ResetIOError
    end;


 function  TDBF.citaj_vetu(_pos: long): bool;
     var   i   : int;
           res : bool;
           nacitanych : word;
           pos,ofs : long;
     begin
       ResetIOError;
       if RWClose then Reset(DBf,1);
       _pos:= N(minimum(_pos,poloziek));
      {$I+}
       ofs:= head.dlz;
       pos:= head.zac; pos:= pos + ofs*_pos;
       Seek(DBf,pos);
       BlockRead(DBf,buff,head.dlz,nacitanych);
       res:= nacitanych=head.dlz;
      {$I-}
       if RWClose then Close(DBf);
       ResetIOError;
       citaj_vetu:= res
     end;


{ poloha 0..poc-1
}
 procedure TDBF.zapis_vetu(_pos: long; _ins: bool);
     var   i, riadkov : int;
           zapisanych : word;
           p,l1,l2 : long;
           s : string;
           b : byte;
     label X;

     begin
       ResetIOError;

      { vytvorenie hlavicky subora, ak subor nexistuje
      }
       if (not FNExist) then
          begin
            Rewrite(DBf,1);
           {$I+}
            BlockWrite(DBf,head,sizeof(head),zapisanych);
           {$I-}
            if polia<>nil then
               for i:= 0 to poli-1 do
                 begin
                   s:= code_field(polia^[i]);
                   BlockWrite(DBf,s[1],sizeof(TDBFfield),zapisanych);
                 end;
            b:= dbf_END_OF_HEADER;
            BlockWrite(DBf,b,sizeof(b),zapisanych);
            FNExist:= true
          end
       else if RWClose then Reset(DBf,1);

      { zapis udajov
      }
       if _pos<0 then p:= head.poc else p:= minimum(head.poc,_pos);
      {$I+}
       l1:= head.zac; l2:= head.dlz;
       l1:= l1 + l2*p;
       Seek(DBf, l1);
       BlockWrite(DBf,buff^,head.dlz,zapisanych);
      {$I-}

       zapisane:= true;
       if p = head.poc then
          begin
            head.poc:= p+1;
            b:= dbf_END_OF_DATA;
            BlockWrite(DBf,b,sizeof(b),zapisanych);
          end;

      { ak bola pridana dalsia polozka, aktualizacia udajov
        o poslednom zapise : o datume vytvorenia a pocte poloziek
      }
       if zapisane then
          begin
            with head do
              begin
                rok:= year mod 100;
                mes:= month;
                den:= day;
              end;
            Seek(DBf,0);
            BlockWrite(DBf,head,1,zapisanych);
          end;

       X:
       if RWClose then Close(DBf);
       ResetIOError
     end;


 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € vyssia uroven       €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }

 procedure TDBF.koduj_vetu(p: pointer);
     var   i: int;
     begin
       FillChar(buff^,buff_size,dbf_FILL_DATA);
       if (DATAcode<>nil) and (p<>nil) then TDBFcode_proc(DATAcode)(p,@buff^[1],buff_size-1{,polia});
     end;

 procedure TDBF.dekoduj_vetu(p: pointer);
     begin
       if (DATAdecode<>nil) and (p<>nil) then TDBFdecode_proc(DATAdecode)(@buff^[1],p,buff_size-1{,polia})
     end;


 function  TDBF.citaj (_pos: long; _data: pointer): bool;
    var    r : bool;
    begin
      if (FNExist) and (_pos<poloziek) then
         begin
           r:= citaj_vetu(_pos);
           if r then dekoduj_vetu(_data);
           citaj:= r
         end
      else citaj:= false
    end;
(*
 {
   hlada _data podla kluca v DB a data nahraje do _data
 }
 function  TDB.najdi(_data: pointer; _read: bool; _disp_data: pointer): long;
    var    _pos: long;
    begin
      _pos:= vyhladaj_data(_data);
      if (_pos>-1) and (_read) then
         begin
           if _disp_data<>nil then TProc_p(_disp_data)(_data);
           if not citaj(_pos, _data) then _pos:= -1;
         end;
      najdi:= _pos
    end;

 {
   hlada nil data
 }
 function TDB.najdi_nil: long;
    var   pos : long;
          res : bool;
          nacitanych : word;
    begin
      najdi_nil:= -1;
      if NOSAVE then Exit;
      if (not FNExist) then Exit;

      ResetIOError;
      pos:= 0; while (pos<poloziek) do
          begin
            if RWClose then Reset(DBf,head.znakov);
           {$I+}
            Seek(DBf, 1 + pos*(1+head.riadkov));
            BlockRead(DBf, buff^[0], 1, nacitanych);
           {$I-}
            if RWClose then Close(DBf);
            ResetIOError;                     { is_IOError(FN+' najdi nil') }
            if nacitanych<1 then break;
            if getstr(buff^[0],1,[ZAC_KEY,KON_KEY]) = DB_NIL then
               begin
                 najdi_nil:= pos;
                 break
               end;
            if RWClose then CheckProcesses0 else CheckProcesses0;
            inc(pos)
          end;
      ResetIOError
    end;

 {
   hlada _data
 }
 function TDB.najdi_data: long;
    var   pos : long;
          res : bool;
          klc : TDB_riadok;
          nacitanych : word;
    begin
      najdi_data:= -1;
      if NOSAVE then Exit;
      if (not FNExist) then Exit;

      ResetIOError;
      pos:= 0; while (pos<poloziek) do
          begin
            if RWClose then Reset(DBf,head.znakov);
           {$I+}
            Seek(DBf, 1 + pos*(1+head.riadkov));
            BlockRead(DBf, buff^[0], 1, nacitanych);
           {$I-}
            if RWClose then Close(DBf);
            ResetIOError;                { is_IOError(FN+' najdi data') }
            if nacitanych<1 then break;
            if getstr(buff^[0],1,[ZAC_KEY,KON_KEY]) <> DB_NIL then
               begin
                 najdi_data:= pos;
                 break
               end;
            if RWClose then CheckProcesses0 else CheckProcesses0;
            inc(pos)
          end;
      ResetIOError
    end;
*)

 procedure TDBF.zapis(_data: pointer; _pos: long; _ins: bool);
     begin
       if (DATAcode<>nil) then
          begin
            koduj_vetu(_data);
            zapis_vetu(_pos,_ins)
          end
     end;

(*
 procedure TDB.oprav(_data: pointer);
     var   _pos: long;
     begin
       _pos:= vyhladaj_data(_data);
       zapis(_data,_pos,false)
     end;


 procedure TDB.zrus(_data: pointer);
     var   _pos: long;
     begin
       _pos:= vyhladaj_data(_data);
       if _pos>-1 then zapis(nil,_pos,false)
     end;
*)

{$ENDIF}