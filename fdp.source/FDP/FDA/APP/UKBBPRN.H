{$IFDEF UKBB_PRN}

 { --------------------------
   FDP/S-EDD  ACC KIEV
   -------------------------- }

   {$DEFINE FDP_EDD}

   {$DEFINE UA}
   {$DEFINE RLP}
   {$DEFINE ACC}
   {$DEFINE KIEV}

   {$DEFINE ENGLISH}
   {$DEFINE RUSSIAN}
   {$DEFINE A36YKA}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }
   {$DEFINE CONNECT_TO_BGU}
   {$DEFINE ARCHIVE_BGU}
   {$DEFINE MPU}


  { ------------------
    Archivacie
    ------------------
  }
   {$DEFINE ARCHIVE_COM}
   {$DEFINE ARCHIVE_NET}
   {$DEFINE ARCHIVE_PROGRAM_ERR}


  { ------------------
     HW
    ------------------
  }
   {$E+}
   {$UNDEF SVGA}
   {$DEFINE EGAVGA}

   { DEFINE _800x600}
   { DEFINE _1280x1024}
   { DEFINE _MOUSE}


  { ------------------
    Spracovavane data
    ------------------
  }
   {$DEFINE NO_PLAN}

   {$DEFINE L4444M}

   {$DEFINE FPL}
      {$DEFINE FPL0}
      {$DEFINE FPL4}
      {$DEFINE FPLC_L}           { dlhi strip   }

   {$DEFINE RDP}
   {$DEFINE GOST}


  { ------------------
    Funkcie
    ------------------
  }
   {$DEFINE DATA_WRITTEN_IN_APP}

   { DEFINE AFTN}
   { DEFINE ALR}
   { DEFINE ERR}

   { DEFINE RDP_ACCEPT}
   { DEFINE SECTORS}

   {$DEFINE STATUS}
   {$DEFINE EXIT_PASSWORD}


  { ------------------
     NET
    ------------------
  }
   {$DEFINE NET}
   {$DEFINE DATA_BIN}
   {$DEFINE DATA_BIN_ONLY}

   {$DEFINE IPX}
     {$DEFINE IPX3}
     {$DEFINE RTR2}

     {$DEFINE CAS_RLI}
     {$DEFINE BROADCAST}
     {$DEFINE ASTERIX}

   { DEFINE PCTCP}
     { DEFINE UDP}
     { DEFINE RTR2}
     { DEFINE CAS_RLI}
{$ENDIF}