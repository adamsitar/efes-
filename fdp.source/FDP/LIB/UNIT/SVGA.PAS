(*-------------------------------------------------------------------*)
(* SVGA  1.0                                                         *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{ Fonty, co pouzivam, by bolo dobre inicializovat v BGIgraph          }
{$I comp.h}

unit SVGA;

interface

   uses TypeDef,
        {$IFDEF WINDOWS}
          --> This program doesn't work in Windows
        {$IFDEF DPMI}
         {$DEFINE PMODE}
          WinApi,
        {$ELSE}
          dos,
        {$ENDIF} {$ENDIF}
        {$IFDEF BGI} graph, {$ENDIF} graph_h;


   {$I SVGA.h}                           { typy, premenne }
   {$I SVGA_zh.h}
   {$I SVGA_fnt.h}

   { procedury inicializacie a uzatvorenia grafickeho prostredia }
    procedure InitBGI;

    procedure instal_LOGO(_VER,_CR: string; _statup: bool);
    procedure set_GrMode(__GraphMode: TGraphMode);

    function  GetMaxXM: int;
    procedure set_RGBcolor (var RGBc: Tcolor; r,g,b: byte);
    procedure set_RGBcolors(P: Tpaleta; od,pocet: word);
    procedure set_RGBpallete;

   { procedury pre nastavenie jasu a zhasinanie }
    procedure check_display;
    function  Rozsviet: bool;
    procedure Zhasni;
    procedure Zhasinaj;

    procedure JasBGI(jas: byte);


implementation

uses  Crt, CrtII,
      DOS, BIOS, IO, _Check,
      {$IFNDEF BGI} Graphs, {$ENDIF}
      {$IFDEF SPEA} SPEA, {$ENDIF}
      str0, utime, math, mouse, mess;

const PathToDriver = '';

{ -------------------------------------------------------- }
{ Inicializacia grafiky                                    }
{ -------------------------------------------------------- }
(*
{$IFDEF INTERNAL}
  procedure Bgi256Proc; external;
  {$L BGI256.OBJ}
{$ENDIF}

{$IFNDEF DEBUG}

  procedure SVGAdriver; far; external; {$L BGI.OBJ}

  function Link_SVGAdriver: bool;
     begin
       if RegisterBGIDriver(@SVGAdriver) < 0 then RunError('BGI.OBJ nenajdeny.')
       else Link_SVGAdriver:= true
     end;

{$ENDIF}
*)

{$I pal_SVGA.inc}
{$I pal_SPEA.inc}
{$I SVGA_pal.inc}   { nastavenie palety }
{$I SVGA_.inc}

{$I SVGA_zhs.inc}   { zhasinanie }
{$I SVGA_lg.inc}    { logo       }
{$I SVGA_fnt.inc}

{$I SVGA_ini.inc}

{$IFDEF DEBUG} {$IFDEF SPEA}
  begin ClrScr;
{$ENDIF} {$ENDIF}
end.