 { -----------------
   INSTALACIA
   -----------------
 }
  {$DEFINE RLP}

  {$DEFINE MATCA}    { MILITARY_ATC_AUTHORITY   }
  {$DEFINE AMC}      { AIRSPACE MANAGEMENT CELL }
  {$DEFINE MACC}
  {$DEFINE A-A}      { AIRSPACE USER }



 { -----------------------
   Spolupracujuce systemy
   -----------------------
 }
  {$IFDEF AMC} { IFNDEF DEBUG}
    {$DEFINE CONNECT_TO_AFTN}
  {$ENDIF} { ENDIF}


 { -----------------
   SPRACOVAVANE DATA
   -----------------
 }
  {$DEFINE PPL}

  {$DEFINE FPL4}
  {$DEFINE FPL}
  {$DEFINE FPL0}

{ IFNDEF DEBUG} { Niektore moduly nie su potrebne pre ladenie }

    {$DEFINE FPLM_L} { velke FPL }
    {$DEFINE FPLO}

    {$DEFINE FPLM_PLAN}     { zatial nema zmysel }
    {$DEFINE PROCESS_FPLM}


    {$DEFINE FPLM_REPORT}
    { DEFINE FPLM_REGULARITA}
    {$DEFINE REPORT_FPLM_ARW}

  {$DEFINE KRL}
    {$DEFINE PROCESS_KRL}

  {$DEFINE ZAM}
    {$DEFINE ZAM_PLAN}       { zatial nema zmysel }
    {$DEFINE PROCESS_ZAM}
    {$DEFINE ZAM_REPORT}

   {$DEFINE QGO}
    {$DEFINE QGO_PLAN}       { zatial nema zmysel }
    {$DEFINE PROCESS_QGO}
    {$DEFINE QGO_REPORT}


  {$DEFINE DVZ}
    {$DEFINE DVZ_REPORT}

{ ENDIF}

  {$DEFINE NOTAM}
    {$DEFINE NOTAM_REPORT}

  {$DEFINE PRZ}
    {$IFDEF AMC}
      {$DEFINE PRZ_REQUEST}
    {$ENDIF}
    {$DEFINE PRZ_REPORT}

  {$DEFINE PRS}
    {$DEFINE PRS_L}
    {$IFDEF AMC}
      {$DEFINE PRS_PLAN}
      {$DEFINE PROCESS_PRS}
    {$ENDIF}
    {$DEFINE PRS_REPORT}
    { DEFINE PRS_REGULARITA}

    {$DEFINE FUA}
      {$DEFINE FUA_DATA}
      {$IFDEF AMC}
        {$DEFINE PROCESS_FUA}
      {$ENDIF}

{ IFNDEF DEBUG} { Niektore moduly nie su potrebne pre ladenie }

 {$DEFINE MET}

  {$DEFINE SPR}
     {$DEFINE SPR_L}

{ ENDIF}


 { -----------------
   FUNKCIE
   -----------------
 }
  { DEFINE MACC_MENU}

  {$DEFINE RDP}
    { DEFINE RDP_ACCEPT}

  {$DEFINE STATISTIKA_OPL}
    {$DEFINE STATISTIKA}


 { -----------------
   KOMUNIKACIA
   -----------------
 }
  {$DEFINE NET}

  { DEFINE COM}
  { DEFINE IPX}
  {$DEFINE PCTCP}
    {$DEFINE UDP}
