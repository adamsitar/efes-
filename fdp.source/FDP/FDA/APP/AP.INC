
{$IFDEF CONNECT_TO_AFTN}

procedure _info_aftn(x0,y0,x1,y1: int; p: pointer); far;
    begin
      bgigraph.button(x0,y0,x1,y1,clBUTTON_COLOR-1,btSmall,btON);
      inc(x0,dx_ed); inc(y0,dy_ed);

      (*
      Write_   (x0+20, y0+15, 'FIR CODE', clGRb);
      OutTextXY(x0+20, y0+30, 'AFTN WP ');

      Write_   (x0+140,y0+15, strpas(aftnMSG^.adr_FIR),clGRd);
      OutTextXY(x0+140,y0+30, strpas(aftnMSG^.adr_AFTN));

      Write_   (x0+20, y0+50,'ICAO SSR', clGRb);
      {$IFDEF GOST}
      OutTextXY(x0+20, y0+60,'GOST SSR');
      {$ENDIF}
      Write_   (x0+140,y0+50,IntToStr(SSRcodes^.iSSRlo,4,0)+'-'+IntToStr(SSRcodes^.iSSRhi,4,0),clGRd);
      {$IFDEF GOST}
      OutTextXY(x0+140,y0+60,IntToStr(SSRcodes^.gSSRlo,5,0)+'-'+IntToStr(SSRcodes^.gSSRhi,5,0));
      {$ENDIF}

      Write_   (x0+20, y0+085,'EST', clGRb);
      OutTextXY(x0+20, y0+095,'SSR ENABLE');
      Write_   (x0+140,y0+085,IntToStr(aftnFPL^.dt_EST,3,1)+' min',clGRd);
      OutTextXY(x0+140,y0+095,IntToStr(SSRcodes^.SSR_NEXT_USE,3,1)+' min')
      *)

    end;

{$ENDIF}
