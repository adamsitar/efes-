     function  load_tlg_editor   (var Ev : TEvent;
                                  E  : PEXTEd;
                                  O  : PO_EXT;
                                  hd : p_type_ext_err_pkt
                                 ): bool; far;

     function  handle_tlg_editor (var Ev : TEvent;
                                  E  : PEXTEd;
                                  O  : PO_EXT;
                                  hd : p_type_ext_err_pkt
                                 ): bool; far;

     function  check_tlg_editor  (E: PEXTEd;
                                  O: PO_EXT;
                                  text_adr: pchar
                                 ): bool; far;
