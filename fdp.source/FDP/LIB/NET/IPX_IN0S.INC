    function GetAdrIPX: bool;
       var   Regs: Registers;
       begin
         with Regs do
           begin
             AX:= $7A00;
             Intr($2F,Regs);
             if (AX and $00FF)=$FF then
                begin
                  AdrIPX[1]:= ES;
                  AdrIPX[0]:= DI;
                  adr_AdrIPX:= Ptr(AdrIPX[1],AdrIPX[0]);
                end
             else adr_AdrIPX:= nil
           end;
         GetAdrIPX:= adr_AdrIPX<>nil
       end; { get_adr_AdrIPX }

    {
      funkcia otvori socket sc_num, sc_num je hi-lo
      ak OK vrati 1, inak 0
    }
    function IPX_open_socket(sc_num: word): byte; far;
       var   pom: byte;
       begin
         asm
           mov  BX,0
           mov  AL,0
           mov  DX,sc_num
           call adr_AdrIPX
           mov  pom,AL
         end;
         if pom=0 then IPX_open_socket:= 1
         else IPX_open_socket:= 0
       end; { IPX_open_socket }


    {
      funkcia zavrie socket sc_num, sc_num je hi-lo
    }
    procedure IPX_close_socket(sc_num: word); {far;}
        begin
          asm
            mov  BX,$01
            mov  DX,sc_num
            call adr_AdrIPX
          end
        end; { IPX_close_socket }

