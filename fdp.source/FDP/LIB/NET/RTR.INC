function NETadr_rtr(adr: TNETadr): TRTRadr;
   var   adrr : TRTRadr;
         nd   : int;
   begin
     nd:= is_NETadr(adr);
     if nd>-1 then adrr:= NODEs^[nd].desc.adrr
     else adrr:= is_in_RTRadr(adr);
     NETadr_rtr:= adrr
   end;


function is_RTRadr(adrr: TRTRadr): TNETadr;
   var   adr : TNETadr;
         i   : int;
   begin
     if adrr=RTRadr then adr:= RTRaddress
     else begin
            i:= 0; while (i<NODEpoc) and (NODEs^[i].desc.adrr<>adrr) do inc(i);
            if (i<NODEpoc) then adr:= NODEs^[i].desc.adr
            else {str(adrr,adr)} adr:= WordToHex(adrr)
          end;
     is_RTRadr:= adr
   end;