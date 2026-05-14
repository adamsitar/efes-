{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   zaznam o poslednej inicializacii fpl z rpl,
   pamata sa den, na ktory boli plany generovane,
   a posledny plan, ak bola inicializacia prerusena,
   ak bola dokoncena, obsahuje "IA5_ETX"
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 const  semaphor_rpl : bool = false;

 type   TlastRPL = record
          date : Tdate;    { datum posledneho dna, na ktory boli spracovane fpl z rpl }
          key  : string;   { posledny spracovany rpl, ak boli vsetky, tak "IA5_ETX"   }
        end;

 var    lastRPL : TlastRPL;

 procedure save_lastRPL;
     var   f: file of TlastRPL;
     begin
       assign(f,fn_RPLupdated);
       rewrite(f);
       write(f,lastRPL);
       close(f)
     end;

 function read_RPLlast: bool;
    var   f: file of TlastRPL;
    begin
      read_RPLlast:= false;
      fillchar(lastRPL,sizeof(lastRPL),0);
      if FExists(fn_RPLupdated)<>0 then Exit;
      read_RPLlast:= true;
      assign(f,fn_RPLupdated);
      reset(f);
      read(f,lastRPL);
      close(f)
    end;

 procedure null_RPLlast;
     begin
       init_date(lastRPL.date, year,month,day);
       {with lastRPL.date do PrevDate(r,m,d);}
       lastRPL.key:= IA5_ETX;
       save_lastRPL;
       is_RPL:= false;
     end;

 function is_RPLpend: bool;
    begin
      is_RPLpend:=     (cut_(lastRPL.key)<>'')
                   and (lastRPL.key<>IA5_ETX)
                   and (datetosec(lastRPL.date.r,lastRPL.date.m,lastRPL.date.d)=datetosec(year,month,day)+secDay);
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   fcia pre spracovanie rpl po jednom,
   pokial nie je vydany prikaz pend,
   alebo nie je precitany posledny
   rpl
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

 type  { pomocna struktura pre odovzdanie parametrov
         o spracovavanej db rpl do riadiacej fcie
       }
         p_rpl_data = ^type_rpl_data;
         type_rpl_data = record
           date : TDate;
           den  : word;
           db   : pdb;
           pos  : int;
         end;


 function _RPLdate_r (date: string): real;
    var   d : TDate;
    begin
    { dekodovanie datumu platnosti rpl
    } if date<>rpl_UFN then
         begin
           decode_l4_date(date,d);
           _RPLdate_r:= DateToSec(d.r,d.m,d.d)
         end
      else _RPLdate_r:= absTime+secDAY
    end;


 function _spracuj_RPLF (data: p_rpl_data; o: PProcess): bool; far;
    var   RPL : DRPLF;
          res : bool;
    begin
      if data^.db^.citaj (data^.pos,@RPL) then
         begin
          { zapamatanie posledneho spracovaneho planu
          }
           lastRPL.key:= codekey_RPLF(@RPL);
           if o<>nil then o^.new_item(RPL.rpl._7a+'-'+RPL.rpl._13a);
           save_lastRPL;

          { urcenie, ci rpl je platny na dalsi den
            a jeho pripadne zaradenie ku fpl
          }
           if     inRange(datetosec(lastRPL.date.r,lastRPL.date.m,lastRPL.date.d),
                          _RPLdate_r(RPL.rpl.zac),_RPLdate_r(RPL.rpl.kon)
                         )
              and (RPL.rpl.dni[data^.den] in [chr(ord('0')+data^.den),'x','X'])
              and (RPL.rpl.val <> RPL_OFF)
                then
                   begin
                     update_date_FPL4 (RPL.fpl,data^.date);
                     if (p_zarad_RPL_FPL4<>nil) then TProc_p(p_zarad_RPL_FPL4)(@RPL);
                   end;

           disp_RPLF (@RPL);

           data^.pos:= data^.pos+1;
           res:= data^.pos >= data^.db^.poloziek;
         end
      else res:= true;

      _spracuj_RPLF:= res;
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   hlavna fcia pre riadenie spracovania rpl
   do rpl, je ju mozne uzivatelsky
   pozastavit
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

 function  make_FPL (en_pend: bool): bool;
    var    data : type_rpl_data;
           r,m,d : word;
           fn : string;
           is_pend,b : bool;
    begin
      make_FPL:= false;

      semaphor_rpl:= true;

     { naplnenie udajov pre spracovanie
       a volanie ext fcie spracovania
       (dekodovanie a zaradenie)
     }

     { a) zistenie poradoveho cisla nasledujuceho dna
     }
      asm cli end;
      GetDate(r,m,d, data.den);  { den je od 1..6, nedela je 0 }
      if den=0 then den:= 7;
      asm sti end;
      init_date(data.date, r,m,d);
      with data do
        begin
          with date do NextDate (r,m,d);
          den:= ((den+1) mod 7);
          if den=0 then den:= 7;
        end;

      if not eq_date(lastRPL.date,data.date) then
         begin
           lastRPL.date:= data.date;
           lastRPL.key:= '';
           save_lastRPL;
         end;

      is_pend:= false;
      while (lastRPL.key<>IA5_ETX) and (not is_pend) do
        begin

         { b) otvorenie databazy, ktora je v poradi...
         }
          if (cut_(lastRPL.key)='') then fn:= get_RPLfn_('A')
          else fn:= get_RPLfn_(lastRPL.key);

          data.db:= New(PDB,Init(fn,false,
                        db_RPLF_RIADKOV,@codeDB_RPLF,
                        @decodeDB_RPLF,@codekey_RPLF,
                        nil,dbattr_RPLF)
                       );

          if (cut_(lastRPL.key)='') then data.pos:= -1
          else data.pos:= data.db^.vyhladaj_kluc(lastRPL.key);

          if data.pos<data.db^.poloziek-1 then
             begin
               inc(data.pos);

              { c) spracovanie planov databazy
              }
               while (data.pos < data.db^.poloziek) and (not is_pend) do
                 begin
                   b:= __INFO_DB; __INFO_DB:= false;
                   InfoProcess (tit_rpl_to_fpl+':',titDLA,'ÿ',rightchar('ÿ',kod_7a+1+kod_AP+1,' '),@_spracuj_RPLF,@data);
                   __INFO_DB:= b;
                   if (data.pos < data.db^.poloziek-1) and en_pend then is_pend:= true;
                 end;
             end;

          dispose(data.db,Done);

          if is_pend then
             begin
               is_RPL:= true;
             end
          else begin
                 if lastRPL.key[1]<'Z' then lastRPL.key:= succ(lastRPL.key[1])
                 else begin
                        lastRPL.key:= IA5_ETX;
                        is_RPL:= false
                      end;
                 save_lastRPL;
               end;

        end;

      if (lastRPL.key[1]=IA5_ETX) then
         begin
           save_lastRPL;
           is_RPL:= false
         end;

      semaphor_rpl:= false;

      make_FPL:= not is_RPL
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Kontrola, ci nenadisla doba automatickej
   inicializacie fpl z databazy rpl...
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure check_RPL;
     const m : byte = 60;
     begin
       if (m=min) or semaphor_rpl then Exit;
       m:= min;

       if     (not is_RPL)    { nie je rucne pozastavene automaticke generovanie rpl-fpl }
          and (not rpl_PND)   { nie je menu/konfiguraciou pozastavene - // -  }
                              { plany na buduci den este neboli inicializovane }
          and (datetosec(lastRPL.date.r,lastRPL.date.m,lastRPL.date.d)<=datetosec(year,month,day))
                              { nadisla hodina inicialzacie }
          and (timetosec(rpl_hour,rpl_min,0)<=timetosec(hour,min,0))
          {$IFDEF BACKUP}
           and (not SERVERstatus)
          {$ENDIF}
             then
          begin
            lastRPL.key:= '';
            save_lastRPL;
            make_FPL(true)
          end

       else if is_RPL and (hour>=23) then
          begin
          { Tady konci sranda a pruser zacina,
            musia sa inicializovat vsetky fpl
            na zaftra
          } make_FPL(false);
          end
     end;


 procedure inicializacia;
     var   s: string;
           t: text;
     begin
       write('Initialize RPL... ');

       if not read_RPLlast then
          begin
          { predstavi si, ze plany rpl boli na dnes podane (vcera)
          }
            null_RPLlast;
          end

       else begin
            { kontrola, ci boli vsetky rpl plany
              na zajtra spracovane
            }
              is_RPL:= is_RPLpend
            end;

       is_RPLDB:= (Exists(fn_RPLext_copy)=0);
       is_RPLDBERR:= Exists(fn_RPLext_err)=0;

       s:= path_RPL_SOURCE;
       if FExists(fn_RPLext_src)=0 then
          begin
            assign(t,fn_RPLext_src);
            reset(t);
            readln(t,s);
            close(t);
          end;
       if s<>'' then path_RPL_SOURCE:= s;

       writeln('Done.')
     end;
