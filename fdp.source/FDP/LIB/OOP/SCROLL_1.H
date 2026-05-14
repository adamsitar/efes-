          { --------------------------------------------- }
          { TScrollBar                                    }
          { --------------------------------------------- }
    type  { Typ Tlacidlo             }
            PScrollBar = ^TScrollBar;
            TScrollBar = object(TView)
               lo,                { index prvej a poslednej polozky v okne }
               hi  : int;         { podla ich indexov v originalnom poli   }
               top : int;         { pocet poloziek                         }
               pos : int;         { pozicia vo vypise v <0,top>            }

               smer       : bool;    { smer vypisu: true = zhora dole         }
               posun      : byte;    { }
               za_posl_en : bool;    { vypis moze byt i za poslednou polozkou }

               sam     : bool;    { kreslit sb oddelene ?         }
               pos_en  : bool;    { povoleny scrollovaci riadok ? }
               stranka : bool;    { rolovanie vypisu len po strankach }

               zn_vys  : int;     { vyska buttonu scroll baru     }
               bg      : byte;


               public { predefinovane }
               constructor Init(_Owner: PGroup; x,y, dy: int;
                                _pos_en, _stranka, _sam: bool
                               );

               procedure   Draw; virtual;
               procedure   HandleEvent(var _Event: TEvent); virtual;

               procedure   ReInit(x,y,dx,dy: int); virtual;
               {procedure   resize(x,y,dy: int);}
               procedure   param (_lo,_hi,_top,_pos: int; _draw: bool);

               {protected}
               procedure   draw_pos; virtual;
               function    scroll_pos: real;
            end;
