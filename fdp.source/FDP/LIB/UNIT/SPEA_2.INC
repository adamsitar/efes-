
{ ---------------- Get Screen Info ----------------------- }

procedure spinfo ( var dversion, card, base_address, xsize,ysize,xmem,ymem : int) ;
begin
	packet.pinfo.pfunc := SPINFOF	;
	call_graphic_driver;
	dversion := packet.pinfo.dversion;
	card := 	packet.pinfo.card;
	base_address := packet.pinfo.base_address;
	xsize := 	packet.pinfo.xsize;
	ysize := 	packet.pinfo.ysize;
	xmem := 	packet.pinfo.xmem;
	ymem := 	packet.pinfo.ymem;
end;



{ ---------------- Get Page Info ----------------------- }

procedure spipage ( var max_page, sel_page, show_page : int) ;
begin
	packet.pipage.pfunc := SPIPAGEF	;					
	call_graphic_driver;
	max_page := packet.pipage.max_page;
	sel_page := packet.pipage.sel_page;
	show_page := packet.pipage.show_page;
end;



{ ---------------- Get Colour Info ----------------------- }

procedure spicolor ( var bit_planes, max_color, nshades : int) ;
begin
	packet.picolor.pfunc := SPICOLF	;
	call_graphic_driver;
	bit_planes := packet.picolor.bit_planes;
	max_color := packet.picolor.max_color;
	nshades := packet.picolor.nshades;
end;



{ ---------------- Get Font Info ----------------------- }

procedure spifont ( var max_char, xchar, ychar : int) ;
begin
	packet.pifont.pfunc := SPIFONTF	;					
	call_graphic_driver;
	max_char := packet.pifont.max_char;
	xchar := packet.pifont.xchar;
	ychar := packet.pifont.ychar;
end;



{ ----------------- Set Current Foreground Colour ------------------------ }

procedure SPcolor(ccolor: word);
    begin
      packet.pccolor.pfunc  := SPCCOLF;
      packet.pccolor.ccolor := int(ccolor);
      call_graphic_driver;
      SPcol:= ccolor;
    end;



{ ----------------  Set Current Background Colour  ------------------ }

procedure SPbcolor(bcolor: word);
    begin
      packet.pbcolor.pfunc  := SPBCOLF;
      packet.pbcolor.bcolor := int(bcolor);
      call_graphic_driver;
      SPbcol:= bcolor
    end;



{ ----------------  Set Current Operation Mode  ------------------ }

procedure SPopmode(op_mode: int);
    begin
      packet.popmode.pfunc  := SPOPMODF;
      packet.popmode.opmode := op_mode;
      call_graphic_driver
    end;


{ ----------------  Set Current Line Style ---------------- }

procedure	splstyle ( lstyle : word);
begin
	packet.plstyle.pfunc := SPLSTYLF;
	packet.plstyle.pattern := lstyle;						
	call_graphic_driver;
end;



{ ----------------  Set Look-Up Table  ------------------ }

procedure SPsetvlu(index, red,green,blue: int);
    begin
      packet.psetvlu.pfunc:= SPSVLUF;
      packet.psetvlu.index:= index;
      packet.psetvlu.red  := red;
      packet.psetvlu.green:= green;
      packet.psetvlu.blue := blue;
      call_graphic_driver;
    end;



{ ----------------  Get Look-Up Table  ------------------ }

procedure SPgetvlu(var index,red,green,blue: int);
    begin
      packet.psetvlu.pfunc:= SPGVLUF;
      call_graphic_driver;
      index := packet.pgetvlu.index;
      red   := packet.pgetvlu.red;
      green := packet.pgetvlu.green;
      blue  := packet.pgetvlu.blue;
    end;



{ ---------------- Reset Look-Up Table ---------------------- }

procedure SPresetvlu;
    begin
      packet.presetvlu.pfunc := SPRVLUF;
      call_graphic_driver;
    end;



{ ----------------  Set Drawing Page  ------------------ }

procedure	spselpg ( page : int);
begin
	packet.pselpg.pfunc := SPSELPGF;
	packet.pselpg.page := page;						
	call_graphic_driver;
end;



{ ----------------  Set Show Page  ------------------ }

procedure	spshwpg (  page : int);
begin
	packet.pshwpg.pfunc := SPSHWPGF;					
	packet.pshwpg.page := page;						
	call_graphic_driver;
end;



{ ----------------  Set Split Screen  ------------------ }

procedure	spsplit (  scr, px, py, ysize : int);
begin
	packet.psplit.pfunc := SPSPLITF;					
	packet.psplit.scr := scr;						
	packet.psplit.px := px;						
	packet.psplit.py := py;
	packet.psplit.ysize := ysize;						
	call_graphic_driver;
end;



{ ----------------  Set Split Screen enable / disable  ------------------ }

procedure	spshow (  enable : int);
begin
	packet.pshow.pfunc := SPSHOWF;					
	packet.pshow.enable := enable;						
	call_graphic_driver;
end;




{
  Set and Enable Hardware Clip Window
}
procedure SPclip(x1,y1, x2,y2: int );
    begin
      packet.pclip.pfunc := SPCLIPF;
      packet.pclip.x1 := x1;
      packet.pclip.y1 := y1;
      packet.pclip.x2 := x2;
      packet.pclip.y2 := y2;
      call_graphic_driver
    end;

{
  Disable Hardware Clip
}
procedure SPnoclip;
    begin
      packet.pnclip.pfunc := SPNCLIPF;
      call_graphic_driver
    end;



{ ----------------- Select active card ---------------------------------- }

function	spselcard ( cardnr : int ) : int;
begin
	packet.pslcard.pfunc := SPSLCARDF ;
	packet.pslcard.cardnr := cardnr;
	call_graphic_driver;
	spselcard := packet.pslcard.status;
end;




{ ----------------- Draw Text ------------------------- }

procedure SPtext(_x,_y: int; txt: str255);
    begin
      with packet.ptext do
        begin
          pfunc   := SPTEXTF;
          x	  := _x;
          y	  := _y;
          n       := Length(txt);
          segment := seg(txt[1]);
          offset  := ofs(txt[1])
        end;
      call_graphic_driver
    end;


{ -------------------- Draw Text direction ----------------------- }

function 	sptxtdir ( textdir : int ): int ;
begin

	packet.ptextd.pfunc := SPTXTDF;
	packet.ptextd.textdir := textdir;
	call_graphic_driver;
	sptxtdir := packet.ptextd.status ;	
end;



{ -------------------- Draw Text orient ----------------------- }

function	sptxtori ( textori : int ): int ;
begin

	packet.ptexto.pfunc := SPTXTOF;
	packet.ptexto.textori := textori;
	call_graphic_driver;
	sptxtori := packet.ptexto.status ;	
	
end;




{ ----------------  Set Pattern  ------------------ }

procedure spspatt ( xsize, ysize, zoomx,zoomy, xpointer, ypointer : int;var patt : pattbuff );
begin
	packet.pspatt.pfunc := SPSPATTF;					
	packet.pspatt.xsize := xsize;						
	packet.pspatt.ysize := ysize;						
	packet.pspatt.zoomx := zoomx;
	packet.pspatt.zoomy := zoomy;						
	packet.pspatt.xpointer := xpointer;						
	packet.pspatt.ypointer := ypointer;						
	packet.pspatt.segment := seg ( patt[0] );
	packet.pspatt.offset  := ofs ( patt[0] );						
	call_graphic_driver;
end;



{ ----------------  Draw Pattern  ------------------ }

procedure SPdpatt(x,y, xsize,ysize, szx,szy, zoomx,zoomy, dir: int );
    begin
      packet.pdpatt.pfunc := SPDPATTF;
      packet.pdpatt.x := x;
      packet.pdpatt.y := y;
      packet.pdpatt.xsize := xsize;
      packet.pdpatt.ysize := ysize;
      packet.pdpatt.szx := szx;
      packet.pdpatt.szy := szy;
      packet.pdpatt.zoomx := zoomx;
      packet.pdpatt.zoomy := zoomy;
      packet.pdpatt.dir := dir;
      call_graphic_driver;
    end;



{ -------------------- Clear Screen --------------------------------- }

procedure spclr(color: int);
    begin
      packet.pclr.pfunc := SPCLRF;
      packet.pclr.color := color;
      call_graphic_driver
    end;



{ -------------------- Draw Dot ------------------------------------- }

procedure SPdot(x,y : int);
     begin
       packet.pdot.pfunc:= SPDOTF;
       packet.pdot.x:= x;
       packet.pdot.y:= y;
       call_graphic_driver
     end;



{ -------------------- Draw Vector ---------------------------------- }

procedure SPvect(x1,y1,x2,y2: int);
    begin
      with packet.pvect do
        begin
	  pfunc := SPVECTF;
  	  p[0]  := x1;
    	  p[1]  := y1;
 	  p[2]  := x2;
    	  p[3]  := y2;
        end;
      call_graphic_driver
    end;



{ -------------------- Draw Polyline ------------------------------- }

procedure SPpoly(nmb: int; pline_p: polybuff_p);
    begin
      with packet.ppoly do
        begin
          pfunc  := SPPOLYF;
          n      := nmb;
          segment:= seg(pline_p^[0]);
          offset := ofs(pline_p^[0])
        end;
      call_graphic_driver;
    end;

procedure SPrect(x1,y1,x2,y2: int);
    var   pline   : array[0..9] of int;
          pline_p : polybuff_p;
    begin
      pline[0]:= x1; pline[1]:= y1;
      pline[2]:= x1; pline[3]:= y2;
      pline[4]:= x2; pline[5]:= y2;
      pline[6]:= x2; pline[7]:= y1;
      pline[8]:= x1; pline[9]:= y1;
      pline_p := addr(pline[0]);
      SPpoly(5,pline_p)
    end;



{ -------------------- Pattern Filled Polygon --------------------- }

procedure SPfpoly(panel_p: polybuff_p);
    begin
      packet.pfpoly.pfunc  := SPFPOLYF;
      packet.pfpoly.segment:= seg(panel_p^[0]);
      packet.pfpoly.offset := ofs(panel_p^[0]);
      call_graphic_driver;
    end;




{ -------------------- Fill Area ---------------------------------- }

procedure SPfill(x1,y1,x2,y2: int);
    begin
      packet.pfill.pfunc := SPFILLF;
      packet.pfill.x1	 := x1;
      packet.pfill.y1	 := y1;
      packet.pfill.x2	 := x2;
      packet.pfill.y2	 := y2;
      call_graphic_driver;
    end;




{ ----------------Pattern Fill Area ---------------------------------- }

procedure sppfill (x1,y1, x2,y2: int);
begin
	packet.ppfill.pfunc := SPPFILLF;	
	packet.ppfill.x1	:= x1;
	packet.ppfill.y1	:= y1;
	packet.ppfill.x2	:= x2;
	packet.ppfill.y2	:= y2;
	call_graphic_driver;
end;



{-----------------Draw Circle -------------------------------}

procedure spcircle (  xc, yc, radius : int);
begin
	packet.pcircle.pfunc := SPCIRF;	
	packet.pcircle.xc	:= xc;
	packet.pcircle.yc	:= yc;
	packet.pcircle.radius	:= radius;
	call_graphic_driver;
end;



{-----------------Pattern filled Circle -------------------------------}

procedure SPfcircle(xc, yc, radius : int);
    begin
      packet.pfcircle.pfunc := SPFCIRF;
      packet.pfcircle.xc    := xc;
      packet.pfcircle.yc    := yc;
      packet.pfcircle.radius:= radius;
      call_graphic_driver;
    end;


{----------------- Draw Arc -----------------------------}

procedure sparc (  dir,xs,ys,xe,ye,xc, yc : int);
begin
	packet.parc.pfunc := SPARCF;	
	packet.parc.xs	:= dir;
	packet.parc.xs	:= xs;
	packet.parc.ys	:= ys;
	packet.parc.xe	:= xe;
	packet.parc.ye	:= ye;
	packet.parc.xc	:= xc;
	packet.parc.yc	:= yc;
	call_graphic_driver;
end;




{ -------------------- Read the pixels from screen --------------------- }

procedure spgetdot (  dir, p1, p2, ccord : int ; var buffer : pixbuff);
begin
	packet.pgetdot.pfunc := SPGDOTF;
	packet.pgetdot.dir	:= dir;
	packet.pgetdot.p1	:= p1;
	packet.pgetdot.p2	:= p2;	
	packet.pgetdot.ccord	:= ccord;	
	packet.pgetdot.segment := seg ( buffer [0] );
	packet.pgetdot.offset  := ofs ( buffer [0] );
	call_graphic_driver;
end;



{ -------------------- Set the pixels to screen --------------------- }

procedure spsetdot (  dir, p1, p2, ccord : int ; var buffer : pixbuff);
begin
	packet.psetdot.pfunc := SPSDOTF;
	packet.psetdot.dir	:= dir;
	packet.psetdot.p1	:= p1;
	packet.psetdot.p2	:= p2;	
	packet.psetdot.ccord	:= ccord;	
	packet.psetdot.segment := seg ( buffer [0] );
	packet.psetdot.offset  := ofs ( buffer [0] );
	call_graphic_driver;
end;



{-------------------- Copy area page to page ---------------------}

procedure SPcopy(src,x1,y1,x2,y2, dest,dx,dy: int );
    begin
      packet.pcopy.pfunc:= SPCOPYF;
      packet.pcopy.src	:= src;
      packet.pcopy.x1	:= x1;
      packet.pcopy.y1	:= y1;
      packet.pcopy.x2	:= x2;
      packet.pcopy.y2	:= y2;
      packet.pcopy.dest	:= dest;
      packet.pcopy.dx   := dx;
      packet.pcopy.dy   := dy;
      call_graphic_driver;
    end;




{ ----------------- init Raster Cursor --------------------- }


procedure spircurs ( curx, cury : int; var andmask, xormask : andxor;
                     xsize, ysize, xzoom, yzoom, xbuffer, ybuffer : int;
                     fgcolor, bgcolor : int );
begin
        packet.pircurs.pfunc := SPIRCURSF;
        packet.pircurs.curx := curx;
        packet.pircurs.cury := cury;
        packet.pircurs.andseg := seg ( andmask[0] );
        packet.pircurs.andoff := ofs ( andmask[0] );
        packet.pircurs.xorseg := seg ( xormask[0] );
        packet.pircurs.xoroff := ofs ( xormask[0] );
        packet.pircurs.xsize := xsize;
        packet.pircurs.ysize := ysize;
        packet.pircurs.xzoom := xzoom;
        packet.pircurs.yzoom := yzoom;
        packet.pircurs.xbuffer := xbuffer;
        packet.pircurs.ybuffer := ybuffer;
        packet.pircurs.fgcolor := fgcolor;
        packet.pircurs.bgcolor := bgcolor;
        call_graphic_driver;
end;



{ ----------------- draw Raster Cursor --------------------- }

procedure spdrcurs ( posx, posy : int );
begin
        packet.pdrcurs.pfunc := SPDRCURSF;
        packet.pdrcurs.posx := posx;
        packet.pdrcurs.posy := posy;
        call_graphic_driver;
end;



{ ----------------- remove Raster Cursor --------------------- }

procedure spcrcurs;
begin
        packet.pcrcurs.pfunc := SPCRCURSF;
        call_graphic_driver;
end;



function SPboxsave(x0,y0,x1,y1: int; var height: int; mode: int): int;
   begin
     packet.pboxsave.pfunc := SPBOXSAVEF;
     packet.pboxsave.x0    := x0;
     packet.pboxsave.y0    := y0;
     packet.pboxsave.x1    := x1;
     packet.pboxsave.y1    := y1;
     packet.pboxsave.mode  := mode;
     call_graphic_driver;
     height    := packet.pboxsave.height;
     SPboxsave := packet.pboxsave.id
   end;

function SPboxinq(id: int; var x0,y0,x1,y1: int; var planes: int): int;
   begin
     packet.pboxinq.pfunc := SPBOXINQF;
     packet.pboxinq.id    := id;
     call_graphic_driver;
     x0 := packet.pboxinq.x0 ;
     y0 := packet.pboxinq.y0 ;
     x1 := packet.pboxinq.x1 ;
     y1 := packet.pboxinq.y1 ;
     planes   := packet.pboxinq.planes;
     SPboxinq := packet.pboxinq.status
   end;

function SPboxrest(id, x,y: int): int;
   begin
     packet.pboxrest.pfunc := SPBOXRESTF;
     packet.pboxrest.id    := id;
     packet.pboxrest.x     := x;
     packet.pboxrest.y     := y;
     call_graphic_driver;
     SPboxrest := packet.pboxrest.status
   end;

function SPboxfree(id: int): int;
   begin
     packet.pboxfree.pfunc := SPBOXFREEF;
     packet.pboxfree.id    := id;
     call_graphic_driver;
     SPboxfree := packet.pboxfree.status;
   end;


procedure SPvectto(x1,y1: int);
    var   x2,y2: int;
    begin
      x2:= packet.pvect.p[2];
      y2:= packet.pvect.p[3];
      spvect(x2,y2,x1,y1);
    end;

procedure SPmoveto(x1,y1: int);
    begin
      packet.pvect.p[2]:= x1;
      packet.pvect.p[3]:= y1;
    end;

procedure SPvectrel(x1,y1: int);
    var   x2,y2: int;
    begin
      x2:=packet.pvect.p[2];
      y2:=packet.pvect.p[3];
      spvect(x2,y2,x2+x1,y2+y1)
    end;

procedure SPmoverel(x1,y1: int);
    begin
      packet.pvect.p[2]:= packet.pvect.p[2]+x1;
      packet.pvect.p[3]:= packet.pvect.p[3]+y1
    end;
