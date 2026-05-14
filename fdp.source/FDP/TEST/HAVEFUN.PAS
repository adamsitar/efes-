{$I comp.h}

uses  bios,keyb,typedef,crt,str0;

var   ch: char; cit: byte;

begin
 ch:= ' '; cit:= 0;
 repeat
   if kbhit then ch:= getkey;
   delay(800);
   gotoxy(1,25);
   TextColor(LightGray{+Blink});
   if cit=0 then write('                              ');
   gotoxy(1,25);
   write('Formating C... '+cstr(cit,2)+'%');
   cit:= (cit+1) mod 100;
   if cit=0 then
      begin
        gotoxy(1,25);
        TextColor(LightGray+Blink);
        write('Disk failure. Trying again...');
        TextColor(LightGray);
        delay(2000);
      end;
 until ch=kbEsc;
 TextColor(LightGray);
end.