{‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
 €                      €
 € TREQ                 €
 €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TFDP_REQ.Init(var _x,_y,  _mode: int; _title: string;
                          _itemd: PForms; _items: byte;

                          _tit : byte;            { vypisovat title pre item ked, tak a ako ? }
                          _inc_dx,_inc_dy,        { len ak title = 1 (bude sa vypisovat dole) }
                          _dx_h, _dy_h: int;

                          _adr_var     : pointer; { adresa premennej, kam nacitat data }
                          _adr_data    : pointer;
                          _rec         : Pplan_rec;

                          _chg_data    : PPLAN_zmeneny;

                          _init_form   : pointer; { inicializacia dat   }
                          _image_form  : pointer; { vykreslenie ciar    }
                          _check_func  : pointer; { kontrola regularity }
                          _handle_rqst : pointer; { obsluha vysledku    }
                          _disp_proc   : pointer;
                          _beep        : bool;

                          _hlpXXX      : Pchar;    { ukazovatel na help  }

                          _copy,_clear,_pole_en: bool
                         );
      begin
        inherited Init(nil,  _x,_y,_mode,  kbNoKey, cmNil,
                       _title, _itemd, _items,
                       clBUTTON_COLOR,cfText,clGR1,cfActT,
                       _tit, _inc_dx,_inc_dy,nil, _dx_h,_dy_h, 0,0,
                       _adr_var, _adr_data, _rec, false,
                       nil, _chg_data,
                       _init_form, _check_func, nil {_done_form},
                       _image_form, nil{_handle_event},
                       _hlpXXX,
                       _copy,_clear,_pole_en
                      );
        win^.btTitle^.cmXXXX:= cmDefault;
        disp_proc  := _disp_proc;
        handle_rqst:= _handle_rqst;
        rqst_res   := _;
        beeping    := _beep
      end;


procedure TFDP_REQ.HandleEvent(var _Event: TEvent);
    var   _Ev : TEvent;
    begin
      inherited HandleEvent(_Event);

      if      ((_Event.What and evMessage) <> 0)
          and (   (_Event.Command = cmREQ_DLA)
               or (_Event.Command = cmREQ_ACK)
               or (_Event.Command = cmREQ_CHG)
               or (_Event.Command = cmREQ_DCL)
              )
                then
         begin
           Ev:= _Event;
           if call_check_func(_Event) then
              begin
                case _Ev.Command of
                  cmREQ_DLA : rqst_res:= dla;
                  cmREQ_ACK : rqst_res:= ack;
                  cmREQ_CHG : rqst_res:= chg;
                  cmREQ_DCL : rqst_res:= dcl
                end;
                if handle_rqst<>nil then
                   if adr_var<>nil then Tproc_rp(handle_rqst)(rqst_res,adr_var)
                   else Tproc_r(handle_rqst)(rqst_res);
              end
           if disp_proc<>nil then proc__adr_var(disp_proc,adr_var)
         end
    end;
