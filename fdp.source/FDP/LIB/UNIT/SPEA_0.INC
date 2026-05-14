{ -----------------------------
   std i-dei-nicializacne fcie
  ----------------------------- }

function CheckRes : int ;
   type  identity  = array [0..7] of Char;
   var   i,intnum : int;
         id : identity;
   label CheckResExit;
   begin
     intnum := $40;
     while intnum < $100 do
       begin
         reg.ax:= $3500 + intnum;  { ah = $35 getintvec; al = intnum }
         msdos(reg);
         i:= 0;
         while i<8 do
           begin
             id[i]:= Chr(Mem[reg.es:reg.bx+3+i]);
             i    := i+1;
           end;
         if (id = 'SPDRIVER') then goto CheckResExit;
         intnum := intnum +1;
       end;
     intnum:= -1;
     CheckResExit: CheckRes:= intnum
   end;

function SPinit: int;
   begin
     if CheckRes<>-1 then
        begin
  	  interrupt_nr:= Checkres;
  	  packet.pinit.pfunc:= SPINITF;
	  call_graphic_driver;
	  spinit:= packet.pinit.status
	end
     else spinit:= -1
   end;


{
  Unload Spea Driver
}
procedure SPunres;
    begin
      packet.punres.pfunc:= SPUNRESF;
      call_graphic_driver
    end;

{
  End
}
procedure SPend;
    begin
      packet.pend.pfunc:= SPENDF;
      call_graphic_driver;
    end;


