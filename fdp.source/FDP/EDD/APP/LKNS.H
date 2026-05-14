  {$IFDEF LK_NS}
  { -------------- }
  { PVO            }
  { -------------- }


  { INSTALACIA
    -----------------
  }
    {$DEFINE CZ}     {$DEFINE CZECH} {$DEFINE HELP_CZ}
    {$DEFINE PVO}
    {$DEFINE NS}

    { DEFINE MATCA}   { moze si naplanovat zamestnanie,... }
    { DEFINE ATCA}


  { SPRACOVAVANE DATA
    A FUNKCIE
    -----------------
  }
    {$DEFINE PPL}

    {$DEFINE L4444M}

    { DEFINE PPL}

    { DEFINE FPL}

    {$DEFINE FPL0}
       {$DEFINE FPL_CHG_ENABLED}         { podanie/oprava FPL }
       { DEFINE FPLM_L}                  { velke FPL }
       { DEFINE FPLM_REPORT}

    {$DEFINE ZAM}
      { DEFINE ZAM_REPORT}
      {$DEFINE TABLET_ZAM}

    {$DEFINE QGO}
      { DEFINE QGO_REPORT}

    {$DEFINE DVZ}
      { DEFINE DVZ_REPORT}


    { DEFINE NOTAM}
    { DEFINE PRZ}

    { DEFINE FUA}
    {$DEFINE PRS}
      { DEFINE PRS_L}
      { DEFINE PRS_REPORT}
      {$DEFINE TABLET_PRS}


    {$DEFINE MET}

    {$DEFINE SPR}
      { DEFINE SPR_L}



  { FUNKCIE
    -----------------
  }
    {$DEFINE _1280x1024}
    {$DEFINE EDD_17}
    {$DEFINE DISPLAY_PREPNI}

    { DEFINE FL_DIR}               { Smer letu urceny urceny letovou hladinou }
    { DEFINE LINE_STRIP}           { Strip na riadok }
    { DEFINE TABLET_DEP_ARR}
    { DEFINE TABLET_WEST_EAST}

    {$DEFINE MAPY}
    {$DEFINE PRN}

    {$DEFINE RDP}
    { DEFINE RDP_ACCEPT}



  { KOMUNIKACIE
    -----------------
  }
    { DEFINE COM}

    {$DEFINE IPX}
      {$DEFINE IPX3}
      {$DEFINE RTR2}

    { DEFINE PCTCP}
      { DEFINE UDP}
      { DEFINE RTR2}

    { DEFINE CAS_SERVER}
    { DEFINE CAS_RLI}   { DEFINE ASTERIX}
    {$DEFINE CAS_RTR}

    {$DEFINE MNU_TRASY}
    {$DEFINE NODES30}

  {$ENDIF}
