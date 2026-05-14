     function  read_cfg_line(var f: text): string;

     function  __read_cfg_line (fn,key: string;
                                _ind : int;       { index opakovanej prememnnej }
                                _pos : int        { na pozicii v riadku         }
                               ): string;

     function  _read_cfg_line  (fn,key: string; _ind,_pos: int): string;

     function  __read_cfg   (fn,key: string; _pos: int): string;
     function  _read_cfg    (fn,key: string; upcas: bool): string;
     function  _read_cfg_i  (fn,key: string; _ind: int; _pos: int; upcas: bool): string;

     function  read_cfg_str (fn,key: string; var s: string): bool;
     function  read_cfg_str_(fn,key: string; s: string): string;
     function  read_cfg_pch (fn,key: string): pchar;
     function  read_cfg_word(fn,key: string; i: word): word;
     function  read_cfg_real(fn,key: string; i: real): real;
     function  read_cfg_bool(fn,key: string; b: bool): bool;


     function  read_line (var f: text; var s: string; skip: TCharSet; skip_comment: bool): bool;
