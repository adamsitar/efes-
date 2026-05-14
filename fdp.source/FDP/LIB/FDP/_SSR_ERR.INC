
 procedure err_save (ires: int; code,flight,res, src: string);
     var   err: string;
     begin
       err:= codeERR_SSR (ires, code,flight,res);
       reports_SSR^.save_rep (spr_SSR_ERR,src,flight,res,length(err),@err[1]);
       is_SSR_ERR:= true;
     end;


 procedure _pkt_SSR_ERR_REC (const pkt: TNETpkt);
     var   error,code,flight,res: string;
           ires: int;
     begin
       decode_msg (pkt,@error);
       decodeERR_SSR (error, ires,code,flight,res);
       err_save (ires, code,flight,res, pkt.ods);
     end;


 procedure _pkt_SSR_ERR_COR (const pkt: TNETpkt);
     var   sres: string;
           ires: int;
     begin
       {decode_msg (pkt,@sres);
       reports_FDP^.save_rep (spr_SSR_COR,pkt.ods,'',sres,pkt.pkt.data,pkt.pkt.dlz);
       }
     end;
