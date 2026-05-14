 constructor O_EXT.Init (_Owner   : PObject;
                         _p_power : pbool;
                         _cfg_FN  : string;

                         { nastavenia : potvrdenia, linka
                         }
                           _lam: int; _async : bool;

                         { spracovavany paket
                         }
                           _ipkt_size, _ibuff_size: word; _is_ibuff0: bool;
                           _pbuff_size: word;

                         { synchronizacia/zalohovanie
                         }
                           _spr_send_ext,
                           _spr_new,_spr_prd,_spr_ed,_spr_del,
                           _spr_err,_spr_err_ed,_spr_err_del,
                           _spr_items_del,_spr_item_del : TNETtyp;
                           _sync_info,_coor_info : pchar;

                         { spracovavane spravy
                         }
                           _p_heads_EXT : Pheads_ICAO; _heads_EXT : word;
                           _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

                         { archivacne premenne
                         }
                          _p_wr, _p_arch, _p_utc{, _p_nl} : pointer;
                          _cl_s, _cl_r : byte;
                          _pathSTREAM,_pathERR, _ext : string
                         );

       var   s: string; c: int; r: single;

       begin
         is_4444:= false;

         NODE_THIS:= ''; NODE_REMOTE:= '';

         EXT_HEADER_ADR:= true;
         CISLO_SPRAVYcfg:= 'c-'+getstr(_cfg_FN,1,['.'])+ext_kod;
         CISLO_SPRAVY24h:= false;
         CISLO_SPRAVY:= 0;

         fn_ext:= _ext;
         ArchDays:= Archiv.ArchDays;

         archive_all_en  := true;
         process_all_adr := false;
         process_all_msg := false;
         process_err_en  := false;
         write_in_nl_en  := false;
         uncomplete_pkt_en := false;

         {pkt_cis:= 0;}
         Tr_:= AbsTime; TrTimeOut:= 60;
         Ts_:= AbsTime; TsTimeOut:= 60;
         isTrTimeOut:= true;
         HeartBeat:= '';

         p_master_line:= nil;

         ed_riadkov := MTK_2_PAGE;
         ed_znakov  := MTK_2_LINE;
         ed_velkost_strany := IcaoEditorPage;

         inherited Init(_Owner, _p_power,_cfg_FN,_async, _ipkt_size,_ibuff_size, _is_ibuff0);

         src_type := letvis;
         dst_set  := [];

         spr_send_ext:= _spr_send_ext;
         spr_new:= _spr_new; spr_prd:= _spr_prd; spr_ed:= _spr_ed; spr_del:= _spr_del;
         spr_err:= _spr_err; spr_err_ed:= _spr_err_ed; spr_err_del:= _spr_err_del;
         spr_items_del:= _spr_items_del; spr_item_del:= _spr_item_del;

         sync_info:= strnew(_sync_info);
         coor_info:= strnew(_coor_info);

         p_heads_EXT:= _p_heads_EXT; heads_EXT:= _heads_EXT;

         p_scroll_data:= nil;
         p_wr:= _p_wr; p_arch:= _p_arch; p_utc:= _p_utc; p_nl:= nil;
         cl_s:= _cl_s; cl_r:= _cl_r;

         pathSTREAM:= _pathSTREAM; if pathSTREAM[length(pathSTREAM)]<>'\' then pathSTREAM:= pathSTREAM+'\';
         _mkdir(pathSTREAM);
         pathERR:= _pathERR; if pathERR[length(pathERR)]<>'\' then pathERR:= pathERR+'\';
         _mkdir(pathERR); _mkdir(pathERR+path_NOT_PROCESSED);


        { buffer pre pakety
        }
         pbuff_size:= _pbuff_size;
         pbuff:= New(PDynamic2, Init(pbuff_size,sizeof(TEXTpkt), @new_EXTpkt,nil,@disp_EXTpkt));


        { register posledne prijatych paketov
        } {$IFDEF SYNCHRONIZE_EXT}
           is_ireg:= false;
           ireg_size:= _pbuff_size;
           ireg:= New(PDynamic2, Init(ireg_size,sizeof(TIREGpkt), @new_REGpkt,nil,@disp_REGpkt));
          {$ENDIF}


        { IFDEF DEBUG}
          testing_fn:= '';
          testing_txt_file:= false;
          testing_one_msg := true;
          test_last_pos   := 0;
        { ENDIF}


        { spracovanie
        }
         okamzite_spracovanie:= false;



        { LAM
        }
         p_heads_LAM:= _p_heads_LAM; heads_LAM:= _heads_LAM;
         LAM_pred_spracovanim:= false;
         if _lam>0 then EXTack:= New(POEXTack,Init(_lam)) else EXTack:= nil;


         initialize_STATUS(false);

         if EXT_DEVICESpoc<max_EXT_DEVICES then
            begin
              EXT_DEVICES[EXT_DEVICESpoc]:= @Self;
              inc(EXT_DEVICESpoc)
            end;

         if async then
            begin
              SaveCOMi(asyncCOM);
              SetCOMi (asyncCOM,_MODE(asyncMODE,true),0,_LCR(asyncBITs,asyncSTOP_BITs,asyncPARITY),$01,$0B)
            end;
       end;


 destructor O_EXT.Done;
      begin
        inherited Done;
        if EXTack<>nil then begin Dispose(EXTack,Done); EXTack:= nil end;
        strdispose(coor_info);
        strdispose(sync_info);
        {$IFDEF SYNCHRONIZE_EXT}
         if ireg <>nil then begin Dispose(ireg,Done); ireg:= nil end;
        {$ENDIF}
        if pbuff<>nil then begin Dispose(pbuff,Done); pbuff:= nil end;
      end;


 function O_EXT.read_cfg(_cfg_FN: string): bool;
    var   res,s: string;
          _err: bool;
    begin
      _err:= false;
      read_cfg:= false;

      if Exists(_cfg_FN)<>0 then RunError('Can not read '+_cfg_FN+'.');
      res:= '';

      power:= read_cfg_bool(_cfg_FN,cfg_POWER,power);

     { Velkost paketu
     }
      ipkt_size := Limit(read_cfg_word(_cfg_FN, cfg_PKT_SIZE,     ipkt_size),EXT_pkt_size_lo,EXT_pkt_size_hi,0);
      {$IFNDEF DEBUG}
       ibuff_size:= Limit(read_cfg_word(_cfg_FN, cfg_REC_BUF_SIZE, ibuff_size),3,300,0);
      {$ENDIF}

     { RS232 ?
     }
      if async then
         begin
           asyncCOM       := read_cfg_word(_cfg_FN,cfg_COM_0X,asyncCOM);
           asyncMODE      := read_cfg_word(_cfg_FN,cfg_COM_MODE,asyncMODE);
           asyncBITs      := read_cfg_word(_cfg_FN,cfg_COM_BITs,asyncBITs);
           asyncSTOP_BITs := read_cfg_word(_cfg_FN,cfg_COM_STOP_BITs,asyncSTOP_BITs);
           asyncPARITY    := _PARITY(read_cfg_str_(_cfg_FN,cfg_COM_PARITY,sPARITY[asyncPARITY]),true);
         end;

      if res<>'' then RunError(_cfg_FN+' -> item "'+res+'" is missing.');

      process_all_adr:= read_cfg_bool(_cfg_FN,cfg_PROCESS_ALL,process_all_adr);

     { Nazov FIR-u
      FIR_adr:= _read_cfg(_cfg_FN,cfg_FIR_ADR,true);
      if FIR_adr='' then res:= cfg_FIR_ADR;
     }

     { Nazov uzla
     }
      NODE_THIS:= _read_cfg(_cfg_FN,cfg_NODE_THIS,true);
      if NODE_THIS='' then res:= cfg_NODE_THIS;
      if getstritems(NODE_THIS,[icao_NXIT])>1 then RunError(_cfg_FN+' '+cfg_NODE_THIS+' More then one address.');

      NODE_REMOTE:= _read_cfg(_cfg_FN,cfg_NODE_REMOTE,true);
      if NODE_REMOTE='' then res:= cfg_NODE_REMOTE;
      if     (not process_all_adr)
         and (    (NODE_REMOTE=NODE_PROMISCUITE)
               or (NODE_THIS=NODE_PROMISCUITE)
             )
         then
         begin
           MessError(_cfg_FN+' Promiscuity mode will be enabled.',true,_err);
           process_all_adr:= true;
         end;

     { Kodovanie
     }
      EXT_HEADER_ADR := read_cfg_bool(_cfg_FN,cfg_HEADER_ADR,EXT_HEADER_ADR);
      CISLO_SPRAVY:= read_cislo(CISLO_SPRAVYcfg);


     { Parametre spracovania
     }
      hold_TLG := read_cfg_word(_cfg_FN,cfg_hold_TLG,hold_TLG);
      hold_ERR := read_cfg_word(_cfg_FN,cfg_hold_ERR,hold_ERR);

      TsTimeOut:= read_cfg_word(_cfg_FN, cfg_Ts_TimeOut, TsTimeOut_);
      TrTimeOut:= read_cfg_word(_cfg_FN, cfg_Tr_TimeOut, TrTimeOut_);
      LAM_TimeOut:= read_cfg_word(_cfg_FN, cfg_LAM_TimeOut, LAM_TimeOut_);

      s:= NL__to_NL(_read_cfg (_cfg_FN,cfg_HeartBeat,false));
      if s<>'' then HeartBeat:= s;

      if res<>'' then RunError(_cfg_FN+' -> item "'+res+'" is missing.');
      read_cfg:= true;

      if _err then writeln
    end;


 procedure O_EXT.initialize_STATUS(_draw: bool);
     begin
       initialize_ERR(_draw)
     end;

 procedure O_EXT.initialize_ERR(_draw: bool);
     var   c : int;
           s : string;
     begin
       is_ALR:= false {najmladsi_subor(pathALR, '*.'+ext_ALR)<>''};

       {val(delchar(najmladsi_subor(pathERR, _fn_ERRmask(ext_ERR)),setPism+['.','\']),cis_ERR,c);
       is_ERR:= cis_ERR<>0;}
       is_ERR:= najmladsi_subor(pathERR, _fn_ERRmask(ext_ERR))<>'';

       {val(delchar(najmladsi_subor(pathERR, _fn_ERRmask(ext_ERS)),setPism+['.','\']),cis_ERS,c);
       is_ERS:= cis_ERS<>0;}
       is_ERS:= najmladsi_subor(pathERR, _fn_ERRmask(ext_ERS))<>'';

      (*{$IFDEF STATUS}
       if _draw then
          begin
           {$IFDEF ALR} btALR^.visibility(is_ALR); {Hide; btALR^.Draw;} {$ENDIF}
           {$IFDEF ERR} btERS^.visibility(is_ERS); {Hide; btERS^.Draw}  {$ENDIF}
          end
       else begin
             {$IFDEF ALR} btALR^.visible:= is_ALR; {$ENDIF}
             {$IFDEF ERR} btERS^.visible:= is_ERS; {$ENDIF}
            end
      {$ENDIF}*)
     end;



 procedure indicate_ext (is: int);
     begin
       if p_indicate_ext<>nil then proc_indicate_process(p_indicate_ext)(is)
     end;
