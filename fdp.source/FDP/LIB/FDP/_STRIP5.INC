constructor O_STRIP.Init(_items,_data_size : word;

                         _new_item,
                         _format_item,
                         _disp_item : pointer;

                         _eq,
                         _id,
                         _chg,
                         _poz,
                         _est : pointer;

                         _distribute : pointer;  { TNET_distribute_rdp_pkt  }
                         _send       : pointer;  { TNET_send_pkt }
                         _en_net     : bool;

                         _item_list  : pointer;
                         _item_dx,_item_dy : int;
                         _get_item_dx,_get_item_dy : pointer;

                         _p_viewer : PScrollInd;
                         {$IFDEF MAPY}
                          _p_kresli : pointer;
                         {$ENDIF}

                         {$IFDEF EDD}
                          _adrBOARD : PPObject;
                          _cmADD,_cmCHG,_cmDEL,_cmCLR: word;

                          _skupina         : string;
                          _p_strip_draw    : pointer;
                          _p_strip_handler : pointer;
                         {$ENDIF}

                         var _p_PRN  : bool;
                         _p_print    : pointer;

                         _save       : pointer;
                         _zobraz     : pointer;
                         _formular   : pointer;
                         _p_comp     : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
                         _p_handler  : pointer;

                         {_fn_ext : string;}
                         _p_nameDB, _p_decodeDB : pointer;
                         _riadkovDB : byte;
                         _p_codekey : pointer;

                         _limit_add, _limit_cnl, _limit_del : pint;
                         _nacitanie : bool;

                         _hlpXXX    : Pchar
                        );
      begin
        if not _en_net then
           begin
             _send:= nil;
             _distribute:= nil;
             {_message:= nil}
           end;

        inherited Init(_items,_data_size,
                       _new_item,_format_item,_disp_item,

                       _eq,_id,_chg,_poz,_est,

                       _distribute,_send,

                       _item_list,
                       _item_dx,_item_dy,
                       _get_item_dx,_get_item_dy,
                       _p_viewer,
                       {$IFDEF MAPY} _p_kresli, {$ENDIF}
                       _p_PRN,_p_print,

                       _save,_zobraz,_formular,_p_comp,_p_handler,

                       _p_nameDB,_p_decodeDB, _riadkovDB,_p_codekey,

                       _limit_add, _limit_cnl, _limit_del,
                       _nacitanie,

                       _hlpXXX
                      );

        {$IFDEF EDD}
          adrBOARD:= _adrBOARD;
          cmADD:= _cmADD; cmCHG:= _cmCHG; cmDEL:= _cmDEL; cmCLR:= _cmCLR;
          p_strip_draw:= _p_strip_draw;
          skupina:= _skupina;
          p_strip_handler:= _p_strip_handler;
          p_PRN2:= @c_true
        {$ENDIF}
      end;


{$IFDEF EDD}

  {$IFDEF PRN}
   procedure O_STRIP.set_printed (p: pointer; was: bool);
      begin
        {$IFDEF EDD}
          if (p_PRN2<>nil) and (not p_PRN2^) then Exit;
        {$ENDIF}
        inherited set_printed (p,was)
      end;
  {$ENDIF}

  function  O_STRIP.vypis_plan(ind: int; _sort,_novy: bool): bool;
      var   bres  : bool;
            cmXXX : word;
            p     : pointer;
      begin
        p:= ap^[ind];
        bres:= inherited vypis_plan(ind, _sort,_novy) and (not PLANZET_MAPA);
        vypis_plan:= bres;
        if adrBOARD=nil then Exit;

        if bres then
           begin
             if _novy then cmXXX:= cmADD else cmXXX:= cmCHG;
             zarad_strip(ind, cmXXX)
           end;
       {$IFDEF SECTORS}
        if (p=ap^[ind]) then set_on_sector(ap^[ind],bres);
       {$ENDIF}
       {$IFDEF EDD}  { Pocet planov na planzete treba update-ovat }
         send_mail(@Self,appGui, cmEDD_STATUS, one, nil,0);
       {$ENDIF}
        vypis_plan:= bres
      end;


  procedure O_STRIP.zmaz_plan(ind: int; _zrus: bool);
      var   cmXXX : word;
      begin
        inherited zmaz_plan(ind, _zrus);
        if adrBOARD=nil then Exit;

        if _zrus then cmXXX:= cmDEL else cmXXX:= cmCLR;
        if not PLANZET_MAPA then zarad_strip(ind, cmXXX);
       {$IFDEF SECTORS}
        set_on_sector(ap^[ind],false);
       {$ENDIF}
       {$IFDEF EDD}  { Pocet planov na planzete treba update-ovat }
         send_mail(@Self,appGui, cmEDD_STATUS, one, nil,0)
       {$ENDIF}
      end;


  procedure O_STRIP.strip(ind, x,y: int; b: bool);
      begin
        if (ind>=0) and (ind<=top) and (p_strip_draw<>nil) then
           TProc_pi2b(p_strip_draw)(ap^[ind], x,y, b)
      end;

  {
    sprava o type planu a jeho indexe v poli planov
  }
  procedure O_STRIP.zarad_strip(ind: int; cmXXX: word);
      const mail_size = sizeof(PSTRIP)+sizeof(int);
      var   mail_buff : array[0..mail_size-1] of byte;
            p,s       : pointer;
      begin
        if adrBOARD=nil then Exit;
        p:= @mail_buff;
        s:= @self;
        move(s,p^,sizeof(PSTRIP)); incptr(p,sizeof(PSTRIP));
        move(ind,p^,sizeof(ind));
        send_mail(@Self,adrBOARD^, cmXXX, one, @mail_buff, mail_size) { PPObject }
      end;


  function O_STRIP.zarad(ind: int; is: TSpecGroups): string;
     begin
       if get_poz(ap^[ind])<poz_PROPOSED then zarad:= ''
       else zarad:= skupina
     end;

  function O_STRIP.zarad_inde(ind: int; is: TSpecGroups; res: string): string;
     begin
       zarad_inde:= ''
     end;


  function O_STRIP.smer(ind: int): Ts_dir;
     begin
       smer:= dir_no
     end;


  function O_STRIP.NDB(ind: int): string;
     begin
       NDB:= ''
     end;

  function O_STRIP.ETO(ind: int): real;
     begin
       ETO:= 0.
     end;

  function O_STRIP.ETD(ind: int): real;
     begin
       ETD:= 0.
     end;

  function O_STRIP.ETA(ind: int): real;
     begin
       ETA:= 0.
     end;

  function O_STRIP.FL (ind: int): real;
     begin
       FL:= 0.
     end;


  { ------------------------------
     Nedoriesene zobrazenie LAM
    ------------------------------ }

  procedure _LAM(x0,y0,x1,y1: int; p: pointer); far;
      const _ACK: array[false..true] of char = ('-','*' {,'N'});
            _C  : array[false..true] of byte = (lightred,lightcyan);
      var   i : int;
            b : bool;
      begin
        bgigraph.button(x0,y0,x1,y1, clBUTTON_COLOR-1,btSmall,btON);
        for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
            if typ in [FDP,FDP0] then
               begin
                 SetColor(clGRe);
                 OutTextXY(x0+dx_ed+10,y0+dy_ed+10+i*15,strpas(name));
                 if p<>nil then
                    begin
                      b:= Pplan_rec(p)^[i] in [is_rec];
                      if b then icYes(x1-17, y0+i*15+8)
                      else icNo(x1-21, y0+i*15+5)
                      {
                      SetColor(_C[b]);
                      OutTextXY(x1-20,y0+dy_ed+10+i*15,_ACK[b])
                      }
                    end
               end
      end;

  procedure O_STRIP.LAM(p: pointer);
      var   i,m,k: int;
            pr: Pplan_rec;
      begin
        pr:= get_rec(p);
        m:= 0; k:= 0;
        for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
            if typ in [FDP,FDP0] then
               begin
                 m:= Maximum(m,strlen(name));
                 inc(k)
               end;
        Info(cut_('LAM - '+get_id(p)),@_LAM,pr,m shl 3 + 30,k*15 + 15,nil,0)
      end;

{$ENDIF}
