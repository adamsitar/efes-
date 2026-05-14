  const PACKET_FN         = 'packet.tmp';
        PACKET_FN_        = 'packet.$$$';

        namPKT            = 'NET';
        znakovPKT         =  5;
        extPKT            = '.PKT';

        {$IFDEF DEBUG}
          PACKET_ALLOC_TO = $AFFF;
        {$ELSE}
          PACKET_ALLOC_TO = $1FFFF;
        {$ENDIF}


  const {$IFDEF DEBUG}           max_NETBuffer    : word = 50;
        {$ELSE}
         {$IFDEF SERVER}         max_NETBuffer    : word = 500;
         {$ELSE}                 max_NETBuffer    : word = 300;
         {$ENDIF}
          {NETBuffer_REZERVA = 50;
          NETBuffer_MIESTO  = NETBuffer_REZERVA*2;}
        {$ENDIF}


  const  _INFO_NET_RES    : bool = false;
         _NET_EN          : bool = false;  { semafor spracovania _NET }

  const  net_FILE_EXT = '~';