     procedure NET_init (_NET: PNET);

     procedure Sprava_o_zapnuti;
     procedure Sprava_o_vypnuti;



    { odosielanie sprav do heterogennej siete LETVISu
    }

     function  NETmsg (err: word): pchar;

     procedure NETsend_msg  (adr  : TNETadr;
                             typ  : TNETtyp;

                             data : pchars;
                             dlz  : TNETdlz;

                             check_ack : bool;
                             flag : word
                            );

     procedure NETsend_err  (adr    : TNETadr;
                             level  : byte;
                             dialog : bool;
                             err    : pchars;
                             dlz    : TNETdlz
                            );

     procedure NETdistribute_msg
                            (tp   : Tnd_typ_set;
                             sw   : Tnd_sw_set;
                             nd   : Tnd_nd_set;
                             typ  : TNETtyp;

                             data : pchars;
                             dlz  : TNETdlz;

                             check_ack : bool;
                             flag : word
                            );


     function  NETsend_data (adr      : TNETadr;
                             typ      : TNETtyp;

                             p_data   : pointer;
                             p_cdata  : Pcode_NETpkt_data;
                             p_ckey   : Pcode_NETkey;
                             p_rec    : Pplan_rec;

                             is_filter  : bool;
                             info     : string;
                             filter   : pointer; { maju narok data byt tam odpravene ? }
                             wait,msg : bool;    { ako vysielat }
                             flag     : word     { i ked nie je spojenie [udp?] }
                            ): int; far;


     function  NETdistribute_data
                            (tp      : Tnd_typ_set;
                             sw      : Tnd_sw_set;
                             nd      : Tnd_nd_set;
                             typ     : TNETtyp;

                             p_data  : pointer;
                             p_cdata : Pcode_NETpkt_data;
                             p_ckey  : Pcode_NETkey;
                             p_rec   : Pplan_rec;

                             is_filter : bool;
                             info      : string;
                             filter    : pointer;
                             slave     : bool;
                             backup    : bool;

                             flag : word
                            ): bool; far;


     function  NETsend_file (adr     : TNETadr;
                             typ     : TNETtyp;

                             fn      : string;
                             info    : string;
                             flag    : word;    { i ked nie je spojenie [udp?] }

                             ispath,isext : bool;
                             isrec,isrecdb : bool;
                             isbmode : bool
                            ): int;


     function  NETdistribute_file
                            (tp      : Tnd_typ_set;
                             sw      : Tnd_sw_set;
                             nd      : Tnd_nd_set;
                             typ     : TNETtyp;

                             fn      : string;
                             info    : string;
                             flag    : word;    { i ked nie je spojenie [udp?] }

                             ispath,isext : bool;
                             isrec,isrecdb : bool;
                             isbmode : bool
                            ): bool; far;



    { prijimanie sprav z heterogennej siete LETVISu
    }

     function  NETreceived_file_name
                            (fn: string): string;

     function  NETreceive_file
                            (var pkt: TNETpkt;
                             var fn,fr: string;  { meno posielaneho a prijateho (docasneho) subora }
                             p_fn  : PSFunc_s;   { fcia pre urcenie mena }
                             isname,             { spracovava sa uplne meno ? }
                             isnl,
                             isrec,isrecdb : bool
                            ): string;


    { nekonecny cyklus
    }

     procedure NET_check0; far;
     procedure NET_checkA; far;
     procedure NET_checkD; far;



    { pomocne fcie
    }

     function  read_file_rec  (fr: string; isrecdb: bool; var rec: Tplan_rec): bool;
     function  write_file_rec (fr: string; isrecdb: bool; rec: Tplan_rec): bool;
     procedure file_rec       (nd: int; fn: string; isrecdb: bool; what: char; clear: bool);

     function  print_str_to_net   (PortNo: byte; s: string): string;
     function  print_str_from_net (pkt: TNETpkt): string;

     procedure say_data_sended (res: bool);

     function  net_pkt_head (var pkt: TNETpkt; typ: TNETtyp; adr: TNETadr): bool;

      function  net_pkt_data (var pkt: TNETpkt; pdlz: TNETdlz; data: pchars): bool;
      procedure net_pkt_ack  (const pkt: TNETpkt; var ack: TNETpkt);

      function  NETsend_pkt  (var pkt: TNETpkt; flag: word;
                              check_ack: bool;
                              key : string;
                              id  : PNETpkt_head;
                              disp: bool
                             ): int;

     {$IFDEF DEBUG}
      function  pkt_cis: word;
      procedure NETcfg_read;
     {$ENDIF}


     { IFDEF DD_EXE}
       procedure  net_pkt_test(fn: string; _h,_m: int);
     { ENDIF}

     {$IFDEF _X25}
      function  is_bridge: bool;                            { kvoli net_cfg }
      function  is_X25_LANadr(var adr: TNETadr): int; far;
     {$ENDIF}
