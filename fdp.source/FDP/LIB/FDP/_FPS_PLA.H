     { ------------------------------------------
        plan realizovany dna... - pre statistiku
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     }

      const  db_FPS_RIADKOV   = 2;
             db0_FPS_RIADKOV  = 2;
             dbchg_FPS : bool = false;

             db_FPS_data = 0;
             db_FPS_reg  = 1;

             dbattr_FPS  = DBbin;


      type   PFPS = ^DFPS;
             DFPS =  record
               fdr  : DFDR;          { udaje }

               flo  : pchar;         { prevadzkovatel }
               opr  : pchar;
               reg  : pchar;         { registracia    }

               dr_  : string[2];
               dr   : word;
             end;


      type  PFPSs = ^TFPSs;
            TFPSs = array[0..MAX_PTRs-1] of PFPS;

