{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollInd                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

function comp_Dir_name(p1,p2: PFileAttr): bool;
   begin
     comp_Dir_name:= p1^.name < p2^.name
   end;

function comp_Dir_date(p1,p2: PFileAttr): bool;
   begin
     comp_Dir_date:= p1^.date > p2^.date
   end;


constructor TScrollDIR.Init(_path,_name  : string;
                            _title,_mess : string;

                            _p_filter    : PBFunc_s;
                            _p_decode_fn : pointer;
                            _add_info  : bool;
                            _dx : int;

                            _comp_dir : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                            _comp_by  : byte;     { 0 - dir, 1 - items }
                            _handler  : pointer;  { TIFunc_s }

                            _hlpXXX : Pchar
                           );
      var   dx: int;
      begin
        path:= _path; name:= _name;
        mess:= _mess;

        p_filter:= _p_filter;
        Dir := nil; Files := 0;
        select := nil;
        items := nil;

        comp_dir:= _comp_dir;
        comp_by:=  _comp_by;

        add_info:= _add_info;
        if add_info then dx:= 24 else dx:= 13;
        p_decode_fn:= _p_decode_fn;
        fn:= '';

        inherited Init(nil,_title,
                       nil,nil,true, nil,nil,nil,
                       0,nil,nil,
                       nil,nil,nil,
                       dx*8{_item_dx}+_dx,dy_FN+1{_item_dy},
                       0,0,2,0,
                       nil{_item_list},
                       minimum(1+GetNmbOfFiles(path+name),max_page_SCROLL_DIR),
                       true,true,true,

                       0,0, nil,nil,nil,
                       _TNull,_handler,nil,
                       _hlpXXX {nil _arr ,}
                      );
        bg:= __bgsl;
        pos_en:= true
      end;


procedure TScrollDIR.new_data;
    var   dx,_dx,i: int;
          s: string;
    begin
      disp_data;
      GetDir_(Path+Name, Dir, DataAttr, Files,p_filter);
      top:= Files-1;
      arr_adr:= pointer(Dir);
      inherited new_data;

      dx:= x1-x0;
      if Files>0 then
         begin
           if p_decode_fn<>nil then
              begin
                {items:= New(PstreamPackedStrings,Init);
                for i:= 0 to top do altern^.add(TSFunc_s(p_decode_fn)(Dir^[get_ind(i)]^.name))
                }
                GetMem (items, sizeof(pchar)*(Files));
                for i:= 0 to Files-1 do
                  begin
                    s:= TSFunc_s(p_decode_fn)(Dir^[get_ind(i)]^.name);
                    items^[i]:= StrPasNew(s);
                    _dx:= 3*__dxisl + length(s) shl 3;
                    if _dx > dx then dx:= _dx
                  end;
              end
           else items:= nil;
           GetMem(select,sizeof(bool)*Files);
           FillChar(select^,sizeof(bool)*Files,0)
         end;
      if dx>x1-x0 then
         begin
           dx:= dx-(x1-x0);
           TView.ReSize(dx,0);
           inc(win^.x1,dx);
           win^.btEsc^.MoveRel(dx,0);
           win^.btTitle^.ReSize(dx,0);
           sb^.MoveRel(dx,0)
         end;

      if comp_dir<>nil then
         if (comp_by=0) and QuickSort_IndArr(ind,Pptrs(Dir),comp_dir,0,top) then top_prev:= -1
         else if (comp_by=1) and (items<>nil) and QuickSort_IndArr(ind,Pptrs(items),comp_dir,0,top) then top_prev:= -1
    end;

procedure TScrollDIR.disp_data;
    var   i : int;
    begin
      if Files>0 then
         begin
           {if altern<>nil then Dispose(altern,Done)}
           if items<>nil then
              begin
                for i:= 0 to Files-1 do StrDispose(items^[get_ind(i)]);
                FreeMem (items, sizeof(pchar)*(Files));
              end;
           if select<>nil then FreeMem (select,sizeof(bool)*Files);
           if Dir<>nil then FreeDirFiles(Dir,Files)
         end;
      inherited disp_data;
      items:= nil;
      select:= nil;
      Dir:= nil;
    end;


procedure TScrollDir.HandleEvent(var _Event: TEvent);
    var   i,r: int;
          is: bool;
          s: string;
    begin
      if     (handler<>nil)
         and (_Event.What = evKeyDown)
         and (_Event.Key in [kbEnter,kbIns,' ','*','-','+']) then
             case _Event.Key of
               kbEnter  : SetCommand(_Event,cmOK);
               kbIns,' ': SetCommand(_Event,cmScrollItemClicked);
               '*'      : begin
                            for i:= 0 to Files-1 do select^[i]:= not select^[i];
                            List
                          end;
               '-'      : begin
                            for i:= 0 to Files-1 do select^[i]:= false;
                            List
                          end;
               '+'      : begin
                            for i:= 0 to Files-1 do select^[i]:= true;
                            List
                          end
             end
      else inherited HandleEvent(_Event);

      is:= (   isCommand(_Event,cmScrollItemEntered)
            or isCommand(_Event,cmScrollItemClicked)
           );

      if is and (handler<>nil) then
         begin
           select^[pos]:= not select^[pos];
           item_list(pos, get_x,get_yi(pos), true);
           if SELECT_DOWN_SCROLL then
              begin
                SetKeyEvent(_Event,@Self,kbDown);
                inherited HandleEvent(_Event)
              end;
           ClearEvent(_Event)
         end

      else if    (is and (handler=nil))
              or isCommand(_Event,cmOK)
              or win^.btTitle^.isClicked(_Event) then
              begin
                with win^.btTitle^ do OnOff(TbtStat(not bool(stat)));
                r:= do_it;
                if (r<=0) then SetCommand(_Event,cmClose)
                else if r>0 then
                        begin
                          Err2('',ErrorMessage(r,path+name));
                          ClearEvent(_Event)
                        end;
                Wait(1,nil);
                with win^.btTitle^ do OnOff(TbtStat(not bool(stat)))
              end
    end; { TScrollAct.HandleEvent }



procedure TScrollDIR.item_list(i, x,y: int; b: bool);
    const bk : array[false..true] of byte = (__bgsl,__bgsl-1);
          co : array[false..true] of byte = (clGRa,clGRe);
    var   s  : string;
    begin
      if b then BGIgraph.button(x0+dxi-1,y-2,x1-dxi,y+TextHeight('H')+1,bk[b], btSmall,btON)
      else FillWin(x0+dxi-1,y-2,x1-dxi,y+TextHeight('H')+1, bk[b]);
      SetColor(co[select^[i]]);
      if (p_decode_fn<>nil) and (items<>nil) then s:= strpas(items^[get_ind(i)])
      else s:= Dir^[get_ind(i)]^.name;
      if add_info then s:= s + '  ' + inttostr(Dir^[get_ind(i)]^.size,9,1);
      s:= copy(s,1,minimum(length(s),(x1-x0-2*__dxisl) shr 3));
      OutTextXY(x+4,y+1, s)
    end;


function  TScrollDIR.do_it: int;
    var   p,i,
          r: int;
    begin
      r:= 0; i:= 0; p:= 0;
      if (handler<>nil) then
         while (i<Files) and (r=0) do
           begin
             if select^[i] then
                begin
                  if mess<>'' then InfoCakaj(msgINFO,Dir^[get_ind(i)]^.name+': '+mess);
                  r:= TIFunc_s(handler)(path+Dir^[get_ind(i)]^.name);
                  if mess<>'' then InfoCakaj_zatvor;
                  if r=0 then
                     begin
                       select^[i]:= not select^[i];
                       item_list(i, get_x,get_yi(i), i=pos)
                     end;
                  if kbhit and (GetKey=kbEsc) then r:= io_intr_by_user;
                  if (r=io_intr_by_user) then
                     if Ask2(msgVERIPHY,ask_CancelProc,titNO,
                             White,clBUTTON_COLOR,waitASK*18
                            ) = ansAno
                        then
                          begin
                            Say2(msgMESS,msg_CancelProc);
                            break
                          end
                     else r:= 0
                  else inc(p)
                end;
             inc(i)
           end
      else fn:= path+Dir^[get_ind(pos)]^.name;
      if p=0 then r:= -1;
      do_it:= r
    end;


function  scroll_DIR(_path,_name  : string;
                     _title,_mess : string;

                     _p_filter    : PBFunc_s;
                     _p_decode_fn : pointer;
                     _add_info  : bool;
                     _dx : int;

                     _comp_dir : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                     _comp_by  : byte;     { 0 - dir, 1 - items }
                     _handler  : pointer;  { TIFunc_s }

                     _hlpXXX : Pchar
                    ): string;

   var    sc: PScrollDIR;
          _Event: TEvent;
          info: pchar;
   begin
     sc:= New(PScrollDIR,Init(_path,_name, _title,_mess,
                              _p_filter,_p_decode_fn,_add_info,_dx,
                              _comp_dir,_comp_by,
                              _handler,
                              _hlpXXX
                             ));
     if _handler<>nil then info:= SCROLL_NC else info:= SCROLL_SEL;
     sc^.RunLocalFunc(_Event,info);
     scroll_DIR:= sc^.fn;
     dispose(sc,Done);
   end;