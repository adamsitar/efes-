function GetMaxXM: int;
   begin
     {$IFNDEF SPEA}
       if GraphMode<_TIGA then GetMaxXM:= GetMaxX
       else GetMaxXM:= 1279
     {$ELSE}
       GetMaxXM:= GetMaxX
     {$ENDIF}
   end;

procedure set_GrMode(__GraphMode: TGraphMode);
    var   bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      ClearDevice;
      SetGraphMode(ord(__GraphMode)+1);
      DirectVideo:= true;
      MaxColor := GetMaxColor;  { Get the maximum allowable drawing color }
      MaxX:= GetMaxXM;
      MaxY:= GetMaxY;
      set_RGBpallete;
      SetWriteMode(0);
      m_clip(0,0,GetMaxX,GetMaxY);
      set_xy(GetMaxX shr 1,GetMaxY shr 1);
      m_on(bp, xl,yl);
{    end;

procedure set_GrMode(__GraphMode: TGraphMode);
    begin
      GrMode(__GraphMode);}
      GraphMode:= __GraphMode
    end;

