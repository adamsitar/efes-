(*-------------------------------------------------------------------*)
(* BIOS                                                              *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$R- }                         { funkcie pre kontrolu casu su volane v intr }


unit BIOS;


interface


     uses  TypeDef;


     const secDAY  = 24*60*60;
           secHOUR = 60*60;
           secMIN  = 60;

           TIMER_PERIOD = High(word);
           ZVUK : bool {$IFNDEF NO_SOUND} = true {$ELSE} = false {$ENDIF};
           _486 : byte  = 1;


     var   Year,Month,Day, hour,min,sec,den   : word;
           absTime  : real;

     const absTime_ : bool = true;  { indikuje, ze som prestavil cas }

     var   novyDatum    : TDatum;
     const nastavDatum  : bool = false; { indikuje, ze sa ma nastavit cas podla nizsie uvedenych premennych }

           ZMENIL_SA_CAS      : bool = false; { o 1 min }
           ZMENIL_SA_CAS_SPAT : bool = false;


     const _1990 : array[1..12] of byte = (31,28,31,30,31,30,31,31,30,31,30,31);
           _Rok0 = 1990;


     const DefaultTimeZone : long = 5; {like in BC++ library}
     var   TimeZone        : long;


     const ProgramError  : bool = false;
           {MIN_HEAP_SIZE = $11000;  kB }



     procedure GetTimem(var h,m,s: word);
     procedure GetDatem(var r,m,d {$IFNDEF CMOS_TIME}, den {$ENDIF}: word);

     procedure SetTimem(h,m,s: word);
     procedure SetDatem(r,m,d: word);


     function  _29_2__(_year: word): bool;
     procedure _19__(_Year: word); { uz by to islo i sikovnejsie spravit, ale nemame cas }
     function  dni_mesiaca(rok,mes: word): byte;

     function  CheckTime(hour,min,sec: byte): bool;
     function  CheckDate(_year,_month,_day: word; _forward: bool): bool;

     procedure PrevDateH  (var _year: word; var _month, _day,_hour: byte);
     procedure PrevDate   (var _year: word; var _month, _day: byte);
     procedure NextDate   (var _year: word; var _month, _day: byte);
     procedure MilleniumDate (var y: word);

     function  DTtoSec(_Year,_Month,_Day, _hour,_min,_sec: real): real;
     function  DatumToSec(D: TDatum): real;
     function  DateToSec(_Year,_Month,_Day: real): real;
     function  TimeToSec(hour,min,sec: real): real;
     function  TimeFromSec (t: real; var h,m,s: byte): int;

     function  dos2unix (dt: TDatum): UNIX_time;
     procedure unix2dos (ut: UNIX_time; var dt:TDatum);


     function  GetTicks: tick_counter;
     function  _TimeOut(start, tick, periode, loops: real): bool;
     function  TimeOut (start, tick, loops: tick_counter): bool;
     function  TimeOutSec (start_sec, sec, delay: real): bool;
     function  WaitForEvent (loops: long; Podmienka: TBfunc; Proc: TProc): bool;
     procedure Wait (loops: long; Proc: TProc);
    {procedure Delay(MS: Word);}

     function  InGraphMode: bool;
     procedure Beep(Hz,Time: word);

     function  is_ParamStr(tit: string): string;



implementation

   { casovac
     procedure InitTimer;
     procedure DoneTimer;
     procedure TimerHandler; interrupt;
     function  TimerInstalled: bool;
   }

uses  Dos, Crt {$IFDEF SPEA}, SPEA {$ENDIF}, math;


{ ------------------------------------------------------------------
   Hodiny
  ------------------------------------------------------------------ }
{$IFDEF CMOS_TIME}

   Procedure GetTimem(var h,m,s: word);
     Var   PByte,PByte1,PByte2: Byte;
           _h,_m,_s: word;
     Begin
       Asm
         cli
         mov al,$00
         out $70,al
         jmp @a
   @a:   jmp @b
   @b:   jmp @c
   @c:   in  al,$71
         mov [PByte],al
         mov al,$02
         out $70,al
         jmp @d
   @d:   jmp @e
   @e:   jmp @f
   @f:   in  al,$71
         mov [PByte1],al
         mov al,$04
         out $70,al
         jmp @g
   @g:   jmp @h
   @h:   jmp @i
   @i:   in  al,$71
         mov [PByte2],al
         sti
       End;
       _s:= (PByte  and $0f)+(PByte  shr 4)*10;
       _m:= (PByte1 and $0f)+(PByte1 shr 4)*10;
       _h:= (PByte2 and $0f)+(PByte2 shr 4)*10;
       if CheckTime(_h,_m,_s) then
            begin
              h:= _h; m:= _m; s:= _s
            end
       else begin
              h:= hour; m:= min; s:= sec
            end;
     End;

   procedure GetDatem(var r,m,d {$IFNDEF CMOS_TIME}, den {$ENDIF}: word);
     Var PByte,PByte1,PByte2:Byte;
         _r,_m,_d: word;
     Begin
       Asm
         cli
         mov al,$07
         out $70,al
         jmp @a
   @a:   jmp @b
   @b:   jmp @c
   @c:   in  al,$71
         mov [PByte],al
         mov al,$08
         out $70,al
         jmp @d
   @d:   jmp @e
   @e:   jmp @f
   @f:   in  al,$71
         mov [PByte1],al
         mov al,$09
         out $70,al
         jmp @g
   @g:   jmp @h
   @h:   jmp @i
   @i:   in  al,$71
         mov [PByte2],al
         sti
       End;
       _d:= (PByte  and $0f)+(PByte  shr 4)*10;
       _m:= (PByte1 and $0f)+(PByte1 shr 4)*10;
       _r:= (PByte2 and $0f)+(PByte2 shr 4)*10;
       if _r<70 then inc(_r,2000) else inc(_r,1900);
       if CheckDate(_r,_m,_d, false) then
          begin
            r:= _r; m:= _m; d:= _d
          end
       else begin
              r:= year; m:= month; d:= day
            end;
     End;


   Procedure SetTimem(h,m,s: word);
     Var
       PByte,PByte1,PByte2:Byte;
     Begin
       PByte :=((s div 10) shl 4)+(s mod 10);
       PByte1:=((m div 10) shl 4)+(m mod 10);
       PByte2:=((h div 10) shl 4)+(h mod 10);
       Asm
         cli
         mov al,$04
         out $70,al
         sti
       End;
       delay(1);
       Asm
         cli
         mov al,[PByte2]
         out $71,al
         mov al,$02
         out $70,al
         sti
       End;
       delay(1);
       Asm
         cli
         mov al,[PByte1]
         out $71,al
         mov al,$00
         out $70,al
         sti
       End;
       delay(1);
       Asm
         cli
         mov al,[PByte]
         out $71,al
         sti
       End;
       absTime_:= true
     End;

   procedure SetDatem(r,m,d: word);
     Var     PByte,PByte1,PByte2: Byte;
     Begin
       r:= r mod 100;
       PByte := ((d div 10) shl 4)+(d mod 10);
       PByte1:= ((m div 10) shl 4)+(m mod 10);
       PByte2:= ((r div 10) shl 4)+(r mod 10);
       Asm
         cli
         mov al,$09
         out $70,al
         sti
       End;
       delay(1);
       Asm
         cli
         mov al,[PByte2]
         out $71,al
         mov al,$08
         out $70,al
         sti
       End;
       delay(1);
       Asm
         cli
         mov al,[PByte1]
         out $71,al
         mov al,$07
         out $70,al
         sti
       End;
       delay(1);
       Asm
         cli
         mov al,[PByte]
         out $71,al
         sti
       End;
       absTime_:= true
     End;

{$ELSE}

    procedure GetTimem(var h,m,s: word);
        var   Sec100: word;
        begin
          asm cli end;
          GetTime(h,m,s, Sec100);
          asm sti end
        end;

    procedure GetDatem(var r,m,d {$IFNDEF CMOS_TIME}, den {$ENDIF}: word);
        begin
          asm cli end;
          GetDate(r,m,d, den);
          asm sti end
        end;

    procedure SetTimem(h,m,s: word);
        begin
          asm cli end;
          SetTime(h,m,s, 0);
          asm sti end;
          absTime_:= true
        end;

    procedure SetDatem(r,m,d: word);
        begin
          asm cli end;
          SetDate(r,m,d);
          asm sti end;
          absTime_:= true
        end;

{$ENDIF}


function _29_2__(_year: word): bool;
   begin
     _29_2__:= not ({not((Frac(_Year/4)=0) and (Frac(_Year/40)<>0))} (_year and 3<>0))
   end;

procedure _19__(_year: word);
    begin
      if _29_2__(_year) then _1990[2]:= 29
      else _1990[2]:= 28
    end; { _19__ }


function dni_mesiaca(rok,mes: word): byte;
   begin
     _19__(rok);
     dni_mesiaca:= _1990[mes];
     _19__(year)
   end;


procedure PrevDateH(var _year: word; var _month, _day,_hour: byte);
    begin
      if _hour=0 then
         begin
           _hour:= 23;
           if _day=1 then
              begin
                if _month=1 then
                   begin
                     _month:= 12;
                     dec(_year)   {if year=2000 then year:= 1999}
                   end
                else Dec(_month);
                _19__(_year);
                _day:= _1990[_month];
                _19__(year); { nojmajny jok }
              end
           else Dec(_day)
         end
      else Dec(_hour)
    end;

procedure PrevDate(var _year: word; var _month, _day: byte);
    var   _hour: byte;
    begin
      _hour:= 0; PrevDateH(_year,_month,_day,_hour);
    end;


procedure NextDate(var _year: word; var _month, _day: byte);
    begin
      _19__(_year);
      if _day=_1990[_month] then
         begin
           _day:= 1;
           if _month=12 then
              begin
                _month:= 1;
                Inc(_year)
              end
           else Inc(_month);
         end
      else Inc(_day);
      _19__(year)
    end; { NextDate }


(*procedure MilleniumDate(var y: word);
    begin
      if y<100 then
         begin
           y:= (year div 100)*100 + y;
           if y<1990 then y:= y+100
           else if (y>50+year) {and (y>2080)} then y:= y-100 { Problem 1998 v roku 2000 }
           else
         end
    end;
*)

procedure MilleniumDate(var y: word);
    begin
      if y>=100 then Exit;
      y:= (year div 100)*100 + y;
      if y=year then Exit;
      if y < 1995 then y:= y + 100
      else if y > 2095 then y:= y - 100
    end;



{ --------------------------------------------- }
{ Kontrola spravnosti:                          }
{ --------------------------------------------- }

function CheckTime(hour,min,sec: byte): bool;
   begin
     if (hour in[0..23]) and (min in[0..59]) and (sec in[0..59])
        then CheckTime:= true
        else CheckTime:= false
   end; { CheckTime }

function CheckDate(_year,_month,_day: word; _forward: bool): bool;
   begin
     _19__(_year);
     CheckDate:= true;
     if not ((_month>0) and (_month<13)) then CheckDate:= false
     else if not ((_day>0) and (_day<=_1990[_month])) then CheckDate:= false
          else if _forward and (DateToSec(_year,_month,_day) < DateToSec(Year,Month,Day)) then CheckDate:= false
               else if not ((_year>1993) and (_year<2994)) then CheckDate:= false;
     _19__(year)
   end; { CheckDate }


{ --------------------------------------------- }
{ Konverzie s realnym formatom                  }
{ --------------------------------------------- }

function DateToSec(_Year,_Month,_Day: real): real;
   var   dni : real;
         i,m : int;
   begin
     { spocitanie ubehnutych dni od roku "0" s uvazenim priestupnych dni
     }
      _19__(trunc(_Year));
      dni:= (_Year-_Rok0)*365;
      for i:= _Rok0+1 to trunc(_Year-1) do if _29_2__(i) then dni:= dni+1;

     { spocitanie ubehnutych dni v roku
     }
      dni:= dni + _Day;
      m:= trunc(_Month);
      while m>0 do
        begin
          if m>12 then m:= 12;
          if m>trunc(_Month-1) then m:= trunc(_Month-1);
          for i:= 1 to m do dni:= dni + _1990[i];
          _Year:= _Year+1;
          _19__(trunc(_Year));
          _Month:= _Month-12;
          m:= trunc(_Month)
        end;

{!}  DateToSec:= dni * 24*60*60;
     _19__(year)
   end; { DateToSec }

function TimeToSec(hour,min,sec: real): real;
   begin
     TimeToSec:= sec + min*60 + hour*60*60
   end; { TimeToSec }


function DTtoSec(_Year,_Month,_Day, _hour,_min,_sec: real): real;
   begin
     DTtoSec:= DateToSec(_Year,_Month,_Day) + TimeToSec(_hour,_min,_sec)
   end;

function DatumToSec(D: TDatum): real;
   begin
     DatumToSec:= DTtoSec(D.rok,D.mes,D.den,D.h,D.m,D.s)
   end;

{
  vrati kolko dni to je
}
function  TimeFromSec(t: real; var h,m,s: byte): int;
   var    _d, _h,_m,_s: real;
   begin
     {while t>secDAY do t:= t-secDAY;}

     _d:= N(trunc(system.int(t/secDAY))); t:= t - _d*secDAY;
     _h:= N(trunc(system.int(t/secHOUR))); t:= t - _h*secHOUR;
     _m:= N(trunc(system.int(t/secMIN)));
     _s:= N(trunc(t - _m*secMIN));

     h:= trunc(_h); m:= trunc(_m); s:= trunc(_s);
     TimeFromSec:= trunc(_d)
   end; { TimeToSec }


procedure DateFromSec(t: real; var r,m,d: word);
    begin
    end;


{ --------------------------------------------- }
{ UNIX time format                              }
{ --------------------------------------------- }

{*---------------------------------------------------------------------*

Name            dos2unix - converts date and time to UNIX time format

Usage           function dos2unix(d:DOS_date; t:DOS_time) : LongInt;

Description     Converts a date and time (as returned from getdate and
                gettime) into UNIX-format time.
                There is little difference between dos2unix and BC++ like
                dostounix functions - this pascal version doesn't test the
                TZ environment variable and ignores daylight saving correction

Return value    UNIX version of the given date and time.

*---------------------------------------------------------------------*}
type   tDays = array[0..11] of Integer;

const  MonthDays:tDays = (31,28,31,30,31,30,31,31,30,31,30,31);

function dos2unix(dt: TDatum) : LongInt;
   var   ut : UNIX_time;
         i,days,hours : int;
   begin
     _19__(1990);

     {tzset();}   { get timezone info }
     ut := LongInt(3652) * LongInt(24) * LongInt(3600) + TimeZone;
     i := dt.rok - 1980; { Convert from 1980 to 1990 base date GMT  }
     if i<0 then i:= i-4;
     ut := ut + (i div 4) * LongInt(1461) * LongInt(24) * LongInt(3600);
     ut := ut + (i and 3) * LongInt( 365) * LongInt(24) * LongInt(3600);
     if (i and 3)<>0 then ut := ut + 24 * 3600;
     days := 0;
     i:= dt.mes-1;  {  Add in months  }
     while (i > 0) do
       begin
         days:= days + _1990[i];
         Dec(i)
       end;
     days:= days + dt.den - 1;
     if (dt.mes > 2) and ((dt.rok and 3)=0) then Inc(days); {  Currently in leap year  }
     hours := days * 24 + dt.h;  {  Find hours  }
     { __isDST is not implememnted - see BC++ runtime libraries source code }
     { if daylight<>0  && __isDST( t.hour,days,0,d.year-1990)) then }
       Dec(hours);
     ut := ut + hours * LongInt(3600);
     ut := ut + LongInt(60) * dt.m + dt.s;

    { cas sa pocita s chybou +4 hodiny }
     ut:= ut - 4*3600;

     dos2unix := ut;
     _19__(year)
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

procedure unix2dos(ut: UNIX_time; var dt: TDatum);
begin
  _19__(1990);

  { cas sa pocita s chybou -4 hodiny }
  ut:= ut + 4*3600;

  {tzset();}                                   {get timezone info}
  ut := ut - (LongInt(3652) * 24 * 3600 + TimeZone);
  dt.s:= ut mod 60;
  ut := ut div 60;                             {Time in minutes}
  dt.m:= ut mod 60;
  ut := ut div 60;                             {Time in hours}
  dt.rok := 1980 + Integer((ut div (1461*24)) *4);
  if ut<0 then
    begin
    dt.rok:=dt.rok-4;
    ut := 1461*24+ut mod (1461 * 24);
    end
  else
    ut := ut mod (1461 * 24);
  if ut >= 366 * 24 then
    begin
    ut := ut - 366 * 24;
    Inc(dt.rok);
    dt.rok := dt.rok + Integer(ut div (365 * 24));
    ut := ut mod (365 * 24);
    end;
  {__isDST is not implememnted - see BC++ runtime libraries source code}
  {if (daylight<>0 and __isDST(Integer(ut mod 24),Integer(ut div 24),0,d.year-1990 )) }
     Inc(ut);
  dt.h := ut mod 24;
  ut := ut div 24;                             {Time in days}
  Inc(ut);
  if ((dt.rok and 3)=0) then
    begin
    if ut > 60 then
      Dec(ut)
    else
    if ut = 60 then
      begin
      dt.mes := 2;
      dt.den := 29;
      Exit;
      end;
    end;
  dt.mes := 0;
  while _1990[dt.mes] < ut do
    begin
      Inc(dt.mes);
      ut := ut - _1990[dt.mes];
    end;
  Inc(dt.mes);
  dt.den := ut;

 { cas sa pocita s chybou -4 hodiny

  inc(dt.h,4);
  if dt.h>23 then
     begin
       dt.h:= dt.h mod 24;
       NextDate(dt.rok,dt.mes,dt.den);
     end;
  }
  _19__(year)
end;


{ ------------------------------------------------------------------
   Ticky
  ------------------------------------------------------------------ }

function GetTicks: tick_counter;
  { var   Ticks : word absolute $40:$006C;  priamo pouzitelne len v Real mode }
   begin
{     asm
	  MOV	ES,Seg0040
          MOV	AL,ES:ShiftState
     end;}
     GetTicks:= MemW[Seg0040:$006C]
   end; { GetTicks }

{
 TimeOut vrati true, ak vyprsal pocet loop-ov od start_ticku.
}
function _TimeOut(start, tick, periode, loops: real): bool;
   begin
     if (start > tick) then tick:= tick+periode;
     _TimeOut:= (start+loops < tick)
   end; { TimeOut }

{
 TimeOut vrati true, ak vyprsal pocet loop-ov od start_ticku.
}
function TimeOut(start, tick, loops: tick_counter): bool;
   begin
     TimeOut:= _TimeOut(start,tick,TIMER_PERIOD,loops)
   end; { TimeOut }


function TimeOutSec(start_sec, sec, delay: real): bool;
   begin
     if (start_sec > sec) then sec:= sec+60;
     TimeOutSec:= (start_sec+delay < sec)
   end; { TimeOut }


{
  WaitForEvent vrati true, ak v casovom limite loops cyklov sa uskutocni
  udalost, ktora je popisana funkciou Podmienka(=true, ak sa uskutocni).
}
function WaitForEvent(loops: long; Podmienka: TBfunc; Proc: TProc): bool;
   var   start_tick : long;
         time_out   : bool;
   begin
     start_tick:= GetTicks;
     if loops<>0 then
        repeat
          if (@Proc <> nil) then Proc;
          time_out:= TimeOut(start_tick,GetTicks,loops)
        until (Podmienka) or (time_out)
     else time_out:= false;
     WaitForEvent:= time_out
   end; { WaitForEvent }

{
Ako WaitForEvent, ale bez podmienky, len caka.
}
procedure Wait(loops: long; Proc: TProc);
   begin
     WaitForEvent(loops,GetFalse,Proc)
   end;

(*
procedure Delay(MS: Word);
    var   start_tick: long;
    begin
      crt.delay(ms)
      {start_tick:= GetTicks;
      repeat
      until TimeOut(start_tick, GetTicks, 18*MS div 1000)}
    end;

procedure Delay (ms: word);
    var   tc, bc : word;
          done   : bool;
    begin
      tc := getticks;
      repeat
        bc := getticks;
        if bc < tc then done:= (($FFFF - tc) + bc >= (18 * ms))
        else done:= (bc - tc >= (18 * ms))
       {fi}
      until done
    end;

*)

{ ------------------------------------------------------------------
   ine
  ------------------------------------------------------------------ }

{
  Ak je karta v grafickom rezime, vrati true
}
function InGraphMode: bool;
   var   reg: Registers;
   begin
     InGraphMode:= false;
    {$IFDEF BGI}
       reg.AH:= $0F;
       Intr($10,reg);
       InGraphMode:= not (reg.AL in [0..3,7])
    {$ENDIF}
    {$IFDEF SPEA}
       InGraphMode:= SPEAinitialized
    {$ENDIF}
   end;


procedure Beep(Hz,Time: word);
    begin
      if not ZVUK then Exit;
      Sound(Hz);
      Delay(Time);
      NoSound
    end; { Beep }


function is_ParamStr(tit: string): string;
   var   i,j: int; s: string;
   begin
     is_ParamStr:= '';
     for i:= 1 to ParamCount do
         begin
           s:= ParamStr(i);
           for j:= 1 to length(s) do s[j]:= upcase(s[j]);
           if pos(tit,s)<>0 then
              begin
                is_ParamStr:= s;
                Exit
              end
         end;
   end;


begin
  TimeZone := DefaultTimeZone*3600;
  {if is_ParamStr('/386')<>'' then _486:= 0;}
  GetTimem(hour,min,sec);
  GetDatem(year,month,day {$IFNDEF CMOS_TIME}, den {$ENDIF});
end. { BIOS }