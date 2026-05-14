 function  zarad_ssr (flight,ssr,ssrp : string;
                      exi  : real;
                      stat : string;

                      zaradit : bool;
                      var res : string;
                      err : pstring
                     ): int;

    var    ires, i : int;
    begin
      zarad_ssr:= -1;
      res:= '';
      if err<>nil then err^:= '';
      ires:= -1;


     {$IFDEF SSR_MANAGEMENT}

     { Je kod pouzity danym letom, v ochrannej lehote alebo nepouzity ?
     }
       ires:= ssr_in_use (ssr,flight);
       if ires>-1 then l4_err (a_SSR,'',0,ires,res);


     { Neexistuje, bol zmeneny kod alebo exi
     }
       if (ssr<>'') then
          begin
            if zaradit then
               begin
                {$IFDEF SSR_SERVER}
                 if (ires=-1) then ssr_save (ssr,flight,exi,stat)
                 else err_save (ires,ssr,flight,res,'');
                {$ELSE}
                 ssr_save (ssr,flight,exi,stat);
                {$ENDIF}
               end;
            if (ires>-1) and (err<>nil) then err^:= codeERR_SSR (ires,ssr,flight,res);
          end;


     { Bol kod zmeneny ?
     }
       if zaradit and ((ssrp<>ssr) and (ssrp<>'')) then
          begin
            i:= SSRs^.najdi(ssrp);
            if (i>-1) and eq_str(strpas(SSRs^.ssr_a^[i]^.flight),flight) then ssr_zrus (ssrp);
          end;

     {$ENDIF}

      zarad_ssr:= ires
    end;


 function list_ssr (x,y: int; mil: bool; var res: string): string;

    var   s, fn1,fn_, sres : string;
          ft1 : text;
          {$IFDEF BN_MANAGEMENT}
           fn2 : string;
           ft2 : text;
          {$ENDIF}
          i, p1,p2: int;

          ssr : p_ssr_record;

          ld : TListDesc;
          lst: PList;

    begin
      sres:= '';
      res:= '';

      {$IFDEF SSR_MANAGEMENT}

      { a) vytvorenie docasnych suborov s volnyni kodmi ssr
      }
       m_set_shape(HODINY);
       fn1:= pathTMP+'ssr.@@1';
       Assign(ft1,fn1); Rewrite(ft1);
       writeln(ft1,'; '+cfg_SSR_CODE+kbNL);
       {$IFDEF BN_MANAGEMENT}
        fn2:= pathTMP+'ssr.@@2';
        Assign(ft2,fn2); Rewrite(ft2);
        writeln(ft2,'; '+cfg_BOARD_NUMBER+kbNL);
       {$ENDIF}
       p1:= 0; p2:= 0;
       for i:= 0 to SSRs^.top do
         begin
           ssr:= SSRs^.ssr_a^[i];
           if (_is_ssr_used(ssr^.last)=-1) then
              begin
                if (((not mil) and (ssr^.user=ssr_atca)) or (mil and (ssr^.user=ssr_mil))) then
                  begin
                    writeln(ft1,' '+ssr^.code);
                    inc(p1);
                  end
                {$IFDEF BN_MANAGEMENT}
                 else if (((not mil) and (ssr^.user=uvd_atca)) or (mil and (ssr^.user=uvd_mil))) then
                   begin
                    writeln(ft2,' '+ssr^.code);
                    inc(p2)
                  end
                {$ENDIF}
              end;
         end;
       writeln(ft1,kbNL);
       Close(ft1);
       {$IFDEF BN_MANAGEMENT}
        writeln(ft2,kbNL);
        Close(ft2);
       {$ENDIF}

       fn_:= pathTMP+'ssr.@@@';
       vytvor_novy_subor(fn_);
       if p1>0 then CopyFileI (fn1,fn_,0,true,false);
       {$IFDEF BN_MANAGEMENT}
        if p2>0 then CopyFileI (fn2,fn_,0,true,false);
       {$ENDIF}
       m_restore_shape;

      { b) volba kodu volneho ssr
      }
       if (p1>0) or (p2>0) then
          begin
            fillchar(ld,sizeof(ld),0); fn_:= fn_+NULL; ld.fn:= @fn_[1];
            lst:= New(PList,Init(@ld,'',[],lst_vsetky_polozky,false,nil,true));
            lst^.hlpXXX:= hlp_SSR_ASSIGN;
            sres:= lst^.get_item(x,y);
            Dispose(lst,Done)
          end
       else l4_err(a_ssr,'',0,err_ssr_noavaible, res);

      { c) upratanie
      }
       DelFile(fn1);
       {$IFDEF BN_MANAGEMENT}
        DelFile(fn2);
       {$ENDIF}
       DelFile(fn_);
      {$ENDIF}

      list_ssr:= sres
    end;




 function _assign_ssr (mil: pbool; ssr: p_ssr_record): bool; far;
    begin
      _assign_ssr:=      (_is_ssr_used(ssr^.last)=-1)
                     and (   ((not mil^) and (ssr^.user in [ssr_atca{,uvd_atca}]))
                          or (mil^ and (ssr^.user in [ssr_mil{,uvd_mil}]))
                         )
    end;

 function assign_ssr (mil: bool; var res: string): string;
    var   sres : string;
          ssr  : p_ssr_record;
          i    : int;
    begin
      sres:= '';
      res:= '';

      {$IFDEF SSR_MANAGEMENT}
       i:= 0; while i<=SSRs^.top do
         begin
           ssr:= SSRs^.ssr_a^[i];
           if _assign_ssr(@mil,ssr) then
              begin
                sres:= ssr^.code;
                break;
              end;
           inc(i);
         end;
       if (sres='') or (i>SSRs^.top) then l4_err(a_ssr,'',0,err_ssr_noavaible, res);
      {$ENDIF}

      assign_ssr:= sres
    end;


 procedure list_of_used_ssr;
     var   s,fn,t,u : string;
           ft : text;
           i,c,p : int;
           r : real;
           h,m,e : byte;
           d : Tdate;

           ssr : p_ssr_record;

           ld  : TListDesc;
           lst : PList;

     begin
       {$IFDEF SSR_MANAGEMENT}

       { a) vytvorenie docasneho subora pre vypis
       }
        m_set_shape(HODINY);
        fn:= pathTMP+'ssr.@@3';
        Assign(ft,fn); Rewrite(ft);
        fillchar(ssr,sizeof(ssr),0);
        c:= 0; p:= 0;
        for c:= 0 to 1 do
          begin
            for i:= 0 to SSRs^.top do
              begin
                ssr:= SSRs^.ssr_a^[i];
                if    ((c=0) and (ssr^.user<>ssr_user) and (_is_ssr_used(ssr^.last)<>-1))
                   or ((c=1) and (ssr^.user=ssr_user)  and (_is_ssr_used(ssr^.last)<>-1))
                 then
                   begin
                     s:= rightchar (ssr^.code,kod_rbs_SSR+4,' ');
                     if ssr^.last=0 then continue;
                     r:= ssr^.last+SSR_NEXT_USE*60;
                     TimeFromSec (r, h,m,e);
                     s:= s + ' -> '+TimeToStr (h,m,':');
                     if ssr^.flight<>nil then
                        begin
                          decodekey_fpl(strpas(ssr^.flight),t,u,d);
                          s:= s+',  '+t;
                          if u<>'' then s:= s+' ('+u+')';
                        end;
                     writeln(ft,s);
                     inc(p);
                   end;
              end;
            if (c=0) and (p>0) then writeln(ft,kbNL);
          end;
        Close(ft);
        m_restore_shape;

       { b) zobrazenie
       }
         if p>0 then _infop (fn,' '+tit_ssr_used_codes+' - '+TimeToStr(hour,min,':')+' ',0,0,true,false,nil);

       { c) upratanie
       }
        DelFile(fn);
       {$ENDIF}
      end;

{ - kontrola spravnosti zadania kodu ssr
}
 function check_filled_ssr (FPLp,FPLn: pointer;
                            ssrp, ssr_,ssr0 : string;
                            var ssr: string;
                            var res: string
                           ): bool;
    var   s: string;
    begin
      check_filled_ssr:= true;
      res:= '';

     { Je zadany kod odpovedaca na predchadzajucom uzemi a spravne ?
     }
      if (ssr0<>'') and (not is_ssr(ssr0,(length(ssr0)=kod_uvd_BN),res)) then Exit;

     { Je kod odpovedaca zadany, a ak ano, tak spravne ?
     }
      if (ssr<>'')  and (not is_ssr(ssr, (length(ssr)=kod_uvd_BN),res))  then Exit;

      {$IFDEF SSR_MANAGEMENT}
       if FPLC_SSR then
          begin
            if (ssr='') then
               begin
                 if    ((FPLp<>nil) and (ssrp<>ssr))      { ak uz bol priradeny }
                    or ((FPLp=nil)  and (ssr_<>eqp_NONE)) { ak nie je uvedeny, ze let ma odpovedac }
                       then
                    begin
                      l4_err (a_SSR,'',0,ask_ssr_none,s);
                      case (Ask2(msgVERIPHY,s,titNo,White,clBUTTON_COLOR,waitASK*18)) of
                        ansAno    : begin
                                      ssr:= assign_ssr (false, res);
                                      if res<>'' then Exit;
                                    end;
                        ansNie    : {nu, choroso} ;
                        else  check_filled_ssr:= false
                      end;
                    end
               end;
          end;

     { Exituje konflikt kodov odpovedacov ?
     }
     {$ENDIF}
    end;


 function form_init_ssr (form: PAForm; ind: int): bool;
    var   res,s: string;
    begin
      form_init_ssr:= false;
      if form=nil then Exit;

      res:= '';
      with form^.itemd^[ind],form^.itemv^[ind] do s:= list_ssr(form^.x0+dx+i*dx_ch,form^.y0+dy+10,false,res);
      if res<>'' then Say2(msgWARNING,res)
      else if cut_(s)<>'' then
         begin
           form_init_ssr:= true;
           form^._in(ind,s);
           form^.write;
         end;
    end;


