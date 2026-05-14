     type   PStatusButton = ^TStatusButton;
            TStatusButton = object(TFButton)
              lastTime       : real;
              click_and_hide : bool;

              constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _click, _ck,_ct: byte;
                               var hi_: int;
                               _hide: bool
                              );
              procedure   Idle(var _Event: TEvent); virtual;
              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   ReInit;
              procedure   Show; virtual;
            end;

