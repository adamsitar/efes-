{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TmFPLform - vojensky FPL                                 Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

function TmFPLform.is_upcas(_ind: int): bool;
   var   _upcas: bool;
   begin
     _upcas:= true;
     {$IFDEF SK}
(*     _upcas:=  not ((_ind in [i_7Ma {$IFNDEF L4444M},i_7Ma2{$ENDIF}]) {or (_ind >= i_15M))};*)
     {$ENDIF}
     is_upcas:= _upcas
   end;


procedure TmFPLform.init_buttons_trat(x,y: int);
    var   bt1 : PDialogButton;
          xt,yt, c : int;
          _kbHot : char;
    begin
      c:= 1;
      if fnRTE_M.fn<>nil then
         begin
           Win^.get_btXY(1,c, xt,yt);
           btRTE := New(PDialogButton,Init(Win, xt,yt,
                        GetAltCode(get_HotKey(_kbHot,titRTEM)),cm_RTE,titRTEM,
                        icKey,icText));
           btRTE^.visible:= false;
           btRTE^.bk0:= clBUTTON_COLOR;
           inc(c);
         end
      else btRTE:= nil;

      Win^.get_btXY(1,c, xt,yt);
      btOB:= New(PDialogButton,Init(Win, xt,yt,
                 GetAltCode(get_HotKey(_kbHot,titBOD)),cm_OB,titBOD,
                 icKey,icText)
                );
      btOB^.visible:= false;
      btOB^.bk0:= clBUTTON_COLOR;
      inc(c);

      Win^.get_btXY(1,c, xt,yt);
      btNDB:= New(PDialogButton,Init(Win, xt,yt,
                  GetAltCode(get_HotKey(_kbHot,titNDB)), cm_NDB,titNDB,
                  icKey,icText));
      btNDB^.visible:= false;
      btNDB^.bk0:= clBUTTON_COLOR;
      inc(c);

      btABC:= nil;
      {$IFDEF SK}
       Win^.get_btXY(1,c, xt,yt);
       btABC := New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titABC)), cm_ABC, titABC, icKey,icText));
       btABC^.visible:= false;
       btABC^.bk0:= clBUTTON_COLOR;
       inc(c);
      {$ENDIF}

      Win^.get_btXY(1,c, xt,yt);
      btACT := New(PDialogButton,Init(Win, xt,yt,
                   GetAltCode(get_HotKey(_kbHot,titACT)),cm_ACTIVITY,titACT,
                   icKey,icText));
      btACT^.visible:= false;
      btACT^.bk0:= clBUTTON_COLOR;
      inc(c);

      {$IFDEF MAPY}
       Win^.get_btXY(0,bt_y, xt,yt);
       bt1:= New(PDialogButton,Init(Win, xt,yt+off_y,
                 GetAltCode(get_HotKey(_kbHot,titTRAT)),
                 cm_KRESLI_TRAT,titTRAT,icKey,icText)
                );
       inc(bt_y);
      {$ENDIF}

      {$IFDEF PRS}
      {$IFDEF FPLM_REGULARITA}
       if (not FPLM_REGULARITA_FUA_PLAN) then
          begin
            Win^.get_btXY(0,bt_y, xt,yt);
            bt1:= New(PDialogButton,Init(Win, xt,yt+off_y,
                      GetAltCode(get_HotKey(_kbHot,titREG)),
                      cm_REGULAR_TRATE,titREG,icKey,icText)
                     );
            inc(bt_y);
          end;
      {$ENDIF}
      {$ENDIF}

      inc(off_y,5);
      Win^.get_btXY(0,bt_y, xt,yt);
      bt1:= New(PDialogButton,Init(Win,xt,yt+off_y,
                GetAltCode(get_HotKey(_kbHot,mnu_AIP)), cm_xDATA,
                mnu_AIP, icKey,icText)
               );
      inc(bt_y);
     end;


procedure TmFPLform.init_buttons(x,y: int);
    begin
      inherited init_buttons(x,y);
      init_buttons_trat(x,y);
    end;


constructor TmFPLform.Init(var _x,_y,  _mode: int;
                           _title : string;

                           _init_form  : pointer; { inicializacia dat   }
                           _check_func : pointer; { kontrola regularity }
                           _pos        : byte;

                           _adr_var,              { adresa premennej, kam nacitat data    }
                           _adr_data   : pointer; { data pre kontrolu, ci dany plan este neexistuje }

                           _rec        : pointer;
                           _src        : fdp_src;
                           _stat       : string;

                           _novy       : bool;

                           _date_proc,            { zadanie datumu TBFunc_p3(p,c,d: pointer) }
                           _save_rpl_proc,        { ulozenie rpl Tproc_p(p: pointer)      }
                           _zarad_proc : pointer;

                           _hlpXXX: Pchar         { ukazovatel na help  }

                           {$IFDEF ODOSLI_ULOZ}; _uloz: bool {$ENDIF}
                          );
      begin
        if _check_func=nil then _check_func:= @mFPL_check;

        inherited Init(_x,_y,_mode, _title, @form_mFPL,SIZE_frm_mFPL,
                       0,1, 0,0, 0,0,
                       _init_form, @mFPL_image,_check_func, _hlpXXX,
                       _adr_var,_adr_data,
                       _rec,_src,_stat,
                       _novy, sizeof(DcFPL),@codekey_FPLM,
                       @read_mFPL,@existuje_mFPL,@zmeneny_mFPL,
                       _date_proc,_save_rpl_proc,_zarad_proc,@disp_mFPL,
                       true,false,true
                       {$IFDEF ODOSLI_ULOZ}, _uloz {$ENDIF}
                       {$IFDEF SKRY_OKNA}, true {$ENDIF}
                       {$IFDEF STATISTIKA_OPL}, p_info_STA_FPLM {$ENDIF}
                       );

        ins:= true;
        upcas:= true;
        pole_en:= true;
        {pole_cr:= true;}
        copy_back:= true;
        first_pos:= _pos;
        nbg:= clBUTTON_COLOR+1;
        kresli:= {$IFDEF MAPY} @mFPL_kresli {$ELSE} nil {$ENDIF};

        if save_rpl_proc<>nil then
           RPL_scroll_init (tit_PLANvzor,@get_fn_mFPL_RPL_let,
                            sizeof(DmFPL),@new_mFPL,@format_mFPL,
                            db_mFPL_RIADKOV,@decodeDB_FPLM,
                            dxi_mFPL, dyi_mFPL, @plan_mFPL
                           );
      end;


procedure TmFPLform.draw_buttons;
    begin
      if (not (ind in[i_15M..i_15M+max_mFPL_15_r_hi-1])) and (btOB<>nil) and (btOB^.visible) then
         begin
           btOB^.hide;
           if (btNDB<>nil) then btNDB^.hide;
           if (btABC<>nil) then btABC^.hide;
           if (btACT<>nil) then btACT^.hide;
           if (btRTE<>nil) then btRTE^.hide;
         end;

      inherited draw_buttons;

      if (ind in[i_15M..i_15M+max_mFPL_15_r_hi-1]) and (btOB<>nil) and (not (btOB^.visible)) then
         begin
           btOB^.show;
           if (btNDB<>nil) then btNDB^.show;
           if (btABC<>nil) then btABC^.show;
           if (btACT<>nil) then btACT^.show;
           if (btRTE<>nil) then btRTE^.show
         end
    end;


function kod_trate(form: PmFPLform; ind: int; s: string): string; far;
   var   M : PWinMenu;
         E : TEvent;
         x,y, i,p : int;
         t,u, b1,bn, r1,r2 : string;
   begin
     kod_trate:= '';
     if (form=nil) or (cut_(s)='') then Exit;
     form^.IndXY(ind, x,y, '');
     s:= getstr(s,pos_rtem,[odd_rtem_item]);

     if s[1]<>odd_rtem_subitem then
        begin
          M:= WinMenu(mnufrm_VLOZIT_TRAT,nil,
                      Item(' ~a~) '+mnufrm_TRAT+' ',cmVLOZ_TRAT,
                      Item(' ~b~) '+mnufrm_BODY+' ',cmVLOZ_BOD,
                      nil ) )
                     );
          M^.MoveRel(x-M^.x0,y-M^.y0);
          M^.Run(E);
          Dispose(M, Done);
          if ((E.What and evMessage)<>0) then
             case E.Command of
               cmVLOZ_TRAT : begin
                               kod_trate:= cut_(getstr(s,pos_rtem_kod_,[odd_rtem_subitem]));
                               Exit
                             end;
               cmVLOZ_BOD  :
               else Exit
             end
          else Exit
        end;

     if s[1]<>odd_rtem_subitem then s:= getstr(s,pos_rtem_bod_,[odd_rtem_subitem])
     else s:= copy(s,2,length(s)-1);
     kod_trate:= cut_(s);
     p:= getstritems(s,[odd_rtem_subitems]);
     if p<=1 then Exit;

     b1:= cut_(getstr(s,1,[odd_rtem_subitems]));
     bn:= cut_(getstr(s,p,[odd_rtem_subitems]));
     t:= s; u:= ''; for i:= p downto 1 do u:= u + cut_(getstr(s,i,[odd_rtem_subitems])) + odd_rtem_subitems;

     if b1<>bn then
       begin
         r1:= b1+'->'+bn;
         r2:= bn+'->'+b1;
       end
     else begin
            r1:= mnufrm_TRAT_SMER;
            r2:= mnufrm_TRAT_OPAK;
          end;

     M:= WinMenu(mnufrm_SMER_LETU,nil,
                 Item(' ~a~) '+r1+' ',cmEST_NEXT,
                 Item(' ~b~) '+r2+' ',cmEST_LAST,
                 nil ) )
                );
     M^.MoveRel(x-M^.x0,y-M^.y0);
     M^.Run(E);
     Dispose(M, Done);

     s:= '';
     if ((E.What and evMessage)<>0) then
        case E.Command of
          cmEST_NEXT : s:= t;
          cmEST_LAST : s:= u
        end;

     kod_trate:= s
   end;


procedure TmFPLform.HandleEvent(var _Event: TEvent);
    var   xt,yt : int;
          s : string;
          b : bool;
    begin
      inherited HandleEvent(_Event);
      if (_Event.What and evMessage) <> 0 then
         begin
           case _Event.Command of

            { Vlozenie udajov
            }
             cm_RTE  : RunList(@fnRTE_M,lst_vsetky_polozky,true,@vlastna_trat,nil,@kod_trate);
             cm_OB   : RunList(@fnOB,1,true,nil,nil,nil);
             cm_NDB  : RunList(@fnNDB,1,true,nil,nil,nil);
             cm_ABC  : begin
                         if formular_s(s,1, tit_abc,@fn_7xM,0,@setABC,@setNil, 0,nil,false,true,false,nil) then
                         if s<>'' then
                            begin
                              s:= s+abcExt;
                              if (fnABC.fn=nil) or (strpas(fnABC.fn)<>s) then
                                 begin
                                   strdispose(fnABC.fn);
                                   fillchar(fnABC,sizeof(fnABC),0);
                                   fnABC.fn:= StrPasNew(s)
                                 end;
                              RunList(@fnABC,lst_posledna,true,nil,nil,nil)
                            end
                       end;

             cm_ACTIVITY   : RunList(@fn_15M,1,true,nil,nil,nil);

            { Zobrazenie udajov
            }
             cm_KRESLI_TRAT   : if kresli<>nil then TProc_p(kresli)(@self);
             cm_REGULAR_TRATE : begin
                                  b:= FPLM_REGULARITA_FUA_ACT; FPLM_REGULARITA_FUA_ACT:= true;
                                  _mFPL_check(@Self,adr_var,false,true,true);
                                  FPLM_REGULARITA_FUA_ACT:= false;
                                end;

             cm_xDATA         : begin
                                  Win^.get_btXY(0,5, xt,yt);
                                  {$IFDEF MATCA} _list_OPL(xt-170,yt)
                                  {$ELSE}        _list_AIP(xt-170,yt)
                                  {$ENDIF}
                                end;
             else Exit
           end;
           ClearEvent(_Event)
         end
    end; { HandleEvent }


function TmFPLform.plan_uz_bol_podany (data: pointer): bool;
   var   FPL  : PDmFPL;
         ires : int;
         sres : string;
   begin
     plan_uz_bol_podany:= false;
     if not (novy and (data<>nil) and (p_is_data<>nil)) then Exit;

     FPL:= PDmFPL(data);
     if (not is_KRL(FPL)) and _identifikacia_letu_do_tsa(FPL) then
        begin
          InfoCakaj(msgMESS, msgWAITING+'. '+msgFINDING);
          FPL^.idn_:= _prirad_dalsie_cislo_letu_do_tsa (FPL);
          InfoCakaj_zatvor;
          if FPL^.idn_=' ' then
             begin
               plan_uz_bol_podany:= true;
               l4_err(a_FPLM,'',i_15Ma,err_FPLM_7a_letTSA_nemoze_dalsi, sres);
               ErrorS (i_7Mc,sres);
             end
        end
     else plan_uz_bol_podany:= inherited plan_uz_bol_podany (data)
   end;
