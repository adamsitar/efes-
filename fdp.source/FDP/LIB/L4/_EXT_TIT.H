      const  {$IFDEF SLOVAK}

               tit_ini           = 'KONFIGURèCIA SPOJENIA';

               {tit_sprava        = 'Spr†va';
               tit_nebola        = 'nebola';
               tit_potvrdena     = 'potvrden†.';}

             {$ENDIF}


             {$IFDEF CZECH}

               tit_ini           = 'KONFIGURACE SPOJENã';

               {tit_sprava        = 'Zpr†va';
               tit_nebola        = 'nebyla';
               tit_potvrdena     = 'potvrzena.';}

             {$ENDIF}


             {$IFDEF ENGLISH}

               tit_ini           = 'INTERFACE CONFIGURATION';


             {$ENDIF}

               tit_sprava        = 'Message';
               tit_nebola        = 'was not';
               tit_potvrdena     = 'accepted by LAM.';


      const  err_ext_unable_read_i_buffer      = 'Unable to read input buffer.';
             err_ext_invalid_packet_frame      = 'Invalid packet frame.';
             err_ext_unable_decode_packet      = 'Unable to decode received packet.';

             err_ext_frame_begin               = 'Cannot find start of text "'+icao_STD+'".';
             err_ext_frame_end                 = 'Cannot find end of text "'+icao_END+'".';

             err_ext_undecoded_message_header  = 'Cannot find message header.';
             err_ext_undecoded_message_type    = 'Cannot identify message type.';
             err_ext_undecoded_message_sender  = 'Cannot identify message sender.';
             err_ext_undecoded_message_address = 'Cannot identify message address.';
             err_ext_undecoded_message_number  = 'Cannot decode message sequence number.';

             err_ext_unprocessed_message_type  = 'This message type is not to be processed.';
             err_ext_received_address          = 'Another destination address.';
             err_ext_sender_address            = 'Unexpected sender address.';

             err_ext_packet_exists             = 'Packet already exists.';
             err_ext_packet_not_sent           = 'Packet not send.';
             err_ext_uncorrect_address         = 'Incorrect address';

             err_ext_lam_data                  = 'Unrecognised lam data.';

             say_message_processed_            = 'Edited message has been processed by ';
             say_message_changed_              = 'Edited message has been changed by ';
             ask_message_changed               = 'Message content has been revised. Save changes ?';
             ask_message_deleted               = 'Message will be deleted. Are you sure ?';
             say_checking_message              = 'Checking integrity and processing of message...';

             edi_queue_start                   = 'Start of queue.';
             edi_queue_end                     = 'End of queue.';
