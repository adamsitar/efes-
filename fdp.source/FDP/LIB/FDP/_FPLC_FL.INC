{$IFDEF FLI_COORDINATION}

{ Pre odoslanie sprav "FLI" o prelete statnej hranice platia nasledujuce
  pravidla :

  - sprava sa vydava nastaveny limit pred preletenim hranicneho bodu,
    nie po jeho preleteni
  - sprava sa vydava na dany bod len raz, ak sa zmeni cas dosiahnutia
    bodu alebo ine parametre letu, dalsia sprava sa uz nevydava
  - ak nie je mozne spravu vydat, nastavenie priznaku nespracovania

  Spracovanie spravy sa pamata v poli s popismi bodov trate letu :

  - v bin db sa uklada automaticky s polom
  - cez siet sa prenasa spolu s popisom planu (v poli "19")

  Stanica, ktora zabezpecuje spracovanie udajov FLI, pri zaradzovani
  spravy FPLC kontroluje, ci ma uvedene udaje o spracovani FLI,
  ak nie, nastavi tam posledne vlastnie
}
 function _najdi_fli(FPL: PDcFPL; bod_fli: int): int; forward;

 procedure _nastav_przn_fli (FPL: PDcFPL; bod: string);
     var   i : int;
     begin
       with FPL^ do for i:= 0 to bodov-1 do
         if (trat[i].kod=bod) then
            begin
              trat[i].pozn:= trat[i].pozn or sp_fli;
              FPL^.przn[p_others]:= FPL^.przn[p_others] or sp_fli
            end
     end;

 function _nastaveny_przn_fli(OB: TOB): bool;
    begin
      _nastaveny_przn_fli:= OB.pozn and sp_fli <> 0
    end;


 function _code_l4_fli(FPL: PDcFPL): string;
    var   s : string;
          i : int;
    begin
      s:= '';
      with FPL^ do for i:= 0 to bodov-1 do
        if _nastaveny_przn_fli(trat[i]) then
           begin
             if s<>'' then s:= s+icao_NXIT;
             s:= s + trat[i].kod
           end;
      if s<>'' then s:= ht_FLI+icao_NXT+s;
      _code_l4_fli:= s
    end;

 procedure _decode_l4_fli(_19: string; FPL: PDcFPL);
    var    i : int;
           bres : bool;
    begin
      _19:= _19+NULL;
      _19:= _item_18_(@_19[1],ht_FLI,1);
      bres:= false;
      for i:= 1 to getstritems(_19,[icao_NXIT]) do _nastav_przn_fli(FPL,getstr(_19,i,[icao_NXIT]));
      FPL^.przn[p_fli]:= _najdi_fli(FPL,0);
    end;


 function _code_tlg_fli(FPL: PDcFPL): string;
    var   s,reg : string;
          FP4   : DFPL4;
    begin
      s:= '';
      with FPL^ do if przn[p_fli] < bodov then
        begin
          s:=              idn
              + icao_ARR + format_s(getstr(typ,1,[icao_NXT]))
              + icao_ARR + format_s(start.kod)
              + icao_ARR + format_s(prist.kod)
              ;

          with FPL^.trat[przn[p_fli]] do
             s:= s + icao_ARR + kod + code_l4_utc (h,m)
                   + icao_ARR + code_l4_vys (vys,vysOB) + vysab
              ;

         reg:= '';
         {$IFDEF FPL4}
          if read_FPL4(codekey_FPLC(FPL), @FP4)>=0 then
             begin
               reg:= _item_18(FP4._18,rmk_REG, 1);
               disp_FPL4(@FP4)
             end;
         {$ENDIF}
         reg:= delchar(copy(getstr(reg,1,[icao_NXT]),1,kod_REG),[icao_ARR]);

         s:=  s + icao_ARR + rmk_REG+icao_NXT+format_s(reg)
                + icao_ARR + rmk_DATE+icao_NXT+code_l4_date_r(date.d,date.m,false)
       end;
      _code_tlg_fli:= s
    end;


 { Urcenie bodu, nad ktorym ma byt odoslana koordinacna sprava FLI.
   - kazdy bod si pamata priznakom sp_fli, ze bola odoslana sprava
   - v polozke przn[p_fli] je ulozeny dalsi bod, na ktory ma byt sprava odoslana;
     ak sa ta nachadza hodnota rovna poctu bodov, znamena to, ze vsetky spravy
     uz boli odoslane alebo neodosielaju sa ziadne
 }
  function  _najdi_fli(FPL: PDcFPL; bod_fli: int): int;
      var   i : int;
      begin
        while (bod_fli<FPL^.bodov) do with FPL^ do
          begin
            if not _nastaveny_przn_fli(trat[bod_fli]) then
               begin
                 i:= 0; while (i<OBs_io) and (trat[bod_fli].kod<>OB_io^[i].kod) do inc(i);
                 if (i<OBs_io) and (strpos(OB_io^[i].pozn,info_FLI)<>nil) then break
               end
            else FPL^.przn[p_others]:= FPL^.przn[p_others] or sp_fli;
            inc(bod_fli)
          end;
        _najdi_fli:= bod_fli
      end;

  function _bude_fli(FPL: PDcFPL): bool;
     begin
       _bude_fli:= FPL^.przn[p_fli]<FPL^.bodov;
     end;

  function _odoslat_fli(FPL: PDcFPL; var err: bool): bool;
     var   Tr  : real;
           i   : int;
           res : bool;
     begin
       err:= false;
       _odoslat_FLI:= false;
       if (FPL^.przn[p_fli]>=FPL^.bodov) then Exit;
       {if not _bude_fli(FPL) then Exit;}

       Tr:= limit_FLI*60;
       with FPL^ do
         begin
         { je Tr pred bodom alebo uz za ?
         } res:= (trat[przn[p_fli]].cas-Tr <= absTime);

         { moze sa zaplnit uplna sprava ?
         } err:=      res
                 and (   (cut_(start.kod)='')
                      or (cut_(prist.kod)='')
                      or (trat[przn[p_fli]].vys=0)
                      or (cut_(typ)='')
                     )
         end;

       _odoslat_fli:= res
     end;


 { zapamatanie udajov o odoslani FLI,
   odkazujem sa konktretny udaj v strukture cFPL;
   vyhladanie indexu je len kvoli zisteniu indexu
   pre vypis
 }
  procedure _odoslane_fli(FPL: PDcFPL; nastav,dalsi,zarad: bool);
      var   przn : byte;
            i : int;
            err : bool;
      begin
        if nastav then _nastav_przn_fli(FPL,FPL^.trat[FPL^.przn[p_fli]].kod);
        if dalsi  then FPL^.przn[p_fli]:= _najdi_fli(FPL,FPL^.przn[p_fli]+1);   { dalsi }

        if zarad then
           begin
             NETdistribute_data
                       (
                        [FDP],[],[MASTER,SLAVE],
                        spr_FPLC, FPL,@code_FPLC,@codekey_FPLC,@FPL^.rec,
                        true,ht_FLI,nil,false,false,net_flag_NIL
                       );

             if cFPL<>nil then
                begin
                  i:= cFPL^.find(FPL);
                  if i>-1 then cFPL^.vypis_plan(i,false,false)
                end;

             save_cFPL(FPL)
           end;
      end;

  function _odosli_fli (FPL: PDcFPL): bool;
     var   data, prty,adr : string;
           err : bool;
     begin
       _odosli_fli:= false;
       data:= _code_tlg_fli(FPL);
       if (not get_msg_adr (ht_FLI, prty,adr)) or (data='') then
           write_err_log(codekey_FPLC(FPL)+' - FLI not sended, unknown destination address.')
       {else if not send_FLI then
               write_err_log(codekey_FPLC(FPL)+' - FLI not sended, disabled function.')
       }
       else begin
              _proc_send_TLG (prty,adr,ht_FLI, @data[1],length(data));
              _odoslane_fli (FPL,true,true,true);
            end;
       _odosli_fli:= true
     end;


 { ------------------------------------------------------------------------
   Funkcia pre zistenie preletu statnej hranice a automaticke odoslanie
   spravy, ak nie je mozne spravu vydat, nastavenie priznaku nespracovania
 }
   function OcFPL.coordinate_FLI: bool;
      const _semaphor : bool = false;
            _min  : byte = 60;
            _tick : long = 0;
      var   err,ers,bres : bool;
            i : int;
      begin
        coordinate_FLI:= false;

        {$IFDEF BACKUP}
         if (SERVERstatus) then Exit;
        {$ENDIF}

        if (not send_FLI) or ((min=_min) and (arr_chg=_tick)) then Exit;

        coordinate_FLI:= true;
        if _semaphor then Exit;

        _semaphor:= true;
        _min:= min; _tick:= arr_chg;
        ers:= false;
        i:= 0; while (i<=top) do
          begin
            err:= false;
            bres:= _odoslat_fli(ap^[i],err);
            if bres then
               begin
                 if err then ers:= true
                 else _odosli_fli(ap^[i]);
               end;
            {if bres and (not err) then
            else} inc(i);
            CheckProcesses0;
          end;
        _semaphor:= false;

        is_FLI_ERR:= ers;
        coordinate_FLI:= ers
      end;


  function OcFPL.coordinate_FLI_ERR (var display_FLI_ERR: bool): bool;

     function find_err_fli : int;
        var   ers : bool;
              i   : int;
        begin
          i:= 0; ers:= false;
          while (i<=top) and (not ers) do
            begin
              if _odoslat_fli(ap^[i],ers) and ers then break;
              inc(i)
            end;

          find_err_fli:= i
        end;

     const _semaphor : bool = false;
     var   i : int;

     begin
       if _semaphor or (not is_FLI_ERR) or (not display_FLI_ERR) then Exit;

       _semaphor:= true;
       i:= find_err_fli;
       while display_FLI_ERR and (i<=top) do
         begin
           if not p_formular_FLI(PDcFPL(ap^[i])) then display_FLI_ERR:= false;
           i:= find_err_fli;
           CheckProcesses;
         end;
       _semaphor:= false;

       is_FLI_ERR:= i<=top;
       coordinate_FLI_ERR:= is_FLI_ERR
     end;

 { prototyp funkcie pre odoslanie spravy FLI
 }
  function _formular_FLI(FPL: PDcFPL): bool;
     begin
       _formular_FLI:= false
     end;

 (*
  {function OcFPL.formular_FLI(FPL: PDcFPL): bool;
     var   res : bool;
     begin
       res:= p_formular_FLI(FPL);
       if res then odoslane_FLI(FPL);
       formular_FLI:= res
     end;}
  *)
{$ENDIF}