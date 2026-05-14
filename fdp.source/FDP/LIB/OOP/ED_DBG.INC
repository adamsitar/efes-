{$I scroll.inc}

procedure TEditors._HandleEvent(var _Event: TEvent);
    var   cez,{prev_pos,prev_lo,prev_hi,}rel_pos: int;
    label X;
    begin

      TGroup.HandleEvent(_Event);

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
           if     (top>=0) and (pos>=0) and (rel_pos>=0) and ((pos=lo+rel_pos) or (not pos_en)) then
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

      X: if (pos_prev<>pos) and ((pos_chg_and_list) or (lo_prev<>lo) or (hi_prev<>hi)) then List;

      if (_Event.what<>evNothing) and (win<>nil) then win^.HandleEvent(_Event);
      if (handle_buttons<>nil) and (_Event.what<>evNothing) then
          TBFunc_vEp3(handle_buttons)(_Event,@Self,handler_owner,handler_data)
    end;
