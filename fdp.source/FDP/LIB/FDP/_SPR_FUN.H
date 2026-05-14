   { -----------------
      zakladnie fcie
     -----------------
   }

     procedure new_SPR  (SPR1, SPR2: PSPR); far;
     procedure disp_SPR (SPR: PSPR); far;

     function  eq_SPR   (SPR1, SPR2: PSPR): bool; far;

     {procedure init_SPR(SPR: PSPR; adr: TNETadr);}


   { ------------
      kodovanie
     ------------
   }
     function  code_l4_SPR_  (SPR: PSPR; cislo: string): pchar; far;
     function  decode_l4_SPR_(data: pchars; size: TNETdlz; SPR: PSPR): string; far;

     function  codekey_SPR   (SPR: PSPR): string; far;
     procedure decodekey_SPR (key: string; SPR: PSPR); far;

     procedure code_SPR      (SPR: PSPR; var pkt: TNETpkt); far;
     procedure decode_SPR    (const pkt: TNETpkt; SPR: PSPR); far;
     {$IFDEF DATA_BIN}
      procedure decode0_SPR  (const pkt: TNETpkt; SPR: PSPR); far;
     {$ENDIF}

     procedure codeDB_SPR    (SPR: PSPR; buff: PDB_buff; desc: PDB_head); far;
     procedure decodeDB_SPR  (buff: PDB_buff; SPR: PSPR; desc: PDB_head); far;


   { ------------
      read/save
     ------------
   }
     function  get_dbSPRfn(SPR: PSPR): string;

     function  read_SPR (key: string; SPR: PSPR): int; far;
     procedure save_SPR (SPR: PSPR); far;


   { ------------
      send
     ------------
   }
     function  send_SPR(SPR: PSPR; adr: TNETadr; wait: bool): bool; far;


   { ------------
      zobrazenie
     ------------
   }
     function  print_SPR(SPR: PSPR): bool; far;
     {procedure  _info_SPR(x0,y0,x1,y1: int; SPR: PSPR); far;}
     function  info_SPR(SPR: PSPR; title: string): bool; far;


   { ------------
      NET
     ------------
   }
     procedure _pkt_SPR_REC (const pkt: TNETpkt); far;
     procedure _pkt_SPR_LAM (const pkt: TNETpkt); far;
     procedure _ack_SPR (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;

     procedure process_report_SPR(const REP: TREP); far;
