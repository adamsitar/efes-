    type  TGraphMode = (_EGA,_VGA,_VESA,_SVGA,_TIGA);

          Tcolor = record
            r,g,b:byte;
          end;
          Tpaleta = array[0..255] of Tcolor;


    const GraphMode: TGraphMode =
          {$IFDEF SVGA}
            {$IFDEF VGA}
               _VGA;
            {$ELSE}
               _VESA{_SVGA};
            {$ENDIF}
          {$ELSE}
             _VGA;
          {$ENDIF}

          JAS : bool = false;


    var   P256        : Tpaleta;
          MaxColor    : word;     { The maximum color value available }
