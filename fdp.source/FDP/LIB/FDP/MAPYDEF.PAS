(*-------------------------------------------------------------------*)
(* LETVIS LIS - MAPY 1.0  Dynamicky obojsmerny zoznam,  aj Fill      *)
(* (c) Ales Kosice 1993   Igor                                       *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}


unit MapyDef;


interface

    uses   TypeDef,
           Ovr,
           DOS, IO, {$I unit_gr.h}, dyn_zoz,
           Menus,
           FIR_def, ZemSur, Bod_def;


    const  {$IFDEF DEBUG}
             PathToMaps  = '\FDPÿDATA\MAPS\'+firDir;
           {$ELSE}
             PathToMAPs  = '.\MAPS\';
           {$ENDIF}

           cfg_MAP       = 'maps';

           MAPS_CFG      = cfg_MAP+ext_kod;
           ext_usm       = '.usm';
           APP_MAPS_CFG  = exe+ext_usm;
           USER_MAPS_CFG : string = exe+ext_usm;


    const  MAPcfg   = 'maps'+ext_kod;
           MAPscfg  = 'maps'+ext_ini;

           setMAP   = [':'];
           setZAC   =  '*';


    const  cfg_MAPY_SYMBOLY   = 'SYMBOL FILE';
           cfg_NASTAV_SYMBOLY = 'SYMBOL MENU';

           cfg_MARKED_SYM     = 'DRAW MARKED SYMBOLS';
           MARKED_SYM: bool   = false;

           MAPsBACKGROUND = 0;
           MAPsCl         = clGRa;
           SYMsCl         = clGR9;


    const  map_FIR         = FIR;
           map_CTR         = 'CTR';
           map_TMA         = 'TMA';
           map_RESTRICTED  = FIR+'R';
           map_PROHIBITED  = FIR+'P';
           map_AREA        = FIR+'A';
           map_SYM         = 'SYM';


    const  MAPS_DATA: bool = false;



implementation


end.