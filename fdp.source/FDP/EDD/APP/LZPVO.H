{ -------------- }
{ UVS PVO        }
{ -------------- }

{$IFDEF LZ_PVO}

  { -----------------
    Instalacia
    -----------------
  }
   {$DEFINE LZ}
   {$DEFINE SK}

   {$DEFINE SLOVAK}
   {$DEFINE HELP_SK}

   {$DEFINE PVO}
   {$DEFINE UVS}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }


  { ------------------
     Konfiguracia
    ------------------
  }
   {$DEFINE IDD}

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


   {$DEFINE RDP}

   {$DEFINE PRN}

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

     {$DEFINE PROCESS_FPLM}
     {$DEFINE FPLM_REPORT}
     {$DEFINE FPL_CHG_ENABLED}    { podanie/oprava FPL }


   {$DEFINE ZAM}
     {$DEFINE ZAM_REPORT}

    {$DEFINE QGO}
     {$DEFINE QGO_REPORT}

   {$DEFINE DVZ}
     {$DEFINE DVZ_REPORT}


   {$DEFINE PRS}
     {$DEFINE PRS_L}
     {$DEFINE PRS_REPORT}

     {$DEFINE FUA}
       {$DEFINE FUA_DATA}

   {$DEFINE NOTAM}
   {$DEFINE PRZ}


   {$DEFINE MET}

   {$DEFINE SPR}
      {$DEFINE SPR_L}


  { ------------------
     NET
    ------------------
  }
   {$DEFINE NET}

   { DEFINE COM}

   { DEFINE IPX}
     { DEFINE IPX3}
     { DEFINE RTR2}

   {$DEFINE PCTCP}
      {$DEFINE UDP}
      {$DEFINE RTR2}

{$ENDIF}
