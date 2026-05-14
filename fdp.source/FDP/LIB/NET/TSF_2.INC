{
  Add "_local_name" to the local list

  - Ak pouzijem NB_ADD_EXTENDED_NAME, pri CALL REQUEST bude kontrolovane pole Call User Data

}
function  O_TSF.add_local_name(_local_name : Network_Service_Access_Point;
                               _local_nua  : Network_User_Address;
                               _MODE       : byte
                              ): byte;
    var   pkt : P_TSFpacket;
          res : int;
          s   : string;
    begin
      New(pkt); init_pkt(pkt^);

      pkt^.ncb.sl.service:= _MODE;
      pkt^.ncb.command:= NCB_ADD_SPECIAL_NAME_WAIT; { The command to the API                              }

      pkt^.ncb.name:= _local_name;                  { Put our name in to the packet name field            }
      with pkt^.ncb.cs_chain do                     { Put the associated NUA in the packet callname field }
           Move(_local_nua,cs_callname,Minimum(length(_local_nua)+1,sizeof(cs_callname)));

      res:= call_API(pkt^.ncb);                     { Issue the NetBIOS packet to the API }
      if res<>0 then
         begin
           case res of
             13   : s:= 'TSF, Xú25 - Duplicate local name added.';
             else   s:= 'TSF, Xú25 - Add Name failed; return code = '+IntToStr(res,0,0)+'.'
           end;
           RunError(s)
         end;

      add_local_name:= {local_session_num:= } pkt^.ncb.num;
      Dispose(pkt)
    end;

{
  Delete "local_session_num" from the list
}
procedure O_TSF.delete_local_name(_local_session_num: byte);
    var   pkt : P_TSFpacket;
          res : int;
    begin
      New(pkt);
      init_data_pkt(pkt^, _local_session_num);
      pkt^.ncb.command:= NCB_DELETE_NAME_WAIT;
      res:= call_API(pkt^.ncb);
      Dispose(pkt)
    end;

