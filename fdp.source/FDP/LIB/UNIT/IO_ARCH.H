     function  comp_time_FileAttr (f1,f2: PFileAttr): bool; far;
     function  comp_fn_FileAttr   (d1,d2: PFileAttr): bool; far;

     function  najstarsi_subor (Path,Name: string): string;
     function  najmladsi_subor (Path,Name: string): string;
     function  dalsi_subor     (path,name, iname: string; smer: int): string;

     procedure zmaz_najstarsi_subor (Path,Name: string);
     procedure zmaz_stare_subory    (Path,Name: string; pocet_hodin: longint);

     function  vytvor_novy_subor    (Path: string): bool;
     procedure zapis_text_do_subora (fn,s: string);

     procedure check_directories (pch: PPChars; max: int);
     procedure check_files       (fn, err: string; _halt: bool);



     const   archREC       = #255;
             archUNPROC    = '-';
             archNET       = 'N';
             archED        = 'E';

             arch_PKT_REC  = {$IFDEF A36YKA} 'ú' {$ELSE} 'ù' {$ENDIF}+archREC;
             arch_PKT_RECU = {$IFDEF A36YKA} 'ú' {$ELSE} 'ù' {$ENDIF}+archUNPROC;
             arch_PKT_RECN = archNET+{$IFDEF A36YKA} 'ú' {$ELSE} 'ù' {$ENDIF};
             arch_PKT_RECE = archED +{$IFDEF A36YKA} 'ú' {$ELSE} 'ù' {$ENDIF};

             archSEND      = ' ';
             arch_PKT_SEND = ' '+archSEND;
             arch_PKT_SENN = archNET+archSEND;

             archSYS       = 'þ';
             archMESS      = '>';
             archERR       = '?';

             arch_SYS      = archSYS+ ' ';
             arch_MESS     = archMESS+' ';
             arch_ERR      = archERR+ ' ';

             archive_COM     : bool = false;  { nahravat vsetky data este do jedneho subora ? }
             cfg_archive_COM = 'COMMON ARCHIV';



     procedure archive_err(fn, err: string);

     const     _another_line_err_log: bool = false;
     procedure _write_err_log(s: string);
     procedure write_err_log(s: string);

     procedure archive_data(_path,_name: string; data: PBytes; pocet: long; ident: string; is_utc, is___: bool);
