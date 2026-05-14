unit CopyMan;

{
    manager for creating and copying files at background
    translated from C++

    Copyright (c) R. B”hmer

    last change: Nov 18 1994

    restrictions: the destination must not be in same directory where
                  the source is if copying with multiple volume source
                  and destination due to conflict of source and destination
                  volume file names
                  copying to same removable media is not possible
                  source file in StartCopy must be valid existing file

}

INTERFACE

uses Dos,Str0,Types,Basic,Error,File_IO,Mem;

type
  copy_msg = (NoCopyMsg,NextSrcVolume,NextDstVolume,CopyErrorMsg);

const
  NextVolumeFollows = $0001;

const
  CopyWholeFile     = $0001;
  LateReplace       = $0002;
  SrcMultVolumes    = $0004;
  DstMultVolumes    = $0008;
  CopyStarted       = $0010;
  CopyActive        = $0020;
  MessageEntered    = $0040;
  MessageExited     = $0080;
  CopyError         = $8000;

const
  VolumeMagic :ulong = $F7CA4294;

  LeftSpace      = 1024;
  VolumeInfoSize =  256;
  UsedVolumeInfoSize = (uintSize+indexSize+bit_maskSize+(MAXEXT-1)*byteSize);
  EmptyVolumeInfoSize = VolumeInfoSize-UsedVolumeInfoSize-sizeof(VolumeMagic);

  CopyManagerVersion :uint=$0100;

type

  copy_manager = object

    CopyStatus :bit_mask;

    SrcFlags,DstFlags :bit_mask;

    SrcDrive,DstDrive :DriveStr;
    SrcDir,DstDir     :  DirStr;
    SrcName,DstName   : NameStr;
    SrcExt,DstExt     :  ExtStr;

    SrcTempName,DstTempName :NameExtStr;

    SrcFile,DstFile :FilePtr;
    SrcFileVar, DstFileVar :file;

    BufferSize :size;
    Buffer :Pointer;

    SrcVersion   :uint;
    SrcBlockPtr  :Pointer;
    SrcBlockSize,SrcDoneSize :long_size;

    SrcVolumeNo,DstVolumeNo :index;
    SrcVolumeStatus,DstVolumeStatus :bit_mask;
    SrcOriginalExt,DstOriginalExt :ExtStr;
    RealDstVolumeSize,WrittenVolumeSize :long_size;

    DstVolumeSize :long_size;

    EndOfCopy :logic;
    ReadBytes,WrittenBytes :int;

    LastMessage :copy_msg;

    constructor Init(aLateReplace:logic);
    destructor  Done;

    function Open(SrcFileName:String; DstPath:String;
                  MultVolumes:logic; aDstVolumeSize:long_size) :result;
    procedure CloseCopy;

    function OpenSrcVolume :int;
    function OpenDstVolume :int;

    function CloseSrcVolume :result;
    function CloseDstVolume :result;

    procedure AdjustDstVolumeSize;

    function StartFileCopy(WhichFile :String; DstPath :String;
                           MultVolumes:logic; aDstVolumeSize:long_size)
                           :result;

    function StartBlockCopy(DstPath :String;
                           MultVolumes:logic; aDstVolumeSize:long_size)
                           :result;

    function CopyBlock(From:FilePtr; Fromoffset:long; BlockSize:long_size)
                       :result;
    function SaveBlock(Block:Pointer; BlockSize:long_size) :result;

    function Refresh :int;

    function EndCopy :result;
    function Break :result;

    function StandardMessageText(Which:copy_msg;Parameter:index) :String; virtual;

    {User of COPY module must inherit from copy_manager and redefine the
     EnterMessage method
     the ExitMessage method must be called somewhere in user application
     after the message was confirmed by Enter or sommething like that}
    procedure EnterMessage(Which:copy_msg; Parameter:index); virtual;
    procedure ExitMessage;

    function SingleCopy(FileToCopy:string; DstPath :string;
                        DstMultVolumes:logic; aDstVolumeSize:long_size)
                       :result;

    procedure Error(ErrorNo:index);

    end;

IMPLEMENTATION

constructor copy_manager.Init(aLateReplace:logic);
begin
if aLateReplace=YES then
  CopyStatus:=LateReplace
else
  CopyStatus:=$0000;
Buffer:=NULL;
SrcFile:=NULL;
DstFile:=NULL;
EndOfCopy:=NO;
ReadBytes:=0; WrittenBytes:=0;
LastMessage:=NoCopyMsg;
end;

destructor copy_manager.Done;
begin
if IsSet(CopyStatus,CopyStarted)=YES then
  Break;
end;

{
CopyWholeFile: SrcFileName is source file name with (optional) path ,
               DstPath is destination path or file name with (optional) path
               whole source will be copied to destination in this mode
else           SrcFileName='', DstPath is destination file name with
               (optional) path
               blocks will be saved to destination file via CopyBlock or
               SaveBlock methods in this mode
}

function copy_manager.Open(SrcFileName:String; DstPath:String;
                           MultVolumes:logic; aDstVolumeSize:long_size)
                           :result;
const
  SrcClusterSize:size = 0;
  DstClusterSize:size = 0;
var
  DiskInfo :dfree;
  Result  :int;
begin
ToUpper(SrcFileName);
ToUpper(DstPath);
if MultVolumes=ON then
  CopyStatus:=DstMultVolumes
else
  CopyStatus:=$0000;
SrcVersion:=CopyManagerVersion;
SrcBlockPtr:=NULL;
DstVolumeSize:=aDstVolumeSize;
SrcVolumeNo:=0;
DstVolumeNo:=0;
SrcVolumeStatus:=$0000;
DstVolumeStatus:=$0000;
LastMessage:=NoCopyMsg;
SrcBlockPtr:=NULL;
ReadBytes:=0;

HwErrNo:=NoHwError;

if Length(SrcFileName)<>0 then     {CopyWholeFile mode}
  begin
  SetBit(CopyStatus,CopyWholeFile);

  SrcFlags := fnsplit(SrcFileName,@SrcDrive,@SrcDir,@SrcName,@SrcExt);
  DstFlags := fnsplit(    DstPath,@DstDrive,@DstDir,@DstName,@DstExt);

  if IsSet(SrcFlags,FILENAME)=NO then
    begin Error(BadData); Open:=ERR; Exit; end;
  if IsSet(DstFlags,FILENAME)=NO then
    begin
    DstName:=SrcName;
    DstExt :=SrcExt;
    SetBit(DstFlags,FILENAME or EXTENSION);
    end;
  end
else                               {block-mode}
  begin
  SrcFile:=NULL;
  SrcBlockSize:=0;

  SrcFlags:=0;
  DstFlags:=fnsplit(DstPath,@DstDrive,@DstDir,@DstName,@DstExt);

  if IsSet(DstFlags,FILENAME)=NO then             {if DST is not a file}
    begin Error(BadData); Open:=ERR; Exit; end;
  end;


if IsSet(SrcFlags or DstFlags,WILDCARDS)=YES then {wildcards not supported}
  begin Error(NoSupport); Open:=ERR; Exit; end;

if IsSet(CopyStatus,CopyWholeFile)=YES then       {CopyWholeFile mode}
  begin
  getdfree(DriveNo(SrcDrive[1]),DiskInfo);
  SrcClusterSize := DiskInfo.df_sclus*DiskInfo.df_bsec;
  end;
getdfree(DriveNo(DstDrive[1]),DiskInfo);
DstClusterSize := DiskInfo.df_sclus*DiskInfo.df_bsec;
if SrcClusterSize>DstClusterSize then
  BufferSize := SrcClusterSize
else
  BufferSize := DstClusterSize;

if (HwErrNo<>NoHwError) or (OpenSrcVolume=0) or (OpenDstVolume=0) then
  begin Open:=ERR; Exit; end;

Result:=OpenSrcVolume;
case Result of
  0: begin Open:=ERR; Exit; end;
  1: begin
     Result:=OpenDstVolume;
     if Result=0 then
       begin Open:=ERR; Exit; end;
     end
  end;

GetMem(Buffer,BufferSize); {StrNew !!!!!!!!!!!!!!!!!!!!!!}
if Buffer=NULL then
  begin Error(OutOfMemory); Open:=ERR; Exit; end;

Open:=OK;
end;

procedure copy_manager.CloseCopy;
begin
CloseSrcVolume;
CloseDstVolume;
ClearBit(CopyStatus,CopyStarted or CopyActive);
if(Buffer<>NULL) then
  begin
  FreeMem(Buffer,BufferSize);
  Buffer:=NULL;
  end;
end;

{
opens volume SrcVolumeNo, reads VolumeInfo

returns:  0 if error
          1 if O.K.
          2 if message was enterred
}

function copy_manager.OpenSrcVolume :int;
var
  SrcPath,TmpPath :String;
  SomeVolumeFound:logic;
  DirInfo :SearchRec;              {for FindFirst,FindNext}
  ReadInfoBytes,TmpReadInfoBytes :int;
  MagicNo :ulong;                  {for VolumeMagic testing}
  ExtNo,Ret :int;                  {for volume no got from extension}
  RealVolumeNo :index;
  TmpPtr :Pointer;
begin
if IsSet(CopyStatus,CopyWholeFile)=NO then
  begin                            {block-mode}
  SrcFile:=NULL;
  SrcBlockSize:=0;
  OpenSrcVolume:=1;
  Exit;
  end;

if SrcFile<>NULL then             {CopyWholeFile mode}
  begin OpenSrcVolume:=0; Exit; end;

if ( (IsSet(CopyStatus,MessageExited)=NO) or (LastMessage<>NextSrcVolume)) and
   (RemovableMedia(DriveNo(SrcDrive[1]))=1) then {removable media}
  begin
  EnterMessage(NextSrcVolume,SrcVolumeNo);
  OpenSrcVolume:=2; Exit;
  end;

Inc(SrcVolumeNo);

SrcVolumeStatus:=$0000;
if SrcVolumeNo=1 then
  SrcOriginalExt:=SrcExt;
if SrcVolumeNo>1 then
  begin
  SrcExt:='.v  ';
  SrcExt[3]:= Chr( (SrcVolumeNo div 10) mod 10 + Ord('0') );
  SrcExt[4]:= Chr( SrcVolumeNo mod 10 + Ord('0') );
  end;

SrcTempName:='SRC_XXXX.XXX';
fnmerge(SrcPath,@SrcDrive,@SrcDir,@SrcName,@SrcExt);
fnmerge(TmpPath,@DstDrive,@DstDir,NULL,NULL);
TmpPath:=TmpPath+SrcTempName;

SrcFile:=@SrcFileVar;
Assign(SrcFile^,SrcPath);
Rename(SrcFile^,TmpPath);

FileMode := 0;  {Set file access to read only}
{$I-}
Reset(SrcFile^,1);
{$I+}
if IOResult<>0 then
  SrcFile:=NULL;

if SrcFile=NULL then
  begin
  SomeVolumeFound:=NO;
  if (HwErrNo=NoHwError) and (SrcVolumeNo+1>1) then
    begin
    SrcPath:=Copy(SrcPath,1,Length(SrcPath)-2)+'*';
    FindFirst(SrcPath,0,DirInfo);
    if DosError=0 then
      SomeVolumeFound:=YES;
    end;
  if SomeVolumeFound=YES then
    Error(BadOrder)
  else
    Error(NoFile);
  OpenSrcVolume:=0;
  Exit;
  end;
SrcBlockSize:=FileSize(SrcFile^);
SrcDoneSize:=0;

Dec(SrcVolumeNo);                  {testing VolumeMagic, reading volume info}
Val(Copy(SrcExt,3,2),ExtNo,Ret);
if (SrcVolumeNo>0) or ((Copy(SrcExt,1,2)='.v') and (Ret=0) and (ExtNo>0)) then
  begin
  Seek(SrcFile^,FileSize(SrcFile^)-ulongSize);

  ReadInfoBytes:=0;
  BlockRead(SrcFile^,MagicNo,ulongSize,ReadInfoBytes);
  if ReadInfoBytes<>ulongSize then
    begin Error(FileReadError); OpenSrcVolume:=0; Exit; end;

  ReadInfoBytes:=0; TmpReadInfoBytes:=0;
  if MagicNo=VolumeMagic then
    begin
    Inc(SrcVolumeNo);              {volume recognized}
    Seek(SrcFile^,FileSize(SrcFile^)-long(VolumeInfoSize));

    BlockRead(SrcFile^,SrcVersion,uintSize,TmpReadInfoBytes);
    ReadInfoBytes:=ReadInfoBytes+TmpReadInfoBytes;

    BlockRead(SrcFile^,RealVolumeNo,indexSize,TmpReadInfoBytes);
    ReadInfoBytes:=ReadInfoBytes+TmpReadInfoBytes;

    BlockRead(SrcFile^,SrcVolumeStatus,bit_maskSize,TmpReadInfoBytes);
    ReadInfoBytes:=ReadInfoBytes+TmpReadInfoBytes;

    TmpPtr:=@SrcOriginalExt;
    IncPtr(TmpPtr,1);
    BlockRead(SrcFile^,TmpPtr^,MAXEXT-1,TmpReadInfoBytes);
    ReadInfoBytes:=ReadInfoBytes+TmpReadInfoBytes;
    SrcOriginalExt:='.'+SrcOriginalExt;

    if ReadInfoBytes<>UsedVolumeInfoSize then
      begin Error(FileReadError); OpenSrcVolume:=0; Exit; end;
    if RealVolumeNo<>SrcVolumeNo then
      begin Error(BadOrder); OpenSrcVolume:=0; Exit; end;

    SrcBlockSize:=SrcBlockSize-VolumeInfoSize;
    if SrcVolumeNo=1 then
      begin
      DstName:=SrcName;
      DstExt:=SrcOriginalExt;
      end;
    end;
  Seek(SrcFile^,0);                 {from file begin}
  end;

if (MagicNo<>VolumeMagic) and (SrcVolumeNo>0) then
  begin Error(BadFormat); OpenSrcVolume:=0; end
else
  OpenSrcVolume:=1;
end;

{closes source volume}

function copy_manager.CloseSrcVolume :result;
var
  HwErrOnSrc :Boolean;
  SrcPath :String;
begin
HwErrOnSrc:=(HwErrNo<>NoHwError) and (HwErrDriveNo=DriveNo(SrcDrive[1]));
{I-}
if (not HwErrOnSrc) and
   (SrcFile<>NULL) and (IsSet(CopyStatus,CopyWholeFile)=YES) then
  Close(SrcFile^);
{I+}
SrcFile:=NULL;
SrcBlockPtr:=NULL;
SrcBlockSize:=0;

fnmerge(SrcPath,@SrcDrive,@SrcDir,@SrcName,@SrcExt);
Rename(SrcFile^,SrcPath);

if HwErrOnSrc then
  CloseSrcVolume:=ERR
else
  CloseSrcVolume:=OK;
end;

{
opens volume DstVolumeNo

returns:  0 if error
          1 if O.K.
          2 if message was enterred
}

function copy_manager.OpenDstVolume :int;
var
  TmpPath :String;
begin
if ( (IsSet(CopyStatus,MessageExited)=NO) or (LastMessage<>NextDstVolume)) and
   (RemovableMedia(DriveNo(DstDrive[1]))=1) then  {removable media}
  begin
  EnterMessage(NextDstVolume,DstVolumeNo);
  OpenDstVolume:=2; Exit;
  end;

Inc(DstVolumeNo);

if DstVolumeNo=1 then
  DstOriginalExt:=DstExt;

if IsSet(CopyStatus,DstMultVolumes)=YES then
  begin
  if DstVolumeNo=1 then
    SetBit(DstVolumeStatus,NextVolumeFollows);
  DstExt:='.v  ';
  DstExt[3]:= Chr( (DstVolumeNo div 10) mod 10 + Ord('0') );
  DstExt[4]:= Chr( DstVolumeNo mod 10 + Ord('0') );
  end;

AdjustDstVolumeSize;
if RealDstVolumeSize<DstVolumeSize div 10 then
  begin Error(DiskFull); OpenDstVolume:=0; Exit; end;

WrittenVolumeSize:=0;

DstFile:=@DstFileVar;

if (DstVolumeNo=1) and (IsSet(CopyStatus,DstMultVolumes)=NO) and
   (IsSet(CopyStatus,LateReplace)=NO) then
  begin
  fnmerge(TmpPath,@DstDrive,@DstDir,@DstName,@DstExt);
  Assign(DstFile^,TmpPath);
  Erase(DstFile^);
  end;

DstTempName:='DST_XXXX.XXX';
fnmerge(TmpPath,@DstDrive,@DstDir,NULL,NULL);
TmpPath:=TmpPath+DstTempName;

Assign(DstFile^,TmpPath);          {temporrary file}
FileMode := 1;                     {Set file access to write only}
{$I-}
Rewrite(DstFile^,1);
{$I+}
if IOResult<>0 then                {open file error}
  begin Error(NoFile); OpenDstVolume:=0; end
else
  OpenDstVolume:=1;
end;


function copy_manager.CloseDstVolume :result;
type
  empty_info = array [1..EmptyVolumeInfoSize] of Byte;
  empty_infoFile = file of empty_info;
var
  WrittenInfoBytes,TmpWrittenBytes :int;
  Tmp :ExtStr;
  TmpPtr :Pointer;
  EmptyInfo :empty_info;
  TmpPath,DstPath :String;
  TmpDstF :file;
  HwErrOnDst :Boolean;
begin
if DstFile=NULL then
  begin CloseDstVolume:=OK; Exit; end;

if (HwErrNo<>NoHwError) and (HwErrDriveNo=DriveNo(DstDrive[1])) then
  CloseDstVolume:=ERR
else
  begin
  if IsSet(CopyStatus,DstMultVolumes)=YES then
    begin
    WrittenInfoBytes:=0;
    BlockWrite(DstFile^,CopyManagerVersion,uintSize,TmpWrittenBytes);
    WrittenInfoBytes:=WrittenInfoBytes+TmpWrittenBytes;

    BlockWrite(DstFile^,DstVolumeNo,indexSize,TmpWrittenBytes);
    WrittenInfoBytes:=WrittenInfoBytes+TmpWrittenBytes;

    BlockWrite(DstFile^,DstVolumeStatus,bit_maskSize,TmpWrittenBytes);
    WrittenInfoBytes:=WrittenInfoBytes+TmpWrittenBytes;

    TmpPtr:=@Tmp;
    StrPCopy(TmpPtr,DstOriginalExt);
    IncPtr(TmpPtr,1);
    {Tmp:=Copy(DstOriginalExt,2,MAXEXT-2)+#0;
    TmpPtr:=@Tmp;
    IncPtr(TmpPtr,1);}

    BlockWrite(DstFile^,TmpPtr^,MAXEXT-1,TmpWrittenBytes);
    WrittenInfoBytes:=WrittenInfoBytes+TmpWrittenBytes;

    FillChar(EmptyInfo,EmptyVolumeInfoSize,0);
    BlockWrite(DstFile^,EmptyInfo,EmptyVolumeInfoSize,TmpWrittenBytes);
    WrittenInfoBytes:=WrittenInfoBytes+TmpWrittenBytes;

    BlockWrite(DstFile^,VolumeMagic,ulongSize,TmpWrittenBytes);
    WrittenInfoBytes:=WrittenInfoBytes+TmpWrittenBytes;

    if WrittenInfoBytes<>VolumeInfoSize then
      begin Error(FileWriteError); CloseDstVolume:=ERR; Exit; end;
    end;
  {I-}
  Close(DstFile^);
  {I+}
  if IOResult<>0 then
    begin
    CloseDstVolume:=ERR; Exit;
    end;

  fnmerge(TmpPath,@DstDrive,@DstDir,@DstTempName,NULL);
  fnmerge(DstPath,@DstDrive,@DstDir,@DstName,@DstExt);

  Assign(TmpDstF,DstPath);
  {$I-}
  Erase(TmpDstF);
  {$I+}
  if IOResult<>0 then begin end;
  Rename(DstFile^,DstPath);
  CloseDstVolume:=OK;
  end;
DstFile:=NULL;
end;

{allignes DstVolumeSize according to free space on destination drive}

procedure copy_manager.AdjustDstVolumeSize;
var
  DiskInfo :dfree;
  ClusterSize :size;
  MaxVolumeSIze :long_size;
begin
getdfree(DriveNo(DstDrive[1]),DiskInfo);
ClusterSize:=DiskInfo.df_sclus*DiskInfo.df_bsec;
MaxVolumeSize:=DiskInfo.df_avail*long_size(ClusterSize);
if (HwErrNo<>NoHwError) or (MaxVolumeSize<=LeftSpace) then{long_size == ulong}
  MaxVolumeSize:=0
else
  MaxVolumeSize:=MaxVolumeSize-LeftSpace;
if DstVolumeNo>0 then
  if MaxVolumeSize<DstVolumeSize then
    RealDstVolumeSize := MaxVolumeSize
  else
    RealDstVolumeSize := DstVolumeSize
else
  RealDstVolumeSize := MaxVolumeSize;
end;


{starts copying whole source file to destination path}

function copy_manager.StartFileCopy(WhichFile :String; DstPath :String;
                       MultVolumes:logic; aDstVolumeSize:long_size)
                       :result;
begin
if (WhichFile='') or (IsSet(CopyStatus,CopyStarted)=YES) then
  begin StartFileCopy:=ERR; Exit; end;
if Open(WhichFile,DstPath,MultVolumes,aDstVolumeSize)=ERR then
  StartFileCopy:=ERR
else
  begin
  SetBit(CopyStatus,CopyStarted or CopyActive);
  StartFileCopy:=OK;
  end;
end;


{starts creating destination file, prepares everything needed
 to enable CopyBlock & SaveBlock operations}

function copy_manager.StartBlockCopy(DstPath :String;
                       MultVolumes:logic; aDstVolumeSize:long_size)
                       :result;
begin
if IsSet(CopyStatus,CopyStarted)=YES then
  begin StartBlockCopy:=ERR; Exit; end;
if Open('',DstPath,MultVolumes,aDstVolumeSize)=ERR then
  StartBlockCopy:=ERR
else
  begin
  SetBit(CopyStatus,CopyStarted);
  StartBlockCopy:=OK;
  end;
end;


{starts copying block from specified offset in file
does nothing while CopyActive bit is set in CopyStatus}

function copy_manager.CopyBlock(From:FilePtr; Fromoffset:long; BlockSize:long_size)
                   :result;
begin
if (IsSet(CopyStatus,CopyStarted)=NO) or (IsSet(CopyStatus,CopyActive)=YES) then
  begin CopyBlock:=ERR; Exit; end;
SrcFile:=From;
Seek(SrcFile^,FromOffset);
SrcBlockPtr:=NULL;
SrcBlockSize:=BlockSize;
SrcDoneSize:=0;
SetBit(CopyStatus,CopyActive);     {activates file block copying}
CopyBlock:=OK;
end;

{starts saving block from specified area in memory
does nothing while CopyActive bit is set in CopyStatus}

function copy_manager.SaveBlock(Block:Pointer; BlockSize:long_size) :result;
begin
if (IsSet(CopyStatus,CopyStarted)=NO) or (IsSet(CopyStatus,CopyActive)=YES) then
  begin SaveBlock:=ERR; Exit; end;
SrcFile:=NULL;
SrcBlockPtr:=Block;
SrcBlockSize:=BlockSize;
SrcDoneSize:=0;
SetBit(CopyStatus,CopyActive);     {activates memory block copying}
SaveBlock:=OK;
end;

{ret: 1   if everything was O.K.
      0   if any error occured
     -1   if end of source file was reached in CopyWholeFile mode
}

function copy_manager.Refresh :int;
var
  BytesToRead,BytesToWrite :size;
  ActSrcPtr,ActDstPtr :Pointer;
  RestOfVolume :long_size;
  LastVolume :bool;
begin
if IsSet(CopyStatus,CopyStarted or CopyActive)=YES then
  if IsSet(CopyStatus,MessageExited)=YES then
    case LastMessage of            {start of passive part - waiting loop}
      NextSrcVolume:
        begin
        if OpenSrcVolume=0 then
          begin Refresh:=0; Exit; end;
        ClearBit(CopyStatus,MessageExited);
        if DstFile=NULL then       {OpenDstFile was not called in Open}
          begin Refresh:=OpenDstVolume; Exit; end;
        end;
      NextDstVolume:
        begin
        if OpenDstVolume=0 then
          begin Refresh:=0; Exit; end;
        ClearBit(CopyStatus,MessageExited);
        end;
      end                          {end of passive part - waiting loop}
  else
    begin                          {start of active part - copy loop}
    if IsSet(CopyStatus,MessageEntered)=YES then   {waiting for ExitMessage}
      begin Refresh:=1; Exit; end;

    EndOfCopy:=NO;

    if ReadBytes=0 then
      begin
      if SrcDoneSize<SrcBlockSize then
        begin
        if SrcBlockSize-SrcDoneSize<BufferSize then
          BytesToRead:=SrcBlockSize-SrcDoneSize
        else
          BytesToRead:=BufferSize;
        if SrcFile<>NULL then
          begin
          BlockRead(SrcFile^,Buffer^,BytesToRead,ReadBytes);
          if ReadBytes<>BytesToRead then
            begin Error(FileReadError); Refresh:=0; Exit; end;
          end
        else
          begin
          ReadBytes:=BytesToRead;
          ActSrcPtr:=SrcBlockPtr;
          IncPtr(ActSrcPtr,SrcDoneSize);
          Move(ActSrcPtr^,Buffer^,ReadBytes);
          end;
        SrcDoneSize:=SrcDoneSize+ReadBytes;
        end;

      if ((SrcFile<>NULL) and eof(SrcFile^)) or (SrcDoneSize=SrcBlockSize) then
        begin
        if CloseSrcVolume=ERR then
          begin Refresh:=0; Exit; end;
        if IsSet(CopyStatus,CopyWholeFile)=YES then
          if (SrcVolumeNo>0) and ((SrcVolumeStatus and NextVolumeFollows)<>0) then
            case OpenSrcVolume of
              2: begin Refresh:=1; Exit; end;
              0: begin Refresh:=0; Exit; end;
            end
          else
            EndOfCopy:=YES
        else
          ClearBit(CopyStatus,CopyActive);
        end;
      end;

    BytesToWrite:=ReadBytes;
    RestOfVolume:=RealDstVolumeSize-VolumeInfoSize-WrittenVolumeSize;
    if (DstVolumeNo>0) and (RestOfVolume<BytesToWrite) then
      BytesToWrite:=size(RestOfVolume);
    BlockWrite(DstFile^,Buffer^,BytesToWrite,WrittenBytes);
    if (WrittenBytes<>BytesToWrite) or (HwErrNo<>NoHwError) then
      begin Error(FileWriteError); Refresh:=0; Exit; end;
    WrittenVolumeSize:=WrittenVolumeSize+WrittenBytes;

    if(WrittenBytes<ReadBytes) then{prepare to write the rest of Buffer}
      begin
      ActDstPtr:=Buffer; IncPtr(ActDstPtr,WrittenBytes);
      ReadBytes:=ReadBytes-WrittenBytes;
      Move(ActDstPtr,Buffer,ReadBytes);
      end
    else
      ReadBytes:=0;

    if IsSet(CopyStatus,DstMultVolumes)=YES then
      if WrittenVolumeSize+VolumeInfoSize=RealDstVolumeSize then
        begin                      {close this, open next volume}
        LastVolume:=(EndOfCopy=YES) and (WrittenBytes=ReadBytes);
        if LastVolume then
          ClearBit(DstVolumeStatus,NextVolumeFollows);
        if CloseDstVolume=ERR then
          begin Refresh:=0; Exit; end;
        if not LastVolume then
          case OpenDstVolume of
            2: begin Refresh:=1; Exit; end;
            0: begin Refresh:=0; Exit; end;
          end;
        end;

    if HwErrNo<>NoHwError then     {test for hardware error}
      begin Error(HardwareError); Refresh:=0; Exit; end;

    if EndOfCopy=YES then
      begin
      ClearBit(DstVolumeStatus,NextVolumeFollows);
      CloseCopy;
      Refresh:=-1; Exit;
      end;
    end;                           {end of active part - copy loop}
Refresh:=1;
end;


{finishes creating new file in block-mode and closes copying
 does nothing while CopyActive bit is set in CopyStatus}

function copy_manager.EndCopy :result;
begin
if IsSet(CopyStatus,CopyActive)=YES then
  EndCopy:=ERR
else
  begin
  ClearBit(DstVolumeStatus,NextVolumeFollows);
  CloseCopy;
  EndCopy:=OK;
  end;
end;

function copy_manager.Break :result;
var
  DstPath :String;
begin
CloseCopy;
if (HwErrNo<>NoHwError) and (HwErrDriveNo=DriveNo(DstDrive[1])) then
  begin Break:=OK; Exit; end;      {hardware error occured on DstDrive}

fnmerge(DstPath,@DstDrive,@DstDir,@DstName,@DstExt);
Assign(DstFileVar,DstPath);
{$I-}
Erase(DstFileVar);
{$I+}
if IOResult<>0 then begin end;
Break:=OK;
end;


{method returns standard text for copy-message Which}

function copy_manager.StandardMessageText(Which:copy_msg;Parameter:index)
                                                                      :String;
var
  MsgText:String;
begin
StandardMessageText:='';
case Which of
  NextSrcVolume,NextDstVolume:
    begin
    if Which=NextSrcVolume then
      MsgText:='Insert media with source volume'
    else
      MsgText:='Insert media with destination volume';
    if Parameter<>0 then
      MsgText:=MsgText+ ' #'+Chr( (Parameter div 10) mod 10 + Ord('0') );
      MsgText:=MsgText+ Chr( Parameter mod 10 + Ord('0') );
    StandardMessageText:=MsgText;
    end;
  CopyErrorMsg:
    case Parameter of
      HardwareError:
        if (HwErrStatus and HwErrDeviceType)=HwErrDiskDevice then
          case HwErrNo of
            WriteProtected:
              StandardMessageText:='Drive is write-protected';
            DriveNotReady:
              StandardMessageText:='Drive not ready';
            WriteFault:
              StandardMessageText:='Read fault error';
            ReadFault:
              StandardMessageText:='Read fault error';
            else  {DiskDataCRC,DiskSeek,UnknownDiskMedia,DiskSectorNotFound,}
              StandardMessageText:='Drive error'; {GeneralFailure and others}
          end;
      BadFormat:
        StandardMessageText:='Bad volume file found';
      BadOrder:
        StandardMessageText:='Inproper order of source volumes';
      FileReadError:
        StandardMessageText:='Read file error';
      FileWriteError:
        StandardMessageText:='Write file error';
      DiskFull:
        StandardMessageText:='Destination disk is full';
    end;
  end;
end;

{
the simplest way to serve message enter

This example of EnterMessage calls ExitMessage immediately after the message
was typed to stdout and some key was pressed. This approach is not suitable
for event driven system. The ExitMessage is typically called somewhere in user
application outside of copy manager
}

procedure copy_manager.EnterMessage(Which:copy_msg; Parameter:index);
begin
{prolog - 4 necessarry lines}
if Which=NoCopyMsg then
  Exit;
SetBit(CopyStatus,MessageEntered);
LastMessage:=Which;

{user action using StandardMessageText service}
Writeln;
Write(StandardMessageText(Which,Parameter));

{waiting for confirmation & exit message mode to continue copying}
Readln;      {this need not be done right now inside EnterMessage !}
ExitMessage; {it may be called anywhere and anytime after the}
end;         {EnterMessage method ended}

procedure copy_manager.ExitMessage;
begin
ClearBit(CopyStatus,MessageEntered);
SetBit(CopyStatus,MessageExited);
end;


function copy_manager.SingleCopy(FileToCopy:string; DstPath :string;
                    DstMultVolumes:logic; aDstVolumeSize:long_size)
                   :result;
begin
StartFileCopy(FileToCopy,DstPath,DstMultVolumes,aDstVolumeSize);
while Refresh<>-1 do begin end;
if IsSet(CopyStatus,CopyError)=YES then
  SingleCopy:=ERR
else
  SingleCopy:=OK;
end;

procedure copy_manager.Error(ErrorNo:index);
var
  ErrVal:index;
begin
SetBit(CopyStatus,CopyError);
if (ErrorNo=NoFile) and (HwErrNo<>NoHwError) then
  ErrVal:=HardwareError
else
  ErrVal:=ErrorNo;

case ErrVal of
  NoFile,BadData,NoSupport,OutOfMemory:
    begin
    EM.Serve(ErrorNo);
    EM.Message(' in class copy_manager');
    end;
  HardwareError,      {some Mongol did not insert the diskette or
                       took the diskette out while copy_manager was active or
                       the diskette is wrong or
                       the hardware says 'Go and fuck yourself'}
  BadFormat, BadOrder, FileReadError, FileWriteError, DiskFull:
    begin
    if HwErrNo=NoHwError then
      EnterMessage(CopyErrorMsg,ErrorNo)
    else
      EnterMessage(CopyErrorMsg,HardwareError);
    end
  end;
Break;
end;


BEGIN
END.