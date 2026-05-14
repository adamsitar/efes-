     const  maxEXTs = 30;

     type   TEXTnode_desc = record

             { a) popis stanice
             }
               obj   : PO_EXT;    { objekt pre komunikaciu v danom smere }

             { b) adresy
             } adr   : pchar;

             { c) popis
             } name  : pchar;
               inf   : pchar;     { zoznam odosielanych informacii     }

             { d) ine ako spolocne nastavenia
             } tmout : word;      { iny ako standartny time out        }
             end;


     type    PEXTnode = ^TEXTnode;
             TEXTnode = record
               desc : TEXTnode_desc;
               stat : TNETnode_status;
             end;


     type    PEXTnodes = ^TEXTnodes;
             TEXTnodes = array[0..maxEXTs-1] of PEXTnode;


     const   EXTs: PEXTnodes = nil;
             EXTpoc : int = 0;
