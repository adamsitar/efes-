{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ formular_DATUM                                           €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const  Form_DATUM: array [0..0] of TForm =
            (( item : '  .  .    '; title: '';
               Lst  : nil; pos: 0;
               legal: @setCisl; skip : @setDatum;
               dx:0 ; dy:0; font:0; color: 0
             ));

var plan_date: TDate;

function Datum_check(p: pointer): bool; far;
   var   dd,mm: byte; yy: word;
         b: bool;
   begin
     b:= GetDateStr(yy,mm,dd,StrPas(Form_DATUM[0].item),false);
     if b then with plan_date do begin m:= mm; d:= dd; r:= yy end;
     Datum_check:= b
   end;

function formular_DATUM(var _plan_date: TDate; x,y: int; _tit: string): bool;
   var   form  : PSingleForm;
         dd,mm : byte; yy: word; m: int;
         E     : TEvent;
   begin
   { priprava dat }
     fillchar(plan_date,sizeof(TDate),0); m:= ord(GraphMode);
     if not (       GetDateStr( yy,mm,dd,StrPas(Form_DATUM[0].item),false )
              and ( DateToSec(Year,Month,Day) <= DateToSec(yy,mm,dd ) )
            )
        then StrPCopy(Form_DATUM[0].item,DateToStr(day,month,year, 1,'.'));
   { nacitanie }
     form:= New(PSingleForm,Init(nil, x,y,m, kbEnter,cmOK,
                _tit, @Form_DATUM,
                clGR2,cfText, 1,
                nil, nil,@Datum_check,nil, nil, false)
               );
     form^.RunLocalFunc(E,tit_den_platnosti);
     Dispose(form,Done);
     formular_DATUM:= plan_date.r<>0;
     _plan_date:= plan_date
   end;


const  form_DATUM_CAS : array [0..1] of TForm =
            (( item : '01.  .    ';
               title: '';
               lst : nil; pos: 0;
               legal: @setCisl; skip : @setDatum;
               dx:10 ; dy:18; font:0; color: 0
             ),
             ( item : '02:  '; title: '';
               lst : nil; pos: 0;
               legal: @setCisl; skip : @setCas;
               dx:110 ; dy:18; font:0; color: 0
             )
             );

procedure init_DATUM_CAS(form : PFormular; d: PDatum); far;
    begin
      StrPCopy(form^.itemd^[1].item,TimeToStr(d^.h,d^.m, ':'));
      StrPCopy(form^.itemd^[0].item,DateToStr(d^.den,d^.mes,d^.rok, 1, '.'))
    end;

function check__DATUM_CAS(form : PFormular; d: PDatum): bool; far;
   var   h,m,s, den,mes: byte; rok: word;
   begin
     if GetTimeStr(h,m,s,StrPas(form^.itemd^[1].item)) and GetDateStr(rok,mes,den,StrPas(form^.itemd^[0].item),false) then
        begin
          d^.rok:= rok; d^.mes:= mes; d^.den:= den;
          d^.h:= h; d^.m:= m; d^.s:= s;
          check__DATUM_CAS:= true
        end
     else check__DATUM_CAS:= false
   end;


function  formular_DATUM_CAS(_title: string; var datum: TDatum): bool;
    var   form   : PFormular;
          _Event : TEvent;
          sec    : byte;
    const f : Tcentr = (x: initX; y: initY; m:1);
    begin
      if datum.rok=0 then datum_init(datum, day,month,year, hour,min,sec);
      form:= New(PFormular,Init(nil, f.x,f.y, f.m,
                 kbCtrlEnter,cmOK, _title,
                 @form_DATUM_CAS, 2,0, 0,0,0, 0, 0, 0,0,nil,0,0,0,0,
                 @datum, @init_DATUM_CAS,@check__DATUM_CAS, nil,nil,false,false,false,nil
                ));
      form^.first_pos:= 1;
      form^.RunLocalFunc(_Event,EDIT_INFO);
      formular_DATUM_CAS:= form^.corr_res;
      Dispose(form,Done)
    end;
