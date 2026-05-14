{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TBox                                                     €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TBox.Init(_Owner: PGroup;
                       x,y, dx,dy: int;
                      _kbHot: char; _cmXXXX: word;
                      _itemd: PForms; _items: byte;
                      _abg,_atext{,_form}: byte;
                      _adr_var: pointer;
                      _init_form, _check_func, _done_form: pointer;
                      _ins,_alone, _copy,_clear: bool
                     );
      begin
        Win:= nil;
        btOK:= nil; btCa:= nil;
        {$IFDEF A36YKA} btA36:= nil; {$ENDIF}
        xp:= nil; yp:= nil;
        inherited Init(_Owner, x,y, dx,dy);
        slow_done_app:= true;

        {$IFDEF EGAVGA} if _abg=darkgray then _abg:= black; {$ENDIF}
        kbHot:= _kbHot; cmXXXX:= _cmXXXX; MCursor:= SIPKA;

       { buffery pre editaciu
       }
        itemd_adr:= _itemd;
        {arch:= false;}
        copy_of_form:= _copy;
        if copy_of_form then
           begin
             _itemd:= new_form(_itemd,_items);
             if _clear then clear_form(_itemd,_items,nil)
           end;
        items := _items; itemd := _itemd;
        GetMem(itemv,SizeOf(TFPar)*items);
        ind:= 0;

       { farby }
        if (_abg<>_atext) then
           begin
             abg:= _abg; atext:= _atext; {form:= _form;}
           end
        else begin
               abg:= cbBack; atext:= cbText; {form := cbForm;}
             end;

        tit:= 0;
        dole:= 0;
        ins:= _ins;
        first_pos:= 0;

        viewer:= false;

       { pomocne premenne        }
        item_in_button:= false;

       { adresy }
        adr_var   := _adr_var;
        disp_proc := nil;
        adr_par   := nil;

        init_form := _init_form;
        check_func:= _check_func;
        done_form := _done_form;

        init_list := nil;
        clear_list:= false;
        sort_list := false;
        done_list := nil;

        alone:= _alone;
        pswrd:= false; upcas:= false;
        corr_res:= false; clear:= true;

        if alone then
           begin
             init_local_var;
             active:= false
           end
        else active:= true;

        last_kbhit:= absTime;

        is_update:= false;
        is_cancel:= false;
      end; { TBox.Init }


function  TBox.init_local_var: bool;
    var   nul_form, nil_form, first_frm: int;
          k: int;
    begin
      init_formular;
      init_local_var:= true;

      k:= 0; first_frm:= -1;
      { IFDEF DEBUG}
        nul_form:= -1; nil_form:= 0;
      { ENDIF}
      while (k < items) { IFDEF DEBUG} and (nul_form=-1) { ENDIF} do
        begin
          if viewer then itemd^[k].legal:= @setNil;
          if itemd^[k].legal=nil then itemd^[k].legal:= @setNil;
          if itemd^[k].skip=nil  then itemd^[k].skip:=  @setNil;
         { IFDEF DEBUG}
           if strlen(itemd^[k].item)=0 then nul_form:= k;
           if nul_form<>-1 then break;
           {if itemd^[k].legal=@setNil then inc(nil_form);}
         { ENDIF}
          if itemd^[k].legal=@setNil then inc(nil_form);
          ind:= k;
          with itemv^[ind] do
            begin
              _lo:= 1; _hi:= 0; i:= 0;
              SetPBound(itemd^[ind].item,_lo,_hi,i,itemd^[ind].skip^);
              {SetPos;}
              MoveRight(0);
              if ins then last_char
            end;
          if (itemd^[k].legal<>@setNil) and (first_frm=-1) then first_frm:= k;
          inc(k);
        end;
      corr_res:= false;
      if (first_pos=0) and (first_frm<>-1) then first_pos:= first_frm;
      ind:= Limit(first_pos, 0,items-1, 0);
      prev_ind:= ind;
      (*{$IFDEF DEBUG}
        if nul_form<>-1 then RunError('Polozka formulara c.'+inttostr(nul_form,1,1)+' ma nulovu dlzku.');
        if (not viewer) and (nil_form=items) then RunError('Formular je setNil.');
      {$ELSE}
        init_local_var:= (viewer) or (not ((nul_form<>-1) or (nil_form = items)))
      {$ENDIF}*)
      init_local_var:= (viewer) or (not ((nul_form<>-1) or (nil_form = items)))
    end;


procedure TBox.set_location(var _x,_y, _mode: int);
    begin
      if ( TGraphMode(N(_mode)) <> GraphMode ) or (_x=-1) or (_y=-1) then
         begin
           _x:= InitX; _y:= initY;
           {if (_mode<>-1) then} _mode:= ord(GraphMode)
         end;
      xp:= @_x; yp:= @_y
    end;

procedure TBox.Centre;
    var   x,y: int;
    begin
      if (Win<>nil) and (xp<>nil) and (yp<>nil) then
        begin
          if (int(xp^)=initX) and (int(yp^)=initY) then
             begin
               x:= Win^.x0;  y:= Win^.y0;
               Win^.Centre;
               TView.MoveRel(Win^.x0 - x, Win^.y0 - y)
             end
          else begin
                 x:= int(xp^);  y:= int(yp^);
                 if move_reg(x,y, x,y, Win^.x0 - x,Win^.y0 - y)=2 then
                    begin
                      Win^.MoveRel (Win^.x0 - x, Win^.y0 - y);
                      TView.MoveRel(Win^.x0 - x, Win^.y0 - y)
                    end
               end
        end
    end;

procedure TBox.proc__Self_adr_var(p: pointer);
    begin
      if (adr_var<>nil) then Tproc_p2(p)(@Self,adr_var)
      else Tproc_p(p)(@Self)
    end;

{
 len pre init a done
}
procedure TBox.Run(var _Event: TEvent);
    var   bres,kblayout : bool;
    label X;
    begin
      kblayout:= is_kblayout; is_kblayout:= false;
      bres:= true;
      if alone then ScreenSave:= false
      else bres:= init_local_var;

      if bres then inherited Run(_Event)
      else corr_res:= false;

      if corr_res then
         begin
         { spracovanie vysledku }
           if (done_form<>nil) then proc__Self_adr_var(done_form)
           else done_formular;
         end;

      is_kblayout:= kblayout;
      ClearEvent(_Event)
    end; { TBox.Run }


function TBox.EndState(var _Event: TEvent): bool;
   var   res: bool;
   begin
     res:= inherited EndState(_Event);
     if res then
        begin
          if (isCommand(_Event,cmXXXX)) then
             begin
               res:= check_formular;
               corr_res:= res
             end
        end
     else res:= is_cancel;
     EndState:= res
   end;


procedure TBox.init_formular; { inicializacia formulara  }
    begin
      if clear and (init_form<>nil) then proc__Self_adr_var(init_form)
      else if clear_list then clear_form(itemd,items,nil)
    end;

procedure TBox.write_in_formular;
    begin
    end;

function  TBox.check_formular: bool; { kontrolna funkcia }
   begin
     if (not viewer) and (check_func<>nil) then
        begin
          if disp_proc<>nil then proc__adr_var(disp_proc,adr_var);
          if (adr_var<>nil) then check_formular:= TBFunc_p2(check_func)(@Self,adr_var)
          else check_formular:= TBFunc_p(check_func)(@Self)
        end
     else check_formular:= false
   end;

procedure TBox.done_formular; { akcia po spravnom zadani }
    begin
    end;


procedure TBox.RunList(_lst: PListDesc; _pos: int; _add: bool;
                       _filter: PBFunc_s;
                       _gets: PSFunc_s; _getpis: PSFunc_pis
                      );
    var   s, t,r,z : string;
          l,k : int;
    begin
      if viewer or (itemd^[ind].legal=nil) or (_lst=nil) then Exit;
      with itemd^[ind] do
        begin
          if init_list<>nil then proc__adr_var(init_list,adr_var);
          s:= _get_item(x0+dx+itemv^[ind].i*dx_ch{dx-11},y0+dy+10, _lst,[], _pos{lst_cely_riadok}, sort_list, _filter);
          t:= s;
          {s:= GetStr(GetStr(t,1,setKomen),_pos,setOddel);}
          if _getpis<>nil then s:= TSFunc_pis(_getpis)(@Self,ind,s)
          else if _gets<>nil then s:= TSFunc_s(_gets)(s);
          if upcas then s:= upstring(s);
          if done_list<>nil then proc__adr_var(done_list,adr_var);
          if s<>'' then
             begin
               k:= ind;
               if not _add then clear_item_i(ind);
               vloz_text(s);
               vlozeny_text(k,t)
             end
        end
    end;

procedure TBox.vlozeny_text(kde: int; s: string);
    begin
      { reakcia i na ostatne polia }
    end;

procedure TBox.form_copy;
    var   _itemd : PForms;
          _items : int;
    begin
      _itemd:= itemd; _items:= items;
      if copy_of_form then
         begin
           if copy_back then copy_form(_itemd,itemd_adr,items);
           disp_form(_itemd,_items);
           itemd:= nil
         end;
    end;


destructor TBox.Done;
     begin
       if Win<>nil then
          begin
            if xp<>nil then int(xp^):= Win^.x0;
            if yp<>nil then int(yp^):= Win^.y0;
          end;
       FreeMem(itemv,SizeOf(TFPar)*items);
       form_copy;       { neviem, preco je to na konci, lepsie by bolo pred }
       if disp_proc<>nil then proc__adr_var(disp_proc,adr_var);
       inherited Done;
     end;  { Tbox.Done }


procedure TBox.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);

      if alone then
         begin
          if bool(_Event.What=evMouseClick) then
             begin
               if (_Event.M.bt<>0) then
               if bool(_Event.M.bt and mbLeftButton) then SetKeyEvent(_Event,@Self,kbHot)
               else if bool(_Event.M.bt and mbRightButton) then SetKeyEvent(_Event,@Self,kbEsc)
             end;
           if isKey(_Event, kbHot) then SetCommand(_Event,cmXXXX)
           else if isKey(_Event, kbEsc) then SetCommand(_Event,cmCancel)
         end;

      case _Event.What of

      { kliknutie mysi     }
        evMouseClick, evMouseDouble : with _Event do
          if isClicked(_Event) then item_clicked(_Event)
          else Exit;

      { stacenie klavesy  }
        evKeyDown :
          begin
            SetPos;
            if not AcceptedKey(_Event.Key) then Exit;
            Write
          end

      else if      (    isCommand(_Event,cmList)
                    {or (     (not pswrd)
                        and  isCommand(_Event,cmXXXX)
                        and  (items=1)
                        and  (delchar(_it(ind),itemd^[ind].skip^+[' '])='')
                       )}
                   )
              and  (itemd^[ind].legal<>nil)
              and  (itemd^[ind].lst<>nil)  then
               with itemd^[ind] do RunList(lst, abs(pos), ins and (pos<0), nil,nil,nil)

           {$IFDEF A36YKA}
             else  if isCommand(_Event,cmA36YKA) then is_kblayout:= not is_kblayout
           {$ENDIF}

          { inak odchod       }
           else Exit
      end;
      ClearEvent(_Event);
    end; { TBox.HandleEvent }


procedure TBox.Draw;
    var   j: int;
          bp: bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      for j:= 0 to items-1 do WriteItem(j);
      Write;
      write_in_formular;
      m_on(bp, xl,yl);
    end; { TBox.Draw }


procedure TBox.ReDraw;
    begin
      if not alone then
         if not init_local_var then
            begin
              R_err:= true;
              Exit
            end;
      Draw
    end;


procedure TBox.Write;
    {const s: string = '';
          i: int    = -1;
          v: bool   = false;}
    var   dx_c : int;
          {s : string;}
          c : char;
    begin
      {if not (     (s=StrPas(itemd^[ind].item))
               and (i=itemv^[ind].i)
               and (v=ins)) then} dx_c:= WriteItem(ind);
      SetPos;
      {s:= StrPas(itemd^[ind].item);}
      {if DelChar(s,[' ']) <> '' then
         begin}
           with itemd^[ind] do with itemv^[ind] do
             begin
               c:= item[i];
               if pswrd and (c<>' ') then c:= '*';
               if active and (not viewer) then
                  show_cursor(x0+dx_c,y0+dy, TextWidth('W'),TextHeight('H'),dy_crs,0, i,0, c,ins, atext,abg)
             end
         {end;}
      {i:= itemv^[ind].i;
      v:= ins}
    end; { TBox.Write }


function TBox.WriteItem(_ind: int): int;
   var   s: string;
         x,y: int;
         bp: bool; xl,yl : int;
   begin
     m_off(bp, xl,yl);
     s:= StrPas(itemd^[_ind].item);
     if pswrd then
        for x:= 1 to length(s) do
            if (s[x]<>' ') and ((itemd^[ind].skip=nil) or (not (s[x] in itemd^[ind].skip^))) then
               s[x]:= '*';
     with itemd^[_ind] do
       begin
         x:= x0+dx; y:= y0+dy;
         {$IFDEF SPEA} { zmazania kurzora } FillWin(x-2,y-dy_crs,x+TextWidth(s)-2,y+TextHeight('H')+1, abg); {$ENDIF}
         WriteStr(x+dx_ed,y+dy_ed, s, atext,abg);
         WriteItem:= dx
       end;
     m_on(bp, xl,yl);
   end; { TBox.WriteItem }


procedure TBox.clear_item_i(i: int);
    begin
      delete_item(itemd^[i]);
      itemv^[i].i:= first_char_i(i){last_char_i(i)}
    end;

procedure TBox.clear_item;
    begin
      clear_item_i(ind)
    end;


procedure TBox.clear_items;
    var   i: int;
    begin
      clear_form(itemd,items,nil);
      for i:= 0 to items-1 do itemv^[i].i:= first_char_i(i){last_char_i(i)};
      ind:= minimum(items-1,1);
      MoveLeft(1);
      TBox.Draw
    end;

{
 ak bude vypisovat text, vrati true
}
procedure TBox.odsun_text;
    begin
      with itemv^[ind],itemd^[ind] do Move(item[i],item[i+1],_hi-i)
    end;

procedure TBox.vloz_text(s: string);
    var   is, i: int;
    begin
      is:= ind;
      for i:= 1 to length(s) do
        begin
          WriteKey(s[i]);
          if itemv^[ind].i=itemv^[ind]._hi then break
        end;
      Write
    end;


function TBox.EditingKey(key: char): bool;
   var   k : char;
   begin
     last_kbhit:= absTime;
     k:= keyb.upcase(key);
     if    (not (    ((k in itemd^[ind].legal^+[' ']) and (k in legal_keys))
                 {$IFDEF A36UKA}
                  or (mtkch_rus_to_lat(k) in itemd^[ind].legal^+[' '])
                 {$ENDIF}
                )
           )
        or (k in itemd^[ind].skip^)
        then begin
               EditingKey:= false;
               Beep(200,80);
               Exit
             end
     else begin
            EditingKey:= true;
            key:= kblayout(key);
            if upcas then key:= keyb.upcase(key);
            WriteKey(key)
          end
   end;

function TBox.AcceptedKey(key: char): bool;
   var   j : int;
         k : char;
   begin
     AcceptedKey:= false;
     case key of

       kbIns : ins:= not(ins);

     { mazanie znaku }
       kbDel,kbBS :
         with itemv^[ind] do begin
           if (key=kbBS) then
              begin
                if i=0 then Exit;
                MoveLeft(1);
                SetPos
              end;
           with itemd^[ind] do
             begin
               Move(item[i+1],item[i],_hi-i);
               item[_hi]:= ' '
             end
         end;

     { zmazanie celej polozky }
       kbCtrlDel : clear_item;

     { zmazanie vsetkych poloziek }
       kbAltDel  : clear_items;

     { posun kurzora po formulari }

     { - po polozke: }
       kbLeft  : MoveLeft(1);
       kbRight : MoveRight(1);
       kbHome  : with itemv^[ind] do i:= _lo;
       kbEnd   : begin
                   last_char;
                   MoveRight(1)
                 end;

     { - medzi polozkami: }
       kbCtrlLeft  : { naspat - dolava }
         with itemv^[ind] do begin
           i:= _lo;
           MoveLeft(1);
           with itemd^[ind] do while (i>0) and not(item[i-1] in skip^) do Dec(i)
         end;
       kbCtrlRight : { dopredu - doprava }
         with itemv^[ind] do begin
           i:= _hi;
           MoveRight(1);
           if i=_hi then i:= _lo
         end;
       kbCtrlHome : MoveRight(-itemv^[ind].i);   { na prvu     }
       kbCtrlEnd  :
         with itemv^[ind] do begin               { na poslednu }
           MoveLeft(-StrLen(itemd^[ind].item)+i);
           with itemd^[ind] do while not (item[i-1] in skip^) do Dec(i)
         end;

     { ZAPIS ZNAKU DO FORMULARA }
       else if not EditingKey(key) then Exit
     end;
     AcceptedKey:= true
   end; { TBox.AcceptedKey }


procedure TBox.WriteKey(key: char);
    begin
      with itemv^[ind] do
        begin
          if ins then odsun_text; {with itemd^[ind] do Move(item[i],item[i+1],_hi-i);}
          itemd^[ind].item[i]:= key;
          MoveRight(1)
        end
    end;


procedure TBox.MoveRight(di: int);
    begin
      with itemv^[ind] do with itemd^[ind] do
        begin
          oi:= i;
          i := i+di;
          while
            (i < StrLen(item)) and (item[i] in skip^)
          do Inc(i);
          if (i >= StrLen(item)) or (item[i] in skip^) then i:= oi
        end
    end; { MoveRight }

procedure TBox.MoveLeft(di: int);
    begin
      with itemv^[ind] do with itemd^[ind] do
        begin
          oi:= i;
          i := i-di;
          while
            (i >= 0) and (item[i] in skip^) do
          Dec(i);
          if (i < 0) then i:= oi
        end
    end; { MoveLeft }


procedure TBox.GoToPos(_pos: byte);
    begin
       prev_ind:= ind; ind:= _pos;
     { vyhodnotenie znaku
     }
       with itemv^[ind] do with itemd^[ind] do
         begin
           i:= 0;
           while item[i] in skip^ do MoveRight(1)
         end;
       Write
    end;

{ kontrola, aby som neditoval na zakazanom mieste
}
procedure TBox.SetPos;
    var   pos: byte;
    begin
      with itemv^[ind] do
        begin
          _lo:= 1; _hi:= 0; pos:= 0;
          while (not(i in[_lo.._hi])) and (pos<=strlen(itemd^[ind].item)) do
            begin
              SetPBound(itemd^[ind].item,_lo,_hi,pos,itemd^[ind].skip^);
              inc(pos)
            end
        end
    end; { SetPos }


function TBox.first_char_i(_ind: int): int;
   begin
     with itemv^[_ind] do
       begin
         i:= _lo;
         first_char_i:= i
       end
   end;


{ nastavi sa na posledne pismeno vo formulari
}
function TBox.last_char_i(_ind: int): int;
   var   c : int;
   begin
     with itemv^[_ind] do
       begin
         c:= _hi; while (c>_lo) and (itemd^[_ind].item[c{-1}] in[' ',kbCRLF]) do Dec(c)
       end;
     last_char_i:= c
   end;

procedure TBox.last_char;
    begin
      with itemv^[ind] do i:= last_char_i(ind)
    end; { Lastchar }

{
presun mysi na nove miesto
}
procedure TBox.item_clicked(var _Event: TEvent);
    const size_item: array[false..true] of byte = (0,8);
    var   c_ind, c_pos, dx_t,dx_c, j,k : int;
    begin
      c_ind:= 0;
      while (c_ind<items) do
        with itemd^[c_ind] do
         begin
           if tit<>2 then dx_c:= dx else dx_c:= dx + TextWidth(StrPas(title)) + dx_ch;
           if (itemd^[c_ind].legal<>@setNil) then
              if inRectangle(_Event.M.x,_Event.M.y,
                             x0+dx_c,y0+dy,
                             x0+dx_c+TextWidth(StrPas(itemd^[c_ind].item)),
                             y0+dy+TextHeight('T')+size_item[item_in_button]
                            ) then break;
           inc(c_ind)
         end;
      if (c_ind>=items) or (itemd^[c_ind].legal=@setNil) then Exit;
      prev_ind:= ind; ind:= c_ind;
      with itemv^[ind] do with itemd^[ind] do
        begin
          c_pos:= Limit((_Event.M.x - (x0+dx_c) + 1) div Maximum(1,TextWidth('W')),0,StrLen(item)-1,0);
          if    (_Event.What = evMouseDouble)
             or ((prev_ind=ind) and (itemv^[ind].i=c_pos)) then
                 with itemd^[ind] do RunList(lst, abs(pos), ins and (pos<0), nil,nil,nil)
          else begin
                 j:= c_pos;
                 while (j < StrLen(item)) and (item[j] in skip^) do inc(j);
                 if (j < StrLen(item)) then
                    begin
                      i:= c_pos; while item[i] in skip^ do MoveRight(1)
                    end;
                 Write
               end
        end;
      ClearEvent(_Event)
    end;

function TBox.is_upcas(_ind: int): bool;
   begin
     is_upcas:= upcas
   end;


function TBox._it_(_ind: int): string;
   var   s: string;
   begin
     if (_ind<0) or (_ind>=items) then _it_:= ' '
     else begin
            s:= strpas(itemd^[_ind].item);
            if s='' then s:= ' ';
            _it_:= s
          end
   end;


function TBox._it(_ind: int): string;
   var   s: string;
   begin
     s:= _it_(_ind);
     if s<>' ' then s:= cut_r(s);
     _it:= s
   end;


procedure TBox._in(_ind: int; s: string);
   var    i : int;
   begin
     if is_upcas(_ind) then s:= upstring(s);
     for i:= 1 to length(s) do if ord(s[i])<ord(' ') then s[i]:= ' ';
     if (_ind>=0) and (_ind<items) then StrPICopy(itemd^[_ind].item,s,strlen(itemd^[_ind].item))
   end;


procedure TBox.IndXY(var _pos: int; var x,y: int; _mess: string);
    begin
      if _pos<0 then _pos:= 0;
      x:= Maximum(15, x0 + itemd^[_pos].dx
                         + TextWidth(strpas(itemd^[_pos].item)) shr 1 - ( TextWidth(_mess) + 40 ) shr 1
                 );
      y:= Maximum(15,y0 + itemd^[_pos].dy + 15);
    end;

procedure TBox.Error(_pos: int; _mess: PChar);
    var   x,y: int;
    begin
      if (_pos<0) or (_pos>=items) then _pos:= first_pos;
      if itemd^[_pos].legal=@setNil then _pos:= ind;
      IndXY(_pos, x,y,strpas(_mess));
      PosErr(x,y,'',_mess);
      GoToPos(_pos)
    end;

procedure TBox.ErrorS(_pos: int; _mess: string);
    begin
      _mess:= _mess+NULL;
      Error(_pos,@_mess[1])
    end;

                                                                                                                                                                     