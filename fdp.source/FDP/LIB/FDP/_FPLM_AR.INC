function znova_uloz_FPLM(FPL: PDmFPL; p: pointer): byte; far;
   begin
     save_mFPL(FPL);
     znova_uloz_FPLM:= do_item__NEXT
   end;

{function znova_uloz_RPLM(FPL: PDmFPL; fn: pstring): byte; far;
   begin
     DB_oprav(FPL, FN^,db_mFPL_RIADKOV,@codeDB_FPLM,@codekey_FPLM,nil, dbattr_FPM);
     znova_uloz_RPL:= do_item__NEXT
   end;
}
{$I arc_format.inc}         { Kontrola integrity archivnych suborov }

procedure kontrola_archivu_FPLM;
    var   fn : string;
          P: PathStr; D: DirStr; N: NameStr; E: ExtStr;
          FPL : DmFPL;
          is : bool;

    begin
      fn:= najmladsi_subor(pathFPL_M,'*.'+ext_mFPL);
      {if konvertovat_archiv(pathFPL_M+fn,DB0) then}
         begin
          {$IFDEF DATA_BIN}
           konverzia_archivu (pathFPL_M,ext_mFPL,@znova_uloz_FPLM,sizeof(DmFPL),@disp_mFPL,db0_mFPL_RIADKOV,@_decodeDB0_FPLM);
           konverzia_archivu (pathARCH_FPL_M,ext_mFPL,@znova_uloz_FPLM,sizeof(DmFPL),@disp_mFPL,
                              db0_mFPL_RIADKOV,@_decodeDB0_FPLM
                             );
          {$IFDEF FDP_OPL}
{           konverzia_archivu(pathFPL_M,ext_KRL,
                             @znova_uloz_FPLM,sizeof(DmFPL),@disp_mFPL,
                             db0_mFPL_RIADKOV,@_decodeDB0_FPLM
                            );
           konverzia_archivu(pathARCH_FPL_M,ext_KRL,
                             @znova_uloz_FPLM,sizeof(DmFPL),@disp_mFPL,
                             db0_mFPL_RIADKOV,@_decodeDB0_FPLM
                            );

           if konvertovat_archiv (get_fn_mFPL_RPL_let,DB0) then
              begin
                FSplit(fn,D,N,E);
                MoveFile(fn,D+N+'.0');
                fillchar(FPL,sizeof(FPL),0);
                do_items_DB(@znova_uloz_RPL,@fn,
                            @FPL,@disp_mFPL,
                            fn, db0_mFPL_RIADKOV,nil,@_decodeDB0_FPLM,nil,
                            nil
                           )
              end;}
          {$ENDIF}
         {$ENDIF}
         end;

      {if (dbattr_FPM=DBbin) and konvertovat_archiv (pathFPL_M+fn,DBtxt) then
         begin
           konverzia_archivu (pathFPL_M,ext_mFPL,@znova_uloz_FPLM,sizeof(DmFPL),@disp_mFPL,db_mFPL_RIADKOV,@_decodeDBT_FPLM);
         end;}
    end;
