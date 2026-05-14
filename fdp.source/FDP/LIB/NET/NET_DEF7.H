     const  path_NET = path_A+#255+'NET\';
            extNET   = 'NET';


     const  writeln_NET_REC       : bool = {$IFDEF EXTERNAL_NET} true {$ELSE} true {$ENDIF};
            writeln_NET_SEND      : bool = {$IFDEF EXTERNAL_NET} true {$ELSE} true {$ENDIF};
            writeln_NET_DATA      : bool = true;
            writeln_MEM           : bool = false;

            archive_NET_REC       : bool = {$IFDEF EDD} true {$ELSE} true {$ENDIF};
            archive_NET_SEND      : bool = {$IFDEF EDD} true {$ELSE} true {$ENDIF};


            cfg_archive_NET_SEND  = 'ARCHIVE-NET-SEND';
            cfg_archive_NET_REC   = 'ARCHIVE-NET-REC';

            writeln_NET_ACK       : bool = true;
            writeln_NET_HEARTBEAT : bool = false;
            archive_NET_HEARTBEAT : bool = false;

            cl_NET_REC            : byte = clGRc;
            cl_NET_SEND           : byte = clGR9;
            cl_NODE_ON                   = lightcyan;
            cl_NODE_OFF                  = cyan;
