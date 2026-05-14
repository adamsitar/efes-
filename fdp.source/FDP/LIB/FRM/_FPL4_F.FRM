 procedure _display_decoded_FPL4 (FPL: PFPL4; check: bool; var res: string; var ires: int);
    var    is  : bool;
    begin
      res:= ''; ires:= -1;
      if FPL=nil then Exit;
      InfoCakaj(msgWAITING,tit_dekoduje_plan);
      {is:= (FPL^.data<>nil) and (FPL^.data^.fdr=nil);
      if is then
         begin
           new_FDR_(nil,FDR);
           ires:= _decode_FDR(FPL^,FDR^,check,res);
         end
      else FDR:= FPL^.data^.fdr;}
      _fpl4_date_all:= true;
      ires:= _decode_FPL4(FPL^,false{check},res);
      InfoCakaj_zatvor;
      if (res<>'') then begin res:= ' ('+res+')'; {Err2(res)} end;
      if (FPL^.data<>nil) and (FPL^.data^.fdr<>nil) and (FPL^.data^.fdr^.fpl<>nil) then
         with FPL^.data^.fdr^ do
           begin
             format_cFPL(fpl);
             p_info_FPLc (fpl,{tit_dekodovany_plan_+}codekey_FPLC(fpl)+res);
           end;
      {if is then disp_FDR_(FDR)}
    end;


 function  formular_FPL4 (_FPLi   : PFPL4;
                          _src    : fdp_src;
                          _stat   : string;
                          _novy   : bool;

                          _tit    : string;
                          {_pos    : byte;}
                          _check  : pointer;
                          _hlpXXX : Pchar
                         ): bool;
    const  f    : Tcentr = (x: initX; y: initY; m: 1);
    var    form : PFPL4form;
           E    : TEvent;
    begin
      if _hlpXXX=nil then _hlpXXX:= hlp_FPL4;
      if _FPLi<>nil then _tit:= _tit+' "'+idn_FPL4(_FPLi)+'"';
      form:= New(PFPL4form,Init
                  (f.x,f.y,f.m, _tit,
                   @form_FPL4,size_FPL4frm,0,
                   _FPLi,_src,_stat,_novy
                  )
                );
      form^.hlpXXX:= hlp_FPL4;
      form^.RunLocalFunc(E,FDPFormLocalMenu);
      formular_FPL4:= form^.corr_res;
      Dispose(form,Done)
    end;


 function  formular_FPL4_ (FPL: PFPL4; tit: string; novy: bool): bool;
    begin
      formular_FPL4_:= formular_FPL4 (FPL,user,'',novy,tit,nil,nil);
    end;
