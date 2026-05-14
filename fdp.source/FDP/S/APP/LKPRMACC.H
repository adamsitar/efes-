{$IFDEF LKPR_MACC}

 { --------------------------
   FDP/S-EDD  MACC Praha
   --------------------------
 }

   {$DEFINE MATCA}
   {$DEFINE MACC}
   {$DEFINE AMC}      { AIRSPACE MANAGEMENT CELL }

   {$DEFINE LK}
   {$DEFINE CZ}
   {$DEFINE PRAHA}

   {$DEFINE CZECH}
   {$DEFINE HELP_CZ}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }

   {$DEFINE BACKUP_ACTIVE_2_NET}
   { DEFINE BACKUP_ACTIVE_2_EXT}

   {$IFNDEF SERVER_2}

     {$DEFINE MASTER}

     {$DEFINE CONNECT_TO_CAMUS}
       {$IFDEF CONNECT_TO_CAMUS}
         {$DEFINE CAMUS_OLDI}
         {$DEFINE OLDI}
         {$DEFINE OLDI_BACKUP}
         {$DEFINE EXCEPTION_CALL_DESC}
         {$DEFINE CONNECT_TO_FDPOX}
       {$ENDIF}

     {$DEFINE CONNECT_TO_ASTA_EXT}
         { DEFINE ASTA_PRN}
         { DEFINE ASTA_FDP}

     {$DEFINE CONNECT_TO_VERA}

   {$ELSE}

     {$DEFINE BACKUP}

     { DEFINE CONNECT_TO_ASTA_EXT}
         { DEFINE ASTA_PRN}

   {$ENDIF}


   {$DEFINE CONNECT_TO_OPL_EXT}
       { DEFINE OPL_EXT_ASYNC}
       {$DEFINE OPL_EXT_UDP}


   {$DEFINE CONNECT_TO_FDA}


  { --------------------
     Konfiguracia
    --------------------
  }
   {$DEFINE DATA_BIN}
   {$DEFINE DB_BIN}

   {$DEFINE CAS_RTR}


  { ------------------
    Archivacie
    ------------------
  }
   { DEFINE ARCHIVE_DAR}

   {$DEFINE ARCHIVE_NET}
   {$DEFINE WRITELN_NET}

   {$DEFINE ARCHIVE_PROGRAM_ERR}


  { ------------------
    Spracovanie planov
    ------------------
  }
   {$DEFINE L4444}
   {$DEFINE L4444M}

 { IFNDEF DEBUG}
   {$DEFINE FPL4}
   {$DEFINE PPL}
 { ENDIF}

   {$DEFINE FPL}
   {$DEFINE FPL0}
     {$DEFINE FPLC_ION}         { zobraz vstupnu/vystupnu vysku }
     { DEFINE FPLM_L}
     {$DEFINE FPLO}

 {$IFDEF DEBUG}
    { DEFINE FPLM_PLAN}
    { DEFINE PROCESS_FPLM}
 {$ENDIF}

 { IFNDEF DEBUG}
   {$DEFINE RTZ}

   {$DEFINE PRS}
     {$DEFINE PRS_L}
     {$DEFINE PRS_PLAN}
     {$DEFINE PROCESS_PRS}
     { DEFINE SEND_2_NODE_PRS}

     {$DEFINE REQUEST_AUP}
     {$DEFINE FUA}

   { DEFINE MET}
   { DEFINE SPR}
 { ENDIF}


  { ------------------
    Funkcie
    ------------------
  }
   {$DEFINE RDP}
   {$DEFINE STATUS}
   {$DEFINE RVSM}


  { ------------------
     NET
    ------------------
  }
   {$DEFINE NET}

   { DEFINE IPX}
     { DEFINE IPX3}
     { DEFINE RTR2}

   {$DEFINE PCTCP}
     {$DEFINE UDP}
     {$DEFINE RTR2}


  { ------------------
     HW
    ------------------
  }
   { DEFINE _1280x1024}
   { DEFINE _MOUSE}

{$ENDIF}