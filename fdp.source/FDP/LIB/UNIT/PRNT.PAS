{$DEFINE PRNT_ERR_MESS}

{$I comp.h}


unit PRNT;


interface


     uses   TypeDef;


     const  PRN_TAB     : int  = 1;
            PRN_TAB_lo  = 0;
            PRN_TAB_hi  = 20;

            PRINTER_COM    : int  = 2;
            PRINTER_COM_lo = 1;
            PRINTER_COM_hi = 2;

            PortNo             = 0;
            PRN_TIME_OUT       = 3*18;

            is_PRN      : bool = {$IFDEF OPL} true
                                 {$ELSE} {$IFDEF PRN_SERVER} true
                                         {$ELSE} false
                                         {$ENDIF}
                                 {$ENDIF};

            PRN_NET    : bool = true;
            is_PRN_NET : bool = false;


     const  DATA_LF: bool = false;


     {$I prnt.h}


     type      T_print_str  = function (PortNo: byte; s: string): string;
     function  _print_str (PortNo: byte; s: string): string;
     const     p_print_str : T_print_str = _print_str;

     type      T_print_strs = function (PortNo: byte; s: Pstrs; pocet: int): string;
     function  _print_strs (PortNo: byte; s: Pstrs; pocet: int): string;
     const     p_print_strs : T_print_strs = _print_strs;

     function  print_str (PortNo: byte; s: string): bool;
     function  print_strs(PortNo: byte; s: Pstrs; pocet: int): bool;

     function  send_string_to_prn (PortNo: byte; s: string; ext: bool): string;

     function  printer_init(PortNo: byte): byte;
     function  printer_status(PortNo: byte): byte;
     function  printer_test(PortNo: byte): bool;

     function  print_char(PortNo: byte; ch: char): byte;
     function  print_head(PortNo: byte; title: string): bool;

     function  is_printer_err(stat: byte): bool;
     function  printer_msg(stat: byte): string;

     function  _PRN_TAB: string;

    {$IFDEF IER}
       function setup_IER: bool;
    {$ENDIF}


implementation

uses  Printer, BIOS, IO, _Check, COMs, DOS,
      str0, utime, math, msg, keyb, sets,
      {$I unit_gr.h}
      {$IFDEF PRNT_ERR_MESS},
        Dialog
      {$ENDIF};

{$IFDEF IER}
  function setup_IER: bool;
     var   s   : string;
           res : bool;
     begin
       SetCOMi(PRINTER_COM,12,0,$1A,$01,$0B);

       s  :=  ''#2; {^A';}
       res:= SendCOMi(PRINTER_COM,s);

       if res then
          begin
            s:=     '^J04^T001^L000020210'
                  + '^J07^T031^L000010345'
                  + '^J10^T012^L000730001'
                  + '^J10^T022^L000430001'
                  + '^J10^T031^L000730002';
            res:= SendCOMi(PRINTER_COM,s)
          end;

       setup_IER:= res
     end;
{$ENDIF}

function printer_init(PortNo: byte): byte;
   var   reg : Registers;
   begin
     with reg do
       begin
         AH := 1;
	 DX := PortNo;
	 Intr($17,Reg);
	 printer_init:= AH
       end;
   end;

function printer_status(PortNo: byte): byte;
   var   reg : Registers;
   begin
     with reg do
       begin
         AH := 2;
	 DX := PortNo;
	 Intr($17,Reg);
	 printer_status:= AH
       end;
   end;


function printer_test(PortNo: byte): bool;
   begin
     printer_test:= print_str(PortNo,_LF+_PRN_TAB+msg_prn_TEST+_LF)
   end;


function print_char(PortNo: byte; ch: char): byte;
   var   reg : Registers;
   begin
     with reg do
       begin
         AH := 0;
         AL := ord(ch);
	 DX := PortNo;
	 Intr($17,Reg);
	 print_char:= AH
       end;
   end;


function send_string_to_prn(PortNo: byte; s: string; ext: bool): string;
   var   tick : tick_counter;
         stat : byte;
         i    : int;
         res  : string;

   function _continue(stat: word; ext: bool; var res: string): string;
      begin
        res:= printer_msg(stat);
        if res='' then res:= msg_prn_TIME_OUT;
        {$IFDEF PRNT_ERR_MESS}
         if (not ext) and (Ask2(msgERR, res+' '+ask_PrintContinue,'',White,Red,-1)=ansAno) then res:= '';
        {$ENDIF}
        _continue:= res
      end;

   label L1,L2,L3, X;
   begin
     res:= '';
     L1: stat:= printer_status(PortNo);
     if is_printer_err(stat) then
        if (_continue(stat,ext, res)='') then goto L1
        else goto X;
     s:= cs_ascii_str2(s);
     for i:= 1 to length(s) do
        begin
          tick:= GetTicks;
          repeat
            L2: stat:= printer_status(PortNo);
            if is_printer_err(stat) then
               if _continue(stat,ext, res)='' then goto L2
               else goto X;
            if TimeOut(tick, GetTicks, PRN_TIME_OUT) then
               begin
                 if _continue(stat,ext, res)<>'' then
                    begin
                      stat:= _TimeOut;
                      goto X
                    end
               end;
            CheckProcesses0
          until ((stat and _NotBusy)<>0);
          write(Lst,s[i]); {print_char(PortNo,s[i])}
        end;
     X: send_string_to_prn:= res
   end; { print_str }


function _print_str(PortNo: byte; s: string): string;
   begin
     _print_str:= send_string_to_prn(PortNo,s,false)
   end;

function print_str(PortNo: byte; s: string): bool;
   var   t : text;
   begin
     print_str:= p_print_str(PortNo,s)='';
     {IFDEF DEBUG
      assign(t,'1.bak');
      if Exists('1.bak')<>0 then rewrite(t) else append(t);
      write(t,s);
      close(t);
     ENDIF}
   end;


function _print_strs(PortNo: byte; s: Pstrs; pocet: int): string;
   var   res,nl : string;
         i : int;
   begin
     res:= ''; i:= 0;
     while (i<pocet) and (res='') do
       begin
         if (s^[i]<>'') and (not (s^[i][length(s^[i])] in setNL+setNL_)) then nl:= kbNL else nl:= '';
         res:= p_print_str(PortNo,s^[i]+nl);
         inc(i);
         {CheckProcesses0}
       end;
     _print_strs:= res
   end;

function print_strs(PortNo: byte; s: Pstrs; pocet: int): bool;
   begin
     print_strs:= p_print_strs(PortNo,s,pocet)=''
   end;


function print_head(PortNo: byte;  title: string): bool;
   begin
     title:= _LF+_LF+_LF+_LF+_PRN_TAB+_CE+_US+_TS+_MS+title+_UE+_TE+_ME+_LF+_LF;
     print_head:= print_str(PortNo,title)
   end;


function is_printer_err(stat: byte): bool;
   begin
     is_printer_err:= ((stat and _OnLine)=0) or ((stat and ErrorStatus)<>0)
   end;

{
  odladene na EPSON FX1050
}
function printer_msg(stat: byte): string;
   begin
     if is_printer_err(stat) then
        begin
        { kombinacie chybovych kodov }
          if      (stat and $30<>0) then printer_msg:= msg_prn_NO_CONNECT
          else if (stat and $C8<>0) then printer_msg:= msg_prn_OFF
          else if (stat and $18<>0) or ((stat and _OnLine)=0) then printer_msg:= msg_prn_OFF_LINE

        { konkretne chyby }
          else if (stat and _NoPaper)<>0 then printer_msg:= msg_prn_PAPER_OUT
          else printer_msg:= msg_prn_ERROR
        end
     else printer_msg:= ''
   end;


function _PRN_TAB: string;
   var   s: string;
         i: int;
   begin
     s:= '';
     for i:= 0 to PRN_TAB do s:= s+' ';
     _PRN_TAB:= s
   end;

end.
