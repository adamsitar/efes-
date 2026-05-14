{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TNazov   {pre mapu, symbol, a ine 8 znakov               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const  Form_Nazov: TForm =
            ( item : 'meno    ';
               title: '';
               List : nil;
               legal: @setABC;
               skip : @setDatum;
               dx:0 ; dy:0; font:0;
               color: 0
            );

procedure Nazov__init; far;
    begin
      StrCopy(Form_Nazov.item,'        ');
    end;

function Nazov__check: bool; far;
   var   _novemeno: string[8];
         b: bool;
   begin
     b:=     GetNazov(_novemeno,StrPas(Form_Nazov.item));
     if b then begin
        SetNazov(_novemeno);
     end;
     Nazov__check:= b
   end;


