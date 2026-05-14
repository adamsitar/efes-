       const {$IFDEF SLOVAK}
               ask_CFG = 'Zadanò konfiguraánò s£bor existuje. Prep°saü ?';
             {$ENDIF}

             {$IFDEF CZECH}
               ask_CFG = 'Zadanò konfiguraánò s£bor jië existuje. P©epsat ?';
             {$ENDIF}

             {$IFDEF ENGLISH}
               ask_CFG = 'Entered configuration file already exists. Overwrite ?';
             {$ENDIF}


      function  vrat_meno_uzivatela (ext: string; index: word): string;
      function  zadaj_meno_uzivatela (fn,ext: string): string;
