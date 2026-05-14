(*-------------------------------------------------------------------*)
(* Mys 1.0                                                           *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$X+,I-,S-,P-,O-}
{$C FIXED PRELOAD PERMANENT}

{
  - kurzor si kreslim sam, lebo ta svina nad standartom VGA nefunguje
  - kliknutie vrati suradnicu laveho horneho rohu stvorca
    ohranicujuceho ikonu mysi => musi sa prepocitat stred na obrazok
    dany Moff.

    Pozn: Pri Views zatial neprepocitavam RUKU a SIPKA,
          posun je maly.
}

unit Mouse;

interface


     uses    TypeDef;


     {$I mouse_c.h}
     {$I mouse_v.h}


     procedure InitMouse;

     procedure m_off (var bp: bool; var xl,yl: int);
     procedure m_on  (bp: bool; xl,yl: int);
     procedure m_cl;
     procedure m_st;

     procedure m_hide;
     procedure m_show;
     procedure m_put;

     function  m_hit: bool;
     function  m_pop (var m: TMouseChar): bool;
     procedure m_clear;


     procedure m_cursor(Cursor: TMCursor);

     procedure set_xy (x,y: int);
     function  get_xy (var x,y: int): int;
     {procedure get_dxy(var dx,dy: int);}
     function  get_bt (var bt: byte): int;
     function  get_m  (var x,y: int; var bt: byte): bool;

     procedure m_clip(x0,y0,x1,y1: int);
     procedure m_sensitivity(dx,dy: int);
     procedure m_speed(treshold: word);

     procedure m_set_shape(Cursor: TMCursor);
     procedure m_restore_shape;
     procedure m_reinit_shape;



implementation

uses  DOS, BIOS,
      math, _Check,
      graph_h,
      {$IFDEF BGI}   Graph  {$ELSE}  Graphs  {$ENDIF}
      {$IFDEF SPEA}, SPEA   {$ENDIF}
      ;


var   m_enabled    : bool;   { povolenie/zakazanie mysi    }
      mIntFlag     : bool;   { nastavi sa pri stlaceni tlacidla na mysi }

      m_int_enabled : bool;  { povolenie prerusenia mysi   }
      m_show__flag  : bool;  { zobraz mys, bola zhasnuta   }
      m_shape__flag : bool;  { nastav tvar mysi            }
      m_pos_change  : bool;  { presun mys do novej pozicie }

    { musim si strazit suradnice, lebo vo VGA a SVGA       }
      m_restr_reg : TRegion; { zakazana oblast             }
      m_x,m_y     : int;     { globalne suradnice mysi     }

     {is_ver_6    : bool;      vo verzii 6.0 mys skakala
      cfg_ver_MOUSE      = 'MOUSE VER';}


{$I m_curs.inc}
{$I m_draw.inc}
{$I m_act.inc}
{$I m_par.inc}
{$I m_int.inc}


procedure InitMouse;
    var   CurSize: long;
    begin
      init__m_cursors;
      asm
           MOV  m_int_enabled,0
           MOV  mIntFlag,0
	   MOV	AX,3533H         { detekcia pritomnosti mysi }
	   INT	21H
	   MOV	AX,ES
	   OR	AX,BX
	   JE	@@1
	   XOR	AX,AX
	   INT	33H
	   OR	AX,AX
	   JE	@@1
	   PUSH	BX
	   MOV	AX,4
	   XOR	CX,CX
	   XOR	DX,DX
	   INT	33H
	   POP	AX
      @@1: MOV	is_mouse,AL
           XOR	AX,AX
	   CMP	AL,is_mouse
	   JE	@@2              { ak is_mouse=0 then Exit }
	   MOV	AX,3
	   INT	33H
	   XCHG	AX,CX            { MOV	CL,3  SHR AX,CL SHR DX,CL}
	   MOV	mouse_status.stat.bt,BL
	   MOV	mouse_status.stat.x,AX
	   MOV	mouse_status.stat.y,DX
	   MOV	mouse_status.curs,MYS
	   MOV	AX,12
	   MOV	CX,mIntMask
	   MOV	DX,OFFSET CS:MouseInt
	   PUSH	CS
	   POP	ES
	   INT	33H
           MOV  AX,1             { poloz kurzor }
           INT  33H
 	   MOV	AX,2
	   INT	33H
           MOV	m_visible,0      { m_visible:= false }
           MOV  m_enabled,0
           MOV  m_show__flag,0
           MOV  m_shape__flag,0
           MOV  mcit,0           { citaci index                 }
           MOV  mzap,0           { zapisovaci index             }
           MOV  m_int_enabled,1
      @@2:
      end;
      m_clip(0,0,MaxX,MaxY);
      set_xy(MaxX shr 1,MaxY shr 1);
    { instalacia driveru mysi do hlavneho programu }
      SaveMain0:= ACheckProcesses0;
      ACheckProcesses0:= check_mouse
    end;


procedure DoneMouse; { far; }
    var   i: TMCursor;
    begin
     {$IFDEF DEBUG_EXIT} writeln('MOUSE'); {$ENDIF}
    { odinstalovanie interrupt procedury     }
      asm
	     CMP  is_mouse,0
	     JE	  @@1
             MOV  AX,2
             INT  33H
	     MOV  AX,12
	     XOR  CX,CX
	     MOV  DX,CX
	     MOV  ES,CX
	     INT  33H
        @@1:
      end;
    { uvolnenenie kurzorov pre mys z pamate }
      { a) FreeMem(p_buffer,ImageSize(0,0,15,15)); }
      { b) for i:= MYS to High(TMCursor) do FreeMem(Mcur[i],Msize[i]); }
      done__m_cursors;
    { dalsia Exit procedura                 }
      ExitProc:= SaveExit
    end;

begin
 {  is_ver_6:= read_cfg_real(SYSTEMcfg,cfg_ver_MOUSE,0.0)=6.0;}
  SaveExit:= ExitProc;
  ExitProc:= @DoneMouse
end.
