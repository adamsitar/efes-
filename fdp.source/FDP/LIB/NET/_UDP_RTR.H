            { parametre sluziace pre identifikaciu paketu
            }
      type   TRTCpkt_id   = record
               prizn : byte;       { zdroj      : kod_RTR_PKT, kod_CISCO_PKT, kod_SIM_PKT }
               typ   : word;       { typ spravy : rsprACK ... rspr_RTB2,rspr_RT_          }
             end;

             TRTCpkt_head = TNETpkt_head;


            { data spracovane od/pre UDP
            }
      const  size_of_RTCdata =    size_of_NETpkt
                               - (   sizeof(TRTCpkt_id)
                                   + sizeof(TRTCpkt_head)
                                 );

      type   TRTCpkt_data = array[0..size_of_RTCdata-1] of byte;

             PRTCpkt  = ^TRTCpkt;
             TRTCpkt  = record
               id   : TRTCpkt_id;
               head : TRTCpkt_head;  { Polozky head a ind su oddelene kvoli kompatibilite so starym protokolom bez ind }

               dlz  : word;
               data : TRTCpkt_data;
             end;


      function code_NETpkt_to_RTCpkt (const Np   : TNETpkt;
                                      var   Up   : TUDPdata;
                                      var   size : word;
                                      typ : word
                                     ): word;
