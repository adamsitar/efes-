{ ------------------------------
  polozka NDB na tabuli stripov
  ------------------------------ }

{$I acc2a.inc} { init,...     }
{$I acc2b.inc} { scroll_cl,st }
{$I acc2c.inc} { sort         }
{$I acc2d.inc} { utility      }
{$I acc2e.inc} { reinit...    }


function  _handle_item(var _Event: TEvent; sc: PScroller; FPL: PindFPL): bool; far;
    var   _E : TEvent;
    begin
      Move(MailBox^,_E,SizeOf(TEvent));
      if FPL<>nil then
         with FPL^ do
           if (iFPL^.p_strip_handler<>nil) then
              Tstrip_handler_Bp3vEi2(iFPL^.p_strip_handler)
                      (iFPL, iFPL^.ap^[ind],
                       sc,_Event,
                       _E.M.x - sc^.x0-sc^.dxi,
                       _E.M.y - sc^.y0-sc^.dyi-(sc^.hi-sc^.pos)*(sc^.item_dy+sc^.medzera)
                      );
      _handle_item:= false
    end;

procedure _item_window(FPL: PindFPL; x,y: int; b: bool); far;
    begin
      with FPL^ do iFPL^.strip(ind, x,y+2, b)
    end;


procedure TlstACC.HandleEvent(var _Event: TEvent);
    var   _E : TEvent;
    begin
      if (top<0) and (not NDB_NULL) then Exit;

      inherited HandleEvent(_Event);
      if (_Event.What and evMessage<>0) then
         begin
           case _Event.Command of

             cmScrollItemEntered, cm_NDB_view  :

                begin
                  if is_scroll then
                     if active then Window
                     else Mail(Owner,rq_lstACC_zapni, One,@popis.NDB[0],sizeof(popis.NDB)+1);
                  ClearEvent(_Event)
                end;

             cmScrollItemClicked :

                begin
                  _handle_item(_Event,@Self,FPLs^[pos]);
                  ClearEvent(_Event)
                end;

             cm_NDB_move :

                begin
                  if zmen_stlpec then SetCommand(_Event, rq_lstACC_move)
                end;

             cm_NDB_set  :

                begin
                  set_sort;
                  ClearEvent(_Event)
                end

           end
         end
    end;

procedure TlstACC.Window;
    var   Ev: TEvent;
    begin
      sc_lst:= New(PScroll_lstAct,Init(nil,
                   popis.NDB,

                   FPLs, @top,
                   @is_chg,nil{OBoard nema @t_chg},

                   0, nil,nil,

                   dx_strip_[miniSTRIP],dy_strip_[lineSTRIP],
                   2,2,2,0,
                   @_item_window,
                   max_rdk,
                   true,true,true,

                   0,0,nil,nil,nil,

                   _TBFunc_vEp2, @_handle_item, nil,

                   kbNoKey, cmNil,
                   hlp_PREHLAD_FPLi
                   )
                  );
      sc_lst^.adr_arr_adr:= @FPLs;
      sc_lst^.MoveRel(x0-sc_lst^.x0-14,MaxY-sc_lst^.y1);
      sc_lst^.RunLocalFunc(Ev,SCROLL_ACTF1);
      Dispose(sc_lst,Done);
      sc_lst:= nil
    end;