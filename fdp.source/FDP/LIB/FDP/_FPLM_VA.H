      const max_9bMs = 100;

{      type  T_9bM  = record
                       mil : string[2];
                       l4  : string[kod_9b]
                     end;

            T_9bMs = array[0..max_9bMs-1] of T_9bM;
            P_9bMs = ^T_9bMs;

      const lst9bMs  : P_9bMs = nil;
            poc_9bMs : int = 0;

}

      const  { Kontroluje sa, ci prijata sprava neobsahuje
               uz spracovany plan... ...externou referenciou
               na objekt... tu nie su dokonale naprogramovane
               handlery na message. Mohla by sa stratit...
             }
             p_formular_REQ_FPL: PFDP_AForm0 = nil;

