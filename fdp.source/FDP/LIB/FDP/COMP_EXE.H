{ DEFINE _DPMI}
{$DEFINE _OVR}

{$IFDEF DEBUG} { Don`t change compiller directives, in your own interess... }
 {$A+,B-,D+,E-,F+,G+,I-,L+,N+,O-,P-,Q+,R+,S+,T-,V-,X+,Y+}
{$ELSE}
 {$A+,B-,D-,E-,F+,G+,I-,L-,N+,O-,P-,Q-,R-,S-,T-,V-,X+,Y-}
 (*{$A+,B-,D+,E-,F+,G+,I-,L+,N+,O-,P-,Q+,R+,S+,T-,V-,X+,Y+}*)
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
