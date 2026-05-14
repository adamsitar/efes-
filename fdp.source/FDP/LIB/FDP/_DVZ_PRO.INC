{$IFDEF PROCESS_DVZ}

(*  procedure _zobraz_priznaky_ziadosti;
      begin
        {$IFDEF STATUS}
          if (btREQ<>nil) then
             begin
               if isDVZ_REQ_DLA then btREQ^.show else btREQ^.hide
             end
        {$ENDIF}
      end;*)


  { ziadost ?
  }
  function _ziadost_o_DVZ(p, DVZi: PDVZ): bool;          {_is_prop_DVZ}
     begin
       _ziadost_o_DVZ:=      (DVZi<>nil)
                         and _plan_pre(DVZi^.kym)
                         and (get_chars(DVZi^.stat, cnst_prop) = 1)
     end;

  { odlozena ziadost ?
  }
  function _odlozena_ziadost_o_DVZ(p, DVZi: PDVZ): bool; {_is_prop_DVZ_}
     begin
       _odlozena_ziadost_o_DVZ:=
                             (DVZi<>nil)
                         and _plan_pre(DVZi^.kym)
                         and (get_chars(DVZi^.stat, cnst_prop) = 2)
     end;


  procedure _pozri_ziadosti_o_DVZ(DVZ: PDVZ);
      begin
        if _ziadost_o_DVZ(nil,DVZ) then isDVZ_REQ:= true
        else isDVZ_REQ:= find_DVZ(nil,@_ziadost_o_DVZ)<>-1;
        {_zobraz_priznaky_ziadosti;}
      end;

  procedure _pozri_odlozene_ziadosti_o_DVZ(DVZ: PDVZ);
      begin
        if _odlozena_ziadost_o_DVZ(nil,DVZ) then isDVZ_REQ_DLA:= true
        else isDVZ_REQ_DLA:= find_DVZ(nil,@_odlozena_ziadost_o_DVZ)<>-1;
        {_zobraz_priznaky_ziadosti;}
      end;


  procedure pozri_ziadosti_o_DVZ(DVZ: PDVZ);
      begin
      { prisla ziadost o spracovanie diverzie s priznakom "cnst_prop" ?
         -prop             -> ziadost o diverziu
         -prop+active      -> odoslanie na diverziu
      }
      if (DVZ=nil) or _plan_pre(DVZ^.kym) then
         begin
          { prisla poziadavka na drzanie alebo aktivizaciu DVZ ?
          } _pozri_ziadosti_o_DVZ(DVZ);

          { odlozenie poziadavky na pripomienku ?
          } _pozri_odlozene_ziadosti_o_DVZ(DVZ);
         end;
      end;

{$ENDIF}
