{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   kodovanie pre siet routerov CISCO
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
function code_NETpkt_to_RTCpkt (const Np   : TNETpkt;
                                var   Up   : TUDPdata;
                                var   size : word;
                                typ        : word
                               ): word;
   var   id  : TRTCpkt_id;
         dlz : word;
         pL  : bool;
   begin
     pL:= is_proL(Np.adr) and (Np.head.poc>0);
     { NX zatial ocakava kratky za kratky a dlhy za dlhy }

     fillchar(Up,sizeof(Up),0);
     id.prizn := ast_CISCO_PKT;
     id.typ   := typ;
     if pL then inc(id.typ,rspr_LONGoffs);

     size := 0;
     Move(id,Up[size],sizeof(id));                   inc(size,sizeof(id));
     Move(Np.head.typ,Up[size],sizeof(Np.head.typ)); inc(size,sizeof(Np.head.typ));
     Move(Np.head.cis,Up[size],sizeof(Np.head.cis)); inc(size,sizeof(Np.head.cis));
     if id.typ in set_rspr_FDP_L then
        begin
          Move(Np.head.ind,Up[size],sizeof(Np.head.ind)); inc(size,sizeof(Np.head.ind));
          Move(Np.head.poc,Up[size],sizeof(Np.head.poc)); inc(size,sizeof(Np.head.poc));
        end;

     dlz:= Minimum(Minimum(Np.pkt.dlz,sizeof(Up)-size),size_of_NETdata);
     if Np.pkt.data<>nil then
        begin
          Move(Np.pkt.data^, Up[size], dlz);
          inc(size,dlz)
        end;

     if (id.typ in [rspr_RT_,rspr_LRT_]) then
        begin
          if not (size+2*sizeof(TNETadr) <= sizeof(Up)) then size:= size{of(Up)}-2*sizeof(TNETadr);
          Move(Np.adr,Up[size],minimum(1+length(Np.adr),sizeof(TNETadr)));
          inc(size,sizeof(TNETadr));
          Move(Np.ods,Up[size],minimum(1+length(Np.ods),sizeof(TNETadr)));
          inc(size,sizeof(TNETadr))
        end;

     code_NETpkt_to_RTCpkt:= size
   end;


{ Predpoklad (dolezity) : ze Np je vynulovany...; ale polozky s adrsou su uz nastavene
}
function decode_RTCpkt_to_NETpkt (const Up : TUDPdata; size : word;
                                  var Np : TNETpkt
                                 ): bool;
   var   id : TRTCpkt_id;
         p,dlz : word;
   begin
     Np.pkt.data:= nil;
     p:= 0;

     Move(Up[p],id,sizeof(id));                   inc(p,sizeof(id));

     Move(Up[p],Np.head.typ,sizeof(Np.head.typ)); inc(p,sizeof(Np.head.typ));
     Move(Up[p],Np.head.cis,sizeof(Np.head.cis)); inc(p,sizeof(Np.head.cis));
     if id.typ in set_rspr_FDP_L then
        begin
          Move(Up[p],Np.head.ind,sizeof(Np.head.ind)); inc(p,sizeof(Np.head.ind));
          Move(Up[p],Np.head.poc,sizeof(Np.head.poc)); inc(p,sizeof(Np.head.poc));
        end;

     dlz:= N(size-p);
     if (id.typ in [rspr_RT_,rspr_LRT_]) then
        begin
          Move(Up[size-2*sizeof(TNETadr)], Np.adr, sizeof(TNETadr));
          Move(Up[size-sizeof(TNETadr)],   Np.ods, sizeof(TNETadr));
          dec(dlz,2*sizeof(TNETadr))
        end;

     new_NETpkt_data (@Up[p],dlz, Np.pkt);

     decode_RTCpkt_to_NETpkt:= true
   end;
