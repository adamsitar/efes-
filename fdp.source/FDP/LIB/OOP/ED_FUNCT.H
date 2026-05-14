     procedure clear_form    (_itemd: PForms; _items: byte; _init: PCharSet);
     procedure set_rk        (var erra: string; _erra: string;
                              var errc: int; _errc: int;
                              var ires: int; _ires: int
                             );
     procedure delete_item   (var itemd: TForm);
     function  chg_legal_set (var CharSet: PCharSet; Value: PCharSet): PCharSet;

     function  alloc_form  (items: byte): PForms;
     procedure acpy_form   (itemd1,itemd2: PForms; items: byte);
     function  new_form    (itemd: PForms; items: byte): PForms;
     procedure disp_form   (itemd: PForms; items: byte);
     procedure copy_form   (itemd1,itemd2: PForms; items: byte);

     function  new_editor  (_items,_znakov: byte; _text: byte): PForms;
     procedure disp_editor (itemd: PForms; items: byte);


     function  s_check      (form: PSingleForm; s: Pstring): bool; far;

     function  formular_s   (var _res : string;
                             _max_len : byte;

                             _title   : string;
                             _lst     : PListDesc; { ponuka moznych poloziek }
                             _pos     : int;       { pozicia v polozkach     }
                             _legal   : PCharSet;  { povolene znaky          }
                             _skip    : PCharSet;  { zakazane znaky          }
                             _titpos  : int;       { pozicia popisu          }

                             _s_check : pointer;   { s_check(form: PSingleForm; s: Pstring): bool; }
                             _pswrd   : bool;
                             _upcas   : bool;
                             _init    : bool;

                             _hlpXXX  : Pchar
                            ): bool;
