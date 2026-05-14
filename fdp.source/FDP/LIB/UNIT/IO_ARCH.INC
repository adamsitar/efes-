 function get_ARCHfn(min: word): string;
    begin
      get_ARCHfn:= inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(min,2,0)
    end;

 {function decode_ARCHfn(fn: string; date: TDatum): bool;
    begin
      date utime
    end;}


 procedure check_directories(pch: PPChars; max: int);
     var   i: int;
     begin
       for i:= 0 to max-1 do _mkdir(StrPas(pch^[i]))
     end;

 procedure archive_data(_path,_name: string; data: PBytes; pocet: long; ident: string; is_utc, is___: bool);
     var   F : file;
           s : string;
           i : int;
           NumWrite, NumWritten : word;
     begin
       {#13#10<->#17#217 ?}
       if DiskFree(0)<Minimum(MIN_SPACE_HDD,5*1024*1024) then Exit;

       vytvor_novy_subor(_path+_name);
       if Exists(_path+_name)<>0 then Exit;

       Assign(F,_path+_name); Reset(F,1);
       Seek(F,FileSize(F));
       if is_utc then s:= TimeToStr2(hour,min,sec,':','ú')+' ' else s:= '';
       if s<>''     then BlockWrite(F,s[1],    Length(s),    NumWritten);
       if ident<>'' then BlockWrite(F,ident[1],Length(ident),NumWritten);
       while pocet>0 do
         begin
           NumWrite:= Minimum(pocet,sizeof(s)-1);
           move(data^,s[1],NumWrite); s[0]:= chr(NumWrite); { len ladenie }
           s:= NL_to_NL_(s);
           BlockWrite(F,s[1],NumWrite,NumWritten);
           IncPtr(pointer(data),NumWrite);
           Dec(pocet,NumWrite)
         end;
       if is___ then s:= '...' else s:= '';
       s:= s+kbNL;
       BlockWrite(F,s[1],length(s),NumWritten);
       Close(F); ResetIOError
     end;


 procedure save_cislo(fn: string; cislo: word);
     var   f: file of word;
     begin
       assign(f,fn);
       rewrite(f);
       write(f,cislo);
       close(f);
     end;

 function read_cislo(fn: string): word;
     var   f: file of word;
           cislo: word;
     begin
       read_cislo:= 0;
       if Exists(fn)<>0 then Exit;
       assign(f,fn);
       reset(f);
       read(f,cislo);
       close(f);
       read_cislo:= cislo
     end;


function decode_date_fn(s: string): string;
   var   c,i: int; s1,s2,s3,s4: string[3]; t: string;
   begin
     s:= GetStr(s,GetStrItems(s,['\']),['\']);
     decode_date_fn:= s;

     if pos('-',s)>0 then
        begin
        { 3 mozne formaty :
          06-97.PRZ
          09-06-97.23
          09-06-97.FPL
        } s4:= getstr(s,2,['.']);
          s := delchar(getstr(s,1,['.']),['-']);
          if length(s)=6 then
             begin
               t:= ' '+copy(s,1,2); i:= 3;
               t:= t+'.'+copy(s,i,2)+'.'''+copy(s,i+2,2);
               val(s4,i,c);
               if c=0 then t:= t + ' ,   '+s4+'h';
             end
          else
             begin
               t:= ' '; i:= 1;
               c:= scis(s,1,2);
               if c in [1..12] then t:= t+ Months[c]+' '''+copy(s,3,2)
               else t:= t+s
             end;
          decode_date_fn:= t+' '
        end

     else begin
          { nahravky : 11291600.net
          } t:= getstr(s,1,['.']);
            if (length(t)=8) and (delchar(t,setPism)='') then
               begin
                 decode_date_fn:= ' '+copy(s,3,2)+'.'+copy(s,1,2)+', '+copy(s,5,2)+'ú'+copy(s,7,2)+' h '
                 {decode_date_fn:= ' '+copy(s,3,2)+'.'+copy(s,1,2)+', '+copy(s,5,2)+'ú'+copy(s,7,2)+'ú'+copy(s,9,2)+' h '}
               end
          end
   end;
