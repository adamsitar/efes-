{ - najde, skontroluje zmenu a ak je, potom zapise
  - pouzitie parametrov bool znamena, ze statistika
    sa vyhodnoti vzhladom ku aktualne sledovanym
    parametrom
}

{ ---------------------------------------
  kodovanie, lisi sa medzyi modulmi
}
 {const  db_STA_RIADKOV = 1;
        db_sta = 0;
 }

 function sta_to_str(var sta; sta_size: byte): string;
    var   s: string;
    begin
      Move(sta,s[1],sta_size);
      s[0]:= chr(sta_size);
      sta_to_str:= s
    end;

 procedure str_to_sta(s: string; var sta; sta_size: byte);
     begin
       s:= cut_(s);
       Move(s[1],sta,minimum(sta_size,length(s)))
     end;


{ ---------------------------------------
  nazvy pracovnych suborov
}

 function get_STAfn(date: TDate; path: string; ext: str3): string;
    begin
    { subor pretazujuci standartny "get_STAfn" z "archiv",
      pretoze ten presuva data starsie ako den do archivu,
      tu sa presuvaju az data za uplynuly mesiac
    }
      if DateToSec(date.r,date.m,date.d) < DateToSec(year,month,not_archive_day) then path:= get_ARCHIVfn(path);
      get_STAfn:= path + get_PLANfn(date.d,date.m,date.r)+'.'+ext
    end;

{ *.inc - subory: nazvy, nacitanie, ukladanie;
  ak je date.d=0(not_archive_day), vytvori sa
  nazov pre subor na mesiac
}
 function get_STAfn_(date: TDate; ext_sta,ext: string): string;
    begin
      get_STAfn_:= get_STAfn(date, path_STA,ext_sta+copy(ext,length(ext_sta)+1,length(ext)-length(ext_sta)))
    end;

 function get_STAfn_type(fn: string): string;
    var   D: DirStr; N: NameStr; E: ExtStr;
    begin
      FSplit(fn, D,N,E);
      get_STAfn_type:= copy(delchar(E,['.']),1,1)
    end;


 function get_STAdata_fn(date: TDate; ext: string): string;
    begin
     { datovy denny subor o vyvoji spracovania udajov }
      get_STAdata_fn:= get_STAfn_(date, extSTAdata,ext)
    end;

 function is_STAdata_fn(fn: string): bool;
    begin
      is_STAdata_fn:= get_STAfn_type(fn)=extSTAdata
    end;


 function get_STAsuma_fn(date: TDate; ext: string): string;
    begin
     { priebezna/konecna suma za obdobie }
      get_STAsuma_fn:= get_STAfn_(date, extSTAsuma,ext)
    end;

 function is_STAsuma_fn(fn: string): bool;
    begin
      is_STAsuma_fn:= get_STAfn_type(fn)=extSTAsuma
    end;


 function get_STAwork_fn(date: TDate; ext: string): string;
    begin
     { pracovny textovy subor pre vystup udajov statistiky }
      if ext<>'' then
      else if denna_statistika(date) then ext:= extSTD
      else ext:= extSTM;
      get_STAwork_fn:= get_STAfn_(date, extSTAwork,ext)
    end;

 function is_STAwork_fn(fn: string): bool;
    begin
      is_STAwork_fn:= get_STAfn_type(fn)=extSTAwork
    end;


 function get_STAarch_fn_(date: TDate; ext: string): string;
    begin
     { pracovny textovy subor pre vystup udajov statistiky }
      get_STAarch_fn_:= get_STAfn(date, path_STA,ext)
    end;

 function get_STAarch_fn (date: TDate; externy: bool): string;
    var   ext: string;
    begin
     { archivacny denny/mesacny/vystupny subor :
        - pre jednotlive plany : ext = data_ext
        - pre sumarnu dennu/mesacnu/vystupnu statistiku : ext = extSTD/extSTM/extSTA
     }
      if externy then ext:= extSTE
      else if denna_statistika(date) then ext:= extSTD
      else ext:= extSTM;
      get_STAarch_fn:= get_STAarch_fn_(date,ext)
    end;


 function denna_statistika(d: TDate): bool;
    begin
      denna_statistika:= d.d<>not_archive_day;
    end;



{ ---------------------------------------
  nacitanie cfg
}
{ - nacitanie nazvu identifikatora polozky z cfg subora,
    ak nie je naplenena, pouzije vlastny identifikator;
  - ak obsahuje pole %id%,
}
 function  sta_doplnit_nazov_polozky (polozka, id, numid,numval: string; doplnit: bool; zarovnat: byte): string;
    var    tit, s,t : string;
           is : bool;
           i : int;
    begin
      s:= polozka;
      is:= s<>'';
      if doplnit and (not is) then s:= id;
      if numid<>'' then
         begin
           t:= cfg_CISLO+numid+cfg_CISLO;
           i:= pos(t,upstring(s));
           if is and (i>0) then s:= copy(s,1,i-1)+numval+copy(s,i+length(t)+1,length(s)-i-length(t))
           {else s:= s + ' ('+numval+')'};
         end;
      if zarovnat>0 then s:= InsChar_(s,zarovnat,' ',1,true); {s:= copy(s,1,zarovnat)+' '+sta_odd_nazov+'  '}
      sta_doplnit_nazov_polozky:= s
    end;

 function  sta_nazov_polozky (id, numid,numval: string; zarovnat: byte): string;
    var    i : int;
           s : string;
    begin
      {if zarovnat then i:= najdlhsi_nazov else i:= 0;}
      s:= sta_doplnit_nazov_polozky(_read_cfg (cfgSTA,id,false), id, numid,numval, true,zarovnat);
      sta_nazov_polozky:= s
    end;

 procedure read_FL_XX(_cfg_FN: string; cfg_FL_XX: string;
                      var FL_XX: long; var FL_XX_: string
                     );
     begin
       if read_cfg_str(_cfg_FN,cfg_FL_XX,FL_XX_) then
          FL_XX:= get_altM(getchar(delchar(FL_XX_,setCisl_)),getint(FL_XX_,1,setPism_))
     end;


{ ---------------------------------------

}
