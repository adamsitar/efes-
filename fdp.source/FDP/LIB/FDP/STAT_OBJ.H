     type   PIButton = ^TIButton;
            TIButton = object(TFButton)
              click_and_hide : bool;

              check_adr : pointer;
              en_bool   : bool;

              constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _click, _ck,_ct,_bk: byte;
                               _check_adr: pointer; _en_bool: bool;
                               var hi_: int; _hide: bool
                              );
              procedure   Reinit(x,y,dx,dy: int); virtual;

              procedure   check; virtual;
            end;


    { ----------------------------------
       TimeOut button
      ..................................
    }
     {$IFDEF EXTERNAL_NET}
      type   PTimeOutExtButton = ^TTimeOutExtButton;
             TTimeOutExtButton = object(TIButton)
               p_ext: PO_EXT;

               constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                                _kbHot: char; _cmXXXX: word; _title: string;
                                _click, _ck,_ct,_bk: byte;
                                _p_ext: PO_EXT;
                                var hi_: int; _hide: bool
                               );
               procedure   check; virtual;
             end;
     {$ENDIF}


    { ----------------------------------
       Casovy button
      ..................................
    }
     type   PTButton = ^TTButton;
            TTButton = object(TIButton)
              lastTime       : real;

              constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _click, _ck,_ct,_bk: byte;
                               _check_adr: pointer; _en_bool: bool;
                               var hi_: int; _hide: bool
                              );
              procedure   Idle(var _Event: TEvent); virtual;
              procedure   HandleEvent(var _Event: TEvent); virtual;
              procedure   Reinit(x,y,dx,dy: int); virtual;
            end;


    { ----------------------------------
       Stavovy button
      ..................................
    }
     type   PSButton = ^TSButton;
            TSButton = object(TIButton) { TTBu... }

              bt_vis : pbool; op_vis : bool;
              bt_act : pbool; op_act : bool;

              constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _click, _ck,_ct,_bk: byte;
                               _bt_vis : pbool; _op_vis : bool;
                               _bt_act : pbool; _op_act : bool;
                               _check_adr: pointer; _en_bool: bool;
                               var hi_: int; _hide: bool
                              );

              procedure  Draw; virtual;
              procedure  HandleEvent(var _Event: TEvent); virtual;
              procedure  check; virtual;

              procedure  parameters (_bt_vis : pbool; _op_vis : bool;
                                     _bt_act : pbool; _op_act : bool
                                    );
            end;


     const  maxStatusIndicators = 20;
            StatusIndicators    : byte = 0;

     type   TStatLine = array[0..maxStatusIndicators-1] of PButton;
     var    StatLine : TStatLine;

     procedure addStatIndicator(p: PButton);
