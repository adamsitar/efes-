{$IFDEF LZIB_MACC}

 { ---------------------------
   FDP/S-OPL  SRLP Bratislava
   ---------------------------
 }
   {$DEFINE FDP_OPL}

   {$DEFINE LZ}
   {$DEFINE SK}

   {$DEFINE MATCA}
   {$DEFINE MACC}
   {$DEFINE BLAVA}

   {$DEFINE SLOVAK}
   {$DEFINE HELP_SK}


 { -----------------------
   Spolupracujuce systemy
   -----------------------
 }
   {$IFDEF SERVER_2}

   { ---------------------------------
      SERVER2 - rozhranie pre E2000
     ---------------------------------
   }

    {$DEFINE SLAVE}

     {$DEFINE CONNECT_TO_CAMUS}
      {$IFDEF CONNECT_TO_CAMUS}
        {$DEFINE CAMUS_OLDI}
        {$DEFINE OLDI}
        { DEFINE EXCEPTION_CALL_DESC}
      {$ENDIF}

   {$ELSE}

    { ---------------------------------
       SERVER1 - rozhranie pre LETVIS
      ---------------------------------
    }
    {$DEFINE MASTER}

   {$ENDIF}


  {$DEFINE CONNECT_TO_ASTA_EXT}
      {$DEFINE ASTA_PRN}        { DEFINE ASTA_PRN_ACK}
      {$DEFINE ASTA_FDP}        { DEFINE ASTA_FDP_ACK}


 { ------------------
   Spracovanie planov
   ------------------
 }
   {$DEFINE PPL}

   {$DEFINE FPL}
   {$DEFINE FPL4}
   {$DEFINE FPL0}
     {$DEFINE FPLC_CPL}

    {$IFDEF MASTER}
     {$DEFINE FPLM_L}           { velke FPL }
     {$DEFINE FPLO}

     {$DEFINE ZAM}

     {$DEFINE QGO}
      {$DEFINE QGO_PLAN}         { zatial nema zmysel }
      {$DEFINE PROCESS_QGO}

     {$DEFINE DVZ}


     {$DEFINE NOTAM}
     {$DEFINE PRZ}

     {$DEFINE PRS}
       {$DEFINE PRS_L}

       {$DEFINE FUA}
       {$DEFINE FUA_DATA}

     {$DEFINE MET}

    {$ENDIF}

   {$DEFINE SPR}
     {$DEFINE SPR_L}


 { --------------------
    Funkcie
   --------------------
 }
  {$DEFINE RDP}
    { DEFINE RDP_ACCEPT}

  {$DEFINE STATUS}

  { DEFINE STATISTIKA_OPL}
    { DEFINE STATISTIKA_SERVER}
    { DEFINE STATISTIKA}


 { --------------------
    Konfiguracia
   --------------------
 }
  {$DEFINE DB_BIN}
  {$DEFINE DATA_BIN}

  { DEFINE CAS_SERVER}
  {$DEFINE CAS_RLI}
    {$DEFINE ASTERIX_ALas03}


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

   { DEFINE IPX}
     { DEFINE RTR1}

   {$DEFINE PCTCP}
     {$DEFINE UDP}


 { ------------------
    HW
    ------------------
 }
   {$IFNDEF DEBUG}
     {$DEFINE VGA} { DEFINE B_W}
   {$ENDIF}

{$ENDIF}
