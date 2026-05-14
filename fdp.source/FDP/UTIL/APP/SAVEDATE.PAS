uses dos;

type TDatum = record
       h,m,s,
       den,mes,
       rok : word;
     end;

var  d: TDatum;
     w: word;
     f: file of TDatum;


begin
  GetTime(d.h,d.m,d.s,w);
  GetDate(d.rok,d.mes,d.den,w);
  Assign(f,'date.kod'); Rewrite(f);
  Write(f,d);
  Close(f);
end.