function time_out_nd(nd: int): word;
   begin
     if (nd>-1) and (nd<NODEpoc) then
        begin
         {$IFDEF BACKUP}
           if nd=SERVERnode then time_out_nd:= SERVERtimeout*18
           else
         {$ENDIF}
         {$IFDEF MASTER}
           if nd=BACKUPnode then time_out_nd:= SERVERtimeout*18
           else
         {$ENDIF}
          time_out_nd:= NODEs^[nd].desc.tmout
        end
     else time_out_nd:= tmout_ACK
   end;


{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û VYSLEDKY                                                 Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

function NETres(res: byte): bool;
   begin
     NETres:= res in[netRES_OK,netADDR_OK,netACK_OK, ipxRES_OK,x25RES_OK]
   end; { NETres }


function NETres_(res: bool): TPlanRec;
   begin
     if res then NETres_:= is_ack else NETres_:= no_ack
   end; { NETres }
