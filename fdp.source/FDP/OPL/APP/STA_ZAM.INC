{ -----------------------------------------
  lokalne fcie : zapis a nacitanie suborov
  -----------------------------------------
}
 procedure codeDB_ZAM_sta (sta: PZAM_sta; buff: PDB_buff; desc: PDB_head); far;
     var   s,t: string;
     begin
       s:= '';
       add_s (@sta^.let, sizeof(sta^.let), s,t);
       add_s (@sta^.sta, sizeof(sta^.sta), s,t);
       str_toDBstr (s,buff^[db_sta_ZAM_sta]);
     end;

 procedure decodeDB_ZAM_sta (buff: PDB_buff; sta: PZAM_sta; desc: PDB_head); far;
     var   s  : string;
           p  : pchars;
     begin
       fillchar(sta^,sizeof(sta^),0);

       s:= DBstr_to_str (buff^[db_sta_ZAM_sta]);
       p:= @s[1];
       get_s(p, @sta^.let, sizeof(sta^.let));
       get_s(p, @sta^.sta, sizeof(sta^.sta));
     end;

 function  codeDBkey_ZAM_sta (sta: PZAM_sta): string; far;
    begin
      codeDBkey_ZAM_sta:= sta^.key
    end;


{ -----------------------------------------
  externe fcie : zapis, info
  -----------------------------------------
}
 procedure save_STA_ZAM (ZAM: PZAM); far;
     var   date: TDate;
     begin
       init_date (date, ZAM^.zac.rok,ZAM^.zac.mes,ZAM^.zac.den);
       if sta_ZAM<>nil then sta_ZAM^.zapis_polozky(date,ZAM);
       if     (StatistikaAPP<>nil)
          and  StatistikaAPP^.aktualizacia_uzatvorenej_statistiky(date)
          then StatistikaAPP^.aktualizuj_uzatvorenu_statistiku(date);
     end;

 procedure info_STA_ZAM; far;
     begin
       if StatistikaAPP<>nil then StatistikaAPP^.zobraz_priebeznu_statistiku_(true);
     end;


{ -----------------------------------------
  instancia objektu pre ZAM :
  -----------------------------------------
}
 constructor OStatistikaZAM.Init(_cfg_FN: string);
       begin
         inherited Init(extZAM,

                        sizeof(TZAM_sta), nil,nil,
                        @codeDB_ZAM_sta,  @decodeDB_ZAM_sta,@codeDBkey_ZAM_sta,db_riadkov_ZAM_sta,

                        sizeof(TZAMs_staDen), nil,nil,nil,nil,
                        0,

                        _cfg_FN
                       );

         prepocitavat_pri_uzatvarani:= false;
         {$IFDEF STATISTIKA_SERVER}
          p_save_STA_ZAM := @save_STA_ZAM;
         {$ENDIF}
         p_info_STA_ZAM := @info_STA_ZAM;
       end;


{ -----------------------------------------
  Naplnenie udajov statistiky
  -----------------------------------------
}
 procedure OStatistikaZAM.initialize_sta (data: pointer; _sta: PStaFDP);
    var    ZAM : PZAM;
           sta : PZAM_sta;
           is  : bool;
           i,ind : int;
    begin
      ZAM:= PZAM(data);
      sta:= PZAM_sta(_sta);
      fillchar(sta^,sizeof(TZAM_sta),0);

      sta^.key:= codekey_ZAM(ZAM);
      sta^.let:= ZAM^.kod;
      sta^.sta.planovanych:= ZAM^.planov;
      if _is_stat (ZAM^.stat,delchar(cnst_stat_actived,[cnst_cnl]),false) then
         sta^.sta.realizovanych:= ZAM^.letov;
    end;


{ -----------------------------------
  denny zaznam spocitanych poloziek
  -----------------------------------
}
 procedure _aktualizacia_zaznamu_ZAM_sta (sta: PZAM_sta; stad: PZAMs_staDen; pridaj: int);
     var   i,ind: int;
     begin
       ind:= _LKmind(sta^.let);
       if ind<0 then Exit;

       with stad^.zam[ind] do
         begin
           planov:= N(planov + sta^.sta.planovanych*pridaj);
           letov:=  N(letov + sta^.sta.realizovanych*pridaj);
           riadenych:= letov;
         end;
     end;

 procedure OStatistikaZAM.aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool);
     begin
       if (not reset) and (_stap<>nil) then _aktualizacia_zaznamu_ZAM_sta (_stap,_stad, -1);
       _aktualizacia_zaznamu_ZAM_sta (_sta,_stad, +1)
     end;

 procedure OStatistikaZAM.aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs);
     var   stad1,stad2: PZAMs_staDen;
     begin
       stad1:= PZAMs_staDen(_sta_suma);
       stad2:= PZAMs_staDen(_sta_ciastocny);

       inc_FPLM_letov(stad1^.zam, stad2^.zam);
     end;

