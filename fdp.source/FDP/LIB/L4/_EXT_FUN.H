    { Synchronizacny paket
    }
     type  PSYNC_EXTpkt = ^TSYNC_EXTpkt;
           TSYNC_EXTpkt = record
             data : pchars;
             size : word;
             tit  : string;
             key  : string;
             fn   : string;
             from : TNETadr
           end;

    {$IFDEF SYNCHRONIZE_EXT}
     procedure disp_SYNC_EXTpkt    (data: PSYNC_EXTpkt); far;
     procedure code_SYNC_EXTpkt    (data: PSYNC_EXTpkt; var pkt: TNETpkt); far;
     procedure decode_SYNC_EXTpkt  (const pkt: TNETpkt; data: PSYNC_EXTpkt); far;
     function  codekey_SYNC_EXTpkt (data: PSYNC_EXTpkt): string; far;
    {$ENDIF}


    procedure indicate_ext (is: int);
    const     p_indicate_ext : p_proc_indicate_process = nil;

