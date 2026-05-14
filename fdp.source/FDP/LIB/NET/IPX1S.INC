{$F+}

{ ---------------------------------------- }
{  Zakladne sluzby IPX                     }
{ ---------------------------------------- }

{
  funkcia zisti adresu stanice v sieti
}
procedure IPX_get_lan_adress(var adresa: TIPXadr);
    var   S,O: word;
    begin
      S:= Seg(adresa);
      O:= Ofs(adresa);
      asm
        mov  BX,$09
        push ES
        push SI
        mov  ES,S  { _ES = FP_SEG(this) }
        mov  SI,O  { _SI = FP_OFF(this) }
        push BP
        call adr_AdrIPX
        pop  BP
        pop  SI
        pop  ES
      end
    end;


function IPX_adr_nil(ad: TNodeAdr): bool;
   var   i: int;
   begin
     i:= 0;
     while (i<sizeof(TNodeAdr)-1) and (ad[i]=0) do inc(i);
     IPX_adr_nil:= i>=sizeof(TNodeAdr)-1
   end;

{
  operator porovnania adries dvoch stanic
}
function IPX_adr_eq(ad1,ad2: TNodeAdr): bool;
   var   i: int;
   begin
     for i:= 0 to sizeof(TNodeAdr)-1 do
       if (ad1[i] <> ad2[i]) then
          begin
            IPX_adr_eq:= false;
            exit
          end;
     IPX_adr_eq:= true
   end;

{ ---------------------------------------- }
{  metody objektu ECB                      }
{ ---------------------------------------- }

constructor TECB.Init;
      begin
        in_use_flag:= 0;
        fragment_count:= 1;
        fragment_size:= sizeof(TIPXpkt);
        New(fragment_adress)      { GetMem(fragment_adress, fragment_size) }
      end;

destructor TECB.Done;
      begin
        Dispose(fragment_adress)  { FreeMem(fragment_adress, fragment_size) }
      end;

{
  polozky pre vyslanie musia byt uz nastavene
}
procedure TECB.send_packet;
    var   S,O: word;
    begin
      S:= Seg(self);
      O:= Ofs(self);
      asm
        mov  BX,$03
        push ES
        push SI
        mov  ES,S  { _ES = FP_SEG(this) }
        mov  SI,O  { _SI = FP_OFF(this) }
        push BP
        call adr_AdrIPX
        pop  BP
        pop  SI
        pop  ES
      end
    end;

{
  polozky pre prijem musai byt uz nastavene
}
procedure TECB.listen_for_packet;
    var   S,O: word;
          pom: byte;
    begin
      S:= Seg(self);
      O:= Ofs(self);
      asm
        mov  BX,$04
        push ES
        push SI
        mov  ES,S  { _ES = FP_SEG(this) }
        mov  SI,O  { _SI = FP_OFF(this) }
        push BP
        call adr_AdrIPX
        pop  BP
        pop  SI
        pop  ES
        mov  pom,AL
      end
    end;

{
  zrusenie udalosti
}
procedure TECB.cancel_event;
    var   S,O: word;
    begin
      S:= Seg(self);
      O:= Ofs(self);
      asm
        mov  BX,$06
        push ES
        push SI
        mov  ES,S  { _ES = FP_SEG(this) }
        mov  SI,O  { _SI = FP_OFF(this) }
        push BP
        call adr_AdrIPX
        pop  BP
        pop  SI
        pop  ES
      end
    end;


{ ---------------------------------------- }
{  pomocne funkcie                         }
{ ---------------------------------------- }

{
  metoda vrati cislo stanice podla adresy karty, inak -1
}
function get_num(uzol: TNodeAdr): int; far;
   var   i: int;
   begin
     i:= 0;
     while (i<maxIPX_NODEs) and (not IPX_adr_eq(uzol,IPXnodes[i]^.adr)) do inc(i);
     if i>=maxIPX_NODEs then i:= -1;
     get_num:= i
   end;

{
  metoda vrati cislo karty podla cisla stanice
  ak stanica nie je v tabulke, vrati 0, ak OK vrati 1
}
function get_node(node: int; var nd: TNodeAdr): int; far;
   begin
     if (node>=maxIPX_NODEs) or (node<0) then get_node:= 0
     else begin
            nd:= IPXnodes[node]^.adr;
            get_node:= 1
          end;
    end;

{
 metoda posle balik do lan
 necaka sa na uvolnenie siete, pre nesupechu vrati 0, inak 1
}
function get_socket(node: int; socket: word): word; far;
   begin
     if (socket=0) then
        if (node=0) then get_socket:= Broadcast_socket
        else get_socket:= Peer_socket
     else get_socket:= socket { Local_socket or System_socket }
   end;


{ ---------------------------------------- }
{  VYSIELANIE                              }
{ ---------------------------------------- }

function _IPX_send_packet_(node: int; adr: TNodeAdr; socket: word;
                           typ: byte; len: word; data: pbyte
                          ): int;
   var   s : string;
         i : int;
   begin
     _IPX_send_packet_:= 0;

     i:= 0;
     while (S_ECB^.in_use_flag<>0) and (i<300) do
       begin
         delay(5);
         inc(i)
       end;
     if (i>=300) then Exit;

     len:= Minimum(len,SizeOf(S_ECB^.fragment_adress^.data));

     S_ECB^.immediate_adress := adr;
     S_ECB^.fragment_size    := sizeof(TIPXhead) + len;

     S_ECB^.fragment_adress^.head.len          := len;
     S_ECB^.fragment_adress^.head.packet_type  := typ;
     S_ECB^.fragment_adress^.head.dest_network := NULL_NET;
     S_ECB^.fragment_adress^.head.dest_node    := adr;
     S_ECB^.fragment_adress^.head.dest_socket  := get_socket(node,socket);


     Move(data^,S_ECB^.fragment_adress^.data,len);
     S_ECB^.send_packet;

     {$IFDEF ARCHIVE_NET_BIN}
      s:= ''; for i:= 0 to sizeof(TEthernetAdr)-1 do s:= s+ByteToHex(adr[i]);
      archive_data (path_NET,get_ARCHfn(0)+'.'+extNET,
                    @S_ECB^.fragment_adress^.data,len,
                    'IPXo,'+cstr(node,1)+', '+'$'+delchar(s,['$'])+', '+cstr(typ,1),
                    true,false
                   );
     {$ENDIF}

     _IPX_send_packet_:= 1
   end;


function IPX_send_packet(pkt: TUSERpkt; socket: word): int;
   var   adr : TNodeAdr;
         i   : int;
   begin
      if get_node(pkt.head.num, adr)<>0 then
         IPX_send_packet:= _IPX_send_packet_(pkt.head.num, adr, socket,
                                             pkt.head.typ, pkt.head.len, pkt.data
                                            )
     else IPX_send_packet:= 0
   end;

{
  metoda vysle sluzobnu spravu pri smerovom vyslani
}
function IPX_send_message(node: int; typ: byte): int;
   var   pkt: TUSERpkt;
   begin
     pkt.head.num := node;
     pkt.head.len := 0;
     pkt.head.typ := typ;
     IPX_send_message:= IPX_send_packet(pkt,0)
   end;

{
  odoslanie dat pri smerovom vyslani
}
function IPX_send_data(node: int; data: pbyte; len: word; socket: word): int;
   var   pkt: TUSERpkt;
   begin
     pkt.head.num  := node;
     pkt.head.len  := len;
     pkt.head.typ  := ipxDATA;
     pkt.data      := data;
     IPX_send_data := IPX_send_packet(pkt, socket)
   end;

