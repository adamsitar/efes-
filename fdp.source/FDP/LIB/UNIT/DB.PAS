(*-------------------------------------------------------------------*)
(* modul pre index-sekvencnu databazu                                *)
(* (c) Ales Kosice 1994  (ab)                                        *)
(* DB 1.0 ( 14-16.11.1994 }                                          *)
(*-------------------------------------------------------------------*)
{$I db.doc}
{$I dbase.doc}

{$I comp.h}

{$IFOPT I+} {$DEFINE IPLUS} {$I-} {$ENDIF}
{ DEFINE DB_LOCK}    { zamknutie suborov }


unit DB;


interface


    uses   TypeDef,
           dyn_zoz,
           Objects;


    { -----------------------------------
       Objekt pre DB
      ----------------------------------
    }

    const cfg_DB_RWClose = 'DB-RW-CLOSE';
          DB_RWClose: bool = false {true};
          NOSAVE: bool = false;  { ak sa seka IPX a disk, nastavi sa }


    {$I DB.h}   { Objekt pre DB LETVIS    }
    {$I DBF.h}
    { I DBASE.h}

    {$I DB_func.h}


    procedure indicate_db (is: int);
    const     p_indicate_db : p_proc_indicate_process = nil;


implementation

uses  Crt,DOS,BIOS,_Check,IO,SVGA,BGIgraph,
      keyb,mouse,str0,math,mem,msg,mess,utime;


procedure indicate_db (is: int);
    begin
      if p_indicate_db<>nil then proc_indicate_process(p_indicate_db)(is)
    end;

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                       €
€ DBFDP                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{$I DB_0.inc}
{$I DB_1.inc}
{$I DB_2.inc}

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                       €
€ DBASE                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{$I DBF_0.inc}
{ I DBF_3.inc}
{ I DBASE.inc}


{$IFDEF IPLUS} {$UNDEF IPLUS} {$I-} {$ENDIF}

begin
 DB_RWClose:= read_cfg_bool(SYSTEMcfg,cfg_DB_RWClose,DB_RWClose);
end.
