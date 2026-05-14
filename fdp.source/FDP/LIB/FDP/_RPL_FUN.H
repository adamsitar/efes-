   { -----------------
      zakladnie fcie
     -----------------
   }
     procedure new_RPL   (RPL1,RPL2: PRPL); far;
     procedure disp_RPL  (RPL: PRPL); far;

     procedure new_RPLF  (RPL1,RPL2: PRPLF); far;
     procedure disp_RPLF (RPL: PRPLF); far;

     function  eq_RPL    (RPL1, RPL2: PRPL): bool; far;

   { ------------
      kodovanie
     ------------
   }
     procedure code_RPL_to_FPL4_ (const RPL: DRPL; var FPL: DFPL4; code_15: bool);


   { ------------
      vypocty
     ------------
   }
     procedure update_RPL_to_FPL4 (const RPL: DRPLF; var FPL: DFPL4);


   { ------------
      read/save
     ------------
   }



   { ------------
      zobrazenie
     ------------
   }
    const  dxm_RPL  = 562;
           dxf_RPL  = 562;
           dym_RPL  =  44;
           dyf_RPL  = 178;



   { ------------
      NET
     ------------
   }



   { ------------
      PLAN
     ------------
   }

     procedure _spracuj_RPL (_find_data,_process_data : bool;

                             _data_filter  : Pkey_fpl;
                             _filter       : pointer;

                             _handler_type : TScrollAct_handler_type;
                             _handler      : pointer;
                             _handler_par  : pointer;

                             _title  : string;
                             _hlpXXX : Pchar
                            );



    {$IFDEF PROCESS_RPL}

     { externe definovany editor
     }
      type  func_rpl_form   = function (RPL: PRPL; tit: string; novy: bool): bool;
            p_func_rpl_form = ^func_rpl_form;

      const p_form_RPL : p_func_rpl_form = nil;

    {$ENDIF}


     { fcia pre zaradenie prijateho/spracovaneho
       planu RPL
     }
      function _zarad_RPLF (RPL: PRPLF;
                            check_par: word; _send: bool; _src: fdp_src;
                            var res: string; var ires: int
                           ): bool;

      function _zarad_RPL  (RPL: PRPL;
                            check_par: word; _send: bool; _src: fdp_src;
                            var res: string; var ires: int
                           ): bool;

     { externa fcia pre zaradenie planu FPL4 podla RPL
     }
      const  p_zarad_RPL_FPL4 : pproc_p = nil;


      procedure  check_RPL;
