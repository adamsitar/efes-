{$IFDEF LZIB_ACC}

 { --------------------------
   FDP/S-EDD  ACC Bratislava
   --------------------------
 }
   {$DEFINE FDP_EDD}

   {$DEFINE LZ}
   {$DEFINE SK}

   {$DEFINE ATCA}
   {$DEFINE ACC}
   {$DEFINE BLAVA}

   {$DEFINE SLOVAK}
   {$DEFINE HELP_SK}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }
   { DEFINE CONNECT_TO_ASTA_EXT}
       {$DEFINE ASTA_FDP}

   {$DEFINE CONNECT_TO_CAMUS}
     {$IFDEF CONNECT_TO_CAMUS}
       { DEFINE CAMUS_OLDI}
       { DEFINE OLDI}
     {$ENDIF}


  { ------------------
    Archivacie
    ------------------
  }
   {$DEFINE ARCHIVE_DAR}

   {$DEFINE ARCHIVE_NET}
   {$DEFINE WRITELN_NET}

   {$DEFINE ARCHIVE_PROGRAM_ERR}


  { ------------------
    Spracovanie planov
    ------------------
  }
   { DEFINE L4444M}

   {$DEFINE FPL4}

   {$DEFINE FPL}
   {$DEFINE FPL0}
     {$DEFINE FPLC_L}
     {$DEFINE FPLM_L}
     {$DEFINE FPLO}


  { ------------------
    Funkcie
    ------------------
  }
   {$DEFINE RDP}

   {$DEFINE DB_BIN}
   {$DEFINE DATA_BIN}

   {$DEFINE CAS_RLI}
     { DEFINE ASTERIX}            { Blava }
     {$DEFINE ASTERIX_ALas03}     { Zvolen }

   {$DEFINE FPLM_DISABLED}

   {$DEFINE STATUS}


  { ------------------
     NET
    ------------------
  }
   {$DEFINE NET}

   { DEFINE IPX}
     { DEFINE RTR1}

   {$DEFINE PCTCP}
     {$DEFINE UDP}


  { ------------------
     HW/NET
    ------------------
  }
   {$DEFINE SVGA}

{$ENDIF}
