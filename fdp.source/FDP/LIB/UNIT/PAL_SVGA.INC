{$IFDEF BGI}

  procedure set_RGBcolors(P: Tpaleta; od,pocet: word); assembler;

  {$IFDEF EGAVGA}
  asm
  end;

  {$ELSE}
  asm
                  push ds
                  mov dx,$3da
  @wait1:         in al,dx
                  test al,08
                  je @wait1

                  lds si,P
                  mov ax,od
                  add ax,od
                  add ax,od
                  add si,ax
		  MOV	CX,pocet

                  CMP	CX,0
		  JG	@GVP0
		  JMP	@GVPX
  @GVP0:		MOV	DX,03C6H
		  MOV	AL,0ffH
		  OUT	DX,AL

		  MOV	BX,od

  @GVP1:		PUSH	CX
		  MOV	DX,03C8H
		  MOV	AL,BL
		  INC	BX

		  OUT	DX,AL

		  INC	DX

		  LODSB
		  SHR	AL,1
		  SHR	AL,1
		  OUT	DX,AL

		  LODSB
		  SHR	AL,1
		  SHR	AL,1
		  OUT	DX,AL

		  LODSB
		  SHR	AL,1
		  SHR	AL,1
		  OUT	DX,AL

		  POP	CX
		  LOOP    @GVP1


  @GVPX:  	POP	DS
  {
                  mov dx,$3da
  @wait:          in al,dx
                  test al,08
                  je @wait
  }
  end;
  {$ENDIF}

  procedure GetDefaultPalette(var P: Tpaleta);
     var    r : registers;
     begin
       with r do begin
         al:= $17;
         ah:= $10;
         bx:= 0;
         cx:= 256;
         es:= seg(P[0].r);
         dx:= ofs(P[0].r);
       end;
       intr($10,r);
     end;

  procedure shift_RGBcolor(var RGBc: Tcolor; val: real);
      begin
        with RGBc do
          begin
            r:= byte (trunc(val*r));
            g:= byte (trunc(val*g));
            b:= byte (trunc(val*b))
          end
      end;


{
  standartne + seda
}
procedure init_RGB_0_31;
    var   i: int;
    begin
      GetDefaultPalette(P256);  { naplnenie pola hodnot registrov  }
      for i:=  0  to  31 do shift_RGBcolor(P256[i],4);  { transformacia EGA (64bitov) do VGA (256bitov) }
    end;

{$ENDIF}