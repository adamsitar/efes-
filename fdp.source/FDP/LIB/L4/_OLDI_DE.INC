{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   prijem dat a detekcia dat
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
{
  Je povolene zoskupene viacerych sprav v jednom pakete
}
function  O_OLDI.extract_data (data: pchars; size: word; var C, pSTX,pSTD,pETX: word): msSystem;
   var    is_SOH, is_STX, is_ETX : bool;
          len  : word;              { End Of Header }
          head : string;
          ms,m : msSystem;
   begin
     is_SOH:= false; is_STX:= false; is_ETX:= false; pSTD:= 0;

   { 1. najdenie paketu ohraniceneho _STX ... _ETX }
     while (C < size) and (not is_ETX) do
       begin
         if      (data^[C] = _SOH) then
                 begin
                   is_STX:= false;
                   is_SOH:= true
                 end

         else if (data^[C] = _STX) then
                 begin
                   if is_SOH then is_SOH:= false
                   else begin
                          is_STX:= true;
                          pSTX:= C
                        end
                 end

         else if is_STX and (data^[C] = _ETX) then
                 begin
                   is_ETX:= true;
                   pETX:= C
                 end;

         if (data^[C] = icao_STD) and (pSTD=0) then pSTD:= C;
         inc(C)
       end;

   { 2. identifikacia typu spravy obsiahnutej v pakete }
     if is_STX and is_ETX then
        begin
          if pSTD=0 then pSTD:= pETX;
          len:= Minimum(sizeof(head)-1, N(pSTD-pSTX+1));
          Move(data^[pSTX],head[1],len);
          head[0]:= chr(len);
          head[len]:= #0;

          ms:= msOther;
          for m:= msStartUp to hdUser do
              if StrLComp(@head[1],headSystem[m],N(len-1))=0 then
                 begin
                   ms:= m;
                   break
                 end;
          if (ms=msOther) and (strpos(@head[1],messStat_) = @head[1]) then ms:= hdStat

        end
     else ms:= msOther;

     extract_data:= ms
   end;

{
  spracuje operatorsku spravu
}
procedure O_OLDI.decode_user (data: pchars; size: word; var header: string);
    var   t : string;
    begin
      if (MainApp=nil) then Exit;

      t[0]:= chr(Minimum(size-length(messUser_)-1,sizeof(t)-1));
      Move(data^[length(messUser_)],t[1],ord(t[0]));
      Beep1;
      MainApp^.writeln(' '+t, cl_MESS , arch_MESS, (p_utc=nil) or (bool(p_utc^)))
    end;


{
  prijem dat, ich identifikacia a spracovanie
}
function  O_OLDI.process_data (src: TPKT_SRC;
                               data: pchars; size: word;
                               var header: string;
                               var resh,resd: string
                              ): bool;

    var   P,C, pSTX,pSTD,pETX : word;
          D : pchars;
          head, s : string;
          prev_stat : stat_OLDI;

    begin
     {$IFDEF DEBUG}
      {writeln_pkt(data,size, '*','3',cl_ERR,false,true);}
      {s:= 'process'; writeln_pkt(@s[1],length(s), '!','',white,false,true);}
     {$ENDIF}

      prev_stat:= stat;
      resh:= ''; resd:= '';
      process_data:= false; { LAM sa vysiela z vnutra tejto fcie, nie po jej opusteni }

     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       nastavenie prijimacieho timera
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     }
      P:= size; GetMem(D,P); Move(data^, D^, P);
      C:= 0;               { detekovanie jednotlivych sprav, spracovanie a zaradenie dat }
      while (C < P) do
        begin
          case extract_data(D,P,  C, pSTX,pSTD,pETX) of

            msStartUp     : handle_OLDI_event(R_Startup,nil);
            msHeartBeat   : handle_OLDI_event(R_Heartbeat,nil);
            msShutDown    : handle_OLDI_event(R_Shutdown,nil);

            hdData        : if    {$IFNDEF DEBUG}
                                    (stat = DATA_READY_STATE)
                               and
                                  {$ENDIF}
                                   decode_header (@D^[pSTD],pETX-pSTD+1, 0,pETX-pSTD+1{,pSTX,pETX}, header,resh, false)
                               and decode_head   (header, head, resh) then
                                   begin
                                     handle_OLDI_event(R_data,nil);
                                     if decode_data (@D^[pSTD],pETX-pSTD+1, header,head, resd) then
                                        begin
                                          if    (not lam_pred_spracovanim)
                                             or (prev_stat<>DATA_READY_STATE)
                                             then send_LAM(data,size, header)
                                        end;
                                   end;

            hdUser,hdStat : {$IFNDEF DEBUG}
                              if (stat = DATA_READY_STATE) then
                            {$ENDIF}
                               begin
                                 handle_OLDI_event(R_data,nil);
                                 decode_user(@D^[pSTX],pETX-pSTX+1, header)
                               end;

            msOther       : begin
                              {writeln_pkt(@D^[pSTX],pETX-pSTX+1, arch_ERR,'OLDI DECODE ERROR - ',cl_ERR,false,true)
                              }
                            end;
          end
      end;
      FreeMem(D,P)
    end;


 procedure O_OLDI.LAM_received_pkt (data: pchars; size: word);
     var   P,C, pSTX,pSTD,pETX : word;
           D : pchars;
           head,header,res : string;

     begin
       if (not lam_pred_spracovanim) or (stat <> DATA_READY_STATE) then Exit;

       res:= '';
       P:= size; GetMem(D,P); Move(data^, D^, P);
       C:= 0;
       while (C < P) do
         begin
           case extract_data(D,P,  C, pSTX,pSTD,pETX) of

            hdData         : if     decode_header (@D^[pSTD],pETX-pSTD+1, 0,pETX-pSTD+1, header,res, false)
                                and _is_to_LAM    (@D^[pSTD],pETX-pSTD+1, header)
                                  then send_LAM (data,size, header);

           end
       end;
       FreeMem(D,P)
     end;

