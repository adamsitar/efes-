{$IFDEF SPEA}

  procedure set_RGBcolors(P: Tpaleta; od,pocet: word);
      var   i: int;
      begin
        for i:= od to od+pocet-1 do SPsetvlu(i, P[i].r,P[i].g,P[i].b)
      end;

  {
    standartne + seda
  }
  procedure init_RGB_0_31;
      var   i: int;
      begin
      { standartne }
        set_RGBcolor(P256[0],  0,0,0);      { black }
        set_RGBcolor(P256[1],  0,0,150);    { blue  }
        set_RGBcolor(P256[2],  0,150,0);    { green }
        set_RGBcolor(P256[3],  0,190,190);  { cyan  }
        set_RGBcolor(P256[4],  150,0,0);    { red   }
        set_RGBcolor(P256[5],  150,0,150);  { magenta }
        set_RGBcolor(P256[6],  120,60,0);   { brown   }
        set_RGBcolor(P256[7],  225,225,225);{ light gray }
        set_RGBcolor(P256[8],  100,100,100);{ dark gray  }
        set_RGBcolor(P256[9],  0,0,200);
        set_RGBcolor(P256[10], 0,200,0);
        set_RGBcolor(P256[11], 0,225,225);
        set_RGBcolor(P256[12], 200,0,0);    { light red  }
        set_RGBcolor(P256[13], 200,0,200);  { light magenta }
        set_RGBcolor(P256[14], 255,255,100);{ yellow }
        set_RGBcolor(P256[15], 255,255,255);

      { seda }
        for i:= 0 to 14 do set_RGBcolor(P256[16+i],i*15,i*15,i*15);
        set_RGBcolor(P256[31],255,255,255);
      end;
{$ENDIF}