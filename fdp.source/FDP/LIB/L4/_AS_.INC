constructor O_ASOC.Init;
      begin
        NODE:= -1;
        EXT_HEADER_ADR:= false;
        IA5:= true;
        ITA2_ASCII:= false;
        ITA2_BIN:= false;

        inherited Init(nil,@power_ASOC,ASOCcfg,strpas(fnOB.fn),
                       0,false,
                       ASOC_PACKET_SIZE,ASOC_BUFFER_SIZE,true,ASOC_BUFFER_SIZE,
                       0,0,0,0,0,0,0,0,0,0,
                       nil,ASOC_coor_info,
                       @hd_ASL4, sizeof(hd_ASL4) div sizeof(Thead_ICAO),
                       nil,0,
                       @writeln_ASOC, @archive_ASOC, @utc_ASOC,
                       cl_ASOC, cl_ASOC_system_mess,
                       path_ASOC, path_ASOC+spath_ERR, extASOC
                      );

        src_type:= _FDP_DEF.asoc;
        dst_set := [];

        est_alt_:= altFL;

        _dct_points:= true;
        _oat_exclude:= true;

        CISLO_SPRAVY24h:= true;

        {SaveMain:= ACheck;
        ACheck:= _check_ASOC}
      end;


function  O_ASOC.read_cfg(_cfg_FN: string): bool;
   var   res: string;
   label E,X;
   begin
     res:= '';
     read_cfg:= inherited read_cfg(_cfg_FN);

    { adresa v NET
    }
     NODE:= 0;
     while     (NODE<NODEpoc)
           and (NODEs^[NODE].desc.typ<>NET_DEF.iny_typ)
           and (strpos(NODEs^[NODE].desc.inf,nd_ASOC)=nil)
     do inc(NODE);
     if NODE>=NODEpoc then
        begin
          NODE:= -1;
          res:= NETcfg+' - missing "@ASOC" node.';
          goto E
        end;


    { kodovanie sprav ICAO pre ASOC
    }
     IA5             := read_cfg_bool(_cfg_FN,cfg_IA5,IA5);
     ITA2_ASCII      := read_cfg_bool(_cfg_FN,cfg_ITA2_ASCII,ITA2_ASCII);
     ITA2_BIN        := read_cfg_bool(_cfg_FN,cfg_ITA2_BIN,ITA2_BIN);
     ITA2_BITS       := read_cfg_word(_cfg_FN,cfg_COM_BITs,MTK_2_BITes);

    { adresy ICAO
    }
     ADR_I:= _read_cfg(_cfg_FN,cfg_MTK_ADR_I,true);
     ADR_O:= _read_cfg(_cfg_FN,cfg_MTK_ADR_O,true);
     if (ADR_O='') then begin res:= cfg_MTK_ADR_O; goto X end;
     if not ((length(ADR_O) in [_MTK_ADR_lo,_MTK_ADR_hi])) then begin res:= cfg_MTK_ADR_O; goto X end;

     CHNL_I:= _read_cfg(_cfg_FN,cfg_MTK_CHNL_I,true);
     CHNL_O:= _read_cfg(_cfg_FN,cfg_MTK_CHNL_O,true);
     if (CHNL_O='') then begin res:= cfg_MTK_CHNL_O; goto X end;
     if (length(CHNL_O)<>_MTK_CHNL) then begin res:= cfg_MTK_CHNL_O; goto X end;

     X: if res<>'' then res:= _cfg_FN+' '+res+'.';
     E: if res<>'' then RunError(res);
     read_cfg:= res=''
   end;


procedure O_ASOC.HandleEvent(var _Event: TEvent);
    var   i : int;
    begin
      inherited HandleEvent(_Event);

      if (_Event.What<>evNothing) then
        case _Event.Command of

          cmASOC_INIT_FPLC : for i:= 0 to cFPL^.top do _send_message_FPLC(hd_EST, true, PDcFPL(cFPL^.ap^[i])^);
          cmASOC_INIT_FPLM : for i:= 0 to mFPL^.top do _send_message_FPLM(hd_ACT, true, PDmFPL(mFPL^.ap^[i])^);
          cmASOC_INIT_FPLO : for i:= 0 to oFPL^.top do _send_message_FPLM(hd_ACT, true, PDmFPL(oFPL^.ap^[i])^);

          {IFDEF DEBUG}
           cmASOC_TEST_FPL : test_fn(hd_ASL4[msFPL]);
           cmASOC_TEST_CHG : test_fn(hd_ASL4[msCHG]);
           cmASOC_TEST_DLA : test_fn(hd_ASL4[msDLA]);
           cmASOC_TEST_CNL : test_fn(hd_ASL4[msCNL]);

           cmASOC_TEST_ACT : test_fn(hd_ASL4[msACT]);

           cmASOC_TEST_CPL : test_fn(hd_ASL4[msCPL]);
           cmASOC_TEST_ARR : test_fn(hd_ASL4[msARR]);
          {ENDIF}

          cmARCHIV_ASOC    : zalohuj_archiv(pathSTREAM,'*.'+fn_ext,msgBCK,msgCOPY,nil);

          else Exit

        end
      else Exit;

      ClearEvent(_Event)
    end;