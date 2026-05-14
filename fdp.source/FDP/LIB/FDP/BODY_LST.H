    const  _fnNDB     = 'ndb';
           _fnOB      = 'ndb-mil';
           _fnNDB_O   = 'ndb-o';
           _fnNDB_I   = 'ndb-i';

           _fnRTE     = 'rte';
           _fnRTE_fir = 'rte-fir';  { nenacitava sa }
           _fnRTE_M   = 'rte-mil';
           _fnRTE_DA  = 'rte-da';   { odlet/prilet }
           _fnRTE_O   = 'rte-o';

           _fnCLet    = 'aip-c';
           _fnMLet    = 'aip-m';
           _fnALet    = 'aip-a';


           fnNDB      : TListDesc = (fn:_fnNDB+firExt   ; lo:0;poz:0; p:nil);
           fnOB       : TListDesc = (fn:_fnOB+firExt    ; lo:0;poz:0; p:nil);
           fnABC      : TListDesc = (fn:nil             ; lo:0;poz:0; p:nil);

           fnMLet     : TListDesc = (fn:_fnMLet+firExt  ; lo:0;poz:0; p:nil);
           fnCLet     : TListDesc = (fn:_fnCLet+firExt  ; lo:0;poz:0; p:nil);
           fnALet     : TListDesc = (fn:_fnALet+firExt  ; lo:0;poz:0; p:nil);

           fnRTE      : TListDesc = (fn:_fnRTE+firExt   ; lo:0;poz:0; p:nil);
           fnRTE_M    : TListDesc = (fn:_fnRTE_M+firExt ; lo:0;poz:0; p:nil);
           fnRTE_O    : TListDesc = (fn:_fnRTE_O+firExt ; lo:0;poz:0; p:nil);
           fnNDB_O    : TListDesc = (fn:_fnNDB_O+firExt ; lo:0;poz:0; p:nil);
           fnNDB_I    : TListDesc = (fn:_fnNDB_I+firExt ; lo:0;poz:0; p:nil);
           {fnNDB_IO  : TListDesc = (fn:_fnNDB_IO+firExt; lo:0;poz:0);}


          { Pomocne zoznamy pre ponuku necivilnych letisk,
            podriadenych letisk a vlastnych trati

           fnAIP_M    : TListDesc = (fn:_fnMLet+firExt  ; lo:0;poz:0);
           fnRTE_Mlst : TListDesc = (fn:_fnRTE_M+lstExt; lo:0;poz:0);
          }
