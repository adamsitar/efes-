{
  podfarbenie stripu podla smeru letu
}
procedure strip_frame(_x,_y, _dx,_dy: int; c1,c2: byte);
    var   _x5: int;
    begin
      _x5:= _x+2; inc(_x,_dx);
      SetColor(c1);
      Line(_x5,_y   ,_x,_y);
      Line(_x5,_y+1 ,_x,_y+1);
      if not lineSTRIP then Line(_x5,_y+dy_strip_[lineSTRIP]-2,_x,_y+dy_strip_[lineSTRIP]-2);
      SetColor(c2);
      if not lineSTRIP then Line(_x5,_y+2 ,_x,_y+2);
      inc(_y,_dy);
      Line(_x5,_y-1,_x,_y-1);
      Line(_x5,_y,_x,_y)
    end;

function  is_plani___(p: pchar; m,r,k: int): bool;
   var    i,j : int;
          b   : bool;
   begin
     {if (r<k) then k:= getPstritems(p,setNL+setNL_);
     if r < k then
        begin
          j:= m;
          while (j>r) and (cut_(getPstr(p,j,setNL+setNL_))='') do dec(j);
          is_plani___:= j>r
        end
     else is_plani___:= false}
     if (r<k) or (k=-1) then is_plani___:= r < get_data_lines_i_(p)
     else is_plani___:= false
   end;


procedure strip_lines(x,y: int; pocet_znakov: Ppocet_znakov; p1,p2: pchar);
    var   i,j, riadkov, znakov, z,k,o: int;
          t,p : string;
          s   : array[0..3] of string;
    begin
      znakov:= pocet_znakov^[miniSTRIP];
      for i:= 0 to 3 do s[i]:= '';

      t:= replchar(strpas(p1),setNL+setNL_,' ');
      riadkov:= 0; i:= 0;
      while (i<length(t)) and (riadkov<4) do
        begin
          z:= Minimum(znakov, length(t)-i);
          p:= Copy(t,i+1, z);
          o:= 0;
          if (i+z < length(t)) then while (o<=z) and (p[Maximum(z-o,1)]<>' ') do inc(o);
          if o<=znakov then z:= z-o;

          s[riadkov]:= copy(t,i+1, z);
          inc(i,z);                     { riadkov*znakov }
          if o>znakov then
             begin
               s[riadkov]:= cut_(copy(s[riadkov],1,length(s[riadkov])-3))+'...';
               while (i <= length(t)) and (t[i] <> ' ') do inc(i);
             end;

          inc(riadkov);
        end;

      if (i<length(t)) then s[riadkov-1]:= cut_(copy(s[riadkov-1],1,znakov-3))+'...'
      else if riadkov<4 then
              begin
                t:= replchar(strpas(p2),setNL+setNL_,' ');
                if length(t)>znakov then t:= cut_(copy(t,1,znakov-3))+'...';
                s[3]:= t;
              end;

      {$IFDEF SPEA} SetTextStyle(BIT8x8, 0,0); {$ENDIF}
      dec(y,2);
      setcolor(citem);
      if riadkov<4 then
         begin
           inc(y,4);
           for j:= 0 to riadkov-1 do outtextxy(x,y+j*dy_ch,s[j]);
           y:= y+6+2*dy_ch
         end
      else begin
             for j:= 0 to riadkov-1 do outtextxy(x,y+j*dy_ch,s[j]);
             y:= y+3*dy_ch
           end;
      {if i >= length(t) then inc(y,2); outtextxy(x,y,s[3]) }
    end;


procedure strip_pozn(x,y: int; pocet_znakov: Ppocet_znakov; p: pchar);
    var   i,j, riadkov, znakov, z,k,o: int;
          s: string;
    begin
      znakov:= pocet_znakov^[miniSTRIP];

      setcolor(citem); {$IFDEF SPEA} SetTextStyle(BIT8x8, 0,0); {$ENDIF}
      riadkov:= 0;
      for i:= 1 to get_lines_i_(p) do
        begin
          s:= get_line_i(p,i);
          if cut_(s)='' then continue;
          if length(s)>znakov then s:= copy(s,1,znakov-3)+'...';
          outtextxy(x,y+riadkov*dy_ch,s);
          inc(riadkov);
          if riadkov>3 then break
        end;
    end;


function _is_mini_strip(m: T_strip): T_strip;
   var   res: bool;
   begin
     if m=full_strip then
        begin
          if 50 + dx_strip_[m] > MaxX-btmdXY.x0-btmdXY.x1 then m:= short_strip;
        end;
     if m=short_strip then
        begin
          if 50 + dx_strip_[m] > MaxX-btmdXY.x0-btmdXY.x1 then m:= mini_strip;
        end;
     _is_mini_strip:= m;
   end;

function dx_sc_strip(m: T_strip): int;
   begin
     dx_sc_strip:= dx_strip_[_is_mini_strip(m)];
   end;

function dy_sc_strip: int;
   begin
     dy_sc_strip:= dy_strip_[false]
   end;


