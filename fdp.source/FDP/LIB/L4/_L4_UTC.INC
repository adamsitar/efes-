function code_l4_utc (h,m: byte): string;
   begin
     code_l4_utc:= inttostr(h,2,0)+inttostr(m,2,0)
   end;

function decode_l4_utc (s: string; var h,m: byte): bool;
   begin
     h := scis(s,1,2);
     m := scis(s,3,2);
     decode_l4_utc:= CheckTime(h,m,0)
   end;

function decode_l4_utc_s (s: string): string;
   begin
     decode_l4_utc_s:= copy(s,1,2)+':'+copy(s,3,2)
   end;


function code_l4_time (t: TTime): string;
   begin
     code_l4_utc(t.h,t.m)
   end;

function decode_l4_time (s: string; var T: TTime): bool;
   begin
     decode_l4_utc(s, t.h,t.m)
   end;




procedure assign_date_r (den,mes : byte; var rok: word);
   begin
     rok:= year;
     if (mes=1)  and (month=12)  then rok:= rok+1;
     if (mes=12) and (month=1) then rok:= rok-1;
   end;

function decode_l4_date_r (s: string; var d: TDate; am: bool): bool;
   var   id,im: int;
   begin
     if length(s)>4 then decode_l4_date_r:= decode_l4_date(s,d)
     else begin
            if am then begin id:= 3; im:= 1 end
            else begin id:= 1; im:= 3 end;
            d.d := scis(s,id,2);
            d.m := scis(s,im,2);
            assign_date_r (d.d,d.m, d.r);
            decode_l4_date_r:= CheckDate(d.r,d.m,d.d,false)
          end;
   end;

function code_l4_date_r (den,mes: byte; am: bool): string;
   var   id,im: byte;
   begin
     if am then begin id:= mes; im:= den end
     else begin id:= den; im:= mes end;
     code_l4_date_r:= inttostr(id,2,0)+inttostr(im,2,0)
   end;


function code_l4_date_(r: word; m,d: byte): string;
   begin
     code_l4_date_:=    inttostr(r mod 100,2,0)
                      + inttostr(m,2,0)
                      + inttostr(d,2,0)
   end;

function code_l4_date(d: TDate): string;
   begin
     code_l4_date:= code_l4_date_(d.r,d.m,d.d)
   end;

function code_l4_datum(d: TDatum): string;
   begin
     code_l4_datum:=   inttostr(D.rok mod 100,2,0)
                     + inttostr(D.mes,2,0)
                     + inttostr(D.den,2,0)
                     + inttostr(D.h  ,2,0)
                     + inttostr(D.m  ,2,0)
                     {+ inttostr(D.s  ,2,0)}
   end;

function code_l4_datums(d: TDatum): string;
   begin
     code_l4_datums:= code_l4_datum(d) + inttostr(D.s,2,0)
   end;


function decode_l4_date(s: string; var d: TDate): bool;
   begin
     decode_l4_date:= true;
     fillchar(d,sizeof(d),0);
     d.r:= scis(s,1,2);
     MilleniumDate(d.r);
     d.m:= scis(s,3,2);
     d.d:= scis(s,5,2);
     decode_l4_date:= CheckDate(d.r,d.m,d.d,false)
   end;

function decode_l4_datum(s: string; var d: TDatum): bool;
   begin
     decode_l4_datum:= true;
     fillchar(d,sizeof(d),0);
     d.rok:= scis(s,1,2);
     MilleniumDate(d.rok);
     d.mes:= scis(s,3,2);
     d.den:= scis(s,5,2);
     d.h  := scis(s,7,2);
     d.m  := scis(s,9,2);
     if length(s)>10 then d.s  := scis(s,11,2);
     decode_l4_datum:= CheckDate(d.rok,d.mes,d.den,false) and CheckTime(d.h,d.m,d.s)
   end;

function decode_l4_datums(s: string; var d: TDatum): bool;
   begin
     decode_l4_datums:= decode_l4_datum(s,d);
     d.s:= scis(s,11,2)
   end;
