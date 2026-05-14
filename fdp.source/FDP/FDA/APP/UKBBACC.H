{$IFDEF UKBB_ACC}

 { --------------------------
    FDP/S-EDD  ACC KIEV
   --------------------------
 }

  {$DEFINE ATCA}       {$DEFINE RLP}
  {$DEFINE ACC}

  {$DEFINE UK}
  {$DEFINE UKBB}
  {$DEFINE KIEV}

  {$DEFINE ENGLISH}
  {$DEFINE RUSSIAN}
  {$DEFINE A36YKA}


 { -----------------------
   Spolupracujuce systemy
   -----------------------
 }
  {$DEFINE CONNECT_TO_AFTN}
  {$DEFINE BACKUP_AFTN}


 { --------------------
   Konfiguracia
   --------------------
 }
  {$DEFINE EXE_KEY}


  {$DEFINE MASTER}
  { DEFINE BACKUP}           { zalozny }
  { IFNDEF DEBUG}
    {$DEFINE BACKUP_ACTIVE_2_NET}
  { ENDIF}

  {$DEFINE DATA_BIN}         { Povodny prenosovy format }
  {$DEFINE DB_BIN}           { Povolenie zapisovat db binarne kvoli zrychleniu zapisu/nacitania }
  {$DEFINE DB_DBASE}

  {$DEFINE CAS_RLI}
  {$DEFINE ASTERIX}

  {$DEFINE EXIT_PASSWORD}


  {$DEFINE DISPLAY_ZHASNI}
  {$DEFINE DISPLAY_PREPNI}
  { DEFINE SKRY_OKNA}

  {$IFNDEF DEBUG} {$DEFINE DATA_WRITTEN_IN_APP} {$ENDIF}
  { DEFINE MAPY}
  {$DEFINE ZOZNAMY}
  {$DEFINE STATUS}


 { ------------------
   Spracovavane data
   ------------------
 }
  {$DEFINE PPL}

  {$DEFINE FPL}

  {$DEFINE FPL4}
   {$DEFINE PROCESS_FPL4}              { podanie FPL4 }
   {$DEFINE FDR}
(*
  {$DEFINE RPL}
   {$DEFINE PROCESS_RPL}

  {$DEFINE PLN}
   {$DEFINE PROCESS_PLN}
*)
  {$DEFINE FPL0}
   {$DEFINE FPLC_L}
   {$DEFINE FPLM_DISABLED}
   { DEFINE FPLM_L}
   { DEFINE FPLO}


  { DEFINE SPR}

  {$DEFINE TLG}


 { ------------------
   FDP funkcie
   ------------------
 }
  {$DEFINE GOST}
  {$DEFINE TSGA}

  {$DEFINE ERR}
  {$DEFINE ALR}

  {$DEFINE FL_DIR}              { Smer letu urceny urceny letovou hladinou }
(*
  {$IFDEF BACKUP}
    {$DEFINE STATISTIKA}
     {$DEFINE STATISTIKA_PRELETY}
  {$ENDIF}

  {$DEFINE FLI_COORDINATION}
  {$DEFINE CNL_FPLC}            { odoslanie spravy EST-CNL do systemu }

  {$DEFINE SSR_MANAGEMENT}
  {$DEFINE SSR_SERVER}
*)
  {$DEFINE RDP}
   { DEFINE RDP_ACCEPT}
(*
  { DEFINE SECTORS}

  {$DEFINE L4444M}
  {$DEFINE DATA_OB}

  {$DEFINE SYNCHRONIZE_EXT}
*)

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