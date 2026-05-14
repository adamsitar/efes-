{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TPrompt                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TPrompt.Ask(var _Event: TEvent; _cmXXXX: word; _title,_s, _nie: string; _cl,_bk: int; _loops: long);
      var   dx,dy: int;
      begin
        Init(_cmXXXX, _title,_s, _nie, _cl,_bk, _loops);
        Run(_Event);
        Done
      end;


constructor TPrompt.Init(_cmXXXX: word; _title,_s, _nie: string; _cl,_bk: int; _loops: long);
      var   dx,dy,l: int;
            m : TMess;
      begin
       {$IFDEF ARCHIVE_PROGRAM_ERR}
        _write_err_log(_s+'  ('+WordToHex(Seg(Self))+':'+WordToHex(Ofs(Self))+')');
       {$ENDIF}
        s:= _s;
        if (_cl=0) and (_bk=0) then begin _cl:= clGRe; _bk:= clBUTTON_COLOR-2 end;
        cl:= _cl; bk:= _bk;
        loops:= _loops;

        {SetTextStyle(0, HorizDir, 1);
        l := Minimum(Maximum(length(_title),length(s)+3),MaxX div Maximum(1,TextWidth('W'))-10);
        if l<length(s) then s:= copy(s,1,l-3)+'...';
        dx:= Maximum(TextWidth(_title),TextWidth(s)+20);
        dy:= TextHeight('H') * 6;}
        s:= _s+NULL;
        m[0]:= @s[1];
        _title:= _title+' ';
        message_split(@m,1, 0,0, _title, mp,ms, dx,dy);

        inherited Init(nil, 0,0, dx,dy, kbEnter, _cmXXXX, _title, _nie, true, 1,0, false);
        Centre;
        {hlpXXX:= hlp_ask;}

        start_tick:= GetTicks;
        beep:= nil;
      end;


procedure TPrompt.Draw_;
    var   bp : bool;
          xl,yl : int;
    begin
      _message_draw(x0,y0,x1,y1, mp,ms, cl,bk)
      (*FillWin(x0+12,y0+btHEIGHT+22,x1-12,y1-btHEIGHT-22,bk);
      on_off(x0+10,y0+btHEIGHT+20,x1-10,y1-btHEIGHT-20,
            clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall,btOFF
            );
      {$IFDEF SPEA} SetBkColor(clBUTTON_COLOR); {$ENDIF}
      WriteCentr(x0,x1,y0,y1, s, cl);
      *)
    end;


function  TPrompt.HelpDisplayed(var _Event: TEvent): bool;
   var    bres: bool;
   begin
     bres:= inherited HelpDisplayed(_Event);
     if bres then start_tick:= GetTicks;
     HelpDisplayed:= bres
   end;

procedure TPrompt.Idle(var _Event: TEvent);
    begin
      if (loops<>-1) and TimeOut(start_tick, GetTicks, loops) then SetCommand(_Event,cmCancel)
    end;


function  TPrompt.Result(_Event: TEvent): TAnswer;
   var    res: TAnswer;
          sres: string;
   begin
     if isCommand(_Event,btTitle^.cmXXXX) then res:= ansAno
     else if isCommand(_Event,cmClose) then res:= ansNie     { logicky opacne Close<-> Cancel, ale kto to ma opravovat }
     else res:= ansZrus;
     {$IFDEF ARCHIVE_PROGRAM_ERR}
      sres:= strpas(titAnswer[res]);
      {if (btOK<>nil) and isCommand(_Event,btOK^.cmXXXX) then sres:= strpas(btOK^.title)
      else if (btCancel<>nil) and isCommand(_Event,btCancel^.cmXXXX) then sres:= strpas(btCancel^.title);}
      _write_err_log('('+WordToHex(Seg(Self))+':'+WordToHex(Ofs(Self))+')'+' -> '+delchar(sres,[cnst_HotKey]));
     {$ENDIF}
     Result:= res
   end;


procedure TPrompt.InitApp2;
    begin
      if beep<>nil then {if} TBFunc(beep) {then};
      start_tick:= GetTicks
    end;


destructor TPrompt.Done;
     var   i: int;
     begin
       for i:= 0 to ms-1 do strdispose(mp[i]);
       inherited Done
     end;

