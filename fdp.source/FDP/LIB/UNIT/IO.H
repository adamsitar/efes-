     const  NAME       = 8;
            EXT        = 3;
            NAME_EXT   = 12;


     const  IOERR_N            = 'IOERR';      { subor pre ulozenie chyb io }
            SYSERR_N           = 'SYSERR';
            MAX_SIZE_IOERR_FN  = $1024*50;     { max velkost tohto subora }
            MIN_SPACE_HDD      = 5*1024*1024;

            err_log_cfg        = 'err.log';
            err_log_cfg_size   = 1024;

            subdir     = '.';
            prevdir    = '..';
            fn_all     = '*';
            allfiles   = '*.*';


     const  ext_ini    = '.ini';
            ext_kod    = '.kod';
            ext_usr    = '.usr';
            ext_all    = '.*';
            ext_wrk    = '.$$$';

            SYSTEMcfg  = 'system'+ext_ini;
            odd_cfg    = ['=',';'];
            setKomen   = [';','{'];  { komentar   }

     const  another_log_proc : TProc_s = nil;


     type   PFileAttr = ^TFileAttr;
            TFileAttr = record
              attr : byte;
              name : string[NAME_EXT];
              date : long;
              size : long
            end;

           { Pole musi byt typu Pptrs : }
            TDir = array[0..MAX_ARRAY_SIZE div SizeOf(PFileAttr)-1] of PFileAttr;
            PDir = ^TDir;


     var    IOErrorCode: int;

            sPath : PathStr;
            sDir  : DirStr;     { ak su lokalne, nemusi to fungovat korektne }
            sName : NameStr;
            sExt  : ExtStr;


     const  IORES_OK             = 0;
            IORES_FILE_NOT_FOUND = 2;