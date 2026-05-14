
procedure O_AFTN._process_test (data: pbytes; dlz: int);
    var   res: string;
    begin
      {inherited _process_data(pchars(data),dlz);}
      receive_pkt (src_ext,'',pchars(data),dlz, res,true);
    end;



{ nacitanie dat z binarneho subora
}
{$IFDEF DEBUG}
  procedure O_AFTN._test_bin_file(fn: string; skp: int);
      var   f : file of char;
            s : string;
            p : pchar;
            c : char;
            i : int;
            res : string;
            pkt : PAFTNpkt;
      begin
        if Exists(fn)<>0 then Exit;

        Assign(f,fn); Reset(f);
        new(pkt); fillchar(pkt^,sizeof(pkt^),0);
        while not eof(f) do
          begin
            read(f,c);

            if pkt^.p>=sizeof(pkt^.b) then fillchar(pkt^,ipkt_size,0);
            pkt^.b[pkt^.p]:= c;
            inc(pkt^.p);
            if (c=kbLF) and (pkt^.p=2) and (pkt^.b[0]=kbCR) then
               begin
                 pkt^.p:= 0;
                 continue
               end;
            if     (pkt^.p>kod_aftnEOT)
               and (strcomp(p_aftnEOT, pchar(@pkt^.b[pkt^.p-kod_aftnEOT]))=0) then
               begin
                 if pkt^.b[0]<>';' then
                   {if (buff<>nil) then buff^.save(pkt);}
                    begin
                      for i:= skp to pkt^.p-skp do
                        begin
                          if pkt^.b[i]=kbLF_ then pkt^.b[i]:= kbLF;
                          if pkt^.b[i]=kbCR_ then pkt^.b[i]:= kbCR
                        end;
                      save_pkt(pkt); {receive_pkt (@pkt^.b[skp], pkt^.p-skp, res, true);}
                      c:= getkey;
                    end;
                 fillchar(pkt^,ipkt_size,0) { musi byt, inak sa nevyhodnoti koniec spravy }
               end;
           end;
        dispose(pkt);
        Close(f);
        ResetIOError
      end;

  {
    nacitanie dat z textoveho subora, ked velkost riadku presiahne string;
    - preskocenie znakov na zaciatku
    - nacitava az po sekvenciu ends
  }
  procedure O_AFTN._test_txt_file(fn: string; ends: string; skip: byte);
      var   f : text;
            s : string;
            p : pchar;
            i : int;
            b : bool;
            pkt : TAFTNpkt;
      begin
        if Exists(fn)<>0 then Exit;

        Assign(f,fn); Reset(f);
        while not eof(f) do
          begin
            p:= nil; s:= '';
            while (s='') and (s=ends) and (not eof(f)) do
              begin
                readln(f,s); s:= cut_(s)
              end;
            p:= StrNPCopy(p,s, true,true);
            repeat
              readln(f,s); s:= cut_(s);
              s:= kbNL+s;
              p:= StrNPCopy(p,s, true,true)
            until (s=kbNL+ends) or (eof(f));

            for i:= 0 to strlen(p)-1 do
              begin
                if p[i]=kbLF_ then p[i]:= kbLF;
                if p[i]=kbCR_ then p[i]:= kbCR
              end;

            b:= testing_txt_file; testing_txt_file:= true;
            pkt.p:= strlen(p)-2-skip;
            move(pchars(pointer(p+2+skip))^,pkt.b,pkt.p);
            {receive_pkt('',pointer(p+2+skip),strlen(p)-2-skip, true);}
            testing_txt_file:= b;
            strdispose(p)
          end;
        Close(f);
        ResetIOError
      end;

{$ENDIF}