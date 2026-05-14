{$IFDEF RDP_ACCEPT}

  function find_FPL(idn: string; var Fi: TindFPL): bool;
     begin
       Fi.ind:= cFPL^.find_id(idn);
       if Fi.ind<>-1 then Fi.iFPL:= cFPL
       else begin
              Fi.ind:= mFPL^.find_id(idn);
              if Fi.ind<>-1 then Fi.iFPL:= mFPL
              else begin
                     Fi.ind:= oFPL^.find_id(idn);
                     if Fi.ind<>-1 then Fi.iFPL:= oFPL
                     else Fi.iFPL:= nil
                   end
            end;
       find_FPL:= Fi.ind<>-1
     end;


  {
    EDD bude rozosielat rovnaku spravu accept na RDP,
    ako dostava od neho. Zabezpeci rozoslanie.
    Server si pamata, kto ho riadi.

  }
  {
    RDP prevzalo neriadeny let.
  }
  procedure FL_ACCEPT(idn: string; RDP: TRTRadr);
      var   Fi: TindFPL;
      begin
      { spriahnute EDD dostalo spravu o prevzati letu }
        if find_FPL(idn, Fi) then P_OFPL(Fi.iFPL)^.FL_accept(idn,RDP)
      end;

  {
    RDP zrusilo riadeny let. Nikto ho neriadi.
  }
  procedure FL_UNACCEPT(idn: string; RDP: TRTRadr);
      var   Fi: TindFPL;
      begin
      { spriahnute EDD dostalo spravu o zruseni riadenia letu }
        if find_FPL(idn, Fi) then P_OFPL(Fi.iFPL)^.FL_unaccept(idn,RDP)
      end;

  {
    RDP prevzalo riadnie letu od ineho.
  }
  procedure FL_A_HANDOVER(idn: string; RDP: TRTRadr);
      var   Fi: TindFPL;
      begin
        if find_FPL(idn, Fi) then P_OFPL(Fi.iFPL)^.FL_handover(idn,RDP)
      end;

  {
    RDP odovzdalo riadnie letu inemu.
  }
  procedure FL_U_HANDOVER(idn: string; RDP: TRTRadr);
      var   Fi: TindFPL;
      begin
        if find_FPL(idn, Fi) then P_OFPL(Fi.iFPL)^.FL_unhandover(idn,RDP)
      end;

{$ENDIF}