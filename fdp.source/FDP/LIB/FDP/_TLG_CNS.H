    const  TLGcfg = 'TLG'+ext_ini;

    function  get_msg_adr (head: string; var prty,adr: string): bool;


    type   tproc_send_TLG = function (prty,adr,head: string; data: pchars; size: word): string;
           pproc_send_TLG = ^tproc_send_TLG;

    const  p_proc_send_TLG : pproc_send_TLG = nil;

    function _proc_send_TLG (prty,adr,head: string; data: pchars; size: word): string;


    const  tlg_SS : bool = true;         { povolenie zobrazenia telegramov kategorie SS/DD }
           tlg_FF : bool = false;
           tlg_KK : bool = false;

           is_SS  : bool = false;
           is_FF  : bool = false;        { detekovane chyby }
           is_KK  : bool = false;        { chyby ulozene pre dalsie spracovanie }

           tlg_Print    : bool = false;
           tlg_PrintAll : bool = false;

           tlg_SSprint  : bool = false;
           tlg_FFprint  : bool = false;
           tlg_KKprint  : bool = false;


           RUSSIAN_TLG  : bool = true;


    const  size_TLGaftn   = 30;

           i_tlg_prty = 0;
           i_tlg_adr  = 1;
           i_tlg_adrs = 3;

           dy_TLGadr = 45;
