 constructor THelp.Init(_fn: string; _sorry: bool; _hlpXXX: pchar);
       begin
         fn:= GetFname(_fn,'',lstExt);

         if Exists(fn)<>0 then vytvor_novy_subor(fn);

         {$IFDEF HELP_NOEMS} strm:= nil;
         {$ELSE}             stre:= nil;
         {$ENDIF}

         riadkov:= 0;
         top:= -1;

         item_dy:= 8;
         inc(help_open);

         dxb:= 0; dyb:= 0;
         init_buttons:= nil;
         handler_buttons:= nil;
         handler_owner:= nil;

         is_help:= false;
         is_pos_en:= false;
         item_en:= false;
         empty_en:= true;
         comment_en:= false;
         is_comment:= true;
         is_comment0:= true;
         is_sorry:= _sorry;

         SOH:= hlp_SOH; EOT:= hlp_EOT; EOH:= hlp_EOH;
         hlpXXX:= _hlpXXX;

         dxm:= 0; dym:= 0;
       end;

 destructor THelp.Done;
      begin
        inherited Done;
        dec(help_open)
      end;


 procedure  THelp.HandleEvent (var _Event: TEvent);
     var    i: int;
     begin
       inherited HandleEvent (_Event);
       if isCommand (_Event,cmPrint) then
          begin
            i:= 0;
            while i<=top do
              if print_str (PortNo,_PRN_TAB+delchar(get(i),[hlp_NXT, hlp_const_h1,hlp_const_h2,hlp_sipka_vpravo])+kbNL)
                 then inc(i)
              else break;
            ClearEvent(_Event)
          end;
     end;


 procedure THelp.List;
     var   s : string;
           cez, _top_prev,_pos_prev,_lo_prev,_hi_prev : int;
           k : char;
     label L;
     begin
       if item_en then
          begin
            _top_prev:= top_prev; _pos_prev:= pos_prev; _lo_prev:= lo_prev; _hi_prev:= hi_prev;
            L: s:= cut_(get(pos));
            if (not is_help) and ((s='') or (s[1]=';')) then
               begin
                 if (pos_prev<>-1) and (pos_prev<pos) then k:= kbDown
                 else if (pos_prev>pos) or (pos>top) then k:= kbUp
                 else k:= ' ';

                 if (k in[kbUp,kbDown]) and set_scroll_par(k, lo,hi,pos,top, cez, pos_en, smer, za_posl_en,false) then goto L
                 else if (_top_prev<>-1) and (_pos_prev<>-1) and (_lo_prev<>-1) and (_hi_prev<>-1) then
                        begin
                          top:= _top_prev; pos:= _pos_prev; lo:= _lo_prev; hi:= _hi_prev;
                          top_prev:= _top_prev; pos_prev:= _pos_prev; lo_prev:= _lo_prev; hi_prev:= _hi_prev;
                        end
               end
          end;
       inherited List;
     end;

 procedure THelp.item_list(ind, x,y: int; b: bool);
     var   s, sn, s_, s__, _s : string;
           i,dx, _lo,_hi  : int;
           c : byte;
     begin
       s:= get(ind);

       if is_help then
          begin
            x:= x+5 + ord(not(sb^.visible))*5;

            sn := get_s_(s, hlp_NXT,[hlp_const_h1,hlp_const_h2]);
            s_ := get_s_(s, hlp_const_h1,[hlp_NXT,hlp_const_h2]);
            s__:= get_s_(s, hlp_const_h2,[hlp_NXT,hlp_const_h1]);
            s  := InsChar(DelChar(s,[hlp_NXT,hlp_const_h1,hlp_const_h2]),max_len,' ',1);

           {$IFDEF BGI}
            WriteStr(x+dx_ed,y+dy_ed, s, hlp_cl_tx,hlp_cl_bg);
            if delchar(s_,set_) <>'' then Write_ (x+dx_ed,y+dy_ed, s_,  hlp_kb_tx);
            if delchar(s__,set_)<>'' then Write_ (x+dx_ed,y+dy_ed, s__, hlp_k__tx);
            if delchar(sn,set_) <>'' then Write_ (x+dx_ed,y+dy_ed, sn,  hlp_nx_tx);
           {$ENDIF}

           {$IFDEF SPEA}
            dx:= TextWidth('W'); SetBkColor(hlp_cl_bg);
            SetColor(hlp_cl_tx);
            OutTextXY(x+dx_ed,y+dy_ed, s);

            SetColor(hlp_kb_tx);
            _lo:= 1;
            repeat
              _s:= get_sp(s_, _lo,_hi);
              if s_<>'' then
                 begin
                   OutTextXY(x+dx_ed+dx*(_lo-1),y+dy_ed, _s);
                   _lo:= _hi
                 end
            until _s='';

            SetColor(hlp_k__tx);
            _lo:= 1;
            repeat
              _s:= get_sp(s__, _lo,_hi);
              if _s<>'' then
                 begin
                   s_:= get_sp(s__, _lo,_hi);
                   OutTextXY(x+dx_ed+dx*(_lo-1),y+dy_ed, _s);
                   _lo:= _hi
                 end
            until _s='';

           {$ENDIF}
         end
       else begin
              ClearStr (x+dx_ed-1,y+dy_ed,max_len,bg);
              if item_en and b then c:= white else c:= hlp_cl_tx;
              SetColor(c);
              OutTextXY(x+dx_ed,y+dy_ed, copy(s,1,max_len));
            end;
     end;


 function THelp.is_to_be_Run: bool;
    var   p: int;
    begin
      p:= top; while (p>=0) and (cut_(get(p))='') do dec(p);
      if (p<0) then
         begin
           if is_sorry then Say2(msgSORRY,msgDATA_NOT_FOUND);
           is_to_be_Run:= false
         end
      else is_to_be_Run:= true
    end;


 procedure THelp.show_help (title: string);
     var   _Event: TEvent;
           i,j,k, _top, _hi: int;
           _hlpXXX: pchar;
     begin
       _top:= top;
       _hi:= Minimum(top,(MaxY-hlp_dy0-hlp_dy1-winHEIGHT {$IFDEF SPEA}-50{$ENDIF}) div Maximum(item_dy,1));
       _hi:= Minimum(_hi,MaxY-200 div Maximum(item_dy,1));
       max_len:= 0;
       for i:= 0 to top do max_len:= Maximum(max_len,Length(DelChar(get(i),[hlp_NXT, hlp_const_h1,hlp_const_h2])));
       max_len:= Maximum(max_len,length(title));
       max_len:= Minimum(max_len,(MaxX-100) shr 3);
       _hlpXXX:= hlpXXX;
       inherited Init(nil, title,
                      nil,@top,nil,nil,
                      0,0, 10 + max_len shl 3 + 10,item_dy,
                      {$IFDEF BGI}  0,0,0, {$ENDIF} {$IFDEF SPEA} 0,0,2, {$ENDIF}
                      hlp_cl_bg,nil,
                      _hi+1,
                      is_pos_en,true {_top>_hi+1}, false,
                      dxb,dyb, init_buttons,handler_buttons,handler_owner, {0,0,nil,nil,nil,}
                      kbEnter, cmCancel
                     );
       if is_pos_en then win^.btTitle^.cmXXXX:= cmNil
       else item_en:= false;
       on:= btOFF; stranka_en:= true; sb^.stranka:= true;
       hlpXXX:= _hlpXXX;
       Centre;
       if (dxm<>0) and (dym<>0) then MoveRel(dxm-x0,dym-y0);
       dxm:= 0; dym:= 0;
       lo:= 0; {hi:= _hi;} top:= _top;
       if top<=hi then sb^.visible:= false;
       Run(_Event);
       Done;
     end;


 procedure THelp.help(key,title: string);
     var   _title : string;
     begin
       _title:= title;
       key_read (key,_title);
       if title='' then title:= _title;
       show_help(title);
       key_release;
     end;
