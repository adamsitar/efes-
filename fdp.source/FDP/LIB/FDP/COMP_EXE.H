{ DEFINE _DPMI}
{$DEFINE _OVR}

{$IFDEF DEBUG} { Don`t change compiller directives, in your own interess... }
 {$A+,B-,D+,E-,F+,G+,I-,L+,N+,O-,P-,Q+,R+,S+,T-,V-,X+,Y+}
{$ELSE}
 { D+,L+ added to the original D-,L- so every unit is source-debuggable in
   the BP IDE (which keeps debug info in DPMI extended memory). Pure symbol
   switches - generated code unchanged, runtime checks Q,R,S stay off.
   Caveat: the full /V symbol table in the EXE overflows real-mode TD's
   16-bit name pool (garbled module names, ~326 KB table, heap squeeze);
   if you must use standalone TD, flip back to D-,L- here and put a local
   D+,L+ directive only in the units you step through. Original line:
   A+,B-,D-,E-,F+,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V-,X+,Y- }
 {$A+,B-,D+,E-,F+,G+,I-,L+,N+,O-,P-,Q-,R-,S-,T-,V-,X+,Y-}
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
