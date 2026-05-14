{$IFDEF LZIB_UVS}

 { ---------------------------
   FDP/S-UVS
   ---------------------------
 }
   {$DEFINE PVO}
   {$DEFINE UVS}

   {$DEFINE LZ}
   {$DEFINE SK}

   {$DEFINE SLOVAK}
   {$DEFINE HELP_SK}


 { -----------------------
   Spolupracujuce systemy
   -----------------------
 }
   {$DEFINE CONNECT_TO_ASOC}


 { ------------------
   Spracovanie planov
   ------------------
 }
   {$DEFINE FDP_OPL}

   {$DEFINE PPL}

  {$IFNDEF DEBUG}
   {$DEFINE FPL}
   {$DEFINE FPL4}

   {$DEFINE FPL0}
    {$DEFINE FPLM_L}           { velke FPL }
    {$DEFINE FPLO}
  {$ENDIF}


  {$IFDEF DEBUG}
   { DEFINE FPLM_PLAN}
   { DEFINE PROCESS_FPLM}
  {$ELSE}

   {$DEFINE ZAM}

   {$DEFINE QGO}

   {$DEFINE DVZ}


   {$DEFINE NOTAM}

   {$DEFINE PRZ}

   {$DEFINE PRS}
     {$DEFINE PRS_L}

   {$DEFINE FUA}
     {$DEFINE FUA_DATA}
   {$ENDIF}


   {$DEFINE MET}
     {$DEFINE MET_RLI}

   {$DEFINE SPR}
     {$DEFINE SPR_L}

 {$ENDIF}


 { --------------------
    Funkcie
   --------------------
 }
   {$DEFINE RDP}
    { DEFINE RDP_ACCEPT}

   {$DEFINE STATUS}


 { --------------------
    Konfiguracia
   --------------------
 }
  {$DEFINE DB_BIN}
  {$DEFINE DATA_BIN}

  {$DEFINE CAS_RLI}
    {$DEFINE ASTERIX_ALas03}

  { DEFINE PRN}


 { ------------------
   Archivacie
   ------------------
 }
   { DEFINE ARCHIVE_DAR}
   {$DEFINE WRITELN_NET}


 { ------------------
    NET
   ------------------
 }
   {$DEFINE NET}
   {$DEFINE NODES100}

   { DEFINE IPX}
     { DEFINE RTR1}

   {$DEFINE PCTCP}
     {$DEFINE UDP}


 { ------------------
    HW
   ------------------
 }
  { UNDEF SVGA}
  { DEFINE EGAVGA}
