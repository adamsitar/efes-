
          { ----------------------------------------------- }
          { Stav planu :                                    }
          {                                                 }
          {  - popisuje posledny vysledok spracovania planu }
          {                                                 }
          { ----------------------------------------------- }


    type   { Zakladne stavy spracovania planu...
           }
            Tstav = (_plan,
                     _ziadost,_zamietnuty,_schvaleny,
                     _aktivovany,_preruseny,_ukonceny,
                     _zruseny,
                     _neplatny
                    );


    const  { Elementarne polozky popisujuce
             stav spracovania planu
             a prenasane spolu s nim...
           }

            kod_plan_status = 5;


            cnst_disk     = '.';
            cnst_sended   = '*';    { odoslany }

            cnst_start    = '';
            cnst_finish   = '';

            cnst_active   = 'A';    { active  }
            cnst_mzp      = 'M';
            cnst_dla      = 'D';    { oneskoreny }
            cnst_pause    = 'B';    { break   }

            cnst_chg      = 'C';    { correct }
            cnst_cnl      = '@';    { zruseny }
            cnst_cnlsys   = '#';    { zruseny systemom }

            cnst_prop     = '?';    { ziadost o pripomienku planu }
            cnst_acc      = '+';    { accept  }
            cnst0_acc     = '+';
            cnst_dec      = 'N';    { decline }
            cnst0_dec     = '-';

            cnst_read     = '%';    { pripomienkovana sprava na let, este nespracovana,

                                      napr : cnst_acc + cnst_req_chg + cnst_read
                                    }

            cnst_warn     = 'W';    { warovanie pred zrusenim diverzie }

            {cnst_accepted = '*';
            cnst_denied   = '-';}


    const  { Mozne kombinacie poloziek
             pre moznych skupin stavov
           }

            cnst_requested    =   cnst_disk + cnst_sended + cnst_prop; { nemenit kvoli FUA }

            cnst_planned_     =   cnst_disk + cnst_sended + cnst_dla;

            cnst_planned      =   cnst_disk + cnst_sended
                                + cnst_prop + cnst_acc + cnst_dec
                                + cnst_dla;

            cnst_all_valid    =   cnst_disk  + cnst_sended {+ cnst_server}
                                + cnst_chg
                                + cnst_prop  + cnst_acc    {+ cnst_dec} + cnst_dla
                                + cnst_start + cnst_active + cnst_pause + cnst_mzp
                                {+ cnst_read}
                                {+ cnst_warn};

            cnst_all          = cnst_all_valid + cnst_warn + cnst_cnl + cnst_dec + cnst_finish;


          { pripomienky }
            cnst_str_chg      = cnst_read + cnst_chg;  { priznak, ze plan bol spracovany na stredisku }
            cnst_req_approved = cnst_acc  + cnst_dec;  { schvaleny/zamietnuty }

            cnst_req_acc      = cnst_read + cnst_acc;
            cnst_req_chg      = cnst_read + cnst_chg + cnst_acc;
            cnst_req_dec      = cnst_read + cnst_dec;



          { kody (pre)aktivnych stavov }
            cnst_stat_dep     = cnst_start+cnst_active;
            cnst_stat_arr     = cnst_finish+cnst_cnl;

            cnst_stat_mzp     = cnst_finish+cnst_mzp;
            cnst_stat_mzs     = cnst_start+cnst_mzp;

            cnst_stat_act     = cnst_start + cnst_active + cnst_pause + cnst_mzp;
            cnst_stat_preact  = cnst_acc + cnst_stat_act;
            cnst_stat_actived = cnst_stat_act+cnst_stat_arr;

            {cnst_stat_mzp    = cnst_act_plan;}




    function  _is_stat    (_stat: string; { stav }
                           _cond: string; { podmienky }
                           _all : bool    { vsetky podmienky musia byt splnene ? }
                          ): bool;
    function  _is_statp   (_stat  : string;
                           _pcond : pstring;
                           _all   : bool
                          ): bool;

    function  __is_stat   (_stat,_cond : string): bool;
    function  __is_statp  (_stat: string; _cond : pstring): bool;

    function  _is_stat_cnl(_stat : string): bool;

    function  _is_stat_us (_src, _stat,_cond: string): bool; far;
    function  _is_stat_ot (_src, _stat,_cond: string): bool; far;
    function  _sw_stat_us (all: bool; p_all,p_own: pointer): pointer;


    function  _decode_stav (stat: string): Tstav;
    {function  _code_stav   (stat: Tstav): string;}

    function  decode0_stat (stat: string): string;
    function  code0_stat   (stat: string): string;

    function  code_l4_stat_ (stat: string; oprava: bool): string;
    function  code_l4_stat (stat: string): string;
    {function  decode_l4_stat (stat: string): string;}


    function  decode_stat_s   (stat: string; rod: byte): string;
    function  decode_stat_fpl (stat: string): string;
    function  decode_stat_act (stat: string): string;


    function  add_stat(status: string; novy: string): string;
    function  del_stat(status: string; novy: string): string;


    function  valid_plan   (stt : string): bool;
    function  sended_stat  (adr: TNETadr; stat: string): string;
    function  cnl_stat     (stat: string): string;
    function  del_cnl_stat (status: string): string;


    procedure write_stat  (stat: string; rec: TPlan_rec; adr: TNETadr; xi,yi, cl: int);
    function  get_stat_cl (stat: string): byte;
