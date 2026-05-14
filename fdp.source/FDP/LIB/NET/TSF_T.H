    { ----------------------
      NETBIOS Command Block
     תתתתתתתתתתתתתתתתתתתתתתת
    }

    { Note:- when using these data structures the field offset in the record
      is significant.  These fields MUST be byte aligned in the record, see
      the X.25 API manual for the field offset values. In Turbo 5. check
      the setting of the $A compiler directive - other Pascal compilers
      check with the compiler reference for byte aligning fields within
      structures.
    }

    type   NETBIOS_control_block = record

             command    : byte;           { 0  command                           }
             retcode    : byte;           { 1  return code                       }

             lsn        : byte;           { 2  local session number, alebo kanal }
             num        : byte;           { 3  number of application name        }

             buffer     : pbytes;         { 4  message buffer address ?= char far *buff, were as "int?!" }

             sl         : record
                          case byte of
                            0 : (service : word); { 8  service required }
                            1 : (length  : word)  {    or buffer length }
                          end;

             cs_chain   : record
                          case byte of
                            0 : (cs_callname : Network_Service_Access_Point); { 10 name or NUA }
                            1 : (csend_chain : record
                                  chain_length : word;                { - length of 2nd buf for chain send }
                                  chain_buff   : pbytes               { - 4  message buffer address        }
                                 end)
                          end;

             name       : Network_Service_Access_Point;  { 26  local name, pseudoadresa   }

             rto        : byte;           { 42  rcv timeout                      }
             sto        : byte;           { 43  send timeout                     }

             posting    : pbytes;         { 44  ! posting function  int (far *ncb_post)();  }

             lana_num   : byte;           { 48  adapter number                   }
             cmd_cplt   : byte;           { 49  command complete                 }
                                          { 50  reserved for Netbios             }

             reserved1  : array[1..4] of byte;
             cause      : byte;
             diag       : byte;
             reserved2  : array[1..8] of byte

           end;


    { תתתתתתתתתתתתתתתתתתתתתת
       X25 name data record
      תתתתתתתתתתתתתתתתתתתתתת

      pre NCB.ADD.EXTENDED.NAME a NCB.QUERRY.EXTENDED.NAME commands

    }

    type   X25_name_data_record = record
             ae_service : byte;   { NAME MODE : STDMODE, X25MODE... }
             ae_wild    : byte;   { Wild CUD indicator : 0 - CUD preset, 1 - wild CUD }
             {
              ... doplnit podla strany 25 v X.25 Programming Interface Reference Manual ...
             }
           end;


    { תתתתתתתתתתתתתתתתתתתת
       X25 preamble block
      תתתתתתתתתתתתתתתתתתתת

      One of these precedes all data blocks transferred in X25 mode
    }
    type   X25_preamble_block = record
             mbit      : byte;
             qbit      : byte;
             idata     : byte;
             reset     : byte;

             reserved1 : array[1..4]  of byte;
             dbit      : byte;
             reserved2 : array[1..11] of byte
           end;


    { תתתתתתתתתתתתתתתתתתתתתתת
       X25 connection record
      תתתתתתתתתתתתתתתתתתתתתתת

      Used by NCB.TSF.CALL, NCB.TSF.LISTEN  commands
    }
    type   X25_connection_record = record             { ( x25_cr, xc ) }
             zero        : array[1..4]  of byte;
             reserved1   : array[1..19] of byte;
             facilities  : byte;

             name        : Network_Service_Access_Point; { 16B }
             nua         : Network_User_Address;         { 16B }

             cug         : byte;
             data_length : byte;

             reserved2   : array[1..18]  of byte;
             data        : array[1..128] of byte
           end;


    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       X25 extended connection record
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

      Used by NCB.EXTENDED.CALL, NCB.EXTENDED.LISTEN
      Refer to API manual SWF-X25/NB
    }

    type   X25_extended_connection_record = record    { ( ext_cr, xe ) }
             zero        : array[1..4]  of byte;      { dongle array   }
             res         : array[1..16] of byte;      { XE_RESERVED... }

             req_type    : byte;                      { request type   }
             report_code : byte;                      {                }
             mode_op     : byte;                      {                }
             fill_1      : byte;                      { 24 ...         }

             ph_lnua     : record
                           case byte of
                             0 : ( phone_no : record
                                     ph_len  : array[1..2]  of char;
                                     ph_no   : array[1..30] of char
                                   end
                                 );
                             1 : ( loc_nua : record  { returns local called NUA after wcard listen }
                                     res2    : Network_Service_Access_Point;
                                     loc_nua : Network_User_Address
                                   end
                                 )
                           end;

             name        : Network_Service_Access_Point;      { pseudoname reffered to NUA }
             nua         : Network_User_Address;              { called NUA                 }

             calltype    : byte;
             ignore_reset: byte;

             line_select : byte;
             window_size : byte;
             packet_size : word;

             cause       : byte;
             diag        : byte;

             cud_len     : byte;
             fill        : byte;
             cud         : array[1..128] of byte;     { asi CALL USER DATA }

             prof_len    : byte;
             facil_len   : byte;
             facilities  : array[1..200] of byte;
             profile     : array[1..72]  of byte
           end;

    { תתתתתתתתתתתתתתתתתתתתתתת
       Adapter status buffer
      תתתתתתתתתתתתתתתתתתתתתתת

      Refer to API manual SWF-X25/NB
    }

    type   Adapter_status_buffer = record
             addr              : array[1..6] of byte;
             version           : array[1..4] of byte;

             period            : word;
             frmr_rxed         : word;
             frmr_txed         : word;
             i_frm_err_rxed    : word;
             aborted_txs       : word;
             pkts_txed         : {unsigned} long;
             pkts_rxed         : {unsigned} long;
             i_frm_err_txed    : word;
             lost_data         : word;
             t1_expired        : word;
             ti_expired        : word;
             ext_address       : pbytes;
             free_ncbs         : word;
             max_conf_ncbs     : word;
             max_ncbs          : word;
             buf_unavailable   : word;
             max_packet_size   : word;
             sess_in_use       : word;
             conf_max_sess     : word;
             max_poss_sess     : word;
             int_data_buf_size : word;
             local_names       : word;

             name_data         : array[0..MAX_NAMES-1] of record
                                   name     : Network_Service_Access_Point;
                                   name_num : byte;
                                   name_stat: byte
                                 end
           end;


    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       Status of individual session
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

      1 of these is included for each session owned by a local name
    }
    type   tsf_sess_stat = record
             lsn         : byte;
             state       : byte;

             local_name  : Network_Service_Access_Point;
             remote_name : Network_Service_Access_Point;

             nrcv        : byte;
             nsnd        : byte
           end;


    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       Status of group of sessions
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
    type   tsf_gsess_stat = record
             no_of_sess : byte;
             name_sess  : byte;
             dummy1     : byte;
             rcv_anys   : byte;
             space1     : array[0..MAX_SESSIONS-1] of tsf_sess_stat;  { struct  tsf_sess_stat space1 }
           end;



    { ----------------------
      TSF packet
     תתתתתתתתתתתתתתתתתתתתתתת
    }

    type   P_TSFpacket = ^TSFpacket;
           TSFpacket   = record
              ncb  : NETBIOS_control_block;
              conn : record
                     case byte of
                       0 : (n_ds : X25_name_data_record);
                       1 : (x_cr : X25_extended_connection_record);
                       2 : (pole : array[0..DATAMAX+4 - 1] of byte);
                       3 : (data : record
                                     preamble : X25_preamble_block;
                                     data     : X25_packet_array
                                   end
                           )
                     end
           end;
