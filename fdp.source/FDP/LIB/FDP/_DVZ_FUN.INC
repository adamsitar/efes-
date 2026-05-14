 procedure add_DVZ(DVZ: PDVZ);
     begin
     end;

(*
{ -------------------------- }
{ spracovanie                }
{ -------------------------- }

{ kontroly na jednoznacnost spracovania
}
 function exists_DVZ (DVZ: TDVZ; var DVZp: TDVZ): bool;
    var   rec : Tplan_rec;
          r_ : word; m_,d_,h_ : byte;
          res : int;

    label X;

    begin
      rec:= DVZ.rec;
      r_:= DVZ.zac.rok;
      if r_=0 then datum_init (DVZ.zac, day,month,year, cas_DVZ_zac,0,0);
      fillchar(DVZp,sizeof(DVZp),0);

     { najprv prehlada data v pamati }
      if DVZs<>nil then
         begin
           res:= DVZs^.find(@DVZ);
           if res<>-1 then copy_DVZ(DVZs^.ap^[res],@DVZp)
         end;

     { potom na disku z dnesneho dna }
      if res<>-1 then res:= read_DVZ(codekey_DVZ(@DVZ),@DVZp);

      X: exists_DVZ:= res<>-1;
      DVZp.rec:= rec
    end;


 function existuje_DVZ(DVZ: PDVZ; _zobraz: bool): bool;
    var   res: bool;
          s: string;
    begin
     { kontrola na konflikt s inym podanym planom priestoru
     } res:= _find_DVZ(DVZ, @konfliktne_plany, '','')>-1;
       if res then
         begin
           s:=  msg_priestor+DVZ^.kod
               +' '+inf_na_den+' '+DateToStr2(DVZ^.zac.den,DVZ^.zac.mes,0)
               +msg_planovany+DVZ^.let;
           if DVZ^.unt<>'' then s:= s+'/'+DVZ^.unt;
           s:= s+'. '+ask_podat;
           res:= Ask2(msgWARNING,s,'',White,clBUTTON_COLOR,waitASK*18)<>ansAno;
         end;
      existuje_DVZ:= res
    end;


 function zmeneny_DVZ(DVZ: PDVZ; _zobraz: bool): bool;
    var   DVZn: TDVZ;
          bres: bool;
    begin
      if read_DVZ(codekey_DVZ(DVZ),@DVZn)>=0 then
         begin
           bres:= chg_DVZ(DVZ,@DVZn);
           if bres and _zobraz then info_DVZ(@DVZn, tit_zmeneny_DVZ);
           zmeneny_DVZ:= bres;
           disp_DVZ(@DVZn)
         end
      else zmeneny_DVZ:= false
    end;
*)

 function zarad_DVZ(DVZ: PDVZ; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_DVZ:= false;

      zarad_DVZ:= true;
      if _stat<>'' then DVZ^.stat:= _stat;
      format_DVZ(DVZ);
      save_DVZ(DVZ);

      {$IFDEF STATISTIKA_SERVER}
        if p_save_STA_DVZ<>nil then TProc_p(p_save_STA_DVZ)(DVZ);
      {$ENDIF}

     { musi byt na konci pertoze tato funkcia moze byt volana
       po spracovani z handlera tohto objektu objektu, ktory
       moze data uvolnit z pamate a dostanem takto referenciu
       na odalokovanu pamat
     }
      if _send then _odosli_DVZ(DVZ,_src);
      add_DVZ(DVZ);

      if (p_dvz_dbscroller<>nil) then p_dvz_dbscroller^.data_update(DVZ);
    end;

