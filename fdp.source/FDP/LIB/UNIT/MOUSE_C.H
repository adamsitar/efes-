     const { Mouse button state masks }
             mbLeftButton   = $01;
             mbRightButton  = $02;
             mbMiddleButton = $04;
           { velkost buffera    }
             maxMouseBuff   = 16;

     const   mIntMask: word = $002B;   { maska prerusenia - stlacenie + poloha }
           {
             0  -  cursor location changed
             1  -  left button pressed
             2  -  left button released
             3  -  right button pressed
             4  -  right button released
             5  -  middle button pressed
             6  -  middle button released

             00101011 -> 2B 00101111 -> 2F -> pre Drag
           }

     type    Tbyte16x16 = array[0..15,0..15] of byte;
             TMCursor   = (bez,MYS,SIPKA,RUKA,HODINY,KRIZ,CIEL,KRUH,NIC);
             TMouseChar = record
               x,y : int;      { suradnice kurzora mysi }
               bt  : byte;     { stav tlacidiel mysi    }
               tick: word;     { stav citaca v okamihu prerusenia }
               curs: TMCursor  { tvar curzora -//-             }
             end;


     const   Moff: array[MYS..High(TMCursor)] of TPoint =
                 ((x: 0; y: 0),(x: -1; y: 0),(x: 1; y: -2),(x: 0; y: 0),(x: -7; y: -7),(x: -7; y: -7),(x: -7; y: -7),
                  {MYS,         SIPKA,       RUKA,          HODINY,      KRIZ,          CIEL,          KRUH,}
                  (x: 0; y: 0));
                  {NIC         );}


