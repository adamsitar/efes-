     { zoznam vsetkych spracovavanych statisickych typov
     }
      const  max_StaFDP = 50;
      type   TStaFDP    = array[0..max_StaFDP] of POStaFDP;

      {const poc_StaFDP : word = 0;}
      {var   StaFDP  : TStaFDP;}


      type   POStaAPP = ^OStaAPP;
             OStaAPP  = object {(TObject)}

               cfg_STA,kod_STA  : string[12];
               najdlhsi_nazov   : byte; { najdlsi nazov polozky }

               hod_vypoctu_sta  : byte;
               posledna_sta     : TDate;

               StaFDP     : TStaFDP;
               poc_StaFDP : word;

               tvorba_samostatnych_modulov_statistiky: bool;
               tvorba_spolocneho_modulu_statistiky: bool;


               constructor Init(_cfg_STA,_kod_STA: string);
               destructor  Done; virtual;

               procedure   read_cfg(_cfg_STA: string); virtual;
               procedure   read_kod_STA;
               procedure   save_kod_STA;

               function    inicializuj_modul(p_OStaFDP: POStaFDP): POStaFDP;
               procedure   inicializacia_modulov; virtual;
               procedure   inicializacia_dennych_zaznamov (nacitaj,uloz: bool);

               function    _tit (key: string; sirka: int): string;
               function    _cis (val: int; sirka: int): string;

               procedure   vytvor_tabulku_statistiku_za_ (date: TDate; externy: bool;
                                                          spolocny_subor: string; datove_subory: PPChars
                                                         ); virtual;
               function    vytvor_statistiku_za_den     (date: TDate; uzatvor,externy: bool): string; virtual;
               procedure   uzatvor_statistiku_za_den    (date: TDate); virtual;
               function    vytvor_statistiku_za_mesiac  (date: TDate; uzatvor,externy: bool): string; virtual;
               procedure   uzatvor_statistiku_za_mesiac (date: TDate); virtual;


               procedure   zobraz_subor_statistiky_      (fn,title: string; den,uzatvorena: bool); virtual;
               procedure   zobraz_priebeznu_statistiku_  (den: bool); virtual;
               procedure   zobraz_uzatvorenu_statistiku_ (den: bool); virtual;

               procedure   check;

               function    povolena_aktualizacia_statistiky (date: TDate): bool;
               function    aktualizacia_uzatvorenej_statistiky (date: TDate): bool;
               procedure   aktualizuj_uzatvorenu_statistiku (date: TDate);
             end;
