function znova_uloz_DVZ(DVZ: PDVZ; p: pointer): byte; far;
   begin
     save_DVZ(DVZ);
     znova_uloz_DVZ:= do_item__NEXT
   end;

procedure kontrola_archivu;
    var   fn : string;
          DVZ : TDVZ;
    begin
      fn:= najmladsi_subor(pathDVZ,'*.'+extDVZ);
      if konvertovat_archiv (pathDVZ+fn,DB0) then
         begin
           konverzia_archivu(pathDVZ,extDVZ,
                             @znova_uloz_DVZ,sizeof(TDVZ),@disp_DVZ,
                             db_DVZ_RIADKOV,@_decodeDBT_DVZ
                            );
          {$IFDEF FDP_OPL}
           {konverzia_archivu(pathARCH_DVZ,extDVZ,
                             @znova_uloz_DVZ,sizeof(TDVZ),@disp_DVZ,
                             db0_DVZ_RIADKOV,@decode0DB_DVZ
                            );}
          {$ENDIF}
         end
    end;
