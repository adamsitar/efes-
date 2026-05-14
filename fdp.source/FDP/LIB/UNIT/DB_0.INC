{
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                                                          €
 € Objekt TDB                                               €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

 constructor TDB.Init(_FN : string;
                      _RWClose    : bool;
                      _riadkov    : byte;

                      _DATAcode   : pointer; { @TDBcode_proc   }
                      _DATAdecode : pointer; { @TDBdecode_proc }
                      _KEYcode    : pointer; { @TDBcode_proc   }
                     {_KEYdecode  : pointer;   @TDBdecode_proc
                      _isKEY      : pointer;   @TDBkey_func    }

                      _DBchg : pointer;    { @bool }
                      _attr  : TDB_attr
                     );

       var   l1,l2 : long;
             nacitanych,attr : word;
             s : string;
             i : int;

       begin
         indicate_db(1);
         FN:= _FN; RWClose:= _RWClose;

         DATAcode := _DATAcode; DATAdecode := _DATAdecode;
         KEYcode  := _KEYcode;  {KEYdecode := _KEYdecode; isKEY:= _isKEY;}
         p_another_key := nil;
         DBchg := _DBchg;

       { precitat hlavicku a z nej parametre znakov,riadkov,...
         ak sa lisia od zadanych parametrov, ktore su nenulove,
         otvorit novu DB
       }
         with head do
           begin
             s:= DB_copyright;
             Move(s[1],cprght[0],Minimum(sizeof(cprght),length(s)));
             dlz_head := DB_znakov;
             znakov   := DB_znakov;
             riadkov  := minimum(_riadkov,DB_riadkov);
             attr     := _attr;
             fillchar(reserved,sizeof(reserved)-2,0);
             reserved[high(reserved)-1]:= $D;
             reserved[high(reserved)]:= $A
           end;

       { alokacia buffera }
         l1:= head.znakov; l2:= 1 + head.riadkov; { kluc }
         buff_size:= (l1) * (l2);
         GetMem(buff,buff_size); {GetMem(buff,l2*sizeof(PDB_riadok)); for i:= 0 to l2-1 do GetMem(buff^[i],l1);}

       { otvorenie subora, priznak RWClose znamena, ze pri
         kazdom pristupe sa DB otvori a zatvori kvoli
         eliminacii konfliktov viacnasobneho pristupu do DB }
         ResetIOError;
         Assign(DBf,FN);
         FNExist:= FExists(FN)=0;
         {IFDEF DB_LOCK}
          if FNExist then
             begin
               GetFAttr(DBf,attr);
               if attr and ReadOnly <> 0 then SetFAttr(DBf,Archive);
             end;
         {ENDIF}
         if (FNExist) then
            begin
              Reset(DBf,sizeof(head));
              BlockRead(DBf,head,1,nacitanych);
              Close(DBf);
              if not RWClose then Reset(DBf,head.znakov);
            end;
         if (not RWClose) and (FNExist) then Reset(DBf,head.znakov);
         semaphor:= false;

         ResetIOError
       end;


 destructor TDB.Done;
      var   l1,l2 : long;
            i     : int;
      begin
        if (not RWClose) and (FNExist) then Close(DBf);
        {$IFDEF DB_LOCK}
          if FNExist then SetFAttr(DBf,Archive+ReadOnly);
        {$ENDIF}
        ResetIOError;
       {l1:= 1+head.znakov; l2= head.riadkov+1; for i:= 0 to l2-1 do FreeMem(buff^[i],l1);FreeMem(buff,l2*sizeof(PDB_riadok));}
        FreeMem(buff,buff_size);
        indicate_db(-1);
      end;


 {
  ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
  €                     €
  € nizsia uroven       €
  €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }
 {
 function TDB.dalsi_riadok(p: pointer): pointer;
    begin
      incptr(p,(1+head.znakov));
      dalsi_riadok:= p
    end;
 }
 {
   vrati pocet poloziek v DB
 }
 function TDB.poloziek: long;
    begin
      poloziek:= 0;
      if (not FNExist) then Exit;

      ResetIOError;
      if (RWClose) then Reset(DBf,head.znakov);
      poloziek:= (FileSize(DBf)-1) div Maximum(1,1+head.riadkov);    {(FileSize(DBf)-1 sizeof(head)) div buff_size}
      if (RWClose) then Close(DBf);
      ResetIOError
    end;


 {‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

    citanie/zapis
  ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 }
 function TDB.citaj_kluc (_pos: long): string;
    var   pos : long;
          s   : string;
          nacitanych : word;
    begin
      citaj_kluc:= '';
      if NOSAVE then Exit;
      if (not FNExist) then Exit;

      ResetIOError;
      if (_pos<poloziek) then
        begin
          if RWClose then Reset(DBf,head.znakov);
         {$I+}
          Seek(DBf, 1 + _pos*(1+head.riadkov));      { hlavicka + subor }
          BlockRead(DBf, buff^[0], 1, nacitanych);
         {$I-}
          if RWClose then Close(DBf);
          ResetIOError;
          if nacitanych>=1 then citaj_kluc:= getstr(buff^[0],1,[ZAC_KEY,KON_KEY])
        end;
      ResetIOError
    end;

 {
   nacitanie polozky z pozicie _pos
 }
 function  TDB.citaj_vetu(_pos: long): bool;
     var   i   : int;
           res : bool;
           nacitanych : word;
     begin
       citaj_vetu:= false;
       if (not FNExist) then Exit;

       ResetIOError;
       if RWClose then Reset(DBf,head.znakov);
       _pos:= maximum(0, minimum(_pos,(FileSize(DBf)-1) div Maximum(1,1+head.riadkov)));   { kluc+data }
      {$I+}
       Seek(DBf, 1 + _pos*(1+head.riadkov));        { hlavicka + subor }
       i:= 0; res:= true;
       while (i<=head.riadkov) and (res) do
         begin
           BlockRead(DBf, buff^[i], 1, nacitanych);
           {buff^[i][0]:= chr(head.znakov);}
           res:= nacitanych=1;                      { is_IOError(FN+' pri nacitani') }
           inc(i)
         end;
      {$I-}
       if RWClose then Close(DBf);
       ResetIOError;
       citaj_vetu:= (res) and (getstr(buff^[0],1,[ZAC_KEY,KON_KEY])<>DB_NIL)
     end;

 {
   prepisanie alebo vlozenie vety Veta na poziciu _pos podla _ins
 }
 procedure TDB.zapis_vetu(_pos: long; _ins: bool);
     var   i, riadkov : int;
           zapisanych : word;
     label X;
     begin
       if NOSAVE then Exit;
       ResetIOError;

       if (not FNExist) then
          begin
            Rewrite(DBf,head.znakov);
           {$I+}
            BlockWrite(DBf, head,1, zapisanych);
            if zapisanych<1 then goto X; { is_IOError(FN+' pri otvarani) }
           {$I-}
            FNExist:= FExists(FN)=0
          end
       else if RWClose then Reset(DBf,head.znakov);

       riadkov:= FileSize(DBf)-1;
       if _pos<0 then _pos:= riadkov else _pos:= minimum(_pos*(1+head.riadkov),riadkov);
      {$I+}
       Seek(DBf, 1 + _pos);              { Seek(DBf, sizeof(head) + _pos*buff_size); }
       i:= 0; while i<=head.riadkov do
         begin
           BlockWrite(DBf, buff^[i],1, zapisanych);
           if zapisanych<1 then goto X;  { is_IOError(FN+' pri zapise') }
           inc(i)
         end;
      {$I-}
       if (DBchg<>nil) then bool(DBchg^):= true;

       X:
       if RWClose then Close(DBf);
       ResetIOError
     end;

 {
   hladanie pozicie kluca
 }
 const b: bool = false;

 function TDB.vyhladaj_kluc(_kluc: TDB_riadok): long;
    var   pos : long;
          res : bool;
          nacitanych : word;
          s   : string;
    begin
      vyhladaj_kluc:= -1;
      if NOSAVE then Exit;
      if (not FNExist) then Exit;

      ResetIOError;
      _kluc:= getstr(_kluc,1,[ZAC_KEY,KON_KEY]);
      {if (_kluc='') then exit;}
      res:= false;
      pos:= 0;
      while (pos<poloziek) do
        begin
          if RWClose then Reset(DBf,head.znakov);
         {$I+}
          Seek(DBf, 1 + pos*(1+head.riadkov));      { hlavicka + subor }
          BlockRead(DBf, buff^[0], 1, nacitanych);
         {$I-}
          if RWClose then Close(DBf);
          ResetIOError;                             { is_IOError(FN+' hladanie kluca') }
          if nacitanych<1 then break;
          s:= getstr(buff^[0],1,[ZAC_KEY,KON_KEY]);

          if (_kluc=s) then
             begin
               vyhladaj_kluc:= pos;
               break
             end
          else if (p_another_key<>nil) and (TSFunc_s(p_another_key)(_kluc)=TSFunc_s(p_another_key)(s)) then
                  begin
                    if res then
                       begin
                       { dalsi kluc, musi odfiltrovat viacnasobnu zhodu klucov,
                         vrati -2;
                       } vyhladaj_kluc:= -2;
                         break
                       end
                    else vyhladaj_kluc:= pos;
                    res:= true
                  end;
          if RWClose then CheckProcesses0 else CheckProcesses0;
          inc(pos)
        end;
      ResetIOError
    end;


 function TDB.vyhladaj_data(_data: pointer): long;
    var   kluc: string;
    begin
      if (not FNExist) or (_data=nil) or (KEYcode=nil) then vyhladaj_data:= -1
      else begin
             kluc:= TSFunc_p(KEYcode)(_data);
             vyhladaj_data:= vyhladaj_kluc(kluc)
           end
    end;


 {
 ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                     €
 € vyssia uroven       €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
 }

 procedure TDB.koduj_vetu(p: pointer);
     var   i: int;
     begin
       FillChar(buff^,buff_size,' ');

     { zakodovanie kluca }
       if (p<>nil) then
          if (KEYcode<>nil) then buff^[0]:= TSFunc_p(KEYcode)(p)
          else buff^[0]:= ''
       else buff^[0]:= DB_NIL;
       buff^[0]:= ZAC_KEY+buff^[0]+KON_KEY;

     { zakodovanie dat }
       if (DATAcode<>nil) and (p<>nil) then TDBcode_proc(DATAcode)(p, @buff^[1], @head);
       {else for i:= 1 to head.riadkov do buff^[i]:= 'Neinicializovana DB';}
       for i:= 0 to head.riadkov do
           begin
             byte(buff^[i][head.znakov-2]):= byte(kbCR);
             byte(buff^[i][head.znakov-1]):= byte(kbLF)
           end
     end;

 procedure TDB.dekoduj_vetu(p: pointer);
     begin
       {if KEYdecode<>nil then TDBdecode_proc(KEYdecode) (@buff^[0],p);}
       if (DATAdecode<>nil) and (p<>nil) then TDBdecode_proc(DATAdecode)(@buff^[1],p, @head)
     end;

 function  TDB.citaj (_pos: long; _data: pointer): bool;
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


 procedure TDB.zapis(_data: pointer; _pos: long; _ins: bool);
     begin
       if (DATAcode<>nil) then
          begin
            koduj_vetu(_data);
            zapis_vetu(_pos,_ins)
          end
     end;


 function  TDB.oprav_riadok(_kluc: TDB_riadok; _data: pointer; _riadok: long; _code: pointer): bool;
     var   _pos : int;
           count : word;
     begin
       _pos:= vyhladaj_kluc(_kluc);
       if (_pos>-1) and (_data<>nil) and (_code<>nil) then
          begin
            if RWClose then Reset(DBf,head.znakov);
            {$I+}
             Seek(DBf, 1 + _pos*(1+head.riadkov)+1+_riadok);
             BlockRead(DBf, buff^[1+_riadok],1, count);
             TDBcode_proc(_code)(_data, @buff^[1+_riadok], @head);
             byte(buff^[1+_riadok][head.znakov-2]):= byte(kbCR);
             byte(buff^[1+_riadok][head.znakov-1]):= byte(kbLF);
             Seek(DBf, 1 + _pos*(1+head.riadkov)+1+_riadok);
             BlockWrite(DBf, buff^[1+_riadok],1, count);
            {$I-}
             if RWClose then Close(DBf);
          end;
       oprav_riadok:= _pos>-1
     end;


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

