 function _check_mtk_adr (line: string;       { testovany riadok }
                          var adr: string;    { adresy, musia by predinicializovane externe }
                          var znakov: int;    { pocet znakov celkom, musi byt nulovany na zaciatku externe }
                          posledny: bool;     { posledny riadok adresy }
                          max_dlzka: int;     { maximalna dlzka adresy, ignoruje sa, ak je "0" }
                          var res: string     { vysledok }
                         ): int;
    var   a : string;
          i,ires : int;
    begin
      res:= ''; ires:= -1;
      if (line<>'') then
       for i:= 1 to getstritems(line,[icao_NXIT]) do
           begin
             a:= getstr(line,i,[icao_NXIT]);
             if (length(a)<_MTK_ADR_lo) or (length(a)>_MTK_ADR_hi) then
                begin
                  ires:= l4_err(a_TLG,a, 0,err_MTK_2_adr_length, res);
                  break
                end;
             if a<>'' then
                begin
                  if adr<>'' then a:= icao_NXIT+a;
                  adr:= adr+a;
                end;
             inc(znakov,length(a))
           end;
      if (ires=-1) and posledny and (znakov=0) then ires:= l4_err(a_TLG,'',0,err_MTK_2_adr_missing, res);
      if (ires=-1) and (max_dlzka>0) and (znakov>max_dlzka) then ires:= l4_err(a_TLG,'',0,err_MTK_2_adr_to_much, res);
      _check_mtk_adr:= ires
    end;


 function code_MTK2_date (den,hod,min: byte): string;
    begin
      code_MTK2_date:= inttostr(den,2,0)+code_l4_utc(hod,min)
    end;


 function INC_CISLO_SPRAVY(var CISLO_SPRAVY: word; fn: string): word;
    begin
      CISLO_SPRAVY:= (CISLO_SPRAVY + 1) mod MTK_2_MOD_CISLA_SPRAVY;
      if CISLO_SPRAVY=0 then CISLO_SPRAVY:= 1;
      save_cislo(fn,CISLO_SPRAVY);
      INC_CISLO_SPRAVY:= CISLO_SPRAVY
    end;
