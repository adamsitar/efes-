unit Error;

INTERFACE

uses Types,Basic,File_IO;

const
  MaxErrors=25;            {error message table size}

const
  NoError=0;               {error message table indexes}
  FailedInit=1;
  FailedDone=2;
  OutOfMemory=3;
  GraphicsError=4;
  RangeCheck=5;
  NoCode=6;
  NoDriver=7;
  NoFind=8;
  NoFile=9;
  NoData=10;
  NoInit=11;
  BadData=12;
  DuplicateData=13;
  DataInUse=14;
  DataOverflow=15;
  BadOrder=16;
  BadFormat=17;
  BadAdress=18;
  NoSupport=19;
  FailedOperation=20;
  HardwareError=21;
  DiskFull=22;
  FileReadError=23;
  FileWriteError=24;

type
  MsgArray = array [0..MaxErrors-1] of String;
  MsgArrayPtr=^MsgArray;

const
  MessageTable :MsgArray =         {tabulka chybovych sprav}
       (
       'No error',
       'Initialization failed',
       'Destruction failed',
       'Out of memory',
       'Graphics error',
       'Range check error',
       'The program code is not implemented',
       'Driver not installed',
       'Value not found',
       'File not found or cannot open file',
       'No data exist to operate',
       'Variable or table was never or badly initialized',
       'Bad data recognized',
       'Duplicate data found',
       'Data already used',
       'Data space overflowed',
       'Data is not ordered correctly',
       'Data in bad format found',
       'Bad adress found',
       'Operation is not supported',
       'Last operation failed',
       'Hardware error',
       'Disk is full',
       'File read error',
       'File write error (disk full ?)'
       );


type
  error_manager=object

    ErrorNo :index;                {index najdenej chyby}
    Console :logic;                {OFF => vypisy sprav su potlacene}

    constructor Init;
    destructor  Done;

    function Serve(NewErrorNo:index) :result;{vrati OK, ak bola chyba rozpoznana}
    procedure Message(Text:string);           {vypise doplnkovy retazec Text}
    procedure Warning(Text:string);           {vypise Warning: Text}
    procedure FatalMessage(Text:string);
    end;

var
  EM :error_manager;

IMPLEMENTATION


{inicializacia systemu spracovania chyb}

var
  LogFile:Text;

{class error_manager}

constructor error_manager.Init;
begin
ErrorNo:=0;
SetHwErrHandler(@HwErrHandler);
Assign(LogFile,'error.log');
FileMode := 1;                     {Set file access to write only}
Rewrite(LogFile);
Append(LogFile);
if IOResult<>0 then
  begin
  Serve(DiskFull);
  Message(' in class error_manager');
  Halt;
  end;
end;

destructor error_manager.Done;
begin
Close(LogFile);
RestoreHwErrHandler;
end;

{vrati OK, ak bola chyba rozpoznana}

function error_manager.Serve(NewErrorNo:index) :result;
begin
if NewErrorNo>=MaxErrors then
  begin
  Serve:=ERR;
  Exit;
  end;
ErrorNo:=NewErrorNo;
Writeln(LogFile);
Write(LogFile,'Error ',ErrorNo,': ',MessageTable[ErrorNo]);
ErrorSound;
Serve:=OK;
end;


{vypise doplnkovy retazec Text}

procedure error_manager.Message(Text:string);
begin
Write(LogFile,Text);
end;


{vypise Warning: Text}

procedure error_manager.Warning(Text:string);
begin
Writeln(LogFile);
Message('Warning: ');
Message(Text);
end;

procedure error_manager.FatalMessage(Text:string);
begin
Message(Text);
Message(' - fatal');
Halt;
end;

var saveexit: pointer;

procedure done_EM;
    begin
      EM.Done;
      ExitProc:= SaveExit
    end;

BEGIN ??????????????
  saveexit:= exitproc;
{  exitproc:= @done_EM; }
  EM.Init;
END.