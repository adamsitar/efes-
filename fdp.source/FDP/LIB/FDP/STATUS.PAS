(*-------------------------------------------------------------------*)
(* LETVIS FDP - stavovy riadok pre hlasky                            *)
(* (c) Ales Kosice 1994     (ab)                                     *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}

{$X+,I-,S-,P-}


unit Status;


interface


     uses   TypeDef,
            Events, Views, Button, App
            {$IFDEF EXTERNAL_NET}, _EXT  {$ENDIF}
            ;


     {$IFDEF STATUS}
       {$I stat_obj.h}
       {$I stat_but.h}
       { I stat_app.h}


       procedure STATUS_init(_App: PApp {$IFDEF DATA_WRITTEN_IN_APP}; _AppGui: PAppGui{$ENDIF});
       procedure STATUS_reinit;

       procedure STATUS_show;
       procedure STATUS_hide;

       procedure pozri_indikatory_STATUS;
     {$ENDIF}


implementation

uses  bios, keyb, mouse, math, utime, str0,
      {$I unit_gr.h},
      cms, cm, db,
      Report, _FDP_def

      {$IFDEF NET}, NET_def {$ENDIF}

      {$IFDEF AFTN},               _AFTN {$ENDIF}
      {$IFDEF CONNECT_TO_OPL_EXT}, _OPL  {$ENDIF}
      ;


{$IFDEF STATUS}

 {$I stat_obj.inc}
 {$I stat_app.inc}


 procedure STATUS_reinit;
     var   i: int;
     begin
       for i:= 0 to StatusIndicators-1 do StatLine[i]^.ReInit(0,0,MaxX,MaxY)
     end;

 procedure STATUS_show;
     var   i: int;
     begin
       for i:= 0 to StatusIndicators-1 do StatLine[i]^.show
     end;

 procedure STATUS_hide;
     var   i: int;
     begin
       for i:= 0 to StatusIndicators-1 do StatLine[i]^.hide
     end;

 procedure pozri_indikatory_STATUS;
     const s: byte = 60;
     var   i: int;
     begin
       if sec=s then Exit;
       s:= sec;
       for i:= 0 to StatusIndicators-1 do StatLine[i]^.check
     end;


 procedure indikacia_pkt(is: int; var cntr: int; bt: PFButton);
     begin
       cntr:= N(cntr+is);
       if bt=nil then Exit;
       if cntr>0 then begin if not bt^.visible then bt^.show end
       else begin if bt^.visible then bt^.hide end
     end;

 procedure indikacia_db (is: int); far;
     begin
       indikacia_pkt(is,cntrDB,btDBis);
     end;

 {$IFDEF NET}
  procedure indikacia_net(is: int); far;
      begin
        indikacia_pkt(is,cntrNET,btNETis);
      end;
 {$ENDIF}

 {$IFDEF EXTERNAL_NET}
  procedure indikacia_ext(is: int);
      begin
        indikacia_pkt(is,cntrEXT,btEXTis);
      end;
 {$ENDIF}

begin
 { IFDEF    }
   p_indicate_db := @indikacia_db;
 { ENDIF}

 {$IFDEF NET}
   p_indicate_net:= @indikacia_net;
 {$ENDIF}

 {$IFDEF EXTERNAL_NET}
   p_indicate_ext:= @indikacia_ext;
 {$ENDIF}

{$ENDIF}
end.