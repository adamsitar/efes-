 procedure add_RTZ(RTZ: PRTZ);
     begin
     end;


 function zarad_RTZ(RTZ: PRTZ; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_RTZ:= false;
      zarad_RTZ:= true;

      {if _stat<>'' then RTZ^.stat:= _stat;}
      format_RTZ(RTZ);
      save_RTZ(RTZ);

      {$IFDEF STATISTIKA_SERVER}
        {if p_save_STA_RTZ<>nil then TProc_p(p_save_STA_RTZ)(RTZ);}
      {$ENDIF}

      { musi byt na konci pertoze tato funkcia moze byt volana
        po spracovani z handlera tohto objektu objektu, ktory
        moze data uvolnit z pamate a dostanem takto referenciu
        na odalokovanu pamat
      }
      if _send then _odosli_RTZ(RTZ,_src);
      add_RTZ(RTZ);
    end;
