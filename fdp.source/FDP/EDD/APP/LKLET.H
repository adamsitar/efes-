{$IFDEF LK_LET}

  { -------------- }
  { Letisko        }
  { -------------- }

   {$DEFINE LK}
   {$DEFINE CZ}

   {$DEFINE CZECH}
   {$DEFINE HELP_CZ}

   {$DEFINE RLP}
   {$DEFINE AIRBASE}
   {$DEFINE TWR}
   {$DEFINE MATCA}


  { -----------------------
    Spolupracujuce systemy
    -----------------------
  }


  { ------------------
     Konfiguracia
    ------------------
  }
   { DEFINE IDD}

   {$DEFINE DATA_BIN}             { Povodny prenosovy format }
   {$DEFINE DB_BIN}               { Povolenie zapisovat db binarne kvoli zrychleniu zapisu/nacitania }

   {$DEFINE EDD_17}               { Zmensene EDD na 17 palcovy display }

   {$DEFINE EDD_17}
   {$DEFINE _1280x1024}
   { DEFINE DISPLAY_PREPNI}
   { DEFINE MAPY}

   {$DEFINE FL_DIR}               { Smer letu urceny urceny letovou hladinou }
   { DEFINE LINE_STRIP}           { Strip na riadok }

   {$DEFINE TABLET_DEP_ARR}
   {$DEFINE TABLET_WEST_EAST}
   { DEFINE TABLET_ZAM}
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
     Spracovavne data
    ------------------
  }
   {$DEFINE PPL}

   {$DEFINE L4444}
   {$DEFINE L4444M}
   {$DEFINE RVSM}

   {$DEFINE FPL}
   { DEFINE FPL4}

   {$DEFINE FPL0}
     {$DEFINE FPLM_L}           { velke FPL }
     {$DEFINE FPLO}
     { DEFINE FPLM_REPORT}
     {$DEFINE FPLC_ION}         { zobraz vstupnu/vystupnu vysku }
     {$DEFINE FPL_CHG_ENABLED}  { podanie/oprava FPL }


   {$IFDEF IDD}
     {$DEFINE RTZ}
   {$ENDIF}


   {$DEFINE PRS}                {$IFDEF DEBUG} {$DEFINE PROCESS_PRS} {$ENDIF}
     {$DEFINE PRS_L}
     {$DEFINE PRS_PLAN}
     { DEFINE PROCESS_PRS}
     { DEFINE PRS_REPORT}


   { DEFINE MET}
     {$DEFINE TABLET_MET}


   { DEFINE SPR}


  { ------------------
     NET
    ------------------
  }
    { DEFINE COM}

    { DEFINE IPX}
      { DEFINE IPX3}
      { DEFINE RTR2}

    {$DEFINE PCTCP}
       {$DEFINE UDP}
       {$DEFINE RTR2}

{$ENDIF}