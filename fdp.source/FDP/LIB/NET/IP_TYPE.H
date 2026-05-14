      type p_arp_entry = ^arp_entry;
           arp_entry = record
	     ip_addr : in_name;	                { IP address }
	     timeout : long;	                { time until expiration [ms],
                                                  negative time means already expired }
	     hd_addr : array[0..5] of byte;     { hardware address }

      	     rif     : record                   { token-ring Routing Information Field }
               (*
	       unsigned length : 5;		{ Length of RIF segment }
	       unsigned broadcast : 3;		{ Broadcast Indicators }
	       unsigned reserved : 4;		{ Reserved -- must be 0 }
	       unsigned max_frame : 3;		{ MTU maximum length }
	       unsigned direction : 1;		{ Direction of RDs }
               *)
               carry   : array[0..1] of byte;
	       desig   : array[0..7] of word 	{ Routing Designators }
             end
           end;


      type p_conf_item = ^conf_item;
           conf_item = record
             tag     : byte;		{ Tag number }
             flags   : byte;		{ Flags (see below) }
             sigbyte : short;	        { Size of datum }
             data    : pointer		{ Pointer to the actual data }
           end;

           mult_item = record
             max     : byte;	        { How many we can handle }
             num     : byte;	        { How many we've got }
             data    : pointer		{ Pointer to the actual stuff }
           end;
