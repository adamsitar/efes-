{**************************************************************
*
*		spea ag
*		SPEA GRAPHICS DEVICE DRIVER
*
*		File : spunit.pas Turbo Pascal Ver. 4.00
*	  Ver  ; 1.70
*		date : 19.02.91
*
*************************************************************}

{$I comp.h}


unit SPEA;


interface



    uses  TypeDef, Dos, graph_h;


    {$I SPEA_c.h}
    {$I SPEA_t.h}


    const VGAx1: int = 610;
          VGAy1: int = 200;
          VGAdx: int = 648;
          VGAdy: int = 488;

          grResCode : byte = 0;

          {MaxXS     = 1279;
          MaxYS     = 1023;}

          maxFonts  = 6;

    const SPEAinitialized: bool = false;


    type  Tfont = record
            ind : byte;
            dx  : byte;
            dy  : byte
          end;


    var   Fonts     : array[0..maxFonts-1] of Tfont;

    var   packet    : packet_t;
          nr        : long;


    procedure SPEAinit;                                {+}
    procedure SPEAend;                                 {+}

    procedure VGAmove  (_dx,_dy: int);                 {.}
    procedure VGAresize(_dx,_dy: int);                 {.}

    function  SPselfont(fontnr: word): int;            {+}

    procedure SPinfo  ( var dversion, card, base_address, xsize,ysize,xmem,ymem : int) ;
    procedure SPipage ( var max_page, sel_page, show_page : int) ;
    procedure SPicolor( var bit_planes, max_color, nshades : int) ;
    procedure SPifont ( var max_char, xchar, ychar : int) ;

    procedure SPcolor (ccolor: word);                  {+}
    procedure SPbcolor(bcolor: word);                  {+}

    procedure SPopmode(op_mode: int);                  {+}

    procedure SPlstyle(lstyle : word);                 {+}

    procedure SPsetvlu( index, red, green, blue : int );      { SVGA }
    procedure SPgetvlu( var index, red, green, blue : int );
    procedure SPresetvlu;

    procedure SPselpg ( page : int );
    procedure SPshwpg ( page : int );
    procedure SPsplit ( scr, px, py, ysize : int );
    procedure SPshow  (enable : int );

    procedure SPclip(x1, y1, x2, y2 : int);            {+}
    procedure SPnoclip;                                {+}

    function  SPselcard (cardnr : int) : int;

    procedure SPtext(_x,_y: int; txt: str255);         {+}
    function  SPtxtdir(textdir: int): int;
    function  SPtxtori(textori: int): int;

    procedure SPspatt(xsize,ysize, zoomx,zoomy, xpointer,ypointer : int; var patt: pattbuff);
    procedure SPdpatt(x,y,xsize,ysize, szx,szy, zoomx,zoomy, dir : int);
    procedure SPclr(color: int);
    procedure SPdot(x,y: int) ;                        {+}
    procedure SPvect(x1,y1,x2,y2: int);                {+}
    procedure SPpoly(nmb: int; pline_p: polybuff_p);   {+}
    procedure SPfpoly(panel_p: polybuff_p);            {+}
    procedure SPrect (x1,y1,x2,y2: int);               {+}

    procedure SPfill(x1,y1,x2,y2    : int);            {+}
    procedure SPpfill(x1,y1,x2,y2   : int);
    procedure SPcircle(xc,yc,radius : int);
    procedure SPfcircle(xc,yc,radius: int);

    procedure SParc ( dir,xs,ys,xe,ye,xc, yc : int);
    procedure SPcopy(src,x1,y1,x2,y2, dest,dx,dy: int);
    procedure SPgetdot ( dir, p1, p2, ccord : int ; var buffer : pixbuff);
    procedure SPsetdot ( dir, p1, p2, ccord : int ; var buffer : pixbuff);

    procedure SPircurs ( curx, cury : int; var andmask, xormask : andxor;
                         xsize, ysize, xzoom, yzoom, xbuffer, ybuffer : int;
                         fgcolor, bgcolor : int );
    procedure SPdrcurs ( posx, posy : int );
    procedure SPcrcurs;

    procedure SPvspos    ( x, y : int );
    procedure SPvgpos    ( var x, y : int );
    procedure SPvswindow ( x1, y1, x2, y2 : int );
    procedure SPvgwindow ( var x1, y1, x2, y2 : int );
    procedure SPvzoom    ( zfactor : int );
    procedure SPvgsize   ( var x, y : int );
    procedure SPvdisp    ( mode : int );
    procedure SPvgdisp   ( var mode : int );
    procedure SPvgzoom   ( var zfactor : int );

    function  SPboxsave(x0,y0,x1,y1: int; var height: int; mode: int): int;
    function  SPboxinq (id: int; var x0,y0,x1,y1: int; var planes: int): int;
    function  SPboxrest(id, x,y: int): int;
    function  SPboxfree(id: int): int;

    procedure SPvectto (X1,Y1: int);
    procedure SPmoveto (X1,Y1: int);
    procedure SPvectrel(x1,y1: int);
    procedure SPmoverel(x1,y1: int);



implementation

uses  BIOS, math;

var   reg          : registers;
      interrupt_nr : byte;


{ Call Resident Program }

procedure call_graphic_driver;
    begin
      reg.ax:=seg (packet);
      reg.bx:=ofs (packet);
      intr (interrupt_nr, reg)
    end;



{$I SPEA_0.inc}  { inicializacne funkcie }
{$I SPEA_1.inc}  { fonty                 }
{$I SPEA_2.inc}  { funkcie               }
{$I SPEA_3.inc}  { VGA funkcie           }



procedure SPEAinit;
    var   i: byte;
    begin
      if SPinit=-1 then
         begin
           ProgramError:= true;
           WriteLn(#7,'SPdriver not instaled',#7);
           Halt(1)
         end;
    { for i:= 0 to 19 do SPsetvlu(i ,i*13,i*13,i*13); }
      { SP_vlu; }
      SPEAinitialized:= true;
      {$IFDEF DEBUG}
         SPvdisp(7);
      {$ELSE}
         SPvdisp(2);
      {$ENDIF}
      SPopmode(0);
      SPclr(0);
      SPclip(0,0,MaxX,MaxY); { SPclip(0,0,2047,1279); }
      SPvzoom(0);
      SPvspos(500,300);
      Fonts_init;
      SPselfont(STDxFNT)
    end; { SPEAinit }


procedure SPEAend;
    begin
      if not SPEAinitialized then Exit;
      SPvdisp(2);
      SPnoclip;
      Fonts_done;
      SPclr(0);
      SPend
    end;

end.