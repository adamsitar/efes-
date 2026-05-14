{ Dolezite :
  -----------
  V slucke by sa nemal program zastavovat a cakat na spracovanie dat,
  pretoze sa moze stat, ze zatial nevyhodnoti ostane pakety.
}

{
  1. dalsie rozoslanie
     -----------------
      - funkcie pre dekodovanie nastavia prijemcu do pola rec
      - add distribuuje na uzly oznacene ako EST
      - inak je distribucia riesena falsim volanim distribute s parametrami pre OPL

  2. nastavenie priznkov prijatia planov:
     ------------------------------------
        FPL,KRL,ZAM,PRS  - predbezne plany
        DVZ,QGO          - tiez ine ako dnesnie spravy

  3. pri spracovani sprav o diverzii je jedna vynimka:
     ------------------------------------------------------
        letisko posle spravu na protilahle letisko i na server
        letisko prijmu dostane spravu od letiska odoslania a nasledne
        i od servera, tu musi ignorovat


  4. Pri pouziti Reportu musia byt spravy najprv nahrate, aby mali
     spravne priradene "cis" pre kluce...


  5. distribuciu v FDP_EDD robi add,
     a aby som nemal vela direktiv vo volani,
     distribuciu robi _pkt_...

}


{$I _rec_sys.inc}
{$I _rec_rdp.inc}
{$I _rec_4fpl.inc}

procedure TFDP_NET.decode_app_data_pkt(var pkt: TNETpkt; _stream: bool);
    var   b1,b2,b3 : bool;
    begin

      inherited decode_app_data_pkt(pkt,_stream);

      case pkt.head.typ of

        0  : ;


       { --------------------------------------------------------
         Spracovanie planov a ich zaradenie do datovych struktur
         תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       }

        spr_NUDZA       : ;


        {$IFDEF SPR}
         spr_SPR        : _pkt_SPR_REC(pkt); {_de...(pkt, sizeof(DSPR), @disp_SPR, @decode_SPR, nil,nil,@_pkt_SPR, nil,true);}
         spr_SPR_LAM    : _pkt_SPR_LAM(pkt);

         (*spr_SPRAVA     : {_decode_data_pkt(pkt, sizeof(DSPR), @disp_SPR, @decode_SPR, nil, @save_SPR, @_pkt_SPR, nil,true)};
         spr_TELEGRAM   : {_decode_data_pkt(pkt, sizeof(DSPR), @disp_SPR, @decode_SPR, nil, @save_SPR, @_pkt_SPR, nil,true)};
         spr_PRECITANE  : { decode_pkt_SPR_ACK(pkt)};*)
        {$ENDIF}


        spr_SECTOR      : { Nie je to este odladene... };


        {$IFDEF RDP_ACCEPT}
         spr_ACCEPT,
         spr_UNACCEPT,
         spr_HANDOVER,
         spr_UNHANDOVER : _pkt_TARGET_CONTROL (pkt);  { Nie je to este odladene... }
        {$ENDIF}


        {$IFDEF SSR_MANAGEMENT}
         spr_SSR_ERR  : _pkt_SSR_ERR_REC (pkt);
         spr_SSR_COR  : _pkt_SSR_ERR_COR (pkt);
        {$ENDIF}


        {$IFDEF FPL4}
         spr_FPL4      : if _stream then save_tmp_pkt(pkt)
                         else _decode_data_pkt(pkt,sizeof(DFPL4),@disp_FPL4,@decode_FPL4,nil,nil,@_pkt_FPL4,nil,false);

         spr_FPL4_MES,
         spr_FPL4_REQ,
         spr_FPL4_DATA : reports_FDP^.save_rep(pkt.head.typ,pkt.ods,'','',pkt.pkt.dlz,pkt.pkt.data);
        {$ENDIF}

        {$IFDEF RPL}
         {spr_RPL      : if _stream then save_tmp_pkt(pkt)
                        else _decode_data_pkt(pkt, sizeof(DRPL), @disp_RPL, @decode_RPL, nil,nil,@_pkt_RPL, nil,false);}
        {$ENDIF}

        {$IFDEF PLN}
         spr_PLN      : if _stream then save_tmp_pkt(pkt)
                        else _decode_data_pkt(pkt, sizeof(DPLN), @disp_PLN, @decode_PLN, nil,nil,@_pkt_PLN, nil,false);
        {$ENDIF}


        {$IFDEF FPL0}
         spr_FPLC     : _decode_data_pkt(pkt, sizeof(DcFPL), nil,
                                         @decode_FPLC, @_pkt_FPLC_, nil,nil,nil, false
                                        );
        {$IFNDEF FPLM_DISABLED}
         spr_FPLM     : _decode_data_pkt(pkt, sizeof(DmFPL), @disp_mFPL,
                                         @decode_FPLM, @_accept_FPLm, nil, @_pkt_FPLM, nil,false
                                        );
        {$ENDIF}
        {$ENDIF}


        {$IFDEF ZAM}
         spr_ZAM      : _decode_data_pkt(pkt, sizeof(TZAM), @disp_ZAM, @decode_ZAM, nil,nil, @_pkt_ZAM, nil,false);
        {$ENDIF}


        {$IFDEF DVZ}
         spr_DVZ      : _decode_data_pkt(pkt,sizeof(TDVZ),@disp_DVZ,@decode_DVZ,nil,nil,@_pkt_DVZ,nil,false);
        {$ENDIF}


        {$IFDEF QGO}
         spr_QGO      : _decode_data_pkt(pkt,sizeof(TQGO),@disp_QGO,@decode_QGO,nil,nil,@_pkt_QGO,nil,false);
        {$ENDIF}

        {$IFDEF RTZ}
         spr_RTZ      : _decode_data_pkt(pkt,sizeof(TRTZ),@disp_RTZ,@decode_RTZ,nil,nil,@_pkt_RTZ,nil,false);
        {$ENDIF}


        {$IFDEF PRZ}
         spr_PRZ      : _decode_data_pkt(pkt, sizeof(TPRZ), @disp_PRZ, @decode_PRZ, nil,nil, @_pkt_PRZ, nil,false);
         spr_PRN      : _decode_data_pkt(pkt, sizeof(TPRN), @disp_PRN, @decode_PRN, nil,nil, @_pkt_PRN, nil,false);
         spr_PRN_VLIS : _pkt_VLIS (pkt);
        {$ENDIF}

        {$IFDEF PRS}
         spr_PRS      : _decode_data_pkt(pkt, sizeof(TPRS), @disp_PRS, @decode_PRS, nil,nil, @_pkt_PRS, nil,false);
        {$ENDIF}

        {$IFDEF FUA_DATA}
         spr_AUP      : _pkt_AUP(pkt);
         spr_UUP      : _pkt_UUP(pkt);
        {$ENDIF}


        {$IFDEF MET}
         spr_SYNOP    : {_decode_data_pkt(pkt, sizeof(TSYN), @disp_SYN, @decode_SYN, nil, @nil, @_pkt_SYN, nil,false)};
         spr_METAR    : {_decode_data_pkt(pkt, sizeof(TMET), @disp_MET, @decode_SYN, nil, @nil, @_pkt_MET, nil,false)};
         {$IFDEF MET_RLI}
          spr_MRL     : _pkt_MRL (pkt);
         {$ENDIF}
        {$ENDIF}


        else { --------------------------------------------------------
               Spracovanie sprav v povodnom formate
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             } {$IFDEF DATA_BIN}
                 if decode_app_data_bin_pkt(pkt,_stream) then
                 else
               {$ENDIF}

             { --------------------------------------------------------
               Spracovanie datoveho prudu od AFTN
               תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             } {$IFDEF SYNCHRONIZE_EXT} {$IFDEF AFTN}
                 if _stream then save_tmp_pkt(pkt)
                 else if DEV_AFTN<>nil then DEV_AFTN^.decode_NETpkt(pkt)
               {$ENDIF} {$ENDIF}
      end
    end;


{$IFDEF DATA_BIN}

  function  TFDP_NET.decode_app_data_bin_pkt(var pkt: TNETpkt; _stream: bool): bool;
      begin

        decode_app_data_bin_pkt:= true;

        case pkt.head.typ of

          0  : ;


          {$IFDEF SPR}
           spr0_SPR      : _pkt_SPR_REC(pkt); {_dec...(pkt,sizeof(DSPR),@disp_SPR,@decode0_SPR,nil,nil,@_pkt_SPR,nil,true);}
           spr0_SPR_LAM  : _pkt_SPR_LAM(pkt);
          {$ENDIF}

          spr0_SECTOR_PASSWORD : decode_SECTOR_PASSWORD(pkt);


          {$IFDEF RDP_ACCEPT}
           spr0_RDP_A,
           spr0_RDP_UA,
           spr0_RDP_H,
           spr0_RDP_UH   : _pkt_RDP_A(pkt);
          {$ENDIF}


          {$IFDEF PLN}
           spr0_PLN      : if _stream then save_tmp_pkt(pkt)
                           else _decode_data_pkt(pkt,sizeof(DPLN), @disp_PLN,@decode0_PLN,nil,nil,@_pkt_PLN,nil,false);
          {$ENDIF}

          {$IFDEF FPL4}
           spr0_FPL4     : if _stream then save_tmp_pkt(pkt)
                           else _decode_data_pkt(pkt,sizeof(DFPL4),@disp_FPL4,@decode0_FPL4,nil,nil,@_pkt_FPL4,nil,false);

          {$ENDIF}

          {$IFDEF FPL4_ACT}
           {spr0_REQ_ACT  : reports_FPL4^.save_rep(pkt.head.typ,pkt.ods,'','',pkt.pkt.dlz,pkt.pkt.data);
           spr0_REQ_MES,
           spr0_REQ_EST : reports_FPL4^.save_rep(pkt.head.typ,pkt.ods,'','',pkt.pkt.dlz,pkt.pkt.data);}
          {$ENDIF}


          {$IFDEF FPL0}
           spr0_cFPL  : _decode_data_pkt(pkt, sizeof(DcFPL), nil,
                                         @decode0_cFPL, @_pkt_FPLC_, nil,nil,nil,false
                                        );
          {$IFNDEF FPLM_DISABLED}
           spr0_mFPL  : _decode_data_pkt(pkt, sizeof(DmFPL), @disp_mFPL,
                                         @decode0_mFPL, @_accept_FPLm,nil, @_pkt_FPLM, nil,false
                                        );
          {$ENDIF}
          {$ENDIF}


          {$IFDEF TRENAZER}
           spr0_RDP_cFPL : _decode_data_pkt(pkt, sizeof(DcFPL), nil,
                                            @decode0_cFPL_RDP, @_pkt_FPLC_, nil,nil,nil, false
                                           );

           spr0_RDP_mFPL : _decode_data_pkt(pkt, sizeof(DmFPL),
                                            @disp_mFPL, @decode0_mFPL_RDP, nil, @save_mFPL, @_pkt_FPLM, nil,false
                                           );
          {$ENDIF}


          {$IFDEF ZAM}
           spr0_ZAM  : _decode_data_pkt(pkt,sizeof(TZAM),@disp_ZAM,@decode0_ZAM,nil,nil,@_pkt_ZAM,nil,false);
          {$ENDIF}


          {$IFDEF DVZ}
           spr0_DVZ  : _decode_data_pkt(pkt,sizeof(TDVZ),@disp_DVZ,@decode0_DVZ,nil,nil,@_pkt_DVZ,nil,false);
          {$ENDIF}


          {$IFDEF QGO}
           spr0_QGO  : _decode_data_pkt(pkt,sizeof(TQGO),@disp_QGO,@decode0_QGO,nil,nil,@_pkt_QGO,nil,false);
          {$ENDIF}


          {$IFDEF PRZ}
           spr0_PRZ       : _decode_data_pkt(pkt, sizeof(TPRZ), @disp_PRZ, @decode0_PRZ, nil,nil, @_pkt_PRZ, nil,false);
           spr0_PRN       : _decode_data_pkt(pkt, sizeof(TPRN), @disp_PRN, @decode0_PRN, nil,nil, @_pkt_PRN, nil,false);
           spr0_PRN_VLIS  : _pkt_VLIS(pkt);
          {$ENDIF}

          {$IFDEF PRS}
           spr0_PRS       : _decode_data_pkt(pkt,sizeof(TPRS),@disp_PRS,@decode0_PRS,nil,nil,@_pkt_PRS,nil,false);

           {$IFDEF CONNECT_TO_FDA}
            spr0_RDPNX_PRS,
            spr0_PRS_FDA   : _decode_data_pkt(pkt,sizeof(TPRS),@disp_PRS,@decode0NX_PRS,nil,nil,@_pkt_PRS_FDA,nil,false);
           {$ENDIF}
          {$ENDIF}


          {$IFDEF MET}
           spr0_SYN  : _decode_data_pkt(pkt,sizeof(TSYN),@disp_SYN,@decode_SYN,nil,nil, @_pkt_SYN, nil,false);
           {$IFDEF MET_RLI}
            spr0_MRL : _pkt_MRL(pkt);
           {$ENDIF}
          {$ENDIF}

          else decode_app_data_bin_pkt:= false
        end;

      end;

{$ENDIF}
