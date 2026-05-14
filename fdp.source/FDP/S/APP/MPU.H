    const  BGUcfg = 'BGU'+ext_ini;

           MAX_RDK_MPU        = 5;
           MAX_ZNAK_MPU       = 70;

           MON_STATUS_REFRESH = 30;


    type   PMPUbuff = ^TMPUbuff;
           TMPUbuff = array [0..MAX_RDK_MPU-1,0..MAX_ZNAK_MPU-1] of char;

    const  lo_MPUadr = 0;    { prva tlaciaren     }
           hi_MPUadr = $F;   { posledna tlaciaren }

           lo_BGUadr = 0;
           hi_BGUadr = 1;

           BGUactive : byte = lo_BGUadr; { aktualne BGU }


    const  BGU_DEL : int = 0;
           BGU_DEL_lo = 0;
           BGU_DEL_hi = 100;

           NOBGU = $FF;


    type   TBGUind = byte;
                                         { pripojene ku bgu, suvisi s menu }
           PMPUrec = ^TMPUrec;
           TMPUrec = record
             bgu  : TBGUind;
             buff : TMPUbuff;

             st, bus0,bus1,bus2 : byte;  { stav a popisne registre }

             {$IFDEF STATUS}
               bt : PFButton
             {$ENDIF}
           end;

           TMPUs = array[lo_MPUadr..hi_MPUadr] of TMPUrec;
           PMPUs = ^TMPUs;

           {$IFDEF STATUS} {UKBB_PRN}
    const    cbtBGU0   = 'BGU~0~';
             cbtBGU1   = 'BGU~1~';

    var      btBGUi : array[lo_BGUadr..hi_BGUadr] of PFButton;
           {$ENDIF}


    type   P_BGU = ^O_BGU;
           O_BGU  = object(TObject)

            { archivacne premenne }
             path  : string[80];
             ext   : string[4];
             p_scroll_data : PPOScrollStream;

             constructor   Init(_Owner: PObject);
             destructor    Done; virtual;

             procedure   HandleEvent(var _Event: TEvent); virtual;

             function    streamFN: string; virtual;
             procedure   writeln_pkt  (data: string; prompt, message: string; cl: byte; is_utc,is_nl: bool);
           end;


    const  DEV_BGU : P_BGU = nil;
           MPUs    : PMPUs = nil;          { potom to stiahnut dole }
