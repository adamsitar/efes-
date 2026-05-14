{ ---------------------------------------------------------------- }
{  PRERUSOVACIE RUTINY                                             }
{ ---------------------------------------------------------------- }

{$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
{$IFOPT S+} {$DEFINE R} {$S-} {$ENDIF}
                        {$F+}

procedure IPXinterrupt(node: byte); far;
    var   typ : int;
    begin
      if (ECB[1,node].Compl = 0) {and (LANnodes[node]^.is_intr_en)} then
         with IPXnodes[node]^ do
         begin
           intr_cli;
           typ:= IPXBuf[1,node].PacketType;

           if (typ = ipxDATA) then
              begin
                inp_buff^.size:= IPXBuf[1,node].Len[0] shl 8 + IPXBuf[1,node].Len[1] - 30;
                if inp_buff^.size>sizeof(inp_buff^.data) then inp_buff^.size:= sizeof(inp_buff^.data);
                Move(IPXBuf[1,node].Data,inp_buff^.data,inp_buff^.size);

                if (pro in [RTR,RTI]) or ((ROUTERipx>-1) and (node=ROUTERipx)) then RTRsave(inp_buff)
                else IPXsave(inp_buff)
              end;

           if (typ = ipxVYZVA) or (not TrasaOK) then begin to_init:= 1; Out_buff^.size:= 0 end;
           TrasaOK   := true;
           SendOK    := true;
           next_test := (sec+IPX__HEARTBEAT) mod 60;
           Tested    := false;
           if (typ<>ipxPOTVRDENIE) then MessIPX(node,ipxPOTVRDENIE);  {(typ=IPXdata) or (typ = ipxVYZVA) or (typ = ipxTEST)}
           intr_sti
         end;
      ListenIPX(node)
    end; { IPXinterrupt }



{
 !!! Bacha na konflikt IPXarch a BROADCAST v NET ...
}
{$IFDEF BROADCAST}
  procedure IPXbroadcast(node: byte); far;
      begin
        if ECB[1,node].Compl=0 then with IPXnodes[node]^ do
           begin

             SKONTROLOVAT

            {$IFDEF ARCHIVE_DAR}

              with inp_buff^ do
                begin
                  size:= IPXBuf[1,node].Len[0] shl 8 + IPXBuf[1,node].Len[1] - 31;
                  data:= IPXBuf[1,node].Data
                end;
              if (save_RLI<>nil) then Tproc_pw(save_RLI)(@Inp_buff^.Data, Inp_buff^.size+1);

            {$ELSE}

              with inp_brd_buff^ do
                begin
                  size:= Minimum(sizeof(data),IPXBuf[1,node].Len[0] shl 8 + IPXBuf[1,node].Len[1] - 30);
                         --------> int nemoze byt

                  move(IPXBuf[1,node].Data,data,size)
                end;

              {
              if (isIPXbroadcast=nil) or ((isIPXbroadcast<>nil) and (TBFunc_PIPXp(isIPXbroadcast)(Inp_buff))) then
                 begin
                   IPXBsave(pointer(Inp_buff))
                 end;
              }

             if (isIPXbroadcast=nil) or ((TBFunc_p(isIPXbroadcast)(inp_brd_buff))) then
                begin
                  if brd_buff<>nil then brd_buff^.save(inp_brd_buff)
                end;


            {$ENDIF}
           end;
        ListenIPX(node)
      end;
{$ENDIF}



{ ------------------------ }
{   0.uzol: broadcoast     }
{ ------------------------ }

const intr_0: byte = 0;

procedure PrijInt0;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_0,0
        je   @@1
        mov  intr_0,0 }

        mov  AL,0
        push AX

       {$IFDEF BROADCAST}
         call IPXbroadcast
       {$ELSE}
         call IPXinterrupt
       {$ENDIF}

       {mov  intr_0,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------ }
{   1.uzol:                }
{ ------------------------ }

const intr_1: byte = 0;

procedure PrijInt1;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_1,1
        je   @@1
        mov  intr_1,1 }

        mov  AL,1
        push AX
        call IPXinterrupt

       {mov  intr_1,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------ }
{   2.uzol:                }
{ ------------------------ }

const intr_2: byte = 0;

procedure PrijInt2;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_2,1
        je   @@1
        mov  intr_2,1 }

        mov  AL,2
        push AX
        call IPXinterrupt

       {mov  intr_2,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------ }
{   3.uzol:                }
{ ------------------------ }

const intr_3: byte = 0;

procedure PrijInt3;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_3,1
        je   @@1
        mov  intr_3,1 }

        mov  AL,3
        push AX
        call IPXinterrupt

       {mov  intr_3,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------ }
{   4.uzol:                }
{ ------------------------ }

const intr_4: byte = 0;

procedure PrijInt4;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_4,1
        je   @@1
        mov  intr_4,1 }

        mov  AL,4
        push AX
        call IPXinterrupt

       {mov  intr_4,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------ }
{   5.uzol:                }
{ ------------------------ }

const intr_5: byte = 0;

procedure PrijInt5;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_5,1
        je   @@1
        mov  intr_5,1 }

        mov  AL,5
        push AX
        call IPXinterrupt

       {mov  intr_5,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------- }
{   6.uzol:                 }
{ ------------------------- }

const intr_6: byte = 0;

procedure PrijInt6;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_6,1
        je   @@1
        mov  intr_6,1 }

        mov  AL,6
        push AX
        call IPXinterrupt

       {mov  intr_6,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------- }
{   7.uzol:                 }
{ ------------------------- }

const intr_7: byte = 0;

procedure PrijInt7;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_7,1
        je   @@1
        mov  intr_7,1 }

        mov  AL,7
        push AX
        call IPXinterrupt

       {mov  intr_7,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------- }
{   8.uzol:                 }
{ ------------------------- }

const intr_8: byte = 0;

procedure PrijInt8;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_8,1
        je   @@1
        mov  intr_8,1 }

        mov  AL,8
        push AX
        call IPXinterrupt

       {mov  intr_8,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ------------------------- }
{   9.uzol:                 }
{ ------------------------- }

const intr_9: byte = 0;

procedure PrijInt9;
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

       {cmp  intr_9,1
        je   @@1
        mov  intr_9,1 }

        mov  AL,9
        push AX
        call IPXinterrupt

       {mov  intr_9,0
       @@1:}

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{$IFDEF R} {$UNDEF R} {$R-} {$ENDIF}
{$IFDEF S} {$UNDEF S} {$S-} {$ENDIF}
