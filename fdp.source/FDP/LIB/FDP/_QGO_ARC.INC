function znova_uloz_QGO(QGO: PQGO; p: pointer): byte; far;
   begin
     save_QGO(QGO);
     znova_uloz_QGO:= do_item__NEXT
   end;

procedure kontrola_archivu;
    var   key,fn : string;
          QGO : TQGO;
          is : bool;

    begin
      fn:= najmladsi_subor(pathQGO,'*.'+extQGO);
      if konvertovat_archiv (pathQGO+fn,DB0) then
         begin
           konverzia_archivu(pathQGO,extQGO,
                             @znova_uloz_QGO,sizeof(TQGO),@disp_QGO,
                             db_QGO_RIADKOV,@_decodeDBT_QGO
                            );
          {$IFDEF FDP_OPL}
           konverzia_archivu(pathARCH_QGO,extQGO,
                             @znova_uloz_QGO,sizeof(TQGO),@disp_QGO,
                             db_QGO_RIADKOV,@_decodeDBT_QGO
                            );
          {$ENDIF}
         end
    end;
