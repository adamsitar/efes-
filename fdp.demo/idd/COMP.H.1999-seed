{ DEFINE DEBUG}
{ DEFINE DEMO}

{$I comp_exe.h}


{ -------------------- }
{ Instalacia pre :     }
{ -------------------- }

{$DEFINE FDP}
{$DEFINE FDP_EDD}

{$DEFINE EDD}
{ DEFINE IDD}

{ DEFINE TRENAZER}
  { DEFINE TRENAZER_IPX}
  {$DEFINE TRENAZER_UDP}


{ DEFINE DEMO_EDD}

{ DEFINE LZIB_MACC}
{ DEFINE LZ_PVO}
{$DEFINE LZ_RC}

{ DEFINE LKPR_MACC}
{ DEFINE LKPR_FDO}

{ DEFINE LK_LET}
{ DEFINE LK_RC}                { nie je ozivene }

{ DEFINE LK_PVO}
{ DEFINE LK_NS}

{ DEFINE UKBB_ACC}
  { DEFINE UKBB_MACC}          { Predpoklada potvrdenu direktivu UKBB_MACC}


{ ------------------
  Instalacia pre...
  ------------------
}
  {$IFDEF DEMO_EDD}
    {$I DEMO_EDD.h}
  {$ENDIF}

 { ------------------------------ }
 { Slovensko                      }
 { ------------------------------ }

  {$IFDEF LZIB_MACC}
    {$I LZIBMACC.h}
  {$ENDIF}

  {$IFDEF LZ_PVO}
    {$I LZPVO.h}
  {$ENDIF}

  {$IFDEF LZ_RC}
    {$I LZRC.h}
  {$ENDIF}


 { ------------------------------ }
 { Cechy                          }
 { ------------------------------ }

  {$IFDEF LKPR_MACC}
    {$I LKPRMACC.h}
  {$ENDIF}

  {$IFDEF LKPR_FDO}
    {$I LKPRFDO.h}
  {$ENDIF}

  {$IFDEF LK_LET}
    {$I LKLET.h}
  {$ENDIF}

  {$IFDEF LK_PVO}
    {$I LKPVO.h}
  {$ENDIF}

  {$IFDEF LK_NS}
    {$I LKNS.h}
  {$ENDIF}


 { ------------------------------ }
 { Ukrajina                       }
 { ------------------------------ }

  {$IFDEF UKBB_ACC}
    {$I UKBBACC.h}
  {$ENDIF}



{ -------------------- }
{ Hardware             }
{ -------------------- }

{$DEFINE BGI}
{ DEFINE SPEA}

{$DEFINE _MOUSE}
{$DEFINE NET}


{ -------------------- }
{ Funkcie              }
{ -------------------- }

{$DEFINE DISPLAY_ZHASNI}
{$DEFINE SKRY_OKNA}

{$I comp_FDP.h}

{$DEFINE TABLET_DEP_ARR}
{ DEFINE TABLET_WEST_EAST}


{ ------------------------------------ }
{ A ted se pojd podivat, cos udelal... }
{ ------------------------------------ }

{$IFDEF MAPY}
  {$DEFINE MAPY_2.0}
{$ENDIF}

{$IFDEF CAS_RLI}
  {$DEFINE BROADCAST}
{$ENDIF}


{$IFDEF TRENAZER}
  {$UNDEF IPX}
  {$UNDEF PCTCP}   {$UNDEF UDP}

  {$UNDEF PRN}
  {$UNDEF EXIT_PASSWORD}

  {$IFDEF TRENAZER_IPX}
    {$DEFINE BROADCAST}
    {$DEFINE IPX}
       {$DEFINE RTR1}
  {$ENDIF}

  {$IFDEF TRENAZER_UDP}
    {$UNDEF  IPX}   {$DEFINE RTR2}
    {$DEFINE PCTCP} {$DEFINE UDP}
    {$DEFINE BROADCAST}

    {$DEFINE PCTCP}
       {$DEFINE UDP}
       {$DEFINE RTR2}
  {$ENDIF}
{$ENDIF}


{$IFDEF DD_EXE}
  {$UNDEF COM}
  {$UNDEF IPX}
  {$UNDEF PCTCP} {$UNDEF UDP}
  {$UNDEF BROADCAST}

  { UNDEF DISPLAY_PREPNI}
  { UNDEF MAPY}
  {$DEFINE EDD_17}
{$ENDIF}


{$DEFINE ARCHIVE_PROGRAM_ERR}
{$DEFINE ARCHIVE_NET}
{$DEFINE PRNT_ERR_MESS}


{$IFDEF SPEA}
  {$UNDEF MAPY}
  {$UNDEF EDD_17}
{$ELSE}
  { DEFINE EDD_17}
{$ENDIF}
