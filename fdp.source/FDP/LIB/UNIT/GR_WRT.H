    const {$IFDEF BGI}
            dx_ch  : byte = 8;  { velkost aktualneho fontu }
            dy_ch  : byte = 8;

            dy_bt         = -6; { posun v button }
            dx_ed         = 0;  { posun pre edit dany LeftText,UpperText }
            dy_ed         = 0;
            dy_crs        = 2;  { curzor pre editaciu }
          {$ENDIF}

          {$IFDEF SPEA}
            dx_ch  : byte = 8;
            dy_ch  : byte = 8;

            dy_bt         = 8;
            dx_ed         = -1;
            dy_ed         = 8;
            dy_crs        = 1;
          {$ENDIF}
