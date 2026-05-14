{ rozdekoduje vysku a upravi ju na standartny tvar
  pouzivany systemom 'S'
}

 function decode_vys(s: string; var vys: word; var vys_,vys_a: char): bool;
    var   pocet: int;
          v : word;
    begin
      decode_vys:= true;
      s:= uni_str(s); vys:= 0; vys_:= altS; vys_a:= ' ';
      if s='' then Exit;
      decode_vys:=      decode_l4_vys_ (s,vys,vys_,@vys_a,pocet,true)
                   and (get_altM(vys_,vys)<high(vys))
                   and (pocet=length(s))
    end;


 function urc_bod_vypoctu(form: PcFPLform; FPL: PDcFPL; var bod: int): word;

    var   ndbLAST,ndbNEXT,ndbFIRST: string[KOD_OB];
          od_bodu1,od_bodu2 : int;
          _OB : TOBxy;
          _B  : TsBod;

          FPLitems : array[0..9] of PItem;
          i,x,y, items,last : int;
          M : PWinMenu;
          E : TEvent;

          s1,s2 : string;
          dTh,dT,dTi : real;
          b : bool;

    begin
      format_cFPL(FPL);
      stav_cFPL(FPL,absTime,b);
      urc_bod_vypoctu:= cmEST_NOPL;
      bod:= 0;

      if not (zmenena_trat_FPLc(@form^.FPLp,FPL, od_bodu1) and (FPL^.bodov>1)) then Exit;

      M:= WinMenu(titEST_,hlp_cFPL_vyp, nil);
      items:= 0;

     { Prepocet od vstupneho bodu na trat
     }
      {if (od_bodu1>0) then}
         begin
           FPLitems[items]:= Item(titEST_EST+' ('+FPL^.trat[0].kod+') ', cmEST_EST, nil);
           inc(items)
         end;

     { Prepocet od priebezneho bodu trate
     }
      od_bodu2:= 0;
      dT:= secDAY; dTh:= TimeToSec(hour,min,0);
      for i:= 0 to FPL^.bodov-1 do with FPL^.trat[i] do
        begin
          dTi:= abs(dTh-TimeToSec(h,m,0));
          if dTi<dT then begin od_bodu2:= i; dT:= dTi end
        end;
      if od_bodu1>od_bodu2 then
         begin
           i:= od_bodu2; od_bodu2:= od_bodu1; od_bodu1:= i
         end;

      if (od_bodu1<>0) and (od_bodu1<>od_bodu2) then
         begin
           FPLitems[items]:= Item(titEST_LAST+' ('+FPL^.trat[od_bodu1].kod+') ',cmEST_LAST,nil);
           inc(items)
         end;

      if (od_bodu2<>0) then
         begin
           FPLitems[items]:= Item(titEST_NEXT+' ('+FPL^.trat[od_bodu2].kod+') ',cmEST_NEXT,nil);
           inc(items);
         end;

      FPLitems[items]:= NewLine2(0, nil);
      inc(items);

     { Start zo znameho letiska
     }
      if is_OB (FPL^.start.kod, _B,true) and _B.ine.podriadene then
         begin
           FPLitems[items]:= Item(titEST_DEP+' ('+FPL^.start.kod+') ', cmEST_DEP, nil);
           inc(items)
         end;

     { Bez prepoctu
     }
      FPLitems[items]:= Item(titEST_NOPL,cmEST_NOPL,nil);
      inc(items);

      for i:= 0 to items-1 do M^.AddItem(FPLitems[i]);

      fillchar(E,sizeof(E),0);
      with form^ do begin x:=  x0 + itemd^[i_15c_FDR].dx; y:=  y0 + itemd^[i_15c_FDR].dy end;
      M^.MoveRel(x+30-M^.x0,y+30-M^.y0);
      M^.Run(E);
      Dispose(M, Done);
      bod:= 0;
      if ((E.What and evMessage) <> 0) then
         case E.Command of
           cmEST_LAST : bod:= od_bodu1;
           cmEST_NEXT : bod:= od_bodu2
           else bod:= 0;
         end
      else begin
             E.Command:= cmNil;
             bod:= -1
           end;

      urc_bod_vypoctu:= E.Command
    end;


 function cFPL_check_(form: PcFPLform; FPL: PDcFPL; check_en,update_en: bool): bool;

    var   FPLp : PDcFPL;

          s,p,res : string;
          pom,lh,lm : byte;
          cmXXXX  : word;
          erra: string;
          errc,ires: int;
          i,j,bod: int;
          podany,dt,dtv,dr : real;
          bres,prepocitat: bool;
          c: char;
          B   : TsBod;
          Bxy : TOBxy;

          ry,minr, maxr : single;
          ry_,v_        : char;
          v,minv, maxv  : word;

          ans : TAnswer;
          is,arr : bool;

    label X,Y,E;

    begin
      cFPL_check_:= false;
      erra:= ''; errc:= 0;
      ires:= -1; res:= '';
      FPLp:= PDcFPL(form^.adr_data);

      with FPL^ do
        begin
          if cut_(stt)='' then stt:= hd_EST;

        { identifikacia  ----------------------------- }

          idn:= form^._it(i_7_FDR);
          if idn='' then
             begin
               set_rk(erra,a_7a, errc,err_7a_missing, ires,i_7_FDR);
               if check_en then goto X
             end;

          inf:= form^._it(i_18_FDR);

          _8a:= getchar(form^._it(i_8a_FDR));
          _8b:= getchar(form^._it(i_8b_FDR));

          typ:= form^._it(i_9_FDR);

        { rychlost ---------------------------------- }

          rych_:= getcharu(form^._it(i_15a_FDR_));
          if rych_= ' ' then rych_:= spdK;
          val(form^._it(i_15a_FDR), rych, ires);
          {if (rych<100) or (rych>3000) then begin set_rk(r,k, 5,14); goto X end;}


        { vysky ------------------------------------- }

          if (not decode_vys(form^._it(i_15b_FDR),vys,v_,c)) or (vys=0) then
             begin
               set_rk(erra,a_L4, errc,err_l4444_vyska_chyba, ires,i_15b_FDR);
               if check_en then goto X
            end;
          vys:= _vys_OB (vys,v_);

          if not decode_vys(form^._it(i_14c_FDR), vys1,v_,vys1_a) then
             begin
               set_rk(erra,a_L4, errc,err_l4444_vyska_chyba, ires,i_14c_FDR);
               if check_en then goto X
             end;
          vys1:= _vys_OB (vys1,v_);

          {$IFDEF FPLC_ION}
           s:= form^._it(i_EXIo);
           if (s<>'') and (not decode_vys(s, vysO,v_,vysO_a)) then
              begin
                set_rk(erra,a_L4, errc,err_l4444_vyska_chyba, ires,i_EXIo);
                if check_en then goto X
              end;
           vysO:= _vys_OB (vysO,v_);

           s:= form^._it(i_EXIh);
           if (s<>'') and (not decode_vys(s, vysH,v_,c)) then
              begin
                set_rk(erra,a_L4, errc,err_l4444_vyska_chyba, ires,i_EXIh);
                if check_en then goto X
              end;
           vysH:= _vys_OB (vysH,v_);
          {$ENDIF}


         {$IFDEF FPL4}
          if _9b_rychvys (FPL^.typ,true, ry,ry_, minr, maxr, v,v_, minv,maxv) then
             begin
               if FPL^.rych=0 then begin FPL^.rych:= ry; FPL^.rych_:= ry_ end;
               if FPL^.vys=0  then FPL^.vys := get_altM (v_,v) div m_S
             end;
         {$ENDIF}

        { start, prist ------------------------------ }
          start.kod:= form^._it(i_13a_FDR);
          start.h:= 0; start.m:= 0;
          s:= form^._it_(i_13b_FDR);
          if s<>'  :  ' then
             if not GetTimeStr(start.h,start.m,pom, s) then
                begin
                  set_rk(erra,a_L4, errc,err_l4444_time, ires,i_13b_FDR);
                  if check_en then goto X
                end;

          if (form^._it_(i_13b_FDR+1)<>'  :  ') then
             begin
               if (not GetTimeStr(start_.h,start_.m,pom, form^._it(i_13b_FDR+1))) then
                  begin
                    set_rk(erra,a_L4, errc,err_l4444_time, ires,i_13b_FDR+1);
                    if check_en then goto X
                  end
             end
          else begin start_.h:= start.h; start_.m:= start.m end;

          prist.kod:= form^._it(i_16a_FDR);
          s:= form^._it_(i_16b_FDR);
          if (s<>'  :  ') then
             begin
               if not GetTimeStr(prist.h,prist.m,pom, s) then
                  begin
                    set_rk(erra,a_L4, errc,err_l4444_time, ires,i_16b_FDR);
                    if check_en then goto X
                  end;
             end
          else begin prist.h:= start.h; prist.m:= start.m end;


        { trat -------------------------------------- }
          v:= vys; bodov:= 0; lh:= 0; lm:= 0;
          fillchar(FPL^.trat,sizeof(FPL^.trat),0);
          prepocitat:= true;
          for i:= 0 to max_bod_FPLC-1 do
              begin
                bod:= 3*i+i_15c_FDR;
                s:= form^._it(bod);
                if not NDB_SL then s:= upstring(s);
                if (s<>'') and (s<>no_pl) then with trat[bodov] do
                   begin
                     kod:= s;
                     bres:= is_OB(kod,B,true) or (FPLC_15_MIL_OB and get_OB_XYM(kod,Bxy));
                     if check_en and (prepocitat) and FPLC_CHECK_15 and (not bres) then
                        begin
                          l4_err (a_RTE,'',bod,30,res);
                          form^.GoToPos(bod);
                          if     (Ask2(msgVERIPHY,res+' '+msgCONTINUE+'?',titNo,White,clBUTTON_COLOR,waitASK*18)<>ansAno)
                             and check_en then Exit
                          else res:= '';
                        end;
                     prepocitat:= prepocitat and bres;

                     inc(bod);
                     p:= form^._it_(bod);
                     if (p<>'  :  ') then
                        begin
                          if (not GetTimeStr(h,m,pom, p)) then
                             begin
                               set_rk(erra,a_L4, errc,err_l4444_time, ires,bod);
                               if check_en then goto X
                             end;
                          lh:= h; lm:= m
                        end
                     else if i=0 then
                          begin
                            ires:= l4_err (a_RTE,'',bod,31,res);
                            if check_en then goto X
                          end
                     else if bres then begin h:= lh; m:= lm end
                     else begin
                            ires:= l4_err (a_RTE,'',bod,32,res);
                            if check_en then goto X
                          end;

                     inc(bod);
                     if not decode_vys(form^._it(bod), vys,v_,vysab) then
                        begin
                          set_rk(erra,a_L4, errc,err_l4444_vyska_chyba, ires,bod);
                          if check_en then goto X
                        end;
                     vys:= get_altM(v_,vys) div m_S;
                     if vys=0 then vys:= v;
                     v:= vys;

                   { dalsi bod ... }
                     inc(bodov)
                   end
                else if (not check_en) and (i=0) then break
              end;


        { zvysok ------------------------------------ }

          if not update_en then goto E;

          {_8a:= IFR_let;
          _8b:= PRAV_DOPRAVNY_LET;
          if FPLp<>nil then
             begin
               if cut_(FPLp^._8a)<>'' then _8a:= FPLp^._8a;
               if cut_(FPLp^._8b)<>'' then _8b:= FPLp^._8b;
             end;
        }

          if date.r=0 then
             begin
               init_date(date, year,month,day);
               if     ((hour>=22))
                  and ((trat[0].kod<>'') and (trat[0].h<=1))
                  and ((date.d=day) and (date.m=month))
                      then NextDate(date.r,date.m,date.d);

               podany:= TimeToSec(hour,min,0)
             end;
          {if bodov>0 then init_time(eet, trat[0].h,trat[0].m,0)
          else} init_time(eet,  hour,min,0);
        end;

     {$IFDEF FPL4}
      if check_en and (cut_(FPL^.trat[0].kod)='') or (FPL^.trat[0].kod=no_pl) then
         begin
           ires:= i_15c_FDR; l4_err(a_15c,'',i_15c,err_15c_nenajdene_zname_body_trate, res);
           form^.GoToPos(i_15c_FDR);
           if     (Ask2(msgVERIPHY,res+' '+msgCONTINUE+'?',titNo,White,clBUTTON_COLOR,waitASK*18)<>ansAno)
              and check_en then Exit
           else res:= ''
         end;
     {$ENDIF}

      {cFPL_init_data (form,FPL);
      for i:= 0 to i_15c_FDR-1 do form^.WriteItem(i);}

      arr:= false;

      { Prepocet casov na trati
      }
      if prepocitat and check_en then
         begin
           if (FPL^.bodov>1) then
              begin
                cmXXXX:= urc_bod_vypoctu(form, FPL,bod);
                case cmXXXX of
                  cmEST_NOPL :
                    begin
                    end;

                  cmEST_DEP,
                  cmEST_EST,
                  cmEST_LAST,
                  cmEST_NEXT :
                    begin
                      if (FPL^.rych=0) then
                         begin
                           set_rk(erra,a_L4, errc,err_l4444_rych_chyba, ires,i_15a_FDR);
                           {set_rk(ires,k, i_15a_FDR,13);}
                           goto X
                         end;
                      s:= prepocet_trate_FPLc(FPL,cmXXXX, bod);
                      if s<>NULL then
                         begin
                           form^.ErrorS(i_15c_FDR,s);
                           Exit
                         end;
                      arr:= true
                    end

                  else goto E
                end;
              end
           {else if delchar(form^._it(i_15c_FDR+1),[':',' '])='' then
                   begin
                     set_rk(ires,k, i_15c_FDR+1,61);
                     goto X
                   end};
         end;

      ires:= regularita_casov_na_bodoch_cFPL (FPL,false);
      if ires>-1 then
         begin
           l4_err(a_15c,'',i_15c,err_15c_nespravny_casovy_profil, s);
           form^.ErrorS(i_15c_FDR+ires*3+1,s);
           Exit
         end;

      cFPL_init_route(form, FPL);
      for i:= i_15a_FDR_ to form^.items-1 do form^.WriteItem(i);

      { Oprava zmeny casu startu
      }
      with FPL^ do if check_en and (bodov>0) and (start.kod=trat[0].kod) then
         begin
           start_.h:= trat[0].h; start_.m:= trat[0].m
         end;

      { Prepocet casu pristatia
      }
      if (FPL^.prist.kod<>'') and (arr or (cut_(form^._it(i_16b_FDR))=':')) then
         begin
           pristatie_cFPL(FPL)
         end
      else begin
             oprava_casu_pristatia_cFPL(FPL);
             format_cFPL(FPL);
           end;

      { Aktualny cas podania stripu ?
      }
      if (check_en) and (FPL^.poz>poz_PRIST) then
         begin
           ires:= l4_err (a_RTE,'',3*(FPL^.na_bod)+i_15c_FDR,33,res);
           form^.GoToPos(ires);
           if     (Ask2(msgVERIPHY,res+' '+msgCONTINUE+' ?',titNo,White,clBUTTON_COLOR,waitASK*18)<>ansAno)
              and check_en then Exit
           else res:= ''
         end;

      { Nie je daleko letiska startu ku prvemu bodu
        a od posledneho bodu ku letisku pristatia ?
      }
        {i:= _OBind(FPL^.start.kod,LK,LKs);
        if (i>=0) and (bodov>0) and (rych<>0) then
           begin
             dt:= abs(timetosec(start_.h,start_.m,0) - timetosec(trat[0].h,trat[0].m,0));
             dtv:=
           end;}


      { Je SSR dovoleny ?
      }
      if check_en then
         begin
           FPL^.ssr0:= form^._it(i_7b_FDR+1);
           FPL^.ssr:=  form^._it(i_7b_FDR);
           {$IFDEF SSR_MANAGEMENT}
            if not check_filled_ssr (FPLp,FPL, FPLp^.ssr,FPL^.ssr_,FPL^.ssr0, FPL^.ssr, res) then Exit;
            if (res='') and (FPL^.ssr<>'') then _zarad_FPLCssr (FPL, false,res,nil, nil,false);
           {$ENDIF}
           if res<>''then
              begin
                ires:= i_7b_FDR;
                goto X
              end
           else begin
                  form^._in(i_7b_FDR,FPL^.ssr);
                  form^.WriteItem(i_7b_FDR);
                  form^.Write;
                end;
         end;

      {$IFDEF PVO}
       if FPLp<>nil then FPL^.rec_cas:= FPLp^.rec_cas
       else init_time(FPL^.rec_cas, hour,min,sec);
      {$ENDIF}

      cFPL_check_:= true;
      Exit;

      X : if (res='') then res:= l4_errs(erra,'',errc);
      Y : if (res<>'') then form^.ErrorS(ires,res);

      E :

    end;

 function cFPL_check(form: PcFPLform; FPL: PDcFPL): bool;
    begin
      cFPL_check:= cFPL_check_(form, FPL, true,true)
    end;
