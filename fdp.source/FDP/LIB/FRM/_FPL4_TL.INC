{$IFDEF TLG}

{ -----------
   ARR
  -----------
}

 function  _ALR_FPL4(FPL: PFPL4): bool;
    begin
      _ALR_FPL4:= false;
      {if FPL<>nil then} formular_ALR(FPL)
    end;

 procedure ALR_FPL4i;
     begin
       _spracuj_FPL (true,true,false,true, true,false,
                     nil,nil,
                     nil,ms_ICAOplan+ms_ICAOact,'',
                     _TBFunc_p,@_ALR_FPL4,
                     tit_fpl_alr,hlpmnuFPL4
                    );
     end;


{ -----------
   RCF
  -----------
}

 function  _RCF_FPL4(FPL: PFPL4): bool;
    begin
      _RCF_FPL4:= false;
      {if FPL<>nil then} formular_RCF(FPL)
    end;

 procedure RCF_FPL4i;
     begin
       _spracuj_FPL (true,true,false,true, true,false,
                     nil,nil,
                     nil,ms_ICAOplan+ms_ICAOact,'',
                     _TBFunc_p,@_RCF_FPL4,
                     tit_fpl_rcf,hlpmnuFPL4
                    );
     end;


{$IFDEF TSGA}

 { -----------
    ANP
   -----------
 }
  function  _ANP_FPL4(FPL: PFPL4): bool;
      begin
        _ANP_FPL4:= false;
        {if FPL<>nil then} formular_ANP(FPL)
      end;

  procedure ANP_FPL4i;
      begin
        _spracuj_FPL (true,true,false,true, true,false,
                      nil,nil,
                      nil,ms_ICAOact,'',
                      _TBFunc_p,@_ANP_FPL4,
                      tit_fpl_anp,hlpmnuFPL4
                     );
      end;


 { -----------
    FLA
   -----------
 }
  function  _FLA_FPL4(FPL: PFPL4): bool;
     begin
       _FLA_FPL4:= false;
       {if FPL<>nil then} formular_FLA(FPL)
     end;

  procedure FLA_FPL4i;
      begin
        _spracuj_FPL (true,true,false,true, true,false,
                      nil,nil,
                      nil,ms_ICAOact,'',
                      _TBFunc_p,@_FLA_FPL4,
                      tit_fpl_fla,hlpmnuFPL4
                     );
      end;


(* { -----------
    FLI
   -----------
 }
  function  _FLI_FPL4(FPL: PFPL4): bool;
     begin
       _FLI_FPL4:= false;
       {
       if FPL<>nil then formular_FLI(FPL)
       }
     end;

  procedure FLI_FPL4i;
      begin
        _spracuj_FPL (true,true,false, true,false,
                      ms_ICAOact,'',nil,
                      _TBFunc_p,@_FLI_FPL4,nil,
                      tit_fpl_fli,hlpmnuFPL4
                     );
      end;
*)
{$ENDIF}

{$ENDIF}