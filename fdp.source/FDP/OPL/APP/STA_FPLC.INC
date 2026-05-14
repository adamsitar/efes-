{ -----------------------------------------
  lokalne fcie : kodovanie pre zapis do DB
  -----------------------------------------
}
 procedure codeDB_FPLC_sta (sta: PFPLC_sta; buff: PDB_buff; desc: PDB_head); far;
     var   s,t: string;
     begin
       s:= '';
       add_s (@sta^.sta,sizeof(sta^.sta), s,t);
       add_s (@sta^.fl,sizeof(sta^.fl),   s,t);
       add_s (@sta^.vfr,sizeof(sta^.vfr), s,t);
       str_toDBstr (s,buff^[db_sta_FPLC_sta]);
     end;

 procedure decodeDB_FPLC_sta (buff: PDB_buff; sta: PFPLC_sta; desc: PDB_head); far;
     var   s  : string;
           v_ : char;
           p  : pchars;
     begin
       fillchar(sta^,sizeof(sta^),0);

       s:= DBstr_to_str (buff^[db_sta_FPLC_sta]);
       p:= @s[1];
       get_s(p, @sta^.sta,sizeof(sta^.sta));
       get_s(p, @sta^.fl,sizeof(sta^.fl));
       get_s(p, @sta^.vfr,sizeof(sta^.vfr));
       p:= @s[1];
     end;

 function  codeDBkey_FPLC_sta (sta: PFPLC_sta): string; far;
    begin
      codeDBkey_FPLC_sta:= sta^.key
    end;


{ -----------------------------------------
  externe fcie : zapis, info
  -----------------------------------------
}
 procedure save_STA_FPLC (FPL: PDcFPL); far;
     begin
       if sta_FPLC<>nil then sta_FPLC^.zapis_polozky(FPL^.date,FPL);
     end;

 procedure info_STA_FPLC; far;
     begin
       {if sta_FPLC<>nil then sta_FPLC^.zobraz_priebeznu_statistiku_za_(true);}
     end;


{ -----------------------------------------
  instancia objektu pre FPLC :
  -----------------------------------------
}
 constructor OStatistikaFPLC.Init(_cfg_FN: string);
       begin
         inherited Init(ext_cFPL,

                        sizeof(TFPLC_sta), nil,nil,
                        @codeDB_FPLC_sta,@decodeDB_FPLC_sta,@codeDBkey_FPLC_sta,db_riadkov_FPLC_sta,

                        sizeof(TFPLCs_staDen), nil,nil, nil,nil,
                        0{poloziek_FPLC},

                        _cfg_FN
                       );

         prepocitavat_pri_uzatvarani:= false;
         {$IFDEF STATISTIKA_SERVER}
           p_save_STA_FPLC := @save_STA_FPLC;
         {$ENDIF}
         p_info_STA_FPLC := @info_STA_FPLC;
       end;


 procedure OStatistikaFPLC.nacitaj_cfg(_cfg_FN: string);
     begin
       inherited nacitaj_cfg(_cfg_FN);
       read_FL_XX(_cfg_FN, cfg_FPLC_FL_,FPLC_FL,FPLC_FL_);
     end;

 function  OStatistikaFPLC.najdi_najdlhsi_nazov: byte;
    var    dlz: byte;
    begin
      dlz:= maximum(0, length(sta_nazov_polozky (cfg_FPLC_FL, '','', 0)));
      najdi_najdlhsi_nazov:= dlz
    end;


 procedure OStatistikaFPLC.initialize_sta (data: pointer; _sta: PStaFDP);
    var    FPL : PDcFPL;
           sta : PFPLC_sta;
           i   : int;
    begin
      fillchar(_sta^,sta_size,0);
      FPL:= PDcFPL(data);
      sta:= PFPLC_sta(_sta);
      sta^.key:= codekey_FPLC(FPL);
      sta^.sta.planovany:= true;
      sta^.sta.realizovany:= FPL^.stt<>hd_CNL;
      sta^.vfr:= FPL^._8a=VFR_let; { zatial jednoduche kriterium }
      sta^.fl:= maximum(FPL^.vys,FPL^.vys1);
      for i:= 0 to FPL^.bodov-1 do sta^.fl:= maximum(sta^.fl,FPL^.trat[i].vys);
      sta^.fl:= get_altM(vysOB,sta^.fl);
     end;


 procedure OStatistikaFPLC.initialize_stad (_stad: PStadFDPs);
     begin
       fillchar(_stad^,stad_size,0);
       PFPLCs_staDen(_stad)^.fl_:= FPLC_FL
     end;


{ --------------------
  zapis novej polozky
  --------------------
}
 function  OStatistikaFPLC.zapisat_polozku (date: TDate; data: pointer): bool;
    var    FPL : PDcFPL;
    begin
      FPL:= PDcFPL(data);
      zapisat_polozku:= not (   (STA_TEST and ((pos(rmk_TEST,FPL^.idn)=1) or (FPL^.idn=hd_ULP)))
                             or ((pos(rmk_TEST,FPL^.inf)=1) or (FPL^.inf=hd_ULP))
                            )
    end;


{ -----------------------------------
  denny zaznam spocitanych poloziek
  -----------------------------------
}
 procedure _aktualizacia_zaznamu_FPLC_sta (sta: PFPLC_sta; stad: PFPLCs_staDen; pridaj: int);
     begin
       if sta^.sta.planovany then
          begin
            inc(stad^.sta.planovanych,pridaj);
            if sta^.vfr then inc(stad^.vfr,pridaj);
            if sta^.sta.realizovany then
               begin
                 inc(stad^.sta.realizovanych,pridaj);
                 if sta^.fl >= FPLC_FL then inc(stad^.fl,pridaj)
               end;
          end;
       stad^.fl_:= FPLC_FL
     end;

 procedure OStatistikaFPLC.aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool);
     var   sta  : PFPLC_sta;
           stap : PFPLC_sta;
           stad : PFPLCs_staDen;

     begin
       if (not reset) and (_stap<>nil) then
          begin
            _aktualizacia_zaznamu_FPLC_sta (_stap,_stad,-1)
          end;
       _aktualizacia_zaznamu_FPLC_sta (_sta,_stad,+1);
     end;


 procedure OStatistikaFPLC.aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny: PStadFDPs);
     var   stad1,stad2: PFPLCs_staDen;
     begin
       stad1:= PFPLCs_staDen(_sta_suma);
       stad2:= PFPLCs_staDen(_sta_ciastocny);

       inc(stad1^.sta.planovanych,stad2^.sta.planovanych);
       inc(stad1^.sta.realizovanych,stad2^.sta.realizovanych);

       inc(stad1^.vfr,stad2^.vfr);
       inc(stad1^.fl ,stad2^.fl);
     end;


{ ------------------------------------
  prepocty
  ------------------------------------
  Ruzomberok : Levoca
  182          32
}
 function OStatistikaFPLC.zmenene_parametre_statistiky (_stad : PStadFDPs): bool;
    begin
      zmenene_parametre_statistiky:= PFPLCs_staDen(_stad)^.fl_<>FPLC_FL
    end;


{ ------------------------------------
  pracovny subor spocitanych poloziek
  ------------------------------------
}
{ function stadFPLCs_to_str(_stad: PStadFDPs): string;
    var   s : string;
          i : int;
    begin
      Move(sta,s[1],sizeof(sta));
      s[0]:= chr(sizeof(sta));
      statostr:= s
    end;


 function  OStatistikaFPLC.nazov_polozky (polozka: int): string;
    begin
      case polozka of
       1  : nazov_polozky:= sta_nazov_polozky (cfg_LC, '','', false);
       2  : nazov_polozky:= sta_nazov_polozky (cfg_LC_FL, cfg_FPLC_FL,FPLC_FL_, false)
       else nazov_polozky:= ''
      end
    end;

 function  OStatistikaFPLC.hodnoty_polozky_za_den (polozka: int; _stad: PStadFDPs): string;
    begin
      hodnoty_polozky_za_den:= ''
    end;
}

 function  OStatistikaFPLC.zapis_hlavicku_za_ (var fT: text; p_stad: PStadFDPs; date: TDate; externy: bool): bool;
    begin
      zapis_hlavicku_za_:= true
    end;

 function  OStatistikaFPLC.zapis_riadok_za_ (var fT: text; riadok: int; p_stad: PStadFDPs; date: TDate; externy: bool): bool;
    begin
      zapis_riadok_za_:= false
      {writeln(cfg_LC, '','', false);
      (cfg_LC_FL, cfg_FPLC_FL,FPLC_FL_, false)}
    end;

