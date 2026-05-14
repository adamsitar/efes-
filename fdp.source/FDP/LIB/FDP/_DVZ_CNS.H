     const  hlas_DVZ        : bool = true;
            hlas_vsetky_DVZ : bool = true;
            varovanie_DVZ   : bool = {$IFDEF OPL_LET} true {$ELSE} false {$ENDIF};
            posliZiadostDVZ : bool = true;

            PROC_DVZ  : bool = false;        { povolenie spracovania prijatych DVZ }

            {$IFDEF PROCESS_DVZ}
              isDVZ_REQ     : bool = false;  { prisla poziadavka na diverziu, priznak pre vyvola spracovanie }
              isDVZ_REQ_DLA : bool = false;  { ziadost o DVZ odlozena na disk }
            {$ENDIF}

     { Pomocne vypoctove premenne
     }
     const  isDVZ  : bool = false;           { sprava nebola precitana }

