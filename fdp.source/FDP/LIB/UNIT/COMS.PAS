(*-------------------------------------------------------------------*)
(* LETVIS FDP - COM                                                  *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit COMs;


interface

     uses  TypeDef;

     const maxCOMs       = 4;
           COM__TIME_OUT = 18;

     type  address = array[1..maxCOMs] of word;
           values  = array[1..maxCOMs] of byte;

     const INT_COM : array[1..maxCOMs] of byte = ($0C,$0B,$0E,$0E);
           INT_OFF = 8;

           COM: address = ($3F8,$2F8,$3E8,$2E8);
           IER: address = ($3F9,$2F9,$3E9,$2E9);
           IIR: address = ($3FA,$2FA,$3EA,$2EA);
           LCR: address = ($3FB,$2FB,$3EB,$2EB);
           MCR: address = ($3FC,$2FC,$3EC,$2EC);
           LSR: address = ($3FD,$2FD,$3ED,$2ED);

     type  PARITY  = (NONE,ODD,NONE1,EVEN);
     const sPARITY : array[low(PARITY)..high(PARITY)] of string[4] = ('NONE','ODD','NONE','EVEN');

     const cfg_COM_0X        = 'COM';
           cfg_COM_MODE      = 'MODE';
           cfg_COM_INT       = 'INT';
           cfg_COM_BITs      = 'BITS';
           cfg_COM_STOP_BITs = 'STOP_BITS';
           cfg_COM_PARITY    = 'PARITY';

     const COMsaved: array[1..maxCOMs] of bool = (false,false,false,false);
           COMsemaphor: array[1..maxCOMs] of bool = (false,false,false,false);

     var   LoBd,HiBd,Bits,Inte,Modem: values;
           COMi_rec: values;

     procedure SaveCOMi(i: byte);
     procedure SetCOMi (i: byte; LoBd,HiBd,Bits,inte,Modem: byte);

     function  SendCOMi (_com: byte; vet: string): bool;
     function  SendCOMib(_com: byte; bp: Pbytes; pocet: int; main_en: bool): bool;
     function  DataReadyCOMi(ind: int): bool;

     function  _MODE(Bd: word; err: bool): word;
     function  _PARITY(sP: string; err: bool): PARITY;
     function  _LCR (bits: byte; stop_bit: byte; parita: PARITY): word;


implementation

uses BIOS, _Check, math, mess, str0;


function SendCOMi(_com: byte; vet: string): bool;
   begin
     SendCOMi:= SendCOMib(_com, @vet[1], length(vet), false)
   end;

function SendCOMib(_com: byte; bp: Pbytes; pocet: int; main_en: bool): bool;
   var   i   : int;
         tick: long;
         t_o : bool;
   begin
     SendCOMib:= false;
     if COMsemaphor[_com] then Exit;
     COMsemaphor[_com]:= true;
     for i:= 0 to pocet-1 do
       begin
         tick:= getticks; t_o:= false;
         repeat
           t_o:= TimeOut(tick, getticks, COM__TIME_OUT);
         until t_o or (Port[LSR[_com]]=96) or (Port[LSR[_com]]=97);
         if t_o then break;
         Port[COM[_com]]:= bp^[i];
         CheckProcesses0
       end;
     COMsemaphor[_com]:= false;
     SendCOMib:= (not t_o) {and (i=Length(vet))}
   end;  { SendCOMi }


function DataReadyCOMi(ind: int): bool;
   var   b: byte;
   begin
     if bool (Port[LSR[ind]] and $01) then
        begin
          COMi_rec[ind]:= Port[COM[ind]];
          DataReadyCOMi:= true
        end
     else DataReadyCOMi:= false
   end; { DataReadyCOMi }


{----------------------------------------------------------}
{ setting of 8250 :                                        }
{----------------------------------------------------------}

procedure SaveCOMi(i: byte);
    begin
      Bits[i] := Port[LCR[i]];   { save old parameters from COMi }
      inte[i] := Port[IER[i]];
      Modem[i]:= Port[MCR[i]];
      PortW[LCR[i]]:= $80;
      LoBd[i] := Port[COM[i]];
      HiBd[i] := Port[IER[i]];

      COMsaved[i]:= true
    end; { SaveCOMi }


procedure SetCOMi(i: byte; LoBd,HiBd, Bits, Inte,Modem: byte);
    var   Val: byte;
    begin
      Port[LCR[i]]:= $80 ;  { DLAB = 1   }
      Port[COM[i]]:= LoBd;  { nizsi byte delitela kmitoctu (1200 Bd) }
      Port[IER[i]]:= HiBd;  { vyssi byte delitela kmitoctu }
      Port[LCR[i]]:= Bits;  { 7 bit's, 1 stop bit, EVEN parity }
      Port[IER[i]]:= Inte;  { povol INT COMi od prijateho znaku }
      Port[MCR[i]]:= Modem; { nastav OUT2, RTS, DTR }

      Val:= Port[IIR[i]];
      Val:= Port[LSR[i]];
      Val:= Port[COM[i]]
    end; { SetCOMi }


function _MODE(Bd: word; err: bool): word;
   begin
     if    err
        and (not (   (Bd=150)
                  or (Bd=300)
                  or (Bd=600)
                  or (Bd=1200)
                  or (Bd=2400)
                  or (Bd=4800)
                  or (Bd=9600)
                  or (Bd=19200)
                 )
            )
        then RunError('Invalid value of transmition rate.');
     _MODE:= 115200 div Bd
   end;

function _PARITY(sP: string; err: bool): PARITY;
   var   p : PARITY;
   begin
     sP:= cut_(sP); sP:= upstring(sP);
     p:= low(PARITY);
     while (p<=high(PARITY)) do
       begin
         if (sP<>sPARITY[p]) then
            if (p<high(PARITY)) then inc(p)
            else begin
                   if err then RunError('Invalid value of parity.');
                   p:= NONE;
                   break
                 end
         else break
       end;
     _PARITY:= p
   end;

function _LCR(bits: byte; stop_bit: byte; parita: PARITY): word;
   begin
     _LCR:= ((ord(parita) shl 3) and 24) + ((N(stop_bit-1) shl 2) and 4) + (N(bits-5) and 3)
   end;

end. { _COM }