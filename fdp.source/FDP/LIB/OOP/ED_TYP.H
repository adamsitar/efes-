     type  { typy procedur odovzdavanych ako smerniky do formulara }
             TBfunc_p = function (p: pointer): bool;
             Tproc_p  = procedure(p: pointer);


     type    PForm = ^TForm;
             TForm = record       { Formular :              }
               item  : PChar;     { polozka                 }
               title : PChar;     { hlavicka                }
               lst   : PListDesc; { ponuka moznych poloziek }
               pos   : int;       { pozicia v polozkach, zaporna znamena
                                    vlozenie zvolenej hodnoty za ostatne,
                                    a nie ich prepis...
                                  }
               legal : PCharSet;  { povolene znaky          }
               skip  : PCharSet;  { zakazane znaky          }
               dx,dy : int;
               font  : byte;
              {size  : byte;}
               color : byte;
             end;

             TFPar  = record      { Formularove Parametre       }
               _lo,_hi: int {byte};
               i,oi   : int;
             end;

             TForms = array[0..max_size_Form-1] of TForm;
             TFPars = array[0..max_size_Form-1] of TFPar;
             PForms = ^TForms;
             PFPars = ^TFPars;

