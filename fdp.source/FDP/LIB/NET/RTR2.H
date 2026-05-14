     type  TRTRadr = word;

           TRTRpkt_head = record
             prizn : byte;    { cnst_RTR }

             pocet : byte;    { pocet adries                            }
             adr   : TRTRadr; { adresa(y)                               }
             ods   : TRTRadr; {                                         }

             typ   : word;    { typ spravy                              }
             cis   : word;    { sekvencne cislo spravy                  }
             dlz   : word;    { velkost dat                             }
           end;


     const size_of_RTRpkt  = size_of_NETpkt;
           size_of_RTRdata = size_of_RTRpkt - sizeof(TRTRpkt_head);

     type  TRTRdata = array[0..size_of_RTRdata-1] of byte;
           TRTRpkt  = record
             head  : TRTRpkt_head;
             data  : TRTRdata
           end;

           {PRTRdata = ^TRTRdata;}
           PRTRpkt  = ^TRTRpkt;


     const size_of_RTRdata_bin = sizeof(TRTRpkt); { musi = size_of_NETpkt }

     type  TRTRpkt_bin = array[0..size_of_RTRdata_bin-1] of byte;
           PRTRpkt_bin = ^TRTRpkt_bin;


     type  TRTR_heartbeat = record
             kod : byte;
             ods : TRTRadr;
             typ : word
           end;

     const rtr_RTR = 1;
           rtr_FDP = 4;
