function handle_SYN(SYN: PSYN): bool;
   begin
     {$IFDEF PRN}
       print_SYN(SYN);
     {$ENDIF}
     handle_SYN:= false
   end;


(*
function handle_MET(MET: PMET): bool; far;
   begin
     {$IFDEF PRN}
       print_MET(MET);
     {$ENDIF}
     handle_MET:= false
   end;
*)
