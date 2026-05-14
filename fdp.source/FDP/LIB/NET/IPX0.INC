function isIPXname(var adr: TNETadr): int;
   var   i: int;
   begin
    {$IFDEF IPX}
       adr:= uni_str(adr);
      (*{$IFDEF OPL}
       if adr='' then
          begin
            adr:= IPXnodes[IPXnode]^.name;
            isIPXname:= IPXnode
          end
       else
      {$ENDIF}*)
       if adr<>'' then
          begin
            i:= 1; while (i<maxIPX_NODEs) and ((adr<>IPXnodes[i]^.name) {or (not IPXnodes[i]^.Connected)}) do inc(i);
            if i>=maxIPX_NODEs then i:= -1
            else adr:= IPXnodes[i]^.name;
            isIPXname:= i
          end
       else isIPXname:= -1
    {$ELSE}
       isIPXname:= -1
    {$ENDIF}
   end;

{
  kontrola, ci je to vlastna adresa
}
function is_this_IPXnode(adr: TNETadr): bool;
   begin
    {$IFDEF IPX}
      adr:= uni_str(adr);
      is_this_IPXnode:= (adr = LANaddress)
    {$ELSE}
      is_this_IPXnode:= true
    {$ENDIF}
   end;



function  code_NETpkt_to_ipxIPXpkt (const Np: TNETpkt; var Lp: TIPXdpkt): bool;
   var    res  : bool;
          N0p  : TNET0pkt;
   begin
     FillChar(N0p,SizeOf(N0p),0);
     NETpkt_NET0pkt(Np,N0p);
     Lp.size:= Minimum(sizeof(N0p.head)+N0p.head.dlz,sizeof(Lp.data));
     move(N0p,Lp.data,Lp.size);
     code_NETpkt_to_ipxIPXpkt:= Lp.size=sizeof(N0p.head)+N0p.head.dlz
   end;

function  code_ipxIPXpkt_to_NETpkt (const Lp: TIPXdpkt; var Np: TNETpkt): bool;
   var    res : bool;
          N0p : TNET0pkt;
   begin
     FillChar(Np,SizeOf(Np),0);     { musi byt ! }
     FillChar(N0p,SizeOf(N0p),0);
     {$IFDEF ARCHIVE_NET_BIN}
      archive_data (path_NET,get_ARCHfn(0)+'.'+extNET,@Lp.data,Lp.size,'IPXi,',true,false);
     {$ENDIF}
     move(Lp.data,N0p,Minimum(sizeof(N0p),Lp.size));
     NET0pkt_NETpkt(N0p,Np);
     code_ipxIPXpkt_to_NETpkt:= sizeof(N0p)>=Lp.size
   end;


