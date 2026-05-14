    const  fplNOPL  = 'NOPL';      { uz neplati }
           fplVFR   = 'VFR';

           fplOTHER = 'OTHERS';
           fplWEST  = 'WEST';
           fplEAST  = 'EAST';

           fplMIL   = 'MIL';
           fplTSA   = 'TSA';
           fplFPL   = 'FPL';

           fplDEP   = 'DEP';
           fplARR   = 'ARR';


          {$IFDEF TABLET_ZAM}
            {$IFDEF SLOVAK}    fplZAM = 'ZAM';   {$ENDIF}
            {$IFDEF CZECH}     fplZAM = 'ZAM';   {$ENDIF}
            {$IFDEF ENGLISH}   fplZAM = 'ACT';   {$ENDIF}
          {$ENDIF}

          {$IFDEF TABLET_PRS}  fplPRS = hd_R+icao_NXT+hd_TSA;
                               {fplTSA = hd_TSA;}
          {$ENDIF}


    type  TSpecGroups = record
            is_dep, is_arr,
            is_west,is_east,
            is_tsa               : bool
          end;