{$IFDEF KRL}

{ Spracovanie kridel podanych/prjatych pre vlastne
  alebo ine letisko
}
  {function handle__KRL_pre_FPL_vlastneho_letiska (sc: PScroller; FPL: PDmFPL): bool; far;
     begin
       handle__KRL_pre_FPL_vlastneho_letiska:= false;
       formular_mFPL(FPL,letvis,FPL^.stat,false, msg_KRL_FPL, 0, nil, hlp_mFPL);
     end;
  }

  function handle_KRL (sc: PScroller; FPL: PDmFPL): bool; far;
     const max_items = 20;
     var   KRLmenu   : PWinMenu;
           KRLitems  : TPItems;
           items,i,nl : int;
           _Ev  : TEvent;
           x,y  : int;
           s    : string;
           bres : bool;
     begin
       handle_KRL:= false;
       sc_menu_xy(sc, x,y, 0,0);

       KRLmenu:= WinMenu(tit_KRL,nil,nil);
       items:= 0; nl:= 0;

       {$IFDEF PROCESS_FPLM}
        if DateToSec(year,month,day) >= DateToSec(FPL^.date.r,FPL^.date.m,FPL^.date.d) then
           begin
             KRLitems[items]:= Item (mnu_KRL_oprava, cmKRLchg, nil);
             inc(items);
                          { 2  -> napisal Bubo }
             if (pos(cnst_cnl,FPL^.stat)=0) then
                begin
                  KRLitems[items]:= Item (mnu_KRL_zrus_, cmKRLcnl, nil);
                  inc(items);
                end;

             bres:= _kridlo_pre_vlastne_letisko (FPL, nil);
             if bres then
                begin
                  KRLitems[items]:= Item (mnu_KRL_sprac_,cmKRLsprac,nil);
                  inc(items)
                end;

             if _is_SEND_KRL(FPL,nil) then
                begin
                  KRLitems[items]:= Item (mnu_KRL_odos_+FPL^.start.kod+' ', cmKRLsend,nil);
                  inc(items)
                end;

            {$IFDEF AIRBASE}
             if not bres then
                begin
                  KRLitems[items]:= Item(delchar(mnu_KRL_odos_,[cnst_HotKey])+'~S~RLP ', cmKRLsend_macc,nil);
                  inc(items)
                end;
            {$ENDIF}
           end;
       {$ENDIF}

       {$IFDEF MAPY}
        add_newline(nl,items,KRLitems);
        KRLitems[items]:= Item(tit_DRAW, cmFPLMdraw, nil);
        inc(items);
       {$ENDIF}

       {$IFDEF PRN}
        if nl=0 then add_newline(nl,items,KRLitems);
        KRLitems[items]:= Item(tit_PRINT, cmFPLMprint,nil);
        inc(items);
       {$ENDIF}

       for i:= 0 to items-1 do KRLmenu^.AddItem(KRLitems[i]);

       KRLmenu^.MoveRel(x+10-KRLmenu^.x0,y+30-KRLmenu^.y0);  {KRLmenu^.Centre;}
       KRLmenu^.Run(_Ev);
       if ((_Ev.What and evMessage) <> 0) then _handle_event_FPL_o_sc (_Ev,sc,FPL,nil,sc);
       Dispose(KRLmenu, Done)
     end;


{ Odoslanie FPL ako kridla na zvolene letisko na trati
}
  function handle__podanie_FPL_ako_KRL(sc: PScroller; FPL: PDmFPL): bool;
     var   M         : PWinMenu;
           _Ev       : TEvent;
           x,y,i,j   : int;
           items     : int;
           Mi        : array[0..maxNODEs] of PItem;
           APi       : array[0..maxNODEs] of string[KOD_AP];
           APr       : string[KOD_AP];

     function _add_AP(APr: string): bool;
        var   res: bool;
              k  : int;
        begin
          res:= (eq_airbase(APr,FPL^.start.kod) or _ma_MZP_na_LSRLP(FPL,APr) or (eq_airbase(APr,FPL^.prist.kod)));
          if res then
             begin
               k:= 0;
               while (k<items) and (APi[k]<>APr) do inc(k);
               res:= k>=items
             end;
          _add_AP:= res
        end;

     begin
       handle__podanie_FPL_ako_KRL:= false;

       items:= 0;
       for i:= 0 to NODEpoc-1 do with NODEs^[i] do
           if (strpos(desc.inf,nd_AP)<>nil) and (strpos(desc.inf,inf_KRL)<>nil) then
              begin
                APr:= strpas(desc.name);
                if _add_AP(APr) then
                   begin
                     APi[items]:= APr;
                     Mi [items]:= Item('~'+APi[items][1]+'~'+copy(APi[items],2,length(APi[items])-1),cmOTHER+items,nil);
                     inc(items)
                   end
              end;
       if _add_AP(APr) then
          begin
            APi[items]:= APr;
            Mi [items]:= Item('~'+APi[items][1]+'~'+copy(APi[items],2,length(APi[items])-1),cmOTHER+items,nil);
            inc(items)
          end;
       if items=0 then Exit;

       M:= WinMenu(tit_KRLpre, nil,nil);
       for i:= 0 to items-1 do M^.AddItem(Mi[i]);
       sc_menu_xy(sc, x,y, 0,0);
       M^.MoveRel(x+10-M^.x0,y+30-M^.y0);  {KRLmenu^.Centre;}
       M^.Run(_Ev);
       Dispose(M, Done);

       i:= 0;
       while (i<items) do
         begin
           if isCommand(_Ev,cmOTHER+i) then break;
           inc(i)
         end;
       if not (i<items) then Exit;

       NETsend_data(adr_airbase(NETadr_wan(APi[i])),
                spr_FPLM, FPL, @code_FPLM,@codekey_FPLM,@FPL^.rec,
                true,'',nil{@send2node_mFPL},
                true,false, net_flag_SEND
               );
       FPL^.stat:= cnst_sended;
       save_mFPL(FPL)
     end;

{$ENDIF}