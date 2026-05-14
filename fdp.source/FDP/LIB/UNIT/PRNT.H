     const  _TimeOut = $01;
            _IO__Err = $08;
            _OnLine  = $10;   { 0 = OffLine }
            _NoPaper = $20;
            _AckPrin = $40;   { printer attached }
            _NotBusy = $80;   { 0 = busy }

            ErrorStatus = _TimeOut + _IO__Err + _NoPaper;


     const  _HT = #9;
            _LF = #10;
            _VT = #11;
            _FF = #12;
            _CR = #13;

            _DS = #14;  { double width; ends with CR or LF }
            _DE = #20;  { end double }
            _CS = #15;  { compressed }
            _CE = #18;  { -//- end   }

            _CL = #127; { clear }


            _US = #27#45#01;   { begin underline }
            _UE = #27#45#00;   { end underline   }

            _MS = #27#69;      { begin emphasized }
            _ME = #27#70;      { end              }

            _TS = #27#71;      { begin doublestrike }
            _TE = #27#72;      { end                }

            _SRSS = #27#83#00; { begin superscript }
            _SBSS = #27#83#01; {       subscript   }
            _SSE  = #27#84;    { end               }

            _DWS = #27#87#01;  { begin double width }
            _DWE = #27#87#00;

            _LS1 = #27#48;        { 1/8 inch line spacing  }
            _LS2 = #27#49;        { 7/72 inch line }

            _LSi = #27#65 {+xx};  { xx * 7/72 inch line }
            _LP  = #27#67 {+xx};  { xx * lines per page }



     const {$IFDEF SLOVAK}
            msg_prn_IS_PRINTING = 'Tlaá° sa...';

            msg_prn_NO_CONNECT  = 'Tlaáiare§ nie pripojen† alebo je uvoånenò k†bel.';
            msg_prn_OFF         = 'Vypnut† tlaáiare§.';
            msg_prn_OFF_LINE    = 'Tlaáiare§ je v stave "OFF-LINE".';

            msg_prn_PAPER_OUT   = 'Tlaáiare§ je bez papiera.';
            msg_prn_ERROR       = 'Porucha tlaáiarne... (Sk£ste ju resetovaü alebo vypn£ü a zapn£ü.)';

            msg_prn_TIME_OUT    = 'Od tlaáiarne neprich†dza ëiadna odozva.';

            msg_prn_TEST        = _US+'SlovenskÇ baby s£ '+_MS+'najlep®ie.'+_ME+_UE;
           {$ENDIF}


           {$IFDEF CZECH}
            msg_prn_IS_PRINTING = 'Tiskne se...';

            msg_prn_NO_CONNECT  = 'Tisk†rna nen° p©ipojena nebo je uvolnànò kabel.';
            msg_prn_OFF         = 'Vypnut† tisk†rna.';
            msg_prn_OFF_LINE    = 'Tisk†rna je v stavu "OFF-LINE".';

            msg_prn_PAPER_OUT   = 'Tisk†rna bez pap°ra.';
            msg_prn_ERROR       = 'Porucha tisk†rny... (Zkuste ji resetovat anebo vypnout a zapnout.)';

            msg_prn_TIME_OUT    = 'Od tisk†rny nep©ich†z° ë†dna odezva.';

            msg_prn_TEST        = _US+'Dal bych si '+_MS+'Budv†rek.'+_ME+_UE;
           {$ENDIF}


           {$IFDEF ENGLISH}
            msg_prn_IS_PRINTING = 'Printing...';

            msg_prn_NO_CONNECT  = 'Printer or cabel not connected.';
            msg_prn_OFF         = 'Printer off.';
            msg_prn_OFF_LINE    = 'Printer is in the state "OFF-LINE".';

            msg_prn_PAPER_OUT   = 'Paper out.';
            msg_prn_ERROR       = 'Printer error... (Try reset or switch off/on.)';

            msg_prn_TIME_OUT    = 'No response from printer.';

            msg_prn_TEST        = _US+'Printer '+_MS+'test.'+_ME+_UE;
           {$ENDIF}
