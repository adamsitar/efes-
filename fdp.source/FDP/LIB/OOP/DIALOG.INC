const medzera = 4;

procedure message_split(_messp: PMess; _size: int;
                        _dx,_dy : int;
                        _title : string;
                        var mp: TMess; var ms: int;
                        var dx,dy : int
                       );
    var   dxr, dxm, i,j: int;
          s : string;
          p : pchar;
    begin
     { rozlozenie spravy tak, aby vosla na obrazovku
     }
      dxm:= minimum(MaxX-winDX{ - (MaxX div 4)},620); { kvoli MTK_2_PAGE }
      if _dx>0 then dx:= (_dx {shr 3})
      else dx:= dxm shr 3;
      mp[0]:= strpasnew(' ');
      ms:= 1; i:= 0;
      while (i<_size) and (ms<max_MessStr-1) do
        begin
          p:= _messp^[i];
          dxr:= strlen(p);
          if dxr<=dx then
             begin
               mp[ms]:= strnew(p);
               inc(ms)
             end
          else while (strlen(p)>0) and (ms<max_MessStr-1) do
                 begin
                   s:= copy(strpas(p),1,dx);
                   j:= length(s);
                   if (strlen(p)>dx) then
                      begin
                        while (j>0) and (s[j]<>' ') do dec(j);
                        if j=0 then j:= length(s)
                      end;
                   mp[ms]:= strpasnew(cut_(copy(s,1,j)));
                   inc(ms);
                   inc(p,j)
                 end;
          inc(i)
        end;
      mp[ms]:= strpasnew(' ');
      inc(ms);

      SetTextStyle(0, HorizDir, 1);
      dx:= TextWidth(_title);
      dxr:= 0; for i:= 0 to ms-1 do dxr:= Maximum(TextWidth(cut_(StrPas(mp[i]))),dxr);
      dx:= Minimum(Maximum(dx,dxr),dxm)+winDX;
      dx:= Maximum(dx,_dx);

      dy := Maximum(ms*(medzera+TextHeight('H')),_dy);
      inc(dy,btHEIGHT+20)
    end;

procedure _message_draw(x0,y0,x1,y1: int; mp: TMess; ms: int; cl,bk: byte);
    var   i,yl,yh: int;
          s: string;
    begin
      yl:= y0+btHEIGHT+20;
      yh:= yl+ms*(2+TextHeight('H'))+20;
      on_off(x0+10,yl,x1-10,yh,
             clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,
             btSmall, btOFF {TbtStat(ord(do_it<>nil))}
            );
      if ms>0 then FillWin(x0+12,yl+2,x1-12,yh-2,bk);
      {$IFDEF SPEA} SetBkColor(bk); {$ENDIF}
      for i:= 0 to ms-1 do
          begin
            s:= StrPas(mp[i]);
            if length(s) > (x1-x0-winDXoff) shr 3 then s:= copy(s,1,(((x1-x0-winDX) shr 3)-3))+'...';
            Write_(x0 + winDX div 2,
                   y0 + winHEIGHT+10+dy_ed+i*(medzera+TextHeight('H')),
                   s,cl
                  )
          end
    end;

