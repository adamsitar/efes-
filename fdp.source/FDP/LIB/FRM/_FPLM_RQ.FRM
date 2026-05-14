{$IFDEF PROCESS_FPLM}

 function is_done_REQ_FPL(FPL: PDmFPL): bool; far;
    var   FPLi : DmFPL;
          b    : bool;
    begin
     is_done_REQ_FPL:= false;
     {$IFDEF MACC}
      if isFPLM_SAVED then
         begin
           NoSound;
           if isFPLM_REQ and (read_mFPL(codekey_FPLM(FPL), @FPLi)<>-1) then
              begin
                isFPLM_SAVED:= false;
                is_done_REQ_FPL:= FPLi.stat<>cnst_prop;
                disp_mFPL(@FPLi)
              end
           else is_done_REQ_FPL:= true
         end
      else is_done_REQ_FPL:= false
     {$ENDIF}
    end;

{$ENDIF}


constructor TREQ_FPL.Init(var _x,_y,  _mode: int;
                          _title: string;

                          _FPL,_REQ : PDmFPL;

                          _p_dla,_p_ack,_p_dcl,_p_chg,
                          _handle_rqst : pointer;
                          _beep        : bool;

                          _hlpXXX      : Pchar     { ukazovatel na help  }
                         );
      begin
        TmFPLform.Init(_x,_y, _mode, _title,

                       @mFPL_init, nil, i_15M,
                       _FPL,_REQ,
                       @_FPL^.rec,letvis,'',false,
                       nil,nil,nil,
                       _hlpXXX
                       {$IFDEF ODOSLI_ULOZ}, false {$ENDIF}
                      );

        FPL:= adr_var;
        REQ:= adr_data;

        p_is_data:= nil; { objekt odvodeny od formulara, nie od pripomienky }

        is_rqst:= true;
        p_dla:= _p_dla; p_ack:= _p_ack; p_dcl:= _p_dcl; p_chg:= _p_chg;
        p_handle_rqst:= _handle_rqst;

        beeping  := _beep;
        beep_par := _REQ;

        {$IFDEF MACC} {$IFDEF PROCESS_FPLM}
          {PBFunc := @is_done_REQ_FPL}
        {$ENDIF} {$ENDIF}

        {is_formular_REQ_FPL:= true}
      end;


destructor TREQ_FPL.Done;
     begin
       inherited Done;
       {is_formular_REQ_FPL:= false;}
     end;


procedure TREQ_FPL.Idle(var _Event: TEvent);
    const r : real = 0;
    var   l : real;
    begin
      inherited Idle(_Event);
      {$IFDEF MACC} {$IFDEF OPL}
        if r + 60 > absTime then Exit;
        r:= absTime;
        l:= dT_deactive_FPLM_REQ;
        if (REQ^.start.cas + l*60 < absTime) and (last_kbhit + 60 < absTime) then
           begin
             if _ziadost_o_pripomienku (nil, REQ) then
                begin
                  REQ^.stat:= cnst_prop+cnst_prop;
                  save_mFPL(REQ)
                end;
             is_cancel:= true
           end;
      {$ENDIF} {$ENDIF}
    end;


{$IFDEF AIRBASE}
 procedure TREQ_FPL.init_buttons(x,y: int);
     var   bt1: PDialogButton;
           xt,yt, yi,c : int;
           _kbHot: char;
     begin
       Win^.get_btXY(0,0, xt,yt);
       bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titACK)), cmREQ_ACK {_}, titACK, icKey,icText));

       Win^.get_btXY(0,1, xt,yt);
       bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titCOR)), cmREQ_CHG {_}, titCOR, icKey,icText));

       Win^.get_btXY(0,2, xt,yt);
       bt1:= New(PDialogButton,Init(Win,xt,yt,GetAltCode(get_HotKey(_kbHot,titCANCEL)),cmREQ_DCL{_},  titCANCEL,icKey,icText));

       bt_y:= 5;
       init_buttons_trat(x,y);
     end;
{$ENDIF}


{$IFDEF MACC}
 procedure TREQ_FPL.init_buttons(x,y: int);
      var   bt1 : PDialogButton;
            xt,yt, yi,c : int;
            _kbHot : char;
      begin
        Win^.get_btXY(0,0, xt,yt);
        bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titACK)), cmREQ_ACK, titACK, icKey,icText));

        {Win^.get_btXY(0,1, xt,yt);
        bt1:= New(PDialogButton,Init(Win, xt,yt, hkCOR, cmREQ_CHG, titCOR, icKey,icText));}

        Win^.get_btXY(0,1, xt,yt);
        bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titDIS)), cmREQ_DCL, titDIS, icKey,icText));

        Win^.get_btXY(0,2, xt,yt);
        bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titDLA)), cmREQ_DLA, titDLA, icKey,icText));

        bt_y:= 5;
        init_buttons_trat(x,y);
      end;

 procedure TREQ_FPL.update_formular;
     var   FPLn : DmFPL;
           title: string;
           bres : bool;
     begin
       if (REQ=nil) or (read_mFPL(codekey_FPLM(REQ),@FPLn)<0) then Exit;

       bres:= chg_mFPL(FPL,@FPLn);
       if bres then
          begin
            if    _ziadost_o_pripomienku (nil, @FPLn)
               or _odlozena_ziadost_o_pripomienku (nil, @FPL) then
               begin
                 title:= tit_nova_pripominenka_FPLM;
                 info_mFPL(@FPLn, title);
                 copy_mFPL(@FPLn,REQ);
                 inherited update_formular
               end
            else begin
                   title:= tit_zmeneny_FPLM;
                   Say2(code_FPLM_7a(FPL),title);
                   is_cancel:= true
                 end;
            if title<>'' then ;
            disp_mFPL(@FPLn)
          end
     end;
{$ENDIF}


procedure TREQ_FPL.handle_rqst(_rqst_res: Trqst);
    begin
      if is_rqst and (_rqst_res<>_) then
         begin
          {$IFDEF MACC}
            if     (_rqst_res=ack)
               and (adr_var<>nil) and (adr_data<>nil)
               and chg_mFPL(adr_var,adr_data)
                   then _rqst_res:= chg;
          {$ENDIF}
           if REQ<>nil then fillchar(REQ^.rec,sizeof(REQ^.rec),0);
           if FPL<>nil then fillchar(FPL^.rec,sizeof(FPL^.rec),0);
           case _rqst_res of
             dla : if p_dla<>nil then Tproc_p2(p_dla)(adr_var,adr_data);
             ack : if p_ack<>nil then Tproc_p2(p_ack)(adr_var,adr_data);
             chg : if p_chg<>nil then Tproc_p2(p_chg)(adr_var,adr_data);
             dcl : if p_dcl<>nil then Tproc_p2(p_dcl)(adr_var,adr_data);
           end;
           if p_handle_rqst<>nil then Tproc_rp2(p_handle_rqst)(_rqst_res,adr_var,adr_data);
         end
    end;


procedure TREQ_FPL.HandleEvent(var _Event: TEvent);
    begin
      {$IFDEF DEBUG}
        if isKey (_Event, #11) then net_pkt_test(paramstr(1),-1,-1);
      {$ENDIF}
      inherited HandleEvent(_Event);
      {$IFDEF MACC}
       if     (isCommand(_Event,cmFPLMrec))
          and (_Event.Box<>nil) and (REQ<>nil)
          and (eq_mFPL(PDmFPL(_Event.Box^),REQ))
              then is_update:= true;
      {$ENDIF}
    end;


procedure TREQ_FPL.spracovany_plan(plan: pointer);
    var   FPLn : PDmFPL;
    begin
      FPLn:= plan;
      if (not eq_mFPL(REQ,FPLn)) or (not chg_mFPL(REQ,FPLn)) then Exit;
      Say2(msgMESS,tit_zmeneny_plan);
      is_cancel:= true
    end;
