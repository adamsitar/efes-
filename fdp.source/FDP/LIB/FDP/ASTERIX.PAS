{$I comp.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


unit ASTERIX;


interface

   uses   TypeDef;

   const  utc_type_as             = $03;
          utc_message_type_as     = $A081;
          utc_size_as             = 10;

          utc_type_ALas03         = $F2;   {ast_utcALas03}
          utc_message_type_ALas03 = $000B;
          utc_size_ALas03         = 15;


   function _decode_asterixUTC (data: pbytes; size: word; var r: word; var m,d, h,n,s,t: byte): bool;


implementation

uses  BIOS;

{ byte 1     : 0xF2
       2-3   : 000B v opacnom poradi byte
       4-5   : data source identifier in ordef SAC/SIC
       6-9   : date
       10-13 : time
       14-15 : active radars
}
 function _decode_asterixUTC_ALas03 (data: pbytes; size: word; var r: word; var m,d, h,n,s,t: byte): bool;

    function _lo(b: byte): word;
       begin
         _lo:= b and $0F
       end;

    function _hi(b: byte): word;
       begin
         _hi:= (b and $F0) shr 4
       end;

    var   c : int;

    begin
      _decode_asterixUTC_ALas03:= false;

      if    (size<>utc_size_ALas03)
         or (data^[0]<>utc_type_ALas03)
         or (data^[1]<>lo(utc_message_type_ALas03))
         or (data^[2]<>hi(utc_message_type_ALas03))
            then Exit;

      c:= 5;  r:= _hi(data^[c])*1000+_lo(data^[c])*100+_hi(data^[c+1])*10+_lo(data^[c+1]);
      c:= 7;  m:= _hi(data^[c])*10+_lo(data^[c]);
      c:= 8;  d:= _hi(data^[c])*10+_lo(data^[c]);
      c:= 9;  h:= _hi(data^[c])*10+_lo(data^[c]);
      c:= 10; n:= _hi(data^[c])*10+_lo(data^[c]);
      c:= 11; s:= _hi(data^[c])*10+_lo(data^[c]);
      c:= 12; t:= _hi(data^[c])*10+_lo(data^[c]);

      _decode_asterixUTC_ALas03:= true;
    end;


{ test na cas: 03 81 A0 xx HH MM SS xx
}
 function _decode_asterixUTC_as (data: pbytes; size: word; var r: word; var m,d, h,n,s,t: byte): bool;
    begin
      _decode_asterixUTC_as:= false;

     if    ((hour>=23) and (min>=50))
        or ((hour<=0) and (min<10))
        or (size<>utc_size_as)
        or (data^[0]<>utc_type_as)
        or (data^[1]<>lo(utc_message_type_as))
        or (data^[2]<>hi(utc_message_type_as))
           then Exit;

     r:= year;
     m:= month;
     d:= day;

     {$IFDEF ASTERIX}
     { bolo o 1 menej, nie je tu chyba ?! }
       h:= (data^[5] shr 4)*10 + (data^[5] and $0F);
       n:= (data^[6] shr 4)*10 + (data^[6] and $0F);
       s:= (data^[7] shr 4)*10 + (data^[7] and $0F);
     {$ELSE}
       h:= data^[4];
       n:= data^[5];
       s:= data^[6];
     {$ENDIF}

      _decode_asterixUTC_as:= true;
    end;


 function _decode_asterixUTC (data: pbytes; size: word; var r: word; var m,d, h,n,s,t: byte): bool;
    begin
      {$IFDEF ASTERIX_ALas03}
        _decode_asterixUTC:= _decode_asterixUTC_ALas03 (data,size, r,m,d, h,n,s,t);
      {$ELSE}
        _decode_asterixUTC:= _decode_asterixUTC_as (data,size, r,m,d, h,n,s,t);
      {$ENDIF}
    end;

end.