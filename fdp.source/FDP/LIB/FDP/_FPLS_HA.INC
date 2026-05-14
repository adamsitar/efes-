 function _handle_event_FPL_o_sc (var _Event: TEvent; O: PObject;
                                  FPL: pointer;
                                  iFPL: P_OFPL;
                                  sc: PScroller
                                 ): bool;

    var    {$IFDEF FPL4} FP4: DFPL4; {$ENDIF}
           dx,dy, i, ires: int;
           res : string;

    begin
      _handle_event_FPL_o_sc:= false;
      if _Event.what=evNothing then Exit;
      _handle_event_FPL_o_sc:= true;

      if sc<>nil then sc^.get_pos_xy(sc^.pos, dx,dy)
      else begin dx:= 0; dy:= 0 end;

      case _Event.What of

        evKeyDown:
         case _Event.Key of

           kbF4       : SetCommand(Pending,O,cmESTc_strip);
           kbF5       : SetCommand(Pending,O,cmFPLm);

          {$IFDEF MATCA}
           {$IFDEF MACC}
            kbShiftF5 : SetCommand(Pending,O,cmREQm);
           {$ENDIF}

           kbCtrlF12  : SetCommand(Pending,O,cmDEPm_PVO);
           kbAltF12   : SetCommand(Pending,O,cmARRm_PVO);
          {$ENDIF}

           kbAltF4    : SetCommand(Pending,O,cmPREHLAD_cFPL);
           kbAltF5    : SetCommand(Pending,O,cmPREHLAD_mFPL);
           kbAltF3    : SetCommand(Pending,O,cmPREHLAD_oFPL);

          {$IFDEF AIRBASE}
           kbCtrlF5   : SetCommand(Pending,O,cmPREHLAD_mFPL_all);
          {$ELSE}
           kbCtrlF5   : SetCommand(Pending,O,cmPREHLAD_mFPL_all);
          {$ENDIF}

           else _handle_event_FPL_o_sc:= false
         end;


        evCommand, evBroadcast:

          case _Event.Command of

            0 : ;

            {$IFDEF FPL0}
            {$IFNDEF FPLM_DISABLED}

             { --------------
                KRL
               --------------
             }

              {$IFDEF KRL}
               {$IFDEF PROCESS_FPLM}
                cmKRLchg       : if FPL<>nil then _KRL_oprava(sc,FPL)  else KRL_oprava;
                cmKRLcnl       : if FPL<>nil then _KRL_zrusenie(sc,FPL) else KRL_zrusenie;
                cmKRLsprac     : if FPL<>nil then _KRL_spracovanie(sc,FPL) else KRL_spracovanie;

                cmKRLsend      : if FPL<>nil then _odosli_mFPL_(FPL);
                cmKRLsend_macc : if FPL<>nil then
                                    for i:= 0 to NODEpoc-1 do
                                        if strpos(NODEs^[i].desc.inf,nd_MACC)<>nil then
                                           send_mFPL(FPL, NODEs^[i].desc.adr, false);
               {$ENDIF}


               cmPRIJATE_KRL,
               cmPREHLAD_KRL_nase     : prehlad_KRL(0,1);
               cmPREHLAD_KRL_ine      : prehlad_KRL(1,1);
               cmPREHLAD_KRL          : prehlad_KRL(2,1);

               cmPREHLAD_KRL_PPL_nase : prehlad_KRL(0,2);
               cmPREHLAD_KRL_PPL_ine  : prehlad_KRL(1,2);
               cmPREHLAD_KRL_PPL      : prehlad_KRL(2,2);

               cmPREHLAD_KRL_ARCH_nase: prehlad_KRL(0,0);
               cmPREHLAD_KRL_ARCH_ine : prehlad_KRL(1,0);
               cmPREHLAD_KRL_ARCH     : prehlad_KRL(2,0);

               cmPREHLAD_mFPL_KRL     : podanie_FPL_ako_KRL(true);

              {$ENDIF}


             { --------------
                FPL-M
               --------------
             }
              {$IFDEF PROCESS_FPLM}
              {$IFDEF MATCA}
               cm_FPLM_RPL_CHG        : if FPL<>nil then _CHG_FPLM_RPL(sc,FPL);
               cm_FPLM_RPL_CNL        : if FPL<>nil then _CNL_FPLM_RPL(sc,FPL);
               cmPREHLAD_mFPL_RPL     : prehlad_mFPL_RPL;
              {$ENDIF}

               cmFPLm    : formular_mFPL(FPL,letvis,'',true, msg_FPLm,0,nil,hlp_mFPL);

               cmFPLMsend: if FPL<>nil then say_data_sended(_SEND_FPL(FPL));
               cmCHGm    : if FPL<>nil then _CHG_FPL(sc,FPL) else mFPL_CHG;
               cmCNLm    : if FPL<>nil then _CNL_FPL(sc,FPL) else mFPL_CNL;

               {cmDLA    : if FPL<>nil then _DLA_FPL(sc,FPL) else mFPL_DLA;}
               {$IFDEF OPL}
                cmREQm  : if FPL<>nil then _REQ_FPL(sc,FPL) else mFPL_REQ;
                {cmREQ2m : if FPL<>nil then _REQ2_FPL(sc,FPL) else mFPL_REQ2;}
               {$ENDIF}

               cmDEPm    : if FPL<>nil then _DEP_FPL(sc,FPL) else mFPL_DEP;
               cmMZPm    : if FPL<>nil then _MZP_FPL_trat(sc,FPL) else mFPL_MZP;
               cmETOm    : if FPL<>nil then _RTE_FPL_trat(sc,FPL) else mFPL_RTE;
               cmARRm    : if FPL<>nil then _ARR_FPL(sc,FPL) else mFPL_ARR;
               {$IFDEF REPORT_FPLM_ARW}
                cmARWm   : mFPL_ARW;
               {$ENDIF}
              {$ENDIF}

               cmESTm,cmESTm_strip : if ENABLE_FPLM then formular_mFPL(FPL,letvis,cnst_active,true, msg_FPLm,0,nil,hlp_mFPL);
               cmETOm_strip : if ENABLE_FPLM then if FPL<>nil then _CHG_FPL(sc,FPL) else mFPL^.oprava(msg_FPLm_CHG);
               cmCNLm_strip : if FPL<>nil then mFPL^.zrus(FPL,true) else mFPL^.zrusenie(msg_FPLm_CNL);

               {$IFDEF FPLO}
                cmESTo_strip : if ENABLE_FPLM then formular_mFPL(FPL,letvis,cnst_active,true, msg_FPLm,0,nil,hlp_mFPL);
                cmETOo_strip : if ENABLE_FPLM then if FPL<>nil then _CHG_FPL(sc,FPL) else oFPL^.oprava(msg_FPLm_CHG);
                cmCNLo_strip : if FPL<>nil then oFPL^.zrus(FPL,true) else oFPL^.zrusenie(msg_FPLm_CNL);
               {$ENDIF}

               cmFPLMview        : if FPL<>nil then info_mFPL(FPL,'');
               cmFPLMview_strip  : if FPL<>nil then _display_decoded_FPLM (FPL,false,res,ires);


              {$IFDEF MAPY}
               cmFPLMdraw   : if FPL<>nil then zobraz_trat_mFPL(FPL);
              {$ENDIF}

              {$IFDEF PRN}
               cmFPLMprint  : if FPL<>nil then print_mFPL(FPL);
              {$ENDIF}

              {cmPRIJATY_FPL  : ;}


             { --------------
                PREHLADY
               --------------
             }
               cmPRIJATY_FPLm            : prehlad_mFPL(true,false,cnst_all_valid);


               cmPREHLAD_mFPL            : mFPL^.Vypis(tit_actmFPL);
              {$IFDEF FPLO}
               cmPREHLAD_oFPL            : oFPL^.Vypis(tit_actoFPL);
              {$ENDIF}


               cmPREHLAD_mFPL_plan_nase  : prehlad_mFPL(false,false, cnst_planned_);
               cmPREHLAD_mFPL_plan_sicke : prehlad_mFPL(true, false, cnst_planned_);
               cmPREHLAD_mFPL_plan_ine   : prehlad_mFPL_ine;
               cmPREHLAD_mFPL_plan       : prehlad_mFPL_plan;
               cmPREHLAD_mFPL_acc        : prehlad_mFPL_acc;
               cmPREHLAD_mFPL_dep        : prehlad_mFPL_dep;
               cmPREHLAD_mFPL_arr        : prehlad_mFPL_arr;
               cmPREHLAD_mFPL_all        : prehlad_mFPL_vsetky;

               {cmPREHLAD_mFPL_nase      : prehlad_mFPL(false,false, cnst_all_valid);
               cmPREHLAD_mFPL_sicke      : prehlad_mFPL(true,false), cnst_all_valid;}

               cmPREHLAD_mFPL_PPL_nase   : prehlad_mFPL(false,true, cnst_all_valid);
               cmPREHLAD_mFPL_PPL        : prehlad_mFPL(true,true,  cnst_all_valid);

               cmPREHLAD_mFPL_ARCH_nase  : prehlad_mFPL_ARCH(false);
               cmPREHLAD_mFPL_ARCH       : prehlad_mFPL_ARCH(true);
               {cmPREHLAD_oFPL_ARCH      : prehlad_oFPL_ARCH(true);}

               cmLOAD_ARCHIV_mFPL        : spracuj_ukoncene_mFPL;
               cmLOAD_ARCHIV_oFPL        : spracuj_ukoncene_oFPL;

             {$ENDIF}


             { --------------
                FPL-C
               --------------
             }
               {$IFDEF PROCESS_FPLC}
               {$ENDIF}

               cmESTc_strip  : formular_cFPL(FPL,letvis,true, msg_FPLc_EST,pos_frm_FPLC,false,false,false);

               cmETOc_strip  : if ENABLE_FPLC then
                                 if FPL<>nil then formular_cFPL(FPL,letvis,false,msg_FPLc_CHG,pos_frm_FPLC,false,false,false)
                                 else cFPL^.oprava(msg_FPLc_CHG);

               cmCNLc_strip  : if FPL<>nil then cFPL^.zrus(FPL,true)
                               else cFPL^.zrusenie(msg_FPLc_CNL);


               cmFPLCview    : if FPL<>nil then p_info_FPLc(FPL,'');

               {$IFDEF EDD}
                cmPLAN_HIDE  : if FPL<>nil then cFPL^.put_on_board (FPL,false);
                cmPLAN_SHOW  : if FPL<>nil then cFPL^.put_on_board (FPL,true);
               {$ENDIF}

               {$IFDEF FPL4}
                cmFPLC4view  : if read_FPL4(codekey_FPLC(FPL),@FP4)>-1 then
                                  begin
                                    info_FPL4(@FP4,'');
                                    disp_FPL4(@FP4);
                                  end;

               {$ENDIF}

               {$IFDEF MAPY}
                cmFPLCdraw   : if FPL<>nil then zobraz_trat_cFPL(FPL);
               {$ENDIF}

               {$IFDEF PRN}
                cmFPLCprint  : if FPL<>nil then print_cFPL(FPL);
               {$ENDIF}

               cmFPLCtype    : if (FPL<>nil) and (PDcFPL(FPL)^.typ<>'') then _info_TYP(PDcFPL(FPL)^.typ,dx,dy);


               cmPREHLAD_cFPL            : cFPL^.Vypis(tit_actcFPL);
               cmLOAD_ARCHIV_cFPL        : spracuj_ukoncene_cFPL;
               cmPREHLAD_cFPL_ARCH0      : prehlad_cFPL_ARCH(false);
               cmPREHLAD_cFPL_ARCH1      : prehlad_cFPL_ARCH(true);


               else if iFPL<>nil then _handle_event_FPL_o_sc:= _handle_event_on_strip (_Event, FPL,iFPL, dx,dy)

             {$ENDIF}

              else _handle_event_FPL_o_sc:= false
            end

          else _handle_event_FPL_o_sc:= false
        end
      end;


 function _handle_event_FPL (var _Event: TEvent; O: PObject; FPL: pointer): bool;
    begin
      _handle_event_FPL:= _handle_event_FPL_o_sc (_Event,O,FPL,nil,nil)
    end;
