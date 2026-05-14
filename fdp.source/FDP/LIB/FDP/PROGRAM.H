{ -------------------------------------------------- }
{ Definovanie premmennych                            }
{ -------------------------------------------------- }
{$IFDEF SERVER}
   const path_exe = {$IFDEF DEBUG} '\xe\s\' {$ELSE} '' {$ENDIF};
         exe = 'server';
{$ENDIF}

{$IFDEF BRIDGE}
   const path_exe = {$IFDEF DEBUG} '\xe\b\' {$ELSE} '' {$ENDIF};
         exe = 'bridge';
{$ENDIF}

{$IFDEF FDA}
   const path_exe = {$IFDEF DEBUG} '\xe\a\' {$ELSE} '' {$ENDIF};
         exe = 'fda';
{$ENDIF}

{$IFDEF OPL}
   const path_exe = {$IFDEF DEBUG} '\xe\o\' {$ELSE} '' {$ENDIF};
         exe = 'opl';
{$ENDIF}

{$IFDEF EDD}
   const path_exe = {$IFDEF DEBUG} '\xe\e\' {$ELSE} '' {$ENDIF};
         exe = 'edd';
{$ENDIF}

(*
{$IFDEF IDD}
   const path_exe = {$IFDEF DEBUG} '\xe\e\' {$ELSE} '' {$ENDIF};
         exe = 'edd';
{$ENDIF}
*)
