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
      if r_=0 then datum_init (PRS.zac, day,month,year, {$IFDEF FUA} cas_PRS_zac {$ELSE} hour {$ENDIF},0,0);
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
     } res:= _find_PRS(PRS, {$IFDEF PLAN_PRS} @konfliktne_plany
                            {$ELSE}           nil{@eq_PRS}
                            {$ENDIF},
                       '',''
                      )>-1;
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
           if bres and _zobraz then 
              begin
                info_PRS(@PRSn, tit_zmeneny_PRS);
                bres:= not (Ask2(msgWARNING, tit_zmeneny_PRS+' '+ask_prepisat,'',White,clBUTTON_COLOR,waitASK*18)=ansAno)
              end;
           zmeneny_PRS:= bres;
           disp_PRS(@PRSn)
         end
      else zmeneny_PRS:= false
    end;


 function zarad_PRS(PRS: PPRS; _stat: string; _send: bool; _src: fdp_src): bool;
    var   db  : PDB;
          pos : int;
    begin
      zarad_PRS:= false;
      if is_P(PRS^.kod) and (not process_PRS_P) then Exit;

      zarad_PRS:= true;
      if _stat<>'' then PRS^.stat:= _stat;
      format_PRS(PRS);

      {db:= New(PDB,Init(get_dbPRSifn(PRS),DB_RWClose,
                        db_PRS_RIADKOV,@codeDB_PRS,@codeDB_PRS,@decodekey_PRS,
                        @dbchg_PRS, dbattr_PRS
                       );
      pos:= db^.vyhladaj_data (PRS);}
      if _send then _odosli_PRS(PRS,_src{,db,pos});
      save_PRS(PRS);
      {db^.zapis(_data,_pos,false);
      dispose(db,Done);}

      {$IFDEF STATISTIKA_SERVER}
       if p_save_STA_PRS<>nil then TProc_p(p_save_STA_PRS)(PRS);
      {$ENDIF}

      if (p_prs_dbscroller<>nil) then p_prs_dbscroller^.data_update(PRS);

      { musi byt na konci pretoze tato funkcia moze byt volana
        po spracovani z handlera tohto objektu objektu, ktory
        moze data uvolnit z pamate a dostanem takto referenciu
        na odalokovanu pamat
      }
      add_PRS(PRS);
    end;
