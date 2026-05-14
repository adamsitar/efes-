{ --------------------
  inicializacia
  --------------------
}
 constructor OStaFDP.Init(_data_ext    : string;

                          _sta_size   : word;
                          _p_new_sta, _p_disp_sta : pointer;

                          _db_sta_code    : pointer;
                          _db_sta_decode  : pointer;
                          _db_key_code    : pointer;
                          _db_sta_riadkov : byte;

                          _stad_size  : word;
                          _p_new_stad, _p_disp_stad : pointer;
                          _p_zapis_stad, _p_nacitanie_stad : pointer;

                          _sledovanych_poloziek : byte;

                          _cfg_STA : string
                         );
       var   d : Tdate;
       begin
         {inherited Init(nil);}
         data_ext:= _data_ext;

         sta_size:= _sta_size; p_new_sta:= _p_new_sta; p_disp_sta:= _p_disp_sta;
         db_sta_code    := _db_sta_code;
         db_sta_decode  := _db_sta_decode;
         db_key_code    := _db_key_code;
         db_sta_riadkov := _db_sta_riadkov;

         stad_size:= _stad_size;
         stad_size:= _stad_size; p_new_stad:= _p_new_stad; p_disp_stad:= _p_disp_stad;
         {AllocMem (p_stad,stad_size);}
         p_zapis_stad:= _p_zapis_stad; p_nacitanie_stad:= _p_nacitanie_stad;
         sledovanych_poloziek:= _sledovanych_poloziek;

         nacitaj_cfg(_cfg_STA);
         najdlhsi_nazov:= 0; najdlhsi_nazov:= najdi_najdlhsi_nazov;
         prepocitavat_pri_uzatvarani:= true;

         {if p_stad<>nil then
            begin
              init_date (d, year,month,day);
              if (not nacitanie_sumarneho_zaznamu(d, p_stad)) or zmenene_parametre_statistiky then
                 nacitanie_denneho_sumarneho_zaznamu(d, p_stad,false,true)
            end;}
       end;


 destructor OStaFDP.Done;
      begin
       {DeallocMem (p_stad,stad_size);}
       {inherited Done;}
      end;



 procedure OStaFDP.nacitaj_cfg(_cfg_STA: string);
     begin
     { nacitanie cfg subora, nastavenie parametrov podla neho
     }
     end;

 function OStaFDP.najdi_najdlhsi_nazov: byte;
    begin
    { najde najdlsi nazov, aby ostatne mohli byt zarovnane s nim
    } najdi_najdlhsi_nazov:= 0
    end;


{ --------------------
  zapis novej polozky
  --------------------
}
 procedure OStaFDP.initialize_sta (data: pointer; _sta: PStaFDP);
     begin
       fillchar (_sta^,sta_size,0)
     end;

 procedure OStaFDP.new_sta  (_stap: PStaFDP; var _sta: PStaFDP);
     begin
       NewVar (_sta,sta_size,true,p_new_sta,_stap)
     end;

 procedure OStaFDP.disp_sta (var _sta: PStaFDP);
     begin
       DispVar (_sta,sta_size,p_disp_sta,true)
     end;


 function OStaFDP.zapisat_polozku (date: TDate; data: pointer): bool;
    begin
      zapisat_polozku:= true
    end;


 procedure OStaFDP.zapis_polozky (date: TDate; data: pointer);
     var   sta,stap : PStaFDP;
           p_stad   : PStadFDPs;
           DB       : PDB;
           res      : long;
           novy     : bool;
           p        : pointer;
           i        : int;
     begin
       if not zapisat_polozku (date,data) then Exit;

       new_sta (nil,sta);
       initialize_sta (data,sta);

     { nacitanie povodneho zapisu, ak existuje
       a zapis do denneho subora statistiky
     }
       new_sta (sta,stap);
       DB:= New(PDB,Init(get_STAdata_fn(date,data_ext),true,
                         db_sta_riadkov,db_sta_code,db_sta_decode,db_key_code,
                         nil,DBbin)
                        );
       res:= DB^.najdi(stap,true,p_disp_sta);
       novy:= res=-1;
       DB^.zapis(sta,res,true);
       Dispose(DB,Done);

     { aktualizacia dennych sumarnych udajov pre priebezne zobrazenie,
       aby sa okamzite hodnoty nemuseli stale spocitavat...
     }
       new_stad (nil,p_stad);
       if (p_stad<>nil) then
          begin
            nacitanie_sumarneho_zaznamu (date,p_stad);
            if novy then p:= nil else p:= stap;
            aktualizacia_denneho_zaznamu (sta,p, p_stad, false);
            zapis_sumarneho_zaznamu (date, p_stad);
          end;
       disp_stad(p_stad);

       disp_sta (stap);
       disp_sta (sta);
     end;


{ -----------------------------------
  denny zaznam spocitanych poloziek
  -----------------------------------
}
 procedure OStaFDP.initialize_stad (_stad: PStadFDPs);
     begin
       disp_stad_(_stad);
       if _stad<>nil then fillchar(_stad^,stad_size,0)
     end;

 procedure OStaFDP.new_stad  (_stap: PStadFDPs; var _stad: PStadFDPs);
     begin
       NewVar (_stad,stad_size,true,p_new_stad,_stap)
     end;

 procedure OStaFDP.disp_stad_ (_stad: PStadFDPs);
     begin
       if p_disp_stad<>nil then TProc_p(p_disp_stad)(_stad);
     end;

 procedure OStaFDP.disp_stad (var _stad: PStadFDPs);
     begin
       DispVar (_stad,stad_size,p_disp_stad,true)
     end;


 procedure OStaFDP.zapis_sumarneho_zaznamu (date: TDate; _stad: PStadFDPs);
     var   f   : file;
           fn  : string;
           res : word;
     begin
       if _stad=nil then Exit;
       fn:= get_STAsuma_fn(date,data_ext);
       if p_zapis_stad=nil then
          begin
            assign(f,fn);
            rewrite(f,1);
            BlockWrite(f,_stad^,stad_size,res);
            close(f)
          end
       else T_zapis_sumarneho_zaznamu(p_zapis_stad)(fn,_stad)
     end;

 function  OStaFDP.nacitanie_sumarneho_zaznamu (date: TDate; _stad: PStadFDPs): bool;
     var   f   : file;
           fn  : string;
           res : word;
     begin
       nacitanie_sumarneho_zaznamu:= false;
       if (_stad=nil) then Exit;
       fillchar(_stad^,stad_size,0);
       fn:= get_STAsuma_fn(date,data_ext);
       if (FExists(fn)<>0) then Exit;
       nacitanie_sumarneho_zaznamu:= true;
       if p_nacitanie_stad=nil then
          begin
            assign(f,fn);
            reset(f,1);
            BlockRead(f,_stad^,stad_size,res);
            close(f)
          end
       else nacitanie_sumarneho_zaznamu:= T_nacitanie_sumarneho_zaznamu(p_nacitanie_stad)(fn,_stad)
     end;


 function OStaFDP.zmenene_parametre_statistiky(_stad : PStadFDPs): bool;
    begin
      zmenene_parametre_statistiky:= false
    end;


 procedure OStaFDP.aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool);
     begin
     end;

 procedure OStaFDP.nacitanie_denneho_sumarneho_zaznamu
                                                (date: TDate; _stad: PStadFDPs;
                                                 nacitaj,uloz,uzatvor: bool;
                                                 var zmena: bool
                                                );
     var   sta : PStaFDP;
           DB  : PDB;
           i,p : long;
     begin
       zmena:= false;
       if _stad=nil then Exit;

     { nacitanie z docasneho subora...
     } if nacitaj and nacitanie_sumarneho_zaznamu (date,_stad) then
          begin
            zmena:= zmenene_parametre_statistiky (_stad);
            if {(not uzatvor) and} (not zmena) then Exit
          end
       else zmena:= true;

     { spocitanie vsetkych realizovanych zaznamov...
     }
       disp_stad_(_stad);
       initialize_stad (_stad);
       new_sta (nil,sta);
       DB:= New(PDB,Init(get_STAdata_fn(date,data_ext), true, db_sta_riadkov,
                         db_sta_code,db_sta_decode,db_key_code,
                         nil,DBbin)
                        );
       for i:= 0 to DB^.poloziek-1 do if DB^.citaj(i,sta) then aktualizacia_denneho_zaznamu (sta,nil, _stad,true);
       Dispose(DB,Done);
       if nacitaj or uloz or zmena then zapis_sumarneho_zaznamu (date,_stad);
       disp_sta (sta);
     end;


 procedure OStaFDP.aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs);
     begin
     end;

 procedure OStaFDP.nacitanie_mesacneho_sumarneho_zaznamu
                                                  (date: TDate; _stam: PStadFDPs;
                                                   nacitaj,uloz,uzatvor: bool;
                                                   var zmena: bool
                                                  );
     var   _stad  : PStadFDPs;
           i,dni  : int;
           zmenad : bool;
     begin
       zmena:= false;
       if _stam=nil then Exit;
       date.d:= not_archive_day;

     { nacitanie z docasneho subora...
     } if nacitaj and nacitanie_sumarneho_zaznamu (date,_stam) then
          begin
            zmena:= zmenene_parametre_statistiky (_stam);
            if (not uzatvor) and (not zmena) then Exit
          end
       else zmena:= true;

     { spocitanie vsetkych realizovanych zaznamov...
     }
       disp_stad_(_stam);
       initialize_stad (_stam);
       if (date.r=year) and (date.m=month) then dni:= day  { priebezna statistika }
       else dni:= dni_mesiaca(date.r,date.m);              { uzatvorena statistika }
       for date.d:= 1 to dni do
          begin
            new_stad(nil,_stad);
            nacitanie_denneho_sumarneho_zaznamu (date,_stad, nacitaj,uloz,uzatvor, zmenad);
            aktualizacia_sumarneho_zaznamu_dnom (_stam,_stad);
            disp_stad(_stad);
            zmena:= zmena or zmenad;
            CheckProcesses;
          end;
       date.d:= not_archive_day;
       if uzatvor or nacitaj or uloz or zmena then zapis_sumarneho_zaznamu (date,_stam);
     end;

 procedure OStaFDP.vytvorenie_mesacneho_sumarneho_zaznamu (date: TDate);
     var   _stam: PStadFDPs;
           zmena: bool;
     begin
       new_stad(nil,_stam);
       nacitanie_mesacneho_sumarneho_zaznamu
          (date,_stam, not prepocitavat_pri_uzatvarani,prepocitavat_pri_uzatvarani,true,zmena);
       disp_stad(_stam);
     end;



{ ----------------------------------------------------
  a) Pracovny subor spocitanych poloziek
     podla analyzy Jozka Krokusa,
     zatial sa vsak neopuziva, pretoze sa znacne
     lisi od skutocne pouzivanych tabuliek
  ----------------------------------------------------
}
(*
 function  OStaFDP.nazov_polozky (polozka: int): string;
    begin
      nazov_polozky:= ''
    end;

 function  OStaFDP.hodnoty_polozky_za_den (polozka: int; _stad: PStadFDPs): string;
    begin
      hodnoty_polozky_za_den:= ''
    end;


 procedure OStaFDP.zapis_riadok_statistiky (fn: string; p: pchar);
    var    f   : file;
           res : word;
           s   : string;
    begin
      assign(f,fn);
      rewrite(f,1);
      BlockWrite(f,p^,strlen(p),res);
      s:= kbNL; BlockWrite(f,s[1],length(s),res);
      close(f);
    end;

 function  OStaFDP.zapis_poloziek_statistiky (fn: string; _stam: PStaMesFDPs; _dni: int): bool;
    var    polozka, dna : int;
           riadok  : pchar;
    begin
      for polozka:= 1 to sledovanych_poloziek do
        begin
          riadok:= strpasnew(  InsChar_(nazov_polozky(polozka),najdlhsi_nazov,' ',1,true)
                             + sta_odd_den+sta_odd_nazov+sta_odd_den
                            );
          for dna:= 1 to _dni do
            begin
              riadok:= StrNPCopy(riadok,
                                 sta_odd_den+hodnoty_polozky_za_den(polozka,_stam^[dna]),
                                 true,true
                                )
            end;
          zapis_riadok_statistiky (fn, riadok);
          strdispose(riadok);
        end;
      zapis_riadok_statistiky (fn, nil);
    end;


 function  OStaFDP.vytvor_tabulku_statistiky (date: TDate): string;
     var   ft : text;
           fn : string;
           s  : string;

           stam  : TStaMesFDPs;
           i,dni : int;

     procedure pridaj_denny_zaznam (date: TDate);
         begin
           inc(dni);
           AllocMem (stam[dni],stad_size);
           nacitanie_denneho_sumarneho_zaznamu (date,stam[dni],true,false);
         end;

     begin
       if stad_size=0 then Exit;

       fillchar(stam,sizeof(stam),0);
       dni:= 0;
       if date.d=0 then
          begin
            while     (dni+1<=dni_mesiaca(date.r,date.m))
                  and (AbsTime>DateToSec(date.r,date.m,date.d))
            do begin
                 date.d:= dni+1;
                 pridaj_denny_zaznam(date);
                 {_Check}
               end
          end
       else pridaj_denny_zaznam(date);

       fn:= get_STAwork_fn(date,data_ext);
       delfile(fn);
       vytvor_novy_subor(fn);
       zapis_poloziek_statistiky (fn,@stam,dni);
       for i:= 1 to dni do DeallocMem (stam[i],stad_size);

       vytvor_tabulku_statistiky:= fn
     end;
*)

{ ----------------------------------------------------------
  b_a) "Statisticky prehlad leteckej cinnosti za mesiac..."
        - mesacny vykaz letiska
  ----------------------------------------------------------
}

{ ----------------------------------------------------------
  b_b) "Tabulka realizovan7ch letov..."
        - denny a mesacny vykaz strediska
  ----------------------------------------------------------
}


{ ------------------------------------
  uzatvorenie zaznamov
  ------------------------------------
}
 function  OStaFDP.zapis_hlavicku_za_ (var fT: text; p_stad: PStadFDPs; date: TDate; externy: bool): bool;
    begin
      zapis_hlavicku_za_:= true
    end;

 function  OStaFDP.zapis_riadok_za_ (var fT: text; riadok: int; p_stad: PStadFDPs; date: TDate; externy: bool): bool;
    begin
      zapis_riadok_za_:= false
    end;

 function  OStaFDP.napln_zaznam_statistiky_za_ (fn: string; p_stad: PStadFDPs; date: TDate; externy: bool): string;
    var    fT : text;
           riadok : int;
    begin
     { Funkcia naplni subor pre zobrazenie/tlac alebo externy subor
       udajmi o statistike v textovej podobe
     }
      assign(fT,fn); rewrite(fT);
      zapis_hlavicku_za_ (fT,p_stad,date,externy);
      riadok:= 0; while zapis_riadok_za_ (fT,riadok, p_stad,date,externy) do inc(riadok);
      close(fT);
      napln_zaznam_statistiky_za_:= fn
    end;


 function  OStaFDP.vytvor_zaznam_statistiky_za_den (date: TDate; uzatvor,vytvor_subor,externy: bool): string;
     var   p_stad : PStadFDPs;
           fnw,fna : string;
           zmena : bool;
     begin
      { Vytvorenie denneho zaznamu o statistike zo dna "date".
        Parameter "uzatvor" hovori, ci bude vytvori konecny alebo len pracovny denny zaznam pre priebezne zobrazenie.
        Parameter "externy" udava format vystupneho subora. Smie sa pouzit len pre uzatvoreny subor.

        Pre kazdy typ dat :
         1- skontroluje denna "suma" (prepocita sa znova)
         2- podla "suma" a "cfg" sa vytvori textovy pracovny subor "work" pre prislusne data
         3- pri uzatvarani sa "work" sa premenuje sa "std"
      }
       if externy then uzatvor:= false;

       new_stad (nil,p_stad);
       nacitanie_denneho_sumarneho_zaznamu
          (date,p_stad, not prepocitavat_pri_uzatvarani,prepocitavat_pri_uzatvarani,true,zmena);
       fnw:= get_STAwork_fn (date,data_ext);
       napln_zaznam_statistiky_za_ (fnw,p_stad,date,externy);
       disp_stad (p_stad);
       if uzatvor and vytvor_subor then
          begin
            fna:= get_STAarch_fn_ (date,data_ext);
            movefile (fnw,fna);
            vytvor_zaznam_statistiky_za_den:= fna
          end
       else vytvor_zaznam_statistiky_za_den:= fnw
     end;


 function  OStaFDP.vytvor_zaznam_statistiky_za_mesiac (date: TDate; uzatvor,vytvor_subor,externy: bool): string;
     var   p_stam  : PStadFDPs;
           fnw,fna : string;
           zmena   : bool;
     begin
      { Pre kazdy typ dat :
         1- pre vsetky denne zaznamy "suma" sa vytvori, spocita a zapise mesacna "suma"
         2- podla "suma" a "cfg" sa vytvori textovy pracovny subor "work" pre prislusne data
         3- "work" sa premenuje sa "stm"
      }
       date.d:= not_archive_day;
       if externy then uzatvor:= false;

       new_stad (nil,p_stam);
       nacitanie_mesacneho_sumarneho_zaznamu
          (date,p_stam, not prepocitavat_pri_uzatvarani,prepocitavat_pri_uzatvarani,true,zmena);
       fnw:= get_STAwork_fn (date,data_ext);
       napln_zaznam_statistiky_za_ (fnw,p_stam,date,externy);
       disp_stad (p_stam);
       if uzatvor and vytvor_subor then
          begin
            fna:= get_STAarch_fn_ (date,data_ext);
            movefile (fnw,fna);
            vytvor_zaznam_statistiky_za_mesiac:= fna
          end
       else vytvor_zaznam_statistiky_za_mesiac:= fnw
     end;


{ ------------------------------------
  zobrazenie,tlac,kopirovanie
  ------------------------------------
}
{ informacie o aktualnej statistike,
  v pripade, ak sa nastavene parametre sledovanych udajov zmenili (zmenene_parametre_statistiky),
  prepocitaju sa na aktualne platne (nacitanie_denneho_sumarneho_zaznamu s "nacitaj").

 procedure OStaFDP.zobraz_priebeznu_statistiku_za_ (den: bool);
     var   date : TDate;
           fn   : string;
     begin
       init_date (date, year,month,day);
       if not den then date.d:= not_archive_day;
       {fn:= vytvor_tabulku_statistiky (date);
       delfile(fn)
     end;

 procedure OStaFDP.zobraz_statistiku_za_ (den: bool);
     var   date : TDate;
           fn   : string;
     begin
       init_date (date, year,month,day);
       if not den then date.d:= 0;
       fn:= vytvor_tabulku_statistiky (date);
       delfile(fn)
     end;
}
