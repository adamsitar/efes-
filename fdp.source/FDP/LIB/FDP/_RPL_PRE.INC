 procedure prehlad_RPL;
     begin
       _spracuj_RPL (true,false,nil,nil,
                     _TBFunc_vEp2,@handle_plan_RPL,nil,
                     tit_RPL_PREHLAD,
                     hlp_PREHLAD_RPL
                    );
     end;