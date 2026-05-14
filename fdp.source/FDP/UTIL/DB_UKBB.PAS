{$I comp.h}

uses bios, typedef, math, str0, io, db, dos, utime, keyb, crt,
     _l4_def, archiv, bod_def, body, kody,
     _FDP_def, _FPL_def, NET_def, _MTK_2,
     _FPL4, _FPLC, _FPLM, _PLN, STA_FPLC;

var  s: string;


{$I arc_format.inc}         { Kontrola integrity archivnych suborov }

{$I _FPLc.cod}
{$I _FPLc_archiv.inc}

{$I _FPL4_plan.cod}
{$I _FPL4_archiv.inc}

{$I _FPS.cod}
{$I _FPS.inc}
{$I _FPS_archiv.inc}

{$I _PLN_plan.cod}
{$I _PLN_plan.inc}
{$I _PLN_archiv.inc}

(*
{$I _FPLm_plan.cod}
{$I _FPLm_archiv.inc}

{$I _PRS_plan.cod}
{$I _PRS_archiv.inc}
*)

begin
  kontrola_archivu_FPLC(DB0, db0_cFPL_RIADKOV,@_decodeDB0_FPLC);
  kontrola_archivu_FPL4(DB0, db0_FPL4_RIADKOV,@_decodeDB0_FPL4);
  kontrola_archivu_FPS (DB0, db0_FPS_RIADKOV, @_decodeDB0_FPS);
  kontrola_archivu_PLN (DB0, db0_PLN_RIADKOV, @_decodeDB0_PLN);
  {kontrola_archivu_FPLM;
  kontrola_archivu_PRS;}

  writeln;
  writeln('LETVIS FDP utility to transformate FDP''s databases format.');
  writeln('Copyright by ALES (c) 1989-1999.');
end.

{comp.h pre "db_ukbb"}

{$DEFINE DEBUG}
{$DEFINE POKUS}

{$DEFINE UK}
{$DEFINE UKBB}
{$DEFINE ENGLISH}

{$DEFINE BGI}

{$I comp_exe.h}


{$DEFINE RLP}

{$DEFINE FDP}        {$DEFINE RLP}
{$DEFINE ATCA}       {$DEFINE RLP}
{$DEFINE ACC}

{$DEFINE UKBB}
{$DEFINE KIEV}

{$DEFINE RUSSIAN}
{$DEFINE A36YKA}

{$DEFINE L4444M}
{$DEFINE DATA_OB}
{$DEFINE GOST}
{$DEFINE TSGA}


{$DEFINE FPL4}
{$DEFINE FDR}

{ DEFINE RPL}

{$DEFINE PLN}

{$DEFINE FPL0}
{$DEFINE FPLC_L}
{$DEFINE FPLM_L}
{$DEFINE FPLO}

{$DEFINE PRS}


{$DEFINE STATISTIKA}
{$DEFINE STATISTIKA_PRELETY}


{$DEFINE DATA_BIN}
{$DEFINE DB_BIN}
{$DEFINE NET}
{$DEFINE RDP}


{$I comp_net.h}
{$I comp_ext.h}
{$I comp_fdp.h}

