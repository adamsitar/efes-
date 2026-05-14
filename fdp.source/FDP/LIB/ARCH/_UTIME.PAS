unit _UTime; {Time support - UNIX-DOS conversions and tick counter}


INTERFACE

type

  DOS_date = record
               year  :word;
               month :word;
               day   :word;
             end;
  DOS_time = record
               hour  :word;
               min   :word;
               sec   :word;
             end;

  UNIX_time = LongInt;

  tick_time = LongInt;

const
  DefaultTimeZone : LongInt=5; {like in BC++ library}

var
  TimeZone : LongInt;

  TickCounter : LongInt;

function  dos2unix (d:DOS_date; t:DOS_time) : LongInt;
procedure unix2dos (ut:UNIX_time; var d:DOS_date; var t:DOS_time);

procedure SetTimeHandler;
procedure RestoreTimeHandler;


IMPLEMENTATION

uses
  Dos;

type

  tDays = array[0..11] of Integer;

const

  MonthDays:tDays = (31,28,31,30,31,30,31,31,30,31,30,31);

  TimerIntVect:Byte = $1C;

var
  OldTimeHandler : Procedure;

{*---------------------------------------------------------------------*

Name            dos2unix - converts date and time to UNIX time format

Usage           function dos2unix(d:DOS_date; t:DOS_time) : LongInt;

Description     Converts a date and time (as returned from getdate and
                gettime) into UNIX-format time.
                There is little difference between dos2unix and BC++ like
                dostounix functions - this pascal version doesn't test the TZ
                environment variable and ignores daylight saving correction

Return value    UNIX version of the given date and time.

*---------------------------------------------------------------------*}
function dos2unix(d:DOS_date; t:DOS_time) : LongInt;
var x : LongInt;
    i,days,hours : Integer;

begin
  {tzset();}                                {  get timezone info  }

  x := LongInt(3652) * LongInt(24) * LongInt(3600) + TimeZone;
                           {Convert from 1980 to 1970 base date GMT  }
  i := d.year - 1980;
  if i<0 then
    i:=i-4;
  x := x + (i div 4) * LongInt(1461) * LongInt(24) * LongInt(3600);
  x := x + (i and 3) * LongInt( 365) * LongInt(24) * LongInt(3600);
  if (i and 3)<>0 then
    x := x + 24 * 3600;
  days := 0;
  i := d.month - 1;                      {  Add in months  }
  while (i > 0) do
    begin
      Dec(i);
      days := days + MonthDays[i];
    end;
  days := days + d.day - 1;
  if (d.month > 2) and ((d.year and 3)=0) then
    Inc(days);                         {  Currently in leap year  }
  hours := days * 24 + t.hour;         {  Find hours  }
  {__isDST is not implememnted - see BC++ runtime libraries source code}
  {if daylight<>0  && __isDST( t.hour,days,0,d.year-1970)) then
    Dec(hours);}
  { ak ne Dec(hours) -> vypocita o hodinu vacsi cas }
   { Dec(hours);}
  x := x + hours * LongInt(3600);
  x := x + LongInt(60) * t.min + t.sec;
  dos2unix := x;
end;


{*---------------------------------------------------------------------*

Name            unix2dos - converts from UNIX-format time

Usage           procedure unix2dos(time:UNIX_time;
                                   var d:DOS_date; var t:DOS_time);

Description     Converts a UNIX-format time into date and time.
                There is little difference between dos2unix and BC++ like
                dostounix functions - this pascal version doesn't test the TZ
                environment variable and ignores daylight saving correction

*---------------------------------------------------------------------*}

procedure unix2dos(ut:UNIX_time; var d:DOS_date; var t:DOS_time);

begin
  {tzset();}                                   {get timezone info}
  ut := ut - (LongInt(3652) * 24 * 3600 + TimeZone);
  t.sec:= ut mod 60;
  ut := ut div 60;                             {Time in minutes}
  t.min:= ut mod 60;
  ut := ut div 60;                             {Time in hours}
  d.year := 1980 + Integer((ut div (1461*24)) *4);
  if ut<0 then
    begin
    d.year:=d.year-4;
    ut := 1461*24+ut mod (1461 * 24);
    end
  else
    ut := ut mod (1461 * 24);
  if ut >= 366 * 24 then
    begin
    ut := ut - 366 * 24;
    Inc(d.year);
    d.year := d.year + Integer(ut div (365 * 24));
    ut := ut mod (365 * 24);
    end;
  {__isDST is not implememnted - see BC++ runtime libraries source code}
  {if (daylight<>0 and __isDST(Integer(ut mod 24),Integer(ut div 24),0,d.year-1970 ))
     Inc(ut);}
  t.hour := ut mod 24;
  ut := ut div 24;                             {Time in days}
  Inc(ut);
  if ((d.year and 3)=0) then
    begin
    if ut > 60 then
      Dec(ut)
    else
    if ut = 60 then
      begin
      d.month := 2;
      d.day := 29;
      Exit;
      end;
    end;
  d.month := 0;
  while MonthDays[d.month] < ut do
    begin
    ut := ut - MonthDays[d.month];
    Inc(d.month);
    end;
  Inc(d.month);
  d.day := ut;
end;


procedure TimeHandler; interrupt;
begin
  Inc(TickCounter);
end;

procedure SetTimeHandler;
begin
  GetIntVec(TimerIntVect,@OldTimeHandler);
  SetIntVec(TimerIntVect,@TimeHandler);
end;

procedure RestoreTimeHandler;
begin
  SetIntVec(TimerIntVect,@OldTimeHandler);
end;


BEGIN
  TimeZone := DefaultTimeZone*3600; { Set for EST  }
  TickCounter := 0;
END.

