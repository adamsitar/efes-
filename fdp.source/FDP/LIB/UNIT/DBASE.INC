{$IFDEF DB_DBASE}

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Field                                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
 constructor Field.Init;
 begin
   Node.Init;
   FillChar(Name,32,0);
 end;

 destructor Field.Done;
 begin
 end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ FieldList                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
 constructor FieldList.Init;
 begin
   Count:=0;
   List.Init;
 end;


 procedure FieldList.AddField(N: FieldName; T: Char; L,D: byte);
 var
   Tmp: FieldPtr;
 begin
   Tmp:=New(FieldPtr,Init);
   if Tmp<>Nil then
   begin
     Inc(Count);
     LinkBot(Tmp);
     with Tmp^ do
     begin
       PackStr(N,10,Name);
       Typ:=T;
       Len:=L;
       Dec:=D;
       { Vypocet offsetu }
       Offset:=1;
       Tmp:=FieldPtr(Top);
       while Tmp^.Fwd<>Nil do
       begin
         Offset:=Offset+Tmp^.Len;
         Tmp:=FieldPtr(Tmp^.Fwd);
       end;
     end; { with }
   end;
 end; { AddField }


 function FieldList.Find(_FN: FieldName): boolean;
 Label Konec;
 begin
   Curr:=Top;
   Find:=False;
   if Curr<>Nil then
   while (Curr<>Nil) do
   begin
     if _FN=Name then
     begin
       Find:=True;
       Goto Konec;
     end;
     Curr:=Curr^.Fwd;
   end;
   Curr:=Bot;
   Konec:
 end; { Find }

 function FieldList.Name: FieldName;
 begin
   Name:= UnPackStr(FieldPtr(Curr)^.Name,10);
 end;

 function FieldList.Typ: Char;
 begin
   Typ:=FieldPtr(Curr)^.Typ;
 end;

 function FieldList.Len: byte;
 begin
   Len:=FieldPtr(Curr)^.Len;
 end;

 function FieldList.Dec: byte;
 begin
   Dec:=FieldPtr(Curr)^.Dec;
 end;

 function FieldList.Offset: word;
 begin
   Offset:=FieldPtr(Curr)^.Offset;
 end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TDBF                                                     €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
 constructor TDBF.Init;
 begin
   FillChar(X,32,0);
   Recs.Init;
   Updated:=False;
   DosFile.Init(_FN);
 end;


 destructor TDBF.Done;
 begin
   if Handle<>0 then Close;
   Recs.Done;
   FreeMem(RecBuf,RecLen);
 end;


 function TDBF.Status: word;
 begin
   Status:= IOstatus;
   IOstatus:=0;
 end;


 procedure TDBF.Open;
 var
   I: word;
   F: Field;
 begin
   Recs.Done;
   Recs.Init;
   DosFile.Open;
   CurrRec:=0;
   if IOstatus=0 then
      begin
        {-- Read header }
        N:=BlkRead(32,X); { teÉ v hlaviáce jsou spravnÇ hodnoty }
        {-- Kontrola zda je to DBASE file }
        if not (X in [$3,$83])  { nie 8 ? }
        then IOstatus:=FormatErr
        else for I:=1 to Pred(Offset div 32) do
             begin
               N:= BlkRead(32,F.Name);
               with F do Recs.AddField(Name,Typ,Len,Dec);
             end;
      { P©idàlen° pamàti pro bufr vàty }
        GetMem(RecBuf,RecLen);
        DosFile.Seek(Offset);
        Read(RecBuf^);
        Seek(0)  { jsem na zaá†tku ale m†m prvn° vàtu v bufru }
      end
 end; { Open }


 procedure TDBF.WriteHeader;
 const
   EndOfHeader: Char=#$0D;
 var
   Tmp: FieldPtr;
 begin
   DosFile.Seek(0);
   N:=BlkWrite(32,X);
   Tmp:=FieldPtr(Recs.Top);
   while Tmp<>Nil do
   begin
     N:=BlkWrite(32,Tmp^.Name);
     Tmp:=FieldPtr(Tmp^.Fwd);
   end;
   N:=DosFile.BlkWrite(1,EndOfHeader);
 end; { WriteHeader }


 procedure TDBF.Close;
 const
   EOFmark:char=^Z;
 begin
   WriteHeader;
   DosFile.Seek(Offset+NumRec*RecLen);
   N:= DosFile.BlkWrite(1,EOFmark);
   DosFile.Close;
 end; { Close }


 procedure TDBF.AddField(_FN: FieldName; T: Char; L,D: byte);
 begin
   if Handle=0 then
   begin
     Recs.AddField(_FN,T,L,D);
     Inc(Offset,32);
     Inc(RecLen,L);
   end;
 end; { AddField }


 procedure TDBF.Make;
 var
   Y,D,M,W: word;
 begin
   { Vytvo©it novò soubor }
   DosFile.Make;
   X:=$03;
   CurrRec:=0;
   year:= BIOS.year - (BIOS.year div 100)*100;
   month:= BIOS.month;
   day:= BIOS.day;
   Inc(Offset,32+1);
   Inc(RecLen);
   WriteHeader;
   { P©idàlen° pamàti pro bufr vàty }
   GetMem(RecBuf,RecLen);
 end; { Make }


 function TDBF.EOF: boolean;
 begin
   EOF:= DosFile.Pos>=Offset+NumRec*RecLen;
 end;

 {
  Tyto metody pracuj° s aktu†ln° vàtou a pouë°vaj° RecBuf
 }
 procedure TDBF.GoTop;
 begin
   Seek(0);
 end;


 procedure TDBF.GoBot;
 begin
   if NumRec>0 then Seek(Pred(NumRec)) else Seek(0);
 end;


 function  TDBF.GetFld(_FN: FieldName): string;
 var
   TmpStr: string;
 begin
   if Recs.Find(_FN) then
   begin
     TmpStr[0]:=Char(Recs.Len);
     Move(RecBuf^[Recs.Offset],TmpStr[1],Ord(TmpStr[0]));
     GetFld:=TmpStr;
   end else GetFld:='';
 end; { GetFld }


 procedure TDBF.PutFld(_FN: FieldName; Value: string);
 begin
   if Recs.Find(_FN) then
   begin
     if Length(Value)>Recs.Len then Value[0]:=Char(Recs.Len);
     Move(Value[1],RecBuf^[Recs.Offset],Length(Value));
     FillChar(RecBuf^[Recs.Offset+Length(Value)],Recs.Len-Length(Value),' ');
     Updated:=True;
   end;
 end; { PutFld }


 procedure TDBF.WriteRec;
 begin
   write(RecBuf^);
   if IOstatus=0 then Updated:=False;
 end;


 procedure TDBF.ReadRec;
 begin
   Read(RecBuf^);
   if IOstatus=0 then Updated:=False;
 end;


 procedure TDBF.GoBack;
 begin
   Seek(Pred(CurrRec));
 end;


 procedure TDBF.Seek(D: long);
 begin
   CurrRec:=D;
   DosFile.Seek(Offset+CurrRec*RecLen);
 end; { Seek }


 procedure TDBF.Read(var Rec);
 begin
   N:=DosFile.BlkRead(RecLen,Rec);
   if N=RecLen then
      begin
        Updated:=False;
        Inc(CurrRec);
        if CurrRec>NumRec then Inc(NumRec);
      end
   else { Zotaven° po chybà áten° za koncem souboru }
     if IOstatus=0 then DosFile.Seek(Offset+CurrRec*RecLen)
 end; { Read }


 procedure TDBF.Write(var Rec);
 begin
   { Write je jedin† metoda, kter† mñëe roz®°©it soubor }
   N:=DosFile.BlkWrite(RecLen,Rec);
   if N=RecLen then
   begin
     Inc(CurrRec);
     if CurrRec>NumRec then Inc(NumRec);
   end;
 end; { write }


 function TDBF.Size: long;
 begin
   Size:=NumRec;
 end;


 Function TDBF.RecSize : Word;
 begin
   RecSize:=REcLen;
 end;


 Function TDBF.FilePos : long;
 begin
   FilePos:=CurrRec;
 end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TPolV - polozka vety                                     €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
 constructor tPolV.Init;
 begin
   Node.Init;
 end;

 destructor tPolV.Done;
 begin
 end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TPolVList - zoznam poloziek vety                         €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
 constructor tPolVList.Init;
 begin
   Count:=0;
   List.Init;
 end;


 procedure tPolVList.AddVetu;
 var   Tmp: PPolV;
 begin
   Tmp:=New(PPolV,Init);
   if Tmp<>Nil then
   begin
     Inc(Count);
     LinkBot(Tmp);
     with Tmp^ do
     begin
     end; { with }
   end;
 end; { AddVetu }


 procedure tPolVList.SetVetu(_U : TUnion);
   begin
      PPolV(Curr)^.V := _U
   end;


 function tPolVList.Find(_T: char;_U : TUnion): bool;
 Label Konec;
 begin
   Curr:=Top;
   Find:=False;
   if Curr<>Nil then
   while (Curr<>Nil) do
   begin
     Curr:=Curr^.Fwd;
   end;
   Curr:=Bot;
   Konec:
 end; { Find }


 function tPolVList.V : PUnion;
   begin
     V := @PPolV(Curr)^.V;
   end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TAppDBF                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
 constructor TAppDBF.Init(_FN: PathStr;
                          _DBFdef: PDBFdef; _DBFsize: byte;
                          _DBFcode  : pointer; { TDBFcode_proc   }
                          _DBFdecode: pointer; { TDBFdecode_proc }
                          _DBFchg   : pointer  { @bool }
                         );
       var   poc : long;
       begin
         inherited Init(_FN);
         DBFdef := _DBFdef; DBFsize:= _DBFsize;
         DBFcode:= _DBFcode; DBFdecode:= _DBFdecode;
         DBFchg := _DBFchg;
         GetMem_DBF_BUFF(DBFbuff, DBFsize);
 {      end;
 procedure TAppDBF.Open;
     begin}
         inherited Open;
         if Status <> 0 then
            begin
             {
               VytvorDBF :
               Vytvori hlavicku suboru *.DBF podla nadefinovanej konstanty
               'MyType' p podla poctu poloziek v jednej vete POCETPOL
               a zapise ju na disk
             }
              poc:= 0;
              repeat
                AddField(StrPas(DBFdef^[poc].M),DBFdef^[poc].T,DBFdef^[poc].P,DBFdef^[poc].D);
                inc(poc)
              until poc = DBFsize;
              Make
            end;
       { VytvorTVetu }
         Veta.Init;
         Recs.GoTop;
         repeat
           Veta.AddVetu;
           Recs.GoDown
         until Recs.Curr = nil
       end;


 destructor TAppDBF.Done;
      begin
        Veta.Done;
        inherited Done;
        FreeMem_DBF_BUFF(DBFbuff, DBFsize);
        if NumRec=0 then DelFile(FN)
      end;



 { ----------------------------------------
   private
   ---------------------------------------- }

 procedure TAppDBF.SetD(delete: bool);
     const   _D: array[false..true] of char = (' ','*');
     begin
       D:= _D[delete]
     end;

 function TAppDBF.GetD: bool;
   begin
    GetD:= D='*'
   end;

 procedure TAppDBF.SetRB0(_d : char);
   begin
     RecBuf^[0]:= _d;
   end;


 procedure TAppDBF.SetVetu(_U: TUnion);
   begin
     Veta.SetVetu(_U);
     SetD(RecBuf^[0]='*')
   end;

 procedure TAppDBF.ZapisPol(_T : char;_s : string);
     const _LogYes : array[0..4] of string[3] = ('ANO','YES','Y','A','T');
           _LogNo  : array[0..4] of string[3] = ('NIE','NO', 'N','N','F');
     var   _re  : double;
           code : int;
           _pom : byte;
           _U   : TUnion;
     begin
       case _T of
        'C': _U.C := _s;
        'N': val(_s,_U.N,Code);
        'L': for _pom := 0 to 4 do
               if UpString(_s) = _logYes[_pom] then  _U.L := true
               else if UpString(_s) = _logNo[_pom] then  _U.L := false;
        'D': begin  { datum }
               _U.D.R:= cis(_s, 1,4);
               _U.D.M:= cis(_s, 5,2);
               _U.D.D:= cis(_s, 7,2);
             end
         else RunError('Structure of DBF file '+FN+' is corrupted. Delete it !')
       end;
       SetVetu(_U)
    end;


 {
   vytvorenie jednej prazdnej vety,
   tj. rozsirenie databazy o jednu prazdnu vetu
   na pozicii _pos
 }
 procedure TAppDBF.insert(_pos : long);
     var   _pom,i : long;
     begin
       if NumRec = 0 then Exit;
       GoBot;
       if ( Numrec = 1) or (_pos > NumRec) then ReadRec
       else begin
              _pom := NumRec;
              while _pom <> _pos do
                begin
                  ReadRec; WriteRec;
                  for i:= 0 to 2 do Goback;
                  Dec(_pom);
                end;
       end;
     end;


 procedure TAppDBF.nacitaj;
     var   _s : string;
     begin
       ReadRec;
       Recs.GoTop;
       Veta.GoTop;
       repeat
         _s := GetFld(Recs.Name);
         ZapisPol(Recs.Typ,_s);
         Recs.GoDown;
         Veta.GoDown;
       until Recs.Curr = nil
     end;


 procedure TAppDBF.zapis(_pos: long; _ins: bool);
     const _b : array[false..true] of string[5] = ('False','True');
     var   _s : string;
     begin
       if _ins and (_pos > -1) then insert(_pos);
       if _pos=-1 then _pos:= NumRec; {if _pos = -1 then Seek(NumRec);}
       _pos:= Min(_pos,NumRec);       {if (_pos > -1) and (_pos<Numrec) then Seek(_pos);}
       Seek(_pos);
       Veta.GoTop;
       Recs.GoTop;
       repeat
         case Recs.Typ of
          'C': _s:= Veta.V^.C;
          'N': str(Veta.V^.N:Recs.Len:Recs.Dec,_s);
          'L': _s:= _b[Veta.V^.L];
          'D': _s:=    IntToStr(Veta.V^.D.R,4,0)
                     + IntTostr(Veta.V^.D.M,2,0)
                     + IntTostr(Veta.V^.D.D,2,0);
           else RunError('Structure of DBF file '+FN+' is corrupted. Delete it')
         end;
         PutFld(Recs.Name,_s);
         Recs.GoDown;
         Veta.GoDown;
       until Recs.Curr = nil;
       SetRB0(' ');
       WriteRec;
       if DBFchg<>nil then bool(DBFchg^):= true
     end;



 { ----------------------------------------
   public
   ---------------------------------------- }

 { ----------------------------------------
   CITANIE, ZAPIS
   ---------------------------------------- }
 procedure TAppDBF.koduj_vetu(p: pointer);
     var   i: int;
     begin
       if DBFcode<>nil then TDBFcode_proc(DBFcode)(p, DBFbuff)
       else for i:= 0 to DBFsize-1 do DBFbuff^[i]:= 'neinicializovana'
     end;

 procedure TAppDBF.dekoduj_vetu(p: pointer);
     begin
       if DBFdecode<>nil then TDBFdecode_proc(DBFdecode)(DBFbuff,p,pos)
     end;

 {
   najde jednu vety a nacita ju do TVeta
   ak je _pos <= 0  cita z aktualnej pozicie
 }
 procedure TAppDBF.nastav_na_vetu(_pos: long);
   begin
     if (_pos > -1) and (_pos<NumRec) then Seek(_pos);
     nacitaj;
     GoBack
   end;


 {
   nacitanie jednej vety do TVeta z aktualnej pozicie
 }
 procedure TAppDBF.citaj_vetu(_pos: long; _DBFbuff: PDBF_STRs);
     const _bool: array[false..true] of string[5] = ('False','True');
     var   _b   : PDBF_STRs;
           _s,t : string;
           i    : int;
     begin
       if _DBFbuff<>nil then _b:= _DBFbuff { data pripravene vo vonkajsom bufferi }
       else _b:= DBFbuff;                  { data pripravene vo vnutornom bufferi }
       if pos<>-1 then nastav_na_vetu(_pos);
     { nacitanie jednej vety do TVeta z aktualnej pozicie }
       nacitaj;
     { dekodovanie Vety }
       Recs.GoTop; { nastavi pole poloziek na zaciatok }
       Veta.GoTop;
       {writeln(D);}
       for i:= 0 to DBFsize-1 do
           begin
             case Recs.Typ of
              'C': _s:= Veta.V^.C;
              'N': str(Veta.V^.N:Recs.Len:Recs.Dec,_s);
              'L': _s:= _bool[Veta.V^.L];
              'D': begin
                     str(Veta.V^.D.D:Recs.Len,t); _s:= t;
                     str(Veta.V^.D.M:Recs.Len,t); _s:= _s+t;
                     str(Veta.V^.D.R:Recs.Len,t); _s:= _s+t
                   end
               else RunError('Structure of DBF file '+FN+' is corrupted. Delete it')
             end;
             _b^[i]:= _s;
             Recs.GoDown;
             Veta.GoDown
           end;
     end;


 {
   prepisanie alebo vlozenie vety Veta na poziciu _pos podla _ins
 }
 procedure TAppDBF.zapis_vetu(_DBFbuff: PDBF_STRs; _pos: long; _ins: bool);
     var   _s : string;
           _b : PDBF_STRs;
           i  : int;
     begin
       if _DBFbuff<>nil then _b:= _DBFbuff { data pripravene vo vonkajsom bufferi }
       else _b:= DBFbuff;                  { data pripravene vo vnutornom bufferi }
     { kodovanie do DBF }
       Veta.GoTop;
       Recs.GoTop;
       for i:= 0 to DBFsize-1 do
           begin
             ZapisPol(Recs.Typ,_b^[i]);
             Veta.GoDown;
             Recs.GoDown
           end;
     { ulozenie do DBF }
       zapis(_pos,_ins)
     end;


 procedure TAppDBF.oprav_vetu(_DBFbuff: PDBF_STRs; _pos: long);
     begin
       _pos:= Min(_pos,NumRec);   {if _pos>NumRec+1 then _pos:= NumRec+1;}
       Seek(_pos);                {if (_pos > -1) and (_pos<=NumRec) then Seek(_pos)}
       zapis_vetu(_DBFbuff, _pos, false)
     end;



 { ----------------------------------------
   ERASE / UNERASE
   ---------------------------------------- }

 procedure TAppDBF.oznac_del_veta(_pos: int);
     begin
       if (NumRec<>0) and (_pos>0) and (_pos<=NumRec) then nastav_na_vetu(_pos);
       ReadRec; GoBack;
       SetRB0(#42);
       WriteRec; GoBack
     end;

 procedure TAppDBF.obnov_del_veta(_pos: int);
     begin
       if (NumRec<>0) and (_pos>0) and (_pos<=NumRec) then nastav_na_vetu(_pos);
       ReadRec; GoBack;
       SetRB0(#32);
       WriteRec; GoBack
     end;

 procedure TAppDBF.obnov_del_vety;
   begin
     GoTop;
     repeat
       obnov_del_veta(-1); Readrec;
     until EOF
   end;

 procedure TAppDBF.vymaz_del_vety;
     var   _D : TAppDBF;
           i  : int;
     begin
       (*
       _D.Init(PathToDBF+'$$$1.dbf', DBFdef,DBFsize);
       _D.Veta.Init;

       Recs.GoTop;
       repeat
         _D.AddField(Recs.Name,Recs.Typ,Recs.Len,Recs.Dec);
         _D.Veta.AddVetu;
         Recs.GoDown
       until Recs.Curr = nil;
       _D.Make;

       GoTop;
       for i:= 0 to Numrec-1 do
           begin
             nacitaj;
             if not GetD then
                begin
                  Veta.GoTop;
                  _D.Veta.GoTop;
                  repeat
                    _D.SetVetu(Veta.V^);
                    _D.Veta.GoDown;
                    Veta.GoDown
                  until Veta.Curr = nil;
                  _D.zapis(-1,false)
                end
           end;
       close;
       erase;
       _D.rename(FN);
       _D.done
       *)
     end;

{$ENDIF}

