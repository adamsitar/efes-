 procedure _fdp_co_ordinate_procedure (src: fdp_src; dst: set_fdp_src;
                                       typ: TNETtyp; head: Thead_ICAO;
                                       zmeneny: bool;
                                       var plan
                                      );
     begin
     end;


 function get_msg_adr (head: string; var prty,adr: string): bool;
    var   s : string;
          i : int;
    begin
      adr:= ''; prty:= '';
      s:= read_cfg_str_(TLGcfg,head,'');
      if s<>'' then
         begin
           prty:= getstr(s,1,[icao_NXIT]);
           adr := ''; for i:= 2 to getstritems(s,[icao_NXIT]) do adr:= adr + icao_NXIT+ getstr(s,i,[icao_NXIT]);
           adr:= cut_(adr)
         end;
      get_msg_adr:= (adr<>'') and (prty<>'')
    end;

 function _proc_send_TLG (prty,adr,head: string; data: pchars; size: word): string;
    begin
      if p_proc_send_TLG <> nil
         then _proc_send_TLG:= tproc_send_TLG(p_proc_send_TLG)(prty,adr,head, data,size)
         else _proc_send_TLG:= ''
    end;
