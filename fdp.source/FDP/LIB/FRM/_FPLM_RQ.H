       {
        ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
        €                      €
        € TFPL_REQ             €
        €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
       }

 type   PREQ_FPL = ^TREQ_FPL;
        TREQ_FPL = object(TmFPLform)

          FPL,REQ : PDmFPL;

          p_dla   : pointer;
          p_ack   : pointer;
          p_dcl   : pointer;
          p_chg   : pointer;

          constructor Init(var _x,_y,  _mode: int;
                           _title: string;

                           _FPL,_REQ : PDmFPL;

                           _p_dla,_p_ack,_p_dcl,_p_chg,
                           _handle_rqst : pointer;
                           _beep        : bool;

                           _hlpXXX      : Pchar     { ukazovatel na help  }
                          );

          destructor  Done; virtual;

          procedure   Idle(var _Event: TEvent); virtual;
          procedure   HandleEvent(var _Event: TEvent); virtual;

         {$IFDEF AIRBASE}
          procedure   init_buttons(x,y: int); virtual;
         {$ENDIF}

         {$IFDEF MACC}
          procedure   init_buttons(x,y: int); virtual;
          procedure   update_formular; virtual;
         {$ENDIF}

          procedure   handle_rqst(_rqst_res: Trqst); virtual;

          procedure   spracovany_plan(plan: pointer); virtual;
        end;
