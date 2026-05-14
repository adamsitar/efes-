      const  dt_propose_ZAM    : int = 60;
             dt_propose_ZAM_lo : int = 10;
             dT_propose_ZAM_hi : int = 1440;

             cfg_PROPOSE_ZAM  = 'PROPOSE ZAM';

             dT_unactive_ZAM    : int = 0;   {'}
             dT_unactive_ZAM_lo : int = 0;   {'}
             dT_unactive_ZAM_hi : int = 10;  {'}

             dT_deactive_ZAM    : int = 20;  {'}
             dT_deactive_ZAM_lo : int = 0;   {'}
             dT_deactive_ZAM_hi : int = 120; {'}

             cfg_DEACTIVE_ZAM = 'DEACTIVE ZAM';


      const  poz_est_ZAM : Tpozs  = [poz_PREACTIVE..poz_PATRAT];


      const  cfg_polomer_ZAM    = 'ZAM RADIUS';
             polomer_ZAM : byte = 5;


      const  hlas_ZAM       : bool = true;
             varovanie_ZAM  : bool = {$IFDEF OPL_SAR} true {$ELSE} false {$ENDIF};


      const  bminiZAM       : bool = true;
             pis_STRIP_ZAM  : bool = false;
             miniSTRIP_ZAM  : T_strip = {$IFDEF EDD} full_strip {$ELSE} short_strip {$ENDIF};


      { Pomocne vypoctove premenne
      }
      const  isZAM  : bool = false;              { sprava nebola precitana }
