    type   PRegionSize = ^TRegionSize;
           TRegionSize = record  { pre najdenie najvacsej plochy v skupine }
             Region: TRegion;
             Size  : long;
           end;


          { pomocne funkcia - na zabranenie kruhovych referencii }
    type   hlp_proc = procedure (help: pchar);
           dlg_proc = function  (_title: string; _text,_textp: pointer; _dx,_dy: int; _beep: pointer; _wait: long): bool;


          { interna fcia prostredia }
    const  p_err  : TBFunc_s = nil;
           p_dlg  : dlg_proc = nil;
           p_hlp  : hlp_proc = nil;


    const { kbCentre  = kbAltEnter; -> je v Edit, doriesit presun do stredu }
           clSHADOW     = 16;
           WRITELN_FLOW : bool = true;

