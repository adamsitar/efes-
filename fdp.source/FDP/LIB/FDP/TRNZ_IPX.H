    {$IFDEF TRENAZER_IPX}

       const  max_TRENAZER_POS = 4;

       var    TRENAZER_POSs : array[0..max_TRENAZER_POS-1] of bool;
             {TRENAZER_ADR  : byte;  = 1;    1 shl TRENAZER_ADR }


       function  is_IPXBpacket     (packet: PNETBpacket): bool; far;
       procedure receive_broadcast (packet: PNETBpacket);

       procedure get_trenazer_pos  (adr: byte);
       function  get_trenazer_adr: byte;

       function  TRENAZERmenu_init(title: string): PSubmenu;
    {$ENDIF}
