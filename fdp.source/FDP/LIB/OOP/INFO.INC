{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TInfo                                                    Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
constructor TInfo.Init(_title,_btOKtitle: string;
                       _text, _text_p: pointer; _dx,_dy: int;
                       _messp: PMess; _size: int;
                       _cl,_bk: int;
                       _beep1, _beep2: pointer;
                       _loops: long; _time_out, _res: pbool;
                       _start_tick: long; _do_it: pointer; _data : pointer
                      );
      var   dxt,dxr, dy, i,j: int;
            pom : char;
            p : pchar;
            s : string;
      begin
       {$IFDEF ARCHIVE_PROGRAM_ERR}
         if archive_info_mess then
            begin
              _write_err_log(_title);

              for i:= 0 to _size-1 do
                  begin
                    _another_line_err_log:= i>0;
                    _write_err_log(strpas(_messp^[i]))
                  end;

              archive_info_mess:= false
            end;
       {$ENDIF}

        beep1:= _beep1; beep2:= _beep2;
        do_it:= _do_it; data:= _data;

        res:= _res;
        if res<>nil then bool(res^):= true;
        time_out:= _time_out; loops:= _loops;
        if time_out<>nil then bool(time_out^):= false;

        check:= nil;
        cl:= _cl; if bk<>-1 then bk:= _bk else bk:= clBUTTON_COLOR;

       { rozlozenie spravy tak, aby vosla na obrazovku
       }
        _title:= _title+' ';
        message_split(_messp,_size, _dx,_dy,_title, mp,ms, dxt,dy);
        if do_it=nil then inc(dy,20);

        inherited Init(nil, 0,0, dxt,dy, kbEnter, cmOK, _title, true);
        btTitle^.kbHot:= kbNoKey; btTitle^.cmXXXX:= cmNil;
        set_text(_text, _text_p);

        if do_it=nil then
           begin
             i:= (x1 - x0 - dbtWIDTH) shr 1; j:= y1-dbtHEIGHT-10;
             if _btOKtitle<>'' then btOK:= New(PTextIcon,Init(@Self,i,j, 60,5,kbEnter, cmOk,_btOKtitle,@icYes))
             else btOK:= New(PbtOK,Init(@Self,i,j,kbEnter));
             start_tick:= getticks
           end
        else begin
               mcursor:= HODINY;
               start_tick:= _start_tick
             end;
        Centre;

        lmain:= true;
      end;


function  TInfo.HelpDisplayed(var _Event: TEvent): bool;
   var    bres: bool;
   begin
     bres:= inherited HelpDisplayed(_Event);
     if bres then start_tick:= GetTicks;
     HelpDisplayed:= bres
   end;


procedure TInfo.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if res<>nil then res^:= not (isCommand(_Event,cmCancel) or isCommand(_Event,cmClose))
    end;


procedure TInfo.Draw_;
    begin
      if text=nil then _message_draw(x0,y0,x1,y1, mp,ms, cl,bk)
      else inherited Draw_
    end;


procedure TInfo.LocalMain(var _Event: TEvent);
    begin
      if not lmain then Exit;
      if check<>nil then
         begin
           if TBFunc_p2(check)(@Self,text_p) then Draw_
         end
      else if ((do_it<>nil) and (TBfunc_p(do_it)(data))) then SetCommand(_Event,cmOK)
      else if (loops<>-1) and TimeOut(start_tick, GetTicks, loops) then
              begin
                SetCommand(_Event,cmCancel);
                if time_out<>nil then bool(time_out^):= true
              end
    end;


procedure TInfo.InitApp2;
    begin
      if beep1<>nil then {if} TBFunc(beep1) {then};
      start_tick:= GetTicks
    end;

procedure TInfo.Run(var _Event: TEvent);
    begin
      inc(MainEnabledD);
      inherited Run(_Event);
      dec(MainEnabledD);
    end;

procedure TInfo.DoneApp2;
    begin
      if (beep2<>nil) then TBFunc(beep2);
    end;

destructor TInfo.Done;
     var   i: int;
     begin
       for i:= 0 to ms-1 do strdispose(mp[i]);
       inherited Done
     end;


