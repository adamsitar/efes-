procedure set_RGBcolor(var RGBc: Tcolor; r,g,b: byte);
    begin
      RGBc.r:= r; RGBc.g:= g; RGBc.b:= b
    end;

procedure init_RGB_SVGA;
    var   i: int;
    begin
    { standartne + seda }
      init_RGB_0_31;

    { inicializacia ostatnych farieb }
    { modra2 }
      for i:=  0  to  15 do set_RGBcolor(P256[i+32], 0, 10+i*12, 50+i*12);
    { modra1 }
      for i:=  0  to  15 do set_RGBcolor(P256[i+48], 0, (i*12), (i*12)+50); {i*9, (i+4)*9);}
    { modra }
      for i:=  0  to  15 do set_RGBcolor(P256[i+64], 0, 0, 50+i*12);
    { zelena1 }
      for i:=  0  to  15 do set_RGBcolor(P256[i+80], 0, (i*12)+50, (i*12));
    { zelena  }
      for i:=  0  to  15 do set_RGBcolor(P256[i+96], 0, 10+i*13, 0);
    { fialova }
      for i:=  0  to  15 do set_RGBcolor(P256[i+112],10+i*12, 0, 10+i*12);
    { cervena }
      for i:=  0  to  15 do set_RGBcolor(P256[i+128],10+i*15, 0, 0);
    { fialova }
      for i:=  0  to  15 do set_RGBcolor(P256[i+144],255,10+i*13, 0);
    { seda    }
      for i:=  0  to  15 do P256[i+239]:= P256[i+16];
    { biela   }
      for i:=  0  to   4 do set_RGBcolor(P256[255],255,255,255);
    end; { InitSVGAPalette }


procedure init_RGB_FDP(jas: byte);
    var   i: int;
    begin
    { standartne + seda }
      {$IFDEF B_W}
        set_RGBcolor(P256[Red], 200,200,200);
        set_RGBcolor(P256[LightRed], 230,230,230);
      {$ENDIF}

      init_RGB_0_31;

    { modra1 32 - 41 }
      for i:=  0  to  9 do set_RGBcolor(P256[i+32], 0, 10+(i+3*jas)*12, 10+(i+3*jas)*12);

     {$IFDEF MAPY_1.0}

         set_RGBcolor(P256[41], 0, 142+(3*jas)*12, 142+(3*jas)*12);
         set_RGBcolor(P256[42], 0, 166+(3*jas)*12, 166+(3*jas)*12);

       { modra  43 - 46 }
         set_RGBcolor(P256[43], 0, 0, 10+(3+3*jas)*16);
         set_RGBcolor(P256[44], 0, 0, 10+(5+3*jas)*16);
         set_RGBcolor(P256[45], 0, 0, 10+(7+3*jas)*16);
         set_RGBcolor(P256[46], 0, 0, 10+(9+3*jas)*16);

       { fialova 47 - 50 }
         for i:=  0  to  3 do set_RGBcolor(P256[i+47],10+(i*2+3+3*jas)*12, 0, 10+(i*2+3+3*jas)*12);

       { cervena 51 - 54 }
         set_RGBcolor(P256[51], 75+(1*jas)*12, 0, 0);
         set_RGBcolor(P256[52],120+(1*jas)*12, 0, 0);
         set_RGBcolor(P256[53],190+(1*jas)*12, 0, 0);
         set_RGBcolor(P256[54],235+(1*jas)*12, 0, 0);

     {$ELSE}

       { zelena1 42 - 51 } { 0, 10+(i+3*jas)*12+25, 10+(i+3*jas)*12 }
         for i:=  0 to 10 do set_RGBcolor(P256[i+42], 0, 10+(i+3*jas)*12+25, 10+(i+3*jas)*12);

       { modra 52 - 55   } { 0, 0, 10+(3+i*2+3*jas)*16 }
         for i:=  0 to 3  do set_RGBcolor(P256[i+52], 0, 15*i+35, {$IFDEF UA}10+{$ENDIF}10+(3+i*2+3*jas)*16);

       { fialova 56 - 59 } { 10+(i*2+3+3*jas)*12, 0, 10+(i*2+3+3*jas)*12 }
         for i:=  0 to 4  do set_RGBcolor(P256[i+56], 10+(i*2+3+3*jas)*12, 10*i+10, 10+(i*2+3+3*jas)*12);

     {$ENDIF}

    { kusovky }
     {$IFDEF RDP_ACCEPT}
        set_RGBcolor(P256[60], R60,G60,B60);
        set_RGBcolor(P256[61], R61,G61,B61);
     {$ELSE}
        set_RGBcolor(P256[60], 0,  98+(jas*40), 48+(jas*20));
        set_RGBcolor(P256[61], 0, 146+(jas*40), 96+(jas*20));
     {$ENDIF}

      set_RGBcolor(P256[62], 140, 140, 0);
      set_RGBcolor(P256[63], 200, 200, 0);

    { cFPL    }
      for i:= 64 to 127  do set_RGBcolor(P256[i],215, 210,  0);  {235,230}
    { mFPL    }
      for i:= 128 to 191 do set_RGBcolor(P256[i],  0, 200,200);
    { aFPL    }
      for i:= 192 to 255 do set_RGBcolor(P256[i],  0, 226,126)
    end; { InitBGIPalette }

{
  nastavenie (obnovenie) palety programu
}
procedure set_RGBpallete;
    var   i: int;
    begin
     {$IFDEF EGAVGA}
      {for i:= 0 to 31 do SetRGBPalette(i, (i)*2,(i)*2,(i)*2);}
     {$ELSE}
      set_RGBcolors(P256, 0,256)
     {$ENDIF}
    end;
