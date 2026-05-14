 function pkt_for_this_node(const pkt: TNETpkt): bool;
    begin
      pkt_for_this_node:= eq_str(pkt.adr,self_NETadr(pkt.ods))
    end;

 function pkt_from_this_node(const pkt: TNETpkt): bool;
    begin
      pkt_from_this_node:= eq_str(pkt.ods,self_NETadr(pkt.adr))
    end;


{ Dekoduje, odkial bol plan prijaty a nastavi priznak,
  ze data su od zdroja "nd".
  V pripade, ze "nd" je hlavnym alebo zaloznym serverom,
  nastavi, ze paket pochadza i od zalozneho.

  Inym (lepsim) riesenim by bolo sirenie fyzickej adresy
  aktivneho servera. Zatial neodladene.
  Teraz treba posielat i na hlavny i na zalozny server
  (najlepsie "distribute").
}

 function  rec_pkt_(nd: int; var rec: Tplan_rec; what: char; bck: bool): bool;
     var   i: int;
     begin
       if (nd>-1) then
          begin
            rec_pkt_:= true;
            rec[nd]:= what;
            if bck and (NODEs^[nd].desc.sw in [SERVER,BSERVER]) then
               begin
                 for i:= 0 to NODEpoc-1 do
                   if NODEs^[i].desc.sw in [SERVER,BSERVER] then
                      rec[i]:= what
               end
          end
       else rec_pkt_:= false
     end;

 procedure rec_from_(from: TNETadr; var rec: Tplan_rec; what: char; bck: bool);
     var   nd: int;
     begin
       fillchar(rec,sizeof(rec),no_ack);
       nd:= is_NETadr(from);
       rec_pkt_(nd,rec,what,bck)
     end;


 function  rec_pkt (nd: int; var rec: Tplan_rec; what: char): bool;
     begin
       rec_pkt:= rec_pkt_(nd,rec,what,true)
     end;

 procedure rec_data (from: TNETadr; var rec: Tplan_rec);
     begin
       rec_from_(from,rec,is_rec,true)
     end;

 procedure rec_copy (src: Tplan_rec; var desc: Tplan_rec);
     var   i: int;
     begin
       for i:= 0 to sizeof(Tplan_rec)-1 do if src[i]<>no_ack then desc[i]:= src[i];
     end;


{$IFDEF DATA_BIN}
{ vyhladanie pozicie v datach
}
 function pkt_split(const pkt: TNETpkt_data; pos: int): word;
    var   i,j : int;
    begin
      i:= 0; j:= 0;
      while (i<pkt.dlz) and (j<>pos) do
        begin
          if pkt.data^[i]=ODD_SPR then inc(j);
          inc(i)
        end;
      if i>0 then j:= i-1 else j:= 0;
      pkt_split:= j
    end;
{$ENDIF}