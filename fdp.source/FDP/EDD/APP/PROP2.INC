{ prepinanie medzi PROP a ACC ------------------------------ }

procedure TwinPROP.ActiveOn;
    begin
      inherited ActiveOn;
      with btTitle^ do
        begin
          {ck:= 61; ct:= 61;}
          stat:= btON;
          Draw
        end
    end;

procedure TwinPROP.ActiveOff;
    begin
      inherited ActiveOff;
      with btTitle^ do
        begin
          {ck:= clItem; ct:= clItem;}
          stat:= btOFF;
          Draw
        end
    end;


procedure TwinPROP.zapni;
    begin
      ActiveOn
    end;

procedure TwinPROP.vypni;
    begin
      ActiveOff
    end;
