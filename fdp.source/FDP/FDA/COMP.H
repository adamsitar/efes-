{ DEFINE DEBUG}
{ DEFINE DEMO}

{$I comp_exe.h}


{ ----------------------- }
{ Instalacia pre...       }
{ ----------------------- }

 {$DEFINE FDP}
 { DEFINE SERVER}
 {$DEFINE FDA}                 { FLIGHT DATA OPERATOR/ASSISTENT }


 {$DEFINE UKBB_ACC}
 { DEFINE UKBB_PRN}


{ ----------------------- }
{ Instalacia pre...       }
{ ----------------------- }

 {$IFDEF UKBB_ACC}
   {$I UKBBACC.h}
 {$ENDIF}

 {$IFDEF UKBB_PRN}
   {$I UKBBPRN.h}
 {$ENDIF}


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
