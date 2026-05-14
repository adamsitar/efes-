constructor O_FPL.Init(_items,_data_size : word;

                       _new_item,
                       _format_item,
                       _disp_item : pointer;

                       _eq,
                       _id,
                       _ssr,
                       _chg,
                       _poz,
                       _est : pointer;

                       _distribute : pointer;  { TNET_distribute_rdp_pkt  }
                       _send       : pointer;  { TNET_send_pkt }
                       _en_net       : bool;

                       _item_list    : pointer;
                       _item_dx,_item_dy : int;
                       _get_item_dx,_get_item_dy : pointer;
                       _p_viewer : PScrollInd;

                       {$IFDEF MAPY}
                        _p_kresli  : pointer;
                        _draw_trgt : pointer;    { TProc_piib -> vykreslenie planu }
                        _ciele_en  : pointer;
                        _cl_ciel,
                        _cl_trat   : byte;
                       {$ENDIF}

                       {$IFDEF EDD}
                        _accepted : bool;
                        _adrBOARD : PPObject;
                        _cmADD,_cmCHG,_cmDEL,_cmCLR: word;

                        _strip   : pointer;
                        _skupina : string;
                       {$ENDIF}

                       var _p_PRN  : bool;
                       _p_print    : pointer;

                       _save,
                       _zobraz,
                       _formular,
                       _p_comp,
                       _p_handler  : pointer;

                       _p_nameDB, _p_decodeDB : pointer;
                       _riadkovDB : byte;
                       _p_codekey : pointer;

                       _limit_add, _limit_cnl, _limit_del : pint;
                       _nacitanie : bool;

                       _hlpXXX    : Pchar
                      );

      begin
        p_plan_handler:= _p_handler;
        _p_handler:= @_strip_handler;

        inherited Init(_items,_data_size,
                       _new_item,_format_item,_disp_item,

                       _eq,_id,_chg,_poz,_est,

                       _distribute,_send, _en_net,

                       _item_list,
                       _item_dx,_item_dy,
                       _get_item_dx,_get_item_dy,
                       _p_viewer,

                       {$IFDEF MAPY} _p_kresli, {$ENDIF}

                       {$IFDEF EDD}
                         _adrBOARD, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                         _skupina,
                         _strip,
                         @_edd_board_strip_handler,
                       {$ENDIF}

                       _p_PRN,_p_print,

                       _save,_zobraz,_formular,_p_comp,_p_handler,

                       _p_nameDB,_p_decodeDB,_riadkovDB,_p_codekey,

                       _limit_add, _limit_cnl, _limit_del,
                       _nacitanie,

                       _hlpXXX
                      );

        add_pos:= pozFPL;
        {msg_zrus:= spr_EST_CNL;}

        {$IFDEF EDD}
          accepted:= _accepted;
        {$ENDIF}

        {$IFDEF SECTORS}
          semaphorS:= false; updateS:= 0;
          dayS:= 0; monthS:= 0; yearS:= 0; hourS:= 25; minS:= 60; secS:= 60;
        {$ENDIF}

        {$IFDEF MAPY}
          is_map:= false;
          draw_trgt:= _draw_trgt; ciele_en:= _ciele_en;
          cl_ciel:= _cl_ciel; cl_trat:= _cl_trat;
        {$ENDIF}

        p_ssr:= _ssr; p_ssr0:= nil
      end;


function O_FPL.Eq(ind: int; p: pointer): bool;
   var   acpt: TTRG_stat; rdp: word; przn: bool;
         b : bool;
   begin
    {$IFDEF MAPY}
    { ma let vykreslenu trat a prisla zmena ? }
      b:= get_mapa(ap^[ind])<>nil;
      if b then del_mapa(ap^[ind]);
    {$ENDIF}

    {$IFDEF RDP_ACCEPT}
    { bol let acceptovany a prisla zmena ? }
      get_accept (ap^[ind], acpt,rdp);
    {$ENDIF}

     Eq:= inherited Eq(ind, p);

    {$IFDEF RDP_ACCEPT}
      set_accept (ap^[ind], acpt,rdp);
    {$ENDIF}

    {$IFDEF MAPY}
      if b then add_mapa(ap^[ind])
    {$ENDIF}
   end;


procedure O_FPL.format_data_variables(p: pointer);
    begin
     {if (format_item<>nil) then TProc_p(format_item)(p); -> setrime cas: vid Add }
     {$IFDEF MAPY}
       init_sur(p,true);
     {$ENDIF}
     {$IFDEF SECTORS}
      { najde prvy a vystupny bod sektora
      }
     {$ENDIF}
    end;


function  O_FPL.get_typ (p: pointer): string;
   begin
     if p_typ<>nil then get_typ:= TSFunc_p(p_typ)(p)
     else get_typ:= ''
   end;
