(*-------------------------------------------------------------------*)
(* IO  2.0                                                           *)
(* 1995                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I-}

(*{$IFDEF SERVER}
 {$X+,I-,S-,P-,F+,O-}
 {$C FIXED PRELOAD PERMANENT}
{$ENDIF}()
*)


unit IO;

interface


     uses   TypeDef,
            DOS;

     const  lst_posledna        = -100;   { najma pre lists }

            lst_od_poslednej    = -111;
            lst_vsetky_polozky  = -112;
            lst_aspon_1_polozka = -113;

            lst_cely_riadok     = -121;
            lst_cely_riadok_    = -122;

            io_intr_by_user     = $7FFF; { aby korespondovalo s cchybovymi kodmi, predtym -1 zatvorilo okno }


            {$I io.h}

     const  {$IFDEF DEBUG}
             path_B = '\xe\';
             path_A = '\xe\d\';
            {$ELSE}
             path_A = '.\'; { ! cesta musi byt relativna kvoli roznym instalaciam a odosielaniu suborov }
            {$ENDIF}


     const  pathARCH       = 'ARCHIV\';
            path_ARCHIVES  = path_A+'ARCHIV\';

            pathTMP        {: PathStr} = path_A+'TMP\';
            extTMP         = '.tmp';
            {pathARCH_TMP   : PathStr = path_ARCHIVES+'TMP\';}



     const  DataAttr = ReadOnly+{faHidden+faSysFile+}Archive;

     function  isFileAttr (DirInfo: SearchRec; Attr: word): bool;

     function  GetDirF_(Path: string; Attr: word; p_filter: PBFunc_s): int;
     function  GetDirF (Path: string; Attr: word): int;
     function  GetDir_ (Path: string; var Dir: PDir; Attr: word; var Files: int; p_filter: PBFunc_s): int;
     function  GetDir  (Path: string; var Dir: PDir; Attr: word; var Files: int): int;
     procedure FreeDir (var Dir: PDir; var Files: int);

     function  GetNmbOfFiles (Path: string): int;
     function  GetDirFiles   (Path,Name: string; var Dir: PDir; var Files: int): int;
     procedure FreeDirFiles  (var Dir: PDir; var Files: int);


    { chyby
    }
     function  IOError: bool;
     function  is_IOError(kde: string): bool;
     procedure ResetIOError;
     function  ErrorMessage(ErrorCode: word; FileName: string): string;


     function  drive_ind(dir: string): int;

    { modifikovane standartne funkcie
    }
     function  _Exists (Path: string; Attr: Word; var F: SearchRec): byte;
     function  Exists  (FileName: string): byte;
     function  FExists (FileName: string): byte;

     function  GetFname(fname, fpath, fext: string): string;
     function  _GetFTime(FN: string): long;
     procedure _SetFTime(FN: string; T: long);
     procedure _UpDateFTime(FN: string);

     function  _filesize(name: string): long;
     procedure _mkdir(s: string);


    { nacitanie
    }
     procedure _BlockRW (RW: byte; var f: File; var buf; count: word; var res: word);
     function  ReadFile (var p: pointer; var size: long; fname: string): bool;


    { "nc"
    }
     function  FindFile(path,fn: string): string;

     procedure Del     (fn: string);
     function  DelFile (fn: string): int;
     function  RenFile (fnp, fnn: string): int;

     function  MoveFile(oldf, newf: string): int;
     function  MoveDir (dirfnp, dirfnn: string): int;

     function  CopyFileI(FN1,FN2: string; _pos: long; _append, _main: bool): int;
     function  CopyFile (FN1,FN2: string): int;


    { zalohovanie
    }
     function  get_ARCHfn(min: word): string;
     function  decode_date_fn(s: string): string;

     function  BackupFile_(path: string; dest: string): int;
     function  BackupFile (path: string): int;

     procedure save_cislo(fn: string; cislo: word);
     function  read_cislo(fn: string): word;


     {$I sys_cfg.h}
     {$I io_cfg.h}
     {$I io_arch.h}


implementation

uses  BIOS, keyb, mem, math, utime, str0, mess, sort, _check, sets, msg;


{$I io_err.inc}
{$I io_dos.inc}
{$I io_nc.inc}
{$I io_nu.inc}
{$I io_dir.inc}

{$I io_arch.inc}

{$I err_log.inc}
{$I io_cfg.inc}


{$IFDEF FDP}
begin
  {read_cfg_str(SYSTEMcfg, cfgTMP_DIR, pathTMP);
  if pathTMP[length(pathTMP)]<>'\' then pathTMP:= pathTMP+'\';}
  _mkdir(pathTMP);

  {pathARCH_TMP:= path_ARCHIVES+getstr(pathTMP,getstritems(pathTMP,['\']),['\']);
  if pathARCH_TMP[length(pathARCH_TMP)]<>'\' then pathARCH_TMP:= pathARCH_TMP+'\';}
  {pathARCH_TMP:= pathTMP+'ARCHIV\';}
  {_mkdir(pathARCH_TMP);}

  archive_COM:= read_cfg_bool(SYSTEMcfg, cfg_archive_COM, archive_COM);

  ResetIOError;
  SaveExit:= ExitProc;
  ExitProc:= @DoneApp;
  write_err_log('System initialized on '+cstr(day,1)+'.'+cstr(month,1)+'.'+cstr(year,1)+', '+TimeToStr2(hour,min,sec,':','.'))
{$ENDIF}
end.