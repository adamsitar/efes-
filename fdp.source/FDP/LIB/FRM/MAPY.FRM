{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û Rozsah - pre zadanie rozsahu vykreslenia map             Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
const  Form_Rozsah: TForm =
            ( item : '    km'; title: '';
              lst : nil; pos: 0;
              legal: @setCisl; skip : @setPism;
              dx:0; dy:0; font:0; color: 0
            );

procedure Rozsah_init(p: pointer); far;
    var   s :  string;
          r : long;
    begin
      r:= trunc(Mapa^.Rozsah/1000);
      s:= IntToStr(r, StrLen(Form_Rozsah.item)-3, 0)+' km';
      StrPCopy(Form_Rozsah.item,s);
    end;

function Rozsah_check(p: pointer): bool; far;
   var   _Rozsah: int;
         b: bool;
   begin
     _Rozsah:= GetInt(StrPas(Form_Rozsah.item),1,set_);
     b:= (_Rozsah>=2) and (_Rozsah<=999);
     {$IFDEF SK}
      if not b then Err('','Hodnota mimo povolen˜ rozsah (2-999km).');
     {$ENDIF}
     Rozsah_check:= b
   end;

procedure Rozsah_done(p: pointer);
    begin
      Mapa^.Rozsah:= GetInt( StrPas(Form_Rozsah.item),1,set_ ) * 1000;
      Mapa^.Draw
    end;

procedure  formular_Rozsah;
    var    form: PSingleForm;
           _Ev : TEvent;
    const  f: Tcentr = (x: initX; y: initY; m: 1);
    begin
      if not PLANZET_MAPA then exit;

      form:= New(PSingleForm,Init(nil, f.x,f.y, f.m,
                 kbEnter,cmOK, 'km : ', @Form_Rozsah,
                 clGR2,cfText, 0,
                 nil,@Rozsah_init,@Rozsah_check,@Rozsah_done, nil, false)
                );
      form^.Run(_Ev);
      Dispose(form,Done);
    end;


{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û Priestor   pre zadanie priestoru pre vystredenie         Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
const  Form_Priestor: TForm =
            ( item : '      ÿ2'; title: '';
              lst : @fnMapStred; pos: 1;
              legal: @setABC; skip : @setDatum;
              dx:1 ; dy:1; font:0; color: 0
            );

procedure Priestor_init(p: pointer); far;
    begin
      StrCopy(Form_Priestor.item,'        ');
    end;

function Priestor_check(p: pointer): bool; far;
   var   b: bool;
   begin
     with Form_Priestor do b:= _in_list(StrPas(item), lst,[],pos,nil);
     if not b then Err('',err_UNKNOWN_AREA);
     Priestor_check:= b
   end;

procedure Priestor_done(p: pointer);
    var   s: string;
          st,min,sek      : int;
          XPriest,Ypriest : real;
    begin
      with Form_Priestor do s:= getstr(_get_comment(StrPas(item),lst,[],pos), 2, [';']);
      if s<>'' then
         begin
           st:= getint(s,1,set_); min:= getint(s,2,set_); sek:= getint(s,3,set_);
           YPriest := ((st*3600.0)+(min*60.0)+sek)* 30.69444;
           st:= getint(s,4,set_); min:= getint(s,5,set_); sek:= getint(s,6,set_);
           XPriest := ((st*3600.0)+(min*60.0)+sek)* 20.3819;
           with Mapa^ do
             begin
               Rozsah := 200000.0;
               Xvystred := XPriest; Yvystred := YPriest;
               Draw
             end
         end
      else Err('',err_UNKNOWN_XY)
    end;

procedure  formular_Priestor;
    var    form : PSingleForm;
           _Ev  : TEvent;
    const  f: Tcentr = (x: initX; y: initY; m: 1);
    begin
      if not PLANZET_MAPA then Exit;

      form:= New(PSingleForm,Init(nil, f.x,f.y, f.m,
                 kbEnter,cmOK,' ? ',@Form_Priestor,
                 clGR2,cfText, 0,
                 nil,@Priestor_init,@Priestor_check,@Priestor_done, nil, false)
                );
      form^.Run(_Ev);
      Dispose(form,Done);
    end;

