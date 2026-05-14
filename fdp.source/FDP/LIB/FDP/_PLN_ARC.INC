{ -------------------
  inicializacia
  -------------------
}

 function znova_uloz_PLN(PLN: PPLN; p: pointer): byte; far;
    var   res : string;
          i,x,y : int;
    begin
      x:= wherex; y:= wherey;
      if x>2 then writeln;
      x:= wherex; y:= wherey;
      write('Converting '+PLN^.idn+'...');
      save_PLN(PLN);
      write(' och, done.');
      gotoxy(x,y); clreol; gotoxy(x,y);
      znova_uloz_PLN:= do_item__NEXT
    end;

 procedure kontrola_archivu_PLN (attr: byte; riadkov: byte; decode: pointer);
     var   fn  : string;
           FPL : DPLN;

     begin
      {$IFDEF DATA_BIN}
       fn:= najmladsi_subor (pathFPL,'*.'+extPLN);
       if konvertovat_archiv (pathFPL+fn,attr) then
          begin
            konverzia_archivu(pathFPL,extPLN,
                              @znova_uloz_PLN,sizeof(DPLN),@disp_PLN,
                              riadkov,decode
                             );
          end;

       fn:= najmladsi_subor (pathARCH_FPL,'*.'+extPLN);
       if konvertovat_archiv (pathARCH_FPL+fn,attr) then
          begin
            konverzia_archivu(pathARCH_FPL,extPLN,
                              @znova_uloz_PLN,sizeof(DPLN),@disp_PLN,
                              riadkov,decode
                             );
          end;
      {$ENDIF}
     end;
