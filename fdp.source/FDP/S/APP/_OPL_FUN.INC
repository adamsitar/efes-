{$IFDEF FPL0}
 procedure O_OPL._send_message_FPLC (head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL);
     var   res  : string;
           ires : int;
     begin
      {$IFDEF FPL4}
       if not (zmeneny) then Exit;

       ires:= _icao_head_type(head,res);
       if ires>=0 then
         case msOPLdata (ires) of
           msCPL  : send_CPLc (FPL);
           msEST  : send_ESTc (FPL);
         end
      {$ENDIF}
     end;
{$ENDIF}


{$IFDEF PRS}
 procedure O_OPL.send_request_AUP(d: PDate);
     var   s: string;
     begin
       if d<>nil then s:= code_l4_date (d^) else s:= '';
       send_data(NODE_REMOTE,hd_OPL4[msAUP],'',s, nil,0, '',0);
       {$IFDEF REQUEST_AUP}
        Ts_REQUEST_AUP.is:= true;
        {save_lastREQ(Ts_REQUEST_AUP,fn_AUPupdated);}
       {$ELSE}
        Ts_REQUEST_AUP:= absTime;
       {$ENDIF}
     end;
{$ENDIF}


{$IFDEF RTZ}
 procedure O_OPL.send_request_RTZ;
     begin
       send_data(NODE_REMOTE,hd_OPL4[msRTZ],'','', nil,0, '',0);
       Ts_REQUEST_RTZ:= absTime
     end;
{$ENDIF}
