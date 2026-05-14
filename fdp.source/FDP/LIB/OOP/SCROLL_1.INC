{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollBar                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TScrollBar.Init(_Owner: PGroup; x,y, dy: int;
                            _pos_en, _stranka, _sam: bool
                           );
      begin
        inherited Init(_Owner, x,y,SCROLL_BAR__SIRKA,dy);
        lo:= 0; hi:= 0; top:= -1; pos:= 0;
        MCursor:= SIPKA;
        pos_en:= _pos_en; stranka:= _stranka; sam:= _sam;
        smer:= true; posun:= 0;
        za_posl_en:= false; {true;}
        zn_vys:= ZNACKA__VYSKA; bg:= {$IFDEF EGAVGA}darkgray{$ELSE}clBUTTON_COLOR-2{$ENDIF};
        ReInit(x0,y, 0,dy)
      end;

procedure TScrollBar.Draw;
    var   bp : bool; xl,yl : int;
    begin
      if not visible then Exit;
      m_off(bp, xl,yl);
      if sam then BGIgraph.Button(x0,y0,x1,y1,bg,btSmall,btON);
      icArrowUp  (x0+dxAr,y0+dyAr, btOFF);
      icArrowDown(x0+dxAr,y1-dyAr, btOFF);
      draw_pos;
      m_on(bp, xl,yl)
    end;


procedure TScrollBar.HandleEvent(var _Event: TEvent);
    var   _pos, m_pos : int; xl,yl : int;
          cez, xAr, yUp, yDown, x0pos, x1pos: int;
          koef   : real;
          kbXXXX : char;
          bp: bool;

    label X;
    begin { TScrollBar.HandleEvent }

      if (_Event.What and evMessage)<>0 then
         if isCommand(_Event,cmScrollerChanged) then receive__scroll_mail(lo,hi,top,pos)
         else Exit;

      if not visible then Exit;
      xAr:= x0+dxAr; yUp:= y0+dyAr; yDown:= y1-dyAr; x0pos:= x0+dx0pos; x1pos:= x0+dx1pos;
      _pos:= pos;

      if (_Event.What and evMouse <> 0) then
         if isClicked(_Event) then
            with _Event do begin
             { Scroll bar kliknuty ? vyhodnotenie novej pozicie }
               if inRectangle(M.x,M.y, x0+2,yUp+3,x1-2,yDown-3) then
                  begin
                    koef := ((M.y+zn_vys div 2 - yUp-3)/Maximum(yDown-yUp-6,1));
                    if not smer then koef:= 1-koef;
                    m_pos:= N(trunc(N(top+posun) * koef));
                    if not set__scroll_pos(lo,hi, pos, top,m_pos, za_posl_en,false) then goto X
                  end
             { Stlacena sipka ? vyhodnotenie polohy stisku }
               else begin
                      if inRectangle(M.x,M.y, x0+2,yUp-5,x1-2,yUp+2) then kbXXXX:= kbUp { sipka hore kliknuta }
                      else if inRectangle(M.x,M.y, x0+2,yDown-2,x1-2,yDown+5) then kbXXXX:= kbDown { sipka dole kliknuta }
                           else Exit;
                      if not set_scroll_par(kbXXXX, lo,hi, pos,top,cez, pos_en or (not stranka), smer, za_posl_en,false) then
                         goto X
                    end
            end
         else Exit;

      if (_Event.What and evKeyboard <> 0) then
          begin
            if not (     PView(Owner)^.Active
                     and set_scroll_par(_Event.Key, lo,hi,pos,top, cez, pos_en or (not stranka), smer, za_posl_en,false)
                   ) then Exit
          end;

      m_off(bp, xl,yl);
      if (_pos < pos) then icArrowDown(xAr, yDown, btON);
      if (_pos > pos) then icArrowUp(xAr, yUp, btON);
      draw_pos;
      if not isCommand(_Event,cmScrollerChanged) then
        { volanie vlastnika, ten zavola vlozeny objekt Scroller,
          ktory vyberie schranku (na hlasenie cmScrollBarClicked)
          a odroluje vypis ... } Mail(Owner, cmScrollBarClicked, One, @lo,4*SizeOf(int));
      if (_pos < pos) then icArrowDown(xAr, yDown, btOFF);
      if (_pos > pos) then icArrowUp(xAr, yUp, btOFF);
      m_on(bp, xl,yl);

      kb_clear;

      X: ClearEvent(_Event)
    end; { TScrollBar.HandleEvent }


procedure TScrollBar.ReInit(x,y,dx,dy: int);
    begin
      XY(x,y,SCROLL_BAR__SIRKA,dy);
    end;

{procedure TScrollBar.resize(x,y,dy: int);
    begin
      reinit(x,y,dy);
      Draw
    end;}

procedure TScrollBar.param(_lo,_hi,_top,_pos: int; _draw: bool);
    begin
      lo:= _lo; hi:= _hi; top:= _top; pos:= _pos;
      if _draw then draw_pos
    end;

{
nastavi poziciu znacky v rolovacom stlpci
}
procedure TScrollBar.draw_pos;
    var   zn_off      : int;  { posun znacky oproti zaciatku  }
          zn_y0,zn_y1 : int;  { suradnice znacky              }
          bp : bool; xl,yl : int;
    begin
      zn_vys:= (y1-y0 - ((dyAr+3) shl 1)) div Maximum(top+1,1); { vyska scrollovacej znacky }
      if top>0 then zn_vys:= Maximum(ZNACKA__VYSKA,zn_vys);
      if not visible then Exit;

      zn_off:= trunc(scroll_pos*(y1-y0-2*dyAr-6-zn_vys)); { relativna poloha znacky }
      if smer then zn_y0:= y0+dyAr+3 + zn_off
      else zn_y0:= y1-dyAr-3 - zn_off-zn_vys;
      zn_y1:= minimum(zn_y0 + zn_vys, y1-dyAr-3);

      m_off(bp, xl,yl);
      FillWin(x0+2,y0+dyAr+3,x1-2,y1-dyAr-3,bg);
      BGIgraph.Button(x0+dx0pos,zn_y0,x0+dx1pos,zn_y1,clBUTTON_COLOR,btSmall,btOFF);
      m_on(bp, xl,yl);
    end; { TScrollBar.draw_pos }

{
vrati relativnu polohu <0,1>
}
function TScrollBar.scroll_pos: real;
   begin
     if (top>0) then scroll_pos:= N(Minimum(pos,top))/top
     else scroll_pos:= 0;
   end; { TScrollBar.scroll_pos }


