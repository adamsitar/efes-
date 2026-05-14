{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ ZAMESTNANIE LETISKA                                      €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{ -------------------------
   Inicializacia formulara
  -------------------------
}

 procedure _ZAM_init_buttons(form: PFDP_AForm); far;
     var   bt1   : PDialogButton;
           xt,yt : int;
           _kbHot: char;
     begin
       form^.Win^.get_btXY(0,4, xt,yt);
       bt1:= New(PDialogButton,Init(form^.Win,xt,yt,
                 GetAltCode(get_HotKey(_kbHot,tit_AIP)), cm_xDATA,
                 tit_AIP, icKey,icText)
                );
     end;

 {$IFDEF PROCESS_ZAM}
   procedure _ZAM_handle_event(form: PFDP_AForm; var _Event: TEvent); far;
       var   xt,yt: int;
       begin
         if isCommand(_Event,cm_xDATA) then
            begin
              form^.Win^.get_btXY(0,4, xt,yt);
              _list_OPL(xt-170,yt);
              ClearEvent(_Event, form)
            end
       end;
 {$ENDIF}


 procedure _ZAM_init(form: PFDP_AForm; ZAM: PZAM); far;
     var   p: PZAM;
     begin
       {if FPL<>nil then FPLi:= FPL
       else if (form^.parameter<>nil) then FPLi:= PDmFPL(form^.parameter)
       else FPLi:= nil;}

      { Naplnenie poli
      }
       if form^.adr_data<>nil then with PZAM(form^.adr_data)^ do
         begin
           form^._in(i_kod,kod);
           if (PFDP_AForm(form)^.arch) then form^._in(i_dat,' ')
           else form^._in(i_dat,code_l4_date_(zac.rok,zac.mes,zac.den));
           form^._in(i_zac,TimeToStr(zac.h,zac.m, ':'));
           form^._in(i_kon,TimeToStr(kon.h,kon.m, ':'));
           form^._in(i_prav,prav);
           form^._in(i_vys,vys);
           form^._in(i_vu,vu);
           form^._in(i_ulohy,strpas(ulohy));
           form^._in(i_typy,strpas(typy));
           form^._in(i_planov,inschar(cstr(planov,1),strlen(form^.itemd^[i_planov].item),' ',0));
           form^._in(i_letov,cstr(letov,1));
           form^.init_pole (i_pozn0, pozn);
         end
       else begin
              {$IFDEF AIRBASE}
                if cut_(form^._it(i_kod))='' then form^._in(i_kod,this_airbase);
              {$ENDIF}
              {form^._in(i_zac,TimeToStr(hour,min, ':'))}
            end;

      { Nastavenie spracovania poli
      }
       if (not form^.arch) and (form^.adr_data<>nil) and (ZAM^.dap.rok<>0) then
          begin
            form^.itemd^[i_kod].legal:= @setNil;
            form^.itemd^[i_dat].legal:= @setNil
          end
       else if cut_(form^._it(i_dat))='' then
               begin
                 form^._in(i_dat,code_l4_date_(year,month,day));
               end;
     end;

 procedure _ZAM_image(x0,y0,x1,y1: int); far;
     var   bp: bool; xlm,ylm: int;
     begin
       m_off (bp, xlm,ylm);
       _plan_ZAM(x0,y0,x1,y1, clBUTTON_COLOR+1,0);
       m_on (bp, xlm,ylm);
     end;


{ -------------------------
   Spracovanie formulara
  -------------------------
}

{ Kontrola spravnosti zadania planu
}
 function _check_ZAM(ZAM: PZAM; var res: string): int;
    var   ires, i : int;
          v: word; v_: char;
          s: string;
          e: bool;

    label X;
    begin
      res:= ''; ires:= 0;
      with ZAM^ do
        begin

         { kod letiska }
          if cut_(kod)='' then ires:= l4_err(a_OPL,'',i_kod,err_OPL_chyba_letisko, res);
         {$IFDEF AIRBASE}
          if not _plan_pre_pracovisko(ZAM) then ires:= l4_err(a_OPL,kod,i_kod,err_OPL_neopravnene_letisko, res);
         {$ENDIF}
          if res<>'' then goto X;

         { planovana doba zamestnania }


         { P/V }
          if (not _in_list(prav, @fn_8a,[], 1,nil)) then
             begin
               l4_err(a_FPLM,prav,i_prav,err_FPLM_8a,res);
               goto X;
             end;

         { vyska : decode_l4_vys (vys, v,v_) }
          if not decode_l4_vyss (vys, v,v_, nil) then
             begin
               ires:= l4_err(a_L4,vys,i_vys,err_l4444_vyska_chyba,res);
               goto X
             end;

         { VU }
          if (not _in_list(VU, @fnPrevM,[], 1,nil)) then
             begin
               ires:= l4_err(a_OPL,vys,i_vu,err_OPL_neznamy_prev,res);
               goto X
             end;

         { ulohy }
          i:= 0; s:= getPstr(ulohy,i+1,[icao_NXIT]);
          while (s<>'') do
            begin
              if (not _in_list(s, @fnUlohyM,[], 1,nil)) then
                 begin
                   ires:= l4_err(a_OPL,s,i_ulohy,err_OPL_neznamy_task,res);
                   goto X
                 end;
              inc(i);
              s:= getPstr(ulohy,i+1,[icao_NXIT])
            end;
          if i=0 then
             begin
               ires:= l4_err(a_OPL,'',i_ulohy,err_OPL_chyba_task,res);
               goto X
             end;

         { typy }
          i:= 0; s:= getPstr(typy,i+1,[icao_NXIT]);
          while (s<>'') do
            begin
              if (length(s)>2) and (s[1] in setCisl) and (s[2] in setCisl) then s:= copy(s,length(s)-1,2);
              if (not _in_list(s, @fnUlohyM,[], 1,nil)) then
                 begin
                   ires:= l4_err(a_OPL,s,i_typy,err_OPL_neznamy_typ,res);
                   goto X
                 end;
              inc(i);
              s:= getPstr(ulohy,i+1,[icao_NXIT])
            end;
          if i=0 then
             begin
               ires:= l4_err(a_OPL,'',i_typy,err_OPL_neuvedeny_typ,res);
               goto X
             end;

        end;

      X: _check_ZAM:= ires
    end;


 function _ZAM_check(form: PFDP_AForm; ZAM: PZAM): bool; far;
    var   ires  : int;
          res,s : string;
          datum : bool;
          date  : TDate;

    label X;

    begin
      disp_ZAM(ZAM);
      datum:= false; ires:= -1; res:= '';

      ZAM^.kod:= form^._it_i(i_kod);

      if not GetTimeStr(ZAM^.zac.h,ZAM^.zac.m,ZAM^.zac.s,form^._it(i_zac)) then
         begin
           l4_err(a_L4,'',i_zac,err_l4444_time, res);
           goto X
         end;
      if not GetTimeStr(ZAM^.kon.h,ZAM^.kon.m,ZAM^.kon.s,form^._it(i_kon)) then
         begin
           l4_err(a_L4,'',i_kon,err_l4444_time, res);
           goto X
         end;

      ZAM^.prav:= getchar(form^._it_i(i_prav));
      ZAM^.vys:= form^._it_i(i_vys);
      ZAM^.vu:= form^._it_i(i_vu);

      ZAM^.ulohy:= strpasnew(form^._it_i(i_ulohy));
      ZAM^.typy:= strpasnew(form^._it_i(i_typy));
      ZAM^.planov:= s_int(form^._it_i(i_planov));
      ZAM^.letov:= s_int(form^._it_i(i_letov));

      form^.read_pole(i_pozn0,ZAM^.pozn);

      ires:= _check_ZAM(ZAM,res);
      if res<>'' then goto X;

      {$IFDEF FDP_OPL}
        {datum:= form^.decode_DATUM (i_pozn0, ZAM^.zac, res,ires);}
        s:= cut_(form^._it_i(i_dat));
        if (s<>'') then
           if decode_l4_date (s,date) then form^.is_date:= true
           else begin
                  ires:= l4_err(a_L4,'',i_dat,err_l4444_date, res);
                  goto X
                end;
        datum_init (ZAM^.zac, date.d,date.m,date.r, ZAM^.zac.h,ZAM^.zac.m,ZAM^.zac.s);
      {$ELSE}
        datum:= assign_DATE (zac.rok,zac.mes,zac.den, zac.h,zac.m,zac.s);
      {$ENDIF}

      if (ZAM^.dap.rok=0) then datum_init(ZAM^.dap, day,month,year, hour,min,sec);
      if (ZAM^.src='') then
         begin
           ZAM^.src:= _mairbase(ZAM^.kod);
           {$IFDEF AIRBASE}
            ZAM^.src:= this_airbase;
           {$ELSE}
            {let:= nadriadene_letisko(kod);}
           {$ENDIF}
         end;

      _ZAM_check:= true;
      Exit;

      X: _ZAM_check:= false;
         form^.ErrorS(ires, res);
         disp_ZAM(ZAM);
         if datum then fillchar(ZAM^.zac,sizeof(ZAM^.zac),0)
    end;


 function _ZAM_date(ZAM: PZAM; p: pointer; date: PDate): bool; far;
    begin
    { zadanie datumu, ak nebol vo formulari
    }
      if date<>nil then datum_init (ZAM^.zac, date^.d,date^.m,date^.r, ZAM^.zac.h,ZAM^.zac.m,ZAM^.zac.s);

    { urcenie datumu ukoncenia, pocita sa na max 24h, ale nezadava sa
    }
      datum_init (ZAM^.kon, ZAM^.zac.den,ZAM^.zac.mes,ZAM^.zac.rok, ZAM^.kon.h,ZAM^.kon.m,ZAM^.kon.s);
      if   DTtoSec(ZAM^.kon.rok,ZAM^.kon.mes,ZAM^.kon.den, ZAM^.kon.h,ZAM^.kon.m,ZAM^.kon.s)
         < DTtoSec(ZAM^.zac.rok,ZAM^.zac.mes,ZAM^.zac.den, ZAM^.zac.h,ZAM^.zac.m,ZAM^.zac.s)
         then NextDate(ZAM^.kon.rok,ZAM^.kon.mes,ZAM^.kon.den);

    { nepotrebujem kontrolovat na ziaden konflikt planu;
      mozno, ci nie je vyhlasene QGO...
    }
      _ZAM_date:= true
    end;


{ -------------------------
   Volanie formulara
  -------------------------
}
  function  formular_ZAM(ZAMi: PZAM; _uloz,_arch: bool; _stat,_tit: string): bool;

     const  f    : Tcentr = (x: initX; y: initY; m: 1);
     var    form : PFDP_AForm;
            ZAM  : TZAM;
            s    : string;
            i    : int;
            E    : TEvent;
            _p_date,_p_uloz_rpl : pointer;
            _novy: bool;

     begin
       fillchar(ZAM,sizeof(ZAM),0);

       _p_date:= @_ZAM_date;
       _novy:= (ZAMi=nil) or (_arch);
       if not _novy then
          begin
            new_ZAM(ZAMi,@ZAM);
            if _stat<>'' then ZAM.stat:= _stat
          end
       else begin
             {if (ZAMi<>nil) and _arch then new_ZAM(ZAMi,@ZAM);}

            { kluc sa urci pri zadani datumu platnosti
            }
              {$IFDEF PROCESS_ZAM} ZAM.stat:= cnst_disk;
              {$ELSE}              ZAM.stat:= cnst_active;
              {$ENDIF}

            { Polozky pre urcenie kluca, smu sa naplnit len v pripade uplne
              novej premennej v check alebo tu... :
            }
             {$IFDEF AIRBASE} ZAM.kod:= this_airbase;
             {$ENDIF}
              fillchar(ZAM.zac, sizeof(ZAM.zac),0); {!}
              fillchar(ZAM.dap, sizeof(ZAM.dap),0); {!}
            end;

       _p_uloz_rpl:= nil;
       {$IFDEF PROCESS_FPLM} {$IFDEF OPL} _p_uloz_rpl:= @save_ZAM_RPL; {$ENDIF} {$ENDIF}

       form:= New(PFDP_AForm,Init(f.x,f.y, f.m, _tit,
                  @frm_ZAM,SIZE_frm_ZAM,
                  0,1, 0,0, 0,0,

                  @_ZAM_init,@_ZAM_image,@_ZAM_check, hlp_ZAM,
                  @ZAM, ZAMi, @ZAM.rec, letvis, ZAM.stat,

                  _novy, sizeof(TZAM),@codekey_ZAM,@read_ZAM,nil,nil,
                  _p_date, _p_uloz_rpl,
                  @zarad_ZAM, @disp_ZAM,

                  true,false,true
                  {$IFDEF ODOSLI_ULOZ}, _uloz or _novy {$ENDIF}
                  {$IFDEF SKRY_OKNA}, false {$ENDIF}
                  {$IFDEF STATISTIKA_OPL}, nil{p_info_STA_ZAM} {$ENDIF}
                  ));

       if form^.save_rpl_proc<>nil then
          begin
            form^.RPL_scroll_init (tit_PLANvzor,@get_dbZAM_RPLfn,
                             sizeof(TZAM),@new_ZAM,@format_ZAM,
                             db_ZAM_RIADKOV,@decodeDB_ZAM,
                             dx_ZAM, dy_ZAM, @plan_ZAM
                            );
          end;

       form^.upcas:= true;
       form^.p_init_buttons:= @_ZAM_init_buttons;
       form^.arch:= _arch and (ZAMi<>nil);
       {$IFDEF PROCESS_ZAM} form^.p_handle_event:= @_ZAM_handle_event; {$ENDIF}

       form^.RunLocalFunc(E,nil);
       formular_ZAM:= form^.corr_res;
       Dispose(form,Done);

       disp_ZAM(@ZAM)
     end;
