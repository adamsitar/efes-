    function GetAdrIPX: bool;
       var   Regs: Registers;
       begin
         with Regs do begin
           AX:= $7A00;
           Intr($2F,Regs);
           if (AX and $00FF)=$FF then
              begin
                AdrIPX[1]:= ES;
                AdrIPX[0]:= DI;
                adr_AdrIPX:= Ptr(AdrIPX[1],AdrIPX[0]);
                GetAdrIPX:= true
              end
            else GetAdrIPX:= false
         end
       end; { GetAdrIPX }

    procedure GetSocketTable(CS: byte);
        var   d,e: byte;
        begin
          for d:=1 to maxIPX_NODEs do
            begin
              CSocket[1,d,0]:= $50;
              CSocket[1,d,1]:= (d shl 4) or CS;
            end;
          e:= CS shl 4;
          for d:=1 to maxIPX_NODEs do
            Begin
              CSocket[0,d,0]:= $50;
              CSocket[0,d,1]:= e or d;
            End;
          CSocket[0,0,0]:= $51; CSocket[0,0,1]:= $00;
          CSocket[1,0,0]:= $51; CSocket[1,0,1]:= $00
        end;

    function OpenSocket(p1,p2: byte): byte;
       var   Pom1,Pom2,Pom3: byte;
       begin
         Pom1:= CSocket[p1,p2,0];
         Pom2:= CSocket[p1,p2,1];
         asm
           mov  BX,$0000
           mov  AL,$00
           mov  DH,Pom2
           mov  DL,Pom1
           call adr_AdrIPX
           mov  Pom3,AL
         end;
         OpenSocket:= Pom3
       end; { OpenSocket }

    procedure CloseSocket(p1,p2: byte);
        var   Pom1,Pom2: byte;
        begin
          Pom1:= CSocket[p1,p2,0];
          Pom2:= CSocket[p1,p2,1];
          asm
            mov  BX,$0001
            mov  DH,Pom2
            mov  DL,Pom1
            call adr_AdrIPX
          end;
        end; { CloseSocket }

