{$IFDEF PROCESS_DVZ}

 { --------------------------------------------
   spracovanie planov, na ktore dosla ziadost
 }

 function handle_prop_DVZ (p: pointer; DVZ: PDVZ): bool; far;
    var   res: bool;
    begin
      res:= _ziadost_o_DVZ(nil, DVZ);
      if res then formular_so_ziadostou_o_DVZ (DVZ,true);
      handle_prop_DVZ:= res
    end;


 function prenos_na_dalsi_den (DVZi: PDVZ; nic: pointer): byte; far;
    var   DVZ : TDVZ;
          zac,kon : TTime;
    begin
      prenos_na_dalsi_den:= do_item__NEXT;

     { Len vlastnie a platnie }
      if (not _vlastne(DVZi,nil)) or _is_stat(DVZi^.stat,cnst_disk+cnst_cnl,false) then Exit;

     { Spravne zadane casy ? }

      if not (GetTimeStr(zac.h,zac.m,zac.s,DVZi^.zac) and GetTimeStr(kon.h,kon.m,kon.s,DVZi^.kon)) then Exit;

     { Prechadza plan na nasledujuci den  ? }
      if TimeToSec(zac.h,zac.m,zac.s)<TimeToSec(kon.h,kon.m,kon.s) then Exit;

      new_DVZ(DVZi,@DVZ);
      init_date (DVZ.date, year,month,day);
      DVZ.zac:= code_l4_utc(0,0);
      zarad_DVZ(@DVZ,DVZ.stat,true,letvis);
      disp_DVZ(@DVZ);
    end;


 procedure spracuj_ziadosti_o_DVZ;
     const semaphor: bool = false;
           den : byte = 0;

     var   DVZ : TDVZ;
           d   : TDate;
           fn  : string;

     begin
      { Prijate ziadosti o diverziu
      }
       if PROC_DVZ and isDVZ_REQ and (not semaphor) then
          begin
          { bola prijata ziadost o pripomienku }
            semaphor:= true;
            fillchar(DVZ,sizeof(TDVZ),0);
            while DB_prehladaj (@handle_prop_DVZ,
                                nil,@DVZ, @disp_DVZ,
                                get_dbDVZfn, db_DVZ_RIADKOV,@decodeDB_DVZ,@codekey_DVZ,
                                true,''
                               ) <> -1
            do;
            isDVZ_REQ:= false;
            semaphor:= false
          end;

      {$IFDEF AIRBASE}
      { Ziadosti o diverziu prechadzajuce do druheho dna
      } if (den<>day) and (hour=0) then
          begin
            den:= day;
            init_date (d, year,month,day);
            PrevDate (d.r,d.m,d.d);
            fn:= pathDVZ+get_PLANfn(d.d,d.m,d.r)+'.'+extDVZ;
            if FExists(fn)<>0 then fn:= get_ARCHIVfn(pathDVZ)+get_PLANfn(d.d,d.m,d.r)+'.'+extDVZ;
            if FExists(fn)=0 then
               do_items_DB (@prenos_na_dalsi_den,
                            nil, @DVZ, @disp_DVZ,
                            FN, db_DVZ_RIADKOV,nil,@decodeDB_DVZ,nil,
                            @dbchg_DVZ
                           );
          end;
      {$ENDIF}
     end;

{$ENDIF}
