(*-------------------------------------------------------------------*)
(* Graph ii  2.0                                                     *)
(* 1993,94                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit BGIgraph;


interface

    uses    TypeDef,
            DOS,
            graph_h,
            mouse;


    {$I bgigr_t.h}
    {$I bgigr_c.h}


    const bar_mnuXY : TRegion = (x0:0;y0:0;x1:0;y1:0);    { rozmery riadkoveho menu }
          btmdXY    : TRegion = (x0:0;y0:0;x1:0;y1:0);    { oblast, kde sa moze pohybovat oknami }
          btcdXY    : TRegion = (x0:0;y0:0;x1:0;y1:0);    { oblast, kde sa centruju okna         }


    procedure get_region(R: TRegion; var x0,y0,x1,y1: int);
    procedure set_region(x0,y0,x1,y1: int; var R: TRegion);
    function  move_reg  (var x0,y0, x1,y1: int; dx,dy: int): byte;

    function  kbset_xy(kbXXXX: char): bool;
    function  m_to_kb(m: TMouseChar): char;

  { ine procedury }
    procedure show_cursor(x,y, dx,dy, dy_c0,dy_c1, indx,indy : int; ch: char; ins: bool; c,b: byte);
    procedure hide_cursor(x,y, dx,dy, dy_c0,dy_c1, indx,indy : int; ch: char; c,b: byte);

    function  SetX(X: int): int;
    function  SetY(Y: int): int;

    procedure Write_    (x,y: int; S: string; cl: byte);
    procedure ClearStr  (x,y: int; len: int; bg: byte);
    procedure WriteStr  (x,y: int; S: string; cl,bg: byte);
    procedure WriteStrF (x,y: int; s: string; size: byte; cl,bg: byte);
    procedure WriteDStr (x,y: int; S: string; cl,sh,bg: byte);
    procedure WriteCentr(x0,x1,y0,y1: int; S: string; cl: byte);
    procedure WriteInfo (x0,y0,x1,y1: int; Info: string);
    procedure WriteClippedText(x1,y1: int; s: string);

    function  cut_text(s: string): string;

    procedure _linev(x,y0,y1: int; bk: byte);
    procedure _lineh(x0,x1,y: int; bk: byte);

    procedure _linevo(x,y0,y1: int; bk: byte);
    procedure _lineho(x0,x1,y: int; bk: byte);

    procedure _angle(x0,y0,x1,y1,x2,y2: int; cl: byte);
    procedure _drawpoly(x,y: int; cl: byte; p: Pints; nmb: byte);
    procedure _fillpoly(x,y: int; bg: byte; p: Pints; nmb: byte);
    procedure _set_typciary(_typ : byte ; _hr: byte);

    procedure FillWin(x0,y0,x1,y1: int; bg: byte);  { zmaze okno farbou bez uchovania parametrov }
    procedure ClrWin (x0,y0,x1,y1: int; bg: byte);  { zmaze okno farbou s uchovanim parametrov   }

  { ikony }
    procedure icYes_(x,y: int; cl: byte);
    procedure icYes (x,y: int);
    procedure icNo_ (x,y: int; cl: byte);
    procedure icNo  (x,y: int);
    procedure icMove(x,y: int);
    procedure icList(x,y: int);

    procedure icArrowUp  (x,y: int; on: TbtStat);
    procedure icArrowDown(x,y: int; on: TbtStat);

  { vykreslenie okna alebo buttonu }
    procedure window(Xl,Yl,Xh,Yh: int; shdx,shdy, RectOff, Bg,Ph: byte);
    procedure on_off(x0,y0,x1,y1: int; b1,b2,  thick: byte; on: TbtStat);
    procedure button(x0,y0,x1,y1: int; bk, thick: byte; on: TbtStat);
    procedure ButtonWindow(x0,y0,x1,y1: int; bk, thick: byte);

  { }
    procedure InfoWin(nadpis,veta: string; dyv1,dyv2: int; cl,bk: byte);
    procedure InfoCakaj(nadpis,veta: string);
    procedure InfoCakaj_zatvor;

  { otvorenie a uzatvorenie okna }
    function  SaveWin(_x0,_y0,_x1,_y1: int; var _WinReg: PWinReg): bool;
    function  RestWin(var _WinReg: PWinReg; restore,dealloc: bool): bool;
    function  MoveWin(_x0,_y0,_x1,_y1: int; _x01,_y01: int): bool;

    function  OpenWin(x0,y0,x1,y1, dx,dy: int; fill: bool): int; { >-1 - okno je otvorene }
    procedure CloseWin;

    procedure WinXY(const win: PWin; var _x0,_y0,_x1,_y1: int);

  { }
    function  OpenWins: byte; far;
    function  OverlapWin(_x0,_y0,_x1,_y1: int; SelfWinDesc: int): bool; far;

    function  vypis_do_okna(x0,y0,x1,y1: int; var TempWinReg: PWinReg; SelfWinDesc: int; zostane: int): bool; far;
    procedure obnov_okna(var TempWinReg: PWinReg; novy_obsah: bool); far;



implementation

uses  BIOS, IO,
      keyb, math, str0, mess,
      {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF}
      {$IFDEF SPEA}, SPEA {$ENDIF},
      SVGA
      ;


{$I BGIgr0.inc}
{$I BGIgr1.inc} { text }
{$I BGIgr2.inc} { draw,fill }
{$I BGIgr3.inc} { ikony }
{$I BGIgr4.inc} { clrwin,... , button, info }

{$I BGIgr5.inc} { okna }
{$I BGIgr6.inc} { docasne ukrytie okien a ich obnova }


{$IFDEF BGI}

  var SaveExit: pointer;

  procedure done_WinManager;
      begin
       {$IFDEF DEBUG_EXIT} writeln('BGIGR'); {$ENDIF}
        if ind_WinHDD<>nil then FreeMem(ind_WinHDD,sizeof(byte)*(top_WinHDD+1));
        ExitProc:= SaveExit
      end;

  procedure init_WinManager;
      var   s : string;
            l : long;
            d : char;
      begin
       { nasli posledny disk - mal by byt RAM }
        driveSaveWin:= ord('Z')-ord('A');
        while (driveSaveWin>=0) and (DiskFree(driveSaveWin)<2*1024*1024) do dec(driveSaveWin);
        read_cfg_str(SYSTEMcfg,cfg_pathSaveWin, pathSaveWin);
        if pathSaveWin<>'' then
           begin
             FSplit(pathSaveWin, sDir,sName,sExt);
             l:= drive_ind(sDir);
             if (l>=3) then driveSaveWin:= l
           end
        else begin
               if driveSaveWin=0 then pathSaveWin:= pathTMP
               else pathSaveWin:= chr(ord('A')+driveSaveWin-1)+':\';
             end;

        SaveWinMem:= read_cfg_bool(SYSTEMcfg,cfg_SaveWinMem,SaveWinMem);
        SaveExit:= ExitProc;
        ExitProc:= @done_WinManager
      end;


  begin
    init_WinManager
{$ENDIF}
end.