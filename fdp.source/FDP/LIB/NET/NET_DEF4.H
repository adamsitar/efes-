     const  {$IFDEF NODES100}
              maxNODEs     = 100;
            {$ELSE}
            {$IFDEF SERVER}        { pouzivat max sizof(byte) }
              maxNODEs     = 50;
            {$ELSE}
              maxNODEs     = 30;
            {$ENDIF} {$ENDIF}

     type   TNETnode_desc = record

             { a) popis stanice
             } typ   : Tnd_typ;   { typ stanice : FDP,RDP,MET          }
               sw    : Tnd_sw;    { typ sw      : OPL,IDD,EDD,SRD...   }
               nd    : Tnd_nd;    { pracovisko  : master/slave...      }

               pro   : TProtocol; { komunikacny protokol               }
               proL  : bool;      { kratky/dlhy                        }

             { b) adresy
             } adr   : TNETadr;   { pseudoadresa                       }
               adrr  : TRTRadr;   { RTR adresa                         }
               adrip : TIPadr;    { IP adresa                          }
               ai    : byte;      { ina adresa                         }

             { c) popis
             } name  : pchar;     { meno                               }
               inf   : pchar;     { zoznam odosielanych informacii     }

             { d) ine ako spolocne nastavenia
             } tmout : word;      { iny ako standartny time out        }

             { e)
             } indFDA : int;      { -1 => neexistuje }
               infFDA : pchar;
             end;


             TNETnode_status = record
               TrasaOK  : bool;   { vyprsal TimeOut                      }
              {SendOK   : bool;    caka sa na potvrdenie                 }

               SendTick : long;   { cas vyslania poslednej spravy        }
               RecTick  : long;   { cas prijatia poslednej spravy        }

               NodeInit : bool;   { spojenie sa obnovilo, trasa je OK    }
               Node_ON  : bool;   { stanica je zapnuta                   }
               {Node_ONp : bool;    stanica sa zapla (poslala spravu ON) }

               NextTest : word;   { interval testovania                  }
               NumbFail : byte;   { pocet neuspesnych vyslani za sebou   }

               InitEn   : bool;   { povolena inicializacia               }
               InitPoc  : byte;   { pocet neuspesnych inicializacii      }
               InitLast : real;   { cas poslednej inicializacie          }

               semaphor : bool;
             end;


     type    PNETnode = ^TNETnode;
             TNETnode = record
               desc : TNETnode_desc;
               stat : TNETnode_status;
             end;


     type    PNETnodes = ^TNETnodes;
             TNETnodes = array[0..maxNODEs-1] of TNETnode;
