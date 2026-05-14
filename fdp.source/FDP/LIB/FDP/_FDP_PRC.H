    type    TProc_decode_key    = procedure (key: string; data : pointer);

            Tdbread_key_data    = function  (key: string; data : pointer): int;
            Pdbread_key_data    = ^Tdbread_key_data;

            Tdisplay_plan       = function  (data: pointer; title: string) : bool;
            Pdisplay_plan       = ^Tdisplay_plan;


            TNET_send_pkt           = function  (p: pointer; adr: TNETadr; wait: bool): bool;
            TNET_distribute_pkt     = function  (p: pointer; sw : Tnd_sw_set; nd: Tnd_nd_set): bool;
            TNET_distribute_rdp_pkt = function  (p: pointer; add: pbool): bool;
            TNET_message_pkt        = procedure (p: pointer; kod: word; adr: string);


            TPLAN_zarad   = function (plan: pointer; _stat: string; _send: bool; _src: fdp_src): bool;
            PPLAN_zarad   = ^TPLAN_zarad;

            TPLAN_zmeneny = function (plan: pointer; zobraz: bool): bool;
            PPLAN_zmeneny = ^TPLAN_zmeneny;
