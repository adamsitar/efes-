{
  --------------------------------
  Definicia nasledkov pripojenia
  jednotlivych externych zdrojov
  --------------------------------
}
 {$IFDEF CONNECT_TO_AFTN}
   {$DEFINE EXTERNAL_NET}
     {$DEFINE EXTERNAL_ASYNC}
   {$DEFINE ARCHIVE_AFTN}
   {$DEFINE AFTN}
 {$ENDIF}


 {$IFDEF CONNECT_TO_ASTA_EXT}
   {$DEFINE ARCHIVE_ASTA}
 {$ENDIF}


 {$IFDEF CONNECT_TO_CAMUS}
   {$DEFINE EXTERNAL_NET}
   {$DEFINE ARCHIVE_CAMUS}
   {$DEFINE CAMUS}
   { DEFINE OLDI}   { Len MACC Praha a Blava, ACC Blava nie je  }
 {$ENDIF}


 {$IFDEF CONNECT_TO_ASOC}
   {$DEFINE EXTERNAL_NET}
   {$DEFINE ARCHIVE_ASOC}
 {$ENDIF}



 {$IFDEF CONNECT_TO_OPL_EXT}
   {$DEFINE EXTERNAL_NET}
   {$IFDEF OPL_EXT_ASYNC}
     {$DEFINE EXTERNAL_ASYNC}
   {$ENDIF}
   {$DEFINE ARCHIVE_OPL}
   { DEFINE OPL__SAVE_STREAM}
 {$ENDIF}


 {$IFDEF CONNECT_TO_VERA}
   {$DEFINE EXTERNAL_NET}
   {$DEFINE ARCHIVE_VERA}
 {$ENDIF}


{ --------------------------------
   Dosledky nastaveni
  --------------------------------
}

 {$IFDEF EXTERNAL_NET}
   { DEFINE FPL4}
 {$ENDIF}


 {$IFDEF OLDI}
   {$IFNDEF DEBUG}
     {$D+,F+,L+,Y+}
   {$ENDIF}

   {$DEFINE _X25}
     {$DEFINE AdCOM2}
 {$ENDIF}

 { DEFINE SYNCHRONIZE_EXT}
