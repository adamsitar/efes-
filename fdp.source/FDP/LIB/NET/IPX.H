    { --------------------------------------------- }
    { TIPXnode - buffer pre spravy z IPX            }
    { --------------------------------------------- }

     type  TBFunc_i     = function(i: int): bool;


     type  PIPXnode = ^TIPXnode;
           TIPXnode = object
             Node      : int;          { cislo uzla         }
             Connected : bool;         { uzol je v IPX.cfg  }
             Name      : TNETadr;      { string[dlz_IPX_ADR];  meno uzla }
             Adr       : TEthernetAdr; { fyzicka adresa     }
             Info      : Pchar;        { doplnkove udaje    }
             pro       : TProtocol;    { komunikacny protokol : IPX,RTR,RTI }

             Out_buff  : PIPXdpkt;
             Inp_buff  : PIPXdpkt;

            {$IFDEF IPX0}
             TrasaOK   : bool;         { priznak, ze trasa je OK     }
             SendOK    : bool;         { povolenie pre vysielanie    }
             SendTick  : word;         { stav citaca pri posl.prijme }

             to_init   : int ;         { ziadost o inicializaciu od uzla Node }
             test_en   : bool;         { povoleny test    }
             tested    : bool;         { testovanie linky }
             next_test : byte;         { Cas+3 sec pre nasledujuci test }
             intr_semaphor : bool;     { priznak, ze interrupt rutina je ON }
            {$ENDIF}


             constructor Init(is: byte);
             destructor  Done;

             function    Send(ipxSPRAVA: byte): byte;
             function    SendData(buff: pointer; size: word): byte;


            {$IFDEF IPX0}
             procedure   Test;               { otestuj uzol                  }

             function    isTimeOut: bool;    { vyprsal timeout na odpoved ?  }
             procedure   Wait;

             function    is_intr_en: bool;
             procedure   intr_sti;
             procedure   intr_cli;
            {$ENDIF}
           end;
