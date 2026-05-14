{
  Wait for an incoming call
}
function X25_listen(_local_name : Network_Service_Access_Point;
                    _remote_nua : Network_User_Address): byte;
   var   pkt : P_TSFpacket;
         res : int;
         i   : word;
         s_t : long;
   begin
     X25_listen:= 0;

     New(pkt);
     init_call_pkt(pkt^,_local_name);

     pkt^.ncb.name := _local_name;                { Put our name in the correct packet fields }
                                                  { Use '*   ...' NUA to accept any incoming call }
     if _remote_nua='' then _remote_nua:= InsChar('*',SizeOf(_remote_nua),' ',1);
     with pkt^.ncb.cs_chain do Move(_remote_nua,cs_callname,Minimum(sizeof(_remote_nua),sizeof(cs_callname)));
     pkt^.ncb.command:= NCB_X25_ELISTEN;
     pkt^.ncb.sl.length:= sizeof(pkt^.conn.x_cr);  { Must set the length large enough to accept }
                                                   { the passed extended connection record      }
     res:= call_API(pkt^.ncb);
     if (res = 0) then
        begin
          s_t:= GetTicks;
          while (pkt^.ncb.cmd_cplt=NCB_ERR_PENDING) and (not TimeOut(s_t,GetTicks, X25_LISTEN_TIME_OUT)) do
            begin
              Main0
            end;
          if (pkt^.ncb.cmd_cplt=0) then X25_listen:= pkt^.ncb.lsn
        end;

     Dispose(pkt)
   end;


{
  Make an X25 call, and wait for a response
}
function  X25_call(_local_name,
                   _remote_name : Network_Service_Access_Point;
                   _remote_nua  : Network_User_Address;
                   _user_data   : Pbytes; _user_len: byte
                   ): byte;
   var    pkt : P_TSFpacket;
          res : int;
          i   : word;
          s_t : long;
   begin
     X25_call:= 0;

     New(pkt);
     init_call_pkt(pkt^,_local_name);

     pkt^.ncb.name      := _local_name;            { Put our name in the correct packet fields }
     pkt^.conn.x_cr.name:= _remote_name;
     pkt^.conn.x_cr.nua := _remote_nua ;           { Put destination NUA in the packet }

     with pkt^.conn.x_cr do
        if (_user_data<>nil) and (_user_len>0) then
           begin
             cud_len:= Minimum(_user_len,sizeof(cud));
             Move(_user_data^,cud,cud_len)
           end
        else pkt^.conn.x_cr.cud_len:= 0;

     pkt^.ncb.sl.length := sizeof(pkt^.conn.x_cr); { Put length of connection record in to the length field          }
                                                   { The length field MUST always be correct for the type of command }

     pkt^.ncb.command:= NCB_X25_ECALL;
     res:= call_API(pkt^.ncb);
     if (res = 0) then
        begin
          s_t:= GetTicks;
          while (pkt^.ncb.cmd_cplt=NCB_ERR_PENDING) and (not TimeOut(s_t,GetTicks, X25_CALL_TIME_OUT)) do
            begin
              Main0
            end;
          if (pkt^.ncb.cmd_cplt=0) then X25_call:= pkt^.ncb.lsn
        end;

     Dispose(pkt)
   end;


{
  Disconnect a session
}

procedure X25_disconnect;
    begin
    end;


{
  int  result;


  x25_init_data_pkt (p, local_session_num);
  PKT_COMMAND = NB_WAIT_HANGUP;    /* Note the hangup issued in wait mode */
  result = nb_issue (&p->ptr_ncb); /* Issue the hangup */
  if (result != 0)                 /* Check the result */
    printf ("\nImmediate error %x from nbw_hangup", result);
  /* fi */
}

