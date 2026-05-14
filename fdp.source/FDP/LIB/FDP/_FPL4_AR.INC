 function znova_uloz_FPL4(FPL: PFPL4; p: pointer): byte; far;
    var   res : string;
          i,x,y : int;
    begin
      x:= wherex; y:= wherey;
      if x>2 then writeln;
      x:= wherex; y:= wherey;
      write('Converting '+FPL^._7+'...');
      _decode_FPL4 (FPL^,false,res);
      write(' och, done.');
      DB_oprav(FPL,
               get_DBfn(FPL^.date, pathFPL, extFPL),
               db_FPL4_RIADKOV,@codeDB_FPL4,@codekey_FPL4,
               @dbchg_FPL4, dbattr_FPL4
              );
      gotoxy(x,y); clreol; gotoxy(x,y);
      znova_uloz_FPL4:= do_item__NEXT
    end;

 procedure kontrola_archivu_FPL4 (attr: byte; riadkov: byte; decode: pointer);
     var   fn  : string;
           FPL : DFPL4;

     begin
       fn:= najmladsi_subor (pathFPL,'*.'+extFPL);
       if (attr=$FF) or konvertovat_archiv (pathFPL+fn,attr) then
          begin
            konverzia_archivu(pathFPL,extFPL,
                              @znova_uloz_FPL4,sizeof(DFPL4),@disp_FPL4,
                              riadkov,decode
                             );
          end;

       fn:= najmladsi_subor (pathARCH_FPL,'*.'+extFPL);
       if (attr=$FF) or konvertovat_archiv (pathARCH_FPL+fn,attr) then
          begin
            konverzia_archivu(pathARCH_FPL,extFPL,
                              @znova_uloz_FPL4,sizeof(DFPL4),@disp_FPL4,
                              riadkov,decode
                             );
          end;
     end;


