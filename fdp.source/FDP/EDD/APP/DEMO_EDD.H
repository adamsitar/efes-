{$IFDEF DEMO_EDD}

  { -------------- }
  { ACC...         }
  { -------------- }

    {$DEFINE DEMO}

    {$DEFINE SK}
    {$DEFINE RLP}

    {$DEFINE BLAVA}
    {$DEFINE MACC}
    { DEFINE AIRBASE}
    { DEFINE APP}

    {$DEFINE MATCA}
    {$DEFINE ATCA}

    {$DEFINE ENGLISH}
    { DEFINE RUSSIAN}
    { DEFINE A36YKA}


  { ------------------
     Funkcie
    ------------------
  }
    {$DEFINE EXIT_PASSWORD}

    {$DEFINE EDD_17}               { Zmensene EDD na 17 palcovy display }
    {$DEFINE FL_DIR}               { Smer letu urceny urceny letovou hladinou }
    {$DEFINE LINE_STRIP}           { Strip na riadok }
    {$DEFINE TABLET_DEP_ARR}
    {$DEFINE TABLET_WEST_EAST}


    {$DEFINE FPL}
      {$DEFINE FPL0}
      {$DEFINE FPL4}

    {$DEFINE PRS} {$DEFINE TABLET_PRS}
    { DEFINE ZAM} { DEFINE TABLET_PRS}

    { DEFINE MATCA}
    {$DEFINE PRS} {$DEFINE TABLET_PRS}


    {$DEFINE RDP}
    {$DEFINE RDP_ACCEPT}

    { DEFINE DISPLAY_PREPNI}
    { DEFINE MAPY}

    { DEFINE GOST}
    { DEFINE SECTORS}


  { ------------------
     NET
    ------------------
  }
    {$DEFINE NET}

    { DEFINE IPX}
      { DEFINE IPX3}
      { DEFINE RTR2}

      { DEFINE CAS_RLI}
      { DEFINE BROADCAST}
      { DEFINE ASTERIX}

    { DEFINE PCTCP}
      { DEFINE UDP}
      { DEFINE RTR2}
      { DEFINE CAS_RLI}


  { ------------------
     HW
    ------------------
  }
    { DEFINE _1280x1024}
    {$DEFINE _MOUSE}

    {$DEFINE PRN}
    { DEFINE PRN_SERVER}

{$ENDIF}

    {$DEFINE A36YKA}
    {$DEFINE EXIT_PASSWORD}

    {$IFDEF UKBB_MACC}
      {$DEFINE DISPLAY_PREPNI}
      {$DEFINE MAPY}
      {$DEFINE MATCA}
    {$ENDIF}

    {$DEFINE FPL}
      {$DEFINE FPL0}
      {$DEFINE FPL4}

    {$DEFINE PRS}
      {$DEFINE TABLET_PRS}

    {$DEFINE RDP}
      {$DEFINE RDP_ACCEPT}

    {$DEFINE GOST}

    {$DEFINE SECTORS}


  { ------------------
     NET
    ------------------
  }
    {$DEFINE NET}

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


  { ------------------
     HW
    ------------------
  }
   {$DEFINE _1280x1024}
   {$DEFINE _MOUSE}

   {$IFNDEF TRENAZER}
     {$DEFINE PRN}
     {$DEFINE PRN_SERVER}
     {$DEFINE PRINT_PSTRIP}
   {$ENDIF}
