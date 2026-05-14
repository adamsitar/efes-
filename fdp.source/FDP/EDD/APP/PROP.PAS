(*-------------------------------------------------------------------*)
(* Prop  - zatial neschvalene plany                                  *)
(* 1992,94                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Prop;


interface


    uses  TypeDef, BGIgraph,
          Events, Views, Button, Scroll,
          Board,
          _FDP_def,
          _FPL,_STRIP;


    const clPROP_TABLET = clBUTTON_COLOR;

          dx_PROP = dx_fstrip; {742;}
          dy_PROP = dy_strip2;  {49;}

          y0_winPROP = 20;
          y1_winPROP = {$IFNDEF EDD_20} 156 {$ELSE} 180 {$ENDIF};


    const PROP_TABLET_REINIT: bool = true;    { prepocitat polozky na tablete }

    type  PPropButton = ^TPropButton;
          TPropButton = object(TDialogButton)
            procedure  _do_it(var _Event: TEvent); virtual;
          end;

    type  PwinPROP = ^TwinPROP;
          TwinPROP = object(TStripBoard)

            btTitle   : PButton;
            reg       : TRegion;


            is_to_ack : bool;
            prop_cFPL_top,prop_mFPL_top,prop_oFPL_top : int;


            constructor Init(_Owner: PGroup);
            procedure   HandleEvent(var _Event: TEvent); virtual;

            procedure   Draw; virtual;

            procedure   ActiveOn; virtual;
            procedure   ActiveOff; virtual;

            procedure   reinit_;

          { interface pre Data: zaradenie stripov }
            public
            procedure   add(_iFPL: PSTRIP; _ind: int); virtual;
            procedure   del(_iFPL: PSTRIP; _ind: int; _zrus: bool); virtual;

          { pre scroll }
            procedure   item_list(i, x,y: int; b: bool); virtual;
            function    call_user_handler: bool;

          { pre seba }
            function    is_ack  (_pos: int): bool;
            procedure   accept  (_pos: int);
            procedure   decline (_pos: int);

            procedure   accept_FPL  (const PROP_FPLs,ACC_FPLs: P_OFPL; _pos: int; var _top: int);
            procedure   decline_FPL (const PROP_FPLs: P_OFPL; _pos: int; var _top: int);

          { interface pre GUI }
            public
            procedure   zapni;
            procedure   vypni;

            procedure   check;  { vola GUI... }
          end;


    var   winPROP: PwinPROP;



implementation


uses {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF}, SVGA,
     graph_h, {$IFDEF SPEA} SPEA, {$ENDIF}
     keyb, mem, str0, bios,
     Menus, help_def, Help,
     CMs, CM,
     {$IFDEF SECTORS}    Sector,
     {$ENDIF}
     {$IFDEF FPL0}       _FPL_def, _FPLc, _FPLm,
     {$ENDIF}
     {$IFDEF TABLET_ZAM} _ZAM,
     {$ENDIF}
     {$IFDEF TABLET_PRS} _PRS,
     {$ENDIF}
     ACC, GUI;


{$I prop_tit.h} { init, draw }
{$I prop0.inc}  { init, draw }
{$I prop1.inc}  { addE,...   }
{$I prop2.inc}  { prepinanie medzi PROP a ACC }


{ ----------------------------------------------------------------
  obsluha
  ----------- }

procedure TwinPROP.HandleEvent(var _Event: TEvent);
    var   iFPL : PSTRIP;
          ind,stl,rdk : int;
          NDB  : string;

    procedure decode_mail__iFPL_ind(var _Event: TEvent; var iFPL: PSTRIP; var ind: int);
       var    p: pointer;
       begin
         with _Event do p:= Box;
         move(p^,iFPL,sizeof(PSTRIP)); incptr(p,sizeof(PSTRIP));
         move(p^,ind,sizeof(int));
         ClearEvent(_Event)
       end;

    begin

     {$IFDEF MAPY}
      if (PLANZET_MAPA) then Exit;
     {$ENDIF}

      inherited HandleEvent(_Event);

      if (_Event.What and evMessage<>0) then
          case _Event.Command of

          { vypis planu }

            cm_add_PROP_PLAN : begin
                                decode_mail__iFPL_ind(_Event, iFPL,ind);
                                add(iFPL,ind)
                              end;

            cm_chg_PROP_PLAN : begin
                                decode_mail__iFPL_ind(_Event, iFPL,ind);
                                chg(iFPL,ind)
                              end;

            cm_del_PROP_PLAN : begin
                                decode_mail__iFPL_ind(_Event, iFPL,ind);
                                del(iFPL,ind,true)
                              end;

            cm_clr_PROP_PLAN : begin
                                decode_mail__iFPL_ind(_Event, iFPL,ind);
                                del(iFPL,ind,false)
                              end;

          { prepinanie okien }
            cm_PROP_clicked :
               begin
                 if not active then
                    begin
                      zapni;
                      Mail(winACC,hl_zap_winPROP, one,nil,0) { ziadost o vypnutie winACC }
                    end
                 else begin
                        vypni;
                        Mail(winACC,hl_vyp_winPROP, one,nil,0) { ziadost o vypnutie winACC }
                      end
               end;

             cmScrollItemClicked,
             cmScrollItemEntered : call_user_handler

            else Exit
          end { case }

        else Exit;
      ClearEvent(_Event)
    end;

{
  Generovanie menu pre spracovanie FPL
}
function TwinPROP.call_user_handler: bool;
   var   M    : PWinMenu;
         E    : TEvent;
         iFPL : PSTRIP;
         FPL  : pointer;
         idn  : string;
         _pos,
         ind, x,y : int;
   begin
     if (top<0) or (pos<0) then Exit;

     iFPL:= FPLs^[pos]^.iFPL;
     ind := FPLs^[pos]^.ind;
     FPL := iFPL^.ap^[ind];
     idn := iFPL^.get_id(FPL);

     get_pos_xy(pos, x,y);
     M   := WinMenu(' '+cut_(idn)+' ',hlpmnuPROPOSED_STRIP,
                     Item(tit_ACC, cm_PROP_ACC,
                     Item(tit_DEC, cm_PROP_DEC,
                     nil ) )
                    );
     M^.MoveRel(x+15-M^.x0,y+30-M^.y0);
     RunMenu(M,E);
     Dispose(M,Done);

   { vyhladanie planu letu pre pripad, ze by sa zmenilo poradie }
     call_user_handler:= false;
     ind:= iFPL^.find_id(idn); {find_FPL(FPL);}
     if ind<0 then Exit;
     _pos:= find(iFPL, ind);
     if (_pos<0) or (top<0) then Exit;

   { spracovanie planu letu }
     call_user_handler:= true;
     if ((E.What and evMessage) <> 0) then
        case E.Command of
          cm_PROP_ACC  : accept (_pos);
          cm_PROP_DEC  : decline(_pos);
          else call_user_handler:= false
        end
     else call_user_handler:= false
   end;

end.