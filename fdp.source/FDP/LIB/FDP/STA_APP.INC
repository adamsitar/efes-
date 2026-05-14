{ -----------------------------------------
  inicializacia objektu statistiky
  -----------------------------------------
}
 constructor OStaAPP.Init(_cfg_STA,_kod_STA: string);
       var   fn: string;
             r: word;
             m,d,h: byte;
             i : int;

       begin
         write(kbNL+'Initialize statistics... ');

         hod_vypoctu_sta:= 6;

         poc_StaFDP:= 0;
         tvorba_samostatnych_modulov_statistiky:= false;
         tvorba_spolocneho_modulu_statistiky:= false;


       { nacitanie konfiguraku
       } cfg_STA:= _cfg_STA;
         kod_STA:= _kod_STA;
         read_cfg(cfg_STA);

         init_date(posledna_sta, year,month,day);
         (*fn:= najmladsi_subor (path_STA,'*.'+extSTD);
         posledna_sta.d:= day;
         posledna_sta.m:= month;
         posledna_sta.r:= year;
         if (fn<>'') and decode_archived_date (fn,true, r,m,d,h) then
            begin
              {NextDate(r,m,d);}
              posledna_sta.d:= d;
              posledna_sta.m:= m
            end;
         fn:= najmladsi_subor (path_STA,'*.'+extSTM);
         if (fn<>'') and decode_archived_date (fn,true, r,m,d,h) then
            begin
              posledna_sta.m:= trunc(Limit(m+1, 1,12, 1));
              posledna_sta.r:= r;
              if posledna_sta.m<m then inc(posledna_sta.r);}
            end;*)
         read_kod_STA;


       { inicializacia archivu
       } if not is_cfgArch then
            begin
              {ArchDays  := staArchDays;
              ArchMonths := staArchMonths;}
              check_archiv;
            end;

         _mkdir(path_STA);
         _mkdir(pathARCH_STA);


       { inicializacia modulov sledovanych udajov
       }
         inicializacia_modulov;


       { inicializacia ostatnych parametrov
       }
         najdlhsi_nazov:= 0;
         for i:= 0 to poc_StaFDP-1 do najdlhsi_nazov:= maximum(najdlhsi_nazov,StaFDP[i]^.najdi_najdlhsi_nazov);
         najdlhsi_nazov:= minimum(maximalny_najdlhsi_nazov,najdlhsi_nazov);

         init_STA(@Self);

         writeln('Done.'+kbNL)
       end;


 destructor OStaAPP.Done;
      var   i : int;
      begin
        for i:= 0 to poc_StaFDP-1 do Dispose(StaFDP[i],Done);
      end;


 procedure OStaAPP.read_cfg(_cfg_STA: string);
     begin
       {titO:= getchar(_read_cfg(_cfg_STA,cfg_O,false));
       titP:= getchar(_read_cfg(_cfg_STA,cfg_P,false));
       titS:= getchar(_read_cfg(_cfg_STA,cfg_S,false));
       titZ:= getchar(_read_cfg(_cfg_STA,cfg_Z,false));

       titO_:= _read_cfg(_cfg_STA,cfg_O_,false);
       titP_:= _read_cfg(_cfg_STA,cfg_P_,false);
       titS_:= _read_cfg(_cfg_STA,cfg_S_,false);
       titZ_:= _read_cfg(_cfg_STA,cfg_Z_,false);}
     end;


 procedure OStaAPP.read_kod_STA;
     var   f: file of TDate;
     begin
       if FExists(kod_STA)<>0 then Exit;
       Assign(f,kod_STA);
       Reset(f);
       Read(f,posledna_sta);
       Close(f);
     end;


 procedure OStaAPP.save_kod_STA;
     var   f: file of TDate;
     begin
       Assign(f,kod_STA);
       Rewrite(f);
       Write(f,posledna_sta);
       Close(f);
     end;


 function OStaAPP.inicializuj_modul(p_OStaFDP: POStaFDP): POStaFDP;
    begin
      if p_OStaFDP<>nil then
         begin
           StaFDP[poc_StaFDP]:= p_OStaFDP;
           inc(poc_StaFDP)
         end;
      inicializuj_modul:= p_OStaFDP
    end;


 procedure OStaAPP.inicializacia_modulov;
     begin
     { inicializacia modulov sledovanych udajov
       naplni konkretny objekt
     }
     end;


 procedure OStaAPP.inicializacia_dennych_zaznamov (nacitaj,uloz: bool);
     var   i : int;
           b : bool;
           d : Tdate;
     begin
       {init_date (d, year,month,day);
       for i:= 0 to poc_StaFDP-1 do
         begin
           b:= StaFDP[i]^.zmenene_parametre_statistiky;
           StaFDP[i]^.nacitanie_denneho_zaznamu(d, StaFDP[i]^.p_stad, nacitaj or b, uloz or b);
         end;}
     end;



{ -----------------------------------------
  formatovanie textu
  -----------------------------------------
}

 function OStaAPP._tit(key: string; sirka: int): string;
    var   s,t: string;
          i,p: int;
    begin
      s:= getstr(__read_cfg(cfg_STA,key,1),2,odd_cfg);
      i:= pos(cfg_CISLO,s);
      if i>0 then
         begin
           t:= copy(s,i+1,length(s)-i);
           p:= pos(cfg_CISLO,t);
           if p>0 then
              begin
                t:= copy(t,1,p-1);
                t:= cut_(getstr(__read_cfg(cfg_STA,t,1),2,odd_cfg));
                s:= copy(s,1,i-1)+t+copy(s,i+p+1,length(s)-p-i)
              end;
         end;
      if length(s)>sirka then s:= cut_r(s);
      if length(s)>sirka then s:= cut_(s);
      s:= inschar(s,sirka,' ',1);
      _tit:= s
    end;

 function OStaAPP._cis(val: int; sirka: int): string;
    var   s: string;
    begin
      if val<>0 then s:= cstr(N(val),3) else s:= '';
      _cis:= inschar(' '+s+' ',sirka,' ',1)
    end;


{ -----------------------------------------
  priebezne/konecne vyhodnotenie statistky
  -----------------------------------------
}

 procedure OStaAPP.vytvor_tabulku_statistiku_za_ (date: TDate; externy: bool; spolocny_subor: string; datove_subory: PPChars);
     var   i : int;
     begin
       if tvorba_spolocneho_modulu_statistiky then
          for i:= 0 to poc_StaFDP-1 do
              CopyFileI (spolocny_subor,strpas(datove_subory^[i]),_filesize(spolocny_subor),true, false);
     end;


 function  OStaAPP.vytvor_statistiku_za_den (date: TDate; uzatvor,externy: bool): string;
     var   fn  : string;
           fnds : PPChars;
           i   : int;
     begin
      { Vytvorenie statistickych prehladov za den :
        - pre kazdy typ spracovavanych udajov
        - spolocnu tabulku pre vsetky ich postupnym skopirovanim
          (vytvori zatial podla naprogramovaneho poradia)
      }
       if externy then fn:= extSTE else fn:= extSTD;
       fn:= get_STAarch_fn_ (date,fn);
       vytvor_novy_subor(fn);
       getmem(fnds,sizeof(pchar)*poc_StaFDP);
       fillchar(fnds^,sizeof(pchar)*poc_StaFDP,0);
       for i:= 0 to poc_StaFDP-1 do
          fnds^[i]:= strpasnew(StaFDP[i]^.vytvor_zaznam_statistiky_za_den(
                               date,uzatvor,tvorba_samostatnych_modulov_statistiky,externy
                              ));
       vytvor_tabulku_statistiku_za_ (date,externy, fn,fnds);
       freemem(fnds,sizeof(pchar)*poc_StaFDP);
     end;


 procedure OStaAPP.uzatvor_statistiku_za_den (date: TDate);
     begin
     { Spocitanie
     }
       vytvor_statistiku_za_den (date,true,false);

      { uprace sa v dennom archive :
        - odmazu sa vsetky "work" subory z dni starsich ako je uzatvoreny
          vcitane, pretoze uz nebudu potrebne
      }
       Del(get_STAwork_fn(date,fn_all));
     end;


 function  OStaAPP.vytvor_statistiku_za_mesiac (date: TDate; uzatvor,externy: bool): string;
     var   fn  : string;
           fnds: PPChars;
           i   : int;
     begin
      { Vytvorenie statistickych prehladov za mesiac :
        - pre kazdy typ spracovavanych udajov
        - spolocnu tabulku pre vsetky ich postupnym skopirovanim
          (vytvori zatial podla naprogramovaneho poradia)
      }
       fn:= get_STAarch_fn_ (date,extSTM);
       vytvor_novy_subor(fn);
       getmem(fnds,sizeof(pchar)*poc_StaFDP); fillchar(fnds^,sizeof(pchar)*poc_StaFDP,0);
       for i:= 0 to poc_StaFDP-1 do
           fnds^[i]:= strpasnew(StaFDP[i]^.vytvor_zaznam_statistiky_za_mesiac(
                                date,tvorba_samostatnych_modulov_statistiky,true,false
                               ));
       vytvor_tabulku_statistiku_za_ (date,externy, fn,fnds);
       freemem(fnds,sizeof(pchar)*poc_StaFDP);
     end;


 procedure OStaAPP.uzatvor_statistiku_za_mesiac (date: TDate);
     var   fn : string;
           fnds : PPChars;
           i,dni : int;
           d : TDate;
     begin
       date.d:= not_archive_day;

       vytvor_statistiku_za_mesiac (date,true,false);

      { Upratanie v dennom/mesacnom archive :
        - pracovne subory "data","suma","work" na prislusne dni
          a pracovne subory "work" na dany mesiac
          nebudu potrebne a preto sa zrusia.
        - presun ostatnych suborov z daneho mesiaca do archivu
      }
       d:= date; _19__(d.r); dni:= _1990[d.m]; _19__(year);
       for d.d:= 1 to dni do
          begin
            {Del(get_STAdata_fn(d,fn_all);}
            Del(get_STAsuma_fn(d,fn_all));
            Del(get_STAwork_fn(d,fn_all));
          end;
       Del(get_STAwork_fn(date,fn_all));
       archivuj_subory (path_STA,fn_all,pathARCH_STA,true,by_months);

      { Upratanie v rocnom archive :
      }
       uprac_archiv (pathARCH_STA,fn_all,true,by_days,@staArchDays);
       uprac_archiv (pathARCH_STA,fn_all,true,by_months,@staArchMonths);
     end;



 procedure OStaAPP.check;
     const smphr : bool = false;
           suma  : bool = true;
           h : byte = 25;

     var   d : TDate;
           o : byte;

     begin
       if smphr then Exit;

      { Ak sa zmenil sa sposob sledovania statistiky na priebezny,
        potom sa prepocitaju priebezne sledovane hodnoty
      }
       if (h<>hour) or (suma<>STA_PRIEBEZNE) then
          begin
            smphr:= true;
            if (hour=0) or (not suma) then inicializacia_dennych_zaznamov(true,true);
            h:= hour;
            suma:= STA_PRIEBEZNE;
            smphr:= false;
          end;


      { Uzatvorenie statistiky za posledny den, ked bol program spusteny.
        Ostatne zatial treba spustat manualne.
      }
      {$IFNDEF DEMO}
       if (hour>=hod_vypoctu_sta) then
          begin
            smphr:= true;

            if (day<>posledna_sta.d) or (month<>posledna_sta.m) then
               begin
                 uzatvor_statistiku_za_den(posledna_sta);
                 posledna_sta.d:= day;
                 save_kod_STA
               end;

            if (month<>posledna_sta.m) or (year<>posledna_sta.r) then
               begin
                 d:= posledna_sta; d.d:= 1;
                 uzatvor_statistiku_za_mesiac(d);
                 posledna_sta.m:= month;
                 posledna_sta.r:= year;
                 save_kod_STA;
               end;

            smphr:= false;
          end
      {$ENDIF}
     end;


{ -----------------------------------------
  zmena parametrov po uzatvoreni statitiky
  -----------------------------------------
}
 function OStaApp.povolena_aktualizacia_statistiky (date: TDate): bool;
    var   ri,rd : real;
    begin
      povolena_aktualizacia_statistiky:=
             (DateToSec(date.r,date.m,1) = DateToSec(year,month,1))
          or (    (day=1)
              and (DateToSec(date.r,date.m,dni_mesiaca(date.r,date.m)) + secDay = DateToSec(year,month,1))
              and (hour<hod_vypoctu_sta)
             )
    end;

 function OStaApp.aktualizacia_uzatvorenej_statistiky (date: TDate): bool;
    var   ri,rd : real;
    begin
      ri:= DateToSec(date.r,date.m,date.d);
      rd:= DateToSec(year,month,day);
      aktualizacia_uzatvorenej_statistiky:= (ri+secDay<rd) or ((ri+secDay=rd) and (hour<hod_vypoctu_sta))
    end;

 procedure OStaApp.aktualizuj_uzatvorenu_statistiku (date: TDate);
    begin
      if not aktualizacia_uzatvorenej_statistiky (date) then Exit;
      uzatvor_statistiku_za_den (date);
    end;


{ -----------------------------------------
  zobrazenie priebeznych a konecnych udajov
  -----------------------------------------
}
 procedure OStaAPP.zobraz_subor_statistiky_(fn,title: string; den,uzatvorena: bool);
     begin
       _infop (fn,title, 0,0, true,false,nil);
     end;


 procedure OStaAPP.zobraz_priebeznu_statistiku_(den: bool);
     var   d  : TDate;
           fn : string;
     begin
       init_date (d, year,month,day);
       if not den then d.d:= not_archive_day;
       {fn:= get_STAwork_fn(d,'');}
       fn:= get_STAarch_fn(d,false);
       if den or (FExists(fn)<>0) then vytvor_tabulku_statistiku_za_ (d,false,fn,nil);
       zobraz_subor_statistiky_(fn,tit_priebezna_statistika,den,false);
       {delfile(fn);}
     end;


 procedure OStaAPP.zobraz_uzatvorenu_statistiku_ (den: bool);
     var   ext : string;
     begin
       if den then ext:= extSTD else ext:= extSTM;
       zobraz_subor_statistiky_(pathARCH_STA + najmladsi_subor(pathARCH_STA,fn_all+'.'+ext),
                                tit_uzatvorena_statistika,den,true
                               );
     end;
