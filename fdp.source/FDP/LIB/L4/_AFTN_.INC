 procedure save_last_HeartBeat(last_HeartBeat: word);
     var   f: file of word;
     begin
       assign(f,'hb'+ext_kod);
       rewrite(f);
       write(f,last_HeartBeat);
       close(f);
     end;

 procedure read_last_HeartBeat(var last_HeartBeat: byte);
     var   f: file of word;
           w: word;
     begin
       last_HeartBeat:= min;
       if Exists('hb'+ext_kod)<>0 then Exit;
       assign(f,'hb'+ext_kod);
       reset(f);
       read(f,w); last_HeartBeat:= w;
       close(f);
     end;


 procedure O_AFTN.initialize_STATUS(_draw: bool);
     begin
       inherited initialize_STATUS(_draw);
       initialize_TLG(_draw)
     end;

 procedure O_AFTN.initialize_TLG(_draw: bool);

     function is_tlg(prty: string; var is: bool): bool;
        var   k : int;  s : string;
        begin
          if prty[1]<>'.' then prty:= '.'+prty;
          s:= najmladsi_subor(pathTLG,'*'+prty);
          is:= s<>'';
          is_tlg:= is
        end;

     begin
       is_tlg(tlgSS, is_SS);
       is_tlg(tlgFF, is_FF);
       is_tlg(tlgKK, is_KK);

      (*
      {$IFDEF STATUS}
       btSS^.parameters(@tlg_SS,false, @is_SS,true);
       btFF^.parameters(@tlg_FF,false, @is_FF,true);
       btKK^.parameters(@tlg_KK,false, @is_KK,true);
       if _draw then
          begin
            btSS^.Hide; btSS^.Draw;
            btFF^.Hide; btFF^.Draw;
            btKK^.Hide; btKK^.Draw
          end
      {$ENDIF}
      *)
     end;


 constructor O_AFTN.Init(_cfg_OB : string;
                         { synchronizacia/zalohovanie
                         }
                          _sync_info,_coor_info : pchar;
                         { spracovanie spravy
                         }
                          _p_heads_ICAO: Pheads_ICAO; _heads_ICAO: word
                        );

       var   bdata : pbytes;
             bsize : word;
             s     : string;

       begin
         inherited Init(nil,@power_AFTN,
                        AFTNcfg,_cfg_OB,

                        0,true,

                        sizeof(TAFTNpkt),AFTN_IBUFF_SIZE, false,
                        AFTN_PBUFF_SIZE,

                        spr_AFTN_SEND,
                        spr_AFTN_NEW,spr_AFTN_PRD,spr_AFTN_ED,spr_AFTN_DEL,
                        spr_AFTN_ERR,spr_AFTN_ERR_ED,spr_AFTN_ERR_DEL,
                        spr_AFTN_DEL_ITEMS, spr_AFTN_DEL_ITEM,
                        _sync_info,_coor_info,

                        _p_heads_ICAO,_heads_ICAO, { @hd_AFTN, sizeof(hd_AFTN) div sizeof(Thead_ICAO), }
                        nil,0,

                        @writeln_AFTN, @archive_AFTN, @writeln_AFTN_utc,
                        cl_AFTN_send, cl_AFTN_rec,
                        path_AFTN, path_AFTN+spath_ERR, extAFTN
                       );

         src_type:= _FDP_DEF.aftn;
         spr_tlg:= spr_AFTN_TLG;

         pathTLG:= path_TLG {path_AFTN+'TLG\'};
         _mkdir(pathTLG); _mkdir(pathTLG+path_NOT_PROCESSED);
         ArchDays:= archdaysAFTN;

         Ts_:= 0;

        { predefinovanie internych premennych, ktore sa nemenia stale :
        } process_all_adr:= true;
          archive_all_en:= true;
          process_err_en:= true;
          write_in_nl_en:= true;

          {$IFDEF PROCESS_FPL4}
           spracovanie_fpl4:= true;
          {$ENDIF}

         {NODE_REMOTE:= 'AFTN';}

        { Pretransformovanie citatelneho konca spravy
          do MTK-2 a inverzneho kodu.
          Dovod : pri prijme (v preruseni) sa vyhodnocuje
                  konic spravy -> tak je to rychlejsie
                  a zaroven transformacne moduly je mozne
                  hodit do ovr-leja.
        }
         s:= aftnEOT+' ';
         ascii_to_mtk2bin(@s[1],length(s),false, bdata,bsize, true,asyncBITs);

         if (bsize>0) then bdata^[bsize-1]:= 0;
         p_aftnEOT:= pchar(bdata);
         kod_aftnEOT:= strlen(p_aftnEOT);

         AFTNpkt:= ipkt;
         fillchar(AFTNpkt^,ipkt_size,0); { musi byt, inak sa nevyhodnoti koniec spravy }

         {sended_data:= '';}

         {$IFDEF SYNCHRONIZE_EXT}
          {is_ireg:= true;}
         {$ENDIF}
       end;


 destructor O_AFTN.Done;
      begin
        inherited Done;
        strdispose(p_aftnEOT)
      end;


 function O_AFTN.read_cfg (_cfg_FN: string): bool;
    var   res : string;
    label X;
    begin
      res:= '';

     { implicitne nastavenia
     }
      process_all_adr:= true;

      asyncCOM       := 2;
      asyncMODE      := 1200;
      asyncBITs      := MTK_2_BITes;
      asyncSTOP_BITs := 2;
      asyncPARITY    := NONE;


     { spolocne nastavenia "ext"
     }
      inherited read_cfg(_cfg_FN);

      ADR_I:= _read_cfg(_cfg_FN,cfg_MTK_ADR_I,true);
      ADR_O:= _read_cfg(_cfg_FN,cfg_MTK_ADR_O,true);
      if (ADR_O='') then begin res:= cfg_MTK_ADR_O; goto X end;
      if not ((length(ADR_O) in [_MTK_ADR_lo,_MTK_ADR_hi])) then begin res:= cfg_MTK_ADR_O; goto X end;
      ADR_O_THIS:= ADR_O;

      CHNL_I:= _read_cfg(_cfg_FN,cfg_MTK_CHNL_I,true);
      CHNL_O:= _read_cfg(_cfg_FN,cfg_MTK_CHNL_O,true);
      if (CHNL_O='') then begin res:= cfg_MTK_CHNL_O; goto X end;
      if (length(CHNL_O)<>_MTK_CHNL) then begin res:= cfg_MTK_CHNL_O; goto X end;

      (*ADR_I:= _read_cfg(_cfg_FN,cfg_AFTN_ADR_I,true);
      {if ADR_I='' then begin res:= cfg_AFTN_ADR_; goto X end;}

      ADR_O:= _read_cfg(_cfg_FN,cfg_AFTN_ADR_O,true);
      if (ADR_O='') then begin res:= cfg_AFTN_ADR_O; goto X end;
      if not ((length(AFTN_ADR_O) in [_MTK_ADR_lo,_MTK_ADR_hi])) then begin res:= AFTN_ADR_O; goto X end;

      CHNL_I:= _read_cfg(_cfg_FN,cfg_AFTN_CHNL_I,true);
      {if CHNL_I='' then begin res:= cfg_AFTN_CHNL_I; goto X end;}

      CHNL_O:= _read_cfg(_cfg_FN,cfg_AFTN_CHNL_O,true);
      if (CHNL_O='') then begin res:= cfg_AFTN_CHNL_O; goto X end;
      if (length(AFTN_CHNL_O)<>_MTK_CHNL) then begin res:= cfg_AFTN_CHNL_O; goto X end;
      *)

      ALIAS_NODE:= _read_cfg(_cfg_FN,cfg_ALIAS_NODE,true);
      process_all_adr:=  ALIAS_NODE<>'';


     { aftn
     }
      archive_AFTN_bin := read_cfg_bool(_cfg_FN,cfg_archive_AFTN_bin,archive_AFTN_bin);


     { heartbeat
     }
      TsTimeOut:= TsTimeOut*60;
      TrTimeOut:= read_cfg_word(_cfg_FN, cfg_Tr_TimeOut, MTK_2_Tr_TimeOut)*60;

      HeartBeat_ID      := read_cfg_str_(_cfg_FN, cfg_HeartBeat_ID,'');
      HeartBeat_PERIODE := read_cfg_word(_cfg_FN, cfg_HeartBeat_PERIODE, 20);
      HeartBeat_MIN     := read_cfg_word(_cfg_FN, cfg_HeartBeat_MIN, 1);

      read_last_HeartBeat(last_HeartBeat);


      X: if res<>'' then RunError(_cfg_FN+' '+cfg_NODE_THIS+' '+res+'.');

      read_cfg:= res=''
    end;
