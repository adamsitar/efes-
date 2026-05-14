{$IFDEF EDD}

  function comp_idn_indFPL(indFPL1,indFPL2: PindFPL): bool;
     var   s1,s2: string;
     begin
       with indFPL1^ do s1:= iFPL^.get_id(iFPL^.ap^[ind]);
       with indFPL2^ do s2:= iFPL^.get_id(iFPL^.ap^[ind]);
       comp_idn_indFPL:= s1<s2
     end;

  function comp_NDB_indFPL(indFPL1,indFPL2: PindFPL): bool;
     var   s1,s2: string;
     begin
       with indFPL1^ do s1:= iFPL^.NDB(ind);
       with indFPL2^ do s2:= iFPL^.NDB(ind);
       if s1<>s2 then comp_NDB_indFPL:= s1<s2
       else comp_NDB_indFPL:= comp_idn_indFPL(indFPL1,indFPL2)
     end;

  function comp_ETD_indFPL(indFPL1,indFPL2: PindFPL): bool;
     var   r1,r2: real;
     begin
       with indFPL1^ do r1:= iFPL^.ETD(ind);
       with indFPL2^ do r2:= iFPL^.ETD(ind);
       if r1<>r2 then comp_ETD_indFPL:= r1<r2
       else comp_ETD_indFPL:= comp_idn_indFPL(indFPL1,indFPL2)
     end;

  function comp_ETO_indFPL(indFPL1,indFPL2: PindFPL): bool;
     var   r1,r2: real;
     begin
       with indFPL1^ do r1:= iFPL^.ETO(ind);
       with indFPL2^ do r2:= iFPL^.ETO(ind);
       if r1<>r2 then comp_ETO_indFPL:= r1<r2
       else comp_ETO_indFPL:= comp_idn_indFPL(indFPL1,indFPL2)
     end;

  function comp_ETA_indFPL(indFPL1,indFPL2: PindFPL): bool;
     var   r1,r2: real;
     begin
       with indFPL1^ do r1:= iFPL^.ETA(ind);
       with indFPL2^ do r2:= iFPL^.ETA(ind);
       if r1<>r2 then comp_ETA_indFPL:= r1<r2
       else comp_ETA_indFPL:= comp_idn_indFPL(indFPL1,indFPL2)
     end;

  function comp_FL_indFPL(indFPL1,indFPL2: PindFPL): bool;
     var   r1,r2: real;
     begin
       with indFPL1^ do r1:= iFPL^.FL(ind);
       with indFPL2^ do r2:= iFPL^.FL(ind);
       if r1<>r2 then comp_FL_indFPL:= r1<r2
       else comp_FL_indFPL:= comp_idn_indFPL(indFPL1,indFPL2)
     end;

{$ENDIF}
