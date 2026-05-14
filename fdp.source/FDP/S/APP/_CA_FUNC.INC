{IFNDEF FPLM_DISABLED}
{$IFDEF MATCA} {$IFDEF FPL0}

 procedure O_CAMUS._send_message_FPLM(head: Thead_ICAO; zmeneny: bool; var FPLm: DmFPL);
     var   res  : string;
           ires : int;
     begin
       if not (     zmeneny
               and (send_VFR_FPL or (not is_VFR_FPLM(@FPLm)) {(get_altM(FPLm.vys_,FPLm.vys)>alt_VFR)})
              ) then Exit;

      ires:= _icao_head_type(head,res);
      if ires>=0 then
         case msData(ires) of
           msFPL  : send_FPLm (FPLm);
           msCHG  : send_CHGm (FPLm);
           msDLA  : send_DLAm (FPLm);
           msCNL  : send_CNLm (FPLm);

           msDEP,
           msABI,
           msACT  : send_ACTm (FPLm);
         end
       else if head=hd_CLR then send_ACTm (FPLm);
     end;

{$ENDIF} {$ENDIF}
{ENDIF}
