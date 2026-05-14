    {$IFDEF FPL4_ACT}
      {$DEFINE _FPL4S__FPL4_ACT}
      type  P_REQUEST_ACT_cFPL = ^T_REQUEST_ACT_cFPL;
            T_REQUEST_ACT_cFPL = record
              is  : bool;
              res : string;
              FPL : DcFPL
            end;

      procedure ziadost_ACT_cFPL (idn: string);
      function  odpoved_ACT_cFPL (act: P_REQUEST_ACT_cFPL): bool;
    {$ENDIF}


    {$IFDEF _FPL4S__FPL4_ACT}
      function   ACT_FPL4 (FPL: PFPL4): bool;
    {$ENDIF}

{$IFDEF FPL4_ACT}

  procedure ziadost_ACT_cFPL (idn: string);
     begin
       {ziadost_ACT_cFPL:= false;
       if (not formular_FPLi(' ACTIVATE FLIGHT ',idnFPL,false)) then Exit;
       if delchar(idnFPL,[icao_NXT,icao_NXIT])='' then Exit;}

       InfoCakaj(msgInfo,'Request for FPL on server.');
       idn:= cut_(idn); if idn='' then Exit;
       if idn[length(idn)]<>#0 then idn:= idn+#0;
       NETdistribute_msg([SERVER,BSERVER],[],[], spr_REQ_ACT, @idn[1],length(idn),true, net_flag_SEND);
       InfoCakaj_zatvor
     end;

  function odpoved_ACT_cFPL(act: P_REQUEST_ACT_cFPL): bool;
     begin
       if act^.is then
          begin
            if act^.res<>'' then Say2(msgMESS,act^.res)
            else begin
                   act^.FPL.stt:= hd_ACT;
                   formular_cFPL_(@act^.FPL,' ACTIVATE FLIGHT '+act^.FPL.idn)
                 end;
          end
       else Say2(msgMESS,'FPL not present neither on server.')
     end;

{$ENDIF}


{$IFDEF _FPL4S__FPL4_ACT}
  function  ACT_FPL4(FPL: PFPL4): bool;
      var   _14a,_14b,_14c,_14d,_14e : string;
            res  : string;
            ires : int;
            bres : bool;
            FDR  : DFDR;

      procedure activate_FPL4;
          begin
            formular_FPL4(hd_ICAO[msACT],FPL,'ACT OF FPL '+getstr(FPL^._7,1,[icao_NXT]),false)
          end;

      begin
        ACT_FPL4:= false;
        if FPL=nil then Exit;

        if     in_icao_head (FPL^._STT,ms_ICAOact,bres)
           and (Ask2(msgVERIPHY,'Another activation of the flight '+FPL^._7+'. Continue ?','',
                    White,clBUTTON_COLOR,waitASK*18
                   )<>ansAno) then Exit;

        {$IFDEF FPL4_ACT}
          if ACT_as_EST then
             begin
               InfoCakaj(msgWAITING,'Checking integrity of FPL...');
               FPL^._3:= hd_ACT; FPL^._STT:= hd_ACT;
               _item_14 (FPL, _14a,_14b,_14c,_14d,_14e);
               FPL^._14:= _14a+icao_NXT+_14b+_14c+_14d+_14e;
               res:= ''; fillchar(FDR,sizeof(FDR),0);
               _decode_FDR (FPL^,FDR, false, res);
               InfoCakaj_zatvor;
               if res<>'' then activate_FPL4
               else begin
                      p_add_FDR(FPL, @FDR, check_FPL4_FDR or check_FPL4_EST or zarad_FPL4_EST, res,ires);
                    end;
               disp_FDR(@FDR)
             end
          else activate_FPL4
        {$ELSE}
          activate_FPL4
        {$ENDIF}
      end;

{$ENDIF}

