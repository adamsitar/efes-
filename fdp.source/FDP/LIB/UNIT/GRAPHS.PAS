(*-------------------------------------------------------------------*)
(* Graph pre ine adaptery ako VGA 512kB a SVGA 1MB                   *)
(*  - spomenute adaptery vyuzivaju sluzby originalneho Graphu        *)
(*  - ostatne (SPEA, MiroCrystal) volaju podla kompilacnej direktivy *)
(* 1994                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Graphs;


interface


    uses  TypeDef, graph_h {$IFDEF SPEA}, SPEA {$ENDIF};


    {$I graph.h}

    {
    procedure Arc (X,Y: int; StAngle, EndAngle, Radius: word);
    }
    procedure Bar(x1,y1, x2,y2: int);
    {
    procedure Bar3D(x1, y1, x2, y2: int; Depth: word; Top: bool);
    }

    procedure Circle(X,Y: int; Radius: word);
    procedure ClearDevice;
    procedure ClearViewPort;
    procedure CloseGraph;
    procedure CopyView(src,x0,y0,x1,y1, dest,nx0,ny0: int);

    {
    procedure DetectGraph(var GraphDriver, GraphMode: int);
    }
    procedure DrawPoly(NumPoints: word; var PolyPoints);
    {
    procedure Ellipse(X, Y: int; StAngle, EndAngle: word; XRadius, YRadius: word);
    procedure FillEllipse(X, Y: int; XRadius, YRadius: word);
    }
    procedure FillPoly(NumPoints: Word; var PolyPoints);
    {
    procedure FloodFill(X, Y: int; Border: word);

    procedure GetArcCoords(var ArcCoords: _ArcCoordsType_);
    procedure GetAspectRatio(var Xasp, Yasp: word);
    }
    function  GetBkColor: word;
    function  GetColor: word;
    {
    function  GetDefaultPalette(var Palette: PaletteType);
    function  GetDriverName: string;
    procedure GetFillPattern(var FillPattern: FillPatternType);
    }
    procedure GetFillSettings(var FillInfo: FillSettingsType);
    function  GetGraphMode: int;
    {
    procedure GetImage(x1, y1, x2, y2: int; var BitMap);
    }{
    procedure GetLineSettings(var LineInfo: LineSettingsType);
    }
    function  GetMaxColor: word;
    function  GetMaxMode: int;
    function  GetMaxX: int;
    function  GetMaxY: int;
    {
    function  GetModeName(ModeNumber: int): string;
    procedure GetModeRange(GraphDriver:int; var LoMode, HiMode:int);
    procedure GetPalette(var Palette: PaletteType);
    function  GetPaletteSize: int;
    function  GetPixel(X,Y: int): word;
    procedure GetTextSettings(var TextInfo: TextSettingsType);
    procedure GetViewSettings(var ViewPort: ViewPortType);
    function  GetX: int;
    function  GetY: int;
    procedure GraphDefaults;
    }
    function  GraphErrorMsg(ErrorCode: int): string;
    function  GraphResult: int;
    {
    function  ImageSize(x1, y1, x2, y2: int): word;
    }
    procedure InitGraph(var GraphDriver:int; var GraphMode: int; PathToDriver: string);
    function  InstallUserDriver(Name: string; AutoDetectPtr: pointer): int;
    {
    function  InstallUserFont(FontFileName: string ): int;
    }
    procedure Line(x1, y1, x2, y2: int);
    {
    procedure LineRel(Dx, Dy: int);
    procedure LineTo(X, Y: int);
    procedure MoveRel(Dx, Dy: int);
    procedure MoveTo(X, Y: int);
    procedure OutText(TextString: string);
    }
    procedure OutTextXY(X,Y: int; TextString: string);
    {
    procedure PieSlice(X, Y: int; StAngle, EndAngle, Radius: word);
    }{
    procedure PutImage(X, Y: int; var BitMap; BitBlt: word);
    }
    procedure PutPixel(X, Y: int; Pixel: word);

    procedure Rectangle(x1, y1, x2, y2: int);
    {
    function  RegisterBGIdriver(driver: pointer): int;
    function  RegisterBGIfont(Font: pointer): int;
    procedure RestoreCrtMode;

    procedure Sector(x, y: int; StAngle,EndAngle, XRadius, YRadius: word);
    procedure SetActivePage(Page: word);
    procedure SetAllPalette(var Palette);
    function  SetAspectRatio(Xasp, Yasp: word): word;
    }
    procedure SetBkColor(Color : word);
    procedure SetColor  (Color : Word);
    {
    procedure SetFillPattern(Pattern: FillPatternType; Color: word);
    }
    procedure SetFillStyle(Pattern: word; Color: word);
    {
    procedure SetGraphBufSize(BufSize: word);
    }
    procedure SetGraphMode(Mode: int);
    procedure SetLineStyle(LineStyle: word; Pattern: word; Thickness: word);
    procedure SetTextJustify(Horiz, Vert: word);
    procedure SetTextStyle(Font, Direction: word; CharSize: word);
    {
    procedure SetUserCharSize(MultX, DivX, MultY, DivY: word);
    }
    procedure SetViewPort(x1, y1, x2, y2: int; Clip: bool);
    {
    procedure SetVisualPage(Page: word);
    }
    procedure SetWriteMode(WriteMode: int);

    function  TextHeight(TextString: string): word;
    function  TextWidth (TextString: string): word;



implementation

uses str0;

{
‹‹‹‹‹‹‹
€     €
€  B  €
€‹‹‹‹‹€
}
procedure Bar(x1,y1, x2,y2: int);
    begin
      {$IFDEF SPEA} SPfill(x1,MaxY-y1,x2,MaxY-y2) {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  C  €
€‹‹‹‹‹€
}
procedure Circle(X,Y: int; Radius: word);
   begin
     {$IFDEF SPEA} SPcircle(X,MaxY-Y,Radius) {$ENDIF}
   end;

procedure ClearDevice;
   begin
     {$IFDEF SPEA} SPclr(black) {$ENDIF}
   end;

procedure ClearViewPort;
   begin
     {$IFDEF SPEA} SPnoclip {$ENDIF}
   end;

procedure CloseGraph;
   begin
     {$IFDEF SPEA} SPEAend {$ENDIF}
   end;

procedure CopyView(src,x0,y0,x1,y1, dest,nx0,ny0: int);
    begin
     {$IFDEF SPEA} SPcopy(src,x0,MaxY-y1,x1,MaxY-y0, dest,nx0,MaxY-(ny0+y1-y0)); {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  D  €
€‹‹‹‹‹€
}
procedure DrawPoly(NumPoints: word; var PolyPoints);
    var   i,size : int;
          p      : Pints;
    begin
     {$IFDEF SPEA}
        size:= (NumPoints*2) * sizeof(int);
        getmem(p, size);
        move(PolyPoints,p^,size);
        i:= 0; while i<2*NumPoints-1 do begin p^[i+1]:= MaxY-p^[i+1]; inc(i,2) end;
        SPpoly(NumPoints, polybuff_p(p));
        freemem(p, size)
     {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  F  €
€‹‹‹‹‹€
}
procedure FillPoly(NumPoints: Word; var PolyPoints);
    var   i,size : int;
          p      : Pints;
    begin
     {$IFDEF SPEA}
        size:= (3+NumPoints*2) * sizeof(int);
        getmem(p, size);
        move(PolyPoints,p^[3],size-3*sizeof(int));
        p^[0]:= 1; p^[1]:= 0; p^[2]:= NumPoints;
        i:= 0; while i<2*NumPoints-1 do begin p^[i+4]:= MaxY-p^[i+4]; inc(i,2) end;
        SPfpoly(polybuff_p(p));
        freemem(p, size)
     {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  I  €
€‹‹‹‹‹€
}
function  ImageSize(x1,y1, x2,y2: int): word;
   begin
     ImageSize:= 1
   end;

function  InstallUserDriver(Name: string; AutoDetectPtr: pointer): int;
   begin
   end;

procedure InitGraph(var GraphDriver: int; var GraphMode: int; PathToDriver: string);
    begin
      {$IFDEF SPEA} SPEAinit; {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  G  €
€‹‹‹‹‹€
}
function  GetBkColor: word;
    begin
      {$IFDEF SPEA} GetBkColor:= SPbcol {$ENDIF}
    end;

function  GetColor: word;
    begin
      {$IFDEF SPEA} GetColor:= SPcol {$ENDIF}
    end;


procedure GetFillSettings(var FillInfo: FillSettingsType);
    begin
      {$IFDEF SPEA} FillInfo.Pattern:= 0; FillInfo.Color:= SPcol {$ENDIF}
    end;

function  GetGraphMode: int;
    begin
      {$IFDEF SPEA} GetGraphMode:= 0 {$ENDIF}
    end;


procedure GetImage(x1, y1, x2, y2: int; var BitMap);
    begin
      {$IFDEF SPEA} {$ENDIF}
    end;

function  GetMaxColor: word;
    begin
      {$IFDEF SPEA} GetMaxColor:= 256 {$ENDIF}
    end;

function  GetMaxMode: int;
    begin
      {$IFDEF SPEA} GetMaxMode:= 1 {$ENDIF}
    end;


function  GetMaxX: int;
   begin
     {$IFDEF SPEA} GetMaxX:= 1279 {$ENDIF}
   end;

function  GetMaxY: int;
   begin
     {$IFDEF SPEA} GetMaxY:= 1023 {$ENDIF}
   end;


function GraphErrorMsg(ErrorCode: int): string;
   begin
     case ErrorCode of
       grOk             : GraphErrorMsg:= 'No error';
       grNoInitGraph    : GraphErrorMsg:= 'BGI graphics not installed';
       grNotDetected    : GraphErrorMsg:= 'Graphics hardware not detected';
       grFileNotFound   : GraphErrorMsg:= 'Device driver file not found';
       grInvalidDriver  : GraphErrorMsg:= 'Invalid device driver file';
       grNoLoadMem      : GraphErrorMsg:= 'Not enough memory to load driver';
       grNoScanMem      : GraphErrorMsg:= 'Out of memory in scan fill';
       grNoFloodMem     : GraphErrorMsg:= 'Out of memory in flood fill';
       grFontNotFound   : GraphErrorMsg:= 'Font file not found';
       grNoFontMem      : GraphErrorMsg:= 'Not enough memory to load font';
       grInvalidMode    : GraphErrorMsg:= 'Invalid graphics mode for selected driver';
       grError          : GraphErrorMsg:= 'Graphics error (generic error)';
       grIOerror        : GraphErrorMsg:= 'Graphics I/O error';
       grInvalidFont    : GraphErrorMsg:= 'Invalid font file';
       grInvalidFontNum : GraphErrorMsg:= 'Invalid font number'
       else GraphErrorMsg:= 'Graphics error'
     end
   end;

function GraphResult: int;
   begin
     GraphResult:= grResCode
   end;


{
‹‹‹‹‹‹‹
€     €
€  L  €
€‹‹‹‹‹€
}
procedure Line(x1,y1, x2,y2: int);
    begin
     {$IFDEF SPEA} SPvect(x1,MaxY-y1,x2,MaxY-y2) {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  O  €
€‹‹‹‹‹€
}
procedure OutTextXY(X,Y: int; TextString: string);
    begin
     {$IFDEF SPEA} SPtext(X,MaxY-Y, cs_ascii_str(TextString)) {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  P  €
€‹‹‹‹‹€
}
procedure PutImage(X, Y: int; var BitMap; BitBlt: word);
    begin
     {$IFDEF SPEA} {$ENDIF}
    end;

procedure PutPixel(X, Y: int; Pixel: word);
    begin
     {$IFDEF SPEA} SPcolor(Pixel); SPdot(x,MaxY-y) {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  R  €
€‹‹‹‹‹€
}
procedure Rectangle(x1, y1, x2, y2: int);
    begin
      {$IFDEF SPEA} SPrect(x1,MaxY-y1,x2,MaxY-y2) {$ENDIF}
    end;

{
‹‹‹‹‹‹‹
€     €
€  S  €
€‹‹‹‹‹€
}
procedure SetBkColor(Color: word);
    begin
      {$IFDEF SPEA} SPbcolor(Color) {$ENDIF}
    end;

procedure SetColor(Color: Word);
    begin
      {$IFDEF SPEA} SPcolor(Color) {$ENDIF}
    end;

procedure SetGraphMode(Mode: int);
    begin
      {$IFDEF SPEA} ClearDevice {$ENDIF}
    end;

procedure SetLineStyle(LineStyle: word; Pattern: word; Thickness: word);
    begin
      {$IFDEF SPEA} SPlstyle(LineStyle) {$ENDIF}
    end;

procedure SetFillStyle(Pattern: word; Color: word);
    begin
      {$IFDEF SPEA} SPcolor(Color) {$ENDIF}
    end;

procedure SetTextJustify(Horiz, Vert: word);
    begin
      {$IFDEF SPEA} {SPtxtdir a SPtxtori} {$ENDIF}
    end;

procedure SetTextStyle(Font, Direction: word; CharSize: word);
    begin
      {$IFDEF SPEA} SPselfont(Font) {$ENDIF}
    end;

procedure SetViewPort(x1, y1, x2, y2: int; Clip: bool);
    begin
      {$IFDEF SPEA} SPclip(x1,MaxY-y1, x2,MaxY-y2) {$ENDIF}
    end;

procedure SetWriteMode(WriteMode: int);
    begin
      {$IFDEF SPEA} SPopmode(WriteMode) {$ENDIF}
    end;


{
‹‹‹‹‹‹‹
€     €
€  T  €
€‹‹‹‹‹€
}
function  TextHeight(TextString: string): word;
   begin
     {$IFDEF SPEA} TextHeight:= Fonts[SPfont].dy {$ENDIF}
   end;

function  TextWidth (TextString: string): word;
   var    res: word;
   begin
     {$IFDEF SPEA}
        res:= Fonts[SPfont].dx;
        TextWidth:= res*length(TextString)
     {$ENDIF}
   end;


end.


