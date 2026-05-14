{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TFarba   {pre zadanie farby map a inych                  Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
const  Form_Farba: TForm =
            ( item : ' 2 ';
               title: '';
               List : nil;
               pos  : 0;
               legal: @setDig_;
               skip : @setDatum;
               dx:10; dy:1; font:0;
               color: 0
            );

function  GetFarbaStr(var _Farba: string; FarbaStr: string): bool;
   var   _Farb: int;
   begin
      FarbaStr := DelChar(FarbaStr,[' ']);
     _Farb    := GetInt(FarbaStr,1,[' ']);
     if _Farb > 255 then   GetFarbaStr := false
     else
      begin
         _Farba := FarbaStr;
        GetFarbaStr:= true
      end;
   end; { GetFrabaStr }



procedure Farba__init(p: pointer); far;
    begin
      StrCopy(Form_Farba.item,'1  ');
    end;

function Farba__check(p: pointer): bool; far;
   var   _farba: string[4];
         b: bool;
   begin
     b:=     GetFarbaStr(_farba,StrPas(Form_Farba.item));
     if b then begin
        MapFarba := GetInt(_farba,1,[' ']);
     end;
     Farba__check:= b
   end;


