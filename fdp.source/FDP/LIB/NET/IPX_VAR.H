{$IFDEF SERVER} {$DEFINE SB_BUFFER} {$ENDIF}
{$IFDEF BRIDGE} {$DEFINE SB_BUFFER} {$ENDIF}

const {$IFDEF DEBUG}
        nd_buff_size  : byte = 5;
        rtr_buff_size : byte = 5;
      {$ELSE}
        nd_buff_size  : byte = 50;
        rtr_buff_size : byte = 50;
      {$ENDIF}

       nd_buff  : PBuffer    = nil;
       rtr_buff : PBuffer    = nil;

      {$IFDEF BROADCAST}
        inp_brd_buff  : PNETBpkt = nil; { ! Rovnaky typ ako brd_buff } { konverzia-PIPXdpacket }
        brd_buff_size = {$IFDEF ARCHIVE_DAR} 20 {$ELSE} 5 {$ENDIF};
        brd_buff      : PBuffer  = nil;
      {$ENDIF}


{$IFDEF SOCKET}

   const {$IFDEF DEBUG}
           system_buff_size : byte = 30;
         {$ELSE}
           system_buff_size : byte = 50;
         {$ENDIF}

          system_buff : PBuffer = nil;

   var    system_pkt  : TIPXpkt_nd;


   procedure interrupt__IPX_broadcast; far;
   procedure interrupt__IPX_node;      far;

   {$IFDEF IPX3}
     procedure interrupt__IPX_system;  far;
   {$ENDIF}


{$ELSE}

   procedure PrijInt0; far;
   procedure PrijInt1; far;
   procedure PrijInt2; far;
   procedure PrijInt3; far;
   procedure PrijInt4; far;
   procedure PrijInt5; far;
   procedure PrijInt6; far;
   procedure PrijInt7; far;
   procedure PrijInt8; far;
   procedure PrijInt9; far;

{$ENDIF}

{$UNDEF SB_BUFFER}