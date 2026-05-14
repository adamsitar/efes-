function znova_uloz_FPLC(FPL: PDcFPL; p: pointer): byte; far;
   var   B: TsBod; h : byte;
   begin
     if is_OB(FPL^.start.kod,B,true) and (FPL^.start.h<>0) then h:= FPL^.start.h
     else if (FPL^.bodov>=0) then h:= FPL^.trat[0].h
     else h:= BIOS.hour;
     DB_oprav(FPL,pathFPL_C+get_PLANhod(FPL^.date.d,FPL^.date.m,FPL^.date.r, h),
              db_cFPL_RIADKOV,@codeDB_FPLC,@codekey_FPLC,
              @dbchg_cFPL, dbattr_FPC
             );
     znova_uloz_FPLC:= do_item__NEXT
   end;


procedure kontrola_archivu_FPLC(attr: byte; riadkov: byte; decode: pointer);
    var   fn  : string;
          FPL : DcFPL;
    begin
     {$IFDEF DATA_BIN}
      fn:= najmladsi_subor (pathFPL_C,'*.*');
      if konvertovat_archiv (pathFPL_C+fn,attr) then
         begin
           konverzia_archivu(pathFPL_C,'*',
                             @znova_uloz_FPLC,sizeof(FPL),@disp_cFPL,
                             riadkov,decode
                            );
         end;
      fn:= najmladsi_subor (pathARCH_FPL_C,'*.*');
      if konvertovat_archiv (pathARCH_FPL_C+fn,attr) then
         begin
           konverzia_archivu(pathARCH_FPL_C,'*',
                             @znova_uloz_FPLC,sizeof(FPL),@disp_cFPL,
                             riadkov,decode
                            );
         end;
     {$ENDIF}
    end;
