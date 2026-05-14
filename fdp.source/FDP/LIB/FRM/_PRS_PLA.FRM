{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ PRIESTORY                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{ -------------------------
   Inicializacia formulara
  -------------------------
}

  procedure _PRS_init_buttons(form: PFDP_AForm); far;
      var   bt1   : PDialogButton;
            xt,yt : int;
            _kbHot: char;
      begin
        if (form=nil) then Exit;
        form^.Win^.get_btXY(0,4, xt,yt);
        bt1:= New(PDialogButton,Init(form^.Win,xt,yt,
                  GetAltCode(get_HotKey(_kbHot,tit_AIP)), cm_xDATA,
                  tit_AIP, icKey,icText)
                 );
      end;


  {$IFDEF PROCESS_PRS}
    procedure _PRS_handle_event(form: PFDP_AForm; var _Event: TEvent); far;
        var   xt,yt: int;
        begin
          if isCommand(_Event,cm_xDATA) and (form<>nil) then
             begin
               form^.Win^.get_btXY(0,4, xt,yt);
               _list_OPL(xt-170,yt);
               ClearEvent(_Event, form)
             end
        end;
  {$ENDIF}


 { Naplnenie poli
 }
  procedure _init_formular_by_data(form: PFDP_AForm; PRS: PPRS); far;
      var   l,i: int;
            d: TDate;

      begin
        if (form=nil) then Exit;

        if ((not form^.novy) or form^.arch) and (PRS<>nil)
           {and (form^.adr_data<>nil)} then with PRS^ {PPRS(form^.adr_data)^} do
           begin
             form^._in (it_KOD, PRS^.kod);

             form^._in (it_LET, let);
             {$IFNDEF AIRBASE}
              if (let<>'') then form^.itemd^[it_LET].legal:= @setNil;
             {$ENDIF}

             if not form^.arch then form^._in (it_DAT, code_l4_datum(zac));
             form^._in (it_ZAC, code_l4_utc(zac.h,zac.m));
             form^._in (it_KON, code_l4_utc(kon.h,kon.m));
             form^._in (it_VYS1, vys1);
             form^._in (it_VYS2, vys2);
             form^._in (it_TYP, typ);

             form^._in (it_UNT, unt);
             form^.init_pole (it_POZN, PRS^.pozn)
           end;

        if form^.novy or form^.arch or (PRS=nil) {and (form^.adr_data=nil)} then
           begin
             {$IFDEF AIRBASE}
              form^._in (it_LET, this_airbase);
              form^._in (it_UNT, _cairbase(this_airbase));
              form^.itemd^[it_LET].legal:= @setNil;
             {$ENDIF}

             init_date (d, year,month,day);
             {$IFDEF FUA}
               if cas_FUA_24H_EN then
                  begin
                    nextdate  (d.r,d.m,d.d);
                    if hour >= {$IFDEF AMC} cas_AUP_AMC {$ELSE} cas_AUP_AA {$ENDIF} then nextdate (d.r,d.m,d.d)
                  end;
             {$ENDIF}
             form^._in (it_DAT, code_l4_date(d))
           end;

      end;


 { Nastavenie pripustnosti spracovania poloziek
 }
  procedure _init_formular_by_stat(form: PFDP_AForm); far;
      var   PRS,PRSp : PPRS;
      begin
        if (form=nil) then Exit;

        PRS := form^.adr_var;
        PRSp:= form^.adr_data;

        if (not form^.arch) and (PRSp<>nil) and (PRS^.dap.rok<>0) then
           begin
             form^.first_pos:= it_KON;

             form^.itemd^[it_KOD].legal:= @setNil;
             form^.itemd^[it_DAT].legal:= @setNil;
             if not (_is_CHG(PRSp,nil) or _is_ACT(PRSp,nil)) then form^.itemd^[it_UNT].legal:= @setNil;

             if                 _is_CHG(PRSp,nil)
                {$IFDEF AMC} or _is_ACC(PRSp,nil) {$ENDIF}
                             or _is_DEP(PRSp,nil)
                then Exit;

             form^.itemd^[it_ZAC].legal:= @setNil;

             if    _is_BRK(PRSp,nil)
                or _is_CNT(PRSp,nil)
                then
                begin
                  {form^.itemd^[it_KON].legal := @setNil;
                  form^.itemd^[it_VYS1].legal:= @setNil;
                  form^.itemd^[it_VYS2].legal:= @setNil;}
                end;

             {if _is_ARR(PRSp,nil) then Exit}
           end
      end;

  procedure _PRS_init(form: PFDP_AForm; PRS: PPRS); far;
      begin
        _init_formular_by_data(form,PRS);
        _init_formular_by_stat(form)
      end;


  procedure _PRS_image(x0,y0,x1,y1: int); far;
      begin
        _plan_PRS(x0,y0,x1,y1, clBUTTON_COLOR+1,0)
      end;


{ -------------------------
   Spracovanie formulara
  -------------------------
}
  function _PRS_check(form: PFDP_AForm; PRS: PPRS): bool; far;

     var   PRSp   : PPRS;
           res,s  : string;
           ires,i : int;
           r1,r2  : real;

           _stat    : string;
           _command : word;

     label X;

     begin
       _PRS_check:= false;
       ires:= -1; res:= '';

       disp_PRS(PRS);
       form^.get_stat (_stat,_command);
       PRS^.stat:= _stat;

       PRSp:= form^.adr_data;

       with PRS^ do
         begin

          { kod priestoru }
            kod:= _unique_area_code(form^._it(it_KOD));

          { datum a doba platnosti }
            if (not GetDateStr_(zac.rok,zac.mes,zac.den, form^._it(it_DAT),true,[])) then
               begin ires:= l4_err(a_L4,form^._it(it_DAT),it_DAT,err_l4444_date, res); goto X end;

            if not GetTimeStr(zac.h,zac.m,zac.s, form^._it(it_ZAC)) then
               begin ires:= l4_err(a_L4,form^._it(it_ZAC),it_ZAC,err_l4444_time, res); goto X end;

            if not GetTimeStr(kon.h,kon.m,kon.s, form^._it(it_KON)) then
               begin ires:= l4_err(a_L4,form^._it(it_KON),it_KON,err_l4444_time, res); goto X end;

            kon.rok:= zac.rok; kon.mes:= zac.mes; kon.den:= zac.den;
            if   TimeToSec(zac.h,zac.m,zac.s)
               > TimeToSec(kon.h,kon.m,kon.s)
               then with kon do NextDate(rok,mes,den);

          { pouzite vysky }
            PRS^.vys1:= cut_(form^._it(it_VYS1));
            PRS^.vys2:= cut_(form^._it(it_VYS2));

          { uzivatelia; vazba na   _PRS_ID.frm -> nastavenie kluca (r.79)
                                 a _PRS2.inc   -> vyber zo zoznamu (_item_filter_PRS)
          }
            PRS^.let:= cut_(form^._it(it_LET));
            {$IFDEF AIRBASE}
             if (PRS^.let='') then PRS^.let:= this_airbase;
            {$ELSE}
             {if _LKmind(PRS^.let)<0 then
                begin
                  ires:= l4_err(a_FUA,form^._it(it_LET),it_LET,err_FUA_let, res);
                  goto X
                end;}
            {$ENDIF}

            PRS^.unt:= cut_(form^._it(it_UNT));
            if PRS^.unt='' then PRS^.unt:= aftn_airbase (PRS^.let);

            s:= cut_(form^._it(it_TYP));
            if s<>'' then PRS^.typ:= getchar(s)
            else PRS^.typ:= PRIESTOR_LETECKY;

          { poznamka }
            form^.read_pole(it_POZN,PRS^.pozn)
         end;

      {IFDEF FUA}
       if     ((form^.novy) or (PRS<>nil))
           or (     plan_pred_poslednym_schvalenim(PRS)
               and _is_stat(PRS^.stat,cnst_disk+cnst_sended,false)
              )
       then with PRS^ do
              begin
                vys1p:= vys1;
                vys2p:= vys2;
                zacp := zac;
                konp := kon;
              end
       else begin
              PRS^.vys1p:= PRSp^.vys1p;
              PRS^.vys2p:= PRSp^.vys2p;
              PRS^.zacp := PRSp^.zacp;
              PRS^.konp := PRSp^.konp;
            end;
      {ENDIF}


     { kontrola spravnosti vyplnenia a podania planu
     } if not syntax_PRS (PRS,PRSp, res,ires, true,form) then goto X;

       format_PRS(PRS);

       _PRS_check:= true;
       Exit;

       X: if res<>'' then form^.ErrorS(ires, res);
          disp_PRS(PRS)
     end;


{ -------------------------
   Volanie formulara
  -------------------------
}
function  formular_PRS(PRSi: PPRS; _uloz,_arch: bool; _src: fdp_src; _stat,_tit: string): bool;
   const  f     : Tcentr = (x: initX; y: initY; m: 1);
   var    form  : PFDP_AForm;
          PRS   : TPRS;
          E     : TEvent;
          _novy : bool;
          _p_uloz_rpl : pointer;
   begin
     fillchar(PRS,sizeof(PRS),0);

     _novy:= (PRSi=nil) or (_arch);
     if not _novy then
        begin
         { oprava/spracovanie existujuceho planu
         } new_PRS(PRSi,@PRS);
           if _stat<>'' then PRS.stat:= _stat
        end
     else begin
           { podanie noveho planu, EDD ma len evidencnu funkciu
           } PRS.stat:= cnst_active;
             {$IFDEF PRS_PLAN}
               {$IFDEF AMC}
                 if not cas_FUA_24H_EN then PRS.stat:= cnst_acc
                 else
               {$ENDIF}
               PRS.stat:= cnst_disk;
             {$ENDIF}
          end;

     _p_uloz_rpl:= nil;
     {$IFDEF PROCESS_PRS} {$IFDEF OPL} _p_uloz_rpl:= @save_PRS_RPL; {$ENDIF} {$ENDIF}

     form:= New(PFDP_AForm,Init(f.x,f.y, f.m, _tit,
                @frm_PRS,size_frm_PRS,
                0,1, 0,0, 10,91,

                @_PRS_init,@_PRS_image,@_PRS_check, hlp_PRS,
                @PRS, PRSi, @PRS.rec, _src, PRS.stat,

                _novy, sizeof(TPRS), @codekey_PRS,@read_PRS, @existuje_PRS,@zmeneny_PRS,
                nil,_p_uloz_rpl,
                @zarad_PRS,@disp_PRS,

                true,false,true
                {$IFDEF ODOSLI_ULOZ}, _uloz or _novy {$ENDIF}
                {$IFDEF SKRY_OKNA}, false {$ENDIF}
                {$IFDEF STATISTIKA_OPL}, p_info_STA_PRS {$ENDIF}
                ));

     if form^.save_rpl_proc<>nil then
        begin
          form^.RPL_scroll_init (tit_PLANvzor,@get_dbPRS_RPLfn,
                           sizeof(TPRS),@new_PRS,@format_PRS,
                           db_PRS_RIADKOV,@decodeDB_PRS,
                           dxi_PRS, dyi_PRS, @plan_PRS
                          );
        end;

     form^.upcas:= true;
     form^.novy:= _novy;
     form^.arch:= _arch and (PRSi<>nil);

     {_PRS_init(form,PRSi);}

     form^.ins_date:= false;
     form^.copy_back:= true;

     form^.RunLocalFunc(E,nil);
     formular_PRS:= form^.corr_res;
     Dispose(form,Done);

     disp_PRS(@PRS)
   end;
