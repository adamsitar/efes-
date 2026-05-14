{ X+,I-,S-,P-,F+,O-}


unit PCTCPdef;


interface


    uses  TypeDef;

    { IFDEF PCTCP}
      {$I ip_adr.h}
      {$I ip_type.h}
      {$I ip_tcpip.h}          { konstanty inicializacie, spracovania a systemovych volani }
      {$I ip_opt.h}
      {$I ip_asyn.h}           { konstanty pre spracovanie asynchr vstupu }
      {$I ip_tag.h}
      {$I ip_error.h}
    { ENDIF}

    type Tframe_type = (DIX_Ethernet, PPP);


implementation

end.