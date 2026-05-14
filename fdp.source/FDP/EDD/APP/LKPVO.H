{ -------------- }
{ UVS PVO        }
{ -------------- }

{$IFDEF LK_PVO}

  { -----------------
    Instalacia
    -----------------
  }
   {$DEFINE LK}
   {$DEFINE CZ}

   {$DEFINE CZECH}
   {$DEFINE HELP_CZ}

   {$DEFINE PVO}
   {$DEFINE UVS}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }
   { DEFINE CONNECT_TO_ASOC}


  { ------------------
     Konfiguracia
    ------------------
  }
   {$DEFINE DATA_BIN}             { Povodny prenosovy format }
   {$DEFINE DB_BIN}               { Povolenie zapisovat db binarne kvoli zrychleniu zapisu/nacitania }

   {$DEFINE EDD_17}
   {$DEFINE DISPLAY_PREPNI}
   {$DEFINE MAPY}
   {$DEFINE _1280x1024}

   {$DEFINE FL_DIR}               { Smer letu urceny urceny letovou hladinou }
   { DEFINE LINE_STRIP}           { Strip na riadok }

   {$DEFINE TABLET_DEP_ARR}
   {$DEFINE TABLET_WEST_EAST}
   {$DEFINE TABLET_ZAM}
   {$DEFINE TABLET_PRS}


   { DEFINE SECTORS}

   {$DEFINE RDP}
    { DEFINE RDP_ACCEPT}

   {$DEFINE PRN}
     { DEFINE IER}

   { DEFINE CAS_SERVER}
   {$DEFINE CAS_RTR}
   { DEFINE CAS_RLI}
   { DEFINE ASTERIX}


  { ------------------
     Spracovavane data
    ------------------
  }
   {$DEFINE PPL}

   {$DEFINE L4444}
   {$DEFINE L4444M}
   {$DEFINE RVSM}

   {$DEFINE FPL}
   { DEFINE FPL4}
   {$DEFINE FPL0}
     { DEFINE FPLM_L}           { velke FPL }
     {$DEFINE FPLO}
     { DEFINE FPLM_REPORT}
     {$DEFINE FPLC_ION}         { zobraz vstupnu/vystupnu vysku }
     {$DEFINE FPL_CHG_ENABLED}  { podanie/oprava FPL }

  {$IFNDEF DEBUG}

   {$IFDEF IDD}
     {$DEFINE RTZ}
   {$ENDIF}

   {$DEFINE PRS}
     {$DEFINE PRS_L}
     { DEFINE PROCESS_PRS}
     {$DEFINE PRS_REPORT}

   {$IFNDEF SPEA}
     {$DEFINE MET}
       {$DEFINE TABLET_MET}
   {$ENDIF}

   { DEFINE SPR}

  {$ENDIF}

  { ------------------
     NET
    ------------------
  }
    {$DEFINE NET}

    { DEFINE COM}

    { DEFINE IPX}
      {$DEFINE IPX3}
      {$DEFINE RTR2}

    {$DEFINE PCTCP}
       {$DEFINE UDP}
       {$DEFINE RTR2}

    {$DEFINE NODES30}

{$ENDIF}

