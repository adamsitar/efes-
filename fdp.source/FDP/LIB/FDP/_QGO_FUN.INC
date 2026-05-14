
 function prenos_na_dalsi_den (QGOi: PQGO; nic: pointer): byte; far;
    var   QGO : TQGO;
    begin
      prenos_na_dalsi_den:= do_item__NEXT;

     { Len vlastnie a platnie }
      if (not _is_stat_QGO(QGOi,nil)) or _is_stat(QGOi^.stat,cnst_cnl,false) then Exit;

      new_QGO(QGOi,@QGO);
      init_date (QGO.date, year,month,day);
      if QGO.TQGOc<>'' then QGO.TQGOc:= code_l4_utc(0,0);
      if QGO.MQGOc<>'' then QGO.MQGOc:= code_l4_utc(0,0);
      zarad_QGO(@QGO,QGO.stat,true,letvis);
      disp_QGO(@QGO);
    end;

 procedure spracuj_hlasenia_o_QGO;
     const den : byte = 0;
     var   QGO : TQGO;
           d   : TDate;
           fn  : string;
     begin
      {$IFDEF AIRBASE}
      { Hlasenia o stave letisk prechadzajuce do druheho dna
      } if (den<>day) and (hour=0) then
          begin
            den:= day;
            init_date (d, year,month,day);
            PrevDate (d.r,d.m,d.d);
            fn:= pathQGO+get_PLANfn(d.d,d.m,d.r)+'.'+extQGO;
            if FExists(fn)<>0 then fn:= get_ARCHIVfn(pathQGO)+get_PLANfn(d.d,d.m,d.r)+'.'+extQGO;
            if FExists(fn)=0 then
               do_items_DB (@prenos_na_dalsi_den,
                            nil, @QGO, @disp_QGO,
                            FN, db_QGO_RIADKOV,nil,@decodeDB_QGO,nil,
                            @dbchg_QGO
                           );
          end;
      {$ENDIF}
     end;


 procedure add_QGO(QGO: PQGO);
     begin
     end;


(*{ kontroly na jednoznacnost spracovania
}
 function exists_QGO (QGO: TQGO; var QGOp: TQGO): bool;
    var   rec : Tplan_rec;
          r_ : word; m_,d_,h_ : byte;
          res : int;

    label X;

    begin
      rec:= QGO.rec;
      r_:= QGO.zac.rok;
      if r_=0 then datum_init (QGO.zac, day,month,year, cas_QGO_zac,0,0);
      fillchar(QGOp,sizeof(QGOp),0);

     { najprv prehlada data v pamati }
      if QGOs<>nil then
         begin
           res:= QGOs^.find(@QGO);
           if res<>-1 then copy_QGO(QGOs^.ap^[res],@QGOp)
         end;

     { potom na disku z dnesneho dna }
      if res<>-1 then res:= read_QGO(codekey_QGO(@QGO),@QGOp);

      X: exists_QGO:= res<>-1;
      QGOp.rec:= rec
    end;


 function existuje_QGO(QGO: PQGO; _zobraz: bool): bool;
    var   res: bool;
          s: string;
    begin
     { kontrola na konflikt s inym podanym planom priestoru
     } res:= _find_QGO(QGO, @konfliktne_plany, '','')>-1;
       if res then
         begin
           s:=  msg_priestor+QGO^.kod
               +' '+inf_na_den+' '+DateToStr2(QGO^.zac.den,QGO^.zac.mes,0)
               +msg_planovany+QGO^.let;
           if QGO^.unt<>'' then s:= s+'/'+QGO^.unt;
           s:= s+'. '+ask_podat;
           res:= Ask2(msgWARNING,s,'',White,clBUTTON_COLOR,waitASK*18)<>ansAno;
         end;
      existuje_QGO:= res
    end;


 function zmeneny_QGO(QGO: PQGO; _zobraz: bool): bool;
    var   QGOn: TQGO;
          bres: bool;
    begin
      if read_QGO(codekey_QGO(QGO),@QGOn)>=0 then
         begin
           bres:= chg_QGO(QGO,@QGOn);
           if bres and _zobraz then info_QGO(@QGOn, tit_zmeneny_QGO);
           zmeneny_QGO:= bres;
           disp_QGO(@QGOn)
         end
      else zmeneny_QGO:= false
    end;
*)

 function zarad_QGO(QGO: PQGO; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_QGO:= false;
      zarad_QGO:= true;

      if _stat<>'' then QGO^.stat:= _stat;
      format_QGO(QGO);
      save_QGO(QGO);

      {$IFDEF STATISTIKA_SERVER}
        if p_save_STA_QGO<>nil then TProc_p(p_save_STA_QGO)(QGO);
      {$ENDIF}

      { musi byt na konci pertoze tato funkcia moze byt volana
        po spracovani z handlera tohto objektu objektu, ktory
        moze data uvolnit z pamate a dostanem takto referenciu
        na odalokovanu pamat
      }
      if _send then _odosli_QGO(QGO,_src);
      add_QGO(QGO);

      if (p_qgo_dbscroller<>nil) then p_qgo_dbscroller^.data_update(QGO);
    end;
