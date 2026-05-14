{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TScroller                                                Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

 function TScroller.get_scroller_size(_item_dx: int; var _dxi: int): word;
    begin
      get_scroller_size:= _get_scroller_size(_item_dx,_dxi)
    end;

 function TScroller.get_scroller_height(_page: int; _item_dy: int; var _dyi: int; _medzera: int): word;
    begin
      get_scroller_height:= _get_scroller_height(_page,_item_dy, _dyi,_medzera)
    end;

{
 item_dx     -> sirka polozky
 item_dy     -> vyska polozky
 p_item_list -> procedura pre vypis polozky (ndex, x,y)
 top_adr     -> adresa top v zozname items, mosi byt typu int
 top_chg     -> bool premenna vracajuca true, ak sa zmenil top of items
}
 constructor TScroller.Init(_Owner: PGroup; _page: int;
                             x,y, _item_dx,_item_dy: int;
                            _dxi,_dyi, _medzera: int; _bg: byte;
                            _pos_en, _sam : bool;
                            _p_item_list : pointer;

                            _arr_adr : pointer;
                            _top_adr : pointer;

                            _top_chg : pointer;
                            _p_arr_chg : p_tick_counter  { ukazovatel na premennu o zmene dat <>0 or <>last_tick_counter }
                           );
       begin
         medzera:= _medzera; pos_en:= _pos_en;
         stranka_en:= false; prepis_en:= false;
         sam:= _sam; vpravo:= true;
         smer:= true;
         za_posl_en:= false;
         item_en:= true;
         sort_en:= true;

         item_dx:= _item_dx; item_dy:= _item_dy;
         dxi:= _dxi; dyi:= _dyi; if item_dy=0 then item_dy:= 1;
         dxioff:= 0; dyioff:= 0;
         inherited Init(_Owner, x,y, get_scroller_size(_item_dx,dxi), 0);
         check_idle_all:= false;

         MCursor:= SIPKA;
         sb:= New(PScrollBar,Init(@Self, x1, y0, 0, _pos_en,stranka_en,_sam));
         bg:= _bg; on:= btON;

         maska_is_clicked:= mbLeftButton;
         click_and_handle:= false;
         pos_chg_and_list:= true;
         finded_and_processed_data:= false;

         top:= -1; top_prev:= -1;
         pos:= 0; pos_prev:= -1;
         lo:= 0; hi:= _page-1;
         lo_prev:= -1; hi_prev:= -1;

         p_item_list:= _p_item_list;
         arr_adr:= _arr_adr;
         is_ptr_arr:= true;
         adr_arr_adr:= nil; {_adr_arr_adr};

         p_top_chg:= _top_chg;
         p_top_adr:= _top_adr;
         p_arr_chg:= _p_arr_chg;
         arr_chg:= 0;

         p_arr_init:= nil;
         p_arr_check:= nil;

         if item_dy<>0 then reinit_(x,y,maximum(3*8 div item_dy,_page)) { 3*8..., minimalna velkost aby sa neprekryvali sipky }
       end; { TScroller.Init }


{ dakedy sa uz clovek neserie...
}
 procedure TScroller.draw_inside;
     var   x : int;
     begin
       if sam or (not sb^.visible) then x:= x1-1 else x:= sb^.x1;
       fillwin(x0+1,y0+1,x,y1-1, bg);
       on_off (x0,y0,x,y1, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, on);
     end; { TScroller.Draw }


 procedure TScroller.Draw;
     var   bp: bool; xl,yl: int;
     begin
       if (not visible) then Exit;

       m_off(bp, xl,yl);
       inherited Draw;  { sb^.Draw; }
       draw_inside;
       pos_prev:= -1;
       List;
       m_on(bp, xl,yl)
     end; { TScroller.Draw }


 procedure TScroller.Idle(var _Event: TEvent);
     begin
       if is_initialized or is_checked then Exit;
       if is_changed then
          begin
            renew;
            List
          end
       else Prekreslit
     end;


 procedure TScroller.Prekreslenie;
     begin
       if ma_sa_prekreslit then
          begin
            List;
          end
     end;


 {procedure TScroller.Prekreslit;
     begin
       if PREPIS then
          if (not S_prekreslit) and (not OverlapWin(x0,y0,x1,y1, ScreenDesc)) then
             begin
               S_prekreslit:= true;
               Prekreslenie;
               S_prekreslit:= false
             end
     end;}


 procedure TScroller.handle_scroller(var _Event: TEvent);
     var   cez,{prev_pos,prev_lo,prev_hi,}rel_pos: int;
     label X;
     begin
       if (_Event.What = evKeyDown) then
          begin
          { stlacenie klavesy  }
            if not Active then Exit;

            if (_Event.Key = kbEnter) and (pos>=0) and (top>=0) then
               begin
                 if item_en then
                    begin
                      Move(_Event,MailBox^,SizeOf(TEvent));
                      SetCommand(_Event,cmScrollItemEntered); {cmScrollItemClicked}
                    end;
                 Exit
               end
            else if set_scroll_par(_Event.Key, lo,hi,pos,top, cez, pos_en, smer, za_posl_en,false) then
            else Exit
          end
       else

       if  ( (_Event.What = evMouseClick) or (_Event.What = evMouseDouble) )
         and (     TView.inView(_Event.M.x+(-Moff[_Event.M.curs].x),_Event.M.y+(-Moff[_Event.M.curs].y))
               and bool(_Event.M.bt and maska_is_clicked)
             ) then
          begin
          { kliknuta polozka  }
            if item_dy+medzera<>0 then rel_pos:= (_Event.M.y-(y0+dyi)) div (item_dy+medzera)
            else rel_pos:= 0;
            rel_pos:= Minimum(rel_pos,hi);
            if not smer then rel_pos:= hi-lo-rel_pos;
            if click_and_handle then pos:= lo+rel_pos;
            if (top>=0) and (pos>=0) and (rel_pos>=0) and ((pos=lo+rel_pos) or (not pos_en)) then
               begin
                 Move(_Event,MailBox^,SizeOf(TEvent));
                 SetCommand(_Event,cmScrollItemClicked);
                 goto X
               end
            else set__scroll_pos(lo,hi, pos, top,lo+rel_pos, za_posl_en,false)
          end
       else

       if isCommand(_Event,cmScrollBarClicked) then
          begin
          { sprava od ScrollBaru }
            receive__scroll_mail(lo,hi,top,pos)
          end

       else Exit; { if }

       ClearEvent(_Event);

       X: if (pos_prev<>pos) and ((pos_chg_and_list) or (lo_prev<>lo) or (hi_prev<>hi)) then
             begin
               List
             end
     end;

 procedure TScroller.HandleEvent(var _Event: TEvent);
     begin
       inherited HandleEvent(_Event);
       if (_Event.what<>evNothing) then handle_scroller(_Event)
     end;


 function TScroller.is_initialized: bool;
    begin
      is_initialized:= (p_arr_init<>nil) and (p_arr_init^=true)
    end;

 function TScroller.is_checked: bool;
    begin
      is_checked:= (p_arr_check<>nil) and (p_arr_check^=true)
    end;


{ is_changed urci, ci sa zmenil pocet poloziek
  pre vypis - top a zabezpeci prislusne akcie
}
 function TScroller._is_changed: bool;
    var   res: bool;
    begin
      res:=     ((p_arr_chg<>nil) and ((p_arr_chg^<>0) and (p_arr_chg^<>arr_chg)))
             or ((p_top_adr<>nil) and (int(p_top_adr^)<>top))  { kontrolujem priamo premmenu }
             or ((p_top_chg<>nil) and (bool(p_top_chg^)))      { kontrolujem podla priznaku  }
             or ((adr_arr_adr<>nil) and (pointer(adr_arr_adr^)<>arr_adr));
      if res then
         begin
           if (p_arr_chg<>nil) then arr_chg:= p_arr_chg^;
           if (p_top_chg<>nil) then bool(p_top_chg^):= false;
           if (adr_arr_adr<>nil) then arr_adr:= pointer(adr_arr_adr^)
         end;

      _is_changed:= res
    end;

 function TScroller.is_changed: bool;
    var   res: bool;
    begin
      is_changed:= false;
      if is_initialized or is_checked then Exit;

      is_changed:= _is_changed
    end;


{ kontroluje, ci sa zmenil top
}
 function TScroller.get_top: int;
    begin
      if (p_top_adr<>nil) then get_top:= (int(p_top_adr^))
      else get_top:= top
    end;

 procedure TScroller.renew;
     var   prev_pos: int;
     begin
       prev_pos:= pos;
       disp_data;
       new_data;
       pos:= Limit(prev_pos, lo,N(top), 0)
     end;

{ skontroluje, ci nedoslo ku zmene poctu dat a usporiada ich nanovo
}
 function TScroller.is_to_renew(ind: int): bool;
    var   res: bool;
    begin
      res:= (ind>top) or is_changed;
      is_to_renew:= res
    end;


{ alokovanie novych dat
}
 procedure TScroller.new_data;
     begin
       top:= get_top
     end;

{ odalokovanie dat
}
 procedure TScroller.disp_data;
     begin
       {top:= -1}
     end;


{ procedury, ak je zmena obsahu riadena zvonku:
}
 function TScroller.get_ind(i: int): int;
    begin
      get_ind:= i
    end;

 function TScroller.get_ind_in_list(i: int): int;
    begin
      get_ind_in_list:= i
    end;


 function TScroller.get_x: int;
    begin
      get_x:= x0+dxi+dxioff
    end;

 function TScroller.get_yi(i: int): int;
    begin
      get_yi:= y0+dyi+dyioff + (i-lo)*(item_dy+medzera)
      { ak by to bolo makro/fcia, lepsie, lebo na vypocet sa odvolavam aj inde (TEdit) }
    end;

 function TScroller.get_pos_xy(_pos: int; var x,y: int): bool;
    begin
      if pos<=top then
         begin
           x:= get_x;
           y:= get_yi(_pos);
           get_pos_xy:= true
         end
      else get_pos_xy:= false
    end;


 procedure TScroller.reinit_(x,y,_page: int);
     var   dy: int;
     begin
       lo_prev:= -1; hi_prev:= -1; lo:= 0; hi:= _page-1;
       top:= -1; top_prev:= -1; pos:= 0; pos_prev:= -1;
       dy:= get_scroller_height(_page, item_dy, dyi, medzera);
       XY(x,y, x1-x0,dy);
       sb^.ReInit(x1+MEDZERA__SCROLLER__SCROLL_BAR,y, x1-x0,dy)
     end;

 procedure TScroller.sb_left;
     var   dx, dxs,dxsb: int;
     begin
       if not vpravo then Exit;

       vpravo:= false;
       dx:= sb^.x0-x1; dxs:= x1-x0; dxsb:= sb^.x1-sb^.x0;
       sb^.x0:= x0; sb^.x1:= sb^.x0+dxsb;
       x0:= sb^.x1+dx; x1:= x0+dxs
     end;


{ --------------------------------
  vypis poloziek/zoznamu
  úúúúúúúúúúúúúúúúúúúúúúúúúúúúúúúú
}
 procedure TScroller.item_list_pos(posi: int);
     begin
       item_list(posi, get_x,get_yi(posi), {$IFNDEF EDD} (pos_en) and {$ENDIF} (posi=pos));
     end;

 procedure TScroller.item_list_proc(i, x,y: int; b: bool);
     begin
     end;

 procedure TScroller.item_list(i, x,y: int; b: bool);
     var   bp: bool; xl,yl: int;
     begin
       if (i<lo) or (i>hi) then Exit;

       if   is_initialized
         or (    prepis_en
             and (   OverlapWin(x,y,x+item_dx,y+item_dy,ScreenDesc)
                  or OverlapWin(sb^.x0,sb^.y0,sb^.x1,sb^.y1,ScreenDesc))
                 ) then
            begin
              PREPIS:= absTime;
              Exit
            end;

       i:= get_ind(i);
       m_off(bp, xl,yl);
       if (p_item_list<>nil) then
          if arr_adr<>nil then
             if is_ptr_arr then TProc_pi2b(p_item_list)(Pptrs(arr_adr^[i]), x,y, b)
             else TProc_pi3b(p_item_list)(arr_adr,i, x,y, b)
          else TProc_i3b(p_item_list)(i, x,y, b)
       else item_list_proc(i, x,y, b);
       m_on(bp, xl,yl)
     end;

 procedure TScroller.item_erase(i: int);
     begin
       if (i<lo) or (i>hi) then Exit;

       if     is_initialized
          or (     prepis_en
              and (    OverlapWin(get_x,get_yi(i),get_x+item_dx,get_yi(i)+item_dy,ScreenDesc)
                    or OverlapWin(sb^.x0,sb^.y0,sb^.x1,sb^.y1,ScreenDesc)
                  )
             ) then
           begin
             PREPIS:= absTime;
             Exit
           end;

       FillWin(x0+2, y0+dyi+(i-lo)*(item_dy+medzera){+medzera}, x1-2, y1-2, bg)
     end;


 procedure TScroller.mark_pos;
     begin
       top_prev:= top;
       pos_prev:= pos;
       lo_prev := lo;
       hi_prev := hi;
     end;


 { vypis poloziek, ak sa oznacuju, predefinuje TSelect;
 }
 procedure TScroller.List;
     var   i, x,y: int;
           bp: bool; xl,yl : int;
           b: bool;
     begin
       if     is_initialized
          or  (     prepis_en
               and (   OverlapWin(x0,y0,x1,y1,ScreenDesc)
                    or OverlapWin(sb^.x0,sb^.y0,sb^.x1,sb^.y1,ScreenDesc)
                   )
              ) then
              begin
                PREPIS:= absTime;
                Exit
              end;

       if is_to_renew(top) then renew;
       check_hi(za_posl_en,false, lo,hi, pos, top);
       pos:= Limit(pos, lo,N(top), 0);
       sb^.param(lo,hi,top,pos, true);
       if not (visible and PIS) then Exit;

       {
       if not ( (sb^.lo=lo) and (sb^.hi=hi) and (sb^.top=top) and (sb^.pos=pos) )
          then Mail(sb, cmScrollerChanged, One, @lo,4*SizeOf(int));
       }
       b:= prepis_en; prepis_en:= false;
       m_off(bp, xl,yl);
       x:= get_x;
       if       (* (pos_en {or (not stranka)})
          and*)  (    (top_prev=top)        { nebol vypusteny ziadny clen }
                  and (top_prev<>-1)
                  and (lo_prev=lo)
                  and (hi_prev=hi)
                  and (pos_prev<>pos)       { zmenena pozicia }
                  and (pos_prev<>-1)        { zmenena pozicia }
                 )
                (* taraz uz neviem, preco som to tak spravil:
                  and (pos_prev<>-1)        { nie je inicializacia }
                { nova nie je mimo rozsah okna }
                  and ((pos>lo) {or ((pos=lo) and (pos_prev<>lo+1))})
                  and ((pos<hi) {or ((pos=hi) and (pos_prev<>hi-1))})
                 *)
          then begin
               { rychly vypis, len zmenenej polozky }
                 item_list(pos_prev, x,get_yi(pos_prev), false);
                 item_list(pos, x,get_yi(pos), {$IFNDEF EDD} (pos_en) and {$ENDIF} true)
               end
       else begin
            { vypis celej stranky }
              i:= lo;
              while (i<=top) and (i<=hi) do
                begin
                  item_list(i, x,get_yi(i), {$IFNDEF EDD} (pos_en) and {$ENDIF} (i=pos));
                  inc(i)
                end;
              {item_erase(i);
              if pos_prev=-2 then for i:= i to hi do item_erase(i);}
              for i:= i to hi do item_erase(i);
            end;
       mark_pos;
       m_on(bp, xl,yl);
       prepis_en:= b;
       PREPIS:= 0;
       PREPISANE:= absTime;
     end;  { TScroller.List  }


 procedure TScroller.Scroll;
     var   is_list : bool;
           pg : int;
     begin
       if is_initialized then
          begin
            PREPIS:= absTime;
            Exit
          end;

       pg:= hi-lo;
       is_list:= (top<lo) or (top>hi);
       if is_list then
          begin
            lo:= top;
            hi:= top+pg;
          end;
       pos:= top;

       if is_list then List
       else redraw(pos)
     end;  { TScroller.Scroll  }

 { a) zmena
 }
 procedure TScroller.redraw(ind: int);
     var   bp : bool; xl,yl : int;
     begin
       if not (visible and PIS) then Exit;

       if is_initialized then
          begin
            PREPIS:= absTime;
            Exit
          end;

       ind:= get_ind_in_list(ind);
       if is_to_renew(ind) then
         begin
           renew;
           List
         end
       else if visible and (top>-1) and (ind>=lo) and (ind<=hi) then
         begin
           if (    prepis_en
               and (   OverlapWin(get_x,get_yi(ind),get_x+item_dx,get_yi(ind)+item_dy,ScreenDesc)
                    or OverlapWin(sb^.x0,sb^.y0,sb^.x1,sb^.y1,ScreenDesc)
                   )
              ) then begin
                       PREPIS:= absTime;
                       Exit
                     end;
           m_off(bp, xl,yl);
           item_list(ind, get_x,get_yi(ind), ind=pos);
           sb^.param(lo,hi,top,pos, true);
           m_on(bp, xl,yl)
         end
     end;


{ b) odmazanie
}

 procedure TScroller.erase(ind: int);
     begin
       if is_initialized or (not (visible and PIS)) then PREPIS:= absTime
       else List { obsahuje is_to_renew(ind) }
     end;


 function TScroller.get_p_ind(p: pointer): int;
    begin
      get_p_ind:= -1
    end;

 procedure TScroller.redraw_p (p: pointer);
     begin
       redraw(get_p_ind(p))
     end;

 procedure TScroller.erase_p (p: pointer);
     begin
       erase(get_p_ind(p))
     end;
