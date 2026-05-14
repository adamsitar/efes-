{ DEFINE ARCHIVE_NET_BIN}       { ukladanie binarnych paketov }
{$DEFINE ARCHIVE_NET}           { ukladanie logickych paketov }
{ DEFINE WRITELN_NET}           { vypis paketov na obrazovku  }

{$IFDEF WRITELN_NET} {$DEFINE DOCUMENT_NET} {$ENDIF}
{$IFDEF ARCHIVE_NET} {$DEFINE DOCUMENT_NET} {$ENDIF}
{$IFDEF ARCHIVE_DAR} {$IFDEF IPX} {$DEFINE RTR1} {$ENDIF} {$ENDIF}
{$IFDEF CAS_RLI}     {$DEFINE BROADCAST}    {$ENDIF}

{$IFDEF DD_EXE}
  {$UNDEF X25}
    {$UNDEF _X25}
    {$UNDEF AdCOM2}
  {$DEFINE _X25_NOINIT}

  {$UNDEF IPX}

  {$UNDEF PCTCP}
    {$UNDEF UDP}

  {$UNDEF BROADCAST}
{$ENDIF}
