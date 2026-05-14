(*-------------------------------------------------------------------*)
(* LETVIS FDP - Graphics Users Interface                             *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}


{$IFDEF OPL} {$IFNDEF SAR} {$DEFINE OPL_DATA} {$ENDIF} {$ENDIF}


unit GUI;


interface


    uses  TypeDef,
          BIOS,
          {$I unit_gr.h},
          Events, Objects, Views, Button, Scroll, App,
          _L4_def,
          FDP_scrl,
          _PLAN;


    { I scroll_b.h}   { verzia 3.9 }
    { I dbg_sort.h}


    type  P_GUI = ^T_GUI;
          T_GUI = object({TGroup}TAppGui)

            private
            sirka_prelety : int;    { pomocna premenna pre dx }
            {last_active  : PView;    posledne aktivne okno   }
            _4okno        : PView;

           {$IFDEF FPL}
             mFPL_prel,
             cFPL_prel,
             oFPL_prel : PScrollApp;

             _tab_mFPL,
             _tab_cFPL,
             _tab_oFPL : bool;
           {$ENDIF}


            public
            constructor Init(_Owner: PApp);

            procedure   HandleEvent(var _Event: TEvent); virtual;

            function    reinit_: int;
            procedure   reorganize(_draw: bool);

            private
            function    next_active(P: PView): PView; virtual;
            function    prev_active(P: PView): PView; virtual;
            function    set_active (P: PView): bool;  virtual;
          end;


implementation

uses  _Check, mouse, keyb, math,
      Menus, Dialog, help_def, Help, CM, CMs,
      Hodiny, Status,
      MapyDef, Mapy,
      _FDP_def, _FPL_def,
      _FPL, _FPL4, _FPLc, _FPLm, _FPLms,
      _FDP;


{ I scroll_b.inc}
{ I dbg_sort.inc}

const  tabSIRKA_ITEM = 1 + kod_7a * 8 + 1; { zatial je vsetko natvrdo }
       tabVYSKA_ITEM = 10;

       dxi = 3;
       dyi = 4;

      { prepocet vysky scrollocich zoznamov pre prelety
      }
       dMapaY0 = btHEIGHT + 3;
       dMapaY1 = btHEIGHT + 6;


{$I gui.inc}

procedure T_GUI.HandleEvent(var _Event: TEvent);
    begin
      if isKey(_Event,kbF1) then
         begin
           if last_active<>_4okno then _help(last_active^.hlpXXX)
           else _help(hlpXXX);
           ClearEvent(_Event);
           Exit
         end;

      inherited HandleEvent(_Event);

      case _Event.What of

        evKeyDown:
          case _Event.Key of
            kbTab      : next_active (last_active);
            kbShiftTab : prev_active (last_active)
            else Exit
          end;

        evCommand, evBroadcast:
          case _Event.Command of
          { povel od objektu, ze chce byt aktivny }
            0               : ;

            {$IFDEF MAPY}
             cm_mapa_scroll : set_active(Mapa);
            {$ENDIF}

            {$IFDEF FPL}
             cm_mFPL_scroll : set_active(mFPL_prel);
             cm_oFPL_scroll : set_active(oFPL_prel);
             cm_cFPL_scroll : set_active(cFPL_prel);
            {$ENDIF}

            else Exit
          end

        else Exit
      end; { case }

      ClearEvent(_Event)
    end;


(*var SaveMain : TProc;

procedure check_overlap; far;
    begin
      if @SaveMain<>nil then SaveMain;
      mFPL_prel^.Prekreslit;
      oFPL_prel^.Prekreslit;
      cFPL_prel^.Prekreslit
    end;

begin
  SaveMain:= ACheck;
  ACheck:= check_overlap*)
end. { GUI }