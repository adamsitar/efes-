     const  EDIT_INFO =
              {$IFDEF SLOVAK}
                 '~Tab~,~Ctrl~+...: polo‘ka; ~Shift~+~Tab~: predch zej£ca polo‘ka; '+
                 '~Ins~: vkladanie/prepis; '+
                 '~Ctrl~+~'#17#196#217'~: nastavenie'
              {$ENDIF}
              {$IFDEF CZECH}
                 '~Tab~,~Ctrl~+...: dal¨¡ polo‘ka; ~Shift~+~Tab~: p©edch zej¡ci polo‘ka; '+
                 '~Ins~: vkl dan¡/p©epis; ~Ctrl~+~Enter~: nastaven¡'
              {$ENDIF}
              {$IFDEF ENGLISH}
                 '~Tab~,~Ctrl~+...: next item; ~Shift~+~Tab~: previous item; '+
                 '~Ins~: insert mode; ~Ctrl~+~Enter~: set up'
              {$ENDIF}
              ;

            FORM_INFO =
              {$IFDEF SLOVAK}
                 '~Ctrl~+~'#17#196#217'~ potvrdenie'
              {$ENDIF}
              {$IFDEF CZECH}
                 '~Ctrl~+~'#17#196#217'~ potvrzen¡'
              {$ENDIF}
              {$IFDEF ENGLISH}
                 '~Ctrl~+~'#17#196#217'~ confirmation'
              {$ENDIF}
              ;

            BOX_INFO  =
              {$IFDEF SLOVAK}
                 '~'#17#196#217'~ nastavenie'
              {$ENDIF}
              {$IFDEF CZECH}
                 '~'#17#196#217'~ nastaven¡'
              {$ENDIF}
              {$IFDEF ENGLISH}
                 '~'#17#196#217'~ confirmation'
              {$ENDIF}
              ;


     const { jednoduchy formular }
             cbBack = clGR3;  { farba riadku                }
             cbText = clGRd;  { farba textu                 }
             cbForm = clGRa;  { oddelovace textu napr 12:12 }

     const { formular }
             cfBack = clGR5;
             cfText = clGRc;
             cfForm = clGRa;
             cfActB = {clGR3}0;
             cfActT = clGRe;


     const   max_length_Form = 100;
             max_size_Form   = 100;