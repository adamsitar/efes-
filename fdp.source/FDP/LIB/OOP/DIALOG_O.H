          { --------------------------------------------- }
          { TPrompt                                       }
          { --------------------------------------------- }
    type  { Otazka ano/nie ...                            }
          PPrompt  = ^TPrompt;
          TPrompt  = object(TWindows)

            s     : string;
            mp    : TMess;
            ms    : int;

            cl,bk : byte;
            loops, start_tick: long;
            beep : pointer;

            constructor Ask (var _Event: TEvent; _cmXXXX: word; _title,_s, _nie: string; _cl,_bk: int; _loops: long);
            constructor Init(_cmXXXX: word; _title,_s, _nie: string; _cl,_bk: int; _loops: long);
            destructor  Done; virtual;
            procedure   Draw_; virtual;
            procedure   InitApp2; virtual;
            function    HelpDisplayed(var _Event: TEvent): bool; virtual;
            procedure   Idle(var _Event: TEvent); virtual;
            function    Result(_Event: TEvent): TAnswer;
          end;



          { --------------------------------------------- }
          { TInfo                                         }
          { --------------------------------------------- }
    const archive_info_mess: bool = true;

    type  { Informacia                                    }
          PInfo  = ^TInfo;
          TInfo  = object(TWindow)

            btOK  : PTextIcon;

            mp    : TMess;
            ms    : int;

            cl,bk : byte;
            loops, start_tick : long;
            time_out, res : pbool;
            beep1,beep2 : pointer;

            lmain : bool;
            do_it : pointer; { TBfunc_p }
            data  : pointer;
            check : pointer;

            constructor Init(_title,_btOKtitle: string;
                             _text, _text_p: pointer; _dx,_dy: int;
                             _messp: PMess; _size: int;
                             _cl,_bk: int;
                             _beep1, _beep2: pointer;
                             _loops: long; _time_out, _res: pbool;
                             _start_tick: long; _do_it: pointer; _data : pointer
                            );
            function    HelpDisplayed(var _Event: TEvent): bool; virtual;
            procedure   HandleEvent(var _Event: TEvent); virtual;
            procedure   Draw_; virtual;
            procedure   InitApp2; virtual;
            procedure   LocalMain(var _Event: TEvent); virtual;
            procedure   Run(var _Event: TEvent); virtual;
            procedure   DoneApp2; virtual;
            destructor  Done; virtual;
          end;


          { --------------------------------------------- }
          { TProcess                                      }
          { --------------------------------------------- }

    type  PProcess = ^TProcess;
          TProcess = object(TInfo)
            info,key, sprava : string;
            p_is_done : pbool;

            {items  : int;
            pitem  : pint;}

            constructor Init(_title,_btOKtitle: string;
                             _info, _key: string;
                             _do_it: pointer; _data: pointer;
                             {_items : int; _pitem: pint;}
                             var _is_done: bool
                            );

            destructor  Done; virtual;
            procedure   Idle(var _Event: TEvent); virtual;
            procedure   new_item(_key: string);
          end;

          t_proc_ext_process = function (data: pointer; {item: pint; items: int;} O: PProcess): bool;
          p_proc_ext_process = ^t_proc_ext_process;

          

          { --------------------------------------------- }
          { TMessage                                      }
          { --------------------------------------------- }
    type  { Sprava ...                                    }
          PMessage  = ^TMessage;
          TMessage  = object(TInfo)
             constructor Say (_title: string; _messp: PMess; _size: int;
                              _cl,_bk: int;
                              _beep1, _beep2: pointer;
                              _loops: long; _time_out,_res: pbool;
                              _start_tick: long; _do_it: pointer; _data : pointer
                             );
          end;



          { --------------------------------------------- }
          { Chybove hlasky                                }
          { --------------------------------------------- }
    type  PError  = ^TError;
          TError  = object(TMessage)
             constructor Init(_title: string; _mess: PChar);
             constructor Say (_title: string; _mess: PChar);
          end;


          PPosError  = ^TPosError;
          TPosError  = object(TError)
             constructor Say(_x,_y: int; _title: string; _mess: PChar);
          end;

