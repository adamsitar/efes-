{ -------------------------------------------------- }
{  zobrazenie mysi                                   }
{ -------------------------------------------------- }

procedure m_st;
    begin
      m_enabled:= true;
      m_show
    end;

procedure m_cl;
    begin
      m_hide;
      m_enabled:= false
    end;


procedure m_off(var bp: bool; var xl,yl: int);
    begin
      bp:= m_enabled and m_visible;
      get_xy(xl,yl);
      if bp then m_cl
    end;

procedure m_on(bp: bool; xl,yl: int);
    begin
      if not bp then Exit;
      m_st;
      set_xy(xl,yl)
    end;


{ ---------------------- }
{  docasny tvar mysi     }
{ ---------------------- }
type  Ptemp_shape = ^Ttemp_shape;
      Ttemp_shape = record
         prev  : Ptemp_shape;
         shape : pointer;
      end;

const temp_m_shape: Ptemp_shape = nil;

procedure m_set_shape(Cursor: TMCursor);
    var   p: Ptemp_shape;
    begin
      new(p);
      p^.prev := temp_m_shape;
      p^.shape:= @m_shape;
      temp_m_shape:= p;
      m_shape:= no_action;
      m_cursor(Cursor)
    end;

procedure m_restore_shape;
    var   p: Ptemp_shape;
    begin
      if temp_m_shape=nil then exit;
      p:= temp_m_shape;
      m_shape:= TProc(p^.shape);
      temp_m_shape:= p^.prev;
      dispose(p);
      m_shape
    end;

procedure m_reinit_shape;
    begin
      while temp_m_shape<>nil do m_restore_shape
    end;