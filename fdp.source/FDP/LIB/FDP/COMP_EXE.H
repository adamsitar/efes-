{ DEFINE _DPMI}
{$DEFINE _OVR}

{$IFDEF DEBUG} { Don`t change compiller directives, in your own interess... }
 {$A+,B-,D+,E-,F+,G+,I-,L+,N+,O-,P-,Q+,R+,S+,T-,V-,X+,Y+}
{$ELSE}
 { Debug info (D,L) stays OFF globally in non-DEBUG builds: with D+ in all
   ~150 units the /V symbol table grows so large that real-mode TD corrupts
   module/file names while loading it. Units that should be source-debugged
   get a local D+,L+ directive right after their comp.h include - see
   EDD.PAS and AP.PAS. }
 {$A+,B-,D-,E-,F+,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V-,X+,Y-}
{$ENDIF}

{$IFDEF _OVR} {$O+} {$ENDIF}

{$M 65520,0,655360}

{$IFDEF DEBUG}
  {$DEFINE DD_EXE}
  {$DEFINE NOEMS}
{$ENDIF}

{$IFDEF DEMO}
  {$DEFINE DD_EXE}
{$ENDIF}

{$IFDEF _DPMI}
  {$DEFINE NOEMS}
{$ENDIF}
