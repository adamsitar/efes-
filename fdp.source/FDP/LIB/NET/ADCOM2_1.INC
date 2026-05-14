{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                        €
€  T_AdCOM                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{
  Purpose:

      The purpose of this module is to provide linkable functions that
      can be called to perform software interrupts to the Super-X.25
      device driver.

  functions defined within this module:

     function Name          Brief Description of function
     -------------          -----------------------------
      _init                  Initialization
      _pvcinit               PVC initialization
      _go                    Connect to network
      _gcmd                  Global receive queue status
      _readch                Channel receive queue status
      _open                  Open SVC
      _acpt                  Accept call
      _close                 Close SVC
      _write                 Transmit data
      _int                   Send X.25 interrupt packet
      _reset                 Send X.25 reset packet
      _end                   Disconnect from network
      _status                Get status of Super-X.25
      _reset2i               Reset AdCom2-I

}

var  R :  registers;


{
  Function is to return the base 2 equivalent of a number.
}
function GETB2(SIZE :  U16BIT):  U16BIT;
   var   TMP1,B2 :  U16BIT;
   begin
     tmp1:=  1;
     b2:=  0;
     { range the value just to be sure }
     while (tmp1 < size) do
       begin
         tmp1:= tmp1 SHL 1;
         inc(b2)
       end;
     if b2 < 4 then b2:=  4;
     if b2 > 12 then b2:=  12;
     getb2:=  b2
   end; { GETB2 }


constructor T_AdCOM.Init;
      begin
        fillchar(c,sizeof(cmdintfc),0);
      end;

destructor T_AdCOM.Done;
     begin
     end;


{
  Initializes the Super-X.25 interface, allowing information
  to be sent over the network
}
function T_AdCOM._INIT(LINES: int; INIT_PTR: P_INIT_GLOB): word;
    begin
      C.A := LINES;
      C.B := U32BIT(INIT_PTR);
      R.AX:= OFS(C);
      R.BX:= SEG(C);
      R.CX:= X_INIT;
      Intr(SW_INTR_X25,R);
      _INIT:=  R.AX
    end; { _INIT }


{
  Initializes PVC's to the parameters specified
}
function T_AdCOM._PVCINIT(LINE,CHAN: S16BIT;  PVCTABLE: P_PVCINIT): word;
   begin
     C.A := LINE;
     C.B := CHAN;
     C.C := U32BIT(PVCTABLE);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_PVCINIT;
     Intr(SW_INTR_X25,R);
     _PVCINIT:= R.AX
   end;

{
  Initiates connection to the X.25 network.
}
function T_AdCOM._GO(LINE: S16BIT): word;
   begin
     C.A := LINE;
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_GO;
     Intr(SW_INTR_X25,R);
     _GO:= R.AX
   end;


{
  This function is used to poll the incoming packet command queue
  for data from the X.25 network.
}
function T_AdCOM._GCMD(DESC_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(DESC_PTR);

     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_GCMD;
     Intr(SW_INTR_X25,R);
     _GCMD:= R.AX
   end;


{
  This function is used to read the packet at the head of the
  command queue specified by line and chan.
}
function T_AdCOM._READCH(DATA_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(DATA_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_READCH;
     Intr(SW_INTR_X25,R);
     _READCH:= R.AX
   end;


{
  This function is used to initiate a call on the X.25 network
}
function T_AdCOM._OPEN(CALL_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(CALL_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_OPEN;
     Intr(SW_INTR_X25,R);
     _OPEN:= R.AX
   end;


{
  This function is used to accept an incoming X.25 connection
}
function T_AdCOM._ACPT(CALL_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(CALL_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_ACPT;
     Intr(SW_INTR_X25,R);
     _ACPT:= R.AX
   end;


{
  Clears the specified connection.
}
function T_AdCOM._CLOSE(CLEAR_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(CLEAR_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_CLOSE;
     Intr(SW_INTR_X25,R);
     _CLOSE:= R.AX
   end;


{
  The specified data is transmitted across the network
}
function T_AdCOM._WRITE(DATA_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(DATA_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_WRITE;
     Intr(SW_INTR_X25,R);
     _WRITE:= R.AX
   end;


{
  Transmits an interrupt packet across the specified channel.
}
function T_AdCOM._INT(DATA_PTR: P_DATA_DESC): word;
   begin
     C.A:= U32BIT(DATA_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_INT;
     Intr(SW_INTR_X25,R);
     _INT:= R.AX
   end;


{
  This function will transmit a reset packet across the specified X.25
  logical channel.
}
function T_AdCOM._RESET(LINE,CHAN: S16BIT): word;
   begin
     C.A:= U32BIT(LINE);
     C.B:= U32BIT(CHAN);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_RESET;
     Intr(SW_INTR_X25,R);
     _RESET:= R.AX
   end;


{
  After communications across the network are no longer required
  this function should be called to disconnect from the network.
}
function T_AdCOM._END(LINE: S16BIT): word;
   begin
     C.A:= U32BIT(LINE);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_end;
     Intr(SW_INTR_X25,R);
     _END:= R.AX
   end;


{
  Returns status and statistical information from the X.25
  protocol software.
}
function T_AdCOM._STATUS(STATUS_PTR: P_STATUS_DESC): word;
   begin
     C.A:= U32BIT(STATUS_PTR);
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= X_STATUS;
     Intr(SW_INTR_X25,R);
     _STATUS:= R.AX
   end; { _STATUS }


{
  The purpose of this function is to perform a software reset on the AdCom2-I.
}
function T_AdCOM._RESET2I: word;
   begin
     R.AX:= OFS(C);
     R.BX:= SEG(C);
     R.CX:= RESET2I;
     Intr(SW_INTR_X25,R);
     _RESET2I:= R.AX
   end; { _RESET2I }
