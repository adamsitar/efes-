{$IFDEF SOCKET}

   type  TINetAdr = array[0..3] of byte;
         TNodeAdr = TEthernetAdr;
         TIPXAdr  = record
           net  : TINetAdr;
           node : TNodeAdr
         end;


   type  TIPXhead = record
           CheckSum          : word;
           Len               : word;   { prijem - dlzka Data dostanem, inak plnim }
           transport_control : byte;
           packet_type       : byte;   { 4 data, 2 odpoved, 0 otazka; nastavit pri odoslani }

           dest_network      : TINetAdr;
           dest_node         : TEthernetAdr;
           dest_socket       : word;

           source_net        : TINetAdr;
           source_node       : TEthernetAdr;
           source_socket     : word;
         end;

         PIPXpkt = ^TIPXpkt;
         TIPXpkt = record
           head : TIPXhead;
           data : TIPXdata
         end;


   type  TUSERhead = record
           num : int;  { cislo stanice od, do ktorej sa posiela }
           len : word; { dlzka packetu bez hlavicky }
           typ : byte  { typ packetu }
         end;

         TUSERpkt = record
           { struktura uzivatelskeho packetu pouzita pre komunikaciu na vyssej urovni }
           head: TUSERhead;
           data: Pbyte;     { smernik na pole dat }
         end;


   const NULL_NET  : TINetAdr = (0,0,0,0);
         NULL_NODE : TNodeAdr = ($00,$00,$00,$00,$00,$00);
         BROADCAST : TNodeAdr = ($FF,$FF,$FF,$FF,$FF,$FF);


   {$IFDEF IPX2}
    const Broadcast_socket = $0051;   { cislo tabulky ECB , hi,lo, aby sa spracovalo lo,hi  }
          Peer_socket      = $0050;
          Local_socket     = $0052;
   {$ELSE}
    const Broadcast_socket = $0051;   { vsesmerovy prijem                       }
          Peer_socket      = $0151;   { smerovy prijem                          }
          System_socket    = $0251;   { prijem systemovych sprav o konfiguracii }
          Local_socket     = $0351;   { vysielanie                              }
   {$ENDIF}



   type  TIPXInd    = array[0..1]  of word;

   var   AdrIPX     : TIPXInd;             { adresa IPX v pamati }
         adr_AdrIPX : ^TIPXInd;


   type  PECB = ^TECB;
         TECB = object
           link_adress      : pointer;
           ESR_adress       : pointer;     { s,r - obsluzna rutina }

           in_use_flag      : byte;
           compl_code       : byte;
           socket_number    : word;

           IPX_workspace    : TINetAdr;
           driver_workspace : array[0..11] of byte;
           immediate_adress : TEthernetAdr;

           fragment_count   : word;        { s,r ma byt nastaveny na 1          }
           fragment_adress  : PIPXpkt;     { s,r adresa vyrovnavacieho buffera  }
           fragment_size    : word;        { s,r velkost vyrovnavacieho buffera }

           constructor Init;
           destructor  Done;               { disp fragment_adress;              }

           procedure   send_packet;
           procedure   listen_for_packet;
           procedure   cancel_event;
         end;


   const S_ECB  : PECB = nil;
         R_ECB  : array[0..2] of PECB = (nil,nil,nil);


{$ELSE}

   type  Dva     = array[0..1]  of byte;
         Ctyri   = array[0..3]  of byte;
         Dvanact = array[0..11] of byte;

   type  _Socket = array[0..1]  of byte;
         _AdrIPX = array[0..1]  of word;

   type  _IPXBuf = record
           CheckSum     : Dva;
           Len          : Dva;    { prijem - dlzka Data dostanem, inak plnim }
           TrContr      : byte;
           PacketType   : byte;   { 4 - data, 2 - odpoved, 0 - otazka-init }
           DestNet      : Ctyri;
           DestNode     : TEthernetAdr;
           DestSocket   : _Socket;
           SourceNet    : Ctyri;
           SourceNode   : TEthernetAdr;
           SourceSocket : _Socket;
           Data         : TIPXdata;
         end;

         TabECB = record
           LinkAddress     : pointer;
           ESRAdr          : pointer;
           InUse           : byte;
           Compl           : byte;
           Socket          : _Socket;
           IPXWorkspace    : Ctyri;
           DriverWorkSpace : Dvanact;
           Adresa          : TEthernetAdr;
           BufCount        : word;
           BufAdr          : pointer;
           BufSize         : word;
         end;


   const NulNameNet : ctyri = (0,0,0,0);

   var   AdrIPX     : _AdrIPX;    { adresa IPX v pamati }
         adr_AdrIPX : ^_AdrIPX;

         SegECB     : word;
         OfsECB     : word;

         ECB        : array[0..1,0..maxIPX_NODEs] of TabECB;
         IPXBuf     : array[0..1,0..maxIPX_NODEs] of _IPXBuf;
         SocketOpen : array[0..1,0..maxIPX_NODEs] of bool;
         CSocket    : array[0..1,0..maxIPX_NODEs] of _Socket;

{$ENDIF}