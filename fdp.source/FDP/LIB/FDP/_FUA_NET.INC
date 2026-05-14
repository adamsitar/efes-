 function  AUP_fn(fn: string): string; far;
    begin
      AUP_fn:= pathAUP+cut_(fn)
    end;

 procedure _pkt_AUP(var pkt: TNETpkt);
     var   fn,fr: string;
     begin
       fn:= NETreceive_file (pkt,fn,fr,@AUP_fn,false,true,true,true);
       NETdistribute_file ([FDP],[],[SLAVE],
                           pkt.head.typ, fn,
                           inf_FUA, net_flag_NIL,
                           false,true,true,true,true
                          );
       {$IFNDEF SERVER}
        {if hlas_AUP then} reports_FDP^.save_rep(spr_SAY,'','',tit_rec_AUP+'('+cut_(fn)+').',0,nil)
       {$ENDIF}
     end;


 function  UUP_fn(fn: string): string; far;
    begin
      UUP_fn:= pathUUP+cut_(fn)
    end;

 procedure _pkt_UUP(var pkt: TNETpkt);
    var   fn,fr: string;
    begin
      fn:= NETreceive_file (pkt,fn,fr,@UUP_fn,false,true,true,true);
      NETdistribute_file ([FDP],[],[SLAVE],
                          pkt.head.typ, fn,
                          inf_FUA, net_flag_NIL,
                          false,true,true,true,true
                         );
      {$IFNDEF SERVER}
        {if hlas_UUP then} reports_FDP^.save_rep(spr_SAY,'','',tit_rec_UUP+'('+cut_(fn)+').',0,nil)
      {$ENDIF}
    end;


 procedure _ack_AUP (key: string; rec: Tplan_rec; fdp: bool; nd: int);
     begin
       file_rec (nd,key,true,is_ack,false)
     end;

 procedure _ack_UUP (key: string; rec: Tplan_rec; fdp: bool; nd: int);
     begin
       file_rec (nd,key,true,is_ack,false)
     end;
