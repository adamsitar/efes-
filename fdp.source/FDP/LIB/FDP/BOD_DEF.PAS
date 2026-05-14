{
  Struktury pre spracovanie v poli trat...
}
{$I comp.h}

unit Bod_def;


interface


    uses    TypeDef,
            FIR_def, _L4_def,
            Lists;


    const   pathDATA = pathLST;


   { Premenne pre bodov FIR
   }
            {$I sym_def.h}       { struktura cfg subora bodov }

    type    TOBtyp = TSymType;   { vid sym_def.h }

            POBine = ^TOBine;
            TOBine = record
              icao_kod   : string[kod_NDB];
              podriadene : bool;
              sector     : pointer;
            end;

            PsBod  = ^TsBod;
            TsBod  = record
              kod  : string[kod_OB];
              x,y  : real;

              typ  : TOBtyp;
              ine  : TOBine;
            end;


            TsBods = array[0..1000-1] of TsBod;
            PsBods = ^TsBods;


            TP_init_OBine = procedure(s: string; var ine: TOBine);
            PP_init_OBine = ^TP_init_OBine;

            TP_done_OBine = procedure(var ine: TOBine);
            PP_done_OBine = ^TP_done_OBine;


    function get_OBtyp (s: string): TOBtyp;


   { Premenne pre popis bodov trate letu
   }
    const   max_OB  = 100;            { DEkodOVANA TRAT - En-ROUTE FPL ... }

    type    PAP_ = ^TAP_;
            TAP_ = record             { POPIS LETISKA DEP, ARR ... }
              kod : string[kod_AP];   { -------------------------- }
              h,m : byte;
            end;


    type    PAP = ^TAP;
            TAP = record
              kod : string[kod_AP];
              ind : int;
              h,m : byte;
              cas : real
            end;


    type    PNDB = ^TNDB;             { BOD TRATE ... }
            TNDB = record
              kod   : string[kod_NDB]; { meno, ak by nebolo zname      }
              h,m   : byte;           { realny  --//--                }
            end;

            POB_ = ^TOB_;
            TOB_ = record
              kod   : string[kod_OB]; { meno, ak by nebolo zname      }
              h,m   : byte;           { realny  --//--                }
              cas   : real;
              vys   : word;           { vyska [S] pridelena operatorom }
              vysab : char;           { climb A - dive B              }
            end;

            POB = ^TOB;
            TOB = record
              kod   : string[kod_OB]; { meno, ak by nebolo zname      }
              ind   : int;            { ind ukazuje do pola suradnic  }
              h,m   : byte;           { realny  --//--                }
              cas   : real;           { realny cas pre vypocet polohy }
              vys   : word;           { vyska pridelena operatorom    }
              vysab : char;           { climb A - dive B              }
              {$IFDEF DATA_OB}
               pozn : byte            { priznak : napr. MZP }
              {$ENDIF}
            end;

            PTrat = ^TTrat;           { TRAT En-ROUTE LETU ... }
            TTrat = array[0..max_OB-1] of TOB;


    const   OBxy_PLAN = $01;          { otocny bod je dolezity }
            OBxy_MZP  = $02;          { MZP }

    type    POBxy = ^TOBxy;
            TOBxy = record            { DEKODOVANA TRAT - MIL FPL ... }
              kod  : string[kod_SP];  { meno, ak by nebolo zname; bolo kod_OB }
              h,m  : byte;            { realny  --//--                }

              x,y  : real;            { suradnice bodu      }
              casA : real;            { cas priletu na bod  }
              casD : real;            { cas odletu z bodu   }

              rych  : single;         { rychlost v km/h     }
              rych_ : char;           { velicina            }

              vys   : word;           { vyska               }
              vys_  : char;           { velicina G,H        }
              vysab : char;

              pozn : byte             { priznak : napr. MZP }
            end;

            TOBxys = array[0..max_OB-1] of TOBxy;
            POBxys = ^TOBxys;


    type    T_suradnice_a_vyska_trate = procedure(p: pointer; bodov,bod: int; var x,y: real; var vys: word);
            P_suradnice_a_vyska_trate = ^T_suradnice_a_vyska_trate;

            T_cas_suradnice_a_vyska_trate = procedure(p: pointer; bodov,bod: int; var cas, x,y: real; var vys: word);
            P_cas_suradnice_a_vyska_trate = ^T_cas_suradnice_a_vyska_trate;


    type       Tis_bod = function (kod: string; var B: TsBod; vsetky: bool): bool;
    function   _is_bod (kod: string; var B: TsBod; vsetky: bool): bool;
    const      is_bod : Tis_bod = _is_bod;


    function   chg_AP   (A1,A2: TAP): bool;
    function   chg_AP_  (A1,A2: TAP_): bool;
    function   chg_NDB  (O1,O2: TNDB): bool;
    function   chg_OB_  (O1,O2: TOB_): bool;
    function   chg_OBxy (O1,O2: TOBxy): bool;


implementation

 uses  str0;


 function _is_bod (kod: string; var B: TsBod; vsetky: bool): bool;
    begin
      _is_bod:= true
    end;

 function chg_AP (A1,A2: TAP): bool;
    begin
      chg_AP:= not (    (A1.kod=A2.kod)
                    and (A1.h=A2.h)
                    and (A1.m=A2.m)
                   )
    end;

 function chg_AP_  (A1,A2: TAP_): bool;
    begin
      chg_AP_:= not (    (A1.kod=A2.kod)
                     and (A1.h=A2.h)
                     and (A1.m=A2.m)
                    )
    end;

 function chg_OB_  (O1,O2: TOB_): bool;
    begin
      chg_OB_:= not (    (O1.kod=O2.kod)
                     {and (O1.h=O2.h)
                     and (O1.m=O2.m)}
                     and (O1.cas=O2.cas)
                     and (O1.vys=O2.vys)
                     and (O1.vysab=O2.vysab)
                    )
    end;

 function chg_NDB  (O1,O2: TNDB): bool;
    begin
      chg_NDB:=     (O1.kod<>O2.kod)
                 or (O1.h<>O2.h)
                 or (O1.m<>O2.m)
    end;


 function chg_OBxy (O1,O2: TOBxy): bool;
    begin
      chg_OBxy:= not (    (O1.kod=O2.kod)
                      and (O1.h=O2.h)
                      and (O1.m=O2.m)

                      and (O1.rych=O2.rych)
                      and (O1.rych_=O2.rych_)

                      and (O1.vys=O2.vys)
                      and (O1.vys_=O2.vys_)
                      and (O1.vysab=O2.vysab)
                     )
    end;


 function get_OBtyp (s: string): TOBtyp;
    begin
      s:= uni_str(s);

      if      pos(prizn_CLet,s)>0     then get_OBtyp:= sym_CLet
      else if pos(prizn_MLet,s)>0     then get_OBtyp:= sym_MLet
      else if pos(prizn_ALet,s)>0     then get_OBtyp:= sym_ALet

      else if pos(prizn_NONE,s)>0     then get_OBtyp:= sym_NONE
      else if pos(prizn_OB,s)>0       then get_OBtyp:= sym_OB
      else if pos(prizn_REPORT,s)>0   then get_OBtyp:= sym_REPORT
      else if pos(prizn_SECTOR,s)>0   then get_OBtyp:= sym_SECTOR
      else if pos(prizn_REP1,s)>0     then get_OBtyp:= sym_REP1
      else if pos(prizn_REP2,s)>0     then get_OBtyp:= sym_REP2
      else if pos(prizn_NDB1,s)>0     then get_OBtyp:= sym_NDB1
      else if pos(prizn_NDB2,s)>0     then get_OBtyp:= sym_NDB2
      else if pos(prizn_VOR,s)>0      then get_OBtyp:= sym_VOR
      else if pos(prizn_VOR_DME1,s)>0 then get_OBtyp:= sym_VOR_DME1
      else if pos(prizn_VOR_DME2,s)>0 then get_OBtyp:= sym_VOR_DME2

      else get_OBtyp:= sym_OB
    end;


end.