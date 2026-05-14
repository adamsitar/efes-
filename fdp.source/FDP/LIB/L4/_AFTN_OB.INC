 procedure O_AFTN.HandleEvent(var _Event: TEvent);

     {procedure TLG_XX_en(var tlg: bool; bt: PSButton);
         begin
           tlg:= true;
           bt^.Draw
         end;}

     begin
       inherited HandleEvent(_Event);

       if (_Event.What<>evNothing) then
         case _Event.Command of

           cm_TLG_SSpended : read_tlg(tlgSS); { TLG_XX_en(tlg_SS,btSS); }
           cm_TLG_FFpended : read_tlg(tlgFF); { TLG_XX_en(tlg_FF,btFF); }
           cm_TLG_KKpended : read_tlg(tlgKK); { TLG_XX_en(tlg_KK,btKK); }

           cmAFTN_2LINE    : Say2(msgWARNING,'Switched to backup AFTN line.');
           cmAFTN_ERLINE   : Say2(msgWARNING,'AFTN connection timeout.');

           cmPREHLAD_AFTN  : prehlad_AFTN;

           {$IFDEF ARCHIVE_AFTN}
            cmARCHIV_AFTN  : zalohuj_archiv(path_AFTN,'*.*',msgBCK,msgCOPY,nil);
           {$ENDIF}

           else Exit
         end
       else Exit;

       ClearEvent(_Event)
     end;
