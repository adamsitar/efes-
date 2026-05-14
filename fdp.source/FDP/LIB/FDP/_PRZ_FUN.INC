(*
 procedure add_PRS(PRS: PPRS);
     begin
       PRSs^.add(PRS)
     end;


{ -------------------------- }
{ spracovanie                }
{ -------------------------- }

{ kontroly na jednoznacnost spracovania
}
 function exists_PRS (PRS: TPRS; var PRSp: TPRS): bool;
    var   rec : Tplan_rec;
          r_ : word; m_,d_,h_ : byte;
          res : int;

    label X;

    begin
      rec:= PRS.rec;
      r_:= PRS.zac.rok;
      if r_=0 then datum_init (PRS.zac, day,month,year, cas_PRS_zac,0,0);
      fillchar(PRSp,sizeof(PRSp),0);

     { najprv prehlada data v pamati }
      if PRSs<>nil then
         begin
           res:= PRSs^.find(@PRS);
           if res<>-1 then copy_PRS(PRSs^.ap^[res],@PRSp)
         end;

     { potom na disku z dnesneho dna }
      if res<>-1 then res:= read_PRS(codekey_PRS(@PRS),@PRSp);

      X: exists_PRS:= res<>-1;
      PRSp.rec:= rec
    end;


 function existuje_PRS(PRS: PPRS; _zobraz: bool): bool;
    var   res: bool;
          s: string;
    begin
     { kontrola na konflikt s inym podanym planom priestoru
     } res:= _find_PRS(PRS, @konfliktne_plany, '','')>-1;
       if res then
         begin
           s:=  msg_priestor+PRS^.kod
               +' '+inf_na_den+' '+DateToStr2(PRS^.zac.den,PRS^.zac.mes,0)
               +msg_planovany+PRS^.let;
           if PRS^.unt<>'' then s:= s+'/'+PRS^.unt;
           s:= s+'. '+ask_podat;
           res:= Ask2(msgWARNING,s,'',White,clBUTTON_COLOR,waitASK*18)<>ansAno;
         end;
      existuje_PRS:= res
    end;

 function zmeneny_PRS(PRS: PPRS; _zobraz: bool): bool;
    var   PRSn: TPRS;
          bres: bool;
    begin
      if read_PRS(codekey_PRS(PRS),@PRSn)>=0 then
         begin
           bres:= chg_PRS(PRS,@PRSn);
           if bres and _zobraz then info_PRS(@PRSn, tit_zmeneny_PRS);
           zmeneny_PRS:= bres;
           disp_PRS(@PRSn)
         end
      else zmeneny_PRS:= false
    end;


 function zarad_PRZ(PRZ: PPRZ; _stat: string; _send: bool): bool;
    begin
      if _stat<>'' then PRZ^.stat:= _stat;
      save_PRZ(PRZ);
      {add_PRZ(PRZ);}

      if _send then _odosli_PRZ(PRZ,_src);
    end;
*)


 function _zarad_PRZ (PRZ: PPRZ; _stat: string; _save,_send: bool; _src: fdp_src): bool;
    begin
      _zarad_PRZ:= true;
      _save:= modify_head_NOTAM (PNTM(PRZ),_stat) or _save;
      format_PRZ(PRZ);
      {if _save then} save_PRZ(PRZ);
      if _send then odosli_PRZ(PRZ);

      if (p_prz_dbscroller<>nil) then p_prz_dbscroller^.data_update(PRZ);
    end;


 function  zarad_PRZ (PRZ: PPRZ; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_PRZ:= _zarad_PRZ (PRZ,_stat,true,_send,_src)
    end;
