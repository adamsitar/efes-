{$DEFINE DEBUG}
{ DEFINE DEMO}

{$I comp_exe.h}


{ -------------------- }
{ Instalacia pre...    }
{ -------------------- }

{$DEFINE FDP}
{$DEFINE FDP_OPL}
{$DEFINE OPL}

{$DEFINE LZ}
{$DEFINE SK}

{$DEFINE SLOVAK}
{$DEFINE HELP_SK}

{$DEFINE OPL_LET}
{ DEFINE OPL_SMD}
{ DEFINE OPL_AMC}
{ DEFINE OPL_SAR}
{ DEFINE OPL_BRF}

{ DEFINE TRENAZER}


{ ------------------------- }
{ OPL: Instalacia pre...    }
{ ------------------------- }

{$IFDEF OPL_LET}
  {$I opl_let.h}
{$ENDIF}

{$IFDEF OPL_SMD}
  {$I opl_smd.h}
{$ENDIF}

{$IFDEF OPL_AMC}
  {$I opl_amc.h}
{$ENDIF}

{$IFDEF OPL_SAR}
  {$I opl_sar.h}
{$ENDIF}

{$IFDEF OPL_BRF}
  {$I opl_brf.h}
{$ENDIF}

{$I comp_FDP.h}


{ -------------------- }
{ Hardware             }
{ -------------------- }

{$DEFINE BGI}
{$DEFINE SVGA}
{ DEFINE _1280x1024}
{$DEFINE _MOUSE}


{ -------------------- }
{ Konfiguracia         }
{ -------------------- }

{$DEFINE DATA_BIN}      { Povodny prenosovy format }
{$DEFINE DB_BIN}        { Povolenie zapisovat db binarne kvoli zrychleniu zapisu/nacitania }

{$DEFINE DISPLAY_ZHASNI}
{$DEFINE DISPLAY_PREPNI}
{ DEFINE SKRY_OKNA}

{$DEFINE MAPY}
{$DEFINE ZOZNAMY}
{$DEFINE STATUS}

{$DEFINE PRN}
{$DEFINE PRNT_ERR_MESS}

{ DEFINE CAS_SERVER}
{$DEFINE CAS_RLI}
  {$DEFINE ASTERIX_ALas03}


{ -------------------- }
{ Spolocne ...         }
{ -------------------- }

{$I comp_fdp.h}


{ ------------------
   NET
  ------------------
}
{ DEFINE BRIDGE}

{$I comp_ext.h}
{$I comp_net.h}
{$I comp_sim.h}
