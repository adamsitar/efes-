{*******************************************************}
{                                                       }
{ Turbo Pascal Version 7.0                              }
{ Standard Objects Unit                                 }
{                                                       }
{ Copyright (c) 1992 Borland International              }
{                                                       }
{ Upraveny modul, prevzaty z EMS TEmsStream bol         }
{ povodne odvodeny z TStream, ale nie je to potrebne    }
{                                                       }
{ Aby sa mohlo pracovet s EMS v prostredi IDE musi byt  }
{ nastavena premenna SET DPMIMEM=MAXMEM nnnn            }
{ kde nnnn je pocet kB EMS pre IDE BP                   }
{ Najlepsie je ju nastavit v autoexec.bat.              }
{                                                       }
{                         Igor Valigura November 1996   }
{                                                       }
{*******************************************************}

{$O-,F+,X+,I-,S-}


unit Stream;


interface


    const { TStream access modes }

            stCreate    = $3C00;           { Create new file }
            stOpenRead  = $3D00;           { Read access only }
            stOpenWrite = $3D01;           { Write access only }
            stOpen      = $3D02;           { Read and write access }

          { TStream error codes }

            stOk         =  0;              { No error }
            stError      = -1;              { Access error }
            stInitError  = -2;              { Cannot initialize stream }
            stReadError  = -3;              { Read beyond end of stream }
            stWriteError = -4;              { Cannot expand stream }
            stGetError   = -5;              { Get of unregistered object type }
            stPutError   = -6;              { Put of unregistered object type }

          { Maximum TCollection size }

            MaxCollectionSize = 65520 div SizeOf(Pointer);

          { TCollection error codes }

            coIndexError = -1;              { Index out of range }
            coOverflow   = -2;              { Overflow }

          { VMT header size }

            vmtHeaderSize = 8;


    type  { Type conversion records }

            WordRec = record
              Lo, Hi: Byte;
            end;

            LongRec = record
              Lo, Hi: Word;
            end;

            PtrRec = record
              Ofs, Seg: Word;
            end;

          { String pointers }

            PString = ^String;

          { Character set type }

            PCharSet = ^TCharSet;
            TCharSet = set of Char;

          { General arrays }


          { TObject base object }

    type    PObject = ^TObject;
            TObject = object
              constructor Init;
              procedure   Free;
              destructor  Done; virtual;
            end;

          { TStreamRec }

            PStreamRec = ^TStreamRec;
            TStreamRec = record
              ObjType : Word;
              VmtLink : Word;
              Load    : Pointer;
              Store   : Pointer;
              Next    : Word;
            end;

          { TStream }

            PStream = ^TStream;
            TStream = object(TObject)

              Status    : Integer;
              ErrorInfo : Integer;
              is        : boolean;

              constructor Init;
              procedure   CopyFrom(var S: TStream; Count: Longint);
              procedure   Error(Code, Info: Integer); virtual;
              procedure   Flush; virtual;

              function    Get: PObject;
              function    GetPos: Longint; virtual;
              function    GetSize: Longint; virtual;
              procedure   Put(P: PObject);
              procedure   Read(var Buf; Count: Word); virtual;
              function    ReadStr: PString;
              procedure   Reset;
              procedure   Seek(Pos: Longint); virtual;
              function    StrRead: PChar;
              procedure   StrWrite(P: PChar);
              procedure   Truncate; virtual;
              procedure   Write(var Buf; Count: Word); virtual;
              procedure   WriteStr(P: PString);
            end;


          { TEmsStream }

            PEmsStream = ^TEmsStream;
            TEmsStream = object(TStream)
              Handle     : Word;
              PageCount  : Word;
              Size       : Longint;
              Position   : Longint;

              constructor Init(MinSize, MaxSize: Longint);
              destructor  Done; virtual;

              function    GetPos: Longint; virtual;
              function    GetSize: Longint; virtual;

              procedure   Read(var Buf; Count: Word); virtual;
              procedure   Seek(Pos: Longint); virtual;
              procedure   Truncate; virtual;
              procedure   Write(var Buf; Count: Word); virtual;
            end;


          { Longint routines }

            function LongMul(X, Y: Integer): Longint;
            inline($5A/$58/$F7/$EA);

            function LongDiv(X: Longint; Y: Integer): Integer;
            inline($59/$58/$5A/$F7/$F9);


          { Stream routines }

            procedure RegisterType(var S: TStreamRec);

          { Abstract notification procedure }

            procedure Abstract;



    const { Stream error procedure }

            StreamError  : Pointer = nil;

          { EMS stream state variables }

            EmsCurHandle : Word = $FFFF;
            EmsCurPage   : Word = $FFFF;


implementation

uses Str0, mess;

{$IFDEF Windows}
  {$DEFINE NewExeFormat}
{$ENDIF}

{$IFDEF DPMI}
  {$DEFINE NewExeFormat}
{$ENDIF}

procedure Abstract;
begin
  system.RunError(211);
end;

{ TObject }

constructor TObject.Init;
type
  Image = record
    Link: Word;
    Data: record end;
  end;
begin
{$IFNDEF Windows}
  FillChar(Image(Self).Data, SizeOf(Self) - SizeOf(TObject), 0);
{$ENDIF}
end;

{ Shorthand procedure for a done/dispose }

procedure TObject.Free;
begin
  Dispose(PObject(@Self), Done);
end;

destructor TObject.Done;
begin
end;

{ TStream type registration routines }

const
  StreamTypes: Word = 0;

procedure RegisterError;
begin
  system.RunError(212);
end;

procedure RegisterType(var S: TStreamRec); assembler;
asm
        MOV     AX,DS
        CMP     AX,S.Word[2]
        JNE     @@1
        MOV     SI,S.Word[0]
        MOV     AX,[SI].TStreamRec.ObjType
        OR      AX,AX
        JE      @@1
        MOV     DI,StreamTypes
        MOV     [SI].TStreamRec.Next,DI
        JMP     @@3
@@1:    JMP     RegisterError
@@2:    CMP     AX,[DI].TStreamRec.ObjType
        JE      @@1
        MOV     DI,[DI].TStreamRec.Next
@@3:    OR      DI,DI
        JNE     @@2
        MOV     StreamTypes,SI
end;

{ TStream support routines }

const
  TStream_Error = vmtHeaderSize + $04;
  TStream_Flush = vmtHeaderSize + $08;
  TStream_Read  = vmtHeaderSize + $14;
  TStream_Write = vmtHeaderSize + $20;

{ Stream error handler                                  }
{ In    AX    = Error info                              }
{       DX    = Error code                              }
{       ES:DI = Stream object pointer                   }
{ Uses  AX,BX,CX,DX,SI                                  }

procedure DoStreamError; near; assembler;
asm
        PUSH    ES
        PUSH    DI
        PUSH    DX
        PUSH    AX
        PUSH    ES
        PUSH    DI
        MOV     DI,ES:[DI]
        CALL    DWORD PTR [DI].TStream_Error
        POP     DI
        POP     ES
end;

{ TStream }

constructor TStream.Init;
begin
  TObject.Init;
  Status := 0;
  ErrorInfo := 0;
  is := true
end;

procedure TStream.CopyFrom(var S: TStream; Count: Longint);
var
  N: Word;
  Buffer: array[0..1023] of Byte;
begin
  while Count > 0 do
  begin
    if Count > SizeOf(Buffer) then N := SizeOf(Buffer) else N := Count;
    S.Read(Buffer, N);
    Write(Buffer, N);
    Dec(Count, N);
  end;
end;

procedure TStream.Error(Code, Info: Integer);
type
  TErrorProc = procedure(var S: TStream);
begin
  Status := Code;
  ErrorInfo := Info;
  if StreamError <> nil then TErrorProc(StreamError)(Self);
end;

procedure TStream.Flush;
begin
end;

function TStream.Get: PObject; assembler;
asm
        PUSH    AX
        MOV     AX,SP
        PUSH    SS
        PUSH    AX
        MOV     AX,2
        PUSH    AX
        LES     DI,Self
        PUSH    ES
        PUSH    DI
        MOV     DI,ES:[DI]
        CALL    DWORD PTR [DI].TStream_Read
        POP     AX
        OR      AX,AX
        JE      @@3
        MOV     BX,StreamTypes
        JMP     @@2
@@1:    CMP     AX,[BX].TStreamRec.ObjType
        JE      @@4
        MOV     BX,[BX].TStreamRec.Next
@@2:    OR      BX,BX
        JNE     @@1
        LES     DI,Self
        MOV     DX,stGetError
        CALL    DoStreamError
@@3:    XOR     AX,AX
        MOV     DX,AX
        JMP     @@5
@@4:    LES     DI,Self
        PUSH    ES
        PUSH    DI
        PUSH    [BX].TStreamRec.VmtLink
        XOR     AX,AX
        PUSH    AX
        PUSH    AX
        CALL    [BX].TStreamRec.Load
@@5:
end;

function TStream.GetPos: Longint;
begin
  Abstract;
end;

function TStream.GetSize: Longint;
begin
  Abstract;
end;

procedure TStream.Put(P: PObject); assembler;
asm
        LES     DI,P
        MOV     CX,ES
        OR      CX,DI
        JE      @@4
        MOV     AX,ES:[DI]
        MOV     BX,StreamTypes
        JMP     @@2
@@1:    CMP     AX,[BX].TStreamRec.VmtLink
        JE      @@3
        MOV     BX,[BX].TStreamRec.Next
@@2:    OR      BX,BX
        JNE     @@1
        LES     DI,Self
        MOV     DX,stPutError
        CALL    DoStreamError
        JMP     @@5
@@3:    MOV     CX,[BX].TStreamRec.ObjType
@@4:    PUSH    BX
        PUSH    CX
        MOV     AX,SP
        PUSH    SS
        PUSH    AX
        MOV     AX,2
        PUSH    AX
        LES     DI,Self
        PUSH    ES
        PUSH    DI
        MOV     DI,ES:[DI]
        CALL    DWORD PTR [DI].TStream_Write
        POP     CX
        POP     BX
        JCXZ    @@5
        LES     DI,Self
        PUSH    ES
        PUSH    DI
        PUSH    P.Word[2]
        PUSH    P.Word[0]
        CALL    [BX].TStreamRec.Store
@@5:
end;

procedure TStream.Read(var Buf; Count: Word);
begin
  Abstract;
end;

function TStream.ReadStr: PString;
var
  L: Byte;
  P: PString;
begin
  Read(L, 1);
  if L > 0 then
  begin
    GetMem(P, L + 1);
    P^[0] := Char(L);
    Read(P^[1], L);
    ReadStr := P;
  end else ReadStr := nil;
end;

procedure TStream.Reset;
begin
  Status := 0;
  ErrorInfo := 0;
end;

procedure TStream.Seek(Pos: Longint);
begin
  Abstract;
end;

function TStream.StrRead: PChar;
var
  L: Word;
  P: PChar;
begin
  Read(L, SizeOf(Word));
  if L = 0 then StrRead := nil else
  begin
    GetMem(P, L + 1);
    Read(P[0], L);
    P[L]:= #0;
    StrRead := P;
  end;
end;

procedure TStream.StrWrite(P: PChar);
    var   L : Word;
    begin
      if P = nil then L := 0 else L := StrLen(P);
      Write(L, SizeOf(Word));
      if P <> nil then Write(P[0], L);
    end;

procedure TStream.Truncate;
begin
  Abstract;
end;

procedure TStream.Write(var Buf; Count: Word);
    begin
      Abstract;
    end;

procedure TStream.WriteStr(P: PString);
const
  Empty: String[1] = '';
begin
  if P <> nil then Write(P^, Length(P^) + 1) else Write(Empty, 1);
end;


{ TEmsStream }

const
  EmsPageSize = $4000;

var
  EmsBaseSeg: Word;
  EmsVersion: Byte;

procedure EmsSelectPage; near; assembler;
asm
        MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        MOV     CX,EmsPageSize
        DIV     CX
        SUB     CX,DX
        MOV     SI,DX
        MOV     DX,ES:[DI].TEmsStream.Handle
        CMP     DX,EmsCurHandle
        JNE     @@1
        CMP     AX,EmsCurPage
        JE      @@3
@@1:    MOV     BX,AX
        MOV     AX,4400H
        INT     67H
        MOV     AL,AH
        AND     AX,0FFH
        JE      @@2
        MOV     DX,stError
        JMP     @@3
@@2:    MOV     EmsCurHandle,DX
        MOV     EmsCurPage,BX
@@3:
end;

procedure EmsSetPages; near; assembler;
asm
        CMP     EmsVersion,40H
        JAE     @@1
        MOV     AX,84H
        JMP     @@2
@@1:    MOV     DX,ES:[DI].TEmsStream.Handle
        MOV     BX,AX
        MOV     AH,51H
        INT     67H
        MOV     AL,AH
        AND     AX,0FFH
        JNE     @@2
        MOV     ES:[DI].TEmsStream.PageCount,BX
@@2:
end;

constructor TEmsStream.Init(MinSize, MaxSize: LongInt); {assembler;}
const EmsDeviceLen = 8;
      EmsDeviceStr: array[1..EmsDeviceLen] of Char = 'EMMXXXX0';
begin
  if MinSize=0 then MinSize:= 1;
  if MaxSize=0 then MaxSize:= 1;
  asm
        XOR     AX,AX
        PUSH    AX
        LES     DI,Self
        PUSH    ES
        PUSH    DI
        CALL    TStream.Init

        MOV     AX,3567H
        INT     21H
        MOV     CX,EmsDeviceLen
        MOV     SI,OFFSET EmsDeviceStr
        MOV     DI,0AH
        CLD
        REP     CMPSB
        LES     DI,Self
        MOV     AX,-1
        JNE     @@3

        MOV     AH,41H
        INT     67H
        MOV     EmsBaseSeg,BX
        MOV     AH,46H
        INT     67H
        MOV     EmsVersion,AL
        MOV     CX,EmsPageSize
        MOV     AX,MinSize.Word[0]
        MOV     DX,MinSize.Word[2]
        ADD     AX,EmsPageSize-1
        ADC     DX,0
        DIV     CX
        MOV     BX,AX
        CMP     EmsVersion,40H
        JAE     @@2

        PUSH    AX
        MOV     AX,MaxSize.Word[0]
        MOV     DX,MaxSize.Word[2]
        ADD     AX,EmsPageSize-1
        ADC     DX,0
        DIV     CX
        MOV     CX,AX
        MOV     AH,42H
        INT     67H
        POP     AX
        CMP     BX,CX
        JB      @@1

        MOV     BX,CX
@@1:    CMP     BX,AX
        JA      @@2

        MOV     BX,AX
@@2:    MOV     AH,43H
        INT     67H
        MOV     AL,AH
        AND     AX,0FFH
        JE      @@4

@@3:    MOV     DX,stInitError
        CALL    DoStreamError
        MOV     DX,-1
        XOR     BX,BX
@@4:    MOV     ES:[DI].TEmsStream.Handle,DX
        MOV     ES:[DI].TEmsStream.PageCount,BX
	XOR	AX,AX
	ADD	DI,OFFSET TEmsStream.Size
	MOV	CX,4
	REP	STOSW
  end;
  is:= Status=stOk
 {if Status=stInitError then RunError('Cannot initialize EMS stream.')}
end;

destructor TEmsStream.Done; assembler;
asm
        LES     DI,Self
        MOV     DX,ES:[DI].TEmsStream.Handle
        CMP     DX,-1
        JE      @@1
        MOV     AH,45H
        INT     67H
@@1:    XOR     AX,AX
        PUSH    AX
        PUSH    ES
        PUSH    DI
        CALL    TStream.Done
end;

function TEmsStream.GetPos: Longint; assembler;
asm
        LES     DI,Self
        CMP     ES:[DI].TEmsStream.Status,0
        JNE     @@1
        MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        JMP     @@2
@@1:    MOV     AX,-1
        CWD
@@2:
end;

function TEmsStream.GetSize: Longint; assembler;
asm
        LES     DI,Self
        CMP     ES:[DI].TEmsStream.Status,0
        JNE     @@1
        MOV     AX,ES:[DI].TEmsStream.Size.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Size.Word[2]
        JMP     @@2
@@1:    MOV     AX,-1
        CWD
@@2:
end;

procedure TEmsStream.Read(var Buf; Count: Word); assembler;
asm
        LES     DI,Self
        XOR     BX,BX
        CMP     BX,ES:[DI].TEmsStream.Status
        JNE     @@3
        MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        ADD     AX,Count
        ADC     DX,BX
        CMP     DX,ES:[DI].TEmsStream.Size.Word[2]
        JA      @@1
        JB      @@7
        CMP     AX,ES:[DI].TEmsStream.Size.Word[0]
        JBE     @@7
@@1:    XOR     AX,AX
        MOV     DX,stReadError
@@2:    CALL    DoStreamError
@@3:    LES     DI,Buf
        MOV     CX,Count
        XOR     AL,AL
        CLD
        REP     STOSB
        JMP     @@8
@@5:    PUSH    BX
        CALL    EmsSelectPage
        POP     BX
        JNE     @@2
        MOV     AX,Count
        SUB     AX,BX
        CMP     CX,AX
        JB      @@6
        MOV     CX,AX
@@6:    ADD     ES:[DI].TEmsStream.Position.Word[0],CX
        ADC     ES:[DI].TEmsStream.Position.Word[2],0
        PUSH    ES
        PUSH    DS
        PUSH    DI
        LES     DI,Buf
        ADD     DI,BX
        ADD     BX,CX
        MOV     DS,EmsBaseSeg
        CLD
        REP     MOVSB
        POP     DI
        POP     DS
        POP     ES
@@7:    CMP     BX,Count
        JB      @@5
@@8:
end;

procedure TEmsStream.Seek(Pos: Longint); assembler;
asm
        LES     DI,Self
        MOV     AX,Pos.Word[0]
        MOV     DX,Pos.Word[2]
        OR      DX,DX
        JNS     @@1
        XOR     AX,AX
        CWD
@@1:    MOV     ES:[DI].TEmsStream.Position.Word[0],AX
        MOV     ES:[DI].TEmsStream.Position.Word[2],DX
end;

procedure TEmsStream.Truncate; assembler;
asm
        LES     DI,Self
        XOR     BX,BX
        CMP     ES:[DI].TEmsStream.Status,BX
        JNE     @@2
        CMP     EmsVersion,40H
        JB      @@1
        MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        ADD     AX,EmsPageSize-1
        ADC     DX,BX
        MOV     CX,EmsPageSize
        DIV     CX
        CALL    EmsSetPages
        JE      @@1
        MOV     DX,stError
        CALL    DoStreamError
        JMP     @@2
@@1:    MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        MOV     ES:[DI].TEmsStream.Size.Word[0],AX
        MOV     ES:[DI].TEmsStream.Size.Word[2],DX
@@2:
end;

procedure TEmsStream.Write(var Buf; Count: Word); assembler;
asm
        LES     DI,Self
        XOR     BX,BX
        CMP     BX,ES:[DI].TEmsStream.Status
        JNE     @@7
        MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        ADD     AX,Count
        ADC     DX,BX
        ADD     AX,EmsPageSize-1
        ADC     DX,BX
        MOV     CX,EmsPageSize
        DIV     CX
        CMP     AX,ES:[DI].TEmsStream.PageCount
        JBE     @@4
        PUSH    BX
        CALL    EmsSetPages
        POP     BX
        JE      @@4
@@1:    MOV     DX,stWriteError
        CALL    DoStreamError
        JMP     @@7
@@2:    PUSH    BX
        CALL    EmsSelectPage
        POP     BX
        JNE     @@1
        MOV     AX,Count
        SUB     AX,BX
        CMP     CX,AX
        JB      @@3
        MOV     CX,AX
@@3:    ADD     ES:[DI].TEmsStream.Position.Word[0],CX
        ADC     ES:[DI].TEmsStream.Position.Word[2],0
        PUSH    ES
        PUSH    DS
        PUSH    DI
        MOV     DI,SI
        MOV     ES,EmsBaseSeg
        LDS     SI,Buf
        ADD     SI,BX
        ADD     BX,CX
        CLD
        REP     MOVSB
        POP     DI
        POP     DS
        POP     ES
@@4:    CMP     BX,Count
        JB      @@2
@@5:    MOV     AX,ES:[DI].TEmsStream.Position.Word[0]
        MOV     DX,ES:[DI].TEmsStream.Position.Word[2]
        CMP     DX,ES:[DI].TEmsStream.Size.Word[2]
        JB      @@7
        JA      @@6
        CMP     AX,ES:[DI].TEmsStream.Size.Word[0]
        JBE     @@7
@@6:    MOV     ES:[DI].TEmsStream.Size.Word[0],AX
        MOV     ES:[DI].TEmsStream.Size.Word[2],DX
@@7:
end;

end.