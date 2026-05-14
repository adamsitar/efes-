{ -----------------------------------------
  lokalne fcie : alokovanie a kodovanie
  -----------------------------------------
}
 procedure new_FPLM_sta(sta1, sta2: PFPLM_sta); far;
     begin
       FillChar(sta2^,sizeof(sta2^),0);
       if sta1<>nil then
          begin
            sta2^:= sta1^;
            sta2^.r_tsa:= strnew(sta1^.r_tsa)
          end
     end;

 procedure disp_FPLM_sta(sta: PFPLM_sta); far;
     begin
       strdispose(sta^.r_tsa)
     end;


 procedure new_FPLMs_stad(sta1, sta2: PFPLMs_staDen); far;
     var   i: int;
     begin
       FillChar(sta2^,sizeof(sta2^),0);
       if sta1<>nil then
          begin
            sta2^:= sta1^;
            for i:= 0 to max_AIRBASE do sta2^.r_tsa[i]:= strnew(sta1^.r_tsa[i])
          end
     end;

 procedure disp_FPLMs_stad(stad: PFPLMs_staDen); far;
     var   i: int;
     begin
       for i:= 0 to max_AIRBASE do strdispose(stad^.r_tsa[i])
     end;


{ -----------------------------------------
  lokalne fcie : zapis a nacitanie suborov
  -----------------------------------------
}
 procedure codeDB_FPLM_sta (sta: PFPLM_sta; buff: PDB_buff; desc: PDB_head); far;
     var   s,t: string;
     begin
       s:= '';
       add_s (@sta^.par, sizeof(sta^.par), s,t);
       add_s (@sta^.plan,sizeof(sta^.plan), s,t);
       add_s (@sta^.lsrlp, sizeof(sta^.lsrlp),  s,t);
       str_toDBstr (s,buff^[db_sta_FPLM_sta]);

       str_toDBstr (strpas(sta^.r_tsa),buff^[db_sta_FPLM_tsa]);
     end;

 procedure decodeDB_FPLM_sta (buff: PDB_buff; sta: PFPLM_sta; desc: PDB_head); far;
     var   s  : string;
           p  : pchars;
     begin
       fillchar(sta^,sizeof(sta^),0);

       s:= DBstr_to_str (buff^[db_sta_FPLM_sta]);
       p:= @s[1];
       get_s(p, @sta^.par, sizeof(sta^.par));
       get_s(p, @sta^.plan,sizeof(sta^.plan));
       get_s(p, @sta^.lsrlp, sizeof(sta^.lsrlp));

       sta^.r_tsa:= strpasnew(DBstr_to_str(buff^[db_sta_FPLM_tsa]));
     end;

 function  codeDBkey_FPLM_sta (sta: PFPLM_sta): string; far;
    begin
      codeDBkey_FPLM_sta:= sta^.plan.key
    end;


 procedure zapis_FPLMs_sta (fn: string; stad: PFPLMs_staDen); far;
     var   f   : file;
           len,res : word;
           i : int;
     begin
       assign(f,fn); rewrite(f,1);
       BlockWrite(f,stad^.par,sizeof(stad^.par),res);

       BlockWrite(f,stad^.mil,sizeof(stad^.mil),res);
       BlockWrite(f,stad^.mil_ifr,sizeof(stad^.mil_ifr),res);
       BlockWrite(f,stad^.mil_fl,sizeof(stad^.mil_fl),res);
       BlockWrite(f,stad^.ine,sizeof(stad^.ine),res);

       BlockWrite(f,stad^.zam,sizeof(stad^.zam),res);

       BlockWrite(f,stad^.tsa,sizeof(stad^.tsa),res);
       {BlockWrite(f,stad^.prs[0],strlen(stad^.prs),res);}
       {BlockWrite(f,stad^.prs.pocet,sizeof(stad^.prs.pocet),res);
       BlockWrite(f,stad^.prs.tsa^,stad^.prs.pocet*sizeof(TTSA_lety_),res);}
       for i:= 0 to max_AIRBASE do
         begin
           len:= strlen(stad^.r_tsa[i]);
           BlockWrite(f,len,sizeof(len),res);
           BlockWrite(f,stad^.r_tsa[i][0],len,res)
         end;

       close(f)
     end;

 function nacitanieFPLMs_sta (fn: string; stad: PFPLMs_staDen): bool; far;
    var   f : file;
          len,res : word;
          i : int;
    begin
      fillchar(stad^,sizeof(stad^),0);
      nacitanieFPLMs_sta:= false;
      len:=   _filesize(fn)
            - (  sizeof(stad^.par)
               + sizeof(stad^.mil) + sizeof(stad^.mil_ifr) + sizeof(stad^.mil_fl)
               + sizeof(stad^.ine)
               + sizeof(stad^.zam)
               + sizeof(stad^.tsa)
              );
      if len < 0 then Exit;

      nacitanieFPLMs_sta:= true;
      assign(f,fn); reset(f,1);
      BlockRead(f,stad^.par,sizeof(stad^.par),res);

      BlockRead(f,stad^.mil,sizeof(stad^.mil),res);
      BlockRead(f,stad^.mil_ifr,sizeof(stad^.mil_ifr),res);
      BlockRead(f,stad^.mil_fl,sizeof(stad^.mil_fl),res);
      BlockRead(f,stad^.ine,sizeof(stad^.ine),res);

      BlockRead(f,stad^.zam,sizeof(stad^.zam),res);

      BlockRead(f,stad^.tsa,sizeof(stad^.tsa),res);
      {stad^.tsa:= StrAlloc (len);
      if stad^.tsa<>nil then BlockRead(f,stad^.tsa[0],len,res);}
      {BlockRead(f,stad^.tsa.pocet,sizeof(stad^.tsa.pocet),res);
      if AllocMem(pointer(stad^.tsa.tsa),stad^.tsa.pocet*sizeof(TTSA_lety_)) then
         BlockRead(f,stad^.tsa.tsa^,stad^.tsa.pocet*sizeof(TTSA_lety_),res);}
      for i:= 0 to max_AIRBASE do
        begin
          BlockRead(f,len,sizeof(len),res);
          stad^.r_tsa[i]:= StrAlloc(len);
          if stad^.r_tsa[i]<>nil then BlockRead(f,stad^.r_tsa[i][0],len,res)
          else Seek(f,FilePos(f)+len)
        end;

      close(f)
    end;


{ -----------------------------------------
  externe fcie : zapis, info
  -----------------------------------------
}
 procedure save_STA_FPLM (FPL: PDmFPL); far;
     begin
       if is_KRL(FPL) then Exit;
       if sta_FPLM<>nil then sta_FPLM^.zapis_polozky(FPL^.date,FPL);
     end;

 procedure info_STA_FPLM; far;
     begin
       {if sta_FPLM<>nil then sta_FPLM^.zobraz_priebeznu_statistiku_za_(true);}
       if StatistikaAPP<>nil then StatistikaAPP^.zobraz_priebeznu_statistiku_(true);
     end;


{ -----------------------------------------
  instancia objektu pre FPLM :
  -----------------------------------------
}
 constructor OStatistikaFPLM.Init(_cfg_FN: string);
       begin
         inherited Init(ext_mFPL,

                        sizeof(TFPLM_sta), @new_FPLM_sta,@disp_FPLM_sta,
                        @codeDB_FPLM_sta,  @decodeDB_FPLM_sta,@codeDBkey_FPLM_sta,db_riadkov_FPLM_sta,

                        sizeof(TFPLMs_staDen), @new_FPLMs_stad,@disp_FPLMs_stad, @zapis_FPLMs_sta,@nacitanieFPLMs_sta,
                        {poloziek_FPLM}0,

                        _cfg_FN
                       );

         prepocitavat_pri_uzatvarani:= false;
         {$IFDEF STATISTIKA_SERVER}
          p_save_STA_FPLM := @save_STA_FPLM;
         {$ENDIF}
         p_info_STA_FPLM := @info_STA_FPLM;
       end;

 procedure OStatistikaFPLM.nacitaj_cfg(_cfg_FN: string);
     begin
       inherited nacitaj_cfg(_cfg_FN);
       read_FL_XX (_cfg_FN, cfg_FPLM_FL_,FPLM_FL,FPLM_FL_);
       read_FL_XX (_cfg_FN, cfg_FPLo_FL_,FPLo_FL,FPLo_FL_);
     end;

 function  OStatistikaFPLM.najdi_najdlhsi_nazov: byte;
    var    dlz: byte;
    begin
      dlz:= 0;
      {dlz:= maximum(0,   length(sta_nazov_polozky (cfg_LM, '','', 0)));
      dlz:= maximum(dlz, length(sta_nazov_polozky (cfg_LM_FL, cfg_FPLM_FL,FPLM_FL_, 0)));
      dlz:= maximum(dlz, length(sta_nazov_polozky (cfg_LO, '','', 0)));
      dlz:= maximum(dlz, length(sta_nazov_polozky (cfg_LO_FL, cfg_FPLo_FL,FPLo_FL_, 0)));}
      najdi_najdlhsi_nazov:= dlz
    end;


{ -----------------------------------------
  Naplnenie udajov statistiky
  -----------------------------------------
}
 procedure OStatistikaFPLM.initialize_sta (data: pointer; _sta: PStaFDP);
    var    FPL : PDmFPL;
           sta : PFPLM_sta;
           is  : bool;
           i,ind : int;
           Bi : TsBod;
    begin
      FPL:= PDmFPL(data);
      sta:= PFPLM_sta(_sta);
      fillchar(sta^,sizeof(TFPLM_sta),0);

     { urcenie verifikacnych parametrov
     }
      sta^.par.flm:= FPLM_FL;
      sta^.par.flo:= FPLO_FL;

     { urcenie identifikacnych udajov
     }
      sta^.plan.key:= codekey_FPLM(FPL);
      sta^.plan.dep:= FPL^.start.kod;
      sta^.plan.src:= FPL^.let;

     { urcenie parametrov planu
     }
      sta^.plan.tsa:= _let_do_TSA (FPL);
      sta^.plan.rte:= not sta^.plan.tsa;

      if sta^.plan.rte then
         begin
         { urcenie poctu ifr a vojenskych letov pre tratove lety
         } sta^.plan.rte:= true;
           sta^.plan.mil:= is_mFPL(FPL);
           sta^.plan.ifr:= not is_VFR_FPLM(FPL);
         end;

      sta^.plan.let:= _is_stat (FPL^.stat,delchar(cnst_stat_actived,[cnst_cnl]),false);

      is:= FPL^.trat_<>nil;
      if not is then decode_trat_FPLM(FPL, FPL^.trat_,FPL^.bodov, false,true,false);
      with FPL^ do
        begin
          sta^.plan.fl:= maximum(get_altM(vys_,vys), get_altM(vys2_,vys2));
          for i:= 0 to bodov-1 do sta^.plan.fl:= maximum(sta^.plan.fl,get_altM(trat_^[i].vys_,trat_^[i].vys))
        end;

     { urcenie riadenia letu, tratove i TSA
     }
      ind:= _LKmind(sta^.plan.dep);
      sta^.lsrlp[max_AIRBASE].riadeny:= sta^.plan.let;
      for i:= 0 to poc_AIRBASE-1 do
        begin
          LK_m^.read(i,Bi);
          sta^.lsrlp[i].riadeny:=  {(ind<>i)  medzi riadene sa pocitaju i vlastne }
                                   sta^.plan.let and _prelet_cez_LSRLP (FPL,Bi.kod);
        end;

      if not is then zrus_trat_FPLM (FPL^.trat_,FPL^.bodov);

     { urcenie priestorov, kde ma planovanu cinnost
     }
      sta^.r_tsa:= strpasnew(_cinnost_v_priestore(FPL));
    end;

 procedure OStatistikaFPLM.initialize_stad (_stad: PStadFDPs);
     var   stad: PFPLMs_staDen;
     begin
       stad:= PFPLMs_staDen(_stad);
       fillchar(stad^,stad_size,0);
       stad^.par.flm:= FPLM_FL;
       stad^.par.flo:= FPLO_FL
     end;


{ --------------------
  zapis novej polozky
  --------------------
}
 function  OStatistikaFPLM.zapisat_polozku (date: TDate; data: pointer): bool;
    var    FPL : PDmFPL;
    begin
      FPL:= PDmFPL(data);
      zapisat_polozku:= _item_18_(FPL^.pozn,rmk_RMK,1) <> rmk_TEST;
    end;


{ -----------------------------------
  denny zaznam spocitanych poloziek
  -----------------------------------
}
{ Pomocne fcie pre aktualizacia udajov sledovanych typov
}
 procedure _aktualizacia_typu_letu (var suma: TFPLM_letov; dep: string; plan,let: bool; riadeny: PFPLM_lsrlp; pridaj: int);
     var   i,ind: int;
     begin
       if not plan then Exit;

      { hodnoty pre SRLP
      }
       ind:= max_AIRBASE;
       inc(suma[ind].planov,pridaj);
       if let then inc(suma[ind].letov,pridaj);
       if (riadeny<>nil) and (riadeny^[ind].riadeny) then inc(suma[ind].riadenych,pridaj);

      { hodnoty pre LSRLP
      }
       ind:= _LKmind(dep);
       if ind>-1 then
          begin
            inc(suma[ind].planov,pridaj);
            if let then inc(suma[ind].letov,pridaj);
          end;

       if (riadeny<>nil) then
          for i:= 0 to poc_AIRBASE-1 do
            if riadeny^[i].riadeny then inc(suma[i].riadenych,pridaj);
     end;

 procedure _aktualizacia_sledovanych_typov_letov (_sta: PStaFDP; _stad: PStadFDPs; pridaj: int);
     var   sta  : PFPLM_sta;
           stad : PFPLMs_staDen;
     begin
       sta := PFPLM_sta(_sta);
       stad:= PFPLMs_staDen(_stad);

       stad^.par:= sta^.par;
       with sta^ do
         begin
           _aktualizacia_typu_letu (stad^.mil,     plan.dep, plan.rte and plan.mil,              plan.let, @lsrlp, pridaj);
           _aktualizacia_typu_letu (stad^.mil_ifr, plan.dep, plan.rte and plan.mil and plan.ifr, plan.let, @lsrlp, pridaj);
           _aktualizacia_typu_letu (stad^.mil_fl,  plan.dep, plan.rte and plan.mil and plan.ifr
                                                                      and (plan.fl>=par.flm),    plan.let, @lsrlp, pridaj);

           _aktualizacia_typu_letu (stad^.ine,     plan.dep, plan.rte and (not plan.mil),        plan.let, @lsrlp, pridaj);

          { verzia od roku 2000 pocita i s uvedenim udajov letov v TSA medzi riadene
          }
           _aktualizacia_typu_letu (stad^.tsa,     plan.dep, plan.tsa,                           plan.let, @lsrlp, pridaj);

           {_aktualizacia_typu_letu (stad^.zam,    plan.dep, plan.mil and (prs<>nil),            plan.let, nil,    pridaj);}
         end;
     end;

{ Pomocne fcie pre aktualizaciu udajov o planovanych priestoroch cinnosti
}
 function _zapis_pocet_letov_v_priestore (tsa: string; planov,letov: word): string;
    begin
      if (planov>0) or (letov>0) then tsa:= tsa+icao_NXT+cstr(planov,1)+','+cstr(letov,1) else tsa:= '';
      _zapis_pocet_letov_v_priestore:= tsa
    end;

 function _citaj_pocet_letov_v_priestore (kod: string; var tsa: string; var planov,letov: word): bool;
    begin
      tsa:= cut_(getstr(kod,1,[icao_NXT]));
      planov:= getint(kod,2,[icao_NXIT,icao_NXT,',']);
      letov:= getint(kod,3,[icao_NXIT,icao_NXT,',']);
      _citaj_pocet_letov_v_priestore:= tsa<>''
    end;

 procedure _aktualizacia_priestorov_cinnosti (_sta: PStaFDP; _stad: PStadFDPs; pridaj: int);
     var   sta   : PFPLM_sta;
           stad  : PFPLMs_staDen;
           i,ind : int;
           s,t,u : string;
           planov,letov: word;
     begin
       sta := PFPLM_sta(_sta);
       stad:= PFPLMs_staDen(_stad);

      { kazdy priestor uvedeny v trati planu letu je uvedeny sta.prs;
        preto sa vyhladaju v zazname stad pre letisko startu
        a aktalizuje (pricita alebo odcita)
      }
       ind:= _LKmind(sta^.plan.dep);
       if ind=-1 then Exit;

       for i:= 1 to GetPStrItems(sta^.r_tsa,[icao_NXIT]) do
         begin
           t:= getPstr(sta^.r_tsa,i,[icao_NXIT]);
           s:= _item_18_(stad^.r_tsa[ind],t,1);
           if s<>'' then _dec_18(stad^.r_tsa[ind],t);
           _citaj_pocet_letov_v_priestore (t+icao_NXT+s, u,planov,letov);
           planov:= N(planov+pridaj);
           if sta^.plan.let then letov:= N(letov+pridaj);
           s:= _zapis_pocet_letov_v_priestore (t, planov,letov);
           _inc_18(stad^.r_tsa[ind],s,1);
         end;
     end;


{ Fcia pre naplnenie sledovanych udajov planu
}
 procedure OStatistikaFPLM.aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool);
     begin
       if (not reset) and (_stap<>nil) then
          begin
            _aktualizacia_sledovanych_typov_letov (_stap,_stad,-1);
            _aktualizacia_priestorov_cinnosti (_stap,_stad,-1);
          end;
       _aktualizacia_sledovanych_typov_letov (_sta,_stad,+1);
       _aktualizacia_priestorov_cinnosti (_sta,_stad,+1);
     end;


 function  _inc_TSA_letov (var tsa1: pchar; tsa2: pchar): pchar;
     var   i,j : int;
           si,sj, ti,tj : string;
           pi,pj, li,lj: word;
     begin
      { kazdy priestor uvedeny v trati planu letu je uvedeny sta.prs;
        preto sa vyhladaju v zazname stad pre letisko startu
        a aktalizuje (pricita alebo odcita)
      }
       for i:= 1 to GetPStrItems(tsa2,[icao_NXIT]) do
         begin
           si:= getPstr(tsa2,i,[icao_NXIT]);
           _citaj_pocet_letov_v_priestore (si, ti,pi,li);
           sj:= _item_18_(tsa1,ti,1);
           if sj<>'' then
              begin
                _dec_18(tsa1,ti);
                _citaj_pocet_letov_v_priestore (ti+icao_NXT+sj, tj,pj,lj);
                inc(pi,pj); inc(li,lj)
              end;
           si:= _zapis_pocet_letov_v_priestore (ti,pi,li);
           tsa1:= StrNPCopy(tsa1,icao_NXIT+si,true,true);
         end;
       _inc_TSA_letov:= tsa1
     end;

 procedure inc_TSA_letov(var l1: TTSA_letov; l2: TTSA_letov);
     var   i : int;
     begin
       for i:= 0 to max_AIRBASE do _inc_TSA_letov(l1[i],l2[i]);
     end;


 procedure OStatistikaFPLM.aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs);
     var   stad1,stad2: PFPLMs_staDen;
     begin
       stad1:= PFPLMs_staDen(_sta_suma);
       stad2:= PFPLMs_staDen(_sta_ciastocny);

       inc_FPLM_letov(stad1^.mil,     stad2^.mil);
       inc_FPLM_letov(stad1^.mil_ifr, stad2^.mil_ifr);
       inc_FPLM_letov(stad1^.mil_fl,  stad2^.mil_fl);
       inc_FPLM_letov(stad1^.ine,     stad2^.ine);
       inc_FPLM_letov(stad1^.zam,     stad2^.zam);
       inc_FPLM_letov(stad1^.tsa,     stad2^.tsa);
       inc_TSA_letov (stad1^.r_tsa,   stad2^.r_tsa);
     end;


{ ------------------------------------
  pracovny subor spocitanych poloziek
  ------------------------------------
}
{ function stadFPLMs_to_str(_stad: PFPLMs_staDen): string;
    var   s : string;
          i : int;
    begin
      Move(sta,s[1],sizeof(sta));
      s[0]:= chr(sizeof(sta));
      statostr:= s
    end;   }


 function  OStatistikaFPLM.nazov_polozky (polozka: int): string;
    begin
      {case polozka of
       1  : nazov_polozky:= sta_nazov_polozky (cfg_LC, '','', false);
       2  : nazov_polozky:= sta_nazov_polozky (cfg_LC_FL, cfg_FL_LC,FL_LC_, false)
       else nazov_polozky:= ''
      end
      }
    end;

 function  OStatistikaFPLM.hodnoty_polozky_za_den (polozka: int; _stad: PFPLMs_staDen): string;
    begin
      hodnoty_polozky_za_den:= ''
    end;


{ ------------------------------------
  prepocty
  ------------------------------------
  Ruzomberok : Levoca
  182          32
}
 function OStatistikaFPLM.zmenene_parametre_statistiky(_stad: PStadFDPs): bool;
    begin
      zmenene_parametre_statistiky:=    (PFPLMs_staDen(_stad)^.par.flm<>FPLM_FL)
                                     or (PFPLMs_staDen(_stad)^.par.flo<>FPLO_FL)
    end;
