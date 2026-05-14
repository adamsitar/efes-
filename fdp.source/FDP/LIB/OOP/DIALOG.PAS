(*-------------------------------------------------------------------*)
(* Dialog 1.0                                                        *)
(* 1993,9                                                            *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Dialog;


interface

    uses   TypeDef,
           Events, Views, Button;


    const  waitINFO  : int = 60;
           waitASK   : int = 30;
           waitERR   : int = 30;

    const  max_MessStr = 40;
    type   TMess = array[0..max_MessStr-1] of PChar;
           PMess = ^TMess;

    type   TAnswer   = (ansAno,ansNie,ansZrus);
    const  titAnswer : array[low(TAnswer)..high(TAnswer)] of pchar =
                       {$IFDEF SLOVAK}
                         ('èno','Nie','Zru®');
                       {$ENDIF}

                       {$IFDEF CZECH}
                         ('Ano','Ne','Zru®');
                       {$ENDIF}

                       {$IFDEF ENGLISH}
                         ('Yes','No','Cancel');
                       {$ENDIF}

    {$I dialog_o.h}


    function   Ask  (var _Event: TEvent; _cmXXXX: word; _title,_s, _nie: string; _cl,_bk: int; _loops: long): TAnswer;
    function   Ask2 (_title,_s, _nie: string; _cl,_bk: int; _loops: long): TAnswer;
    function   PosAsk (_x,_y: int; _title,_s, _nie: string): TAnswer;

  { zobrazi okno so spravou vacsou ako jeden riadok
  }
    function   Info_(_title,_btOKtitle: string;
                     _text,_textp: pointer; _dx,_dy: int;
                     _beep: pointer;     { @TBFunc - funkcia pre signalizaciu spravy }
                     _wait: long
                    ): bool;

    function   Info(_title : string;
                    _text,_textp: pointer; _dx,_dy: int;
                    _beep: pointer;     { @TBFunc - funkcia pre signalizaciu spravy }
                    _wait: long
                   ): bool;

  { sprava na jeden riadok
  }
    function   Say (_title: string; _mess: string; _cl,_bk: int;
                    _beep1, _beep2: pointer;
                    _loops: long;
                    _start_tick: long; _do_it: pointer; _data : pointer
                   ): bool;
    function   Say2(_title: string; _mess: string): bool;
    function   Say3(_title: string; data: pchars; size: word): bool;

  { sprava na _size riadok
  }
    function   Say_(_title: string; _messp: PMess; _size: int; _cl,_bk: int;
                    _beep1, _beep2: pointer;
                    _loops: long;
                    _start_tick: long; _do_it: pointer; _data : pointer
                   ): bool;


  { chybove spravy
  }
    function   Err (_title: string; _mess: PChar): bool;
    function   Err2(_title: string; _mess: string): bool;
    function   PosErr(_x,_y: int; _title: string; _mess: PChar): bool;
    procedure  SystemErrorMess(tit: string; tm: bool);


  { vypocet ...
  }
    function  InfoProcess (_title,_btOKtitle: string;
                           _info,_key: string;
                           _do_it: pointer; _data: pointer
                           {_items: int; _pitem: pint}
                          ): bool;


implementation

uses  BIOS, IO, _check,
      str0, math, keyb, mouse, mess, utime, msg, sets,
      graph_h, {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF},
      BGIgraph, SVGA,
      CMs, Scroll;


{$I dialog.inc}
{$I prompt.inc}
{$I info.inc}
{$I process.inc}
{$I message.inc}
{$I errors.inc}


function Ask (var _Event: TEvent; _cmXXXX: word; _title,_s, _nie: string; _cl,_bk: int; _loops: long): TAnswer;
   var   Prompt: PPrompt;
   begin
     Prompt:= New(PPrompt,Ask(_Event, _cmXXXX, _title,_s,_nie, _cl,_bk, _loops));
     Ask:= Prompt^.Result(_Event);
     Dispose(Prompt)
   end;

function Ask2(_title,_s, _nie: string; _cl,_bk: int; _loops: long): TAnswer;
   var   _Event: TEvent;
   begin
     Ask2:= Ask(_Event,cmOK, _title,_s, _nie, _cl,_bk, _loops)
   end;

function PosAsk(_x,_y: int; _title,_s, _nie: string): TAnswer;
   var   Prompt : PPrompt;
         _Event : TEvent;
   begin
     Prompt:= New(PPrompt,Init(cmOK, _title,_s,_nie, clGRe,clBUTTON_COLOR-2,waitASK*18));
     {if ((_x=initX) and (_y=inity)) or ((_x<=0) and (_y<=0)) then Centre
     else} Prompt^.MoveRel(_x-Prompt^.x0,_y-Prompt^.y0);
     Prompt^.Run(_Event);
     PosAsk:= Prompt^.Result(_Event);
     Dispose(Prompt,Done)
   end;


{
  zobrazi okno so spravou vacsou ako jeden riadok
}
function Info_(_title,_btOKtitle: string; _text,_textp: pointer; _dx,_dy: int;
               _beep: pointer;     { @TBFunc - funkcia pre signalizaciu spravy }
               _wait: long
              ): bool;
   var   I: PInfo;
         E: TEvent;
         res,t_o: bool;
   begin
     if _wait=0 then _wait:= waitINFO*18;
     I:= New(PInfo,Init(_title,_btOKtitle, _text,_textp, _dx,_dy-20, { kvoli podmienke if do=it=nil then inc(dy,20)}
                        nil,0,0,0, _beep,nil,
                        _wait, @t_o,@res, 0, nil,nil)
                       );
     I^.Run(E);
     Dispose(I,Done);
     Info_:= res
   end; { Info }


function Info (_title: string; _text,_textp: pointer; _dx,_dy: int;
               _beep: pointer;     { @TBFunc - funkcia pre signalizaciu spravy }
               _wait: long
              ): bool;
   begin
     Info:= Info_ (_title,'', _text,_textp, _dx,_dy,_beep,_wait);
   end;


function Say_(_title: string; _messp: PMess; _size: int; _cl,_bk: int;
              _beep1, _beep2: pointer;
              _loops: long;
              _start_tick: long; _do_it: pointer; _data : pointer
             ): bool;
   var   Message: PMessage;
         res,t_o: bool;
   begin
     Message:= New(PMessage,Say(_title,_messp,_size, _cl,_bk, _beep1,_beep2,
                                _loops, @t_o,@res,
                                _start_tick, _do_it, _data)
                               );
     Dispose(Message);
     Say_:= res
   end;

{ sprava na jeden riadok
}
function Say(_title: string; _mess: string; _cl,_bk: int;
             _beep1, _beep2: pointer;
             _loops: long;
             _start_tick: long; _do_it: pointer; _data : pointer
            ): bool;
   var   pch: pchar;
   begin
     pch:= StrPasNew(_mess);
     Say:= Say_(_title,@pch,1 , _cl,_bk, _beep1,_beep2,
                _loops,
                _start_tick, _do_it,_data
               );
     StrDispose(pch)
   end;

function Say2(_title: string; _mess: string): bool;
   begin
     Say2:= Say(_title,_mess,clGRd,clBUTTON_COLOR-2, nil,nil, waitINFO*18, 0,nil,nil)
   end;

function Say3(_title: string; data: pchars; size: word): bool;
   var   _messp  : TMess;
         i,p : int;
   begin
     p:= get_str_items (data,size, setNL_+setNL);
     i:= 0; while (i<p) and (i<max_MessStr) do
       begin
         _messp[i]:= get_str0 (data,size,i+1,setNL_+setNL);
         inc(i);
       end;
     if (i<max_MessStr) then
       begin
         _messp[i]:= strpasnew(' ');
         inc(i);
       end;
     p:= i;
     Say3:= Say_(_title,@_messp,p,clGRd,clBUTTON_COLOR-2, nil,nil, waitINFO*18, 0,nil,nil);
     for i:= 0 to p-1 do strdispose(_messp[i])
   end;


function Err (_title: string; _mess: PChar): bool;
   var   Error: PError;
   begin
     Error:= New(PError);
     Err:= Error^.Say(_title,_mess);
     Dispose(Error)
   end;


function Err2(_title: string; _mess: string): bool;
   begin
     _mess:= _mess+NULL;
     Err2:= Err(_title,@_mess[1])
   end;


function PosErr(_x,_y: int; _title: string; _mess: PChar): bool;
   var   PosError: PPosError;
   begin
     PosError:= New(PPosError);
     PosErr:= PosError^.Say(_x,_y,_title,_mess);
     Dispose(PosError)
   end;


procedure SystemErrorMess(tit: string; tm: bool);
    var   t: string;
    begin
      t:= tit;
      if tm then t:= DateToStr2(day,month,year)+', '+TimeToStr(BIOS.hour,BIOS.min,':')+' -> '+tit;
      archive_err(SYSERR_N, t);
      Err2('',tit)
    end;


function  InfoProcess (_title,_btOKtitle: string;
                       _info,_key: string;
                       _do_it: pointer; _data: pointer
                       {_items: int; _pitem: pint}
                      ): bool;
   var    P  : PProcess;
          Ev : TEvent;
          is_done : bool;
   begin
     P:= New(PProcess,Init(_title,_btOKtitle,
                           _info,_key,
                           _do_it,_data,
                           {_items,_pitem,}
                           is_done
                          ));
     P^.Run(Ev);
     Dispose(P,Done);
     if is_done then Beep1;
     InfoProcess:= is_done
   end;


begin
  {Views.p_err:= Err2}
  Views.p_dlg:= Info
end.