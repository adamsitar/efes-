 procedure O_EXT._send_co_ordinate_message (src: fdp_src; dst: set_fdp_src;
                                            typ: TNETtyp; head: Thead_ICAO;
                                            zmeneny: bool;
                                            var plan
                                           );
     begin
     end;


 procedure O_EXT.send_co_ordinate_message (src: fdp_src; dst: set_fdp_src;
                                           typ: TNETtyp; head: Thead_ICAO;
                                           zmeneny: bool;
                                           var plan
                                          );
     begin
       if (src=src_type) or ((dst<>[]) and (not (src_type in dst))) then Exit;
       _send_co_ordinate_message (src,dst,typ,head,zmeneny,plan);
     end;

