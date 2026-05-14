 type   TPRSi_sum0   = record
          planov     : word;
          vyuzitych  : word;
          letov      : word;
        end;
        TPRS_sum0    = array[0..max_AIRBASE] of TPRSi_sum0;

        PPRSi_sta0   = ^TPRSi_sta0;
        TPRSi_sta0   = record
          kod        : string[kod_PRS];
          typ        : string[kod_PRS];   { standartne '', pozemny ma GND }
          nazov      : pchar;
          stai       : TPRS_sum0;
        end;

        PPRSs_sta0 = ^TPRSs_sta;
        TPRSs_sta0 = array[0..max_PRSsta-1] of PPRSi_sta0;

        PPRSs_staDen0 = ^TPRSs_staDen0;
        TPRSs_staDen0 = record
          pocet : int;            { predstavte si, cyklus for i:= 0 to wordovsky pocet-1 -> aritmetic owerflow }
          stad  : TPRSs_sta0
        end;


 procedure zapis_PRSs_sta0 (fn: string; stad: PPRSs_staDen0); far;
     var   f : file;
           len,res : word;
           i : int;
     begin
       assign(f,fn); rewrite(f,1);

       BlockWrite(f,stad^.pocet,sizeof(stad^.pocet),res);
       for i:= 0 to stad^.pocet-1 do
          begin
            BlockWrite(f,stad^.stad[i]^.kod,sizeof(stad^.stad[i]^.kod),res);
            BlockWrite(f,stad^.stad[i]^.typ,sizeof(stad^.stad[i]^.typ),res);
            BlockWrite(f,stad^.stad[i]^.stai,sizeof(stad^.stad[i]^.stai),res);

            len:= strlen(stad^.stad[i]^.nazov);
            BlockWrite(f,len,sizeof(len),res);
            BlockWrite(f,stad^.stad[i]^.nazov[0],len,res)
          end;

       close(f)
     end;


      { a) Povodny algoritmus pocital pocet planov

       bres:= false;
       i:= 0; while i<stap^.pocet do
         begin
           while (i<stap^.pocet)
             and (   (stap^.stad[i]^.typ<>PRIESTOR_STRELNICA)
                  or (    (stap^.stad[i]^.typ=PRIESTOR_STRELNICA)
                      and (stap^.stad[i]^.stai[let].planov=0)
                     )
                 )
           do inc(i);
           bres:= bres or (i<stap^.pocet);
           if i<stap^.pocet then
              begin
                if bres then zapis_riadok (f,nl,true);
                zapis_riadok (f,   kbZvisly2 + inschar(' '+strpas(stap^.stad[i]^.nazov),dsLh_g,' ',0)
                                 + kbZvisly  + _cis(stap^.stad[i]^.stai[let].planov,dsLi_g)
                                 + kbZvisly  + _cis(stap^.stad[i]^.stai[let].vyuzity,dsLi_g)
                                 + kbZvisly2,
                              true
                             );
                inc(i)
              end;
         end;
      }

      { b) Opraveny algoritmus pocita pocet dni od 0600 do 0600

       k1:= 0;
       while     (k1<stap^.pocet)
             and (    (stap^.stad[k1]^.typ=PRIESTOR_STRELNICA)
                  and (stap^.stad[k1]^.stai[let].planov>0)
                 )
       do inc(k1);

       if k1>0 then
          begin
            getmem(suma,sizeof(PPRSi_sta)*k1);
            k2:= 0; i:= 0;
            while     (i<k1)
                  and (    (stap^.stad[i]^.typ=PRIESTOR_STRELNICA)
                       and (stap^.stad[i]^.stai[let].planov>0)
                      )
            do begin
                 j:= 0; while (j<k2) and (stap^.stad[i]^.kod<>suma^[j]^.kod) do inc(j);
                 if j<k2 then
                    begin
                      inc(suma^[j]^.stai[let].planov,stap^.stad[i]^.stai[let].planov);
                      inc(suma^[j]^.stai[let].vyuzity,stap^.stad[i]^.stai[let].vyuzity);
                      if suma^[j]^.nazov=nil then suma^[j]^.nazov:= strnew(stap^.stad[i]^.nazov);
                    end
                 else begin
                        new(suma^[j]);
                        new_PRSi_sta(stap^.stad[i],suma^[j]);
                        inc(k2)
                      end;
                 inc(i)
               end;

            for j:= 0 to k2-1 do
              begin
                if (j<k2-1) then zapis_riadok (f,nl,true);
                s:= suma^[j]^.kod;
                if suma^[j]^.nazov<>nil then s:= s + ' ('+strpas(suma^[j]^.nazov)+')';
                zapis_riadok (f,   kbZvisly2 + inschar(' '+s,dsLh_g,' ',1)
                                 + kbZvisly  + _cis(suma^[j]^.stai[let].planov,dsLi_g)
                                 + kbZvisly  + _cis(suma^[j]^.stai[let].vyuzity,dsLi_g)
                                 + kbZvisly2,
                              true
                             );
                disp_PRSi_sta(suma^[j]);
                dispose(suma^[j]);
              end;

            freemem(suma,sizeof(PPRSi_sta)*k1);
          end;
      }

 type  { Suhrnny popis priestoru
         za obdobie

         a) povodne uchovavane udaje
             - miesali sa letecke priestory a strelnice
             - nepocitalo pocet dni strelnic
             - pri prvom spusteni novej verzie sa vsetky neuzatvorene
               (aktualny mesiac) zaznamy skonvertuju na letecke
               priestory
       }


 function nacitaniePRSs_sta0 (fn: string; stad: PPRSs_staDen0): bool; far;
    var   f : file;
          len,res : word;
          i : int;
          {sta : TPRSi_sta;}
    begin
      fillchar(stad^,sizeof(stad^),0);
      nacitaniePRSs_sta0:= true;

      assign(f,fn); reset(f,1);

      BlockRead(f,stad^.pocet,sizeof(stad^.pocet),res);
      for i:= 0 to stad^.pocet-1 do
         begin
           new(stad^.stad[i]); fillchar(stad^.stad[i]^,sizeof(stad^.stad[i]^),0);
           BlockRead (f,stad^.stad[i]^.kod,sizeof(stad^.stad[i]^.kod),res);
           BlockRead (f,stad^.stad[i]^.typ,sizeof(stad^.stad[i]^.typ),res);
           BlockRead (f,stad^.stad[i]^.stai,sizeof(stad^.stad[i]^.stai),res);

           BlockRead (f,len,sizeof(len),res);
           stad^.stad[i]^.nazov:= StrAlloc(len);
           if stad^.stad[i]^.nazov<>nil then BlockRead(f,stad^.stad[i]^.nazov[0],len,res)
           else Seek(f,FilePos(f)+len)
         end;

      close(f)
    end;
