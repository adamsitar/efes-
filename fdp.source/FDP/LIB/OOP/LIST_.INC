{ ---------------------------------------------
  i/de-inicializacne procedury
  ---------------------------------------------
}
 constructor TList.Init(_lst: PListDesc; _fn: string; _odd: TcharSet; _pos: int; _sort: bool; _filter: PBFunc_s; _init: bool);
       var   fn: string;
       begin
         inherited Init(nil,0,0,0,0);

         cmXXXX:= cmOK; hlpXXX:= hlp_index; MCursor:= Ruka;
         b:= clBUTTON_COLOR; t:= clGRa; ab:= clBUTTON_COLOR-1; at:= clGRa;
         lst:= _lst; pos:= _pos; odd:= _odd;
         sort:= _sort; filter:= _filter;

         if _lst<>nil then fn:= strpas(_lst^.fn)
         else fn:= _fn;
         fname:= GetFname(fn,pathLST,lstExt);
         if Exists(fname)=2 then fname:= fn;

         {$IFDEF NOEMS} strm:= nil;
         {$ELSE}        stre:= nil;
         {$ENDIF}

         tit:= nil;
         poc:= 0;
         top:= -1;

         is_list:= false;
         is_init:= _init;
         is_initialized:= false;
         if is_init then InitList
       end;


  {procedure TList.InitData;
      begin
        if not is_init then InitList
      end;

  procedure TList.DoneData;
      begin
        if not is_init then DoneList
      end;}


 destructor TList.Done;
      begin
        if is_init then DoneList
      end;


{ nacitanie poloziek zo subora
}
 function TList.is_to_add(s: string): bool;
    begin
      is_to_add:= (filter=nil) or (TBFunc_s(filter)(s))
    end;

 function TList.put (riadok,polozka: string; ind: int): bool;
    begin
      put:= false;
      if   {$IFDEF NOEMS} (strm=nil)
           {$ELSE}        ((stre=nil) or (not stre^.is_ems))
           {$ENDIF}
        or (ind>=poc) then Exit;

      {$IFDEF DEBUG}
       item_test (polozka);
      {$ENDIF}

      {$IFDEF NOEMS}
       strm^[ind]:= StrPasNew(polozka);
       put:= true;
      {$ELSE}
       stre^.items:= ind;
       stre^.add(polozka);
       put:= true;
      {$ENDIF}

      tit^[ind]:= riadok[1] in setTitle;  { je to hlavicka, komentar pre zobrazenie uzivatelovi ? }
    end;

 function TList.get(ind: int): string;
    begin
      get:= '';
      if   {$IFDEF NOEMS} (strm=nil)
           {$ELSE}        ((stre=nil) or (not stre^.is_ems))
           {$ENDIF}
        or (ind<0) or (ind>=poc) then Exit;

      {$IFDEF NOEMS}
       get:= strpas(strm^[ind]);
      {$ELSE}
       get:= stre^.read(ind);
      {$ENDIF}
    end;


 function TList.alloc: bool;
    var   res: bool;
    begin
      {$IFDEF NOEMS}
       res:= AllocMem(pointer(strm),SizeOf(PChar)*(poc));
      {$ELSE}
       stre:= New(PstreamPackedStrings,Init);
       res:= stre^.is_ems;
       if not res then _write_err_log(fname+' ems init error ');
      {$ENDIF}
      res:= AllocMem(pointer(tit),SizeOf(bool)*(poc)) and res;
      top:= poc-1;
      alloc:= res
    end;

 procedure TList.dealloc;
     var   i : int;
     begin
       {$IFDEF NOEMS}
        if strm<>nil then
           begin
             for i:= 0 to poc-1 do strdispose(strm^[i]);
             DeallocMem (pointer(strm),SizeOf(PChar)*(poc));
             strm:= nil;
           end;
       {$ELSE}
        if stre<>nil then Dispose(stre,Done);
        stre:= nil;
       {$ENDIF}
       if tit<>nil then DeallocMem (pointer(tit),SizeOf(bool)*(poc));
       tit:= nil;
       poc:= 0;
       top:= -1;
     end;


 function TList.InitList: bool;
    var   f : text;
          i,j : int;
          s,u,p : string;

    begin
      InitList:= false;

      if is_initialized then DoneList;

      top:= -1; poc:= 0;
      {$IFDEF NOEMS} strm:= nil;
      {$ELSE}        stre:= nil;
      {$ENDIF}
      tit:= nil;
      if Exists(fname)<>0 then Exit;

     { Urcenie poctu poloziek
     }
      Assign(f,fname); Reset(f);
      poc:= 0;
      while not Eof(f) do
        begin
          ReadLn(f,s);
          s:= ReplChar(s, [#0..#31], ' ');
          if (s[1] in setKomen) or ((poc=0) and (s='')) or (not is_to_add(s)) then continue;
          if poc = MAX_PCHARs then break;
          inc(poc)
        end;
      if (poc>0) and (delchar(s,set_)='') then dec(poc); { posledny prazdny riadok ignoruje }

     { Nacitanie poloziek
     }
      (*if test then
         begin
           assign(txt,'1.$$$');
           rewrite(txt);
           {for i:= 0 to L^.top do writeln(txt,L^.get(i));
           close(txt);}
         end;*)

      if poc>0 then
         begin
           alloc;
           i:= 0;
           max_len:= 0;
           Reset(f);
           p:= '';
           repeat
             ReadLn(f,s);
             s:= ReplChar(s, [#0..#31], ' ');
             read_header(s,p);
             p:= s; u:= s; s:= cut_(s);
             if (s[1] in setKomen) or ((i=0) and (s='')) or (not is_to_add(s)) then continue;

             if pos=lst_cely_riadok_ then u:= u
             else begin
                    if pos=lst_cely_riadok then u:= delchar(u,setTitle) { cely riadok zoznamu i s komentarom... }
                    else u:= delchar(GetStr(u,1, setKomen),setTitle);   { nacitanie riadku az po komentar...    }
                    if not is_list then u:= cut_(u);
                  end;

             {$IFDEF DEBUG} {$IFDEF NOEMS}
              if i>=500 then break;
             {$ENDIF} {$ENDIF}

             put(s,u,i);
             (*j:= 1; while put(s,u,i) and (u<>get(i)) and (j<=3) do
                begin
                  {_write_err_log(fname+' ems error : '+u+'<->'+s+'<->'+get(i));}
                  inc(j);
                end;*)
             inc(i);

             {if test then writeln(txt,s+','+get(i-1));}

             max_len:= Maximum(max_len,length(u))
           until Eof(f) or (i>=poc);

           {if test then close(txt);}
         end;

      Close(f);

      if poc>0 then
         begin
          { Nastavenie poslednej neprazdnej polozky, pretoze pri
            nacitani sa neprazdny riadok mohol zmenit na prazdny string
          }
           while (top>=0) and ((DelChar(get(top),set_)='') or (tit^[top])) do dec(top);
           {if (top<0) then DoneList;}

           {$IFDEF NOEMS}
            if (top>0) and (strm<>nil) and sort then SortStr0(strm, top);
           {$ENDIF}

           is_initialized:= true;
           InitList:= poc>0
         end;
    end;


 procedure TList.DoneList;
     begin
       dealloc;
       is_initialized:= false;
     end;


 function TList.read_header(line,prev: string): bool;
    begin
      read_header:= false;
    end;

 function TList.is_to_be_run: bool;
    begin
      is_to_be_run:=    (top>-1)
                    and {$IFDEF NOEMS} (strm<>nil)
                        {$ELSE}        (stre<>nil) and (stre^.is_ems)
                        {$ENDIF}
    end;

 {$IFDEF DEBUG}
  procedure TList.item_test (s: string);
      begin
      end;
 {$ENDIF}
