          { ---------------------------------------------
            Popis formatu RPL planov podla Doc. IFPS_MAN
            ---------------------------------------------

            0 990325 DEST: UKBVZRZX
            0 990325 SNDR: UKKKZDZX
            1 RPL                990328 991025      UKKKZDZX
            2 990329 991025 1000000 AEW101     B732   UKBB 0330 UKHH 0040
            3            BULAP A137 MATEG

          }


    const { --------------------------------------------
            Zaznamy/ ..._RECORD
            --------------------------------------------
          }
           IFPS_HEADER             = '0';
            r_IFPS_DEST            = 0;
            r_IFPS_SEND            = 1;

           IFPS_RPL_HEADER         = '1';
           IFPS_RPL_FLIGHT_INFO    = '2';
           IFPS_RPL_ROUTE          = '3';  { _15, povinne pole [M], moze byt viac riadkov }
           IFPS_RPL_REMARKS        = '4';  { _18, nepovinne pole [O], moze by t viacejkrat }

           IFPS_TRAILER            = '9';  { moze byt eof }


          { --------
            Polia
            --------
          }

    const record_type              = 1;

          { HEADER

            IFPS : 0 990325 SNDR: SWR                   123/35/87/X
            UKBB : 0 990325 DEST: UKBVZRZX
          }
           file_creation_date      = 3;  { M }
           _file_creation_date     = 8;

           header_identifier       = 10; { M }
           _header_identifier      = 14;
           header_identifier_DEST  = 'DEST:';
           header_identifier_SNDR  = 'SNDR:';

           sender_dest_id          = 16; { M }
           _sender_dest_id         = 35;

           sender_dest_ref         = 37; { O }
           _sender_dest_ref        = 52;

           header_pare             = 54; { O }
           _header_spare           = 72;


          { RPL_HEADER

            IFPS : 1 RPL SWR 89-02 NLST 990328 991025 001
            UKBB : 1 RPL                990328 991025      UKKKZDZX
          }
           text_identifier         = 3;  { M }  { "RPL" }
           _text_identifier        = 5;
           text_identifier_RPL     = 'RPL';

           operator_designator     = 7;  { M }  { "RPL item "E" YY-nn }
           _operator_designator    = 9;

           serial_number           = 11; { M }
           _serial_number          = 15;

           file_type               = 17; { M }  { "NLST", complete new file }
           _file_type              = 20;        { "RLST", revised list }

           validity_period         = 22; { M }  { urcenie platnosti udajov, ak sa maju }
           _validity_period        = 27;        { okamzite nahradit tak "000000",
                                                  inak "YYMMDD"
                                                }

           expiry_date             = 29; { M }  { "YYMMDD", inak RPL_UFN }
           _expiry_date            = 34;
           id_no_expiry            = 'RPL_UFN';

           sequence_number         = 36; { M }  { poradove cislo subora od 0001 do 9999 }
           _sequence_number        = 39;

           sumplementary_data      = 41; { M }  { ako pole "G" u RPL }
           _sumplementary_data     = 72;


          { RPL_FLIGHT_INFO

            IFPS : 2 990329 991025 1234567 SWR436     B732   UKBB 0330 UKHH 0040  +
            UKBB : 2 990329 991025 1000000 AEW101     B732   UKBB 0330 UKHH 0040
          }

           valid_from              = 3;  { M }  { pole "I" "YYMMDD" }
           _valid_from             = 8;

           valid_until             = 10; { M }  { pole "J" "YYMMDD" }
           _valid_until            = 15;

           days_of_operation       = 17; { M }  { pole "K" "YYMMDD" }
           _days_of_operation      = 23;

           aircraft_identification = 25; { M }  { pole "L" }
           _aircraft_identification= 34;

           aircraft_type           = 36; { M }  { pole "M", cast 1  }
           _aircraft_type          = 39;

           wake_turbulency_cat     = 41; { M }  { pole "M", cast 2  }
           _wake_turbulency_cat    = 41;

           departure_aerodrome     = 43; { M }  { pole "N", cast 1  }
           _departure_aerodrome    = 46;

           departure_time          = 48; { M }  { pole "N", cast 2  }
           _departure_time         = 51;

           destination_aerodrome   = 53; { M }  { pole "P", cast 1  }
           _destination_aerodrome  = 56;

           total_est_elapsed_time  = 58; { M }  { pole "P", cast 2  }
           _total_est_elapsed_time = 61;

           entry_type              = 63; { M }
           { referencie do predchadzajuceho subora
             "-" znamena zrusenie kazdeho takeho rpl planu (ak je typ subora RLST)
             "+" pre kazdy novy plan (NLST), alebo opakujuci sa plan (RLST)
             " " prazdny znamena, ze oproti predchadzajucemu planu nedoslo ku zmene
           }


           RPL_AS_FOR_ITEM_X = 'AS FOR RPL ITEM X';  { znamena, ze poznamka obsahuje udaje ako RPL "X" }


          { RPL_ROUTE

            3  N0440F330 BULAP A137 MATEG
            3            BULAP A137 MATEG
          }
           route                   = 3; { M }  { pole "O" }
           _route                  = 72;
           {
           }


          { RPL_REMARK

          }
           remarks                 = 3; { M }  { pole "Q" }
           _remarks                = 72;
           {
           }


          { TRAILER
          }
           as_for_file_header      =  3; { M }
           _as_for_file_header     = 52;

           file_record_count       = 54; { M }  { pocet V zaznamov subora, vcitane hlavicky a chvostika, }
           _file_record_count      = 59;        { zlava dopleneny nulami }

           trail_spare             = 60;
           _trail_spare            = 72;
