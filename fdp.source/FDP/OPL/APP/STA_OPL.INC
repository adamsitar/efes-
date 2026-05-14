{ ===========================================

   Zobrazenie priebeznych a konecnych udajov

  ===========================================
}
 { Odvodit objekt pre preskakovanie medzi
   polozkami... find_key
   a export do externeho subora,
   ak je to uzatvorena statistika
 }

 function get_sta_archiv(fn: string): string; far;
    var   Dir: DirStr; Name: NameStr; Ext: ExtStr;
    begin
      FSplit(fn, Dir,Name,Ext);
      get_sta_archiv:= get_ARCH_FN(Dir,Ext,msgFSELECT);
    end;

 procedure OStaOPL.zobraz_subor_statistiky_(fn,title: string; den,uzatvorena: bool);
     var   p: pointer;
     begin
       if uzatvorena or den then p:= @get_sta_archiv else p:= nil;
       HelpViewer(fn,title, p,nil,true,hlp_STA);
     end;



{ ===========================================

   Uzatvorenie statistiky za den/mesiac,
   vlastna filozofia

  ===========================================
}

 procedure OStaOPL.uzatvor_statistiku_za_den (date: TDate);
     var   fn : string;
           d: DirStr; n: NameStr; e: ExtStr;
           i  : int;
     begin
      { Spocitanie/kontrola sumarnych zaznamov jednotlivych typov
        sprav a vytvorenie konecneho sumarneho subora, ak su algortimy
        priebezneho spocitavania spolahlive, kontrola nie je potrebna.

        => binarne datove (ð??) a sumarne (ä??) statisticke denne subory
      }

      { Vytvorenie

        => uzatvoreneho denneho STD subora.
        => vyvorenie priebeznej statstistiky za mesiac
      }
       InfoCakaj(msgWAITING,tit_uzatvorenie_dennej_statistiky);
       fn:= get_STAarch_fn (date,false);
       vytvor_tabulku_statistiku_za_ (date,false,fn,nil);
       FSplit(fn, d,n,e);
       MoveFile(fn, pathARCH_STA+n+e);
       if dni_mesiaca(date.r,date.m)>date.d then
          begin
            date.d:= not_archive_day;
            for i:= 0 to poc_StaFDP-1 do StaFDP[i]^.vytvorenie_mesacneho_sumarneho_zaznamu (date);
            vytvor_tabulku_statistiku_za_ (date,false,get_STAarch_fn (date,false),nil)
          end;
       InfoCakaj_zatvor;
     end;


 procedure OStaOPL.uzatvor_statistiku_za_mesiac (date: TDate);
     var   fn : string;
           i  : int;
           DirInfo : SearchRec;
           d  : TDate;
           h  : byte;
           r  : real;

     begin
       InfoCakaj(msgWAITING,tit_uzatvorenie_mesacnej_statistiky);

      { Spocitanie statistiky za jednotlive druhy cinnosti.
        Pretoze zatial sa da vypocet vysledne tabulky od seba oddelit,
        a po udaje ineho typu si siahaju az pri tvorbe vystupnej tabulky,
        poradie je lubobolne, je to vseobecnejsi algoritmus
      }
       date.d:= not_archive_day;
       for i:= 0 to poc_StaFDP-1 do StaFDP[i]^.vytvorenie_mesacneho_sumarneho_zaznamu (date);
       vytvor_tabulku_statistiku_za_ (date,false,get_STAarch_fn (date,false),nil);


      { Upratanie v dennom/mesacnom archive. Do archivu sa presunu :
        => binarne datove (ð??) sa zrusia
        => sumarne (ä??) statisticke denne subory (sa zrusia zatial nie)
        => textove denne (STD) a mesacne (STM) subory
        => ostatne subory z daneho mesiaca sa v archive zrusia.
        Aby som nemusel komlikovane triedit, vsetky subory starsie ako
        ako 1. noveho mesiaca idu do archivu
      }
       r:= DateToSec(date.r,date.m,dni_mesiaca(date.r,date.m));
       FindFirst(path_STA+allfiles,DataAttr,DirInfo);
       while DosError=0 do
         begin
           if isFileAttr (DirInfo,DataAttr) then
              begin
                fn:= path_STA+DirInfo.Name;
                if (not decode_archived_date (fn,true, d.r,d.m,d.d,h)) or (DateToSec(d.r,d.m,d.d)<=r) then
                   begin
                     MoveFile(fn, pathARCH_STA+DirInfo.Name);
                   end
              end;
           CheckProcesses0;
           FindNext(DirInfo)
         end;

      { Upratanie v rocnom archive, odmazu sa subory starsie
        ako nastaveny limit :
      }
       d:= date; i:= date.m; i:= i-staArchMonths;
       if i<0 then begin dec(date.r); i:= (i + 12) mod 12 end;
       date.m:= trunc(i);
       r:= DateToSec(date.r,date.m,1);
       FindFirst(pathARCH_STA+allfiles,DataAttr,DirInfo);
       while DosError=0 do
         begin
           if isFileAttr (DirInfo,DataAttr) then
              begin
                fn:= pathARCH_STA+DirInfo.Name;
                if    (not decode_archived_date (fn,true, d.r,d.m,d.d,h))
                   or (DateToSec(d.r,d.m,1)<r)
                   or (    (DateToSec(d.r,d.m,d.d)<AbsTime-30*secDay)
                       and (    is_STAdata_fn(fn)
                             or is_STAsuma_fn(fn)
                             or is_STAwork_fn(fn)
                           )
                      )
                   then DelFile(pathARCH_STA+DirInfo.Name);
              end;
          CheckProcesses0;
          FindNext(DirInfo)
        end;
       InfoCakaj_zatvor;
     end;
