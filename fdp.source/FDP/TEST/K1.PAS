{$I comp.h}

uses _l4_def,crt,math;

var m,i : longint;
    f: text;

procedure FL(m: integer);
    begin
      writeln(f,'S',m,' FL',MtoFL(StoM(m)))
    end;

begin

 clrscr; textmode(C80 + Font8x8);
 assign(f,'1.bak');
 rewrite(f);
(*
 FL(0120);
 FL(0185);
 FL(0245);
 FL(0305);
 FL(0365);
 FL(0425);
 FL(0490);
 FL(0550);
 FL(0610);
 FL(0670);
 FL(0730);
 FL(0790);
 FL(0855);
 FL(0945);
 FL(1065);
 FL(1190);
 FL(1310);
 FL(1435);

 writeln;


 FL(0150);
 FL(0215);
 FL(0275);
 FL(0335);
 FL(0395);
 FL(0455);
 FL(0520);
 FL(0580);
 FL(0640);
 FL(0700);
 FL(0760);
 FL(0825);
 FL(0885);
 FL(1005);
 FL(1130);
 FL(1250);
 FL(1370);
 FL(1495);
*)
 writeln;
{ FL(0365);
 FL(0395);}

{ for i:= 1 to 9 do writeln('F',120+i,' S',MtoS(FLtoM(120+i)));}

 for i:= 0 to 30 do
    begin
      {writeln(f,'S',365+i,' ',
              'F',trunc(Zaokruhli(trunc((365+i)/m_ft/m_S),10) / m_S)
             );}
      FL(365+i);
    end;
 close(f);

 writeln('S',MtoS(FLtoM(125)));
 writeln('S',MtoS(FLtoM(135)));
 writeln('S',MtoS(FLtoM(145)));

 writeln('S',MtoFL(StoM(MtoS(FLtoM(125)))));
 writeln('S',MtoFL(StoM(MtoS(FLtoM(135)))));
 writeln('S',MtoFL(StoM(MtoS(FLtoM(145)))));
end.