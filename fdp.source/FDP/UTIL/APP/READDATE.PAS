uses dos;

type TDatum = record
       h,m,s,
       den,mes,
       rok : word;
     end;

var  d: TDatum;
     f: file of TDatum;

begin
  Assign(f,'date.kod'); Reset(f);
  Read(f,d);
  Close(f);
  SetTime(d.h,d.m,d.s,0);
  SetDate(d.rok,d.mes,d.den);
end.