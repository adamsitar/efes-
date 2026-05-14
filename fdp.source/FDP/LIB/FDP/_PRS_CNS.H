      const { Typ priestoru :
            }
             PRIESTOR_LETECKY   = 'L';
             PRIESTOR_STRELNICA = 'S';

             set_R_TYPE : TCharSet = [PRIESTOR_LETECKY,PRIESTOR_STRELNICA];



      const  cfg_PROPOSE_PRS    = 'PROPOSE PRS';

             dT_propose_PRS     : int = 60;
             dT_propose_PRS_lo        = 10;
             dT_propose_PRS_hi        = 1440;


             cfg_DEACTIVE_PRS   = 'DEACTIVE PRS';

             dT_deactive_PRS    : int = 20;  {'}
             dT_deactive_PRS_lo       = 0;   {'}
             dT_deactive_PRS_hi       = 120; {'}

             dT_unactive_PRS    : int = 0;   {'}
             dT_unactive_PRS_lo       = 0;   {'}
             dT_unactive_PRS_hi       = 10;  {'}


      const  poz_est_PRS : Tpozs = [poz_PREACTIVE..poz_PATRAT];


      const  max_PRS_pozn_rm : int   = 0;
             max_PRS_pozn_r_lo       = 0;
             max_PRS_pozn_r_hi       = {$IFDEF PRS_L}3{$ELSE}1{$ENDIF};

             cfg_polomer_PRS    = 'PRS RADIUS';
             polomer_PRS        : byte = 5;



      const  hlas_PRS_plan         : bool = true;
             hlas_PRS_act          : bool = true;

             find_and_process_PRS  : bool = false;
             process_PRS_P         : bool = false;  { povolenie spracovania sprav typu P }


      const  bminiPRS           : bool = true;
             pis_STRIP_PRS      : bool = false;
             miniSTRIP_PRS      : T_strip = {$IFDEF EDD} full_strip {$ELSE} short_strip {$ENDIF};


             PRS_CHECK_VYS_REG  : bool = true;


      const  lst_PRS_kod  = 1;
             lst_PRS_vys  = 3;
