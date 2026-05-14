var SaveExit : pointer;

procedure done_l4_variables; far;
    begin
      ExitProc:= SaveExit;

      if lst_9bICAO<>nil then Dispose(lst_9bICAO,Done); lst_9bICAO:= nil;
      if lst_9bZZZZ<>nil then Dispose(lst_9bZZZZ,Done); lst_9bZZZZ:= nil;
      if lst_9bTSGA<>nil then Dispose(lst_9bTSGA,Done); lst_9bTSGA:= nil;
      if lst_9bMIL <>nil then Dispose(lst_9bMIL ,Done); lst_9bMIL := nil;
    end;

procedure init_l4_variables;
    var   s,p, fn0,fn1,fn2 : string;
          at : long;
          ft0,ft1,ft2 : text;
          _init,is: bool;
          lst : PList_9b_icao;
          i,k : int;
    begin
      write('Initialize Doc.4444 structures... ');

      SaveExit:= ExitProc;
      ExitProc:= @done_l4_variables;;

     { Nacitanie miestnej hranice vfr vysky
     }
      alt_VFR := read_cfg_word(SYSTEMcfg,cfg_alt_VFR,alt_VFR);
      if read_cfg_str(SYSTEMcfg,cfg_lo_FL,s) then
         lo_FL:= minimum( MtoFL(get_altM(getchar(delchar(s,setCisl_)),
                                getint(s,1,setPism_))
                               ),
                          high(lo_FL)
                        );

     { Nacitanie ciselnikov civilnych, vojenskych a inych typov
     }
      _init:= {$IFDEF FPL4} true {$ELSE} false {$ENDIF};
      lst_9bICAO := New(PList_9b_icao,Init(@fn_9bICAO,'',_init));

     {$IFDEF FPL4}
      lst_9bZZZZ := New(PList_9b_ine, Init(nil,_fn_9bZZZZ,false));
      lst_9bTSGA := New(PList_9b_ine, Init(nil,_fn_9bTSGA,false));
     {$ENDIF}

     { vygenerovanie zoznamu typov do ponuky kratkeho }
      fn0:= {$IFNDEF DEBUG}pathLST+{$ENDIF}_fn_9bICAO+lstExt;
      if FExists(fn0)=0 then
         begin
           at:= _GetFTime(fn0);
           fn1:= pathLST+_fn_9bICAO_;
           fn2:= pathLST+strpas(fn_9b.fn);
           if    (FExists(fn1)<>0) or ((FExists(fn1)=0) and (at>_GetFTime(fn1)))
              or (FExists(fn2)<>0) or ((FExists(fn2)=0) and (at>_GetFTime(fn2)))
           then
             begin
               _init:= (lst_9bICAO=nil);
               if _init then lst:= New(PList_9b_icao,Init(@fn_9bICAO,'',false))
               else lst:= lst_9bICAO;

               Assign(ft0,fn0); Reset  (ft0);
               Assign(ft1,fn1); Rewrite(ft1);
               Assign(ft2,fn2); Rewrite(ft2);

               p:= ''; while not Eof(ft0) do
                 begin
                   ReadLn(ft0,s);
                   s:= ReplChar(s, [#0..#31], ' ');
                   is:= lst^.read_header(s,p);
                   p:= s; s:= cut_(s);
                   if is then continue;
                   if (s[1] in setKomen) or (s='') or (not lst^.is_to_add(s)) then
                      begin
                        writeln(ft1,p);
                        writeln(ft2,cut_3(p,kod_9b+1+kod_9c+2+30))
                      end
                   else begin
                          s:= ' '+inschar(lst^._icao(p),kod_9b+1,' ',1)+inschar(lst^._wtc(p), kod_9c,' ',1) + '   ';
                          p:= lst^._name(p);
                          writeln(ft1,s+p);
                          writeln(ft2,s+cut_3(p,30))
                        end;
                 end;

               close(ft0);
               close(ft1);
               close(ft2);

               if _init then Dispose(lst,Done)
             end;
         end;

     {$IFDEF FPL0}
      _init:= {$IFDEF PROCESS_FPLM} true {$ELSE} false {$ENDIF};
      lst_9bMIL:= New(PList_9b_mil, Init(nil,_fn_9bMIL, _init));
     {$ENDIF}

      writeln('Done.')
    end;
