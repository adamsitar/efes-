{ -------------- }
{ MACC Blava     }
{ -------------- }

{$IFDEF LZIB_MACC}

  { -----------------
    Instalacia
    -----------------
  }
   {$DEFINE LZ}
   {$DEFINE SK}

   {$DEFINE RLP}
   {$DEFINE MACC}     { musi byt... }
   {$DEFINE MATCA}    { MILITARY_ATC_AUTHORITY }

   {$DEFINE BLAVA}

   {$DEFINE SLOVAK}
   {$DEFINE HELP_SK}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }


  { ------------------
     Konfiguracia
    ------------------
  }
   {$DEFINE DATA_BIN}             { Povodny prenosovy format }
   {$DEFINE DB_BIN}               { Povolenie zapisovat db binarne kvoli zrychleniu zapisu/nacitania }

   { DEFINE IDD}
   { DEFINE EDD_17}
   { DEFINE DISPLAY_PREPNI}
   { DEFINE MAPY}
   { DEFINE _1280x1024}

   {$DEFINE FL_DIR}               { Smer letu urceny urceny letovou hladinou }
   { DEFINE LINE_STRIP}           { Strip na riadok }

   {$DEFINE TABLET_DEP_ARR}
   {$DEFINE TABLET_WEST_EAST}
   {$DEFINE TABLET_ZAM}
   {$DEFINE TABLET_PRS}


   { DEFINE SECTORS}

   {$DEFINE RDP}
    {$DEFINE RDP_ACCEPT}

   {$DEFINE PRN}
     { DEFINE IER}

   {$DEFINE CAS_RLI}
     {$DEFINE ASTERIX_ALas03}


  { -----------------
     Data
    -----------------
  }
    {$DEFINE PPL}

    {$DEFINE FPL}
    { DEFINE FPL4}
    {$DEFINE FPL0}
      {$DEFINE FPLM_L}             { velke FPL }
      {$DEFINE FPLO}

      {$DEFINE FPLM_PLAN}
      {$DEFINE PROCESS_FPLM}
      {$DEFINE FPLM_REPORT}
      {$DEFINE FPL_CHG_ENABLED}    { podanie/oprava FPL }

    {$DEFINE PRS}
      {$DEFINE PRS_L}
      {$DEFINE PRS_REPORT}

      {$DEFINE FUA}
        { DEFINE FUA_DATA}


    {$DEFINE SPR}
      {$DEFINE SPR_L}


  { ------------------
     NET
    ------------------
  }
    {$DEFINE NET}
    {$DEFINE DATA_BIN}

    { DEFINE COM}

    { DEFINE IPX}
      { DEFINE IPX3}
      { DEFINE RTR2}

    {$DEFINE PCTCP}
       {$DEFINE UDP}
       {$DEFINE RTR2}

{$ENDIF}
