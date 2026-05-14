     {$IFDEF SLOVAK}
      const   TLGM          = ' TELE~G~RAMY ';

              TLGLIST       = ' A~K~TUAèLNE TELEGRAMY ';
              TLGARCH       = ' ~A~RCHIVOVANê TELEGRAMY ';

              TLGSS         = 'ZOBRAZ SS/DD';
              TLGFF         = ' -//-  FF/GG';
              TLGKK         = ' -//-  KK/LL';
              PRNRECTLG     = 'TLAÄ PRIJATê TELEGRAMY';
              {Switch2('~N~O DELAY PRINT ', @tlg_PrintAll,}
              PRNSS         = 'TLAÄ   SS/DD';
              PRNFF         = '-//-   FF/GG';
              PRNKK         = '-//-   KK/LL';

              TLGHEADERR    = 'VYHODNOTENIE NEZNèMYCH/NEPOVOLENùCH SPRèV';
              TLGHEADERRTLG = 'NEZNèME/NEPOVOLENê AKO CHYBA/TELEGRAM';
              TLGUPDATE     = 'SPRACOVANIE OPRAVENùCH SPRèV';

              DISPERRFLI    = 'DISPLAY ERROR FLI MESSAGE';
              FLIACT        = 'FLI ACTIVATION';
              FLISEND       = 'FLI COORDINATION';
              UPDATEFPLCFLI = 'FLI UPDATING OF STRIP';
              DELETEFPLCFLI = 'FLI DELETE OF STRIP';

              TLGF11        = ' AFTN TELE~G~RAMY ';
              SPRF10        = ' SPRèVY LETVIS FDP ';

              PREHLADAFTN   = ' AFTN TELE~G~RAMY ';
     {$ENDIF}


     {$IFDEF CZECH}
     {$ENDIF}


     {$IFDEF ENGLISH}
      const   TLGM          = ' TE~L~EGRAMMS ';

              TLGLIST       = ' C~U~RRENT TELEGRAMMS ';
              TLGARCH       = ' ~A~RCHIVED TELEGRAMMS ';

              TLGSS         = 'DISPLAY   SS/DD  (ëë/ÑÑ)';
              TLGFF         = ' -//-     FF/GG  (îî/ÉÉ)';
              TLGKK         = ' -//-     KK/LL  (ää/ãã)';
              PRNRECTLG     = 'PRINT RECEIVED TELEGRAMS';
              {Switch2('~N~O DELAY PRINT ', @tlg_PrintAll,}
              PRNSS         = 'PRINT     SS/DD  (ëë/ÑÑ)';
              PRNFF         = ' -//-     FF/GG  (îî/ÉÉ)';
              PRNKK         = ' -//-     KK/LL  (ää/ãã)';

              TLGHEADERR    = 'EVALUATE UNKNOWN/DISABLED MESSAGE';
              TLGHEADERRTLG = 'UNKNOWN/DISABLED AS ERROR/TELEGRAM';
              TLGUPDATE     = 'PROCESS UPDATED MESSAGES';

              DISPERRFLI    = 'DISPLAY ERROR FLI MESSAGE';
              FLIACT        = 'FLI ACTIVATION';
              FLISEND       = 'FLI COORDINATION';
              UPDATEFPLCFLI = 'FLI UPDATING OF STRIP';
              DELETEFPLCFLI = 'FLI DELETE OF STRIP';

              TLGF11        = ' AFTN TE~L~EGRAMM ';
              SPRF10        = ' LETVIS FDP ~M~ESSAGE ';

              PREHLADAFTN   = ' AFTN ~T~ELEGRAMMS ';
     {$ENDIF}
