
 procedure addStatIndicator(p: PButton);
     begin
       if StatusIndicators<maxStatusIndicators then
          begin
            StatLine[StatusIndicators]:= p;
            inc(StatusIndicators)
          end;
     end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TIButton                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

 constructor TIButton.Init(_Owner: PGroup; x,y, dx,dy: int;
                           _kbHot: char; _cmXXXX: word; _title: string;
                           _click, _ck,_ct,_bk: byte;
                           _check_adr: pointer; _en_bool: bool;
                           var hi_: int; _hide: bool
                          );
       begin
         inherited Init(_Owner, x,y, dx,dy, _kbHot,_cmXXXX,_title, _click, _ck,_ct,_bk);
         bk0   := black;
         btSize := btSmall;
         visible := false;
         hi_:= x1;
         click_and_hide:= _hide;
         check_adr:= _check_adr; en_bool:= _en_bool;
       end;


 procedure TIButton.Reinit(x,y,dx,dy: int);
     begin
       MoveRel(0,(MaxY-16)-y0);
       Draw
     end;


 procedure TIButton.check;
     var   b: bool;
     begin
       if check_adr=nil then Exit;
       if en_bool then b:= bool(check_adr^) else b:= not bool(check_adr^);
       if b<>visible then visibility(b)
     end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TTimeOutExtButton                                        €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{$IFDEF EXTERNAL_NET}
 constructor TTimeOutExtButton.Init(_Owner: PGroup; x,y, dx,dy: int;
                                    _kbHot: char; _cmXXXX: word; _title: string;
                                    _click, _ck,_ct,_bk: byte;
                                    _p_ext: PO_EXT;
                                    var hi_: int; _hide: bool
                                   );
       begin
         inherited Init(_Owner, x,y, dx,dy, _kbHot,_cmXXXX,_title, _click, _ck,_ct,_bk, nil,true,hi_,_hide);
         p_ext:= _p_ext
       end;

 procedure TTimeOutExtButton.check;
     var   b: bool;
     begin
       if p_ext=nil then Exit;
       b:= p_ext^.is_receive_pkt;
       b:= b and (p_ext^.Tr_+p_ext^.TrTimeOut+3<=absTime);
       if (b<>visible) then visibility(b)
     end;
{$ENDIF}

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TTButton                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

 constructor TTButton.Init(_Owner: PGroup; x,y, dx,dy: int;
                           _kbHot: char; _cmXXXX: word; _title: string;
                           _click, _ck,_ct,_bk: byte;
                           _check_adr: pointer; _en_bool: bool;
                           var hi_: int; _hide: bool
                          );
       begin
         inherited Init(_Owner, x,y, dx,dy, _kbHot,_cmXXXX,_title, _click, _ck,_ct,_bk, _check_adr,_en_bool, hi_,_hide);
         lastTime:= 0.0;
       end;

 {
   kliknutie lavym buttonom->Enter; pravym->hide
 }
 procedure TTButton.HandleEvent(var _Event: TEvent);
     var   _Ev: TEvent;
     begin
       if not visible then Exit;
       with _Event do
         if   (     ( (What = evMouseClick) or  (What = evMouseDouble) )
                and (  inView(M.x,M.y) and  bool(M.bt and mbRightButton) )
              ) then begin
                       hide;
                       ClearEvent(_Event)
                     end
         else begin
                _Ev:= _Event;
                inherited HandleEvent(_Event);
                if click_and_hide and (_Ev.Command<>_Event.Command) then hide
              end
     end;

 procedure TTButton.Idle(var _Event: TEvent);
     var   r: real;
     begin
       if not visible then Exit;
       r:= 18*60*waitSPRAVY;
       if (lastTime + r < absTime) then hide
     end;

 procedure TTButton.Reinit(x,y,dx,dy: int);
     begin
       MoveRel(0,(MaxY-16)-y0);
       Draw
     end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TSButton                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

 constructor TSButton.Init(_Owner: PGroup; x,y, dx,dy: int;
                           _kbHot: char; _cmXXXX: word; _title: string;
                           _click, _ck,_ct,_bk: byte;
                           _bt_vis : pbool; _op_vis : bool;
                           _bt_act : pbool; _op_act : bool;
                           _check_adr: pointer; _en_bool: bool;
                           var hi_: int; _hide: bool
                          );
       begin
         inherited Init(_Owner, x,y, dx,dy, _kbHot,_cmXXXX,_title,_click, _ck,_ct, _bk, _check_adr,_en_bool, hi_,_hide);
         bk0:= black;
         bt_vis:= _bt_vis; op_vis:= _op_vis;
         bt_act:= _bt_act; op_act:= _op_act
       end;


 procedure TSButton.Draw;
     var   _ct,_ck : byte;
     begin
       if check_adr=nil then visible:= false else visible:= op_bool(bool(check_adr^),en_bool);
       if bt_vis<>nil then visible:= op_bool(bt_vis^,op_vis);
       if bt_act=nil then active:= true else active:= op_bool(bt_act^,op_act);

       _ct:= ct; _ck:= ck;
       if (not active) then begin ct:= clGR8; ck:= clGR8 end;
       if visible then inherited Draw else hide;
       ct:= _ct; ck:= _ck
     end;


 procedure TSButton.HandleEvent(var _Event: TEvent);
     begin
       if active then inherited HandleEvent(_Event)
     end;

 procedure TSButton.check;
     var   b1,b2,b3: bool;
     begin
       if check_adr=nil then Exit;

       if check_adr=nil then b1:= false else b1:= op_bool(bool(check_adr^),en_bool);
       if bt_vis=nil then b2:= b1 else b2:= op_bool(bt_vis^,op_vis);
       if bt_act=nil then b3:= b1 else b3:= op_bool(bt_act^,op_act);

       if (b1<>visible) or (b2<>visible) or (b3<>active) then Draw;
     end;

 procedure  TSButton.parameters (_bt_vis : pbool; _op_vis : bool;
                                 _bt_act : pbool; _op_act : bool
                                );
     begin
       bt_vis:= _bt_vis; op_vis:= _op_vis;
       bt_act:= _bt_act; op_act:= _op_act
     end;
