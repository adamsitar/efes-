{
  Converts from CALL_DESC character format to CCITT 1984 format (BCD)
  for call request packet to decode
     - calling
     - called
     - facility data
     - user data
}
function T_AdCOM.CONV_TO_CPKT(FROM_: CALL_DESC; var TO_: X25_PACKET_ARRAY): S16BIT;
   var   i,count : S16BIT;
         CTMP    : ARRAY[0..31] OF U8BIT;
   begin {for i:=0 to 299 do TO_[i]:=0; for i:=0 to 31 do CTMP[i]:=0;}

     {Build the packet}

     {Step #1 : address conversion from ASCII to BCD}
      count:= 0;
      FROM_.callg_len:= FROM_.callg_len and $0F;    { defensive check }
      FROM_.calld_len:= FROM_.calld_len and $0F;    { defensive check }
      TO_[count]:= (FROM_.callg_len SHL 4) or FROM_.calld_len;
      inc(count);
      move(FROM_.calld_adr,CTMP[0],FROM_.calld_len);
      move(FROM_.callg_adr,CTMP[FROM_.calld_len],FROM_.callg_len);

     {Called address then calling address}
      i:= 0;
      while i < (FROM_.calld_len + FROM_.callg_len) do
        begin
          TO_[count]:= ((CTMP[i] and $0f) SHL 4) or (CTMP[i+1] and $0F);
          inc(i,2);
          inc(count)
        end;

     {Fix up last one to be sure it's zero}
      if ((FROM_.calld_len + FROM_.callg_len) and 1) = 1 then
         begin
           TO_[count-1]:= TO_[count-1] and $F0;
         end;

     {Step #2: facility length and facility data}
      if FROM_.fac_len > SizeOf(FROM_.fac_data) then FROM_.fac_len:= SizeOf(FROM_.fac_data);   { Defensive check }
      TO_[count]:= FROM_.fac_len;
      inc(count);
      i:= 0;
      while (i < FROM_.fac_len) and (count < SizeOf(TO_)) do
        begin
          TO_[count]:= FROM_.fac_data[i];
          inc(count);
          inc(i)
        end;

     {Step #3 : user data}
      if FROM_.usr_len > SizeOf(FROM_.usr_data) then FROM_.usr_len:= SizeOf(FROM_.usr_data); {Defensive check}
      i:= 0;
      while (i < FROM_.usr_len) and (count < SizeOf(TO_)) do
        begin
          TO_[count]:= FROM_.usr_data[i];
          inc(count);
          inc(i)
        end;

      CONV_TO_CPKT:=   (1 + ((FROM_.calld_len + FROM_.callg_len + 1) SHR 1)
                     +  1
                     + (FROM_.fac_len + FROM_.usr_len));

   end; { CONV_TO_CPKT }


{
  Converts to CALL_DESC character format from CCITT 1984 call request packet
}
procedure T_AdCOM.CONV_FROM_CPKT(FROM_: X25_PACKET_ARRAY; LEN: U16BIT; var TO_: CALL_DESC);
   var    CTMP : array[0..29] of U8BIT;
          count,i, size,l1,l2 : int;
   begin
     count:= 0;
     TO_.callg_len:= FROM_[count] shr 4;
     TO_.calld_len:= FROM_[count] and $0F;
     inc(count);

     {Decode the packet}
     {step #1 : address conversions from BCD to ASCII}
     {          called address then calling address}
     i:= 0; while (i < ((TO_.calld_len + TO_.callg_len) and $1E)) and (i < sizeof(CTMP)-1 {22.11.}) do
       begin
         CTMP[i]  := (FROM_[count] shr 4);  {+ ord('0')}
         CTMP[i+1]:= (FROM_[count] and $F); {+ ord('0')}
         inc(count);
         inc(i,2)
       end;

     if ((TO_.calld_len + TO_.callg_len) and 1) = 1 then
        begin
          CTMP[i]:= FROM_[count] shr 4 {+ ord('0')};  {catch last one}
          if EXCEPTION_CALL_DESC then inc(count);
        end;

     move(CTMP,TO_.calld_adr,TO_.calld_len);
     move(CTMP[TO_.calld_len],TO_.callg_adr,TO_.callg_len);

     {step #2 facility data}
     TO_.fac_len:= Minimum(FROM_[count],SizeOf(TO_.fac_data));
     inc(count);
     i:= 0;
     while (i < TO_.fac_len) and (count < SizeOf(FROM_)) do
       begin
         TO_.fac_data[i]:= FROM_[count];
         inc(count);
         inc(i)
       end;

     {step #3 user data}
     l1:= TO_.calld_len + TO_.callg_len;
     l2:= TO_.fac_len;
     size:= LEN - 1;
     size:= size - ((l1 + 1) shr 1) - 1 - l2;
     TO_.usr_len:= N(Minimum(size, SizeOf(TO_.usr_data)));
     {move(FROM_[count],TO_.usr_data,Minimum(TO_.usr_len,SizeOf(FROM_)-count+1));}
     i:= 0; while (i < TO_.usr_len) and (count < SizeOf(FROM_)) do
       begin
         TO_.usr_data[i]:= FROM_[count];
         inc(count);
         inc(i)
       end
   end; { CONV_FROM_CPKT }


(*

function T_AdCOM.STRUC_TO_PKT(var FROM_ : SEND_DESC; var TO_ : X25_PACKET_ARRAY): U16BIT;
   var   count : U16BIT;
         i     : U8BIT;
   begin
     count:=0;
     TO_[count]:=FROM_.callg_len;
     inc(count);
     TO_[count]:=FROM_.calld_len;
     inc(count);

     i:=0;
     while i <= FROM_.callg_len - 1 do
       begin
         TO_[count]:= FROM_.callg_padr[i];
         inc(count);
         inc(i)
       end;

     i:=0;
     while i <= FROM_.calld_len - 1 do
       begin
         TO_[count]:= FROM_.calld_padr[i];
         inc(count);
         inc(i)
       end;

     TO_[count]:=Hi(FROM_.data_len);
     TO_[count+1]:=Lo(FROM_.data_len);
     inc(count,2);

     move(FROM_.data,TO_[count],FROM_.data_len);

     struc_TO_pkt:= 1 + FROM_.callg_len +
                    1 + FROM_.calld_len +
                    2 + FROM_.data_len;

   end; { STRUC_TO_PKT }


procedure T_AdCOM.STRUC_FROM_PKT (var FROM_: X25_PACKET_ARRAY; LEN: U16BIT; var TO_: SEND_DESC);
    var   count : U16BIT;
          i     : U16BIT;
    begin
      count:=0;    {Calling pseudoaddr. length}
      TO_.callg_len:=FROM_[count];
      inc(count);

      TO_.calld_len:=FROM_[count]; {Called pseudoaddr. length}
      inc(count);

      i:=0;       {Calling pseudoaddress}
      while i <= TO_.callg_len - 1 do
        begin
          TO_.callg_padr[i]:=FROM_[count];
          inc(count);
          inc(i);
        end;

      i:=0;       {Called pseudoaddress}
      while i <= TO_.calld_len - 1 do
        begin
          TO_.calld_padr[i]:=FROM_[count];
          inc(count);
          inc(i);
        end;

      TO_.data_len:= (FROM_[count] SHL 8) + FROM_[count+1];
      inc(count,2);

      move(FROM_[count],TO_.data,TO_.data_len)

    end; { STRUC_FROM_PKT }

*)