 {$IFDEF TRENAZER}
   {$IFDEF TRENAZER_IPX}
     {$UNDEF PCTCP}
     {$UNDEF UDP}

     {$DEFINE IPX}
     {$DEFINE RTR1}
     {$DEFINE BROADCAST}

   {$ELSE}
     {$DEFINE TRENAZER_UDP}

     {$UNDEF IPX}
     {$UNDEF RTR1}

     {$DEFINE PCTCP}
     {$DEFINE UDP}
     {$DEFINE RTR2}
     {$DEFINE BROADCAST}
   {$ENDIF}

   {$UNDEF PRN}
   {$UNDEF IER}
 {$ENDIF}
