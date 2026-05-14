{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ ASTA, OPL                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

const COM1handler : pointer = nil;
      COM2handler : pointer = nil;

var   Port21      : byte;

      SaveMain0   : TProc;
      SaveExit    : pointer;


{$IFDEF CONNECT_TO_ASTA_EXT}
  const  comASTA_PRN : byte = 1;
         comASTA_FDP : byte = 2;

  {$I _ASTA.int}
{$ENDIF}


{$IFDEF CONNECT_TO_OPL_EXT}
  {$IFDEF OPL_EXT_ASYNC}
   {$I _OPL.int}
  {$ENDIF}
{$ENDIF}


{$IFDEF CONNECT_TO_CAMUS}
  {$IFNDEF CAMUS_OLDI}
   {$I _CAMUS.int}
  {$ENDIF}
{$ENDIF}


{$IFDEF CONNECT_TO_AFTN}
  {$I _AFTN.int}
{$ENDIF}



procedure check_COMs; far;
    begin
      if @SaveMain0<>nil then SaveMain0;

      {$IFDEF CONNECT_TO_ASTA_EXT}
        {$IFDEF ASTA_PRN}
          check_ASTA_PRN;
        {$ENDIF}
        {$IFDEF ASTA_FDP}
          check_ASTA_FDP;
        {$ENDIF}
      {$ENDIF}
    end;


procedure done_COMs; far;
    begin
      asm cli end;

      if COMsaved[1] then SetCOMi(1,LoBd[1],HiBd[1],Bits[1],Inte[1],Modem[1]);
      if COMsaved[2] then SetCOMi(2,LoBd[2],HiBd[2],Bits[2],Inte[2],Modem[2]);

      SetIntVec(INT_COM[1],COM1handler);
      SetIntVec(INT_COM[2],COM2handler);

     {Port[$21]:= Port[$21] or $18;}  { 0x10 && 0x80 }
      Port[$21]:= Port21;

      asm sti end;

      ExitProc:= SaveExit
    end;


{ Inicializacia je nesikovne v hlavnom programe, pretoze boli problemy
  s inicializaciou intr pre COM v unite a nebol cas preverit spolahlivost
  takeho riesenia.
}
 procedure init_COMs;
     begin
       asm cli end;

       GetIntVec(INT_COM[1],COM1handler);
       GetIntVec(INT_COM[2],COM2handler);


       {$IFDEF CONNECT_TO_ASTA_EXT}
        {$IFDEF ASTA_PRN}
          SaveCOMi (comASTA_PRN);
          SetCOMi  (comASTA_PRN,12,0,$1A,$01,$0B);
          SetIntVec(INT_COM[comASTA_PRN],@ReadCOM_ASTA_PRN);
        {$ENDIF}

        {$IFDEF ASTA_FDP}
          SaveCOMi (comASTA_FDP);
          SetCOMi  (comASTA_FDP,12,0,$1A,$01,$0B);
          SetIntVec(INT_COM[comASTA_FDP],@ReadCOM_ASTA_FDP);
        {$ENDIF}
       {$ENDIF}


       {$IFDEF CONNECT_TO_OPL_EXT}
         {$IFDEF OPL_EXT_ASYNC}
           if DEV_OPL<>nil then SetIntVec(INT_COM[DEV_OPL^.asyncCOM],@ReadOPL);
         {$ENDIF}
       {$ENDIF}


       {$IFDEF CONNECT_TO_AFTN}
         if DEV_AFTN<>nil then SetIntVec(INT_COM[DEV_AFTN^.asyncCOM],@ReadAFTN);
       {$ENDIF}


       {$IFDEF CONNECT_TO_CAMUS} {$IFNDEF CAMUS_OLDI}
         if DEV_CAMUS<>nil then with DEV_CAMUS^ do SetIntVec(INT_COM[DEV_CAMUS^.asyncCOM],@ReadCAMUS);
       {$ENDIF} {$ENDIF}


       Port21:= Port[$21];
       Port[$21]:= Port[$21] and $E7; { 0xE8 && 0xF7 }

       asm sti end;

       SaveMain0:= ACheckProcesses0;
       ACheckProcesses0:= check_COMs;

       SaveExit:= ExitProc;
       ExitProc:= @done_COMs
     end;
