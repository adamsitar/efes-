{$DEFINE DEBUG}
{ DEFINE DEMO}

{$I comp_exe.h}


{$DEFINE FDP}
{$DEFINE FDP_EDD}

{$DEFINE EDD}
{$DEFINE IDD}            { Zapnutie fcii spracovania dat zo suborov, ASM, OPL }

{ DEFINE DEMO_EDD}

{ DEFINE TRENAZER}
  { DEFINE TRENAZER_IPX}
  { DEFINE TRENAZER_DOS}
  { DEFINE TRENAZER_UNIX}


{ -------------------- }
{ Hardware             }
{ -------------------- }

 {$DEFINE BGI}
 { DEFINE SPEA}

 {$DEFINE _MOUSE}
 {$DEFINE NET}


{ -------------------- }
{ Instalacia pre :     }
{ -------------------- }

 { ------------------------------ }
 { Slovensko                      }
 { ------------------------------ }

  { DEFINE LZIB_MACC}
  {$DEFINE LZ_PVO}
  { DEFINE LZ_RC}


 { ------------------------------ }
 { Cechy                          }
 { ------------------------------ }

  { DEFINE LKPR_MACC}
  { DEFINE LK_LET}       { Letectvo ACR }
  { DEFINE LK_PVO}       { PVO ACR      }

  { DEFINE LKPR_FDA}     { Nie su ozivene }
  { DEFINE LK_RC}        {  -  // -       }
  { DEFINE LK_NS}        {  -  // -       }


 { ------------------------------ }
 { Ukrajina                       }
 { ------------------------------ }

  { DEFINE UKBB_ACC}
    { DEFINE UKBB_MACC}  { Predpoklada potvrdenu direktivu UKBB_MACC}


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

  {$IFDEF LK_LET}
    {$I LKLET.h}
  {$ENDIF}

  {$IFDEF LK_PVO}
    {$I LKPVO.h}
  {$ENDIF}


 { ------------------------------ }
 { Ukrajina                       }
 { ------------------------------ }

  {$IFDEF UKBB_ACC}
    {$I UKBBACC.h}
  {$ENDIF}



{ ------------------------ }
{ Spolocne nastavenia...   }
{ ------------------------ }

 {$I comp_FDP.h}

 {$DEFINE DISPLAY_ZHASNI}
 {$DEFINE SKRY_OKNA}

 {$DEFINE TABLET_DEP_ARR}
 { DEFINE TABLET_WEST_EAST}

 {$IFDEF SPEA}
   {$UNDEF MAPY}
   {$DEFINE EDD_20}
 {$ENDIF}


{ ------------------
   NET
  ------------------
}
 {$I comp_sim.h}
 {$I comp_ext.h}
 {$I comp_net.h}


{ ------------------------
  Nastavenia EDD...
  ------------------------
}

 {$IFDEF DD_EXE}
   {$UNDEF SPEA}
   {$DEFINE BGI}
   { UNDEF DISPLAY_PREPNI}
   {$IFNDEF SPEA} {$DEFINE MAPY} {$ENDIF}
   { UNDEF PRS}
   {$DEFINE EDD_17}
   { UNDEF PRN}
 {$ENDIF}
