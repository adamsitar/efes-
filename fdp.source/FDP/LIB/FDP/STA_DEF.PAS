(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 4.2                                              *)
(* (c) Ales Kosice 1993,99  (ab)                                     *)
(* Definicia spolocnych parametrov pre spracovanie statistiky        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit STA_def;


interface


    uses   TypeDef,
           IO, Events, Objects, App,
           _L4_def;


           { referencie na "ext"erne fcie
           }
     const  p_save_STA_FPLC  : PProc_p = nil;
            p_save_STA_FPLM  : PProc_p = nil;
            p_save_STA_ZAM   : PProc_p = nil;
            p_save_STA_QGO   : PProc_p = nil;
            p_save_STA_DVZ   : PProc_p = nil;
            p_save_STA_PRZ   : PProc_p = nil;
            p_save_STA_PRS   : PProc_p = nil;
            p_save_STA_SPR   : PProc_p = nil;

            p_info_STA_FPLC  : PProc   = nil;
            p_info_STA_FPLM  : PProc   = nil;
            p_info_STA_ZAM   : PProc   = nil;
            p_info_STA_QGO   : PProc   = nil;
            p_info_STA_DVZ   : PProc   = nil;
            p_info_STA_PRZ   : PProc   = nil;
            p_info_STA_PRS   : PProc   = nil;

            {p_enabled_modify_STA  : PBFunc_date = nil;}
            p_modify_STA_ZAM      : PProc_date  = nil;


     const     p_handle_event_STATISTIKA : p_proc_handle_object_event = nil;
     function  _handle_event_STATISTIKA (var _Event: TEvent; O: PObject; P: pointer): bool;



implementation

uses  keyb, str0, sets;

function _handle_event_STATISTIKA (var _Event: TEvent; O: PObject; P: pointer): bool;
   var   date: TDate;
   begin
     _handle_event_STATISTIKA:= false;
     if _Event.what=evNothing then Exit;

     if p_handle_event_STATISTIKA<>nil then
        begin
          _handle_event_STATISTIKA:= proc_handle_object_event (p_handle_event_STATISTIKA)(_event,O,P);
          if _Event.what=evNothing then Exit;
        end;
     end;

end.
