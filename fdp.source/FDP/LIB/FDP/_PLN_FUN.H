     { -----------------
        zakladnie fcie
       -----------------
     }
      procedure  new_PLN   (PLN1, PLN2: PPLN); far;
      function   new_PLN_  (PLN1: PPLN; var PLN2: PPLN): PPLN; far;
      procedure  disp_PLN  (PLN: PPLN); far;
      procedure  disp_PLN_ (var PLN: PPLN); far;

      function   eq_PLN  (PLN1, PLN2: PPLN): bool; far;
      function   chg_PLN (PLN1, PLN2: PPLN): bool; far;


     { ------------
        kodovanie
       ------------
     }
      function  decode_PLN_aftn_tsga
                               (data: string; date: TDate; var PLN: DPLN;
                                check_en : bool; var res: string
                               ): bool;


      procedure decode0_PLN   (const pkt: TNETpkt; PLN: PPLN); far;

      procedure decodeDB_PLN  (buff: PDB_buff; PLN: PPLN; head: PDB_head);
      procedure decode_PLN    (const pkt: TNETpkt; PLN: PPLN); far;

      function  codekey_PLN   (PLN: PPLN): string; far;
      procedure decodekey_PLN (s: string; PLN: PPLN); far;


     { ------------
        save/read
       ------------
     }
      function  read_PLN (key: string; PLN: PPLN): int; far;
      procedure save_PLN (PLN: PPLN); far;


     { ------------
        zobrazenie
       ------------
     }
      const  dx_plan_PLN  = (kod_7a+2+kod_9b+2+(sizeof_PLNbod+1)*4+sizeof_PLNpozn) shl 3 + 1;
             dy_plan_PLN  = 8;

      procedure _info_PLN(x0,y0,x1,y1: int; PLN: PPLN); far;
      function  info_PLN(PLN: PPLN; title: string): bool; far;


     { ------------
        NET
       ------------
     }
      function   send_PLN       (FPL: PPLN; adr: TNETadr; wait: bool): bool; far;
      function   distribute_PLN (FPL: PPLN; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;

      procedure  _pkt_PLN (PLN: PPLN); far;
      procedure  _ack_PLN (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;



     { ------------
        PLAN/FPL4
       ------------
     }
      procedure  update_PLN_to_FPL4 (const PLN: DPLN; var FPL: DFPL4);
      procedure  code_PLN_to_FPL4   (const PLN: DPLN; var FPL: DFPL4);


      const  p_zarad_PLN_FPL4 : pproc_p = nil;

      function  _zarad_PLN (PLN: PPLN; _send: bool; _src: fdp_src; _fpl4: bool): bool;
      function  zarad_PLN  (PLN: PPLN; _stat: string; _send: bool; _src: fdp_src): bool;

      (*
      type      T_add_PLN = procedure (PLN: PPLN; check_par: word; var res: string; var ires: int);

      procedure _add_PLN (PLN: PPLN; check_par: word; var res: string; var ires: int);
      const     p_add_PLN : T_add_PLN = _add_PLN;

      {type      Tprocess_pnd_PLN = function (fn: string; all: bool): bool;
      function  _process_pnd_PLN (fn: string; all: bool): bool;
      const     p_process_pnd_PLN : Tprocess_pnd_PLN = _process_pnd_PLN;

      procedure pozri_spracovanie_PLN;
      procedure save_pend_PLN (data: pchars; size: word);
      procedure process_pended_PLN(all: bool);
      *)
