{ ---------------------
  Statistika SRLP
  ---------------------
}

{$IFDEF MACC}

 const  dsSLh      = 10;
        dsSLi      =  8;
        pocSLi     =  5;
        dsSRLP     =  1 + 1+dsSLh + (1+dsSLi)*pocSLi + 1;

        pocSFPLMi  =  6;
        pocSFPLCi  =  3;


 procedure OStaOPL.statistika_letov_letisk (var f: text; date: TDate);
     var   i,l  : int;
           s,nl : string;
           b    : TsBod;
           {$IFDEF FPL0}
            stad: PFPLMs_staDen;
           {$ENDIF}
           suma_vfr,suma_ifr,suma_tsa,suma_ine,suma_let: int;
     begin
      {$IFDEF FPL0}
       zapis_riadok (f,  kbLavy2Horny2    + inschar('',dsSLh,kbVodorovny2,1)
                       + kbVodorovny2Dole + inschar('',(1+dsSLi)*4-1,kbVodorovny2,1)
                       + kbVodorovny2Dole + inschar('',dsSLi,kbVodorovny2,1)
                       + kbPravy2Horny2,
                     true
                    );

       zapis_riadok (f,  kbZvisly2 + inschar('',dsSLh,' ',1)
                       + kbZvisly  + _tit(cfg_REALIZED_FLIGHTS,(1+dsSLi)*4-1)
                       + kbZvisly  + inschar('',dsSLi,' ',1)
                       + kbZvisly2,
                     true
                    );

       s:=  kbZvisly2 + _tit(cfg_AIRBASE,dsSLh) + kbZvislyDoprava;
       for i:= 1 to pocSLi-2 do s:= s + inschar('',dsSLi,kbVodorovny,1) + kbVodorovnyDole;
       s:= s + inschar('',dsSLi,kbVodorovny,1) + kbZvislyDolava;
       s:= s + _tit(cfg_SUMA,dsSLi) + kbZvisly2;
       zapis_riadok (f,s,true);

       zapis_riadok (f,  kbZvisly2 + inschar('',dsSLh,' ',1)
                       + kbZvisly  + _tit(cfg_FPLM_VFR,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLM_IFR,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLM_TSA,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLO,dsSLi)
                       + kbZvisly  + inschar('',dsSLi,' ',1)
                       + kbZvisly2,
                     true
                    );

       new(stad);
       sta_FPLM^.nacitanie_sumarneho_zaznamu (date,stad);

       nl:= kbZvisly2Doprava + inschar('',dsSLh,kbVodorovny,1);
       for i:= 1 to pocSLi-1 do nl:= nl + kbKriz + inschar('',dsSLi,kbVodorovny,1);
       nl:= nl + kbKriz + inschar('',dsSLi,kbVodorovny,1) + kbZvisly2Dolava;

       suma_vfr:= 0; suma_ifr:= 0; suma_tsa:= 0; suma_ine:= 0; suma_let:= 0;
       for l:= 0 to poc_AIRBASE-1 do
         begin
           with stad^ do
             begin
               LK_m^.read(l,b);

               s:=   kbZvisly2 + inschar (' '+b.kod,dsSLh,' ',1)
                   + kbZvisly  + _cis(mil[l].letov - mil_ifr[l].letov, dsSLi)
                   + kbZvisly  + _cis(mil_ifr[l].letov,                dsSLi)
                   + kbZvisly  + _cis(tsa[l].letov,                    dsSLi)
                   + kbZvisly  + _cis(ine[l].letov,                    dsSLi)
                   + kbZvisly  + _cis(  mil[l].letov
                                      + tsa[l].letov
                                      + ine[l].letov
                                                                     , dsSLi)
                   + kbZvisly2;

               inc(suma_vfr,mil[l].letov - mil_ifr[l].letov);
               inc(suma_ifr,mil_ifr[l].letov);
               inc(suma_tsa,tsa[l].letov);
               inc(suma_ine,ine[l].letov);

               inc(suma_let,mil[l].letov + tsa[l].letov + ine[l].letov);
             end;
           zapis_riadok (f,nl,true);
           zapis_riadok (f,s,true);
         end;

       zapis_riadok (f,nl,true);
       s:=   kbZvisly2 + _tit(cfg_SUMA,dsSLh)
           + kbZvisly  + _cis(suma_vfr,dsSLi)
           + kbZvisly  + _cis(suma_ifr,dsSLi)
           + kbZvisly  + _cis(suma_tsa,dsSLi)
           + kbZvisly  + _cis(suma_ine,dsSLi)
           + kbZvisly  + _cis(suma_let,dsSLi)
           + kbZvisly2;
       zapis_riadok (f,s,true);

       nl:= kbLavy2Dolny2 + inschar('',dsSLh,kbVodorovny2,1);
       for i:= 1 to pocSLi-1 do nl:= nl + kbVodorovny2Hore + inschar('',dsSLi,kbVodorovny2,1);
       nl:= nl + kbVodorovny2Hore + inschar('',dsSLi,kbVodorovny2,1) + kbPravy2Dolny2;
       zapis_riadok (f,nl,true);

       disp_FPLMs_stad(stad);
       dispose(stad);
      {$ENDIF}
     end;


 procedure OStaOPL.statistika_letov_sumarna (var f: text; date: TDate);
     var   dx,dxx, i,l  : int;
           s,nl : string;
           {$IFDEF FPL0}
            stam: PFPLMs_staDen;
            stac: PFPLCs_staDen;
           {$ENDIF}
     begin
       dx:= dsSRLP-dsdx;

      {$IFDEF FPL0}
      { -------------------------------------
        Sumarna statistika vojenskych letov
        -------------------------------------
      }
       new(stam);
       sta_FPLM^.nacitanie_sumarneho_zaznamu (date,stam);

       zapis_riadok (f,  kbLavy2Horny2 + inschar('',dx,kbVodorovny2,1) + kbPravy2Horny2, true);
       zapis_riadok (f,  kbZvisly2 + _tit(cfg_MILITARY_FLIGHTS,dx) + kbZvisly2, true);

       s:=  kbZvisly2Doprava + inschar('',dsSLi,kbVodorovny,1);
       for i:= 1 to pocSFPLMi-2 do s:= s + kbVodorovnyDole + inschar('',dsSLi,kbVodorovny,1);
       dxx:= dx-length(s);
       s:= s + kbVodorovnyDole + inschar('',dxx,kbVodorovny,1) + kbZvisly2Dolava;
       zapis_riadok (f,s,true);

       zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLM_VFR,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLM_IFR,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLM_FL, dsSLi)
                       + kbZvisly  + _tit(cfg_FPLM_TSA,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLO,dsSLi)
                       + kbZvisly  + _tit(cfg_SUMA,dxx)
                       + kbZvisly2,
                     true
                    );

       s:=  kbZvisly2Doprava + inschar('',dsSLi,kbVodorovny,1);
       for i:= 1 to pocSFPLMi-2 do s:= s + kbKriz + inschar('',dsSLi,kbVodorovny,1);
       dxx:= dx-length(s);
       s:= s + kbKriz + inschar('',dxx,kbVodorovny,1) + kbZvisly2Dolava;
       zapis_riadok (f,s,true);

       l:= max_AIRBASE;
       with stam^ do
         zapis_riadok (f,  kbZvisly2 + _cis(mil[l].letov-mil_ifr[l].letov,dsSLi)
                         + kbZvisly  + _cis(mil_ifr[l].letov,dsSLi)
                         + kbZvisly  + _cis(mil_fl[l].letov,dsSLi)
                         + kbZvisly  + _cis(tsa[l].letov,dsSLi)
                         + kbZvisly  + _cis(ine[l].letov,dsSLi)
                         + kbZvisly  + _cis(mil[l].letov+ine[l].letov{+tsa[l].letov},dxx)
                         + kbZvisly2,
                       true
                      );

       s:=  kbLavy2Dolny2 + inschar('',dsSLi,kbVodorovny2,1);
       for i:= 1 to pocSFPLMi-2 do s:= s + kbVodorovny2Hore + inschar('',dsSLi,kbVodorovny2,1);
       dxx:= dx-length(s);
       s:= s + kbVodorovny2Hore + inschar('',dxx,kbVodorovny2,1) + kbPravy2Dolny2;
       zapis_riadok (f,s,true);

       sta_FPLM^.disp_stad_(stam);
       dispose(stam);


      { -------------------------------------
        Sumarna statistika civilnych letov
        -------------------------------------
      }
       new(stac);
       sta_FPLC^.nacitanie_sumarneho_zaznamu (date,stac);

       zapis_riadok (f,  kbLavy2Horny2 + inschar('',dx,kbVodorovny2,1) + kbPravy2Horny2, true);
       zapis_riadok (f,  kbZvisly2 + _tit(cfg_CIVILIAN_FLIGHTS,dx) + kbZvisly2, true);

       s:=  kbZvisly2Doprava + inschar('',dsSLi,kbVodorovny,1);
       for i:= 1 to pocSFPLCi do s:= s + kbVodorovnyDole + inschar('',dsSLi,kbVodorovny,1);
       dxx:= dx-length(s);
       s:= s + kbVodorovnyDole + inschar('',dxx,kbVodorovny,1) + kbZvisly2Dolava;
       zapis_riadok (f,s,true);

       zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLC_VFR,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLC_IFR,dsSLi)
                       + kbZvisly  + _tit(cfg_FPLC_FL,dsSLi)
                       + kbZvisly  + _tit(cfg_SUMA,dsSLi)
                       + kbZvisly  + inschar('',dxx,' ',1)
                       + kbZvisly2,
                     true
                    );

       s:=  kbZvisly2Doprava + inschar('',dsSLi,kbVodorovny,1);
       for i:= 1 to pocSFPLCi do s:= s + kbKriz + inschar('',dsSLi,kbVodorovny,1);
       s:= s + kbZvislyDolava + inschar('',dxx,' ',1) + kbZvisly2;
       zapis_riadok (f,s,true);

       l:= max_AIRBASE;
       zapis_riadok (f,  kbZvisly2 + _cis(stac^.vfr,dsSLi)
                       + kbZvisly  + _cis(stac^.sta.realizovanych-stac^.vfr,dsSLi)
                       + kbZvisly  + _cis(stac^.fl,dsSLi)
                       + kbZvisly  + _cis(stac^.sta.realizovanych,dsSLi)
                       + kbZvisly  + inschar('',dxx,' ',1)
                       + kbZvisly2,
                     true
                    );

       s:=  kbLavy2Dolny2 + inschar('',dsSLi,kbVodorovny2,1);
       for i:= 1 to pocSFPLCi do s:= s + kbVodorovny2Hore + inschar('',dsSLi,kbVodorovny2,1);
       dxx:= dx-length(s);
       s:= s + kbVodorovny2Hore + inschar('',dxx,kbVodorovny2,1) + kbPravy2Dolny2;
       zapis_riadok (f,s,true);

       sta_FPLC^.disp_stad_(stac);
       dispose(stac);
      {$ENDIF}
     end;

 procedure OStaOPL.statistika_SRLP(var f: text; date: TDate);
     begin
       zapis_odstavec (f,NETadr_wan(NETaddress),true);
       zapis_hlavicku_pracoviska (f,date,cfg_HEADER_MACC,'',NETadr_lan(NETaddress),dsSRLP);
       statistika_letov_letisk (f,date);
       statistika_letov_sumarna (f,date);
       zapis_odstavec (f,'',false);
     end;

{$ENDIF}
