    type  T_tsf_stat = (tsf_idle, tsf_listen,tsf_call, tsf_receive);


    type  PO_TSF = ^O_TSF;
          O_TSF = object

            tsf_stat: T_tsf_stat;

            SW_INTR_TSF : word;
            ADPTR_NUM   : byte;
            PKTWINDOWSZ : byte;
            PKTPKTSZ    : byte;


            constructor Init;
            destructor  Done;

            function    call_API(var ncb: NETBIOS_control_block): byte;

            procedure   init_pkt     (var pkt: TSFpacket);
            procedure   init_call_pkt(var pkt: TSFpacket; _local_name: Network_Service_Access_Point);
            procedure   init_data_pkt(var pkt: TSFpacket; _local_session_num: byte);

            function    add_local_name(_local_name : Network_Service_Access_Point;
                                       _local_nua  : Network_User_Address;
                                       _MODE       : byte
                                      ): byte;
            procedure   delete_local_name(_local_session_num: byte);

            function    receive: bool;
          end;