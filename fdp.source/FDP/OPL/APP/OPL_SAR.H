 { INSTALACIA
   -----------------
 }
  {$DEFINE RLP}
  {$DEFINE SAR}



 { SPRACOVAVANE DATA
   -----------------
 }
  {$DEFINE PPL}

  {$DEFINE FPL}
  {$DEFINE FPL0}

  {$DEFINE FPLM_L} { velke FPL }
    {$DEFINE FPLO}
    {$DEFINE FPLM_REPORT}
    {$DEFINE REPORT_FPLM_ARW}


  {$DEFINE ZAM}
    {$DEFINE ZAM_PLAN}       { zatial nema zmysel }
    {$DEFINE ZAM_REPORT}

   {$DEFINE QGO}
    {$DEFINE QGO_PLAN}       { zatial nema zmysel }
    {$DEFINE QGO_REPORT}


  {$DEFINE DVZ}
    {$DEFINE DVZ_REPORT}


  {$DEFINE NOTAM}
    { DEFINE NOTAM_REPORT}

  {$DEFINE PRZ}
    { DEFINE PRZ_REPORT}


  {$DEFINE PRS}
    {$DEFINE PRS_L}
    {$IFDEF AMC}
      {$DEFINE PRS_PLAN}
      {$DEFINE PROCESS_PRS}
    {$ENDIF}
    {$DEFINE PRS_REPORT}

    {$DEFINE FUA}
      {$DEFINE FUA_DATA}


  {$DEFINE MET}

  {$DEFINE SPR}
     {$DEFINE SPR_L}



 { FUNKCIE
   -----------------
 }
  {$DEFINE RDP}
    {$DEFINE RDP_ACCEPT}

  {$DEFINE STATISTIKA_OPL}
    {$DEFINE STATISTIKA}


 { KOMUNIKACIA
   -----------------
 }
  {$DEFINE NET}

  { DEFINE COM}
  { DEFINE IPX}
  {$DEFINE PCTCP}
    {$DEFINE UDP}
