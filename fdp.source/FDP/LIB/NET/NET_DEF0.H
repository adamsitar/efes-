     const  size_of_NETpkt  = {$IFDEF PCTCP} 512  { 1024 }   { = size_of_RTRpkt; + TNETpkt_header < size_of_IPXpkt }
                              {$ELSE}        512
                              {$ENDIF};