constructor TcFPLform.Init(var _x,_y, _mode: int; _title : string;

                           FPLi  : PDcFPL;
                           _src  : fdp_src;
                           _novy : bool;

                           _tit  : string;
                           _pos  : int;
                           _ssr,_viewer,_copy_data : bool
                          );
    begin
      fillchar(FPL,sizeof(DcFPL),0);
      fillchar(FPLp,sizeof(DcFPL),0);
      if (FPLi<>nil) then
         begin
           copy_cFPL_(FPLi, @FPL, _novy);
           FPLp:= FPL;
           {inc(FPL.cor_)}
         end
      {$IFDEF PVO}
       else FPL.rec_cas.h:= 25
      {$ENDIF};
      {format_cFPL(@FPL);}

      inherited Init(_x,_y, _mode, _title,
                @Form_cFPL, SIZE_frm_cFPL,
                0,1, 0,0, 0,0,

                @cFPL_init,@cFPL_image,@cFPL_check, hlp_cFPL,

                @FPL, FPLi, @FPL.rec, _src, FPL.stt,
                _novy, sizeof(DcFPL),nil,nil,nil,nil,
                nil, nil, @zarad_FPLc, @disp_cFPL,
                true,false{FPLi=nil}, false
                {$IFDEF ODOSLI_ULOZ}, false {$ENDIF}
                {$IFDEF SKRY_OKNA}, true {$ENDIF}
                {$IFDEF STATISTIKA_OPL},
                  {$IFDEF MACC} p_info_STA_FPLC {$ELSE} nil {$ENDIF}
                {$ENDIF}
               );

      viewer:= _viewer;
      copy_data:= _copy_data;
      upcas:= true;
      check_ssr:= _ssr;

      if (not novy) then
         begin
           itemd^[i_7_FDR].legal:= @setNil;
           itemd^[i_13a_FDR].legal:= @setNil;
           {itemd^[i_13b_FDR].legal:= @setNil;}
           if _pos>i_7_FDR then first_pos:= _pos
           else first_pos:= i_15c_FDR + (FPLi^.na_bod)*3+1
         end
      else fillchar(FPL.date,sizeof(FPL.date),0);

      if viewer then
         begin
           btOK^.new_title(titOK,false);
           btOK^.cmXXXX:= cmClose
         end;
    end;


destructor TcFPLform.Done;
     begin
       if corr_res and copy_data and (adr_data<>nil) then
          begin
            disp_cFPL (PDcFPL(adr_data));
            new_cFPL (@FPL,PDcFPL(adr_data));
          end;
       inherited Done;
     end;


procedure TcFPLform.init_buttons(x,y: int);
    var   bt1: PButton;
          xt,yt, xi,c : int;
          s: string;
          _kbHot: char;
    begin
      inherited init_buttons(x,y);

      btSSR:= nil;
      btSSU:= nil;
      btRTE:= nil;
      btDel:= nil;
      btIns:= nil;

      {$IFDEF SSR_MANAGEMENT}
       Win^.get_btXY(1,0, xt,yt);
       btSSR:= New(PDialogButton,Init(Win, xt,yt, kbAltS, cm_SSR, '~S~SR   ', icKey,icText));
       btSSR^.visible:= false;
       btSSR^.bk0:= clBUTTON_COLOR;
       Win^.get_btXY(1,1, xt,yt);
       btSSU:= New(PDialogButton,Init(Win, xt,yt, kbAltU, cmUsed, '~U~sed  ', icKey,icText));
       btSSU^.visible:= false;
       btSSU^.bk0:= clBUTTON_COLOR;
      {$ENDIF}

      Win^.get_btXY(1,0, xt,yt);
      btNDB:= New(PDialogButton,Init(Win, xt,yt,
                  GetAltCode(get_HotKey(_kbHot,titNDB)), cmList{cm_NDB},titNDB,
                  icKey,icText));
      btNDB^.visible:= false;
      btNDB^.bk0:= clBUTTON_COLOR;

      Win^.get_btXY(1,1, xt,yt);
      xi:= xt;

      {$IFDEF FPL4}
       if Exists(pathDATA+_fnRTE_fir+FIRext)=0 then
          begin
            s:= tit_regRTE;
            btRTE := New(PButton,Init(Win, xt,yt, length(s) shl 3,dbtHEIGHT, hk_regRTE, cm_RTE, s, 1,icKey,icText));
            btRTE^.visible:= false;
            btRTE^.bk0:= clBUTTON_COLOR;
            xt:= btRTE^.x1+5
          end;
      {$ENDIF}

      s:= tit_delNDB;
      btDel := New(PButton,Init(Win, xt,yt, length(s) shl 3,dbtHEIGHT, hk_delNDB, cmItemDelete, s, 1,icKey,icText));
      btDel^.visible:= false;
      btDel^.bk0:= clBUTTON_COLOR;
      xt:= btDel^.x1+5;

      s:= tit_insNDB;
      btIns := New(PButton,Init(Win, xt,yt, length(s) shl 3,dbtHEIGHT, hk_insNDB, cmItemInsert, s, 1,icKey,icText));
      btIns^.visible:= false;
      btIns^.bk0:= clBUTTON_COLOR;
    end;


procedure TcFPLform.HandleEvent(var _Event: TEvent);
    var   i,j,k,r : int;
          s,res : string;
    begin
      inherited HandleEvent(_Event);
      if (_Event.What and evMessage) <> 0 then
         case _Event.Command of

           {$IFDEF SSR_MANAGEMENT}
            cm_SSR      : form_init_ssr (@Self,i_7b_FDR);
            cmUsed      : list_of_used_ssr;
           {$ENDIF}

           cm_RTE       : vloz_trat;

           cmItemInsert : begin
                            k:= (ind-i_15c_FDR) div 3;
                            for i:= max_bod_FPLC-2 downto k do
                              begin
                                r:= 3*i+i_15c_FDR;
                                for j:= 0 to 2 do strcopy(itemd^[r+j+3].item,itemd^[r+j].item)
                              end;
                            for j:= 0 to 2 do clear_item_i(3*k+i_15c_FDR+j);
                            for j:= 3*k+i_15c_FDR to items-1 do writeitem(j);
                            Write
                          end;

           cmItemDelete : begin
                            k:= (ind-i_15c_FDR) div 3;
                            for i:= k to max_bod_FPLC-2 do
                              begin
                                r:= 3*i+i_15c_FDR;
                                for j:= 0 to 2 do strcopy(itemd^[r+j].item,itemd^[r+j+3].item)
                              end;
                            for j:= 0 to 2 do clear_item_i(3*(max_bod_FPLC-1)+i_15c_FDR+j);
                            for j:= 3*k+i_15c_FDR to items-1 do writeitem(j);
                            Write
                          end;
           else Exit
         end
      else Exit;
      ClearEvent(_Event)
    end;


procedure TcFPLform.draw_buttons;
    begin
      if viewer then Exit;

      if (ind<>i_7b_FDR) and (btSSR<>nil) then
         begin
           btSSR^.visibility(false);
           btSSU^.visibility(false);
         end;
      if (btNDB<>nil) and ((ind < i_15c_FDR) or ((ind - i_15c_FDR) mod 3 <> 0)) then btNDB^.visibility(false);
      if (not (ind in[i_15c_FDR..SIZE_frm_cFPL-1])) then
         begin
           if (btRTE<>nil) then btRTE^.visibility(false);
           if (btIns<>nil) then btIns^.visibility(false);
           if (btDel<>nil) then btDel^.visibility(false)
         end;
      inherited draw_buttons;
      if (ind=i_7b_FDR) and (btSSR<>nil) then
         begin
           btSSR^.visibility(true);
           btSSU^.visibility(true);
         end;
      if (btNDB<>nil) and ((ind >= i_15c_FDR) and ((ind-i_15c_FDR) mod 3 = 0)) then btNDB^.visibility(true);
      if ((ind in[i_15c_FDR..SIZE_frm_cFPL-1])) then
         begin
           if (btRTE<>nil) then btRTE^.visibility(true);
           if (btIns<>nil) then btIns^.visibility(true);
           if (btDel<>nil) then btDel^.visibility(true)
         end
    end;

procedure TcFPLform.vlozeny_text(kde: int; s: string);
    var   _9: string;
          var err9b,err9c: bool;
    begin
      if kde<>i_9_FDR then Exit;
      _9:= _it(i_9_FDR); _code_9_by8643_ (_9,_EFIL_9,err9b,err9c);
      _in(i_9_FDR,_9);
      last_char;
      Write
    end;

procedure TcFPLform.vloz_trat;
    {$IFDEF FPL4}
    var   i,j,p : int;
          FPLi  : DcFPL;
          rte   : POBxys;
          bodov : int;
          _1,_n,trat,res,s : string;
          pom   : byte;
    {$ENDIF}
    begin
    {$IFDEF FPL4}
     { a) nacitanie ostatnych parametrov
     }
      fillchar(FPLi,sizeof(FPLi),0);
      cFPL_check_(@self, @FPLi,false,false);

      _1:= _it(cFPLbod(ind));
      if GetTimeStr(FPLi.eet.h,FPLi.eet.m,pom,_it_(cFPLbod(ind)+1)) then
      else fillchar(FPLi.eet,sizeof(FPLi.eet),0);
      if FPLi.bodov>1 then _n:= FPLi.trat[FPLi.bodov-1].kod
      else _n:= '';

     { b) nacitanie trate
     }
      trat:= prirad_trat_FPL4 (x0+itemd^[ind].dx+itemv^[ind].i*dx_ch,y0+itemd^[ind].dy+10,
                               _1,_n, @FPLi, rte,bodov,
                               res
                              );
      if res<>'' then ErrorS(i_15c_FDR,res)
      else if (bodov>0) then
              begin
                p:= minimum(bodov,max_bod_FPLC);
                FPLi.bodov:= 0; fillchar(FPLi.trat,sizeof(FPLi.trat),0);
                for i:= 0 to p-1 do
                  begin
                    FPLi.trat[i].kod:= rte^[i].kod;
                    FPLi.trat[i].h  := rte^[i].h;
                    FPLi.trat[i].m  := rte^[i].m;
                    inc(FPLi.bodov)
                  end;
                pristatie_cFPL(@FPLi);    { vola format_cFPL(@FPLi) }
                cFPL_init_route(@self,@FPLi);
                TBox.draw
              end;

      dealloc_FDRrte(rte,bodov);
     {$ENDIF}
    end;
