    const      cas_PERM  = 'PERM';

               kod_TIME  = 4;
               kod_DATEr = 4;
               kod_DATE  = 6;

   { datum/cas
   }
    function   code_l4_utc      (h,m: byte): string;               { lepsie by bol "time", nie "utc" }
    function   decode_l4_utc    (s: string; var h,m: byte): bool;
    function   decode_l4_utc_s  (s: string): string;

    function   code_l4_time     (t: TTime): string;
    function   decode_l4_time   (s: string; var T: TTime): bool;

    function   code_l4_date_r   (den,mes : byte; am: bool): string;
    function   decode_l4_date_r (s: string; var d: TDate; am: bool): bool;
    {procedure  assign_date_r    (den,mes : byte; var rok: word);}

    function   code_l4_date_    (r: word; m,d: byte): string;
    function   code_l4_date     (d: TDate): string;
    function   decode_l4_date   (s: string; var d: TDate): bool;

    function   code_l4_datum    (d: TDatum): string;
    function   decode_l4_datum  (s: string; var d: TDatum): bool;
    function   code_l4_datums   (d: TDatum): string;
    function   decode_l4_datums (s: string; var d: TDatum): bool;
