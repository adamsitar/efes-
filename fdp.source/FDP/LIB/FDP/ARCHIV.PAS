(*-------------------------------------------------------------------*)
(* LETVIS FDP  NET - archivacia sprav                                *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{
  Pozn.: stripy a meteor-data: synop a metar sa ukladaju do
         hodinovych suborov, inak do dennych suborov.
         U pana jest taka konvencija, ze hodzinovie subory konca
         na oznacenie hodiny a drzia sa v archive 24 hodin, inak
         maju pismena a drzia sa 1 den.

  Pocitam s tym, ze na HDD je len FDP/iii, inak pri kontrole
  check_HDD sa moze program zacyklit...

  Zisiel by sa tu objektik...

}

{$I comp.h}


unit Archiv;


interface

     uses   TypeDef,
            DOS, IO, utime,
            NET_def;

     const  cfg_ArchDays   = 'ARCHIVE DAYS';
            cfg_ArchMonths = 'ARCHIVE MONTHS';

            _ArchDays      = 31;

            ArchDays   : word = _ArchDays {$IFDEF SERVER} *3 {$ENDIF};   { pocet dni na archivovanie nahravok   }
            lo_ArchDays    = 7;
            hi_ArchDays    = 400;

            ArchMonths : word = 12 ;
            lo_ArchMonths  = 1;
            hi_ArchMonths  = 13;

            ArchHours  : byte = 24 ;

            is_cfgArch : bool = false;

            minSpace   : word = 15;                                      { minimalny volny priestor na HDD v MB }


     {$I arch_title.h}
     {$I arch_cnst.h}
     {$I arch_directories.h}


     var        archiv_HODfn: str12;

     procedure  get_plan_date(var d: Tdate; s: string);
     function   get_plan_date_real(s: string): real;

     function   get_PLANfn  (den,mes,rok: word): string;
     function   get_PLANhod (den,mes,rok, hod: word): string;

     function   get_prev_HODfn(f_n: string): string;

     function   get_ARCHIVfn (path: string): string;
     function   get_DBfn   (date: TDate; path: string; ext: string): string;
     function   get_DBfn_  (den,mes,rok: word; path: string; ext: string): string;
     function   get_DBfn__ (Path,Name, AltFN: string): string;

     function   comp_fd1(p1,p2: PFileAttr): bool; far;
     function   comp_fd2(p1,p2: PFileAttr): bool; far;

     function   get_ARCH_FN_(path, ext: string; p_filter: PBFunc_s; title: string): string;
     function   get_ARCH_FN (path, ext, title: string): string;
     function   get_PPL_FN_ (path, ext: string; p_filter: PBFunc_s; title: string): string;
     function   get_PPL_FN  (path, ext, title: string): string;

     function   decode_archived_date (date: string; podla_mena: bool; var r: word; var m,d,h: byte): bool;


     procedure  archivuj_subory (path,mask, arch : string;
                                 podla_mena : bool;       { ak nie, tak podla casu vytvorenia }
                                 archive_by : TypeOfArchive
                                );

     procedure  uprac_archiv    (path,mask    : string;
                                 podla_mena   : bool;       { ak nie, tak podla casu vytvorenia }
                                 archive_by   : TypeOfArchive;
                                 archive_then : Tarch_nmb
                                );

     procedure  archivuj_stare_plany;


    { archivovanie textu
    }
     type SFunc_si = function(S: pointer; I: int): string;
     procedure  save_text(path: string;
                          S: pointer;     { ukazovatel na data s typom string }
                          R: int;         { pocet riadkov }
                          get_s: pointer  { @SFunc_si }
                         );


    { zalohovanie, zatial natvrdo na a:\
    }
     procedure  archivuj_data (_path,_name: string; data: PBytes; pocet: long; ident: string; is_utc, is___: bool);
     procedure  zalohuj_archiv(_path,_name: string; _title,_mess: string; _handler: pointer);


    { konverzia archivu
    }
    (*
     function   addDirExt (dirn,extn: string): string;
     function   konvertovat_archiv (fn: string; attr: byte): bool;
     procedure  konverzia_archivu(path,ext    : string;

                                  resave_p2   : pointer;    { TByFunc_p2 <> nil   }
                                  item_size   : word;
                                  disp_item   : pointer;    { Tproc_p odalokuje nacitany buffer }

                                  riadkov     : byte;
                                  DATAdecode  : pointer
                                 );
    *)

     procedure  check_archiv;

     procedure  archivuj_cmn (s: string);
     procedure  archivuj_cfg (cfg: string);



implementation

uses  BIOS, _Check, Crt,
      str0, keyb, sets, sort, math, mem, msg,
      DB,
      {$I unit_gr.h},
      Events, Dialog, Scroll;


{ Ak sa zmeni konvencia oznacovania suborov,
  treba preskumat archiv_2.inc
}
{$I arc.inc}
{$I arc_directories.inc}    { Spracovanie archivu }
{$I arc_manage_archive.inc} { Presun do archivacnych adresarov a mazanie v nich }
{$I arc_check_archive.inc}
{$I arc_ini.inc}

{ I arc_format.inc}         { Kontrola integrity archivnych suborov }

{$IFDEF FDP}
begin
  scroll.OViewerStreamFile_decode_fn_date:= decode_date_fn;
  init_archiv;
  if is_cfgArch {IFNDEF STATISTIKA} or true {ENDIF} then check_archiv
{$ENDIF}
end.