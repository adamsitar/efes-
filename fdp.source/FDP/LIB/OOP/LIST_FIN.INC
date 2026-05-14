{ function TList.is_initialized: bool;
    var   ini : bool;
    begin
      ini:= (top=-1) and (not is_init);
      if ini then InitData;
      is_initialized:= ini
    end;

 procedure TList.was_initialized(ini: bool);
     begin
       if ini then DoneData;
     end;
}

{ otvori okno pre vyber polozky, vrati vybranu
}
 function TList.get_item(x,y: int): string;

    var   _Event     : TEvent;
          dx,dy, i,p : int;
          res,s,u    : string;

          ini,mp,bp,bp2 : bool;
          xl,yl : int;

    label endp;

    begin
      get_item:= '';
      if lst=nil then Exit;

      ini:= is_initialized;
      bp2:= is_list; is_list:= true;
      if not ini then InitList;
      if (top=-1) then goto endp;  { Mp:= mouse_status.stat;}

      lo := lst^.lo;
      hi := Minimum(top,lst_MAX_ITEMs) + lo;
      poz:= Minimum(lst^.poz,hi);

      dx:= 10 + ({' '+}max_len shl 3 {+' '}) + 10;
      item_dy:= TextHeight('H') + 4; dy:= 6 + item_dy*(hi-lo+1) + 6;
      XY(x,y,dx,dy);

      mp:= MouseMotionEvents; MouseMotionEvents:= true;
      bp:= m_kresli; if bp then begin m_hide; m_kresli:= false end;

      Run(_Event);
      if bp then begin m_show; m_kresli:= true end;
      MouseMotionEvents:= mp;

      if isCommand(_Event,cmOK) then
         begin
           s:= get(poz);
           if pos=0 then
              begin
               { vsetko }
                res:= GetStr(s,1,setKomen);
              end
           else if (pos>0) and (pos<abs(lst_posledna)-1) then
              begin
               { pos    }
                res:= GetStr(s,pos,setOddel+odd+setKomen);
              end
           else if (pos=lst_posledna) or (pos=abs(lst_posledna)) then
              begin
                u:= GetStr(s,1,setKomen);
                p:= getstritems(u,setOddel+odd+setKomen);
                res:= GetStr(s,p,setOddel+odd);
              end
           else if (pos=lst_vsetky_polozky) or (pos=abs(lst_vsetky_polozky)) then res:= GetStr(s,1,setKomen)
           else if (pos=lst_cely_riadok) or (pos=abs(lst_cely_riadok)) then res:= s
           else begin
                 { predposlItem }
                  res:= '';
                  for i:= abs(pos) to getstritems(s,setOddel+odd+setKomen) do
                    begin
                      u:= GetStr(s,i,setOddel+odd+setKomen); u:= cut_(u);
                      res:= res+' '+u
                    end
                end;
           get_item:= cut_(res)
         end;

      lst^.lo := lo;
      lst^.poz:= poz;

      endp: if not ini then DoneList;
      is_list:= bp2
    end;


 function TList.is_nil(i: int): bool;
    begin
      is_nil:= tit^[i] or (cut_(get(i))='')
    end;


{ skontroluje, ci polozka s je v zozname
}
 function TList.is_in(s: string): int;
    var   i,j,k, riadok,pos_: int;
          si,s0,s1: string;
          ini: bool;

    label endp;

    begin
      is_in:= -1;
      s:= cut_(cs_ascii_str(s));
      if s='' then Exit;

      ini:= is_initialized;
      if not ini then InitList;

      if pos=3 then pos_:= 1
      else pos_:= pos;
      i:= 0;
      while i<=top do
        begin
          if not tit^[i] then
             begin
               si:= get(i);
               s0:= getstr(si,1,setKomen);
               k:= GetStrItems(s0, setOddel+odd);
               if pos=lst_vsetky_polozky then
                  begin
                  { rovna sa polozka celej polozke zoznamu ?
                  }
                    s1:= ''; for j:= 1 to k do s1:= s1 + ' ' + GetStr(s0,j, setOddel+odd);
                    if eq_str(s,s0) or eq_str(s,s1) then break{goto endp}
                  end
               else if pos=lst_aspon_1_polozka then
                  { rovna sa polozka apon jednej polozke zo zoznamu ?
                  }
                  for j:= 1 to k do
                    begin
                      s1:= GetStr(s0,j, setOddel+odd);
                      if eq_str(s,s1) then break{goto endp}
                    end
               else begin
                  { rovna sa polozka apon polozke na pozicii "i" zoznamu ?
                    ind=-3 or ind>=0
                  }
                      s1:= GetStr(s0,pos_,setOddel+odd);
                      if eq_str(s,s1) then break{goto endp}
                    end
             end;
          inc(i)
        end;

      if i>top then i:= -1;
      if not ini then DoneList;
      is_in:= i;
    end;


{ vyberie polozku
}
 function TList.get_line(s: string; _pos: int; _ind: pint): string;
    var   p,i : int;
          ini : bool;
    begin
      get_line:= '';
      p:= pos; pos:= _pos;

      ini:= is_initialized;
      if not ini then InitList;

      if (top>-1) then
         begin
           i:= is_in(s);
           if i>-1 then get_line:= get(i);
           if _ind<>nil then _ind^:= i;
         end;

      pos:= p;
      if not ini then DoneList;
    end;


{ vrati komentar polozky
}
 function TList.get_comment(s: string; _ind: pint): string;
    var   f  : text;
          s1,si : string;
          _pos,_pos0,p,i: int;
          ini : bool;
    begin
      get_comment:= '';
      if Exists(fname)<>0 then Exit;

      ini:= is_initialized;
      if not ini then
         begin
           _pos0:= pos;
           pos:= lst_cely_riadok;
           InitList;
         end;

      if top>-1 then
         begin
           _pos:= pos; pos:= 1;
           p:= is_in(s);
           pos:= _pos;
           if p=-1 then Exit;

           if (pos<>lst_cely_riadok) and (pos<>lst_cely_riadok_) then
              begin
                s1:= '';
                Assign(f,fname); Reset(f);
                i:= 0; while (not Eof(f)) and (i<p) do
                  begin
                    ReadLn(f,si);
                    if (si[1] in setKomen) or ((i=0) and (si='')) or (not is_to_add(si)) then continue;
                    if i=p then
                       begin
                         s1:= cut_(delchar(si,[#0..#31]));
                         break;
                       end
                  end;
                Close(f)
              end
           else s1:= get(p);

           if s1<>'' then
              begin
                get_comment:= s1;
                if _ind<>nil then _ind^:= p;
              end
         end;

      if not ini then
         begin
           DoneList;
           pos:= _pos0;
         end;
    end;
