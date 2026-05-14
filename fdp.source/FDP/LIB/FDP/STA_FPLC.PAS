{ תתתתתתתתתתתתתתתתתתתתתתתתת
   (c) ALES 1998,99  Kosice
  תתתתתתתתתתתתתתתתתתתתתתתתת
}

{$I comp.h}


unit STA_FPLc;


interface


    uses   TypeDef,
           {$I unit_gr.h}, db,
           {$I unit_oop.h},
           FIR_def, _L4_def, _MTK_2, NET_def,
           Bod_def, Body,
           STA_def,
           _FDP_def, _FPL_def,
           _FPLc, _FPL4;


    {$IFDEF STATISTIKA_PRELETY}
     const IS_STA_FPLC : bool = true;

     {$I _fps_title.h}
     {$I _fps_plan.h}
     {$I _fps_func.h}
    {$ENDIF}


implementation

uses  bios, dos, _check, mouse, math, mem, io, str0, utime, sets, mess, msg, keyb, prnt,
      Kody, _NET,
      Archiv,
      FDP_msg, FDP_func, FDP_fun2,
      FDP_scrl{,
      Statistika};


{$IFDEF STATISTIKA_PRELETY}

 const p_sta_dbscroller : PScrollDB_FDP = nil;
       _p_handle_event_STATISTIKA : p_proc_handle_object_event = nil;

 {$I _fps.cod}
 {$I _fps.inc}
 {$I _fps.drw}
 {$I _fps.prn}
 {$I _fps_export.inc}
 {$I _fps_ihandle.inc}
 {$I _fps_prehlad.inc}
 {$I _fps_handle.inc}
 {$I _fps_functions.inc}
 { I _fps_archiv.inc}

 procedure initializacia;
     begin
       write('Initialize flight statistics... ');

       _p_save_STA_FPLC:= p_save_STA_FPLC;
       p_save_STA_FPLC:= @zarad_do_statistiky;

       _p_handle_event_STATISTIKA:= p_handle_event_STATISTIKA;
       p_handle_event_STATISTIKA:= @_handle_event_STATISTIKA;

       {kontrola_archivu;}
       writeln('Done.')
     end;

begin
 initializacia;
 {$ENDIF}
end.
