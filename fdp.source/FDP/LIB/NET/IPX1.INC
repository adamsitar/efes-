{ -------------------- }
{                      }
{ -------------------- }


{ -------------------- }
{  Listen & Send       }
{ -------------------- }

function ListenIPX(node: byte): byte;
    var  Pom1,Pom2: word;
         Pom3: byte;
    begin
      Pom1:= Seg(ECB[1,node]);
      Pom2:= Ofs(ECB[1,node]);
      asm
        mov  BX,$0004
        push ES
        push SI
        mov  ES,Pom1
        mov  SI,Pom2
        push BP
        call adr_AdrIPX
        pop  BP
        pop  SI
        pop  ES
        mov  Pom3,AL
      end;
      ListenIPX:= Pom3
    end; { ListenIPX }


procedure SendIPX(node: byte);
    var   Pom1,Pom2: word;
    begin
      Pom1:= Seg(ECB[0,node]);
      Pom2:= Ofs(ECB[0,node]);
      asm
        mov  BX,$0003
        push ES
        push SI
        mov  ES,Pom1
        mov  SI,Pom2
        push bp
        call adr_AdrIPX
        pop  bp
        pop  SI
        pop  ES
      end
    end; { SendIPX }


procedure MessIPX(node,sprava: byte);
    begin
      if ECB[0,node].InUse=0 then
         begin
           ECB[0,node].BufSize      := 30;
           IPXBuf[0,node].PacketType:= sprava;

           IPXBuf[0,node].DestNet   := NulNameNet;
           IPXBuf[0,node].DestNode  := IPXnodes[node]^.Adr;
           IPXBuf[0,node].DestSocket:= CSocket[0,node];
           SendIPX(node)
         end
      else Delay(1)
    end; { MessIPX }
