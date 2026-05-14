{ ======================

   FPL4

  תתתתתתתתתתתתתתתתתתתתתת
}

 procedure image_FPL4(x0,y0,x1,y1: int); far;
     begin
       BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR+1, btSmall, btOFF);
      {_linev(0+320, y0+37,y0+73,  clBUTTON_COLOR+1);}
       _lineh(x0+9,x0+320, y0+37,  clBUTTON_COLOR+1);
       _lineh(x0+9,x1-10,  y0+73,  clBUTTON_COLOR+1);
       _lineh(x0+9,x1-10,  y0+144, clBUTTON_COLOR+1);
     end;


 constructor TFPL4form.Init (var _x,_y, _mode: int; _tit : string;
                             _itemd : PForms; _items: byte; _o_f: byte;
                             _FPLi : PFPL4;
                             _src  : fdp_src;
                             _stat : string;
                             _novy : bool
                            );
       begin
         _novy:= (_novy) or (_FPLi=nil) {or (FPLi^.stat=cnst_stat_arr) or (pos(cnst_cnl,FPLi^.stat)<>0))};
         new_FPL4_(_FPLi,FPLp);
         new_FPL4_(FPLp,FPLn);
         if (_FPLi=nil) or _novy then
            begin
              fplsrc_clear(FPLn^._18);
              fillchar(FPLn^.date,sizeof(FPLn^.date),0)
            end;
         if _stat='' then if (_FPLi<>nil) then _stat:= _FPLi^.stat;
         if (_stat<>hd_ALR) and ((_stat='') or (_novy)) then _stat:= hd_FPL;

         rpl:= _novy;
         rpl4:= {$IFDEF RPL}_novy{$ELSE}false{$ENDIF};
         btSSR:= nil;

         inherited Init (_x,_y,_mode, _tit,
                         _itemd,_items,_o_f,
                         nil{@init_FPL4}, @image_FPL4, nil{@check_FPL4},

                         FPLn,FPLp, @FPLn^.rec,_src,_stat,

                         _novy, sizeof(DFPL4),@codekey_FPL4,@read_FPL4,
                         nil,nil,{@existuje_FPL4,@zmeneny_FPL4,}

                         nil{_date_pro}, nil{_save_rpl_proc},
                         @zarad_FPL4,
                         @disp_FPL4,

                         hlp_FPL4
                        );

         ins:= _FPLi=nil;

         f_7a := i_7a;
         f_7b := i_7b;
         f_13a:= i_13a;
         f_15c:= i_15c;

         {p_decode := display_decoded_FPL4;
         p_process:= p_add_FDR;}
         pos_RPL4:= o_f+f_7a;
       end;

 destructor TFPL4form.Done;
      begin
        inherited Done;
        disp_FPL4_(FPLn);
        disp_FPL4_(FPLp)
      end;


 procedure TFPL4form.HandleEvent(var _Event: TEvent);
     begin
       {IFDEF DEBUG
        if isKey(_event,'?') then net_pkt_test('net.tst',-1,-1);
       ENDIF}

       inherited HandleEvent(_Event);

       if (_Event.What and evMessage) <> 0 then
          begin
            case _Event.Command of

              cmPREHLAD_RPL : init_formular_RPL; {RunList(@fnNDB,1,true,nil,nil,nil);}

              {$IFDEF SSR_MANAGEMENT}
               cm_SSR  : form_init_ssr (@Self,o_f+i_7c);
               cmUsed  : list_of_used_ssr;
              {$ENDIF}

              else Exit
            end;
            ClearEvent(_Event)
          end
     end;


 procedure TFPL4form.form_init(var x,y: int; dx,dy: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _tit: byte;  _inc_dx,_inc_dy: int
                              );
     var   xt,yt: int;
     begin
       pos_RPL4:= bt_pos;
       if (rpl or (save_rpl_proc<>nil)) and rpl4 then inc(bt_pos);
       inherited form_init(x,y, dx,dy, _kbHot,_cmXXXX,_title,_tit,_inc_dx,_inc_dy);
       if rpl4 then
          begin
            Win^.get_btXY(pos_RPL4,0, xt,yt);
            btRPL4:= New(PTextIcon,Init(Win, xt,yt, 60,4, GetAltCode(get_HotKey(_kbHot,titRPL)),cmPREHLAD_RPL,titRPL,@IcList))
          end
       else btRPL4:= nil;
     end;

 procedure TFPL4form.draw_buttons;
     begin
       if (btRPL4<>nil) and (ind<>pos_RPL4) and (btRPL4^.visible) then btRPL4^.visibility(false);
       if (btSSR<>nil) and (not (ind in[o_f+f_7a+1..o_f+f_7a+2])) then
          begin
            btSSR^.visibility(false);
            btSSU^.visibility(false);
          end;
       inherited draw_buttons;
       if (btSSR<>nil) and (ind in[o_f+f_7a+1..o_f+f_7a+2]) then
          begin
            btSSR^.visibility(true);
            btSSU^.visibility(true);
          end;
       if (btRPL4<>nil) and (ind=pos_RPL4) and (not btRPL4^.visible) then btRPL4^.visibility(true);
     end;


{ ======================
   Naplnenie formulara
  ----------------------
}
 procedure TFPL4form.init_formular; { inicializacia formulara  }
     begin
       InfoCakaj(msgWAITING,tit_FPL4_initialize);
       if not novy then clear_form(itemd,items,nil);
       inherited init_formular;
       init_formular_by_data;
       init_formular_by_stat;
       InfoCakaj_zatvor
     end;


{ Povolenie/zakazanie editacie poli,
  krajsie by bolo mat jedno pole podle ktorho by sa to namaskovalo:
  FPL (7a,7b,7c..... ), rovnako by sa spracovali polia pri dekodovani
  a kodovani;
  ale o 20.47 6 dni pred odchodom na to nie je cas. Uz som ho dost presr...
}
 procedure TFPL4form.init_formular_by_stat;
     var   i,ihead, xt,yt : int;
           sres,s,t : string;
     begin
       ihead:= icao_head_type(stat, sres, @hd_ICAO,ord(high(ms_ICAO)));
       if ihead<0 then Exit;
       {with itemd^[o_f+0] do move(hd_ICAO[ms_ICAO(ihead)][1],item^,minimum(kod_HEAD,strlen(item)));}

       if stat<>hd_ALR then
         for i:= o_f+i_5a to o_f+i_5c do
           begin
             itemd^[i].legal:= nil;
             clear_item_i(i);
             first_pos:= i_15c;
           end
         else first_pos:= i_5a;

       if ms_ICAO(ihead) in [msFPL,msCHG] then
          begin
            if not _FPL_CHG__14_17 then
               begin
                 if (ms_ICAO(ihead)=msFPL) then
                    begin
                      for i:= i_14a to i_14e-1 do clear_item_i(i);
                      for i:= i_17a to i_17c-1 do clear_item_i(i);
                    end;
                 for i:= o_f+i_14a to o_f+i_14e do begin itemd^[i].legal:= nil; clear_item_i(i) end;
                 for i:= o_f+i_17a to o_f+i_17c do begin itemd^[i].legal:= nil; clear_item_i(i) end;
               end;

            if (not novy) and ((not _CHG__7_13) and (ms_ICAO(ihead)=msCHG)) then
               begin
                 itemd^[o_f+i_7a].legal := nil;
                 itemd^[o_f+i_13a].legal:= nil
               end;

            if stat=hd_FPL then first_pos:= i_7a
            else first_pos:= i_15c;

            Exit
          end;

       itemd^[o_f+i_7a].legal := nil;
       itemd^[o_f+i_13a].legal:= nil;

       case ms_ICAO(ihead) of

         msDLA : begin
                   itemd^[o_f+i_13b].legal:= nil;
                   first_pos:= i_13c;
                 end;

         msDEP,
         msACT : begin
                   itemd^[o_f+i_13b].legal:= nil;
                   if not _ACT__FIELDS then
                      begin
                        for i:= i_8a to i_10b do itemd^[o_f+i].legal:= nil;
                        {for i:= i_14a to i_14e do itemd^[o_f+i].legal:= form_FPL4[i].legal;}
                        for i:= i_16a to i_16d do itemd^[o_f+i].legal:= nil;
                        for i:= i_17a to i_17c do itemd^[o_f+i].legal:= nil;
                        for i:= i_15a to i_18+max_FPL4_18_r_hi-1 do itemd^[o_f+i].legal:= nil;
                      end;
                   with FPLn^ do if (_14='') and (eet.kod<>'') then _14:= code_l4_14(eet.kod, eet.h,eet.m,vys,vys_,0,' ',' ');
                   init_formular_14(FPLn^._14);
                   if ms_ICAO(ihead)=msDEP then first_pos:= i_13c
                   else begin
                          first_pos:= i_7c;
                          if delchar(_it(o_f+i_7b),[icao_nxt,' '])='' then
                             begin
                               decode_l4_10(FPLn^._10, s,t);
                               t:= cut_(t);
                               if t<>'' then _in(o_f+i_7b,icao_nxt+t)
                               else first_pos:= i_7b
                             end
                        end;
                   Win^.get_btXY(1,bt_pos, xt,yt);
                   {$IFDEF SSR_MANAGEMENT}
                    if btSSR=nil then
                      begin
                        Win^.get_btXY(1,1, xt,yt);
                        btSSR:= New(PDialogButton,Init(Win, xt,yt, kbAltS, cm_SSR, '~S~SR   ', icKey,icText));
                        btSSR^.visible:= false;
                        btSSR^.bk0:= clBUTTON_COLOR;
                        Win^.get_btXY(1,2, xt,yt);
                        btSSU:= New(PDialogButton,Init(Win, xt,yt, kbAltU, cmUsed, '~U~sed  ', icKey,icText));
                        btSSU^.visible:= false;
                        btSSU^.bk0:= clBUTTON_COLOR;
                      end;
                   {$ENDIF}
                 end;

         msARR{,htFLA} :
                 begin
                   if not _ARR__FIELDS then for i:= i_8a to i_15c-1 do itemd^[o_f+i].legal:= nil;
                   init_formular_16(FPLn^._16);
                   init_formular_17(FPLn^._17);
                   first_pos:= i_16b;
                 end;

         {msABI, msACT, msPAC, msREV :
            begin
              itemd^[o_f+i_7b].legal := form_FPL4[i_7b].legal;
              itemd^[o_f+i_13c].legal:= form_FPL4[i_13c].legal;
              itemd^[o_f+i_14a].legal:= form_FPL4[i_14a].legal;
              itemd^[o_f+i_14b].legal:= form_FPL4[i_14b].legal;
            end
         }
       end;

     end;

 procedure TFPL4form.init_formular_13(_13: string);
     var   _13a,_13b,_13c : string;
           r13a,r13b,r13c : bool;
           h,m : byte;
     begin
       decode_l4_13_ (_13,_13a,h,m,h,m,_13b,_13c,r13a,r13b,r13c);
       _in(o_f+i_13a, _lat_FPL4(_13a));
       _in(o_f+i_13b, _13b);
       _in(o_f+i_13c, _13c);
     end;

 procedure TFPL4form.init_formular_14(_14: string);
     var   h1,m1: byte; vys1: word; vys1_ : char;
           vysI: word; vysI_, vysI_ab : char;
           b14a,b14b,b14c,b14de : bool;
           _14a,_14b,_14c,_14d,_14e  : string;
     begin
       if _14=''  then Exit;

       decode_l4_14_ (_14, _14a,h1,m1,vys1,vys1_,true,vysI,vysI_,vysI_ab, b14a,b14b,b14c,b14de, _14b,_14c,_14d,_14e);
       _in(o_f+i_14a,rightchar(_lat_FPL4(_14a),strlen(itemd^[o_f+i_14a].item)-1,' ')+icao_NXT);
       _in(o_f+i_14b,_lat_FPL4(_14b));
       _in(o_f+i_14c,_lat_FPL4(_14c));
       _in(o_f+i_14d,_lat_FPL4(_14d));
       _in(o_f+i_14e,_lat_FPL4(_14e));
     end;

 procedure TFPL4form.init_formular_16(_16: string);
     var   _16a,_16b,_16c : string;
           r16a,r16b,r16c : bool;
           h,m : byte;
     begin
       decode_l4_16_ (FPLn^._16,0,0,_16a,_16b,h,m,h,m,_16c,r16a,r16b,r16c);
       _in(o_f+i_16a, _lat_FPL4(_16a));
       _in(o_f+i_16b, _16b);
       _in(o_f+i_16c, _lat_FPL4(copy(_16c,1,kod_AP)));
       _in(o_f+i_16d, _lat_FPL4(copy(_16c,kod_AP+1,length(_16c)-kod_AP+1)));
     end;

 procedure TFPL4form.init_formular_17(_17: pchar);
     var   _17a,_17b,_17c : string;
           h,m : byte;
           r17a,r17b,r17c : bool;
     begin
       if _17<>nil then
          begin
            decode_l4_17_ (strpas(_17), _17a,_17b, h,m, _17c, r17a,r17b,r17c);
            _in(o_f+i_17a,_lat_FPL4(_17a));
            _in(o_f+i_17b,_17b);
            _in(o_f+i_17c,_lat_FPL4(_17c))
          end;
     end;


 procedure TFPL4form.init_formular_by_data;
     var   i,k : int;
           s1,s2,s3 : string;
           c1,c2 : char;
           b1,b2 : bool;
           h,m   : byte;
           r : single;
           zac,kon : word;
           p : pchar;

     begin
       _in(o_f+i_3a,_lat_FPL4(stat)+icao_ARR);

     { 3 }
       if novy then
          begin
            clear_item_i(o_f+i_7a);
            if cut_(decode_l4_7a(FPLn^._7))='' then Exit;
          end;

       clear_form(itemd,items,nil);

     { 5 }
       if (stat=hd_ALR) and (FPLp^._5<>nil) then
          begin
            decode_l4_5(strpas(FPLp^._5), s1,s2,s3);
            _in(o_f+i_5a, _lat_FPL4(s1));
            _in(o_f+i_5b, icao_NXT+_lat_FPL4(s2));
            _in(o_f+i_5c, icao_NXT+_lat_FPL4(s3));
          end;

     { 7 }
       decode_l4_7 (FPLn^._7, s1,s2,s3);
       _in(o_f+i_7a, _lat_FPL4(s1));
       _in(o_f+i_7b, icao_NXT+_lat_FPL4(s2));
       _in(o_f+i_7c, s3);

     { 8 }
       decode_l4_8 (FPLn^._8,c1,c2);
       _in(o_f+i_8a, _lat_FPL4(c1));
       _in(o_f+i_8b, _lat_FPL4(c2));

     { 9 }
       decode_l4_9 (FPLn^._9, s1,s2,s3);
       _in(o_f+i_9a, _lat_FPL4(s1));
       _in(o_f+i_9b, _lat_FPL4(s2));
       _in(o_f+i_9c, icao_NXT+_lat_FPL4(s3));

     { 10 }
       decode_l4_10 (FPLn^._10, s1,s2);
       _in(o_f+i_10a, _lat_FPL4(s1));
       _in(o_f+i_10b, icao_NXT+_lat_FPL4(s2));

     { 13 }
       init_formular_13 (FPLn^._13);

     { 14 }
       init_formular_14 (FPLn^._14);

     { 16 }
       init_formular_16 (FPLn^._16);

     { 17 }
       init_formular_17 (FPLn^._17);

     { 15 }
       decode_l4_rych_vys_ (getstr(strpas(FPLn^._15),1,[icao_NXIT]),r,c1, s1,b1, zac,c2, s2,b2);
       _in(o_f+i_15a,_lat_FPL4(s1));
       _in(o_f+i_15b,_lat_FPL4(s2));

       {for i:= o_f+i_15c to o_f+i_15c+max_FPL4_15_r_hi-1 do clear_item_i(i);}
       if get_ind(pchars(FPLn^._15),strlen(FPLn^._15),2,[icao_NXIT],zac,kon) then
          begin
            p:= @FPLn^._15[zac];
            init_pole(o_f+i_15c, p)
          end;

     { 18 }
       {for i:= o_f+i_18 to o_f+i_18+max_FPL4_18_r_hi-1 do clear_item_i(i);}
       init_pole(o_f+i_18, FPLn^._18);
     end;


 procedure TFPL4form.vlozeny_text(kde: int; s: string);
     begin
       if kde<>o_f+i_9b then Exit;
       _in(o_f+i_9c,icao_NXT+_9c_data(_it(o_f+i_9b)));
       Write;
     end;


{$IFDEF RPL}

{ ======================
   Naplnenie podla RPL
  ----------------------
}
 function _nacitaj_RPL(RPL: PRPL; adr: Ppb_record): bool; far;
    var   FPL  : PFPL4;
          date : TDate;
    begin
      _nacitaj_RPL:= false;
      if adr=nil then Exit;

      _nacitaj_RPL:= true;
      adr^.b:= true;

      FPL:= PFPL4(adr^.p);
      date:= FPL^.date;
      FPL^.src:= 0;
      disp_FPL4(FPL);
      code_RPL_to_FPL4_ (RPL^,FPL^,true);
      FPL^.date:= date;
    end;


 procedure TFPL4form.init_formular_RPL;
     var   key : Tkey_fpl;
           adr : Tpb_record;
           i   : int;
     begin
       if (f_7a=-1) or (f_13a=-1) then Exit;

       fillchar(key,sizeof(key),0);
       key._7a  := _it(o_f+i_7a);
       key._13a := _it(o_f+i_13a);

       adr.p:= FPLn;
       adr.b:= false;

       _spracuj_RPL (true,true, @key, nil,
                     _TBFunc_p,@_nacitaj_RPL,@adr,
                     tit_RPL_PREHLAD,hlp_PREHLAD_RPL
                    );

       if adr.b then
          begin
            init_formular;
            ReDraw
          end
     end;

{$ENDIF}


{ ===============================
   Nacitanie udajov z formulara
  -------------------------------
}
 function  TFPL4form.read_formular: bool;
    var    s,t,u, x,y, res : string;
           b1,b2,b3 : bool;

    begin
      read_formular:= false;
      disp_FPL4(FPLn);         { nesmie sa zrusit ! }
      res:= '';

      FPLn^._3:= stat; {delchar(_it(o_f+i_3a),[icao_ARR]);}

      if (stat<>hd_ALR) and (FPLp<>nil) then FPLn^._5:= StrNew(FPLp^._5)
      else FPLn^._5:= strpasnew(code_l4_5(_it(o_f+i_5a),_it(o_f+i_5b),_it(o_f+i_5c)));

      x:= delchar(_it(o_f+i_7b),[icao_NXT]);
      FPLn^._7 := code_l4_7 (_it(o_f+i_7a),x,_it(o_f+i_7c));

      _AFIL_10:= _EFIL_10;
      FPLn^._10:= code_l4_10_ (_it(o_f+i_10a),delchar(_it(o_f+i_10b),[icao_NXT]),getchar(x));

      _AFIL_8:= _EFIL_8;
      FPLn^._8:= code_l4_8 (getchar(_it(o_f+i_8a)),getchar(_it(o_f+i_8b)),false);

      _AFIL_9:= _EFIL_9;
      FPLn^._9:= code_l4_9_(_it(o_f+i_9a),_it(o_f+i_9b),delchar(_it(o_f+i_9c),[icao_NXT]));
      _code_9_by8643 (FPLn^._9,false);

      FPLn^._13:= _it_(o_f+i_13a)+_it_(o_f+i_13b)+cut_r(icao_NXIT+_it(o_f+i_13c));

      s:= cut_(delchar(_it(o_f+i_14a),[icao_NXT]));
      if s<>'' then FPLn^._14:= s + icao_NXT + _it(o_f+i_14b) + cut_r(_it(o_f+i_14c)+_it(o_f+i_14d)+_it(o_f+i_14e))
      else FPLn^._14:= '';

      FPLn^._16:= _it_(o_f+i_16a)+_it_(o_f+i_16b)+cut_r(icao_NXIT+_it(o_f+i_16c) + cut_r(icao_NXIT+_it(o_f+i_16d)));

      s:= _it(o_f+i_15a)+_it(o_f+i_15b);
      if (s='') and _EFIL_15ab then s:= _15ab_to_9 (FPLn^._9,s);
      read_pole(o_f+i_15c,FPLn^._15);
      FPLn^._15:= StrNPCopy(FPLn^._15,s+icao_NXIT,false,true);

      read_pole(o_f+i_18,FPLn^._18);

      if FPLp<>nil then FPLn^._19:= StrNew(FPLp^._19);
      if FPLp<>nil then FPLn^._20:= StrNew(FPLp^._20);

      read_formular:= true
    end;


 function TFPL4form.check_formular: bool;
    var   res,r1,r2,r3  : string;
          ires,ir2 : int;
          bres,pomb : bool;
          k1,k2,p,ssrp,ssr_ : string;
          is_ind: bool;
          dbind: int;
          cm : byte;
    label X;

    begin
      check_formular:= false;
      if not read_formular then Exit;

      res:= ''; ires:= -1; bres:= true;

     { Kontrola priznakov podania/spracovania FPL :
        - ak bola vykonana zmena do FPL, nastavenie priznaku do pola 18...,
          zaroven by sa malo skontrolovat, ci neboli porusene ostatne
          priznaky spracovania...
     }
      if (FPLp=nil) or chg_FPL4(FPLp,FPLn) then
         begin
           _dec_18 (FPLn^._18, rmk_FDA);
           _update_18 (FPLn^._18,rmk_FDA+icao_NXT+code_l4_utc(hour,min),0)
         end;

     { Kontrola spravnosti zapisu,
       zapis novo prepocitanych udajov do formulara
     }
      InfoCakaj(msgWAITING,tit_FPL4_checking);
      FPLn^.stat:= stat;
      _format_FPL4new(FPLn,cm_spracuj_FPL4_EDI_,res,ires,is_ind,dbind);
      bres:= res='';
      InfoCakaj_zatvor;

      if     in_icao_head (FPLn^.stat,ms_ICAOest,pomb)
         and (FPLn^.data<>nil) and (FPLn^.data^.fdr<>nil) then
         begin
           if (FPLn^.data^.fdr^.poz >= poz_PRIST) then
              begin
               { Kontrola casovej platnosti spavy EST
               }
                ires:= l4_err(a_rte,'',i_14b,err_rte_ukonceny_let, res);
                bres:= false
                {bres:= Ask2(msgVERIPHY,r2,titNo,clGRe,Red, waitASK*18)=ansAno;}
              end
           else begin
                 { Kontrola duplicity spracovania kodov ssr
                   - zabezpeci formulat FPLC
                     a funkcia zarad FPLC
                 }
                 {$IFDEF SSR_MANAGEMENT}
                  if (FPLn^.data^.fdr^.fpl<>nil) then
                     begin
                       if FPLp<>nil then decode_l4_7 (FPLp^._7, k1,k2,ssrp) else ssrp:= '';
                       decode_l4_7 (FPLn^._7, k1,k2, FPLn^.data^.fdr^.fpl^.ssr);
                       decode_l4_10 (FPLn^._10, k1,ssr_);  FPLn^.data^.fdr^.fpl^.ssr_:= ssr_;
                       if not check_filled_ssr (FPLp,FPLn,k1,k2,'', FPLn^.data^.fdr^.fpl^.ssr, res) then Exit;
                       if (res='') and (FPLn^.data^.fdr^.fpl^.ssr<>'') then
                          _zarad_FPLCssr (FPLn^.data^.fdr^.fpl, false,res,nil, nil,false);
                       if res<>''then ires:= o_f+i_7c
                       else FPLn^._7:= decode_l4_7a(FPLn^._7)+icao_NXT+ssr_+FPLn^.data^.fdr^.fpl^.ssr;
                       bres:= res=''
                     end;
                 {$ENDIF}
                end
         end;

      if bres then
         begin
           init_formular_by_data;
           init_formular_by_stat;
           TBox.ReDraw;

         { Nastavenie sposobu spracovania :

           a) zaradenie spravy FPL4
         }
           if FPLn^.data=nil then
              begin
                New(FPLn^.data);
                fillchar(FPLn^.data^,sizeof(FPLn^.data^),0);
                FPLn^.data^.cmnd:= cm_spracuj_FPL4_EDI_
              end;
           FPLn^.data^.cmnd:= FPLn^.data^.cmnd or cm_spracuj_FPL4_EDI;

         { b) zaradenie spravy FPLC
         }
           {if    in_icao_head (FPLn^.stat,ms_ICAOact,pomb)
               or find_FPLCa(codekey_FPL4(FPLn)<>0) then
               FPLn^.data^.cmnd:= FPLn^.data^.cmnd or cm_spracuj_FPL4_FPLC;

            - riesi fcia "zarad" na zaklade zdroja spracovania...
           }


         { Bola zmenena identifikacia letu ?
         }
           k1:= codekey_FPL4(FPLp);
           k2:= codekey_FPL4(FPLn);
           if (not novy) and (k1<>k2) and (FPLp<>nil) and (FPLp^.stat<>hd_CNL) then
              begin
                k1:= decode_l4_7a(FPLp^._7)+'-'+decode_l4_13a(FPLp^._13);
                k2:= decode_l4_7a(FPLn^._7)+'-'+decode_l4_13a(FPLn^._13);
                l4_err(a_7a,'',i_7a,err_7a_chng1, r1);
                l4_err(a_7a,'',i_7a,err_7a_chng2, r2);
                l4_err(a_7a,'',i_7a,err_7a_chng3, r3);
                case Ask2(msgVERIPHY, r1+' '+k1+' '+r2+' '+k2+'. '+r3,titNo,clGRe,Red, waitASK*18) of
                  ansAno : begin
                           { Zrusenie povodneho planu
                           }
                             New(FPLp^.data);
                             new_FDR_ (nil,FPLp^.data^.fdr);
                             FPLp^.data^.cmnd:= cm_spracuj_FPL4_EDI;
                             if in_icao_head (FPLp^.stat,ms_ICAOact,pomb) then
                                FPLp^.data^.cmnd:= FPLp^.data^.cmnd or cm_spracuj_FPL4_FPLC;
                             FPLp^.stat:= hd_CNL;
                             ir2:= _decode_FPL4 (FPLp^,false,r2);
                             _zarad_FPL4 (FPLp,FPLp^.data^.cmnd,FPLp^.stat,true,user);
                             disp_FPL4_(FPLp);
                             FPLn^.stat:= hd_FPL;
                             novy:= true;
                           end;

                  ansNie : begin
                           { Zaradenie ako noveho planu
                           }
                             FPLn^.stat:= hd_FPL
                           end

                  else bres:= false
                end;
                stat:= FPLn^.stat;
              end;

         (*
          { Existuje uz taky FPL ?
          }
           s:= codekey_FPL4(FPLn);
           if (FPLn._STT = hd_FPL) and (read_FPL4(s, @FPLi)>-1) then
              begin
                if FPLi._STT<>hd_CNL then
                   bres:= Ask2(msgVERIPHY,'FPL '+s+' '+inf_exist+' '+ask_prepisat,titNo,clGRe,Red, waitASK*18)=ansAno;
                disp_FPL4(FPLi)
              end;


           InfoCakaj(msgWAITING,tit_FPL4_processing+'...');

          { Zaradenie FPL do spracovania :
          }
           check_par:= check_FPL4_SRC; { medzitym sa to mohlo zmenit }
                                       { check_FPL4_FDR; -> uz bolo skontrolovane }
           if in_icao_head (FPLn._3, ms_ICAOact, pomb) then
              begin
              { V pripade, ze vysledkom spracovania je sprava na aktivny plan,
                podlieha kontrole na spravnost dekodovania
              }
               check_par:= check_par or zarad_FPL4_EST or check_FPL4_EST;

           if bres and (res='') then
              begin
                p_add_FDR(FPLn,@FDR,check_par,res,ires);
                bres:= (res='') and (ires=0)
              end;
         *)

           if bres and _FPL4act (FPLn) then
              begin
                bres:= formular_cFPL (FPLn^.data^.fdr^.fpl,
                                 user,false,cut_(strpas(Self.win^.bttitle^.title)),i_15c_FDR,true,false,
                                 false
                                );
                if bres then disp_cFPL_(FPLn^.data^.fdr^.fpl);
              end
         end;

      check_formular:= bres;
      if res<>'' then ErrorS(ires,res)
    end;


 function TFPL4form.display_decoded_data (var res: string; var ires: int): bool;
    begin
      read_formular;
      _display_decoded_FPL4 (FPLn,true,res,ires);
      display_decoded_data:= (res='') and (ires=0)
    end;
