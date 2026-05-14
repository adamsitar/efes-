{ ------------------------------
  tabula stripov
  ------------------------------ }

{$I acc3a.inc} { init, done, draw, reinit }
{$I acc3b.inc} { utility }
{$I acc3c.inc} { ADD,CHG,CNL : spracovanie FPL  }
{$I acc3d.inc} { prepinanie lstACC z winACC     }
{$I acc3e.inc} { zmena velkosti a polohy lstACC }
{$I acc3f.inc} { presun lstACC                  }


{ ----------------------------------------------------------------
  obsluha
  ----------- }

procedure TwinACC.HandleEvent(var _Event: TEvent);
    var   iFPL: PSTRIP;
          stl,ind: int;
          cfg_fn,NDB: string;
    begin

     {$IFDEF MAPY}
      if (PLANZET_MAPA) then Exit;
     {$ENDIF}

      inherited HandleEvent(_Event);

      case _Event.What of
        evCommand, evBroadcast:
          case _Event.Command of

          { rekonfiguracia
          }
           cmCFG_SAVED      : begin
                                if not read_mail_s (_Event,cfg_fn) then cfg_fn:= USER_TABLET_CFG;
                                save_tablet_cfg (cfg_fn);
                                Exit
                              end;

           cmCFG_LOADED     : begin
                                if read_mail_s (_Event,cfg_fn) then reinit_tablet (cfg_fn,false);
                                Exit
                              end;


          { vypis planu
          }
            cm_add_ACC_PLAN, cm_chg_ACC_PLAN :
               begin
                 decode_mail__iFPL_ind(_Event, iFPL,ind);
                 add(iFPL,ind,true)
               end;

            cm_del_ACC_PLAN :
               begin
                 decode_mail__iFPL_ind(_Event, iFPL,ind);
                 del(iFPL,ind,true)
               end;

            cm_clr_ACC_PLAN :
               begin
                 decode_mail__iFPL_ind(_Event, iFPL,ind);
                 del(iFPL,ind,false)
               end;


          { scrollovanie zoznamu
          }
            rq_lstACC_zapni  : { ziadost pre winACC, ze lstACC chce byt aktivovane }
               begin
                 with _Event do Move(box^,NDB[0],size);
                 if najdi_skupinu(NDB, stl,ind) then zapni_zoznam(stl,ind)
               end;

            rq_lstACC_zvacsi : { ziadost od lstACC, ze ma malo miesta a potreboval by zvacsit }
               begin
                 zvacsil_sa_zoznam(_Event.From)
               end;

            rq_lstACC_zmensi : { ziadost od lstACC, ze by zahodno zmensit bolo                }
               begin
                 zmensil_sa_zoznam(_Event.From)
               end;

            rq_lstACC_move   :
               begin
                 presun_zoznam(_Event)
               end

            else Exit
          end
        else Exit
      end;

      ClearEvent(_Event)
    end;
