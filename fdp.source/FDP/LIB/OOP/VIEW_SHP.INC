{ ------------------------------------------------------------ }
{  Ovladac prepinania kurzorov mysi                            }
{ ------------------------------------------------------------ }
{
 zisti, ci mys je v nejakom aktualnom okne
 a podla toho nastavi tvar kurzora
}
function View__m_shape(V: PObject): bool; far;
   begin
     View__m_shape:=     (V^.ObjectType >= obj_view)
                     and (PView(V)^.inView(mouse_status.stat.x,mouse_status.stat.y))
   end;

procedure m_shape; far;
    var   S: PObjectReg;
    begin
      if Application=nil then exit;
      {$IFDEF MYS_VO_VRCHNOM}
         with Application^ do PView(ObjectPtr)^.m_shape
      {$ELSE}
         S:= Application;
         FirstThat(@View__m_shape,S);
         if S<>nil then S^.ViewPtr^.m_shape;
      {$ENDIF}
    end;


var  SaveMain : TProc;

procedure check_views; far;
    const semaphor: bool = false;
    begin
      if @SaveMain<>nil then SaveMain;
      if semaphor then Exit;
      semaphor:= true;

      semaphor:= false
    end;
