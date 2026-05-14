{procedure prehlad_TLGr;
    const datum: TDatum = (h:0;m:0;s:0; den:0;mes:0;rok:0);
    var   Viewer: POViewerStreamFile;
          Event: TEvent;
    begin
      if not formular_DATUM_CAS('From',datum) then Exit;

      Viewer:= New(POViewerStreamFile,Init
                   (nil,'Received telegrams',
                    get_icao_streamFN(path_AFTN,extAFTN, datum.den,datum.mes,datum.rok, datum.h,datum.m),
                    true,
                    MTK_2_LINE, -1,
                    0,0,nil,nil,nil,
                    cl_AFTN_send,cl_AFTN_rec,
                    true,
                    nil
                   ));

      Viewer^.Run(Event);
      Dispose(Viewer,Done)
    end;}


procedure prehlad_AFTN;
    const datum: TDatum = (h:0;m:0;s:0; den:0;mes:0;rok:0);
    var   Viewer: POViewerStreamFile;
          Event: TEvent;
    begin
      if not formular_DATUM_CAS(tit_datum_cas,datum) then Exit;

      Viewer:= New(POViewerStreamFile,Init
                   (nil,tlg_list,
                    get_icao_streamFN(path_AFTN,extAFTN, datum.den,datum.mes,datum.rok, datum.h,datum.m),
                    false,
                    MTK_2_LINE, -1,
                    0,0,nil,nil,nil,
                    cl_AFTN_send,cl_AFTN_rec,
                    true,
                    nil
                   ));

      Viewer^.Run(Event);
      Dispose(Viewer,Done)
    end;
