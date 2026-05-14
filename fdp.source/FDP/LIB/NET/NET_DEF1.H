           { -------------------------- }
           { TNETpacket                 }
           { -------------------------- }

     const  dlz_WAN_ADR = {$IFDEF SK} 7 {$ELSE} 7 {$ENDIF}; { 4 }
            dlz_LAN_ADR = {$IFDEF SK} 7 {$ELSE} 7 {$ENDIF}; { 6 }
            odd_NET_ADR = ' ';

            {size_of_NETdata : word = size_of_NETpkt;}


     type   TNETadr = string[dlz_WAN_ADR+1+dlz_LAN_ADR];
            TNETtyp = word;
            TNETcis = word;
            TNETdlz = word;
            TNETind = byte;
            TNETpoc = byte;

            PNETpkt_head = ^TNETpkt_head;
            TNETpkt_head = record
              typ  : TNETtyp;        { typ udajov "data" }
              cis  : TNETcis;        { cislo paketu }
              ind  : TNETind;        { cislo paketu z paketov pre jedno pole dat }
              poc  : TNETpoc;        { pocet paketov jedneho pola dat }
            end;

            PNETpkt_data = ^TNETpkt_data;  { TNETpkt_data = array[0..size_of_NETdata-1] of byte; }
            TNETpkt_data = record
              dlz  : TNETdlz;        { dlzka dat pola dat }
              data : pchars;         { pole dat [pre kratkie pakety] }
              bufe : PstreamBuffer;  { adresa dat v EMS pamati [pre dlhie pakety] }
            end;

            PNETpkt = ^TNETpkt;
            TNETpkt = record
              adr  : TNETadr;        { adresy sa vyuzivaju pre routrovacie protokoly }
              ods  : TNETadr;        { nemusia chodit, daju sa zistit podla protokolu, z hlavicky alebo z dat }

              head : TNETpkt_head;
              pkt  : TNETpkt_data;

              tick : long;           { informacia o case prijmu paketu a nasledne urcenie timeout-u,
                                       ak neprisiel nasledujuci paket
                                     }
            end;

     type   TNET0pkt_head = record
              typ : TNETtyp;

              adr : TNETadr;
              ods : TNETadr;

              cis : TNETcis;
              dlz : TNETdlz
            end;

            TNET0pkt_data = array[0..size_of_NETpkt-1] of byte;
            PNET0pkt_data = ^TNET0pkt_data;

            TNET0pkt = record
              head : TNET0pkt_head;
              data : TNET0pkt_data
            end;

            (*
            TNETpkt_rec = record
              this : bool;        { pre tento uzol }
              pkt  : TNETpacket;
            end;*)


     { -------------------------- }
     { TNETBpacket                }
     { -------------------------- }

     {$IFDEF IPX}
       {$I ipx_def0.h}
     {$ENDIF}

     type   PNETBpkt_data = ^TNETBpkt_data;
            TNETBpkt_data = array[0..{$IFDEF IPX}
                                       max_IPXdata_size-1
                                     {$ELSE}
                                       size_of_NETpkt-1
                                     {$ENDIF}
                                 ] of byte;


     type   PNETBpkt   = ^TNETBpkt;
            TNETBpkt   = record
              size : int;
              data : TNETBpkt_data
            end;
