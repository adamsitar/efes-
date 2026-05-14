Unit File_IO;

{
   module for critical hardware error handling &
   common used file I/O functions

   Copyright (c) Rastislav B”hmer

   last change: Nov 17 1994

}

{$X+}

INTERFACE

uses Dos,Str0,Types,Basic;

{critical hardware error handling}

{call harderr(HwErrorHandler); to initialize (#include <dos.h> is needed)}

type
  hw_error = int;

  FilePtr = ^file;

  byteFile = file of byte;
  byteFilePtr = ^byteFile;


const
      WriteProtected=0;  {Attempt write to write-protected disk}
       UnknownUintId=1;  {Unknown unit ID}
       DriveNotReady=2;  {Disk drive not ready}
      UnknownComamnd=3;  {Unknown command}
         DiskDataCRC=4;  {Disk data error (CRC error)}
  BadStructureLength=5;  {Bad request structure length}
            DiskSeek=6;  {Disk seek error}
    UnknownDiskMedia=7;  {Unknown disk media type}
  DiskSectorNotFound=8;  {Disk sector not found}
   PrinterOutOfPaper=9;  {Printer out of paper}
          WriteFault=10; {Write fault error}
           ReadFault=11; {Read fault error}
      GeneralFailure=12; {General failure}
           NoHwError=32767;

{hardware error status bits}

const
  ReadHwErr  = $00;
  WriteHwErr = $01;

  HwErrAffectedArea = $06;
  HwErrSysFiles     = $00;
  HwErrFAT          = $02;
  HwErrDirectory    = $04;
  HwErrDataArea     = $06;

  HwErrAllowedFail   = $08;
  HwErrAllowedRetry  = $10;
  HwErrAllowedIgnore = $20;

  HwErrDeviceType    = $80;
  HwErrDiskDevice    = $00;
  HwErrNonDiskDevice = $01;

const
  HwErrIgnore=0;
  HwErrRetry =1;
  HwErrAbort =2;
  HwErrFail  =3;

var
  HwErrNo :hw_error;
  HwErrStatus :byte;
  HwErrDriveNo :byte;
  HwErrDeviceHeader :Pointer;

procedure SetHwErrHandler(NewHandler: Pointer);
procedure RestoreHwErrHandler;

procedure HwErrHandler(Flags, CS, IP, AX, BX, CX, DX, SI, DI,
                       DS, ES, BP:Word); interrupt;

{common used definitions}

const
  ActualFilePosition :ulong = $FFFFFFFF;

const
  WILDCARDS = $0001;
  EXTENSION = $0002;
  FILENAME  = $0004;
  DIRECTORY = $0008;
  DRIVE     = $0010;

  MAXPATH  = 80;
  MAXDRIVE =  3;
  MAXDIR   = 66;
  MAXFILE  =  9;
  MAXEXT   =  5;

type
  DriveStr = String[MAXDRIVE];
  DirStr   = String[MAXDIR  ];
  NameStr  = String[MAXFILE ];
  ExtStr   = String[MAXEXT  ];

  DriveStrPtr = ^DriveStr;
  DirStrPtr   = ^DirStr;
  NameStrPtr  = ^NameStr;
  ExtStrPtr   = ^ExtStr;

  NameExtStr = String[MAXFILE+MAXEXT];

  dfree = record
            df_avail,df_total,df_bsec,df_sclus :uint;
          end;

{common used functions}

function DriveNo(DriveChr :char) :int;

{
function  fnsplit(Path:String;
                  var driveP:DriveStrPtr; var dirP:DirStrPtr;
                  var nameP :NameStrPtr;  var extP:ExtStrPtr) :bit_mask;

procedure fnmerge(var Path:String;
                  driveP:DriveStrPtr; dirP:DirStrPtr;
                  nameP :NameStrPtr;  extP:ExtStrPtr);
}

function  fnsplit(Path:String;
                  driveP:DriveStrPtr; dirP:DirStrPtr;
                  nameP :NameStrPtr;  extP:ExtStrPtr) :bit_mask;

procedure fnmerge(var Path:String;
                  driveP:DriveStrPtr; dirP:DirStrPtr;
                  nameP :NameStrPtr;  extP:ExtStrPtr);

function getdfree(DriveNo:int; var DiskInfo:dfree) :result;

function RemovableMedia(DriveNo:int) :int;

IMPLEMENTATION

procedure HwErrHandler(Flags, CS, IP, AX, BX, CX, DX, SI, DI,
                       DS, ES, BP:Word);
begin
HwErrNo := DI;
HwErrStatus := AX shr 8;
HwErrDriveNo := (AX and $00FF)+1; {+1 to convert to default=0,A=1,B=2... format}
HwErrDeviceHeader := Ptr(BP,SI);
asm
  mov AL,HwErrIgnore;
end;
end;

var
  OldHwErrHandler :Pointer;

procedure SetHwErrHandler(NewHandler: Pointer);
begin
  GetIntVec($24,OldHwErrHandler);
  SetIntVec($24,Addr(HwErrHandler));
end;

procedure RestoreHwErrHandler;
begin
if OldHwErrHandler<>NULL then
  begin
  SetIntVec($24,OldHwErrHandler);
  OldHwErrHandler := NULL;
  end;
end;

function DriveNo(DriveChr :char) :int;
begin
  if DriveChr=#0 then
    DriveNo:=0
  else
    DriveNo:= Ord(DriveChr)-Ord('A')+1;
end;

{common used functions}

{---------------------------------------------------------------------

Name            fnsplit - splits a full path name into its components

Usage
                int fnsplit(const char *path, char * drive, char * dir,
                             char * name, char * ext);

                translated from C standard library

Description     fnsplit takes a file's full path name (path) as a string
                in the form

                        X:\DIR\SUBDIR\NAME.EXT

                and splits path into its four components. It then stores
                those components in the strings pointed to by drive, dir,
                name and ext. (Each component is required but can be a
                NULL, which means the corresponding component will be
                parsed but not stored.)

                The maximum sizes for these strings are given by the
                constants MAXDRIVE, MAXDIR, MAXPATH, MAXNAME and MAXEXT,
                (defined in dir.h) and each size includes space for the
                null-terminator.

                        Constant        (Max.)  String

                        MAXPATH         (80)    path
                        MAXDRIVE        (3)     drive; includes colon (:)
                        MAXDIR          (66)    dir; includes leading and
                                                trailing backslashes (\)
                        MAXFILE         (9)     name
                        MAXEXT          (5)     ext; includes leading dot (.)

                fnsplit assumes that there is enough space to store each
                non-NULL component. fnmerge assumes that there is enough
                space for the constructed path name. The maximum constructed
                length is MAXPATH.

                When fnsplit splits path, it treats the punctuation as
                follows:

                * drive keeps the colon attached (C:, A:, etc.)

                * dir keeps the leading and trailing backslashes
                  (\turboc\include\,\source\, etc.)

                * ext keeps the dot preceding the extension (.c, .exe, etc.)

                fnsplit and fnmerge are invertible; if you split a given path
                with fnsplit, then merge the resultant components with
                fnmerge, you end up with path.

Return value    fnsplit returns an integer (composed of five flags,
                defined in dir.h) indicating which of the full path name
                components were present in path; these flags and the components
                they represent are:

                        EXTENSION       an extension
                        FILENAME        a filename
                        DIRECTORY       a directory (and possibly
                                        sub-directories)
                        DRIVE           a drive specification (see dir.h)
                        WILDCARDS       wildcards (* or ? cards)

----------------------------------------------------------------------}

function  fnsplit(Path:String;
                  driveP:DriveStrPtr; dirP:DirStrPtr;
                  nameP :NameStrPtr;  extP:ExtStrPtr) :bit_mask;
var
  PathLen :size;
  NameIdx,DirStartIdx,DotIdx :index;
  Dots :uint;
  Ret :bit_mask;
begin
  if driveP<>nil then       {Set all strings to default value empty}
    begin driveP^:=''; driveP^[MAXDRIVE]:=#0 end;
  if dirP<>nil then
    begin dirP^  :=''; dirP^  [MAXDIR  ]:=#0 end;
  if nameP<>nil then
    begin nameP^ :=''; nameP^ [MAXFILE ]:=#0 end;
  if extP<>nil then
    begin extP^  :=''; extP^  [MAXEXT  ]:=#0 end;

    

  Ret:=0;
  PathLen:=Length(Path);

  if PathLen=0 then
    begin
    fnsplit:=0;
    Exit;
    end;

  {Split the filename and fill corresponding nonzero pointers}

  DirStartIdx:=1;
  if (IsAlpha(Path[1])=YES) and (Path[2]=':') then {drive exist}
    begin
    if driveP<>nil then
      driveP^:=Copy(Path,1,2);
    Ret := Ret or DRIVE;
    DirStartIdx:=DirStartIdx+2;
    end;

  DotIdx:=PathLen+1;
  NameIdx:=PathLen+1;
  while (NameIdx>DirStartIdx) and (Path[NameIdx-1]<>'\') do
    begin
    Dec(NameIdx);
    if Path[NameIdx]='.' then
      DotIdx:=NameIdx;
    end;
  if NameIdx=DotIdx then
    NameIdx:=PathLen+1;
  if NameIdx<PathLen+1 then {filename and/or extension exist}
    begin
      if DotIdx<PathLen+1 then {dot found}
        begin
        if extP<>nil then
          extP^:=Copy(Path,DotIdx,PathLen-DotIdx+1);
        Ret := Ret or EXTENSION;
        end;
      if DotIdx>NameIdx then   {name part exist}
        begin
        if nameP<>nil then
          nameP^:=Copy(Path,NameIdx,DotIdx-NameIdx);
        Ret := Ret or FILENAME;
        end;
    end;
  if DirStartIdx<NameIdx then
    begin
    if dirP<>nil then
      dirP^:=Copy(Path,DirStartIdx,NameIdx-DirStartIdx);
    if dirP^[NameIdx-DirStartIdx]<>'\' then
      dirP^:=dirP^+'\';
    Ret := Ret or DIRECTORY;
    end;
  fnsplit:=Ret;
end;



procedure fnmerge(var Path:String;
                  driveP:DriveStrPtr; dirP:DirStrPtr;
                  nameP :NameStrPtr;  extP:ExtStrPtr);
begin
  if (driveP<>NULL) and (Length(driveP^)<>0) then
    Path:=driveP^
  else
    Path:='';

  if (  dirP<>NULL) and (Length(  dirP^)<>0) then
    begin
    Path:=Path+  dirP^;{if ( *(pathP-1) != '\\' && *(pathP-1) != '/') *pathP++ = '\\';}
    if Path[Length(Path)]<>'\' then
      Path:=Path+'\';
    end;
  if ( nameP<>NULL) and (Length( nameP^)<>0) then
    Path:=Path+ nameP^;
  if (  extP<>NULL) and (Length(  extP^)<>0) then
    begin
    if extP^[1]<>'.' then
      Path:=Path+'.';
    Path:=Path+  extP^;
    end;
end;

function getdfree(DriveNo:int; var DiskInfo:dfree) :result;
var
  r :Registers;
  BX :word;
begin
  r.DL:=DriveNo;
  r.AH:=$36;
  Intr($21,r);
  if r.AX=$FFFF then
    getdfree:=ERR
  else                        {success}
    begin
    BX:=r.BX;                 {backup bx}
    DiskInfo.df_avail := BX;
    DiskInfo.df_total := r.DX;
    DiskInfo.df_sclus := r.AX;
    DiskInfo.df_bsec  := r.CX;
    getdfree:=OK;
    end;
end;

function RemovableMedia(DriveNo:int) :int;
var
  r :Registers;
begin
  r.BL:=DriveNo;
  r.AH:=$44;
  r.AL:=$08;
  Intr($21,r);
  if r.AX=$0F then
    RemovableMedia:=-1        {error - invalid drive number}
  else
    if r.AX=$00 then
      RemovableMedia:=1       {removable}
    else
      RemovableMedia:=0;      {non-removable}
end;

BEGIN
  OldHwErrHandler := NULL;
  HwErrNo := 0;
END.