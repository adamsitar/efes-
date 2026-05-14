(*-------------------------------------------------------------------*)
(* Praca s casom                                                     *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}  { volam v intr procedurach }


unit UTime;


interface


    uses  TypeDef;


    const Days : array[0..6] of string[3] =
                 {$IFDEF SLOVAK}
                   ('NedeŒa','Pondelok','Utorok','Streda','›tvtok','Piatok','Sobota');
                 {$ENDIF}
                 {$IFDEF CZECH}
                   ('Nedele','Pondel¡','Uter˜','St©eda','›tvrtek','P tek','Sobota');
                 {$ENDIF}
                 {$IFDEF ENGLISH}
                   ('Sun','Mon','Tue','Wed','Thu','Fri','Sat');
                 {$ENDIF}

          Months : array[1..12] of string[15] =
                 {$IFDEF SLOVAK}
                   ('janu r','febru r','marec','apr¡l','m j','j£n','j£l','august','september','okt¢ber','november','december');
                 {$ENDIF}
                 {$IFDEF CZECH}
                   ('leden','£nor','b©ezen','duben','kvˆten','‡erven','‡ervenec','srpen','z ©¡','©¡jen','listopad','prosinec');
                 {$ENDIF}
                 {$IFDEF ENGLISH}
                   ('January','February','March','April','May','June','Jule','August','September','October','November',
                    'December');
                 {$ENDIF}


          not_archive_day = 0;
          cnst_time = '  :  ';


    function  set_absTime: real;

    procedure cas_init   (var cas   : Tcas; _hod,_min: byte);
    procedure datum_init (var datum : Tdatum; _den,_mes: byte; _rok: word; _h,_m,_s: byte);

    procedure init_date  (var date: TDate; _r,_m,_d: word);
    procedure init_time  (var time: TTime; _h,_m,_s: word);

    function  eq_datum   (D1,D2: TDatum): bool;
    function  eq_date    (D1,D2: TDate): bool;
    function  eq_time    (T1,T2: TTime): bool;
    function  eq_cas     (C1,C2: TCas) : bool;

    function  prienik_casov  (D0z,D0k, D1z,D1k: TDatum): bool;

    function  is_next_time (h1,m1, h2,m2: byte): bool;
    function  is_next_date (date: TDate): bool;
    function  is_this_date (date: TDate; _r,_m,_d: word): bool;

    procedure IncTimeMin (var h,m: byte; dm: int);
    function  IncRTime   (var t: real; dt: real): real;
    procedure IncTTime   (var t: TTime; t1,t2: TTime);
    procedure IncHMTime  (var h,m: byte; h1,m1,h2,m2: byte);

    procedure dt_time    (h1,m1,s1, h2,m2,s2: byte; var h,m,s: byte);


   { konverzia so stringom }
    function  TimeToStr  (hour,min: byte; ch: str1): string;
    function  TimeToStr2 (hour,min,sec: byte; s1,s2: string): string;
    function  DateToStr  (day,month, year: word; _0: byte; ch: str1): string;
    function  DateToStr2 (day,month, year: word): string;
    function  DateToStrS (day,month, year: word): string;

    function  GetTimeStr (var h,m,s: byte; _time: string): bool;

    function  GetDateStr_(var y: word; var m,d: byte; _date: string; amd: bool; odd: TCharSet): bool;
    function  GetDateStr (var y: word; var m,d: byte; _date: string; amd: bool): bool;

   {$IFDEF DATA_BIN}
    function  code0_utc(t: string): string;
    function  decode0_utc(t: string): string;
   {$ENDIF}



implementation

uses  Dos, BIOS, str0, math;


procedure cas_init(var cas: Tcas; _hod,_min: byte);
    begin
      cas.h:= _hod;
      cas.m:= _min
    end;

procedure datum_init(var datum: Tdatum; _den,_mes: byte; _rok: word; _h,_m,_s: byte);
    begin
      with datum do
        begin
          h:= _h; m:= _m; s:= _s;
          den:= _den; mes:= _mes; rok:= _rok
        end;
    end;


procedure init_date(var date: TDate; _r,_m,_d: word);
    begin
      date.r:= _r; date.m:= _m; date.d:= _d
    end;

procedure init_time(var time: TTime; _h,_m,_s: word);
    begin
      time.h:= _h; time.m:= _m; time.s:= _s
    end;


function eq_datum(D1,D2: TDatum): bool;
   begin
     eq_datum:=     ((D1.rok=D2.rok) and (D1.mes=D2.mes) and (D1.den=D2.den))
                and ((D1.h=D2.h) and (D1.m=D2.m) and (D1.s=D2.s))
   end;

function eq_time (T1,T2: TTime): bool;
   begin
     eq_time:= (T1.h=T2.h) and (T1.m=T2.m) and (T1.s=T2.s)
   end;

function eq_date (D1,D2: TDate): bool;
   begin
     eq_date:= (D1.d=D2.d) and (D1.m=D2.m) and (D1.r=D2.r)
   end;

function eq_cas (C1,C2: TCas) : bool;
   begin
     eq_cas:= (C1.h=C2.h) and (C1.m=C2.m)
   end;


function prienik_casov (D0z,D0k, D1z,D1k: TDatum): bool;
   begin
     prienik_casov:=
       RPrienik
           ( DatumToSec(D0z),
             DatumToSec(D0k),
             DatumToSec(D1z),
             DatumToSec(D1k)
           )
   end;


function is_next_time(h1,m1, h2,m2: byte): bool;
   begin
     is_next_time:= (h1<h2) or ((h1=h2) and (m1<=m2)) { musi ostat <= ... }
   end;

function is_next_date(date: TDate): bool;
   begin
     is_next_date:= DateToSec(year,month,day) < DateToSec(date.r,date.m,date.d)
   end;

function is_this_date(date: TDate; _r,_m,_d: word): bool;
   begin
     is_this_date:= (date.r=_r) and (date.m=_m) and (date.d=_d)
   end;


function  set_absTime: real;
   begin
     absTime:= DTtoSec(Year,Month,Day, hour,min,sec);
     set_absTime:= absTime;
     absTime_:= false;
     nastavDatum:= false
   end;


{ ----------------------------------------------- }

procedure IncTimeMin(var h,m: byte; dm: int);
    var   time: longint;
          s: byte;
    begin
      time:= (trunc((TimeToSec(h,m,00)+0.5)) + dm*secMIN) mod secDAY;
      TimeFromSec(time, h,m,s)
    end;

function IncRTime(var t: real; dt: real): real;
   var   r: real;
   begin
     t:= (abs(t + dt));
     r:=  system.int(t/secDAY); t:= t - r*secDAY;
     IncRTime:= t
   end;

procedure IncTTime(var t: TTime; t1,t2: TTime);
    var   r, r1,r2: real;
          s: byte;
    begin
      r:= TimeToSec(t.h,t.m,0);
      r1:= TimeToSec(t1.h,t1.m,0);
      r2:= TimeToSec(t2.h,t2.m,0);
      IncRTime(r, r1-r2);
      TimeFromSec(r, t.h,t.m,s)
    end;

procedure IncHMTime(var h,m: byte; h1,m1,h2,m2: byte);
    var   t, t1,t2: TTime;
          s: byte;
    begin
      t.h:= h; t.m:= m; t1.h:= h1; t1.m:= m1; t2.h:= h2; t2.m:= m2;
      IncTTime(t, t1,t2);
      h:= t.h; m:= t.m
   end;

{procedure IncTime(var h,m: byte; hi,mi: byte);
    begin
      IncHMTime(h,m, hi,mi,0,0)
    end;
}

procedure dt_time(h1,m1,s1, h2,m2,s2: byte; var h,m,s: byte);
    var   r1,r2: real;
    begin
      r1:= TimeToSec(h1,m1,s1); r2:= TimeToSec(h2,m2,s2);
      if r2<r1 then r2:= r2 + secDAY;
      TimeFromSec(r2-r1, h,m,s)
    end;


{ --------------------------------------------- }
{ Konverzie s realnym formatom                  }
{ --------------------------------------------- }

function TimeToStr(hour,min: byte; ch: str1): string;
   begin
     TimeToStr:= IntToStr(hour,2,0)+ch+IntToStr(min,2,0)
   end; { TimeToStr }

function TimeToStr2(hour,min,sec: byte; s1,s2: string): string;
   begin
     TimeToStr2:= IntToStr(hour,2,0)+s1+IntToStr(min,2,0)+s2+IntToStr(sec,2,0)
   end;

function DateToStr (day,month, year: word; _0: byte; ch: str1): string;
   var   s: string;
   begin
     s:= IntToStr(day,2,_0)+ch+IntToStr(month,2,_0);
     if year<>0 then s:= s+ch+IntToStr(year,4,_0);
     DateToStr:= s
   end; { TimeToStr }

function DateToStr2(day,month, year: word): string;
   var   s: string;
   begin
     s:= IntToStr(day,1,1)+'.'+IntToStr(month,1,1)+'.';
     if year<>0 then s:= s + IntToStr(year,1,1);
     DateToStr2:= s
   end;

function DateToStrS(day,month, year: word): string;
   var   s: string;
   begin
     if day<>not_archive_day then s:= IntToStr(day,1,1)+'.' else s:= '';
     s:= s + Months[month];
     if year<>0 then s:= s + ' ' +IntToStr(year,1,1);
     DateToStrS:= s
   end;

{
function DateToStrE(day,month): string;
   var   s: string;
   begin
     case month of
        1 : s:= 'Januar
        2 :
        3 :
        4 :
        5 :
        6 :
        7 :
        8 :
        9 :
       10 :
       11 :
       12 :
     end;


     s:= IntToStr(day,1,1)+'.'+IntToStr(month,1,1)+'.';
     if year<>0 then s:= s + IntToStr(year,1,1);
     DateToStr2:= s
   end;
}

{ nepripustny prazdny retazec
}
function GetTimeStr(var h,m,s: byte; _time: string): bool;
   var   r1,r2,r3: int;
         s1,s2,s3: string[3];
         t: string;
   begin
     GetTimeStr:= false;
     h:= 0; m:= 0; s:= 0;
     t:= DelChar(_time,['.',':',' ','ú']);
     if (t<>''){ and ((length(t)=4) or (length(t)=6))} then
        begin
          if (Pos(':',_time)<>0) or (Pos('.',_time)<>0) then
             begin
               s1:= GetStr(_time,1,[':','.','ú']);
               s2:= GetStr(_time,2,[':','.','ú']);
               s3:= GetStr(_time,3,[':','.','ú']);
             end
          else begin
                 _time:= DelChar(_time,[' ']);
                 s1:= Copy(_time,1,2);
                 s2:= Copy(_time,3,2);
                 s3:= Copy(_time,5,2)
               end;
          if s1<>'' then val(s1,h,r1) else begin h:= 0; r1:= 0 end;
          if s2<>'' then val(s2,m,r2) else begin m:= 0; r2:= 0 end;
          if s3<>'' then val(s3,s,r3) else begin s:= 0; r3:= 0 end;
          GetTimeStr:= CheckTime(h,m,s) and (r1=0) and (r2=0) and (r3=0)
        end
   end; { GetTimeStr }


function GetDateStr_(var y: word; var m,d: byte; _date: string; amd: bool; odd: TCharSet): bool;
   var   is : bool;
         r  : int;
   begin
     _date:= cut_(_date);
     is:= (odd<>[]);
     if is then
       begin
         r:= 1; while (r<length(_date)) and (not (_date[r] in odd)) do inc(r);
         is:= r<length(_date) { oddelovac na konci nema zmysel }
       end;
     if is then
        begin
          d:= GetInt(_date,1,odd);
          m:= GetInt(_date,2,odd);
          y:= GetInt(_date,3,odd);
          if length(_date)=5 then begin y:= BIOS.year; amd:= false end
        end
     else begin
            Val(Copy(_date,1,2),d ,r);
            Val(Copy(_date,3,2),m ,r);
            Val(Copy(_date,5,4),y ,r);
            if length(_date)=4 then begin y:= BIOS.year; amd:= false end
          end;
     if amd then begin r:= d; d:= y; y:= r end;
     MilleniumDate(y);
     GetDateStr_:= CheckDate(y,m,d, false)
   end; { GetDateStr_ }


function GetDateStr(var y: word; var m,d: byte; _date: string; amd: bool): bool;
   begin
     GetDateStr:= GetDateStr_(y,m,d, _date,amd, ['.'])
   end; { GetDateStr }


procedure DATE_init;
    var   dow,hund : word;
    begin
      asm cli end;
      DOS.GetDate(Year,Month,Day, hund);
      DOS.GetTime(hour,min,sec, dow);
      asm sti end;
      _19__(Year)
    end; { DATE_init }


{$IFDEF DATA_BIN}
  function code0_utc(t: string): string;
     begin
       t:= cut_(t);
       if t<>'' then t:= copy(t,1,2)+':'+copy(t,3,2)
       else t:= format_s(t);
       code0_utc:= t
     end;

  function decode0_utc(t: string): string;
     begin
       decode0_utc:= cut_(delchar(t,[':']))
     end;
{$ENDIF}


begin
  DATE_init;
  set_absTime
end. { Time }
