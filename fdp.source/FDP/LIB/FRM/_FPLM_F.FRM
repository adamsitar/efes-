{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TmFPLform - vojensky FPL                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{ v pouziti funkcie disp_... vo formulari mam zatial bordel,
  nie je to jednotne pre vsetky typy dat
}

 function  formular_mFPL(FPLi    : PDmFPL;
                         _src    : fdp_src;
                         _stat   : string;
                         _novy   : bool;

                         _tit    : string;
                         _pos    : byte;
                         _check  : pointer;
                         _hlpXXX : Pchar
                        ): bool;

     const  f : Tcentr = (x: initX; y: initY; m: 1);

     var    form : PmFPLform;
            E : TEvent;
            i : int;

            FPL : DmFPL;

            _req  : bool;
            _uloz : bool;

            _p_date,_p_uloz_rpl : pointer;

     begin
      formular_mFPL:= false;

      {$IFNDEF DEBUG} {$IFNDEF MATCA}
       if not ENABLE_FPLM then Exit;
      {$ENDIF} {$ENDIF}
      {$IFDEF DISABLED_ETO_FPLM}
       Exit;
      {$ELSE}

       new_mFPL(FPLi,@FPL);

       _req :=     (_stat<>cnst_stat_DEP)
               and _is_stat_us (FPL.let, FPL.stat,cnst_prop+cnst_req_approved);

       _novy:=         (_novy)
                    or (   (FPLi=nil)
                        or (FPLi^.stat=cnst_stat_arr)
                        or (pos(cnst_cnl,FPLi^.stat)<>0)
                       );
       _uloz:= __is_stat(FPL.stat,cnst_disk);
       _p_date:= nil;

       if _novy then
          begin
          { podanie noveho planu
          }
            FPL.let:= '';
            fillchar(FPL.date,sizeof(FPL.date),0); {!}
            fillchar(FPL.dap,sizeof(FPL.dap),0);   {!}
            _uloz:= true;
            _p_date:= @mFPL_date;

            if (_stat<>'') then FPL.stat:= _stat
            else begin
                   FPL.stat:= cnst_active;
                   {$IFDEF FPLM_PLAN}
                     FPL.stat:= cnst_sended;
                     {$IFDEF OPL} {$IFNDEF MACC}
                       FPL.stat:= cnst_disk;
                     {$ENDIF} {$ENDIF}
                   {$ENDIF}
                 end
          end
       else begin
            { spracovanie planu
            } if (_stat<>'') then FPL.stat:= _stat;

            { Oprava pripomienky
            } if _req then
                 begin
                  {$IFDEF FDP_OPL}
                   {$IFDEF MACC} FPL.stat:= cnst_acc;
                   {$ELSE}       FPL.stat:= cnst_prop;
                   {$ENDIF}
                  {$ELSE}
                    FPL.stat:= cnst_stat_DEP;
                  {$ENDIF}
                 end;
            end;

       _p_uloz_rpl:= nil;
       {$IFDEF PROCESS_FPLM} {$IFDEF OPL} _p_uloz_rpl:= @uloz_mFPL_RPL; {$ENDIF} {$ENDIF}

       form:= New(PmFPLform,Init(f.x,f.y, f.m, _tit,
                  @mFPL_init, _check, _pos,

                  @FPL, FPLi, @FPL.rec, _src, FPL.stat, _novy,
                  _p_date,_p_uloz_rpl, @zarad_FPLm,

                  _hlpXXX {$IFDEF ODOSLI_ULOZ}, _uloz or (pos(cnst_disk,FPL.stat)<>0) {$ENDIF}
                  )
                 );

       form^.RunLocalFunc(E,nil);
       formular_mFPL:=     form^.corr_res
                        {$IFDEF AIRBASE}
                         and (not (    ((FPLi<>nil) and (cut_(FPLi^.idn)=''))
                                   and (cut_(FPL.idn) ='')
                                   and (eq_KRL(@FPLi,@FPL))
                                  )
                             )
                        {$ENDIF}
                       ;
       Dispose(form,Done);

       disp_mFPL(@FPL);
      {$ENDIF}
     end;


 function formular_mFPL_(p: pointer; tit: string): bool;
    var   res : bool;
    begin
      res:= formular_mFPL(p,letvis,PDmFPL(p)^.stat,false, tit,i_15M, nil,hlp_mFPL);
      formular_mFPL_:=  res
    end;



 procedure _strip_FPLM (x0,y0,x1,y1: int; FPL: PFPLM); far;
     var   strip: T_strip;
           b : bool;
     begin
       strip:= miniSTRIP_mFPL; miniSTRIP_mFPL:= full_strip;
       b:= pis_STRIP_mFPL_15body; pis_STRIP_mFPL_15body:= true;
       strip_mFPL(FPL,x0,y0,false);
       pis_STRIP_mFPL_15body:= b;
       miniSTRIP_mFPL:= strip;
     end;

 procedure _display_decoded_FPLM (FPL: PFPLM; check: bool; var res: string; var ires: int);
     var   FPM : DFPLM;
     begin
       res:= ''; ires:= -1;
       if FPL=nil then Exit;

       InfoCakaj(msgWAITING,tit_dekoduje_plan);
       new_mFPL(FPL,@FPM);
       res:= format_mFPL_trat (@FPM);
       InfoCakaj_zatvor;
       if (FPM.trat_<>nil) then Info(codekey_FPLM(@FPM), @_strip_FPLM, @FPM, dx_sc_strip(full_strip)+50,dy_sc_strip+10,nil,0)
       else Say2(codekey_FPLM(@FPM),res);
       disp_mFPL(@FPM);
     end;


