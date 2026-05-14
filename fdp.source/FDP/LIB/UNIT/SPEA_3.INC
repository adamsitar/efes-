{ *******************  VGA Window Functions **************** }


{ ---------------- Set Position of VGA window -------------- }

procedure spvspos ( x, y : int );
begin
	packet.pvspos.pfunc := SPVSPOSF;
	packet.pvspos.x := x;
	packet.pvspos.y := y;
        call_graphic_driver;
end;




{ ---------------- Get Position of VGA window -------------- }

procedure spvgpos ( var x, y : int );
begin
	packet.pvgpos.pfunc := SPVGPOSF;
        call_graphic_driver;
	x := packet.pvgpos.x;
	y := packet.pvgpos.y;
end;



{ ----------------- Define VGA window ---------------------- }

procedure spvswindow ( x1, y1, x2, y2 : int );
begin
	packet.pvswindow.pfunc := SPVSWINDF;
	packet.pvswindow.x1 := x1;
	packet.pvswindow.y1 := y1;
	packet.pvswindow.x2 := x2;
	packet.pvswindow.y2 := y2;
        call_graphic_driver;
end;



{ ----------------- Get Info of defined VGA window --------- }

procedure spvgwindow ( var x1, y1, x2, y2 : int );
begin
	packet.pvgwindow.pfunc := SPVGWINDF;
        call_graphic_driver;
	x1 := packet.pvgwindow.x1 ;
	y1 := packet.pvgwindow.y1 ;
	x2 := packet.pvgwindow.x2 ;
	y2 := packet.pvgwindow.y2 ;
end;



{ ----------------- Set zoom factor ----------------------- }

procedure spvzoom ( zfactor : int );
begin
	packet.pvzoom.pfunc := SPVZOOMF;
	packet.pvzoom.zfactor := zfactor;
        call_graphic_driver;
end;



{ ----------------- Get size of VGA window --------------- }

procedure spvgsize ( var x, y : int );
begin
	packet.pvgsize.pfunc := SPVGSIZEF;
        call_graphic_driver;
	x := packet.pvgsize.x;
	y := packet.pvgsize.y;
end;



{ ----------------- Set display mode -------------------- }

procedure spvdisp ( mode : int );
begin
	packet.pvdisp.pfunc := SPVDISPF;
	packet.pvdisp.mode := mode;
        call_graphic_driver;
end;



{ ----------------- Get display mode -------------------- }

procedure spvgdisp ( var mode : int );
begin
	packet.pvgdisp.pfunc := SPVGDISPF;
  	call_graphic_driver;
	mode := packet.pvgdisp.mode;
end;



{ ----------------- Get zoom factor ----------------------- }

procedure spvgzoom ( var zfactor : int );
begin
	packet.pvgzoom.pfunc := SPVGZOOMF;
        call_graphic_driver;
	zfactor := packet.pvgzoom.zfactor;
end;



procedure VGAmove(_dx,_dy: int);
    var   x,y: int;
    begin
      x:= Limit(VGAx1+_dx,0,MaxX-VGAdx,0);
      y:= Limit(VGAy1+_dy,0,MaxY-VGAdy,0);
      if (x<>VGAx1) or (y<>VGAy1) then
         begin
           VGAx1:= x;
           VGAy1:= y;
           SPvspos(VGAx1,VGAy1)
         end
    end; { VGAmove }

procedure VGAresize(_dx,_dy: int);
    var   dx,dy: int;
    begin
      dx:= Limit(VGAdx+_dx,200,Minimum(648,MaxX-VGAx1),0);
      dy:= Limit(VGAdy+_dy,100,Minimum(488,MaxY-VGAy1),0);
      if (dx<>VGAdx) or (dy<>VGAdy) then
         begin
           VGAdx:= dx;
           VGAdy:= dy;
           SPvswindow(8,8,VGAdx,VGAdy)
         end
    end; { VGAresize }

