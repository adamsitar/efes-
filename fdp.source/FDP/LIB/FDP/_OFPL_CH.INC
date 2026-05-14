{ ---------------------------------
   zadne dvierka
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function  O_FPL.nastavenie_platnosti(zmena: bool): bool;
     begin
       zmena:= inherited nastavenie_platnosti(zmena);
       {$IFDEF SECTORS}
         if zmena then nastavenie_platnosti_v_sektore;
       {$ENDIF}
       nastavenie_platnosti:= zmena;
     end;

