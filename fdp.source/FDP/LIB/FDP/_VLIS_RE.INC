 function  VLIS_fn(fn: string): string;
    begin
      VLIS_fn:= pathPRN_VLIS+cut_(fn)+'.'+extPRN_VLIS
    end;

 procedure _pkt_VLIS(var pkt: TNETpkt);
     var   fn,fr: string;
     begin
       fn:= NETreceive_file (pkt,fn,fr,@VLIS_fn,false,true,true,true);
       NETdistribute_file ([FDP,FDP0NX,FDP0],[],[MASTER,SLAVE],
                           pkt.head.typ, fn,
                           inf_VLIS, net_flag_NIL,
                           ispath_VLIS,isext_VLIS,true,true,true
                          );
       {$IFNDEF SERVER}
        {if hlas_PRN_VLIS then} reports_FDP^.save_rep(spr_SAY,'','',tit_rec_PRN_VLIS+'('+cut_(decode_date_fn(fn))+').',0,nil)
       {$ENDIF}
     end;

  procedure _ack_VLIS (key: string; rec: Tplan_rec; fdp: bool; nd: int);
      begin
        file_rec (nd,key,true,is_ack,false)
      end;

