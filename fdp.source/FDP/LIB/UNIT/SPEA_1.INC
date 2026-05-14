
{ ----------------- Load Text Font ------------------------ }

function spldfont(fonttxt: str9): int;
   var   i : int;
   begin
     packet.pldfont.pfunc := SPLDFNTF;
     if length(fonttxt) < 8 then for i:= length(fonttxt)+1 to 8 do fonttxt[i]:= ' ';
     packet.pldfont.segment := seg ( fonttxt [1] );
     packet.pldfont.offset  := ofs ( fonttxt [1] );
     fonttxt[9]:=chr(0);
     call_graphic_driver;
     spldfont := packet.pldfont.stat
   end;



{ ----------------- Set Font System ------------------------ }

function spsetfont(fonttxt: str9): int;
   var   i : int;
   begin
     packet.pstfont.pfunc := SPSTFNTF;
     if length(fonttxt) < 8 then  for i:= length(fonttxt)+1 to 8 do fonttxt[i]:= ' ';
     packet.pstfont.segment:= seg ( fonttxt [1] );
     packet.pstfont.offset := ofs ( fonttxt [1] );
     fonttxt[9]:= chr(0);
     call_graphic_driver;
     spsetfont := packet.pstfont.fontnr
   end;


{ ----------------- Select Font System ------------------------ }

function SPselfont(fontnr: word): int;
   begin
     packet.pslfont.pfunc := SPSLFNTF;
     packet.pslfont.fontnr:= int(fontnr);
     call_graphic_driver;
     SPselfont:= packet.pslfont.stat;
     SPfont:= fontnr;
     dx_ch:= Fonts[SPfont].dx;
     dy_ch:= Fonts[SPfont].dy
   end;



{ ----------------- Remove Font System ------------------------ }

function SPremovefont(fontnr: int): int;
   begin
     packet.prmfont.pfunc := SPRMFNTF;
     packet.prmfont.fontnr:= fontnr;
     call_graphic_driver;
     spremovefont := packet.prmfont.stat
   end;



{ -----------------  Count Font System ------------------------ }

procedure spenfont(var fonts: int);
    begin
      packet.penfont.pfunc := SPENFNTF;
      call_graphic_driver;
      fonts := packet.penfont.count;
    end;



{ -----------------------------
   i-dei-nicializacia fontov
  ----------------------------- }

function load_font(_font: byte; _name: string; _dx,_dy: byte): byte;
   var   res: int;
   begin
     res:= SPsetfont(_name);
     if res<0 then
        begin
          writeln(#7,'Not enough SPEA memory. Reboot computer.',#7);
          Halt(1)
        end;
     with Fonts[_font] do
       begin
         ind:= res;
         dx := _dx;
         dy := _dy
       end;
     SPldfont(_name);
     load_font:= res
   end; { SetFont }


procedure Fonts_init;
    begin
      load_font(BIT8x8,'BIT8x8',8,8);
      load_font(COND8x16,'COND8x16',8,16);
      load_font(SYS8x16,'SYS8x16',8,16);
      load_font(SYS8x20,'SYS8x20',8,20);
      load_font(SYS12x20,'SYS12x20',12,20);
      load_font(SYS16x32,'SYS16x32',16,32)
    end; { SP_fnt }


procedure Fonts_done;
    var   i: int;
    begin
      for i:= 0 to maxFonts-1 do SPremovefont(Fonts[i].ind)
    end;
