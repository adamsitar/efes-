     const X25cfg       = 'X25'+ext_ini;
           maxX25_NODEs = 20;

           pX25_0 = 0;
           pX25_1 = 1;


     type  P_X25node = ^T_X25node;
           T_X25node = record

             UZOL     : TX25name;          { miesto       }
             NAME     : TX25name;          { pseudoadresa }
             ADR      : TX25name;          { X25 adresa   }

             LETVIS   : bool;              { patri do siete LETVIS/FDP ? }
             PROL     : bool;              { true -> novy protokol }

             CHAN     : S16BIT;            { otvoreny kanal                                      }
             OPEN     : BOOL;              { prisla odpoved na poziadavku na spojenie            }
             STATUS   : U8BIT;             { stav stanice->0=odpojena,1=caka,2=vysiela,3=prijima }

             {$IFDEF BRIDGE}
               netnd  : int
             {$ENDIF}
           end;

           T_X25nodes = array[0..maxX25_NODEs-1] of P_X25node;
           P_X25nodes = ^T_X25nodes;


     type  PO_X25nodes = ^O_X25nodes;
           O_X25nodes  = object(TDynamic)
             (*
             nodesX25  : int;  {= -1;       pocet stanic v sieti - v konf. subore X25.cfg }
             nodesX25_ : int;  {= -1;       pocet stanic v sieti X25 - vsetky konf.subory }

             X25node   : int;  {= -1;       cislo uzla v strukture X25nodes               }
             X25bridge : int;  {= -1;                                                     }
             *)

             NODE : P_X25nodes;


             constructor Init;

             function    Add (p: pointer): int; virtual;
             function    AddNode (UZOL,NAME,ADR: TX25name; PROL: bool; LETVIS: bool): int;

             procedure   read_cfg(var _err: bool);

             function    isX25name(var X25name: TX25name): int;
             function    isX25adr (adr: TX25name; svc: byte): int;
             function    isX25chan(chan: U16BIT; svc: byte): int;
           end;
