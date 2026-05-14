{ -----------------------------------------
  lokalne fcie : alokovanie a kodovanie
  -----------------------------------------
}
 procedure new_PRS_sta(sta1,sta2: PPRS_sta); far;
     begin
       FillChar(sta2^,sizeof(sta2^),0);
       if sta1<>nil then
          begin
            sta2^:= sta1^;
            sta2^.nazov:= strnew(sta1^.nazov)
          end
     end;

 procedure disp_PRS_sta(sta: PPRS_sta); far;
     begin
       strdispose(sta^.nazov)
     end;


 procedure new_PRSi_sta(sta1, sta2: PPRSi_sta); far;
     begin
       FillChar(sta2^,sizeof(sta2^),0);
       if sta1<>nil then
          begin
            sta2^:= sta1^;
            sta2^.nazov:= strnew(sta1^.nazov)
          end
     end;

 procedure disp_PRSi_sta(sta: PPRSi_sta); far;
     begin
       strdispose(sta^.nazov)
     end;


 procedure new_PRSs_stad(sta1, sta2: PPRSs_staDen); far;
     var   i: int;
     begin
       FillChar(sta2^,sizeof(sta2^),0);
       if sta1<>nil then
          begin
            sta2^:= sta1^;
            for i:= 0 to sta2^.pocet-1 do
              begin
                New(sta2^.stad[i]);
                new_PRSi_sta(sta1^.stad[i],sta2^.stad[i])
              end;
          end
     end;

 procedure disp_PRSs_stad(sta: PPRSs_staDen); far;
     var   i: int;
     begin
       for i:= 0 to sta^.pocet-1 do
          begin
            disp_PRSi_sta(sta^.stad[i]);
            dispose(sta^.stad[i]);
            sta^.pocet:= 0
          end;
     end;


{ -----------------------------------------
  lokalne fcie : zapis a nacitanie suborov
  -----------------------------------------
}
 procedure codeDB_PRS_sta (sta: PPRS_sta; buff: PDB_buff; desc: PDB_head); far;
     var   s,t, n : string;

     begin
       s:= '';
       add_s (@sta^.kod, sizeof(sta^.kod), s,t);
       add_s (@sta^.typ, sizeof(sta^.typ), s,t);
       add_s (@sta^.let, sizeof(sta^.let), s,t);
       add_s (@sta^.vyuzity, sizeof(sta^.vyuzity), s,t);
       n:= strpas(sta^.nazov);
       add_s (@n,1+max_prs_nazov,  s,t);
       str_toDBstr (s,buff^[db_sta_STA_prs]);
     end;

 procedure decodeDB_PRS_sta (buff: PDB_buff; sta: PPRS_sta; desc: PDB_head); far;
     var   s,n : string;
           p : pchars;
     begin
       fillchar(sta^,sizeof(sta^),0);

       s:= DBstr_to_str (buff^[db_sta_STA_prs]);
       p:= @s[1];
       get_s(p, @sta^.kod, sizeof(sta^.kod));
       get_s(p, @sta^.typ, sizeof(sta^.typ));
       get_s(p, @sta^.let, sizeof(sta^.let));
       get_s(p, @sta^.vyuzity, sizeof(sta^.vyuzity));
       get_s(p, @n, 1+max_prs_nazov);
       sta^.nazov:= strpasnew(n);
     end;

 function  codeDBkey_PRS_sta (sta: PPRS_sta): string; far;
    begin
      codeDBkey_PRS_sta:= sta^.key
    end;


 procedure zapis_PRSs_sta (fn: string; stad: PPRSs_staDen); far;
     var   f : file;
           len,res : word;
           i : int;
     begin
       assign(f,fn); rewrite(f,1);

       BlockWrite(f,stad^.den,  sizeof(stad^.den),  res);
       BlockWrite(f,stad^.pocet,sizeof(stad^.pocet),res);

       for i:= 0 to stad^.pocet-1 do
          begin
            BlockWrite(f,stad^.stad[i]^.kod, sizeof(stad^.stad[i]^.kod), res);
            BlockWrite(f,stad^.stad[i]^.stai,sizeof(stad^.stad[i]^.stai),res);

            len:= strlen(stad^.stad[i]^.nazov);
            BlockWrite(f,len,sizeof(len),res);
            BlockWrite(f,stad^.stad[i]^.nazov[0],len,res)
          end;

       close(f)
     end;

 function nacitaniePRSs_sta (fn: string; stad: PPRSs_staDen): bool; far;
    var   f : file;
          len,res : word;
          i : int;
          {sta : TPRSi_sta;}
    begin
      fillchar(stad^,sizeof(stad^),0);
      nacitaniePRSs_sta:= true;

      assign(f,fn); reset(f,1);

      BlockRead(f,stad^.den,  sizeof(stad^.den),  res);
      BlockRead(f,stad^.pocet,sizeof(stad^.pocet),res);

      for i:= 0 to stad^.pocet-1 do
         begin
           new(stad^.stad[i]); fillchar(stad^.stad[i]^,sizeof(stad^.stad[i]^),0);
           BlockRead (f,stad^.stad[i]^.kod, sizeof(stad^.stad[i]^.kod), res);
           BlockRead (f,stad^.stad[i]^.stai,sizeof(stad^.stad[i]^.stai),res);

           BlockRead (f,len,sizeof(len),res);
           stad^.stad[i]^.nazov:= StrAlloc(len);
           if stad^.stad[i]^.nazov<>nil then BlockRead(f,stad^.stad[i]^.nazov[0],len,res)
           else Seek(f,FilePos(f)+len)
         end;

      close(f)
    end;


{ -----------------------------------------
  externe fcie : zapis, info
  -----------------------------------------
}
 procedure save_STA_PRS (PRS: PPRS); far;
     var   d: TDate;
     begin
       init_date(d, PRS^.zac.rok,PRS^.zac.mes,PRS^.zac.den);
       if sta_PRS<>nil then sta_PRS^.zapis_polozky(d,PRS);
     end;

 procedure info_STA_PRS; far;
     begin
       if StatistikaAPP<>nil then StatistikaAPP^.zobraz_priebeznu_statistiku_(true);
     end;


{ -----------------------------------------
  instancia objektu pre PRS :
  -----------------------------------------
}
 constructor OStatistikaPRS.Init(_cfg_FN: string);
       begin
         poc_PRS_nazvy:= 0;
         PRS_nazvy:= nil;

         inherited Init(extPRS,

                        sizeof(TPRS_sta), @new_PRS_sta,@disp_PRS_sta,
                        @codeDB_PRS_sta,  @decodeDB_PRS_sta,@codeDBkey_PRS_sta,db_riadkov_STA_sta,

                        sizeof(TPRSs_staDen), @new_PRSs_stad,@disp_PRSs_stad, @zapis_PRSs_sta,@nacitaniePRSs_sta,
                        {poloziek_PRS}0,

                        _cfg_FN
                       );

         prepocitavat_pri_uzatvarani:= false;
         {$IFDEF STATISTIKA_SERVER}
          p_save_STA_PRS := @save_STA_PRS;
         {$ENDIF}
         p_info_STA_PRS := @info_STA_PRS;
       end;


 procedure OStatistikaPRS.nacitaj_cfg(_cfg_FN: string);
      var  i,j,p : int;
           s : string;
      begin
        inherited nacitaj_cfg(_cfg_FN);

        i:= 1; poc_PRS_nazvy:= 0;
        repeat
          s:= getstr(__read_cfg_line(_cfg_FN,cfg_LINE_AREA,i,2),2,odd_cfg);
          if s<>'' then
             begin
               inc(poc_PRS_nazvy);
               inc(i)
             end;
        until s='';

        if (poc_PRS_nazvy>0) and AllocMem(pointer(PRS_nazvy),sizeof(TPRS_nazov)*poc_PRS_nazvy) then
           begin
             p:= i; i:= 1; j:= 0; while (j<poc_PRS_nazvy) and (i<=p{multitask, ha!}) do
               begin
                 s:= getstr(__read_cfg_line(_cfg_FN,cfg_LINE_AREA,i,2),2,odd_cfg);
                 if s<>'' then
                    begin
                      PRS_nazvy^[j]:= _unique_area_code(s);
                      inc(j)
                    end;
                 inc(i)
               end;
           end;
      end;

 destructor OStatistikaPRS.Done;
      begin
        if PRS_nazvy<>nil then
           begin
             DeallocMem(pointer(PRS_nazvy),sizeof(TPRS_nazov)*poc_PRS_nazvy);
             poc_PRS_nazvy:= 0;
           end;
        inherited Done;
      end;


{ Inicializacia statistickeho zaznamu
  o vyuziti priestoru
}
 procedure OStatistikaPRS.initialize_sta (data: pointer; _sta: PStaFDP);
    var    PRS : PPRS;
           sta : PPRS_sta;
           is  : bool;
           i   : int;
    begin
      fillchar(_sta^,sta_size,0);
      PRS:= PPRS(data);
      sta:= PPRS_sta(_sta);

      sta^.key:= codekey_PRS (PRS);
      sta^.kod:= PRS^.kod;
      sta^.let:= PRS^.let;
      sta^.typ:= typ_PRS (PRS);

      sta^.nazov:= strpasnew(nazov_PRS(PRS));
      sta^.vyuzity:= _is_stat (PRS^.stat,delchar(cnst_stat_actived,[cnst_cnl]),false);
    end;



{ -----------------------------------
  denny zaznam spocitanych poloziek
  -----------------------------------
}
 function  _najdi_PRS_sta (kod: string; stad: PPRSs_staDen): int;
    var    i: int;
    begin
      i:= 0; while (i<stad^.pocet) and (kod<>stad^.stad[i]^.kod) do inc(i);
      if (i>=stad^.pocet) then i:= -1;
      _najdi_PRS_sta:= i
    end;


 procedure __aktualizacia_denneho_zaznamu_prs (var stad: TPRSi_sum; sta: TPRS_sta; pridaj: int);
     begin
       if (sta.typ<>PRIESTOR_STRELNICA) then
          begin
            inc(stad.planov_l, pridaj);
            if sta.vyuzity then inc(stad.vyuzitych_l, ord(sta.vyuzity)*pridaj);
          end
       else begin
              inc(stad.planov_s, pridaj);
              if sta.vyuzity then inc(stad.vyuzitych_s, ord(sta.vyuzity)*pridaj);
              stad.planov_s_dni:= ord(stad.planov_s);
              stad.vyuzitych_s_dni:= ord(stad.vyuzitych_s);
            end;
     end;

 procedure _aktualizacia_denneho_zaznamu_prs (sta: PPRS_sta; stad: PPRSs_staDen; pridaj: int);
     var   ind,let: int;
     begin
       let:= _LKmind(sta^.let);
       ind:= _najdi_PRS_sta (sta^.kod,stad);
       if (pridaj<0) and (ind<0) then Exit;

       if (not (pridaj<0)) and (ind<0) then
          begin
          { pridanie noveho zaznamu
          } if stad^.pocet>=max_PRSsta then Exit;
            new(stad^.stad[stad^.pocet]);
            fillchar(stad^.stad[stad^.pocet]^,sizeof(stad^.stad[stad^.pocet]^),0);
            stad^.den:= true;
            ind:= stad^.pocet;
            inc(stad^.pocet);
          end;

       __aktualizacia_denneho_zaznamu_prs (stad^.stad[ind]^.stai[max_AIRBASE], sta^, pridaj);
       if let>=0 then __aktualizacia_denneho_zaznamu_prs (stad^.stad[ind]^.stai[let], sta^, pridaj);

       with stad^.stad[ind]^ do
         begin
          if not (pridaj<0) then
             begin
               kod:= sta^.kod;
               if not eq_str0(nazov,sta^.nazov) then
                  begin
                    strdispose(nazov);
                    nazov:= strnew(sta^.nazov)
                  end;
             end
          end;
     end;

 procedure OStatistikaPRS.aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool);
     begin
       if (not reset) and (_stap<>nil) then _aktualizacia_denneho_zaznamu_prs (_stap,_stad, -1);
       _aktualizacia_denneho_zaznamu_prs (_sta,_stad, +1)
     end;


 procedure _aktualizacia_sumarneho_zaznamu_dnom_prs(var stad: TPRSi_sum; sta: TPRSi_sum);
     begin
       inc(stad.planov_l,    sta.planov_l);
       inc(stad.vyuzitych_l, sta.vyuzitych_l);
       inc(stad.letov_l,     sta.letov_l);


       inc(stad.planov_s,    sta.planov_s);
       inc(stad.vyuzitych_s, sta.vyuzitych_s);

       inc(stad.planov_s_dni,    sta.planov_s_dni);
       inc(stad.vyuzitych_s_dni, sta.vyuzitych_s_dni);
     end;

 procedure OStatistikaPRS.aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs);
     var   stad1,stad2: PPRSs_staDen;
           l, ind1,ind2 : int;
     begin
       stad1:= PPRSs_staDen(_sta_suma);
       stad2:= PPRSs_staDen(_sta_ciastocny);

       for ind2:= 0 to stad2^.pocet-1 do
         begin
           ind1:= _najdi_PRS_sta (stad2^.stad[ind2]^.kod,stad1);

           if (ind1<0) then
              begin
              { pridanie noveho zaznamu
              } if stad1^.pocet>=max_PRSsta then Exit;
                new(stad1^.stad[stad1^.pocet]);
                fillchar(stad1^.stad[stad1^.pocet]^,sizeof(stad1^.stad[stad1^.pocet]^),0);
                ind1:= stad1^.pocet;

                stad1^.den:= false;
                inc(stad1^.pocet);
                stad1^.stad[ind1]^.kod:= stad2^.stad[ind2]^.kod;
                stad1^.stad[ind1]^.nazov:= strnew(stad2^.stad[ind2]^.nazov);
              end;

           for l:= 0 to max_AIRBASE do
               _aktualizacia_sumarneho_zaznamu_dnom_prs
                  (stad1^.stad[ind1]^.stai[l],
                   stad2^.stad[ind2]^.stai[l]
                  )
         end;
     end;


{ -----------------------------------------
  pomocne fcie:
}

{ "konverzia" stareho protokolu do noveho, vlastne:
    - prepocitanie novych dennych zaznamov
    - vytvorenie noveho mesacneho zaznamu
}
 procedure konverzia_prs;
   var  d : TDate;  x,y,i : int; by : byte; b: bool;
        fni,fn,dir,ext : string;
        di : SearchRec;
        stad : PStadFDPs;
   begin
     with StatistikaAPP^ do
       begin
         write('Prepocitavam mesacnu statistiku priestorov... ');
         x:= wherex; y:= wherey;

         init_date(d, year,month,day);
         fn:= get_STAsuma_fn (d,extPRS);
         FSplit(fn,dir,fn,ext);
         del(dir+'*'+ext);                 { odmazanie povodnych zaznamov, i mesacnych }
         fn:= get_STAwork_fn (d,extPRS);
         FSplit(fn,dir,fn,ext);            {  -//-  }
         del(dir+'*'+ext);

         fni:= get_STAdata_fn (d,extPRS);
         fsplit(fni,dir,fn,ext);
         fni:= dir+'*'+ext;
         FindFirst(fni,Archive,di);
         while (DosError=0) do
           begin
             write(' -> '+di.name);
             decode_archived_date (di.name,true,d.r,d.m,d.d,by);
             sta_PRS^.new_stad(nil,stad);
             sta_PRS^.nacitanie_denneho_sumarneho_zaznamu (d,stad, false,true,true, b);
             sta_PRS^.disp_stad(stad);
             ResetIOError;
             FindNext(di);
             gotoxy(x,y); clreol; gotoxy(x,y);
           end;
         init_date(d, year,month,day);
         sta_PRS^.vytvorenie_mesacneho_sumarneho_zaznamu (d);
         writeln('Hotovo.');
       end;
   end;
