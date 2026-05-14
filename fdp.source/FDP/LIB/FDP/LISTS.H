     const  cisExt     = '.lst';
            abcExt     = '.abc';

     const
           { ICAO FPL }
            fn_5a      : TListDesc = (fn:'_5a'; lo:0;poz:0; p:nil);

            fn_7b      : TListDesc = (fn:'_7b'+firExt ; lo:0;poz:0; p:nil);
            fn_7bM     : TListDesc = (fn:'_7b-mil'; lo:0;poz:0; p:nil);
            fn_7xM     : TListDesc = (fn:'_7x-mil'; lo:0;poz:0; p:nil);

            fn_8a      : TListDesc = (fn:'_8a'; lo:0;poz:0; p:nil);
            fn_8b      : TListDesc = (fn:'_8b'; lo:0;poz:0; p:nil);
            fn_8bM     : TListDesc = (fn:'_8b-mil'; lo:0;poz:0; p:nil);

            _fn_9bICAO_ = '_9b'+ext_wrk;
            fn_9b      : TListDesc = (fn:'_9b_'+ext_wrk; lo:0;poz:0; p:nil);

            _fn_9bICAO  =  {$IFDEF DEBUG} pathLST_+'_9b-test'; { aby vosli do pamate }
                           {$ELSE}        '_9b-icao';
                           {$ENDIF}
            fn_9bICAO  : TListDesc = (fn:_fn_9bICAO; lo:0;poz:0; p:nil);
            _fn_9bTSGA             = '_9b-tsga';
            _fn_9bZZZZ             = '_9b-zzzz';
            _fn_9bMIL              = '_9b-mil';
            fn_9bMIL   : TListDesc = (fn:_fn_9bMIL; lo:0;poz:0; p:nil);
            fn_9c      : TListDesc = (fn:'_9c'; lo:0;poz:0; p:nil);

            fn_10a     : TListDesc = (fn:'_10a'; lo:0;poz:0; p:nil);
            fn_10b     : TListDesc = (fn:'_10b'; lo:0;poz:0; p:nil);
            fn_10bM    : TListDesc = (fn:'_10b-mil'; lo:0;poz:0; p:nil);

            fn_13a     : TListDesc = (fn:'_13a'+firExt; lo:0;poz:0; p:nil);
            fn_13aM    : TListDesc = (fn:'_13a-mil'+firExt; lo:0;poz:0; p:nil);
            fn_16aM    : TListDesc = (fn:'_16a-mil'+firExt; lo:0;poz:0; p:nil);

            fn_15a     : TListDesc = (fn:'_15a'; lo:0;poz:0; p:nil);
            fn_15      : TListDesc = (fn:'_15'; lo:0;poz:0; p:nil);
            fn_15M     : TListDesc = (fn:'_15-mil'; lo:0;poz:0; p:nil);

            fn_18      : TListDesc = (fn:'_18'; lo:0;poz:0; p:nil);
            fn_18M     : TListDesc = (fn:'_18-mil'; lo:0;poz:0; p:nil);

            fn_19      : TListDesc = (fn:'_19'; lo:0;poz:0; p:nil);
            fn_20      : TListDesc = (fn:'_20'; lo:0;poz:0; p:nil);


           { ICAO RPL }
            fn_rplJ    : TListDesc = (fn:'rpl-_j'; lo:0;poz:0; p:nil);
            fn_aftnADR : TListDesc = (fn:'_AFTN'+firExt; lo:0;poz:0; p:nil);
            fn_aftnTLG : TListDesc = (fn:'_TLG'; lo:0;poz:0; p:nil);

           { NOTAM }
            fnDate     : TListDesc = (fn:'_DATE'; lo:0;poz:0; p:nil);

           { rych, vyska }
            fn15a      : TListDesc = (fn:'_15a'; lo:0;poz:0; p:nil);
            fnAlt_     : TListDesc = (fn:'FL_';  lo:0;poz:0; p:nil);
            fnAlt_ab   : TListDesc = (fn:'FL_';  lo:0;poz:0; p:nil);

            fnAlt      : TListDesc = (fn:'FL'  +firExt; lo:0;poz:0; p:nil);
            fnAlt_L    : TListDesc = (fn:'FL_L'+firExt; lo:0;poz:0; p:nil);
            fnAlt_H    : TListDesc = (fn:'FL_H'+firExt; lo:0;poz:0; p:nil);
            {fnAlt_S_FL : TListDesc = (fn:'FL_S'+firExt; lo:0;poz:0; p:nil);}

           { OPL }
           {fnFPL_     : TListDesc = (fn:'FPL_'; lo:0;poz:0; p:nil);}

            fnMin      : TListDesc = (fn:'MIN'+cisExt; lo:0;poz:0; p:nil);

            fnUlohyM   : TListDesc = (fn:'TASK-mil'+cisExt; lo:0;poz:0; p:nil);

            fnP        : TListDesc = (fn:FIR+'P'  + firExt; lo:0;poz:0; p:nil);
            fnR        : TListDesc = (fn:FIR+'R'  + firExt; lo:0;poz:0; p:nil);
            fnTSA      : TListDesc = (fn:FIR+'TSA'+ firExt; lo:0;poz:0; p:nil);
            fnAREA     : TListDesc = (fn:'AREA'+ext_wrk; lo:0;poz:0; p:nil);
            fnR_TYPE   : TListDesc = (fn:'R-TYPE'; lo:0;poz:0; p:nil);

            {$IFDEF FLI_COORDINATION}
             fnFLI      : TListDesc = (fn:'FLI'+ firExt; lo:0;poz:0; p:nil);
            {$ENDIF}

            fnTQGO     : TListDesc = (fn:'TQGO'; lo:0;poz:0; p:nil);
            fnMQGO     : TListDesc = (fn:'MQGO'; lo:0;poz:0; p:nil);

            fnMapStred : TListDesc = (fn:'map'; lo:0;poz:0; p:nil);

            fnSLNKO    = 'SUN'+firExt;


           { Docasne listingy }
     const  fnIDN : TListDesc = (fn:'idn'+ext_wrk; lo:0;poz:0; p:nil);
            fnSPR : TListDesc = (fn:'adr'+ext_wrk; lo:0;poz:0; p:nil);