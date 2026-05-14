const  form_UTC : array [0..1] of TForm =
            (( item : '  .  .    ';
               title: '';
               lst : nil; pos: 0;
               legal: @setCisl; skip : @setDatum;
               dx:10 ; dy:8; font:0; color: 0
             ),
             ( item : '  :  '; title: '';
               lst : nil; pos: 0;
               legal: @setCisl; skip : @setCas;
               dx:10 ; dy:26; font:0; color: 0
             )
             );




procedure Hodiny__init(form : PFormular); far;
    begin
      StrPCopy(form^.itemd^[1].item,TimeToStr(hour,bios.min, ':'));
      StrPCopy(form^.itemd^[0].item,DateToStr(day,month,year, 1, '.'))
    end;

function Hodiny__check(form : PFormular): bool; far;
   var   d: TDatum;
         b: bool;
   begin
     b:=     GetTimeStr(d.h,d.m,d.s,StrPas(form^.itemd^[1].item))
         and GetDateStr(d.rok,d.mes,d.den,StrPas(form^.itemd^[0].item),false);
     if b then
        begin
          d.s:= {$ifdef debug} 55 {$else} 0 {$endif};
          novyDatum:= d;
          nastavDatum:= true;
          _write_err_log('Time set by operator to the '+DateToStr2(day,month,year)+' '+TimeToStr2(hour,min,sec,':','ú'));
        end;
     Hodiny__check:= b
   end;

procedure  formular_Hodiny;
    var    form   : PFormular;
           _Event : TEvent;
    const  f      : Tcentr = (x: initX; y: initY; m:1);
    begin
      form:= New(PFormular,Init(nil, f.x,f.y, f.m, kbCtrlEnter,cmOK,
                'UTC', @form_UTC, 2,0, 0,0,0, 0, 0, 0,0,nil,0,0,0,0,
                 nil, @Hodiny__init,@Hodiny__check, nil, nil,false,false,false,nil
                ));
      form^.first_pos:= 1;
      form^.RunLocalFunc(_Event,EDIT_INFO);
      Dispose(form,Done)
    end;
