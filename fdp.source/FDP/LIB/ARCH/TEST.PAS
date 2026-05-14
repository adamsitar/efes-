program test;

uses Crt,Dos,Time,LoadSave;


var
  d,d2 : DOS_date;
  t,t2 : DOS_time;
  ut : UNIX_time;

  InFile,OutFile : file;
  header : record_header;
  data : record_data;
  st,et : UNIX_time;

  ThisNetwork : Byte;
  EDD_Node : Byte;
  EDD_Address, ThisNetworkZeroAddress, ThisNetworkBroadcastAddress : Word;
  SaveStrip,SaveRLI : record_header;

BEGIN
  {Initialization}

  ThisNetwork := $01;
  EDD_Node := $09;
  EDD_Address := (ThisNetwork shl 8) or EDD_Node;
  ThisNetworkZeroAddress := (ThisNetwork shl 8) or $00;
  ThisNetworkBroadcastAddress := (ThisNetwork shl 8) or $FF;

  with SaveStrip do
    begin
      Tick := 0;
      FromNode := EDD_Address;
      ToNode   := ThisNetworkZeroAddress;
      DataLength := 0;
    end;
  with SaveRLI do
    begin
      Tick := 0;
      FromNode := ThisNetworkBroadcastAddress;
      ToNode   := ThisNetworkZeroAddress;
      DataLength := 0;
    end;

{!}  SetTimeHandler;

  {Opening files}

  Assign(InFile,'10202009.dar');  { Open input file }
  Reset(InFile,1);  { Record size = 1 }

  Assign(OutFile,'samefile.dar'); { Open output file }
  Rewrite(OutFile,1);  { Record size = 1 }

  {loading/saving records}

  LoadFileHeader(InFile,st,et);
  SaveFileHeader(OutFile,True,st,et); {save header with actual time}

  repeat
    LoadRecord(InFile,header,data);
    SaveRecord(OutFile,false,header,data); {save without change}
  until Eof(InFile);

  {test of RLI saving}
  {
  SaveRLI.DataLength:=0;
  SaveRecord(OutFile,false,SaveRLI,data);
  }

  Close(InFile);
  Close(OutFile);

  {testing uni2dos & dos2unix functions}
  {
  with d do
    begin
    year:=1970;
    month:=1;
    day:=1;
    end;
  with t do
    begin
    hour:=0;
    min:=0;
    sec:=0;
    end;
  ut := dos2unix(d,t);
  unix2dos(ut,d2,t2);
  }

  RestoreTimeHandler;
  writeln(TickCounter);
END.

