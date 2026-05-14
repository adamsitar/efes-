{ -------------------
  inicializacia
  -------------------
}

 function znova_uloz_FPS(FPS: PFPS; p: pointer): byte; far;
    var   res : string;
          i,x,y : int;
    begin
      x:= wherex; y:= wherey;
      if x>2 then writeln;
      x:= wherex; y:= wherey;
      write('Converting '+FPS^.fdr.idn+'...');
      DB_oprav (FPS, get_DBfn(FPS^.fdr.date, pathFPS,extFPS),
                db_FPS_RIADKOV,@codeDB_FPS,@codekey_FPS,
                @dbchg_FPS,dbattr_FPS
               );
      write(' och, done.');
      gotoxy(x,y); clreol; gotoxy(x,y);
      znova_uloz_FPS:= do_item__NEXT
    end;

 procedure kontrola_archivu_FPS (attr: byte; riadkov: byte; decode: pointer);
     var   fn  : string;
           FPL : DFPS;

     begin
      {$IFDEF DATA_BIN}
       fn:= najmladsi_subor (pathFPL,'*.'+extFPS);
       if konvertovat_archiv (pathFPL+fn,attr) then
          begin
            konverzia_archivu(pathFPL,extFPS,
                              @znova_uloz_FPS,sizeof(DFPS),@disp_FPS,
                              riadkov,decode
                             );
          end;

       fn:= najmladsi_subor (pathARCH_FPL,'*.'+extFPS);
       if konvertovat_archiv (pathARCH_FPL+fn,attr) then
          begin
            konverzia_archivu(pathARCH_FPL,extFPS,
                              @znova_uloz_FPS,sizeof(DFPS),@disp_FPS,
                              riadkov,decode
                             );
          end;
      {$ENDIF}
     end;

