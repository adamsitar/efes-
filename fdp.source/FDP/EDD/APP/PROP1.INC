procedure TwinPROP.add(_iFPL: PSTRIP; _ind: int);
    var   TempWinReg : PWinReg;
          _pos: int;
    begin
      PIS:= vypis_do_okna(x0,y0,x1,y1, TempWinReg,-1,ScreenDesc);
      if not PIS then PREPIS:= absTime;

      inherited add(_iFPL,_ind);

      _pos:= find(_iFPL,_ind);
      {FPL := iFPL^[_ind]^.ind];
       if PROP_PRN and REC_PROP_PRN then _iFPL^.tlac(FPL, false);
      }
      if not is_ack(_pos) then is_to_ack:= true; {accept(_pos);}

      obnov_okna(TempWinReg, true);
      EDDgui^.edd_status
    end;

procedure TwinPROP.del(_iFPL: PSTRIP; _ind: int; _zrus: bool);
    var   TempWinReg : PWinReg;
          _pos: int;
    begin
      PIS:= vypis_do_okna(x0,y0,x1,y1, TempWinReg,-1,ScreenDesc);
      if not PIS then PREPIS:= absTime;
      inherited del(_iFPL, _ind, _zrus);
      obnov_okna(TempWinReg, true);

      EDDgui^.edd_status
    end;


function  TwinPROP.is_ack(_pos: int): bool;
   var    iFPL : PSTRIP;
   begin
     iFPL:= FPLs^[_pos]^.iFPL;
     if pointer(iFPL)=pointer(PROP_cFPL)      then is_ack:= PROP_ACK_cFPL
     else if pointer(iFPL)=pointer(PROP_mFPL) then is_ack:= PROP_ACK_mFPL
     else if pointer(iFPL)=pointer(PROP_oFPL) then is_ack:= PROP_ACK_oFPL
     else is_ack:= false
   end;

procedure TwinPROP.check;

    var   TempWinReg : PWinReg;
          iFPL       : PSTRIP;
          FPL        : pointer;
          i          : int;

    const s_check : bool = false;

    begin
      if s_check then Exit;

      if    (is_to_ack)
         or ((not PROP_ACK_cFPL) and (prop_cFPL_top<>prop_cFPL^.top))
         or ((not PROP_ACK_mFPL) and (prop_mFPL_top<>prop_mFPL^.top))
         or ((not PROP_ACK_oFPL) and (prop_oFPL_top<>prop_oFPL^.top))
         then
      else Exit;

      is_to_ack:= false;      { ak sa nahodou v dalsom zmeni, nestrati sa informacia o tom }
      s_check:= true;

      PIS:= vypis_do_okna(x0,y0,x1,y1, TempWinReg,-1,ScreenDesc);
      if not PIS then PREPIS:= absTime;

      { Prevzatie prislusnych stripov zo zoznamu (nepotrebuju potvrdenie)
      }
      {$IFNDEF SECTORS}
        i:= 0; while (i<=top) do
          begin
            if not is_ack(i) then
               begin
                 accept(i)
               end
            else inc(i)
          end;
      {$ELSE}
        if not PROP_ACK_cFPL then while prop_cFPL^.top>=0 do accept_FPL(prop_cFPL,cFPL,0,prop_cFPL_top);
        if not PROP_ACK_mFPL then while prop_mFPL^.top>=0 do accept_FPL(prop_mFPL,mFPL,0,prop_mFPL_top);
        if not PROP_ACK_oFPL then while prop_oFPL^.top>=0 do accept_FPL(prop_oFPL,oFPL,0,prop_oFPL_top);
      {$ENDIF}

      EDDgui^.edd_status;
      obnov_okna(TempWinReg, true);

      s_check:= false
    end;


procedure TwinPROP.accept (_pos: int);
   var    iFPL,nFPL : PSTRIP;
          FPL : pointer;
   begin
     iFPL:= FPLs^[_pos]^.iFPL;
     FPL := iFPL^.ap^[FPLs^[_pos]^.ind];

     if      pointer(iFPL)=pointer(PROP_cFPL) then nFPL:= cFPL
     else if pointer(iFPL)=pointer(PROP_mFPL) then nFPL:= mFPL
     else if pointer(iFPL)=pointer(PROP_oFPL) then nFPL:= oFPL
     else nFPL:= nil;
     {if PROP_PRN and (not REC_PROP_PRN) then iFPL^.tlac(FPL, false);}
     if nFPL<>nil then nFPL^.Add(FPL);
     FPLs^[_pos]^.iFPL^.del(FPLs^[_pos]^.ind)
   end;

procedure TwinPROP.decline(_pos: int);
    begin
      FPLs^[_pos]^.iFPL^.del(FPLs^[_pos]^.ind)
    end;


procedure TwinPROP.accept_FPL(const prop_FPLs,acc_FPLs: P_OFPL; _pos: int; var _top: int);
    begin
      if (prop_FPLs=nil) or (acc_FPLs=nil) or (_pos<0) then Exit;

      acc_FPLs^.Add(prop_FPLs^.ap^[_pos]);
      prop_FPLs^.del(_pos);
      _top:= prop_FPLs^.top
    end;

procedure TwinPROP.decline_FPL(const prop_FPLs: P_OFPL; _pos: int; var _top: int);
    begin
      if (prop_FPLs=nil) or (_pos<0) then Exit;

      prop_FPLs^.del(_pos);
      _top:= prop_FPLs^.top
    end;


