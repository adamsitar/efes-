      const  extSTA  = 'STA'; { adresar }
             extSTE  = 'CSV'; { typ externeho subora }
             extSTD  = 'STD'; { uzatvorene textove subory dennych statistickych suborov    }
             extSTM  = 'STM'; { uzatvorene textove subory mesacnych statistickych suborov  }

             extSTAdata = 'ð';   { predpona pred ext denneho "sta" subora podla typu udajov (99-01-19.~PM)
                                   pre zaznam priebehu spracovania jednotlivych planov
                                 }
             extSTAsuma = 'ä';   {  -//- so sledovanymi udajmi sumarne    :  99-01-19.%PM;
                                   zapis_sumarneho_zaznamu pre jednolive typy udajov
                                 }
             extSTAwork = '÷';   { predpona ext priebeznych a pracovnych suborov *.@T[D][M]
                                   pracovne vypoctove subory dennych a mesacnych statistik,
                                   az kym nie su uzatvorene
                                 }

             path_STA     = path_A+extSTA+'\';
             pathARCH_STA = path_ARCHIVES+extSTA+'\';

             kodSTA       = {path_STA+}extSTA+ext_kod;




      const  STA_PRIEBEZNE    : bool = false; { priebezne/periodicke vyhodnotenie statistiky }
             STA_TEST         : bool = false; { plany s identifikaciou 'TEST' nevyhodnocovat }


      const  staArchDays      : word = 365+31;
             staArchMonths    : word = 12+1;



     { Pri vzajomne sa vylucujuich sa stavoch plati posledny platny stav,
       plan sa zapisuje do statistiky na den realizacie
     }
      type   PStaPlan = ^TStaPlan;
             TStaPlan = record
               {odoslany     : bool;
               prijaty       : bool;
               schvaleny     : bool;
               zamietnuty    : bool;}
               planovany     : bool;
               realizovany   : bool;
             end;

      type   PStaSum = ^TStaSum;
             TStaSum = record
               {odoslanych   : word;
               prijatych     : word;
               schvalenych   : word;
               zamietnutych  : word;}
               planovanych   : word;
               realizovanych : word;
             end;


      function  sta_to_str(var sta; sta_size: byte): string;
      procedure str_to_sta(s: string; var sta; sta_size: byte);

      function  get_STAfn  (date: TDate; path: string; ext: str3): string;
      function  get_STAfn_ (date: TDate; ext_sta,ext: string): string;


      function  get_STAdata_fn (date: TDate; ext: string): string;
      function  get_STAsuma_fn (date: TDate; ext: string): string;
      function  get_STAwork_fn (date: TDate; ext: string): string;

      function  is_STAdata_fn(fn: string): bool;
      function  is_STAsuma_fn(fn: string): bool;
      function  is_STAwork_fn(fn: string): bool;


      function  get_STAarch_fn_(date: TDate; ext: string): string;
      function  get_STAarch_fn (date: TDate; externy: bool): string;

      function  denna_statistika(d: TDate): bool;
      function  sta_doplnit_nazov_polozky (polozka, id, numid,numval: string; doplnit: bool; zarovnat: byte): string;
      function  sta_nazov_polozky (id, numid,numval: string; zarovnat: byte): string;
      procedure read_FL_XX(_cfg_FN: string; cfg_FL_XX: string; var FL_XX: long; var FL_XX_: string);
