procedure pozri_koordinaciu;
    var   i : int;
    begin
      {$IFDEF FLI_COORDINATION}
       with cFPL^ do if not coordinate_FLI then coordinate_FLI_ERR(display_FLI_ERR);
      {$ENDIF}
    end;

procedure _fdp_co_ordinate_procedure (src: fdp_src; dst: set_fdp_src;
                                      typ: TNETtyp; head: Thead_ICAO;
                                      zmeneny: bool;
                                      var plan
                                     ); far;
    var   i: int;
    begin
     {$IFDEF EXTERNAL_NET}
      for i:= 0 to EXT_DEVICESpoc-1 do
          begin
            EXT_DEVICES[i]^.send_co_ordinate_message (src,dst,typ,head,zmeneny,plan)
          end;
     {$ENDIF}
    end;