    type { deklaracia procedur }

            TPFunc_p    = function (p: pointer): pointer;
            PPFunc_p    = ^TPFunc_p;

            TPFunc_p2   = function (p1,p2: pointer): pointer;
            TPFunc_p3   = function (p1,p2,p3: pointer) : pointer;

            TPFunc_s    = function (s: string): pointer;
            PPFunc_s    = ^TPFunc_s;

            TBFunc      = function: bool;
            TBFunc_i    = function (i: int): bool;

            TBFunc_s    = function (s: string): bool;
            PBFunc_s    = ^PBFunc_s;
            TBFunc_s2   = function (s1,s2: string): bool;
            PBFunc_s2   = ^PBFunc_s2;

            TBFunc_p    = function (p: pointer): bool;
            PBFunc_p    = ^TBFunc_p;

            TBFunc_p2   = function (p1,p2: pointer): bool;
            PBFunc_p2   = ^TBFunc_p2;

            TBFunc_p3   = function (p1,p2,p3: pointer) : bool;
            PBFunc_p3   = ^TBFunc_p3;

            TBFunc_pi   = function (p: pointer; i: int): bool;
            TBFunc_pi2  = function (p: pointer; i1,i2: int): bool;

            TBFunc_ps   = function (p: pointer; s: string): bool;
            PBFunc_ps   = ^TBFunc_ps;

            TByFunc_p2  = function (p1,p2: pointer): byte;


            TIFunc      = function: int;
            TIFunc_p    = function (p: pointer): int;
            TIFunc_s    = function (s: string): int;
            TIFunc_sp   = function (s: string; p: pointer): int;
            PIFunc_sp   = ^TIFunc_sp;

            TWFunc_p    = function (p: pointer): word;
            PWFunc_p    = ^TWFunc_p;

            TRFunc_p    = function (p: pointer): real;
            PRFunc_p    = ^TRFunc_p;

            TWFunc_pi   = function (p: pointer; i: int): word;
            PWFunc_pi   = ^TWFunc_pi;

            TRFunc_pi   = function (p: pointer; i: int): real;
            PRFunc_pi   = ^TRFunc_pi;


            TSFunc      = function: string;

            TSFunc_s    = function (s: string) : string;
            PSFunc_s    = ^TSFunc_s;

            TSFunc_p    = function (p: pointer): string;
            PSFunc_p    = ^TSFunc_p;

            TSFunc_pi   = function (p: pointer; i: int): string;
            TSFunc_pis  = function (p: pointer; i: int; s: string): string;
            PSFunc_pis  = ^TSFunc_pis;


            TBFunc_date = function (d: TDate): bool;
            PBFunc_date = ^TBFunc_date;


    type    TProc       = procedure;
            PProc       = ^TProc;

            TProc_i     = procedure(i: int);
            PProc_i     = ^TProc_i;

            TProc_b     = procedure(b: bool);

            TProc_s     = procedure(s: string);
            PProc_s     = ^TProc_s;


            TProc_i4    = procedure(a,b,c,d: int);
            TProc_i4p   = procedure(a,b,c,d: int; p: pointer);

            TProc_p     = procedure(p: pointer);
            PProc_p     = ^TProc_p;

            TProc_p2    = procedure(p1,p2: pointer);
            PProc_p2    = ^TProc_p2;

            TProc_vp    = procedure(var p: pointer);
            TProc_vp2   = procedure(var p1,p2: pointer);
            TProc_p3l   = procedure(p1,p2,p3: pointer; l: long);

            TProc_pi    = procedure(p: pointer; i: int);
            TProc_pi2   = procedure(p: pointer; i1,i2: int);
            TProc_pw    = procedure(p: pointer; w: word);
            TProc_pl    = procedure(p: pointer; l: long);

            TProc_ps    = procedure(p: pointer; s: string);
            PProc_ps    = ^TProc_ps;

            TProc_p2s   = procedure(p1,p2: pointer; s: string);
            TProc_p2i   = procedure(p1,p2: pointer; i: int);


            TProc_date  = procedure(d: TDate);
            PProc_date  = ^TProc_date;
