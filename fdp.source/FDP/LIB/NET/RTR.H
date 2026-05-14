     const kod_ASTERIX_02    = $2;
           kod_ASTERIX_0A    = $A;

           size_of_RTRpkt_02   = 128;
           size_of_RTRpkt{_0A} = 512;


     type  TRTRadr = byte;    { polozka pre adresaciu }

     type  TRTRpkt_header_02 = record
             prizn : byte;    { vzdy 0xf0                               }

             pocet : byte;    { pocet adries                            }
             adr   : TRTRadr; { adresa(y) kam alebo adresa odkial       }

             astrx : byte;    { cnst_ASTERIX -> premenliva dlzka spravy }

             cis   : word;    { sekvencne cislo spravy                  }
             dlz   : byte;    { velkost dat }
             kod   : byte     { kod spravy  }
           end;

           TRTRpkt_header{_0A} = record
             prizn : byte;    { vzdy 0xf0                               }

             pocet : byte;    { pocet adries                            }
             adr   : TRTRadr; { adresa(y) kam alebo adresa odkial       }

             astrx : byte;    { cnst_ASTERIX -> premenliva dlzka spravy }

             cis   : word;    { sekvencne cislo spravy                  }
             dlz   : word;    { velkost dat                             }
             kod   : byte     { kod spravy                              }
           end;


     const size_of_RTRdata_02   = size_of_RTRpkt_02 - sizeof(TRTRpkt_header_02);
           size_of_RTRdata{_0A} = size_of_RTRpkt{_0A} - sizeof(TRTRpkt_header{_0A});


     type  PRTRpkt_bin = ^TRTRpkt_bin;
           TRTRpkt_bin = array[0..size_of_RTRpkt-1]  of byte;

           PRTRdata    = ^TRTRdata;
           TRTRdata    = array[0..size_of_RTRdata-1] of byte;


           PRTRpkt_02 = ^TRTRpkt_02;
           TRTRpkt_02 = record
             head  : TRTRpkt_header_02;
             data  : TRTRdata
           end;

           PRTRpkt  = ^TRTRpkt;
           TRTRpkt  = record
             head  : TRTRpkt_header;
             data  : TRTRdata
           end;
