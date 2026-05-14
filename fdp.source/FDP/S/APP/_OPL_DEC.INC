(*
 function O_OPL.process_data (src: TPKT_SRC;
                              data: pchars; size: word;
                              var head: string;
                              var resh,resd: string
                             ): bool;
    var   s : string;
    begin
      resh:= ''; resd:= ''; head:= '';
      s:= cut_(init_str(data,size)); { s[0]:= chr(minimum(size,sizeof(s)-1)); move(data^,s[1],ord(s[0])); }
      if s=HeartBeat then process_data:= false
      else process_data:= inherited process_data(src,data,size,head,resh,resd)
    end;
*)

{ Mozne headre :
   $(ESTMI/PL001-KAL511...
  ÿ$(FPLPL/MI792-F4205-...

   #RTZ(ID...

   #AUP(01-LKR35   -...
   #AUP/001120(01-LKR35   -...

   $(ASMPL/MI432-ACT-LKR35-...
}

 function O_OPL.decode_header (data: pchars; size: word;
                               zac,kon: word;
                               var header: string;
                               var res: string;
                               decode: bool
                              ): bool;
    var   bres: bool;
    begin
      decode_header:= false;
      res:= '';
      header:= get_str_(data,size,1,[SOH,STX], bres, sizeof(header)-1);
      if (header='') then Exit;

     { $(FPLPL/MI792-F4205-... }
      if     (MES = header[1])
         and (icao_STD = header[2])
             then decode_header:= inherited decode_header (data,size,zac,kon,header,res, decode)

     { #AUP/001120(01-LKR35... }
      else if (header[1] in [QRY,MES]) then decode_header:= true
    end;


 function O_OPL.decode_head (header: string;
                             var head: string;
                             var res: string
                            ): bool;
    begin
     { #AUP/001120(01-LKR35... }
      if header[1] in [QRY,MES] then
         begin
           head:= getstr(copy(header,2,length(header)-1),1,[SOH,STX]);
           head:= getstr(head,1,[icao_NXT]);
           decode_head:= true
         end
     { FPLPL/MI792-F4205-... }
      else decode_head:= inherited decode_head(header,head,res)
    end;


 {function O_OPL.decode_head (header: string
                              var head: string;
                              var res: string
                             ): bool;
    begin
      head:= getstr(header,1,icao_NXT);
      head:= copy(head,1,kod_head);
      if head='' then res:= 'Cannot identify message type.';
      decode_head:= res=''
    end;}


 function O_OPL.decode_data  (data: pchars; size: word;
                              header: string;
                              var head: string;
                              var res: string
                             ): bool;
    var   i : int;
         {$IFDEF FPL4}
          FPL : PFPL4;
         {$ENDIF}
    begin
      decode_data:= false;

      { kontrola na prazdne polia
      } i:= 1; while (i<size) do
         if (data^[i-1]=icao_ARR) and (data^[i]=icao_ARR) then
            begin
              res:= 'Empty array "--" in message.';
              Exit
            end
         else inc(i);

      { zvyknu chodit bludy alebo nestandartne oddelovace
      } for i:= 0 to size-1 do if data^[i]>'z' then data^[i]:= icao_NXIT;


      i:= _icao_head_type(head,res);
      if i<0 then Exit;

      {$IFDEF FPL4}
       new_FPL4_(nil,FPL);
      {$ENDIF}
      case msOPLdata(i) of
         msLAM   : decode_data:= decode_LAM(data,size, header, res);

        {$IFDEF FPL0} {$IFDEF FPL4}
         msFPL   : decode_data:= decode_FPL(data,size, FPL^, res);
         msCHG   : decode_data:= decode_CHG(data,size, FPL^, res);
         msCNL   : begin decode_data:= true; decode_CNL(data,size, FPL^, res); end;
         msDLA   : decode_data:= decode_DLA(data,size, FPL^, res);
         msCLR   : decode_data:= decode_CLR(data,size, FPL^, res);

         msABI   : decode_data:= decode_ABI(data,size, FPL^, res);
         msACT   : decode_data:= decode_ACT(data,size, FPL^, res);

         msCPL   : {decode_data:=} decode_CPL(data,size, FPL^, res);
         msEST   : decode_data:= decode_EST(data,size, FPL^, res);
         msDEP   : decode_data:= decode_DEP(data,size, FPL^, res);
         msARR   : decode_data:= decode_ARR(data,size, FPL^, res);
        {$ENDIF} {$ENDIF}

        {$IFDEF PRS}
         msAUP,
         msAUM  : decode_data:= decode_AUP(data,size, header,head, res);
         msASM  : decode_data:= decode_ASM(data,size, res);
        {$ENDIF}

        {$IFDEF RTZ}
         msRTZ   : decode_data:= decode_RTZ(data,size,res);
        {$ENDIF}
      end;
      if res<>'' then decode_data:= false;

      {$IFDEF FPL4}
       disp_FPL4_(FPL)
      {$ENDIF}
    end;
