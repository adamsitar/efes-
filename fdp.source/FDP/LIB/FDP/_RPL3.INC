{ -----------
   RPL
  -----------
}
 function  _FRM_RPL(RPL: PRPL): bool;
     var   s: string;
     begin
       if RPL<>nil then s:= tit_fpl_copy else s:= tit_rpl_plan;
       formular_RPL_ (RPL,s,true);
       _FRM_RPL:= false
     end;



{ -----------
   CHG
  -----------
}
{ Oprava lubovolneho planovaneho
}
 function  _CHG_RPL(RPL: PRPL): bool; far;
     begin
       _CHG_RPL:= false;
       if RPL<>nil then formular_RPL_ (RPL,tit_rpl_chg,false);
     end;

 procedure CHG_RPLi;
     begin
       _spracuj_RPL (true,true,nil,nil,
                     _TBFunc_p,@_CHG_RPL,nil,
                     tit_rpl_chg,hlpmnuRPL
                    );
     end;


{ -----------
   CNL
  -----------
}
(*
 function  _CNL_RPL(RPL: PRPL): bool; far;
     var   s  : string;
     begin
       _CNL_RPL:= false;
       if Ask2(msgVERIPHY,ask_RPL_cnl+' '+RPL^._7a+icao_NXT+RPL^._13a+'?',
               titNO,White,clBUTTON_COLOR,waitASK*18
              ) <> ansAno then Exit;
       {zarad_RPL (RPL,hd_CNL,true,user);}
       DB_zrus (RPL,
                get_RPLfn(@RPL^.rpl),
                db_RPLF_RIADKOV,@codeDB_RPLF,@codekey_RPLF,
                @dbchg_RPLF, dbattr_RPLF
               );
       info_RPL(RPL,'RPL of '+codekey_RPL(RPL)+' was deleted.');
     end;

 procedure CNL_RPLi;
     begin
       _spracuj_RPL (true,true,nil,
                     _TBFunc_p,@_CNL_RPL,nil,
                     tit_rpl_cnl,hlpmnuRPL
                    );
     end;
*)

{ -----------
   BRK
  -----------
}
 function _is_BRK(RPL: PRPL; p: pointer): bool; far;
    begin
      _is_BRK:= RPL^.val<>rpl_off
    end;

 function  _BRK_RPL(RPL: PRPL): bool; far;
     var   res: string;
           ires: int;
     begin
       _BRK_RPL:= false;
       RPL^.val:= rpl_off;
       _zarad_RPL (RPL,cm_zarad_RPL,true,user,res,ires);
       info_RPL(RPL,RPL^._7a+'('+RPL^._13a+') - '+tit_rpl_deactived);
     end;

 procedure BRK_RPLi;
     begin
       _spracuj_RPL (true,false {! vid 1.7},nil,@_is_BRK,
                     _TBFunc_p,@_BRK_RPL, nil,
                     tit_rpl_brk,hlpmnuRPL
                    );
     end;


{ -----------
   CNT
  -----------
}
 function _is_CNT(RPL: PRPL; p: pointer): bool; far;
    begin
      _is_CNT:= RPL^.val=rpl_off
    end;

 function  _CNT_RPL(RPL: PRPL): bool; far;
     var   res: string;
           ires: int;
     begin
       _CNT_RPL:= false;
       RPL^.val:= rpl_off;
       _zarad_RPL (RPL,cm_zarad_RPL,true,user,res,ires);
       info_RPL(RPL,RPL^._7a+'('+RPL^._13a+') - '+tit_rpl_reactived);
     end;

 procedure CNT_RPLi;
     begin
       _spracuj_RPL (true,false {! vid 1.7},nil,@_is_CNT,
                     _TBFunc_p,@_CNT_RPL,nil,
                     tit_rpl_cnt,hlpmnuRPL
                    );
     end;



{ -----------
   FPL
  -----------
}
 function  _FPL_RPL(RPL: PRPL): bool; far;
     var   FPL  : DFPL4;
           d    : TDate;
           res  : string;
           ires : int;
     begin
       _FPL_RPL:= false;
       fillchar (FPL,sizeof(FPL),0);
       code_RPL_to_FPL4_ (RPL^,FPL,true);
       {init_date(d,year,month,day);
        update_date_FPL4 (RPL.fpl,lastRPL.d);
       _zarad_FPL4 (@RPL.fpl,cm_spracuj_FPL4_RPL,hd_FPL,true,rpl_);}
       formular_FPL4_ (@FPL,tit_rpl_fpl,true);
       disp_FPL4(@FPL)
     end;

 procedure FPL_RPLi;
     begin
       _spracuj_RPL (true,true,nil,nil,
                     _TBFunc_p,@_FPL_RPL,nil,
                     tit_rpl_fpl,hlpmnuRPL
                    );
     end;


{ --------------
   Aktualizacia
  --------------
}
 procedure finish_RPLs;
    begin
      decode_txt_rpl('',true,false,false);
    end;


 procedure add_RPLs;
    var    res: string;
    begin
     {$IFNDEF DEBUG}
      l4_err(a_RPL,'',0,tit_rpl_extend,res);
      if (res<>'') and (Ask2(msgVERIPHY,res,titNO,White,clBUTTON_COLOR,waitASK*18) <> ansAno) then Exit;
     {$ENDIF}
      res:= read_txt_rpls;
      if res<>'' then decode_txt_rpl(res,false,false,false);
    end;


 procedure replace_RPLs(oprava: bool);
    var    res: string;
    begin
     if not oprava then
        begin
         {$IFNDEF DEBUG}
          l4_err(a_RPL,'',0,tit_rpl_replace,res);
          if (res<>'') and (Ask2(msgVERIPHY,res,titNO,White,clBUTTON_COLOR,waitASK*18) <> ansAno) then Exit;
         {$ENDIF}
        end;
      res:= read_txt_rpls;
      if res<>'' then decode_txt_rpl(res,false,oprava,not oprava);
    end;


 procedure restore_RPLs;
    var    res: string;
    begin
      if GetNmbOfFiles (pathRPL+'*.'+extRPP) = 0 then
         begin
           l4_err(a_RPL,'',0,tit_rpl_no_backup,res);
           if res<>'' then Say2(msgSORRY,res);
           Exit
         end;

      l4_err(a_RPL,'',0,ask_rpl_restore,res);
      if (res<>'') and (Ask2(msgVERIPHY,res,titNO,White,clBUTTON_COLOR,waitASK*18) <> ansAno) then Exit;

      del(pathRPL+'*.'+extRPL);
      _bck_rpls(extRPP,extRPL);

      l4_err(a_RPL,'',0,tit_rpl_restored,res);
      if (res<>'') then Say2(msgINFO,res)
    end;
