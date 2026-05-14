        type  PindFPL = ^TindFPL;
              TindFPL = record
                iFPL : PSTRIP;   { smernik na pole PSTRIP }
                ind  : int       { index v poli PSTRIP^   }
              end;

        const max_indFPL = MAX_ARRAY_SIZE div SizeOf(TindFPL);

        type  PAindFPL = ^TAindFPL;
              TAindFPL = array[0..max_indFPL-1] of PindFPL; { P kvoli triedeniu }

              Tstrip_handler_Bp3vEi2 = function (PLAN: PPLAN; P: pointer; SC: PScroller; var Ev: TEvent; dx,dy: int): bool;


       {$IFDEF EDD}
         function  comp_ndb_indFPL (indFPL1,indFPL2: PindFPL): bool; far;
         function  comp_idn_indFPL (indFPL1,indFPL2: PindFPL): bool; far;
         function  comp_ETD_indFPL (indFPL1,indFPL2: PindFPL): bool; far;
         function  comp_ETO_indFPL (indFPL1,indFPL2: PindFPL): bool; far;
         function  comp_ETA_indFPL (indFPL1,indFPL2: PindFPL): bool; far;
         function  comp_FL_indFPL  (indFPL1,indFPL2: PindFPL): bool; far;
       {$ENDIF}