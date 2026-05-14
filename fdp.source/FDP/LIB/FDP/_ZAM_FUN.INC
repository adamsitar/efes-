 function _add_ZAM(ZAM: PZAM): bool;
    begin
      _add_ZAM:= ZAMs^.add(ZAM)<>-1
    end;

 procedure add_ZAM(ZAM: PZAM);
     var   res: bool;
     begin
       res:= _add_ZAM(ZAM)
     end;


(*{ kontroly na jednoznacnost spracovania
}
 function exists_ZAM (ZAM: TZAM; var ZAMp: TZAM): bool;
    var   rec : Tplan_rec;
          r_ : word; m_,d_,h_ : byte;
          res : int;

    label X;

    begin
      rec:= ZAM.rec;
      r_:= ZAM.zac.rok;
      if r_=0 then datum_init (ZAM.zac, day,month,year, cas_ZAM_zac,0,0);
      fillchar(ZAMp,sizeof(ZAMp),0);

     { najprv prehlada data v pamati }
      if ZAMs<>nil then
         begin
           res:= ZAMs^.find(@ZAM);
           if res<>-1 then copy_ZAM(ZAMs^.ap^[res],@ZAMp)
         end;

     { potom na disku z dnesneho dna }
      if res<>-1 then res:= read_ZAM(codekey_ZAM(@ZAM),@ZAMp);

      X: exists_ZAM:= res<>-1;
      ZAMp.rec:= rec
    end;


 function existuje_ZAM(ZAM: PZAM; _zobraz: bool): bool;
    var   res: bool;
          s: string;
    begin
     { kontrola na konflikt s inym podanym planom priestoru
     } res:= _find_ZAM(ZAM, @konfliktne_plany, '','')>-1;
       if res then
         begin
           s:=  msg_priestor+ZAM^.kod
               +' '+inf_na_den+' '+DateToStr2(ZAM^.zac.den,ZAM^.zac.mes,0)
               +msg_planovany+ZAM^.let;
           if ZAM^.unt<>'' then s:= s+'/'+ZAM^.unt;
           s:= s+'. '+ask_podat;
           res:= Ask2(msgWARNING,s,'',White,clBUTTON_COLOR,waitASK*18)<>ansAno;
         end;
      existuje_ZAM:= res
    end;


 function zmeneny_ZAM(ZAM: PZAM; _zobraz: bool): bool;
    var   ZAMn: TZAM;
          bres: bool;
    begin
      if read_ZAM(codekey_ZAM(ZAM),@ZAMn)>=0 then
         begin
           bres:= chg_ZAM(ZAM,@ZAMn);
           if bres and _zobraz then info_ZAM(@ZAMn, tit_zmeneny_ZAM);
           zmeneny_ZAM:= bres;
           disp_ZAM(@ZAMn)
         end
      else zmeneny_ZAM:= false
    end;
*)

 function zarad_ZAM(ZAM: PZAM; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_ZAM:= false;
      zarad_ZAM:= true;

      if _stat<>'' then ZAM^.stat:= _stat;
      format_ZAM(ZAM);
      save_ZAM(ZAM);

      {$IFDEF STATISTIKA_SERVER}
        if p_save_STA_ZAM<>nil then TProc_p(p_save_STA_ZAM)(ZAM);
      {$ENDIF}

      { musi byt na konci pertoze tato funkcia moze byt volana
        po spracovani z handlera tohto objektu objektu, ktory
        moze data uvolnit z pamate a dostanem takto referenciu
        na odalokovanu pamat
      }
      if _send then _odosli_ZAM(ZAM,_src);

      if (p_zam_dbscroller<>nil) then p_zam_dbscroller^.data_update(ZAM);

      add_ZAM(ZAM);
    end;