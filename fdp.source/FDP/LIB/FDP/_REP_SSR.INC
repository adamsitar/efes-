{$IFDEF SSR_MANAGEMENT}

 function Beep99B: bool; far;
    var   b: bool;
    begin
     {$IFNDEF NO_SOUND} b:= ZVUK; ZVUK:= true; {$ENDIF}
      Beep99B:= BeepVB(nil,nil, GetTicks, waitINFO*18, waitBEEP);
     {$IFNDEF NO_SOUND} ZVUK:= b {$ENDIF}
    end;


 procedure _rep_SSR_ERR_REC (const rep: TREP);
     var   title, error,code,flight,res : string;
           ires : int;
           fpl : PFPLC;
           pd  : PPrompt;
           ed  : PError;
           ev  : TEvent;
           ans : TAnswer;

     begin
       error:= init_str (rep.data,rep.dlz);
       decodeERR_SSR (error, ires,code,flight,res);

       title:= msgWARNING;
       if rep.ods<>'' then title:= title+msgOD+rep.ods;
       title:= title + ' - ' + code;

       fpl:= find_FPLCa(flight);

       if    ((ires<>err_ssr_is_used) and (ires<>err_ssr_time_out)
          or (fpl=nil) or (p_form_FPLC=nil)) then
          begin
            res:= res+NULL;
            ed:= New(PError,Init(title,@res[1]));
            ed^.hlpXXX:= hlp_SSR_ERROR;
            ed^.btOK^.new_title_key(titPOTVRD,false);
            ed^.loops:= -1{waitINFO*18};
            ed^.beep1:= @BeepErr;
            {$IFDEF BACKUP}
              if SERVERstatus then
                 begin
                   ed^.beep1:= nil;
                   ed^.loops:= waitINFO*18;
                 end;
            {$ENDIF}
            ed^.Run(ev);
            Dispose(ed,Done);
            Exit
          end;

       pd:= New(PPrompt,Init(cmOK,title,res,'',white,red,-1{waitINFO*18}));
       pd^.hlpXXX:= hlp_SSR_ERROR;
       pd^.btOK^.new_title_key(titSPRACUJ,false);
       pd^.btCancel^.new_title_key(titPOTVRD,false);
       pd^.beep:= @Beep99B;
       {$IFDEF BACKUP}
         if SERVERstatus then
            begin
              pd^.beep:= nil;
              pd^.loops:= waitINFO*18;
            end;
       {$ENDIF}
       pd^.Run(ev);
       ans:= pd^.Result(ev);
       Dispose(pd,Done);

       if (ans=ansAno) and (p_form_FPLC<>nil) then
          begin
            pos_frm_FPLC:= i_7b_FDR;
            TBFunc_ps(p_form_FPLC)(fpl,res);
            {NETsend_msg (rep.ods,spr_SSR_COR,@err[1],length(err),false,net_flag_SEND);}
          end;
     end;


 procedure _rep_SSR_ERR_COR (const rep: TREP);
     begin
     end;


 procedure process_report_SSR (const REP: TREP);
     begin
       case REP.kod of

         0  : ;

         spr_SSR_ERR : _rep_SSR_ERR_REC (REP);

         spr_SSR_COR : _rep_SSR_ERR_COR (REP);
       end;
     end;

{$ENDIF}
