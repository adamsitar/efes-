{$IFDEF UKBB_ACC}

 { --------------------------
    FDP/EDD  ACC KIEV
   --------------------------
 }
  {$DEFINE UK}
  {$DEFINE UKBB}
  {$DEFINE KIEV}

  {$IFDEF UKBB_MACC}
   {$DEFINE MATCA}
   {$DEFINE MACC}
  {$ELSE}
   {$DEFINE ATCA}
   {$DEFINE ACC}                { ACC/APP }
   { DEFINE APP}
   {$DEFINE AIRBASE}
  {$ENDIF}

  {$DEFINE ENGLISH}
  {$DEFINE RUSSIAN}
  {$DEFINE A36YKA}


 { -----------------------
   Spolupracujuce systemy
   -----------------------
 }


 { --------------------
   Konfiguracia
   --------------------
 }
  {$DEFINE EXE_KEY}


  {$DEFINE LAN}                 { Konfiguracia len v LAN }

  {$DEFINE DATA_BIN}            { Povodny prenosovy format }
  {$DEFINE DB_BIN}              { Povolenie zapisovat db binarne kvoli zrychleniu zapisu/nacitania }

  {$DEFINE CAS_RLI}
   {$DEFINE ASTERIX}

  {$DEFINE EXIT_PASSWORD}

  {$DEFINE IDD}

  {$DEFINE DISPLAY_ZHASNI}
  {$DEFINE DISPLAY_PREPNI}
  {$DEFINE SKRY_OKNA}

  {$DEFINE MAPY}

  {$DEFINE TABLET_DEP_ARR}
  {$DEFINE TABLET_WEST_EAST}
  {$DEFINE TABLET_PRS}

  {$DEFINE LINE_STRIP}          { Strip na riadok }

  {$IFNDEF TRENAZER}
   {$DEFINE PRN}
   {$DEFINE PRN_SERVER}
   {$DEFINE PRN_STRIP}          { Automaticka tlac prijateho stripu }
  {$ENDIF}


 { ------------------
   Spracovavane data
   ------------------
 }
  {$DEFINE PPL}

  {$DEFINE FPL}

  {$DEFINE FPL4}
  {$DEFINE FDR}
    { DEFINE PROCESS_FPL4}       { podanie FPL4 }

  {$DEFINE FPL0}
    {$DEFINE FPLC_L}
    {$DEFINE FPLM_L}
    {$DEFINE FPLO}

  {$DEFINE PRS}
    {$DEFINE PRS_L}
    { DEFINE PRS_REPORT}

  {$DEFINE SPR}
  {$DEFINE TLG}


 { ------------------
   FDP funkcie
   ------------------
 }
  {$DEFINE L4444M}
  {$DEFINE DATA_OB}
  {$DEFINE GOST}
  {$DEFINE TSGA}

  {$DEFINE FL_DIR}              { Smer letu urceny urceny letovou hladinou }
  {$DEFINE RDP}

  {$IFDEF ATCA} {$IFNDEF TRENAZER}
   {$DEFINE SECTORS}
   {$IFDEF FPL4}
     {$DEFINE FPL4_ACT}            { aktivacia FPLC z FPL4 }
   {$ENDIF}
   {$DEFINE SSR_MANAGEMENT}      { priradenie kodu ssr   }
   {$DEFINE CNL_FPLC}            { odoslanie spravy EST-CNL do systemu }
   {$DEFINE ABI_COORDINATION}

   {$DEFINE RDP_ACCEPT}
  {$ENDIF} {$ENDIF}

  {$IFDEF MATCA}
   {$DEFINE FPLM_PLAN}
   {$DEFINE PROCESS_FPLM}

   {$DEFINE PRS_PLAN}
   {$DEFINE PROCESS_PRS}

   {$UNDEF FPL4}
  {$ENDIF}

  {$IFDEF TRENAZER}
   {$UNDEF FPL4}
   {$UNDEF PRS}
  {$ENDIF}


 { ------------------
    NET
   ------------------
 }
  {$DEFINE NET}

  {$DEFINE IPX}
    {$DEFINE IPX3}
    {$DEFINE RTR2}
    {$DEFINE BROADCAST}

  { DEFINE PCTCP}
    { DEFINE UDP}
    { DEFINE RTR2}


 { ------------------
    HW
   ------------------
 }
  {$DEFINE BGI}
  {$DEFINE SVGA}
  {$DEFINE _1280x1024}
  {$DEFINE _MOUSE}

  {$DEFINE PRN}

{$ENDIF}