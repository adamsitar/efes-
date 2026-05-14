{ kontrola spravnosti
}
 function _check_ssr_cfg (ssrs: string; uvd: bool): bool;
    var   res, s, s1,s2 : string;
          i,p : int;
          bres : bool;
    begin
      _check_ssr_cfg:= false;
      res:='';
      for i:= 1 to getstritems(ssrs,[',',' ']) do
        begin
           s:= getstr(ssrs,i,[',',' ']);
           p:= getstritems(s,['-']);
           res:= '';
           if not (p in[1,2]) then res:= 'Invalid format of the allowed codes range ('+s+').'
           else if p=1 then bres:= is_ssr(cut_(s),uvd,res)
           else bres:= is_ssr(getstr(s,1,['-']),uvd,res) and is_ssr(getstr(s,2,['-']),uvd,res);
           if res<>'' then RunError(SSR_CFG+' -> '+res)
         end;
      _check_ssr_cfg:= res='';
    end;


 function check_ssr_cfg (var _err: bool): bool;
    var   s: string;
          bres : bool;
    begin
      check_ssr_cfg:= false;
      bres:= true;

      {$IFDEF ATCA}
       s:= cut_(_read_cfg(SSR_CFG,cfg_SSR_CODE,true));
       if s<>'' then bres:= _check_ssr_cfg(s,false)
       else MessError(SSR_CFG+' -> There is missing an allowed ssr codes range.',true,_err);
      {$ENDIF}

      {$IFDEF MATCA}
       s:= cut_(_read_cfg(SSR_CFG,cfg_SSR_MIL,true));
       if s<>'' then bres:= _check_ssr_cfg(s,false) and bres
       else MessError(SSR_CFG+' -> There is missing an allowed military ssr codes range.',true,_err);
      {$ENDIF}

      {$IFDEF BN_MANAGEMENT}
       {$IFDEF ATCA}
        s:= cut_(_read_cfg(SSR_CFG,cfg_BOARD_NUMBER,true));
        if s<>'' then bres:= _check_ssr_cfg(s,true) and bres
        else MessError(SSR_CFG+' -> There is missing an allowed board numbers range.',true,_err);
       {$ENDIF}

       {$IFDEF MATCA}
        s:= cut_(_read_cfg(SSR_CFG,cfg_BOARD_NUMBER_MIL,true));
        if s<>'' then bres:= _check_ssr_cfg(s,true) and bres
        else MessError(SSR_CFG+' -> There is missing an allowed military board numbers range.',true,_err);
       {$ENDIF}
      {$ENDIF}

      check_ssr_cfg:= bres
    end;


{ inicializacia databazy
  - len vtedy, ak konfiguracny subor je mladsi ako db subor pouzivanych kodov
  - postupne nacitanie kodov
  - ak pre nacitavany kod existuje zaznam v aktualnej databaze, nacitanie jeho parametrov
  -
}
 procedure init_ssr_db_cfg (fndb,fntmp : string;     { povodny a pracovny subor db-ssr }
                            ssrs : string;
                            uvd,mil : bool
                           );

     procedure uloz (_code : string;
                     _fir  : string;
                     _user : t_ssr_user
                    );
         var   ssr : t_ssr_record;
         begin
           fillchar(ssr,sizeof(ssr),0);
           ssr.code:= cut_(_code);
           if DB_najdi(@ssr,fndb,db_SSR_RIADKOV,@decodeDB_SSR,@codekey_SSR,true,@disp_SSR,'')>-1 then
              begin
                { nacitaju sa hodnoty last a flight
                }
              end;
           {ssr.fir := _fir;}
           ssr.user:= _user;
           DB_oprav(@ssr,fntmp,db_SSR_RIADKOV,@codeDB_SSR,@codekey_SSR,nil,dbattr_SSR);
           disp_SSR(@ssr);
         end;

     var   res, s, s1,s2 : string;
           i,j, p, i1,i2,k1,k2,c, sirka : int;

           _fir  : string;
           _user : t_ssr_user;

     begin

       if uvd then
          begin
            if mil then _user:= uvd_mil
            else _user:= uvd_atca;
            sirka:= kod_uvd_BN
          end
       else
            begin
              if mil then _user:= ssr_mil
              else _user:= ssr_atca;
              sirka:= kod_rbs_SSR
            end;

       _fir:= FIR_adr;

       for j:= 1 to getstritems(ssrs,[',',' ']) do
         begin
           s:= getstr(ssrs,j,[',',' ']);
           p:= getstritems(s,['-']);
           res:= '';

           if p=1 then uloz(cut_(s), _fir,_user)
           else if p=2 then
                begin
                  s1:= cut_(getstr(s,1,['-']));
                  s2:= cut_(getstr(s,2,['-']));

                  val(s1,i1,k1);
                  val(s2,i2,k2);

                  if uvd then
                     begin
                       if i2<i1 then begin c:= i1; i2:= i1; c:= i2 end;
                       for i:= i1 to i2 do uloz(cstr(i,sirka),_fir,_user);
                     end
                  else begin
                        i1:= _X_10(i1,8); i2:= _X_10(i2,8);
                        if i2<i1 then begin c:= i1; i2:= i1; c:= i2 end;
                        for i:= i1 to i2 do uloz(cstr(_10_X(i,8),sirka),_fir,_user);
                      end;
                end
         end
     end;


{ opatovne ulozi do novej db medzitym pouzite kody,
  aby neboli ani oni opatovne pouzite...
}
 procedure init_ssr_db_notcfg (fndb,fntmp : string);
     var   ssrp : t_ssr_record;
           ssrn : t_ssr_record;
           DBp,DBn : PDB;
           i,j,k : int;
     begin
       fillchar(ssrp,sizeof(ssrp),0);
       fillchar(ssrn,sizeof(ssrn),0);

       DBp:= New(PDB, Init(fndb, false,db_SSR_RIADKOV,nil,@decodeDB_SSR,@codekey_SSR,nil,dbattr_SSR));
       DBn:= New(PDB, Init(fntmp,false,db_SSR_RIADKOV,@codeDB_SSR,@decodeDB_SSR,@codekey_SSR,nil,dbattr_SSR));
       for i:= 0 to DBp^.poloziek-1 do
         begin
           if (DBp^.citaj(i,@ssrp)) and (_is_ssr_used(ssrp.last)>-1) then
              begin
                ssrn.code:= ssrp.code;
                if DBn^.najdi(@ssrn,false,nil)=-1 then
                   begin
                     {ssrp.fir  := '';}
                     ssrp.user := ssr_user;
                     DBn^.zapis(@ssrp,-1,false)
                   end;
                disp_SSR(@ssrn);
              end;
           disp_SSR(@ssrp);
         end;
       Dispose(DBn,Done);
       Dispose(DBp,Done);
       disp_SSR(@ssrn);
       disp_SSR(@ssrp);
     end;


{ vytvorenie db povolenych a pouzitych kodov
}
 procedure initialize_ssr_db;
     var   s, fndb,fntmp: string;
           _err: bool;
     begin
       _err:= false;
       ssr_next_use:= Limit(read_cfg_word(SSR_CFG,cfg_SSR_NEXT_USE,SSR_NEXT_USE), SSR_NEXT_USE_lo,SSR_NEXT_USE_hi, 0);

       fndb  := fn_db__ssr;
       fntmp := fn_db__ssr_+delchar(extTMP,['.']);

       {$IFDEF ATCA}
        s:= cut_(_read_cfg(SSR_CFG,cfg_SSR_CODE,true));
        if s<>'' then init_ssr_db_cfg(fndb,fntmp, s,false,false);
       {$ENDIF}

       {$IFDEF MATCA}
        s:= cut_(_read_cfg(SSR_CFG,cfg_SSR_MIL,true));
        if s<>'' then init_ssr_db_cfg(fndb,fntmp, s,false,true);
       {$ENDIF}

       {$IFDEF BN_MANAGEMENT}
        {$IFDEF ATCA}
         s:= cut_(_read_cfg(SSR_CFG,cfg_BOARD_NUMBER,true));
         if s<>'' then init_ssr_db_cfg(fndb,fntmp, s,true,false);
        {$ENDIF}

        {$IFDEF MATCA}
         s:= cut_(_read_cfg(SSR_CFG,cfg_BOARD_NUMBER_MIL,true));
         if s<>'' then init_ssr_db_cfg(fndb,fntmp, s,true,true);
        {$ENDIF}
       {$ENDIF}

       init_ssr_db_notcfg(fndb,fntmp);

       del(fndb);
       renfile(fntmp,fndb);  { ... su v jednom adresari }
       if _err then writeln;
     end;


 procedure initialize_ssr_act;
     var   db  : PDB;
           i   : int;
           ssr : t_ssr_record;
     begin
       SSRs:= New(PO_SSRs,Init);
       fillchar(ssr,sizeof(ssr),0);

       db:= New(PDB,Init(fn_db__ssr,false,db_SSR_RIADKOV,nil,@decodeDB_SSR,@codekey_SSR,nil,dbattr_SSR));
       i:= 0;
       while (i<db^.poloziek) and (SSRs^.top<max_ssr_records) do
         begin
         if db^.citaj(i,@ssr) then
            begin
              if    (ssr.user<>ssr_user)
                 or (_is_ssr_used (ssr.last)<>-1)
                    then SSRs^.add(@ssr);
              disp_SSR(@ssr);
            end;
         inc(i);
       end;
       Dispose(db,Done);
     end;

 procedure release_ssr_act;
     var   i: int;
     begin
       if SSRs<>nil then
          begin
            dispose(SSRs,Done);
            SSRs:= nil;
          end;
     end;



 var  SaveExit  : pointer;
      SaveMainD : TProc;


 procedure check_ssr_act;
     const m : int = 60;
     var   i : int;
     begin
       if @SaveMainD<>nil then SaveMainD;
       if m=min then Exit;
       m:= min;

       i:= 0;
       while i<=SSRs^.top do
         if (SSRs^.ssr_a^[i]^.last=0) or (_is_ssr_used (SSRs^.ssr_a^[i]^.last)<>-1) then inc(i)
         else ssr_zrus (SSRs^.ssr_a^[i]^.code)
     end;


 procedure done_SSR; far;
     begin
       release_ssr_act;
       ExitProc:= SaveExit
     end;

 procedure init_ssr;
     var   _err: bool;
     begin
       write('Initialize ssr database... ');
       _err:= false;

       SaveExit:= ExitProc;
       ExitProc:= @done_ssr;

       if (Exists(SSR_CFG)=0) then
          begin
            if (Exists(fn_db__ssr)<>0) or (_GetFTime(fn_db__ssr)<=_GetFTime(SSR_CFG)) then
               if check_ssr_cfg(_err) then initialize_ssr_db
               else MessError(SSR_CFG+' -> SSR codes table was not updated !',true,_err);
          end
       else MessError('There was not found configuration file '+SSR_CFG+' of ssr codes range.',true,_err);

       initialize_ssr_act;

       SaveMainD:= ACheckProcessesD;
       ACheckProcessesD:= check_ssr_act;

       if _err then writeln;
       writeln('Done.')
     end;
