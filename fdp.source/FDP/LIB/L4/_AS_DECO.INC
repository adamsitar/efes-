 nechodi nic...

 function O_ASSOC.decode_data (data: pchars; size: word; var head: string; var res: string): bool;
    var   FPL : PFPL4;
          i   : int;
    begin
      decode_data:= false;
      i:= _icao_head_type(head,res);
      if i<0 then Exit;

      new_FPL4_(nil,FPL);
      case msData(i) of
        msLAM   : decode_data:= decode_LAM(data,size, head, res);

       {$IFDEF FPL4}
        {msACT   : decode_data:= decode_ACT(data,size, FPL^, res);
        msREV   : decode_data:= decode_REV(data,size, FPL^, res);}

        msCPL   : decode_CPL(data,size, FPL^, res);
        msEST   : decode_data:= decode_EST(data,size, FPL^, res);
       {$ENDIF}
      end;
      if res<>'' then decode_data:= false;
      disp_FPL4_(FPL)
    end;

