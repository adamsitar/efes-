(*-------------------------------------------------------------------*)
(* Graph ii  1.0                                                     *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit BGItext;

interface


    uses TypeDef;

    procedure DoubleText(Xp,Yp: int; S: string; Ph,Sh,Bk: byte);
    procedure F6x4(Mx,My: int; Veta: string);


implementation

uses Graph, BGIgraph;

{
writes GString S with shadow and parameters Ph,Bk in pixel
coordinates without restoring previous screen atributes
}
procedure DoubleText(Xp,Yp: int; S: string; Ph,Sh,Bk: byte);
    begin
      ClrWin(Xp,Yp,Xp+TextWidth(S)+1,Yp+TextHeight('H')+5,Bk);
      SetColor(Sh);
      OutTextXY(Xp+2,Yp+4,S);
      SetColor(Ph);
      OutTextXY(Xp+1,Yp+3,S)
    end; { DoubleText }


{ ----------------- }
{ Font 6x4          }
{ ----------------- }
procedure F6x4(Mx,My: int; Veta: string);
    type  str = array[0..255] of char;
    var   mes : str absolute Veta;
          ch  : char;
          i   : byte;
    begin
       MoveTo(Mx,My);
       for i:=1 to Length(veta) do
         begin
           ch:= mes[i];
           case ch of
            '1': begin
                   MoveTo(GetX,GetY);LineRel(4,0);
                   MoveRel(-2,-1);LineRel(0,-5);
                   MoveRel(-1,2);LineRel(0,0);
                   MoveRel(5,4)
                 end;
            '2': begin
                   MoveTo(GetX,GetY-5);LineRel(1,-1);
                   MoveRel(1,0);LineRel(1,0);
                   MoveRel(1,1);LineRel(0,1);
                   MoveRel(-1,1);LineRel(-3,3);
                   MoveRel(1,0);LineRel(3,0);
                   MoveRel(2,0)
                 end;
            '3': begin
                   MoveTo(GetX,GetY-1);LineRel(1,1);
                   MoveRel(1,0);LineRel(1,0);
                   MoveRel(1,-1);LineRel(0,-1);
                   MoveRel(-1,-1);LineRel(-1,0);
                   MoveRel(2,-1);LineRel(0,-1);
                   MoveRel(-1,-1);LineRel(-1,0);
                   MoveRel(-1,0);LineRel(-1,1);
                   MoveRel(6,5)
                 end;
            '4': begin
                   MoveTo(GetX+4,GetY-6);LineRel(-4,4);
                   MoveRel(0,1);LineRel(4,0);
                   MoveRel(-1,-1);LineRel(0,0);
                   MoveRel(0,2);LineRel(0,0);
                   MoveRel(3,0)
                 end;
            '5': begin
                   MoveTo(GetX,GetY-1);LineRel(1,1);
                   MoveRel(1,0);LineRel(1,0);
                   MoveRel(1,-1);LineRel(0,-2);
                   MoveRel(-1,-1);LineRel(-3,0);
                   MoveRel(0,-1);LineRel(0,-1);
                   MoveRel(1,0);LineRel(3,0);
                   MoveRel(2,6);
                 end;
            '6': begin
                   MoveTo(GetX+4,GetY-5);LineRel(-1,-1);
                   MoveRel(-1,0);LineRel(-1,0);
                   MoveRel(-1,1);LineRel(0,4);
                   MoveRel(1,1);LineRel(2,0);
                   MoveRel(1,-1);LineRel(0,-1);
                   MoveRel(-1,-1);LineRel(-2,0);
                   MoveRel(5,3)
                 end;
            '7': begin
                   MoveTo(GetX,GetY);LineRel(4,-4);
                   MoveRel(0,-1);LineRel(0,-1);
                   MoveRel(-1,0);LineRel(-2,0);
                   MoveRel(-1,0);LineRel(0,1);
                   MoveRel(6,5)
                 end;
            '8': begin
                   MoveTo(GetX+1,GetY);LineRel(2,0);
                   MoveRel(1,-1);LineRel(0,-1);
                   MoveRel(-1,-1);LineRel(-2,0);
                   MoveRel(-1,1);LineRel(0,1);
                   MoveRel(0,-3);LineRel(0,-1);
                   MoveRel(1,-1);LineRel(2,0);
                   MoveRel(1,1);LineRel(0,1);
                   MoveRel(2,4)
                 end;
            '9': begin
                   MoveTo(GetX,GetY-1);LineRel(1,1);
                   MoveRel(1,0);LineRel(1,0);
                   MoveRel(1,-1);LineRel(0,-4);
                   MoveRel(-1,-1);LineRel(-2,0);
                   MoveRel(-1,1);LineRel(0,1);
                   MoveRel(1,1);LineRel(2,0);
                   MoveRel(3,3)
                 end;
            '0': begin
                   MoveTo(GetX+1,GetY);LineRel(2,0);
                   MoveRel(1,-1);LineRel(0,-4);
                   MoveRel(-1,-1);LineRel(-2,0);
                   MoveRel(-1,1);LineRel(0,4);
                   MoveRel(1,-1);LineRel(2,-2);
                   MoveRel(3,4)
                 end;
            ' ': MoveTo(GetX+6,GetY);
            #5 : begin
                   MoveTo(GetX-2,GetY+1);LineRel(0,-2);
                   MoveRel(1,-1);LineRel(2,0);
                   MoveRel(1,1);LineRel(0,2);
                   MoveRel(-1,1);LineRel(-2,0);
                   MoveRel(5,0)
                 end;
            #6 : begin
                   MoveTo(GetX-2,GetY+2);LineRel(0,-4);
                   MoveRel(1,0);LineRel(4,0);
                   MoveRel(0,1);LineRel(0,4);
                   MoveRel(-1,0);LineRel(-4,0);
                   MoveRel(5,0)
                 end;
            #7 : begin
                   MoveTo(Getx,Gety);LineRel(1,0);
                   MoveRel(-3,2);LineRel(0,-4);
                   MoveRel(1,0);LineRel(4,0);
                   MoveRel(0,1);LineRel(0,4);
                   MoveRel(-1,0);LineRel(-4,0);
                   MoveRel(5,0)
                 end;
            #8 : begin
                   MoveTo(Getx-2,Gety+1);LineRel(2,-3);
                   MoveRel(1,1);LineRel(1,2);
                   MoveRel(0,1);LineRel(-4,0);
                   MoveRel(6,0)
                 end;
            #9 : begin
                   MoveTo(Getx,Gety);
                   LineRel(1,0)
                 end;
            #24: begin
                   MoveTo(Getx,Gety-4);LineRel(2,-2);
                   MoveRel(1,1);LineRel(1,1);
                   MoveRel(-2,3);LineRel(0,-4);
                   MoveRel(5,5);
                 end;
            #25: begin
                   MoveTo(Getx,Gety-2);LineRel(2,2);
                   MoveRel(1,-1);LineRel(1,-1);
                   MoveRel(-2,-3);LineRel(0,4);
                   MoveRel(5,1)
                 end;
            ':': begin
                   MoveTo(Getx+2,Gety);LineRel(0,0);
                   MoveRel(0,-2);LineRel(0,0);
                   MoveRel(4,3);
                 end;
            '+': begin
                   MoveTo(GetX+2,GetY-1);LineRel(0,-1);
                   MoveRel(0,-2);LineRel(0,-1);
                   MoveRel(2,2);LineRel(-4,0);
                   MoveRel(6,3)
                 end;
            '-': begin
                   MoveTo(GetX+1,GetY-3);LineRel(2,0);
                   MoveRel(3,3)
                 end;
            '.': begin
                   MoveTo(GetX+2,GetY);LineRel(0,0);
                   MoveRel(4,0)
                 end;
            '/': begin
                   MoveTo(GetX,GetY);LineRel(6,-6);
                   MoveRel(2,6)
                 end;
            '\': begin
                   MoveTo(GetX,GetY);LineRel(6,6);
                   MoveRel(2,-6)
                 end;
            'o': begin
                   MoveTo(GetX+1,GetY);LineRel(2,0);
                   MoveRel(1,-1);LineRel(0,-2);
                   MoveRel(-1,-1);LineRel(-2,0);
                   MoveRel(-1,1);LineRel(0,2);
                   MoveRel(6,1)
                end;
            'x': begin
                   MoveTo(GetX,GetY);LineRel(4,-4);
                   MoveRel(-4,0);LineRel(1,1);
                   MoveRel(2,2);LineRel(1,1);
                   MoveRel(2,0)
                 end
             else case UpCase(ch) of
                   'A': begin
                          MoveTo(GetX,GetY);LineRel(0,-4);
                          MoveRel(1,-1);LineRel(1,-1);
                          MoveRel(1,1);LineRel(1,1);
                          MoveRel(0,1);LineRel(0,3);
                          MoveRel(-3,-2);LineRel(2,0);
                          MoveRel(3,2)
                        end;
                   'B': begin
                          MoveTo(GetX,GetY);LineRel(3,0);
                          MoveRel(1,-1);LineRel(0,-1);
                          MoveRel(-1,-1);LineRel(-2,0);
                          MoveRel(3,-1);LineRel(0,-1);
                          MoveRel(-1,-1);LineRel(-3,0);
                          MoveRel(0,1);LineRel(0,4);
                          MoveRel(6,1)
                        end;
                   'C': begin
                          MoveTo(GetX+1,GetY);LineRel(1,0);
                          MoveRel(1,0);LineRel(1,-1);
                          MoveRel(0,-4);LineRel(-1,-1);
                          MoveRel(-1,0);LineRel(-1,0);
                          MoveRel(-1,1);LineRel(0,4);
                          MoveRel(6,1)
                        end;
                   'D': begin
                          MoveTo(GetX,GetY);LineRel(3,0);
                          MoveRel(1,-1);LineRel(0,-4);
                          MoveRel(-1,-1);LineRel(-3,0);
                          MoveRel(0,1);LineRel(0,4);
                          MoveRel(6,1)
                        end;
                   'E': begin
                          MoveTo(GetX+4,GetY);LineRel(-4,0);
                          MoveRel(0,-1);LineRel(0,-5);
                          MoveRel(1,0);LineRel(3,0);
                          MoveRel(-3,3);LineRel(1,0);
                          MoveRel(4,3)
                        end;
                   'F': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(1,0);LineRel(3,0);
                          MoveRel(-3,3);LineRel(1,0);
                          MoveRel(4,3)
                        end;
                   'G': begin
                          MoveTo(GetX+2,GetY-3);LineRel(2,0);
                          MoveRel(0,1);LineRel(0,1);
                          MoveRel(-1,1);LineRel(-2,0);
                          MoveRel(-1,-1);LineRel(0,-4);
                          MoveRel(1,-1);LineRel(1,0);
                          MoveRel(1,0);LineRel(1,1);
                          MoveRel(2,5)
                        end;
                   'H': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(4,0);LineRel(0,6);
                          MoveRel(-1,-3);LineRel(-2,0);
                          MoveRel(5,3)
                        end;
                   'I': begin
                          MoveTo(GetX,GetY);LineRel(4,0);
                          MoveRel(-2,-1);LineRel(0,-4);
                          MoveRel(-2,-1);LineRel(4,0);
                          MoveRel(2,6)
                        end;
                   'J': begin
                          MoveTo(GetX,GetY-2);LineRel(0,1);
                          MoveRel(1,1);LineRel(2,0);
                          MoveRel(1,-1);LineRel(0,-5);
                          MoveRel(-1,0);LineRel(-3,0);
                          MoveRel(6,6)
                        end;
                   'K': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(4,0);LineRel(-3,3);
                          MoveRel(1,1);LineRel(2,2);
                          MoveRel(2,0)
                        end;
                   'L': begin
                          MoveTo(GetX+4,GetY);LineRel(-4,0);
                          MoveRel(0,-1);LineRel(0,-5);
                          MoveRel(6,6)
                        end;
                   'M': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(1,1);LineRel(1,1);
                          MoveRel(1,-1);LineRel(1,-1);
                          MoveRel(0,1);LineRel(0,5);
                          MoveRel(2,0)
                        end;
                   'N': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(1,2);LineRel(2,2);
                          MoveRel(1,-4);LineRel(0,6);
                          MoveRel(2,0)
                        end;
                   'O': begin
                          MoveTo(GetX+1,GetY);LineRel(2,0);
                          MoveRel(1,-1);LineRel(0,-4);
                          MoveRel(-1,-1);LineRel(-2,0);
                          MoveRel(-1,1);LineRel(0,4);
                          MoveRel(6,1)
                        end;
                   'P': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(1,0);LineRel(2,0);
                          MoveRel(1,1);LineRel(0,1);
                          MoveRel(-1,1);LineRel(-2,0);
                          MoveRel(5,3)
                        end;
                   'Q': begin
                          MoveTo(GetX+1,GetY); LineRel(2,0);
                          MoveRel(1,-1);LineRel(0,-4);
                          MoveRel(-1,-1);LineRel(-2,0);
                          MoveRel(-1,1);LineRel(0,4);
                          MoveRel(2,-1);LineRel(1,1);
                          MoveRel(1,1);LineRel(0,0);
                          MoveRel(2,0)
                        end;
                   'R': begin
                          MoveTo(GetX,GetY);LineRel(0,-6);
                          MoveRel(1,0);LineRel(2,0);
                          MoveRel(1,1);LineRel(0,1);
                          MoveRel(-1,1);LineRel(-2,0);
                          MoveRel(1,1);LineRel(2,2);
                          MoveRel(2,0)
                        end;
                   'S': begin
                          MoveTo(GetX,GetY-1);LineRel(1,1);
                          MoveRel(1,0);LineRel(1,0);
                          MoveRel(1,-1);LineRel(0,-1);
                          MoveRel(-1,-1);LineRel(-2,0);
                          MoveRel(-1,-1);LineRel(0,-1);
                          MoveRel(1,-1);LineRel(1,0);
                          MoveRel(1,0);LineRel(1,1);
                          MoveRel(2,5)
                        end;
                   'T': begin
                          MoveTo(GetX+2,GetY);LineRel(0,-5);
                          MoveRel(-2,-1);LineRel(4,0);
                          MoveRel(2,6)
                        end;
                   'U': begin
                          MoveTo(GetX,GetY-6);LineRel(0,5);
                          MoveRel(1,1);LineRel(2,0);
                          MoveRel(1,-1);LineRel(0,-5);
                          MoveRel(2,6)
                        end;
                   'V': begin
                          MoveTo(GetX,GetY-6);LineRel(0,4);
                          MoveRel(1,1);LineRel(1,1);
                          MoveRel(1,-1);LineRel(1,-1);
                          MoveRel(0,-1);LineRel(0,-3);
                          MoveRel(2,6)
                        end;
                   'W': begin
                          MoveTo(GetX,GetY-1);LineRel(0,-5);
                          MoveRel(4,0);LineRel(0,6);
                          MoveRel(-1,-1);LineRel(-1,-1);
                          MoveRel(-1,1);LineRel(-1,1);
                          MoveRel(6,0)
                        end;
                   'X': begin
                          MoveTo(GetX,GetY);LineRel(0,-1);
                          MoveRel(1,-1);LineRel(2,-2);
                          MoveRel(1,-1);LineRel(0,-1);
                          MoveRel(-4,0);LineRel(0,1);
                          MoveRel(1,1);LineRel(0,0);
                          MoveRel(2,2);LineRel(1,1);
                          MoveRel(0,1);LineRel(0,0);
                          MoveRel(2,0)
                        end;
                   'Y': begin
                          MoveTo(GetX,GetY-6);LineRel(0,1);
                          MoveRel(1,1);LineRel(1,1);
                          MoveRel(1,-1);LineRel(1,-1);
                          MoveRel(0,-1);LineRel(0,0);
                          MoveRel(-2,4);LineRel(0,2);
                          MoveRel(4,0)
                        end;
                   'Z': begin
                          MoveTo(GetX,GetY-6); LineRel(4,0);
                          MoveRel(0,1);LineRel(-4,4);
                          MoveRel(0,1);LineRel(4,0);
                          MoveRel(2,0)
                        end
                  end
           end
         end
   end; { F6x4 }

end.