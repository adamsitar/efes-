function znova_uloz_PRS(PRS: PPRS; p: pointer): byte; far;
   begin
     save_PRS(PRS);
     znova_uloz_PRS:= do_item__NEXT
   end;

procedure kontrola_archivu;
    var   key,fn : string;
          P: PathStr; D: DirStr; N: NameStr; E: ExtStr;
          PRS : TPRS;
          is : bool;

    begin
      fn:= najmladsi_subor(pathPRS,'*.'+extPRS);
      if {$IFDEF LZ} (dbattr_PRS=DBbin) and {$ENDIF} konvertovat_archiv (pathPRS+fn,DB0) then
         begin
           konverzia_archivu(pathPRS,extPRS,
                             @znova_uloz_PRS,sizeof(TPRS),@disp_PRS,
                            {$IFDEF LZ}
                             db_PRS_RIADKOV,@_decodeDBT_PRS
                            {$ELSE}
                             db0_PRS_RIADKOV,@_decodeDB0_PRS
                            {$ENDIF}
                            );
         end;

      if (dbattr_PRS=DBbin) and konvertovat_archiv (pathPRS+fn,DBtxt) then
         begin
           konverzia_archivu(pathPRS,extPRS,
                             @znova_uloz_PRS,sizeof(TPRS),@disp_PRS,
                             db_PRS_RIADKOV,@_decodeDBT_PRS
                            );
         end;
    end;

