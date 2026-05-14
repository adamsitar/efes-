  { -------------------------- }
  { TNETbuffer                 }
  { -------------------------- }
  {

{ Buffer pre zachytenie sprav z NET.
  Spravy su pred vlozenim konvertovane podla uzla, odkial prisli.

  Pri prijme paketu - ak top<items-1, zaradi ho do do buffera,
  inak ignoruje.
}

  type  Tproc_decode_pkt = procedure (const pkt: TNETpkt; p: pointer);


  type  PNETpkt_buffer = ^TNETpkt_buffer;
        TNETpkt_buffer = array[0..MAX_PTRs-1] of PNETpkt;

        {TNETdata_buffer}


  type  PNET = ^TNET;
        TNET = object(TDynamic)

          buff  : PNETpkt_buffer;   { adresa na svoj ap^... ; data  : PNETdata_buffer; ack_buff : PNETack;}

          Owner : PApp;

         private

          in_file            : bool;  { je nieco v subore tmp_????.pkt }
          cislo_tmp_packet   : int;
          semaphor_tmp_pkt_r : bool;
          semaphor_tmp_pkt_s : bool;

          is_dta     : bool;
          is_brc     : bool;

          is_reroute : bool;
          s_reroute  : bool;

          is_ack     : bool;
          is_pkt     : bool;

          s_ack      : bool;
          s_mess     : bool;
          s_data     : bool;
          s_system   : bool;
          s_init     : bool;

          t_ack,t_data : TNETtyp;


         public

          constructor Init;
          destructor  Done; virtual;

         {private}

          function    NewData  (p: pointer): pointer; virtual;
          procedure   DispData (var p: pointer); virtual;

          function    Add (item: pointer): int; virtual;
          procedure   Del (ind: int); virtual;

          function    is_file: bool;
          procedure   save_tmp_pkt(var pkt: TNETpkt);
          procedure   read_tmp_pkt;



         { --------------------------------
           Prijem paketov
         }
         {private}

          function    is_correct_pkt (const pkt: TNETpkt): bool; virtual;
          function    is_data_to_ack (const pkt: TNETpkt): bool; virtual;

         public {protected}

          function    add_data_pkt   (const pkt: TNETpkt): bool;
          function    add_ack_pkt    (var   pkt: TNETpkt): bool;

          function    receive_pkt (var pkt  : TNETpkt): int; {virtual;}
          procedure   receive_brc (const Bpkt : TNETBpkt {$IFDEF PCTCP}; from : T_IPaddress {$ENDIF}); virtual;

          procedure   read_inp_buff;


         { --------------------------------
           Nacitanie a spracovanie paketov
         }

         {private}

          function    select_pkt_ind (_lo,_hi: long; prty: bool): int;
          procedure   read_data_pkt;       { spracuje najdolezitejsej spravy }

          function    read_ack_pkt: bool;  { spracovanie potvrdenia }
          procedure   read_ack_pkts (ack: PNETpkt;
                                     var key: string;
                                     var rec: Tplan_rec;
                                     var fdp: bool
                                    ); {$IFDEF DEBUG} virtual; {$ENDIF}

          procedure   reroute_pkt;         { posle spravu dalej     }

         public

          procedure   read_net_buff_ack;
          procedure   read_net_reroute_pkt;
          procedure   read_net_buff_data;
          procedure   read_net_file_data;


         { ----------------------------------
           Dekodovanie a spracovanie paketov
         }
          {procedure   _decode_ack_pkt     (var pkt: TNETpkt;
                                           size_item: word; disp_item: PProc_p;
                                           process: PProc_ps
                                          );
         }
          procedure   nodeON  (ods: TNETadr; _node_init,_node_on,_init_en: bool); virtual;
          procedure   nodeOFF (ods: TNETadr; _node_off: bool; id: PNETpkt_head); virtual;

          procedure   decode_app_ack_pkt  (var pkt: TNETpkt); virtual;

          procedure   _decode_data_pkt    (var pkt      : TNETpkt;

                                           size_item     : word;
                                           p_disp_item   : PProc_p;

                                           p_decode_data : Pdecode_NETpkt_data;
                                           p_accept      : Paccept_NETdata;
                                           p_save        : Pprocess_NETdata;
                                           p_process     : Pprocess_NETdata;
                                           {p_process_pkt : Pdecode_NETpkt_data;}

                                           en_inf: pchar;
                                           rec: bool
                                          );
          procedure   decode_app_data_pkt (var pkt: TNETpkt; _stream: bool); virtual;


         { ----------------------------------
           Kontrola uzlov
         }
          procedure   initialize_node (nd: int); virtual;
          procedure   check_nodes; virtual;


         { --------------------------------
           Odoslanie paketov
         }
          function    send_data(adr      : TNETadr;

                                typ      : word;
                                p_data   : pointer;
                                p_cdata  : Pcode_NETpkt_data;
                                p_ckey   : Pcode_NETkey;
                                p_rec    : Pplan_rec;

                                id       : PNETpkt_head;

                                is_filter  : bool;
                                info     : string;
                                filter   : pointer;
                                wait,msg : bool;
                                flag     : word
                               ): int;


          function    id__distributed_data
                               ( typ     : word;
                                 p_data  : pointer;
                                 send_to : PBplan_rec
                               ): PNETpkt_head; virtual;

          function    distribute_data
                               (tp      : Tnd_typ_set;
                                sw      : Tnd_sw_set;
                                nd      : Tnd_nd_set;

                                typ     : word;

                                p_data  : pointer;
                                p_cdata : Pcode_NETpkt_data;
                                p_ckey  : Pcode_NETkey;
                                p_rec   : Pplan_rec;

                                is_filter : bool;
                                info      : string;
                                filter    : pointer;
                                nd_slave  : bool;
                                nd_backup : bool;

                                flag    : word
                               ): bool;


         { --------------------------------
           Odoslanie/prijem suborov
         }

          function    send_file (adr      : TNETadr;
                                 typ      : word;

                                 fn       : string;
                                 id       : PNETpkt_head;

                                 info     : string;
                                 flag     : word;    { i ked nie je spojenie [udp?] }

                                 ispath,isext : bool;
                                 isrec,isrecdb : bool;
                                 isbmode : bool
                                ): int; {$IFDEF DEBUG} virtual; {$ENDIF}


          function    distribute_file
                                (tp      : Tnd_typ_set;
                                 sw      : Tnd_sw_set;
                                 nd      : Tnd_nd_set;

                                 typ     : word;

                                 fn      : string;
                                 info    : string;
                                 flag    : word;    { i ked nie je spojenie [udp?] }

                                 ispath,isext : bool;
                                 isrec,isrecdb : bool;
                                 isbmode : bool
                                ): bool; {$IFDEF DEBUG} virtual; {$ENDIF}


          function    receive_file
                                (var pkt: TNETpkt;
                                 var fn,fr: string;   { meno posielaneho a prijateho (docasneho) subora }
                                 p_fn  : PSFunc_s;    { fcia pre urcenie mena }
                                 isname,              { spracovava sa uplne meno ? }
                                 isnl,
                                 isrec,isrecdb : bool
                                ): string; {$IFDEF DEBUG} virtual; {$ENDIF}
        end;
