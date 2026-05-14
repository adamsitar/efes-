{$I comp.h}
{$A-,O-}

unit DAR_def;


interface

    uses  TypeDef, _Check,
          uTime, BIOS, DOS, IO,
          {$I unit_gr.h},
          NET_def
          ;


    const enDAR_ARCH       : bool = true;
          archive_DAR      : bool = true;

          writeln_DAR      : bool = true;
          writeln_DAR_utc  : bool = false;
          cl_DAR           : byte = clGR5;

          {$IFDEF DEBUG}
             DAR_buff_size : int = 30;
          {$ELSE}
             DAR_buff_size : int = 50;
          {$ENDIF}


    const posRLI_ARCH : byte = 0;



    type  record_data   = array[0..size_of_NETpkt-1] of byte;
          record_header = record
            Tick            : tick_time; { cas v tikoch od zaciatku nahravky }
            FromNode,ToNode : word;      { zdrojovy, cielovy uzol }
            DataLength      : word;      { dlzka packetu bez hlavicky }
          end;


    type  TDARpkt = record
            header : record_header;
            data   : record_data
          end;



    {  precita hlavicku z archivacneho suboru
    }
    function LoadFileHeader(var OutFile:file;
                            var StartTime:UNIX_time; var EndTime:UNIX_time
                           ) : Word;

    {  ulozi hlavicku do archivacneho suboru
       ak je StartNow=True
       pouzije aktualny systemovy cas ako zaciatok, koniec je o hodinu neskor
       StartTime,EndTime sa ignoruje)
       inak pouzije StartTime,EndTime
    }
    function SaveFileHeader(var OutFile:file; StartNow:Boolean;
                            StartTime:UNIX_time; EndTime:UNIX_time
                           ) : Word;

    function ReadFileHeader(var OutFile: file; var StartTime,EndTime: UNIX_time): Word;

    {
      precita zaznam z archivacneho suboru
    }
    function LoadRecord(var  InFile:file;
                        var Header: record_header; var Data: record_data
                       ) : Word;

    { ulozi zaznam do archivacneho suboru
      ak je SetRecordTime=True, nastavi Header.Time na aktualnu hodnotu TickCounter
      inak ulozi Header tak, ako je zadany
    }
    function SaveRecord(var OutFile:file; SetRecordTime:Boolean;
                        var Header:record_header; var Data:record_data) : Word;




implementation


function LoadFileHeader(var OutFile:file;
                        var StartTime:UNIX_time; var EndTime:UNIX_time) : Word;
var
  ReadBytes1,ReadBytes2 : Word;
begin
  BlockRead(OutFile,StartTime,SizeOf(UNIX_time),ReadBytes1);
  BlockRead(OutFile,  EndTime,SizeOf(UNIX_time),ReadBytes2);
  LoadFileHeader := ReadBytes1 + ReadBytes2;
end;


function SaveFileHeader(var OutFile:file; StartNow:Boolean;
                        StartTime: UNIX_time; EndTime: UNIX_time
                       ) : Word;
   var   Dummy,SavedBytes1,SavedBytes2 : Word;
         d : DOS_date;
         t : DOS_time;
         dt : TDatum;
   begin
     if StartNow then
        begin
          GetDatem(d.year,d.month,d.day,dummy);
          GetTimem(t.hour,t.min,t.sec);
          datum_init (dt, d.day,d.month,d.year, t.hour,t.min,t.sec);
          StartTime := dos2unix(dt)  { - 3600};
          EndTime   := StartTime;   { plus one hour }
          TickCounter:= 0;
        end
     else Seek(OutFile,0);
     BlockWrite(OutFile,StartTime,SizeOf(UNIX_time),SavedBytes1);
     BlockWrite(OutFile,EndTime,  SizeOf(UNIX_time),SavedBytes2);
     SaveFileHeader:= SavedBytes1 + SavedBytes2;
     Seek(OutFile,FileSize(OutFile))
   end;


function ReadFileHeader(var OutFile: file; var StartTime,EndTime: UNIX_time): Word;
var   Dummy,SavedBytes1,SavedBytes2 : Word;
begin
  Seek(OutFile,0);
  BlockRead(OutFile,StartTime,SizeOf(UNIX_time),SavedBytes1);
  BlockRead(OutFile,EndTime,  SizeOf(UNIX_time),SavedBytes2);
  ReadFileHeader := SavedBytes1 + SavedBytes2;
  Seek(OutFile,FileSize(OutFile))
end;



function LoadRecord(var  InFile:file;
                    var Header:record_header; var Data:record_data) : Word;
var
  ReadBytes1,ReadBytes2 : Word;
begin
  BlockRead(InFile,Header,SizeOf(record_header),ReadBytes1);
  BlockRead(InFile,Data  ,Header.DataLength    ,ReadBytes2);
  LoadRecord := ReadBytes1 + ReadBytes2;
end;


function SaveRecord(var OutFile:file; SetRecordTime:Boolean;
                    var Header:record_header; var Data:record_data
                   ) : Word;
var
  SavedBytes1,SavedBytes2 : Word;
begin
  if SetRecordTime then Header.Tick := TickCounter;
  ResetIOError;
  BlockWrite(OutFile,Header,SizeOf(record_header),SavedBytes1);
  BlockWrite(OutFile,Data  ,Header.DataLength    ,SavedBytes2);
  ResetIOError;
  SaveRecord := SavedBytes1 + SavedBytes2;
end;


end.