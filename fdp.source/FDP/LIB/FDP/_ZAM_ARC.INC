function znova_uloz_ZAM(ZAM: PZAM; p: pointer): byte; far;
   begin
     save_ZAM(ZAM);
     znova_uloz_ZAM:= do_item__NEXT
   end;


procedure kontrola_archivu;
    var   fn : string;
          ZAM : TZAM;

    begin
      {if is_ParamStr(psDATA_FORMAT)='' then Exit;
      key:= DB_citaj_kluc (0,get_dbZAMfn,db0_ZAM_RIADKOV);
      if key='' then Exit;}

      fn:= najmladsi_subor(pathZAM,'*.'+extZAM);
      if (dbattr_ZAM=DBbin) and konvertovat_archiv (pathZAM+fn,DB0) then
         begin
           konverzia_archivu(pathZAM,extZAM,
                             @znova_uloz_ZAM,sizeof(TZAM),@disp_ZAM,
                             db_ZAM_RIADKOV,@_decodeDBT_ZAM
                            );
          {$IFDEF FDP_OPL}
           {konverzia_archivu(pathARCH_ZAM,extZAM,
                             @znova_uloz_ZAM,sizeof(TZAM),@disp_ZAM,
                             db0_ZAM_RIADKOV,@decode0DB_ZAM
                            );}
          {$ENDIF}
         end
    end;
