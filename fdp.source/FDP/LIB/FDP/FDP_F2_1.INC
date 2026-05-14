 function alloc_AIP_mnu (short: bool): PWinMenu; near;
    var   sbmnu: PWinMenu;
          smnu : TPItems;
          i,items,nl,ihk : int;
    begin
      m_set_shape(HODINY);

      sbmnu:= WinMenu_S(tit_AIP_,hlpmnuAIP,20, nil);
      items:= 0; nl:= 0; ihk:= 0;

      smnu[items]:= Item (' '+hk(ihk)+tit_typy_icao, cmPREHLAD_TYPY_ICAO, nil);
      inc(items);
      smnu[items]:= Item (' '+hk(ihk)+tit_typy_zzzz, cmPREHLAD_TYPY_ZZZZ, nil);
      inc(items);
      {$IFDEF TSGA}
       smnu[items]:= Item (' '+hk(ihk)+tit_typy_tsga,cmPREHLAD_TYPY_TSGA, nil);
       inc(items);
      {$ENDIF}
      {$IFNDEF FPLM_DISABLED}
       smnu[items]:= Item (' '+hk(ihk)+tit_typy_mil,  cmPREHLAD_TYPY_MIL,  nil);
       inc(items);
      {$ENDIF}
      smnu[items]:= Item (' '+hk(ihk)+tit_typ_data,  cmPREHLAD_TYP_DATA,  nil);
      inc(items);

      add_newline(nl,items, smnu);
      smnu[items]:= Item (' '+hk(ihk)+tit_uz,     cmPREHLAD_POUZ,  nil);
      inc(items);
      {$IFNDEF FPLM_DISABLED}
       smnu[items]:= Item (' '+hk(ihk)+tit_uz_mil, cmPREHLAD_POUZM, nil);
       inc(items);
      {$ENDIF}

      {$IFNDEF ATCA}
       smnu[items]:= Item (' '+hk(ihk)+tit_ulohy_mil, cmPREHLAD_ULOHYM, nil);
       inc(items);
      {$ENDIF}

      if not short then
         begin
           add_newline_(1,nl,items, smnu);
           smnu[items]:= Item (' '+hk(ihk)+tit_rte_ats,  cmPREHLAD_RTE, nil);
           inc(items);
           {$IFDEF PROCESS_FPL4}
            smnu[items]:= Item (' '+hk(ihk)+tit_rte_atss, cmPREHLAD_RTES, nil);
            inc(items);
           {$ENDIF}
           smnu[items]:= Item (' '+hk(ihk)+tit_ndb,      cmPREHLAD_NDB, nil);
           inc(items);
           smnu[items]:= Item (' '+hk(ihk)+tit_aip_in,   cmPREHLAD_DAIPORTS, nil);
           inc(items);
           {$IFDEF PROCESS_FPL4}
            smnu[items]:= Item (' '+hk(ihk)+tit_aip_out,  cmPREHLAD_FAIPORTS, nil);
            inc(items);
           {$ENDIF}
           {$IFNDEF FPLM_DISABLED}
            add_newline_(0,nl,items, smnu);
            smnu[items]:= Item (' '+hk(ihk)+tit_rte_mil, cmPREHLAD_RTEM, nil);
            inc(items);
            smnu[items]:= Item (' '+hk(ihk)+tit_ob,      cmPREHLAD_OB, nil);
            inc(items);
            smnu[items]:= Item (' '+hk(ihk)+tit_abc,     cmPREHLAD_ABC, nil);
            inc(items);
            smnu[items]:= Item (' '+hk(ihk)+tit_abc_,    cmPREHLAD_ABC_, nil);
            inc(items);
           {$ENDIF}
         end;

      {$IFNDEF ATCA}
       add_newline_(1,nl,items, smnu);
       smnu[items]:= Item (' '+hk(ihk)+tit_tsa, cmPREHLAD_TSA, nil);
       inc(items);
       smnu[items]:= Item (' '+hk(ihk)+tit_r,   cmPREHLAD_R,   nil);
       inc(items);
      {$ENDIF}

      add_newline_(1,nl,items, smnu);
      smnu[items]:= Item (' '+hk(ihk)+tit_fl,   cmPREHLAD_FL, nil);
      inc(items);


      add_newline(nl,items, smnu);
      smnu[items]:= Item (' '+hk(ihk)+tit_slnko_rok, cmPREHLAD_SLNKO, nil);
      inc(items);
      smnu[items]:= Item (' '+hk(ihk)+tit_slnko_den, cmSLNKO_NA_DEN,  nil);
      inc(items);


      for i:= 0 to items-1 do sbmnu^.AddItem(smnu[i]);
      alloc_AIP_mnu:= sbmnu;
      m_restore_shape
    end;


 function AIP_menu: PWinMenu;
    begin
      AIP_menu:= alloc_AIP_mnu(false)
    end;


 function _handle_AIP_list(var _Event: TEvent; O: PObject): bool;
    var   s : string;
    begin
      _handle_AIP_list:= false;

      if ((_Event.What and evMessage) <> 0) then
         case _Event.Command of

           cmPREHLAD_TYPY_ICAO: _infop(pathLST+_fn_9bICAO_,        tit_typy_icao, 0,0,true,false,nil);
           cmPREHLAD_TYPY_ZZZZ: _infop(pathLST+_fn_9bZZZZ+lstExt,  tit_typy_zzzz, 0,0,true,false,nil);
           cmPREHLAD_TYPY_TSGA: _infop(pathLST+_fn_9bTSGA+lstExt,  tit_typy_tsga, 0,0,true,false,nil);
           cmPREHLAD_TYPY_MIL : _infop(pathLST+_fn_9bMIL+lstExt,   tit_typy_mil,  0,0,true,false,nil);
           cmPREHLAD_TYP_DATA : _info_TYP('',0,0);

           cmPREHLAD_POUZ     : if get_ind(s,tit_uz) then _infop(pathLST+s[1]+extFLO,tit_uz, 0,0,true,false,nil);
           cmPREHLAD_POUZM    : _infop(pathLST+strpas(fnPrevM.fn),    tit_uz_mil, 0,0,true,false,nil);
           cmPREHLAD_ULOHYM   : _infop(pathLST+strpas(fnUlohyM.fn),   tit_ulohy_mil, 0,0,true,false,nil);

           cmPREHLAD_RTE      : _infop(pathLST+strpas(fnRTE.fn),      tit_rte_ats,  0,0,true,false,nil);
           cmPREHLAD_RTES     : _infop(pathLST+_fnRTE_fir+firExt,     tit_rte_atss,  0,0,true,false,nil);
           cmPREHLAD_RTEM     : _infop(pathLST+strpas(fnRTE_M.fn),    tit_rte_mil, 0,0,true,false,nil);

           cmPREHLAD_NDB      : _infop(pathLST+strpas(fnNDB.fn),      tit_ndb, 0,0,true,false,nil);
           cmPREHLAD_OB       : _infop(pathLST+strpas(fnOB.fn),       tit_ob,  0,0,true,false,nil);

           cmPREHLAD_ABC      : if get_ind(s,tit_abc) then _infop(pathLST+s[1]+abcExt,tit_abc, 0,0,true,false,nil);
           cmPREHLAD_ABC_     : if get_ind(s,tit_abc_) then _infop(pathLST+'_'+s[1]+abcExt,tit_abc_, 0,0,true,false,nil);

           cmPREHLAD_DAIPORTS : _infop(pathLST+strpas(_fnCLet+firExt{'.'+FIR}), tit_aip_in,  0,0,true,false,nil);
           cmPREHLAD_FAIPORTS : _infop(pathLST+strpas(fn_13a.fn),       tit_aip_out, 0,0,true,false,nil);

           cmPREHLAD_TSA      : _infop(pathLST+strpas(fnTSA.fn), tit_tsa, 0,0,true,false,nil);
           cmPREHLAD_R        : _infop(pathLST+strpas(fnR.fn),   tit_r,   0,0,true,false,nil);

           cmPREHLAD_FL       : _infop(pathLST+strpas(fnAlt.fn), tit_fl, 0,0,true,false,nil);

           cmPREHLAD_SLNKO    : _infop(pathLST+fnSLNKO, tit_slnko_rok, 0,0,true,false,nil);
           cmSLNKO_NA_DEN     : _info_SLNKO;

           else Exit
         end
      else Exit;

     _handle_AIP_list:= true;
     ClearEvent(_Event,O)
   end;


 procedure _list_OPL(x,y: int);
     var   M   : PWinMenu;
           _Ev : TEvent;
     begin
       M:= alloc_AIP_mnu (false);
       M^.MoveRel(x-M^.x0,y-M^.y0);
       M^.Run(_Ev);
       _handle_AIP_list(_Ev,nil);
       Dispose(M, Done)
     end;


 procedure _list_AIP(x,y: int);
     var   M   : PWinMenu;
           _Ev : TEvent;
     begin
       M:= alloc_AIP_mnu(true);
       M^.MoveRel(x-M^.x0,y-M^.y0);
       M^.Run(_Ev);
       _handle_AIP_list(_Ev,nil);
       Dispose(M, Done)
     end;
