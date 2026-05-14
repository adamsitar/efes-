  { values for asynch routines } { kompilovat s S- }
    const NET_AS_OPEN	  = $01;
          NET_AS_RCV	  = $02;                { signalizuje prijatie data, nado net_read alebo net_readfrom }
          NET_AS_XMT	  = $03;
          NET_AS_XMTFLUSH = $04;                
          NET_AS_FCLOSE	  = $05;                { foreign app has closed its side... }
          NET_AS_CLOSE	  = $06;
          NET_AS_ERROR	  = $07;                { timeout or error }
          NET_AS_URGENT	  = $08;
          NET_AS_ALARM	  = $00;		{ Use the unused 1st entry }

          MAX_AS_EVENT	  = NET_AS_URGENT;	{ The highest event we use }