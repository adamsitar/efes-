{ -------------------------------------------------- }
{  run time                                          }
{ -------------------------------------------------- }

var   int_x, int_y: int;
      int_bt: byte;

procedure read_m_xy;
    begin
      set_m_xy(int_x,int_y);
      mouse_status.stat.x := m_x;
      mouse_status.stat.y := m_y;
      mouse_status.stat.bt:= int_bt;
      mouse_status.stat.curs:= mouse_status.curs
    end;


procedure MouseInt; far; assembler;
    var   Ticks : word absolute $40:$006C; { priamo pouzitelne len v Real mode }
    asm
         MOV   SI,SEG @DATA
	 MOV   DS,SI
	 MOV   SI,CX
         CMP   m_enabled,1        { je povolena ? }
         JE    @@4
         JMP   @@0
    @@4: CMP   m_int_enabled,0    { dokoncene posledne prerusenie ? }
         JE    @@0
         MOV   m_int_enabled,0    { semafor ON }  {MOV   CL,3 SHR   SI,CL SHR   DX,CL}
         MOV   int_bt,BL          { suradnice }
 	 MOV   int_x,SI
 	 MOV   int_y,DX
         CALL  read_m_xy
    	 MOV   ES,Seg0040                 { ticky }
	 MOV   SI,ES:Ticks
         MOV   mouse_status.stat.tick,SI
 	 CMP   mouse_status.stat.bt,0     { bolo stlacene tlacidlo ?   }
	 JE    @@3
         CALL  m_push             { ulozenie parametrov mysi           }
         MOV   mIntFlag,1         { priznak pre m_hit                  }
       { zobrazenie mysi na danej pozicii                              }
    @@3: CMP   m_visible,0
         JE    @@2
         MOV   m_pos_change,1     { vykreslenie mysi v novej pozicii   }
         {CALL  m_put}
         JMP   @@1
    @@2: MOV   m_show__flag,1     { CALL  m_show - ak je neviditelna   }
         {CALL  m_show}
    @@1: MOV   m_int_enabled,1    { povolenie prerusenia               }
    @@0:
    end;

{
 procedura pre kontrolu pouzivania a zhasanie mysi;
 v dalsej podobnej musim uz retazit - volat SaveTimerProc
}
var {SaveDemon: Tproc;}
     SaveMain0 : TProc;
     SaveExit  : pointer;

procedure rozsviet_disp;
    begin
      {$IFDEF DISPLAY_ZHASNI}
        if ZHASINANIE and (@p_rozsviet<>nil) and (@p_zhasni<>nil) then
           if inRectangle (mouse_status.stat.x,mouse_status.stat.y,MaxX-20,0,MaxX,20) then p_zhasni
           else p_rozsviet
      {$ENDIF}
    end;


procedure check_mouse; far;
    const _int_x  : int  = 0;
          _int_y  : int  = 0;
          _int_bt : byte = 0;
    var   x,y     : int;
    begin
      if @SaveMain0<>nil then SaveMain0;
      if (not m_enabled) then Exit;

      if m_pos_change then
         begin
           m_pos_change:= false;
           if m_kresli then m_put;
           rozsviet_disp
         end;

      if m_show__flag then
         begin
           m_show__flag:= false;
           {if m_kresli then}
              begin
                m_show;
                m_shape
              end;
           rozsviet_disp
         end;

      if     m_hide_enable
         and m_visible
        {and m_kresli}
         and TimeOut(mouse_status.stat.tick, GetTicks, mHideTicks) then
             begin
               m_hide
             end
    end;
