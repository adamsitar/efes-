{ -------------------
  Statistika LSRLP
  -------------------
}
 const  dsdx      = 3;

        dsLh_l    = 27;
        dsLi_l    = 13;
        pocLi_l   =  3;
        dsLSRLP_l =  1 + 1+dsLh_l + (1+dsLi_l)*pocLi_l + 1;

        { do roku 2000 :
        dsLh_c    = 41;
        dsLi_c    = 13;
        dsLSRLP_c =  1 + 1+dsLh_c + 1+dsLi_c + 1;
        }
        dsLi_c    = dsLi_l;
        dsLh_c    = dsLSRLP_l - dsLi_l - dsdx - 1;
        {dsLSRLP_c = dsLSRLP_l;}


 procedure OStaOPL.statistika_letov (var f: text; date: TDate; let: int);
     var   dx,dxx, i,l : int;
           s,nl : string;
           {$IFDEF FPL0}
            stam: PFPLMs_staDen;
            stac: PFPLCs_staDen;
           {$ENDIF}
           {$IFDEF ZAM}
            staz: PZAMs_staDen;
           {$ENDIF}
     begin
       dx:= dsLSRLP_l-dsdx;
       l:= let;
       if l<0 then Exit;

      {$IFDEF ZAM}
        new(staz);
        sta_ZAM^.nacitanie_sumarneho_zaznamu (date,staz);
      {$ENDIF}

      {$IFDEF FPL0}
      { -------------------------------------
        Statistika letov podla typu
        -------------------------------------
      }
       new(stam);
       sta_FPLM^.nacitanie_sumarneho_zaznamu (date,stam);

       {$IFDEF ZAM}
        stam^.zam:= staz^.zam;
       {$ENDIF}

       zapis_riadok (f,  kbLavy2Horny2 + inschar('',dx,kbVodorovny2,1) + kbPravy2Horny2, true);
       zapis_riadok (f,  kbZvisly2 + _tit(cfg_REALIZED_FLIGHTS_A,dx) + kbZvisly2, true);

       s:=    kbZvisly2   + inschar('',dsLh_l,' ',1)
           +  kbLavyHorny + inschar('',dsLi_l,kbVodorovny,1);
       for i:= 1 to pocLi_l-1 do s:= s + kbVodorovnyDole + inschar('',dsLi_l,kbVodorovny,1);
       s:= s + kbZvisly2Dolava;
       zapis_riadok (f,s,true);

       zapis_riadok (f,  kbZvisly2 + inschar('',dsLh_l,' ',1) {_tit(cfg_FLIGHT_TYPE_A,dsLh_l)}
                       + kbZvisly + _tit(cfg_PLANNED,dsLi_l)
                       + kbZvisly + _tit(cfg_REALIZED,dsLi_l)
                       + kbZvisly + _tit(cfg_CONTROLLED,dsLi_l)
                       + kbZvisly2,
                     true
                    );

       nl:= kbZvisly2Doprava + inschar('',dsLh_l,kbVodorovny,1);
       for i:= 1 to pocLi_l do nl:= nl + kbKriz + inschar('',dsLi_l,kbVodorovny,1);
       nl:= nl + kbZvisly2Dolava;
       zapis_riadok (f,nl,true);

       with stam^ do
         begin
           zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLM_VFR_A,dsLh_l)
                           + kbZvisly  + _cis(mil[l].planov    - mil_ifr[l].planov,dsLi_l)
                           + kbZvisly  + _cis(mil[l].letov     - mil_ifr[l].letov,dsLi_l)
                           + kbZvisly  + _cis(mil[l].riadenych - mil_ifr[l].riadenych,dsLi_l)
                           + kbZvisly2,
                         true
                        );
           zapis_riadok (f,nl,true);

           zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLM_IFR_A,dsLh_l)
                           + kbZvisly  + _cis(mil_ifr[l].planov,dsLi_l)
                           + kbZvisly  + _cis(mil_ifr[l].letov,dsLi_l)
                           + kbZvisly  + _cis(mil_ifr[l].riadenych,dsLi_l)
                           + kbZvisly2,
                         true
                        );
           zapis_riadok (f,nl,true);

           zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLM_FL_A,dsLh_l)
                           + kbZvisly  + _cis(mil_fl[l].planov,dsLi_l)
                           + kbZvisly  + _cis(mil_fl[l].letov,dsLi_l)
                           + kbZvisly  + _cis(mil_fl[l].riadenych,dsLi_l)
                           + kbZvisly2,
                         true
                        );
           zapis_riadok (f,nl,true);

           zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLM_TSA_A,dsLh_l)
                           + kbZvisly  + _cis(tsa[l].planov,dsLi_l)
                           + kbZvisly  + _cis(tsa[l].letov,dsLi_l)
                           + kbZvisly  + _cis(tsa[l].riadenych,dsLi_l)
                           + kbZvisly2,
                         true
                        );
           zapis_riadok (f,nl,true);

           zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLM_ZAM_A,dsLh_l)
                           + kbZvisly  + _cis(zam[l].planov,dsLi_l)
                           + kbZvisly  + _cis(zam[l].letov,dsLi_l)
                          { v nasledujucej polozke by malo byt spravne riadenych,
                            ale az do verzie v roku 2000 sa tato hodnota nenaplnala
                          }
                           + kbZvisly  + _cis(zam[l].{riadenych}letov,dsLi_l)
                           + kbZvisly2,
                         true
                        );
           zapis_riadok (f,nl,true);

           zapis_riadok (f,  kbZvisly2 + _tit(cfg_FPLO_A,dsLh_l)
                           + kbZvisly  + _cis(ine[l].planov,dsLi_l)
                           + kbZvisly  + _cis(ine[l].letov,dsLi_l)
                           + kbZvisly  + _cis(ine[l].riadenych,dsLi_l)
                           + kbZvisly2,
                         true
                        );
         end;

       s:= kbLavy2Dolny2 + inschar('',dsLh_l,kbVodorovny2,1);
       for i:= 1 to pocLi_l do s:= s + kbVodorovny2Hore + inschar('',dsLi_l,kbVodorovny2,1);
       s:= s + kbPravy2Dolny2;
       zapis_riadok (f,s,true);


      { -------------------------------------
        Celkovy pocet odriadenych letov
        -------------------------------------
      }
       zapis_riadok (f,    kbLavy2Horny2    + inschar('',dsLh_c,kbVodorovny2,1)
                         + kbVodorovny2Dole + inschar('',dsLi_c,kbVodorovny2,1)
                         + kbPravy2Horny2,
                         true
                    );
       zapis_riadok (f,    kbZvisly2 + _tit(cfg_TOTAL_FLIGHTS_A,dsLh_c)
                         + kbZvisly  + _cis(  stam^.mil[l].riadenych
                                            + stam^.ine[l].riadenych
                                            + stam^.tsa[l].riadenych
                                            + stam^.zam[l].letov,
                                            dsLi_c
                                          )
                         + kbZvisly2, true);
       zapis_riadok (f,    kbLavy2Dolny2     + inschar('',dsLh_c,kbVodorovny2,1)
                         + kbVodorovny2Hore  + inschar('',dsLi_c,kbVodorovny2,1)
                         + kbPravy2Dolny2,
                         true
                    );

       sta_FPLM^.disp_stad_(stam);
       dispose(stam);
      {$ENDIF}

      {$IFDEF ZAM}
       sta_ZAM^.disp_stad_(staz);
       dispose(staz);
      {$ENDIF}
     end;



 const  dsLh_r    = 10;
        dsLi_r    =  7;
        pocLi_r   =  3;
        dsLSRLP_r =  1 + 2*(1+dsLh_r + (1+dsLi_r)*pocLi_r) + 1;

        dsLh_g    = 21;
        dsLi_g    = 23;
        pocLi_g   =  2;
        dsLSRLP_g =  1 + 1+dsLh_g + (1+dsLi_g)*pocLi_g + 1;



 {$IFDEF FPL0}
  function  pocet_letov_v_priestore(kod: string; let: int; stam: PFPLMs_staDen): int;
     var    i,p,k: int;
            si,ti: string;
            pi,li: word;
     begin
       pocet_letov_v_priestore:= 0;
       {ind:= _LKmind(lsrlp);
       if ind<0 then Exit;}

       p:= 0;
       k:= GetPStrItems(stam^.r_tsa[let],[icao_NXIT]);
       i:= 1; while i<=k do
         begin
           si:= getPstr(stam^.r_tsa[let],i,[icao_NXIT]);
           _citaj_pocet_letov_v_priestore (si, ti,pi,li);
           if ti=kod then
              begin
                p:= li;
                break
              end;
           inc(i)
         end;
       pocet_letov_v_priestore:= p;
     end;
 {$ENDIF}


 {$IFDEF PRS}
 { vrati naplnenu cast riadku a true,
   ak hodnoty nenulove
 }
  function _riadok_l(tsa: string; let: int;
                     stap: PPRSs_staDen; {$IFDEF FPL0} stam: PFPLMs_staDen; {$ENDIF}
                     O: POStaAPP;
                     var riadok: string
                    ): bool;
     var   sum : TPRSi_sum;
           s   : string;
           i   : int;
     begin
       fillchar(sum,sizeof(sum),0);

       if (tsa<>'') then
          begin
          { vyhladanie zaznamu o vyuziti priestoru
          } if stap<>nil then
               begin
                 i:= 0; while (i<stap^.pocet) and (tsa<>stap^.stad[i]^.kod) do inc(i);
                 if (i<stap^.pocet) then sum:= stap^.stad[i]^.stai[let];
               end;

          { vyhladanie zaznamu o pocte letov v priestore
          } {$IFDEF FPL0}
              if stam<>nil then sum.letov_l:= pocet_letov_v_priestore(tsa,let,stam);
            {$ENDIF}

          end;

       if O<>nil then
          riadok:=   inschar(' '+tsa,dsLh_r,' ',1)
                   + kbZvisly + O^._cis(sum.planov_l,dsLi_r)
                   + kbZvisly + O^._cis(sum.vyuzitych_l,dsLi_r)
                   + kbZvisly + O^._cis(sum.letov_l,dsLi_r)
       else riadok:= '';

       _riadok_l:= (sum.planov_l>0) or (sum.letov_l>0);
     end;


 { vrati naplneny riadok konfigurovaneho priestoru
 }
  function _riadok_l_cfg (ind,let: int;
                          stap: PPRSs_staDen; {$IFDEF FPL0} stam: PFPLMs_staDen; {$ENDIF}
                          O: POStaAPP;
                          var riadok: string
                         ): bool;
     var   tsa: string;
     begin
       if ind<poc_PRS_nazvy then tsa:= PRS_nazvy^[ind] else tsa:= ''; { kvoli neparnemu poctu konf. prs }
       _riadok_l_cfg:= _riadok_l (tsa,let, stap,{$IFDEF FPL0} stam, {$ENDIF} O, riadok)
     end;


 { vrati naplneny riadok prveho a dalsich nenakonfigurovanych priestorov
 }
  function _riadok_l_sum(var ind: int; let: int;
                         stap: PPRSs_staDen; {$IFDEF FPL0} stam: PFPLMs_staDen; {$ENDIF}
                         O: POStaAPP;
                         var riadok: string
                        ): bool;

    function in_PRSnazvy(tsa: string): bool;
       var   i: int;
       begin
         i:= 0; while (i<poc_PRS_nazvy) and (tsa<>PRS_nazvy^[i]) do inc(i);
         in_PRSnazvy:= i<poc_PRS_nazvy
       end;

    var   tsa: string;
    begin
      while (ind<stap^.pocet) and in_PRSnazvy(stap^.stad[ind]^.kod) do inc(ind);
      if ind<stap^.pocet then tsa:= stap^.stad[ind]^.kod else tsa:= '';
      _riadok_l_sum:= _riadok_l (tsa,let, stap,{$IFDEF FPL0} stam, {$ENDIF} O,riadok);
      inc(ind)
    end;

 {$ENDIF}


 procedure OStaOPL.statistika_priestorov (var f: text; date: TDate; let: int);
     var   dx,dxx, i,j,k1,k2,l, riadkov: int;
           s,s1,s2,nl,fn : string;
           tmp  : text;
           bres : bool;
           {$IFDEF FPL0}
            stam: PFPLMs_staDen;
           {$ENDIF}
           {$IFDEF PRS}
            stap : PPRSs_staDen;
           {$ENDIF}

     begin
      { =========================================
        1. Statistika vyuzitia priestorov R a TSA
        -----------------------------------------
      }
      {$IFDEF PRS}
       new(stap);
       sta_PRS^.nacitanie_sumarneho_zaznamu (date,stap);

       {$IFDEF FPL0}
        new(stam);
        sta_FPLM^.nacitanie_sumarneho_zaznamu (date,stam);
       {$ENDIF}

       dx:= dsLSRLP_r-dsdx;
       zapis_riadok (f,  kbLavy2Horny2 + inschar('',dx,kbVodorovny2,1) + kbPravy2Horny2, true);
       zapis_riadok (f,  kbZvisly2 + _tit(cfg_TITLE_R_TSA,dx) + kbZvisly2, true);

       s:=  inschar('',dsLh_r,kbVodorovny,1);
       for i:= 1 to pocLi_r do s:= s + kbVodorovnyDole + inschar('',dsLi_r,kbVodorovny,1);
       s:=  kbZvisly2Doprava + s + kbVodorovnyDole2 + s + kbZvisly2Dolava;
       zapis_riadok (f,s,true);

       zapis_riadok (f,  kbZvisly2 + _tit(cfg_TITLE_AREA,dsLh_r)
                       + kbZvisly  + _tit(cfg_TSA_RESERVED,dsLi_r)
                       + kbZvisly  + _tit(cfg_TSA_USED,dsLi_r)
                       + kbZvisly  + _tit(cfg_TSA_FLIGHTS,dsLi_r)
                       + kbZvisly2 + _tit(cfg_TITLE_AREA,dsLh_r)
                       + kbZvisly  + _tit(cfg_TSA_RESERVED,dsLi_r)
                       + kbZvisly  + _tit(cfg_TSA_USED,dsLi_r)
                       + kbZvisly  + _tit(cfg_TSA_FLIGHTS,dsLi_r)
                       + kbZvisly2,
                     true
                    );

       nl:=  inschar('',dsLh_r,kbVodorovny,1);
       for i:= 1 to pocLi_r do nl:= nl + kbKriz + inschar('',dsLi_r,kbVodorovny,1);
       nl:=  kbZvisly2Doprava + nl + kbKrizZvisly2 + nl + kbZvisly2Dolava;

      { 1a) zapis priestorov, v poradi uvedenom v konfiguracnom subore
      }
       {riadkov:= (poc_PRS_nazvy div 2) + (poc_PRS_nazvy - 2*(poc_PRS_nazvy div 2));}
       riadkov:= poc_PRS_nazvy - (poc_PRS_nazvy div 2);
       i:= 0; while i<riadkov do
         begin
           _riadok_l_cfg (i,let, stap,{$IFDEF FPL0} stam, {$ENDIF} @Self, s1);
           _riadok_l_cfg (i+riadkov,let, stap,{$IFDEF FPL0} stam, {$ENDIF}  @Self, s2); {i+1 + 2*(riadkov div 2)}

           zapis_riadok (f,nl,true);
           zapis_riadok (f,   kbZvisly2 + s1
                            + kbZvisly2 + s2
                            + kbZvisly2,
                            true
                        );

           inc(i);
         end;

      { 1b) zapis priestorov, neuvedenych v konfiguracnom subore
      }
       fn:= pathTMP + TimeToStr2(hour,min,sec,'','') + ext_wrk;
       assign(tmp,fn); rewrite(tmp);

       bres:= false;
       i:= 0; while i<stap^.pocet do
         if _riadok_l_sum (i,let, stap,{$IFDEF FPL0} stam, {$ENDIF} @Self, s1) then
            begin
              writeln(tmp,s1);
              bres:= true
            end;
       close(tmp);

       reset(tmp);
       if bres then
          while not Eof(tmp) do
            begin
              readln(tmp,s1);
              if not Eof(tmp) then readln(tmp,s2)
              else _riadok_l('',-1,nil,nil,@Self,s2);

              zapis_riadok (f,nl,true);
              zapis_riadok (f,   kbZvisly2 + s1
                               + kbZvisly2 + s2
                               + kbZvisly2,
                               true
                           );
            end;
       close(tmp);

       DelFile(fn);

       s:=  inschar('',dsLh_r,kbVodorovny2,1);
       for i:= 1 to pocLi_r do s:= s + kbVodorovny2Hore + inschar('',dsLi_r,kbVodorovny2,1);
       s:=  kbLavy2Dolny2 + s + kbVodorovny2Hore2 + s + kbPravy2Dolny2;
       zapis_riadok (f,s,true);


      { ========================================
        2. Statistika vyuzitia strelnic
        ----------------------------------------
      }
       dx:= dsLSRLP_g-dsdx;
       zapis_riadok (f,  kbLavy2Horny2 + inschar('',dx,kbVodorovny2,1) + kbPravy2Horny2, true);
       zapis_riadok (f,  kbZvisly2 + _tit(cfg_TITLE_GND,dx) + kbZvisly2, true);

       s:=  kbZvisly2Doprava + inschar('',dsLh_g,kbVodorovny,1);
       for i:= 1 to pocLi_g do s:= s + kbVodorovnyDole + inschar('',dsLi_g,kbVodorovny,1);
       s:= s + kbZvisly2Dolava;
       zapis_riadok (f,s,true);

       zapis_riadok (f,  kbZvisly2 + _tit(cfg_TITLE_AREA,dsLh_g)
                       + kbZvisly  + _tit(cfg_GND_RESERVED,dsLi_g)
                       + kbZvisly  + _tit(cfg_GND_USED,dsLi_g)
                       + kbZvisly2,
                     true
                    );

       nl:=  kbZvisly2Doprava + inschar('',dsLh_g,kbVodorovny,1);
       for i:= 1 to pocLi_g do nl:= nl + kbKriz + inschar('',dsLi_g,kbVodorovny,1);
       nl:= nl + kbZvisly2Dolava;

       for i:= 0 to stap^.pocet-1 do with stap^.stad[i]^ do
         begin
           if (stai[let].planov_s=0) then continue;

           s:= kod; if nazov<>nil then s:= s + ' ('+strpas(nazov)+')';
           {with stai[let] do
             if stap^.den then begin k1:= planov_s_dni; k2:= vyuzitych_s_dni; end
             else begin k1:= planov_s_dni; k2:= vyuzitych_s_dni; end;}

           zapis_riadok (f,nl,true);
           zapis_riadok (f,   kbZvisly2 + inschar(' '+s,dsLh_g,' ',1)
                            + kbZvisly  + _cis(stai[let].planov_s_dni,dsLi_g)
                            + kbZvisly  + _cis(stai[let].vyuzitych_s_dni,dsLi_g)
                            + kbZvisly2,
                         true
                        );
           bres:= true;
         end;

       s:= kbLavy2Dolny2 + inschar('',dsLh_g,kbVodorovny2,1);
       for i:= 1 to pocLi_g do s:= s + kbVodorovny2Hore + inschar('',dsLi_g,kbVodorovny2,1);
       s:= s + kbPravy2dolny2;
       zapis_riadok (f,s,true);

       {$IFDEF FPL0}
        sta_FPLM^.disp_stad_(stam);
        dispose(stam);
       {$ENDIF}
       sta_PRS^.disp_stad_(stap);
       dispose(stap);
      {$ENDIF}
     end;


 procedure OStaOPL.statistika_LSRLP (var f: text; date: TDate; let: int);
    var    Bi : TsBod;
    begin
       LK_m^.read(let,Bi);
       zapis_odstavec (f,Bi.kod,true);
       zapis_hlavicku_pracoviska (f,date,cfg_HEADER_AIRBASE,Body.cfg_AIRBASE,Bi.kod,dsLSRLP_l);
       statistika_letov (f,date,let);
       zapis_riadok (f,'',true);
       statistika_priestorov (f,date,let);
       zapis_riadok (f,'',true);
       zapis_odstavec (f,'',false);
     end;

