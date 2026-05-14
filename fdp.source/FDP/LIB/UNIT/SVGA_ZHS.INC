const krok   : int = 0;
var   Paleta : TPaleta;

function Rozsviet: bool;
   begin
     if krok<>0 then
        begin
          krok:= 0;
          set_RGBpallete;
          ZHASINA := false; ZHASNUTE:= false;
          Rozsviet:= true
        end
     else Rozsviet:= false;
     ROZSVIETENE:= absTime
   end;

procedure Zhasinaj;
    var   i, b: int;
    begin
      ZHASINA:= true;
      if krok=0 then Paleta:= P256;
      inc(krok);
      for i:= 1 to 255 do
        with Paleta[i] do
          begin
            r:= N(r-1);
            g:= N(g-1);
            b:= N(b-1);
          end;
      set_RGBcolors(Paleta, 1,255);
      if krok>=Z_X then
         begin
           ZHASNUTE:= true;
           ZHASINA:= false
         end
    end;

procedure Zhasni;
    const semaphor: bool = false;
    begin
      if semaphor then Exit;
      semaphor:= true;
      repeat
        Zhasinaj;
        CheckProcesses
      until ZHASNUTE or (not ZHASINA);
      semaphor:= false
    end;


procedure JasBGI(jas: byte);
    begin
      init_RGB_FDP(jas);
      set_RGBpallete
    end;


procedure check_display;
    var   r: real;
    begin
      if ZHASINANIE and (not ZHASNUTE) then
         begin
           r:= ZHASNI_PO; r:= r*60+ROZSVIETENE;
           if (r <= absTime) then
              if absTime>5+r then ROZSVIETENE:= absTime
              else Zhasinaj
         end
    end;
