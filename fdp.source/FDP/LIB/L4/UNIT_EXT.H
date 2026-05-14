       _EXT_def

      {$IFDEF EXTERNAL_NET}

        ,_EXT, _L4444, _L4_FDP {$IFDEF OLDI}, _X25, _OLDI  {$ENDIF}


       {$IFDEF CONNECT_TO_CAMUS},    _CA_def, _CAMUS
       {$ENDIF}


       {$IFDEF CONNECT_TO_AFTN},  _AFTN {$IFDEF TSGA}, _AF_TSGA {$ENDIF}
       {$ENDIF}


      { PVO ASC/ACR
      }
       {$IFDEF CONNECT_TO_ASOC},     _ASOC
       {$ENDIF}


      { MACC Praha
      }
       {$IFDEF CONNECT_TO_OPL_EXT},  _OPL_def, _OPL
       {$ENDIF}


       {$IFDEF CONNECT_TO_VERA},     _VERA
       {$ENDIF}

      {$ENDIF}


      {$IFDEF CONNECT_TO_ASTA_EXT},  _ASTA_def, _ASTA  {$ENDIF}

