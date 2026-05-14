   {$IFDEF MAPY}

    {$IFDEF  MAPY_1.0}

      const {$IFDEF SLOVAK}
             OBMstr = ' ~O~BMEDZENê PRIESTORY ';
             ZAKstr = ' ~Z~AKèZANê PRIESTORY  ';
             TMAstr = ' ~T~MA                 ';
             CTRstr = ' ~C~TR                 ';
             LETstr = ' ~L~ETISKè             ';
             TRTstr = ' ~A~WY      (trate)    ';
             STHstr = ' ~H~RANICE             ';
             MAPstr = ' ~M~APY                ';
             SYMstr = ' ~S~YMBOLY             ';
            {$ENDIF}

            {$IFDEF ENGLISH}
             OBMstr = ' ~R~estricted area     ';
             ZAKstr = ' ~P~rohibited area     ';
             TMAstr = ' ~T~MA                 ';
             CTRstr = ' ~C~TR                 ';
             LETstr = ' A~i~rbase/Aiport      ';
             TRTstr = ' ~A~WY                 ';
             STHstr = ' ~B~order              ';
             MAPstr = ' ~M~ap                 ';
             SYMstr = ' ~S~ymbol              ';
            {$ENDIF}

      const  OBMmenu  : PSubMenu = nil;
             ZAKmenu  : PSubmenu = nil;
             LETmenu  : PSubmenu = nil;
             CTRmenu  : PSubmenu = nil;
             TMAmenu  : PSubmenu = nil;
             TRTmenu  : PSubmenu = nil;
             STHmenu  : PSubmenu = nil;
             MAPmenu  : PSubMenu = nil;
             SYMmenu  : PSubmenu = nil;

    {$ENDIF}


    const {$IFDEF SLOVAK}
            NSMstr   = ' ~S~YMBOLY ';{     ';}
            MapOnOff = 'Zapni/Vypni';
          {$ENDIF}

          {$IFDEF CZECH}
            NSMstr   = ' ~S~YMBOLY ';
            MapOnOff = 'Zapni/Vypni';
          {$ENDIF}

          {$IFDEF ENGLISH}
            NSMstr   = ' ~S~YMBOLS ';
            MapOnOff = 'On/Off';
          {$ENDIF}

           NSMmenu  : PSubmenu = nil;
           MAPYmenu : PSubmenu = nil;


    const  OMenuS_items = 15;   { maximalny pocet poloziek pre scrollovacie menu }

   {$ENDIF}