    {$IFDEF UKBB_MACC}
      {$DEFINE INIT_PLANY_ZO_SUBORA}

     {$IFNDEF DEMO}
      {$DEFINE DISABLED_ETO_FPLc}
      {$DEFINE RDP_ACCEPT}
      {$DEFINE FPL_ACT}
      {$DEFINE ABI_COORDINATION}
     {$ENDIF}

      {$DEFINE PRS_PLAN}

    {$ELSE}
      {$DEFINE SECTORS}

      { DEFINE DISABLED_ETO_FPLm}

      {$DEFINE RDP_ACCEPT}
      {$DEFINE FPL_ACT}
      {$DEFINE ABI_COORDINATION}

    {$ENDIF}

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

    {$DEFINE DATA_BIN}      { Povodny prenosovy format }


  { ------------------
     HW
    ------------------
  }
   {$DEFINE _1280x1024}
   {$DEFINE _MOUSE}

