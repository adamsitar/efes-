 procedure TList.HandleEvent(var _Event: TEvent);
     var   k : char;
           cez : int;
     label _1;
     begin
       inherited HandleEvent(_Event);
       if not (((_Event.What and evMouse)<>0) or (_Event.What = evKeyDown)) then Exit;

       if _Event.What = evKeyDown then k:= _Event.Key
       else k := m_to_kb(_Event.M);
       ClearEvent(_Event);

       case UpCase(k) of

         kbEnter : SetCommand (_Event,cmOK);
         kbEsc   : SetCommand (_Event,cmClose);

         'A'..'Z',
         '0'..'9': ;

         else _1 : if set_scroll_par(k, lo,hi,poz,top,cez, true,true,false,false) then
                      begin
                        if (DelChar(get(poz),set_)='') or (tit^[poz]) then
                           begin
                             if k in [kbUp,kbPgUp,kbHome] then
                                if poz=0 then k:= kbDown
                                else k:= kbUp
                             else if poz=top then k:= kbUp
                                  else k:= kbDown;
                             goto _1;
                           end;
                        List
                      end
       end
     end;


 procedure TList.Draw;
     var   bp : bool;
           xl,yl : int;
     begin
       m_off(bp, xl,yl);
       BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR, btNorm, btOFF);
       on_off(x0+3,y0+3,x1-3,y1-3, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btON);
       {ClrWin(x0+5,y0+5,x1-5,y1-5,0);}
       List;
       m_on(bp, xl,yl);
     end;


 procedure TList.List;
     var   bp : bool;
           i, xl,yl : int;
     begin
       m_off(bp, xl,yl);
       i:= lo;
       while (i<=top) and (i<=hi) do
         begin
           item_write(i);
           Inc(i)
         end;
       FillWin(x0+6, y0+6 + (i-lo)*item_dy, x1-6, y1-6, clBUTTON_COLOR);
       m_on(bp, xl,yl);
     end;


 function  TList.data_write(i: int): string;
    begin
      data_write:= get(i)
    end;

 procedure TList.item_write(i: int);
     var   y: int;
     begin
       y:= y0+9 + (i-lo)*item_dy;
       if i=poz then
          begin
            BGIgraph.button(x0+6, y-3, x1-6, y+item_dy-4, ab, btSmall, btON);
            SetColor(at)
            {$IFDEF SPEA}; SetBkColor(ab) {$ENDIF}
          end
       else begin
              FillWin(x0+6,y-3,x1-6, y+item_dy-4, b);
              SetColor(t)
              {$IFDEF SPEA}; SetBkColor(b) {$ENDIF}
            end;
       OutTextXY(x0+10,y+dy_ed-1,data_write(i){+' '})
     end;


 function lst_MAX_ITEMs: byte;
    begin
    { vrati maximalny pocet zobrazenych poloziek listu
    }
      lst_MAX_ITEMs:= ord(GraphMode)*2+5;
    end;
