(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 4.0                                              *)
(* (c) Ales Kosice 1997  (ab)                                        *)
(* Priestory                                                         *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}

{ Povodny algoritmus pocital s tym, ze NOTAMY sa poslu len raz.
  Pre taketo spracovanie je nutne urcit spravny kluc NOTAMu,
  aby sa vedel zaradit do databazy spravneho mesiaca.
  Kluc bud posle NOTAM spracovajuca stanica, alebo si ho
  kazda vypocita, co moze zdrzat (format... prehladania db)

  Teraz sa pocita s tym, ze NOTAMy s platnostou ce mesiac sa
  opakuju kazdy mesiac. Nepocita sa so stavom spracovania NOTAMu,
  zobrazuju sa vsetky. Triedia sa podla kluca notamu.
}

{ DEFINE ALL_NOTAM}

unit _NOTAM;


interface


    uses  TypeDef, DB, sets,
          {$I unit_gr.h},
          {$I unit_oop.h},
          {$I unit_net.h},
          {$I unit_map.h},
          _MTK_2, _L4_def, _FDP_def, Lists;

    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € NOTAMY                      €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

     const  NOTAMi = 'NOTAM';
            NOTAMN = 'NOTAMN';
            NOTAMC = 'NOTAMC';
            NOTAMR = 'NOTAMR';


    {$IFDEF NOTAM}
      {$I _NOTAM_cnst.h}
      {$I _NOTAM_data.h}
      {$I ..\fdp\_NOTAM_func.h}
      {$I ..\frm\_NOTAM_frm.h}
    {$ENDIF}


implementation

uses  BIOS, _Check, IO,
      keyb, mouse, str0, mess, utime, math, sort, prnt, msg,
      Vypocty, Archiv,
      Body, FDP_func,
      form_SYS,
      FIR_def,
      FDP_msg, FDP_scrl, FDP_edit
      {$IFDEF ARCHIVE_DAR}, DAR_arch  {$ENDIF}
      ;


{$IFDEF NOTAM}
 {$I _NOTAM.cod}
 {$I _NOTAM.vyp}
 {$I _NOTAM.inc}
 {$I _NOTAM.drw}
 {$I _NOTAM.prn}
{$ENDIF}

end.