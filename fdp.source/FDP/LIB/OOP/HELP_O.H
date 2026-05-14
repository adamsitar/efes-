     const  fn_hlp_exe  =  pathLST+'help.'+language;
            fn_hlpI_exe =  pathLST+'help-I.'+language;
            fn_hlpC_exe =  pathLST+'help-C.'+language;


     const  hlp_SOH = #2;            { zaciatok a koniec hlavicky }
            hlp_EOH = #2;
            hlp_EOT = #3;            { koniec dokumentu           }
            hlp_NXT = #4;

            hlp_const_h1     = '~';
            hlp_const_h2     = '"';
            hlp_sipka_vpravo = '|';  { normalny znak #27 sposobi Eof(f) pri nacitani }

            hlp_max_lines    = 1000; {3200;}

            hlp_dy0 : int = 0;
            hlp_dy1 : int = 0;

            hlp_cl_tx     = 0;

            {$IFDEF EGAVGA}
             hlp_cl_bg   = lightgray;
             hlp_kb_tx   = yellow;
             hlp_k__tx   = cyan;
             hlp_k__bg   = hlp_cl_tx;
            {$ELSE}
             hlp_cl_bg   = clBUTTON_COLOR+2;
             hlp_kb_tx   = clGRe; {yellow;}
             hlp_k__tx   = clGRc; {cyan;}
             hlp_k__bg   = hlp_cl_tx;
            {$ENDIF}
             hlp_nx_tx   = blue;



     type   PHelp = ^THelp;
            THelp = object(TScrollWin)

              fn : string;
              riadkov : int;

              {$IFDEF HELP_NOEMS}
               strm : PPchars;
               {ap  : array[0..hlp_max_lines-1] of pchar;    odsek s polom pre help }
              {$ELSE}
               stre : PstreamPackedStrings;
              {$ENDIF}

              SOH,EOH,EOT : char;
              max_len     : byte;

              is_help     : bool;
              is_pos_en   : bool;
              empty_en    : bool;      { moze sa zobrazit prazdny ? }
              comment_en  : bool;      { nacita riadok komentaru, ak zacita ';' }
              is_comment  : bool;      { nacita komentar, ak je za udajmi ';' }
              is_comment0 : bool;      { povolenie nacitania komentara len z prvej pozicie }
              is_sorry    : bool;
              dxm,dym     : int;


              constructor Init(_fn: string; _sorry: bool; _hlpXXX: pchar);
              destructor  Done; virtual;

              function    is_to_be_Run: bool; virtual;
              procedure   List;  virtual;
              procedure   HandleEvent (var _Event: TEvent); virtual;

              procedure   item_list (ind, x,y: int; b: bool); virtual;
              procedure   show_help (title: string);
              procedure   help (key,title : string);

              function    put (riadok: string; ind: int): bool;
              function    get (ind: int): string;
              function    items: word;

              function    key_find  (var f: text; key: string; _title: pstring): bool;
              function    key_alloc (var f: text; key: string): bool;
              procedure   key_read  (key: string; var _title: string);
              procedure   key_release;
            end;


     type   PHelpIndex = ^THelpIndex;
            THelpIndex = object(THelp)
              constructor Init;
              procedure   HandleEvent (var _Event: TEvent); virtual;
            end;
