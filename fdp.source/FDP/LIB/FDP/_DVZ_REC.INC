{ --------------
   Prijaty plan
  --------------
}

 (*
 function _accept_DVZ(ods: TNETadr; DVZ: PDVZ): bool; far;
    begin
     {$IFDEF FDP_OPL}
      {$IFDEF AIRBASE} _accept_DVZ:= (ods = adr_airbase(DVZ^.let)) or (ods = adr_airbase(DVZ^.let_))
      {$ELSE}          _accept_DVZ:= true
      {$ENDIF}
      {$ELSE}          _accept_DVZ:= true
     {$ENDIF}
    end;
 *)

 procedure _pkt_DVZ(DVZ: PDVZ);
     var   rep,_rep_,stt1 : string;
           DVZp : TDVZ;
           p : pchar;

     label X;

     begin
       stt1:= DVZ^.stat;
       {DVZ^.stat:= delchar(DVZ^.stat,[cnst_chg,cnst_read]);}

       if (read_DVZ(codekey_DVZ(DVZ),@DVZp)>-1) and (not chg_DVZ(DVZ,@DVZp)) then goto X;

       {$IFDEF DVZ_REPORT}
        rep:= ''; _rep_:= rep_pre+DVZ^.pre+rep_na+DVZ^.kym;

        { ------------------------------------------------------
          Sprava o diverzii drzanej pre dane letisko,
          (vyhodnocovana tak, aby sa nepobili priznaky)
        }
        if                  {(pos(cnst_read,stt1)<>0)
                            ((stt1p<>DVZ^.stat) or chg_DVZ(@DVZp,DVZ))}
           {$IFDEF AIRBASE}
                  hlas_vsetky_DVZ
              or (   (_plan_pre(DVZ^.pre))
                  or (     hlas_DVZ
                       and (not (_plan_pre(DVZ^.kym)))
                     )
                 )
           {$ELSE}
                 hlas_DVZ
           {$ENDIF}
           then
             begin
               if (DVZp.stat<>DVZ^.stat) then
                  begin

                  { vystraha pred zruseniem :
                  } if (pos(cnst_dvz_alr,stt1)<>0) then
                       begin
                         if (pos(cnst_dvz_acn,stt1)<>0) then rep:= rep_dvz_acn+_rep_+'.'
                         else rep:= rep_dvz_alr+_rep_+'.'
                       end

                    else if (pos(cnst_dvz_alr,stt1)=0) and (pos(cnst_dvz_alr,DVZp.stat)<>0) then rep:= rep_dvz_cln+_rep_+'.'

                  { povolenie aktivovania, nevyuziva sa :
                  } else if pos(cnst_active,stt1)<>0 then
                       begin
                         {if (stt1=cnst_active) and (pos(cnst_dvz_var,stt1p)<>0) then
                            rep:= rep_dvz_alr+_rep_+' '+rep_dvz_cnl+'.'
                         else} begin
                                _rep_:= rep_dvz_act+' '+DVZ^.kym+rep_od+DVZ^.pre+' ';
                                if pos(cnst_dvz_zad,stt1)<>0 then _rep_:= rep+rep_dvz_act_dec+'.'
                                else if pos(cnst_dvz_zaa,stt1)<>0 then _rep_:= rep+rep_dvz_act_acc+'.'
                              end
                       end

                  { zrusenie diverzie :
                  } else if stt1=cnst_cnl then rep:= rep_dvz_pre+_rep_+' '+rep_dvz_cnl+'.'

                  { schvalenie ziadosti o dvz :
                  } else if pos(cnst_dvz_acc,stt1)<>0 then rep:= rep_dvz_req+_rep_+' '+rep_dvz_req_acc+'.'

                  { zamietnutie -//-          :
                  } else if pos(cnst_dvz_dec,stt1)<>0 then rep:= rep_dvz_req+_rep_+' '+rep_dvz_req_dec+'.'
                  end

               else if (DVZ^.stat<>'') then rep:= rep_dvz_chg+_rep_+'.'
             end;

       { ----------------------------------------------
         Sprava o diverzii pre zabezpecujuce letisko ?
       }
        if                      {((stt1p<>DVZ^.stat) or chg_DVZ(@DVZp,DVZ))}
           {$IFDEF AIRBASE}
                  hlas_vsetky_DVZ
              or (   _plan_pre(DVZ^.kym)
                  or (    hlas_DVZ
                      and (not _plan_pre(DVZ^.pre))
                     )
                 )
           {$ELSE}
              hlas_DVZ
           {$ENDIF}
           then
             begin
               if (DVZp.stat<>DVZ^.stat) then
                  begin
                    if      pos(cnst_dvz_zac,stt1)<>0 then rep:= {rep_dvz_pre+' '+DVZ^.pre+' '+rep_dvz_pre_act+'.'}
                                                                 rep_dvz_act+' '+DVZ^.kym+rep_od+DVZ^.pre+' '
                    else if pos(cnst_dvz_kon,stt1)<>0 then rep:= rep_dvz_pre+' '+DVZ^.pre+' '+rep_dvz_pre_end+'.'
                    else if pos(cnst_cnl,stt1)<>0     then rep:= rep_dvz_pre+' '+DVZ^.pre+' '+rep_dvz_cnl+'.'
                  end
               else if (DVZ^.stat<>'') then rep:= rep_dvz_chg+_rep_+'.'
             end;

        if (rep<>'') and (reports_FDP<>nil) then
           begin
             p:= code_l4_DVZ_(DVZ,'');
             reports_FDP^.save_rep
                (spr_DVZ,'',codekey_DVZ(DVZ),
                 rep, strlen(p),pchars(p)
                );
             strdispose(p)
           end;

            {IFDEF STATUS
             else if is_this_date(DVZ^.date, year,month,day) then btDVZ^.show
            ENDIF}

           {$IFDEF MACC}
            (*if is_this_date(DVZ^.date, year,month,day) then {$IFDEF STATUS} btDVZ^.show {$ENDIF}*)
           {$ENDIF}

       {$ENDIF}

       zarad_DVZ (DVZ,DVZ^.stat,true,letvis);

       X: disp_DVZ(@DVZp)
     end;


{ --------------------
   Prijate potvrdenie
  --------------------
}
 procedure _ack_DVZ(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   DVZ : TDVZ;
     begin
       if read_DVZ(key, @DVZ)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy(rec,DVZ.rec);
               end
            else begin
                   rec_pkt(nd,DVZ.rec,is_ack);
                 end;
            save_DVZ(@DVZ);
            disp_DVZ(@DVZ)
          end
     end;


{ --------------------
   Inicializacia uzla
  --------------------
}
