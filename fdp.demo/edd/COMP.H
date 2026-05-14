{ DEFINE DEBUG}
{ DEFINE TEST}
{ DEFINE DEMO}


{ ----------------------- }
{ Instalacia pre...       }
{ ----------------------- }

{$DEFINE FDP}
{$DEFINE SERVER}
{ DEFINE BACKUP}

{ DEFINE LZIB_MACC}
{ DEFINE LZIB_ACC}
{ DEFINE LZIB_UVS}

{ DEFINE LKPR_MACC}

{$DEFINE UKBB_ACC}
{ DEFINE UKBB_PRN}


{ ----------------------- }
{ Hardware                }
{ ----------------------- }

{$DEFINE BGI}
{$DEFINE SVGA}


{ ----------------------- }
{ exe modul               }
{ ----------------------- }

{$I comp_exe.h}

{$IFNDEF SVGA} {$DEFINE VGA} {$DEFINE EGAVGA} {$ENDIF}
{$DEFINE DISPLAY_ZHASNI} {$DEFINE DISPLAY_PREPNI}


{ ----------------------- }
{ Instalacia pre...       }
{ ----------------------- }

{$IFDEF LZIB_ACC}   { Server EDD, ACC Blava, co nevidys ? }
  {$I LZIBACC.h}
{$ENDIF}

{$IFDEF LZIB_MACC}  { Server OPL, StrRLP Blava }
  {$I LZIBMACC.h}
{$ENDIF}

{$IFDEF LZIB_UVS}
  {$I LZIB_UVS.h}
{$ENDIF}


{$IFDEF LKPR_MACC}  { Server EDD, MACC Praha, vole }
  {$I LKPRMACC.h}
{$ENDIF}


{$IFDEF UKBB_ACC}   { Server EDD, ACC Kiev, cu-cut-nemnozko }
  {$I UKBBACC.h}
{$ENDIF}

{$IFDEF UKBB_PRN}
  {$I UKBBPRN.h}
{$ENDIF}


{ I comp_fdp.h}


{ ------------------------ }
{ Spolocne nastavenia...   }
{ ------------------------ }

{ DEFINE ARCHIVE_NET}

{$IFDEF ARCHIVE_IPX} {$DEFINE BROADCAST} {$ENDIF}
{$IFDEF CAS_RLI}     {$DEFINE BROADCAST} {$ENDIF}

{ IFDEF DD_EXE}
  { DEFINE PRN}
  {$UNDEF COM}
  {$UNDEF X25}   {$UNDEF _X25}
  {$UNDEF PCTCP} {$UNDEF UDP}
  {$UNDEF IPX}
  {$UNDEF BROADCAST}
  {$UNDEF ARCHIVE_DAR}

  { DEFINE _MOUSE}
{ ENDIF}


{$IFDEF ARCHIVE_DAR}
 {$IFDEF IPX} {$DEFINE RTR1} {$ENDIF}
{$ENDIF}