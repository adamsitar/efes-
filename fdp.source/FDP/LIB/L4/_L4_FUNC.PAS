{ ---------------------------------------------------------------
  L4444
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

 תתתתתתתתתתתתתתתתתתתתתתתתת
  (c) ALES 1999,  Kosice,
 תתתתתתתתתתתתתתתתתתתתתתתתת

  Dodatok 3 - obsah a formy sprav letovych prevadzkovych sluzieb

   - kodovanie parametrov FPL podla ICAO (L4444)
   - implementovane funkcie pre spracovanie FPL
}

{$I comp.h}


unit _L4_func;


interface


    uses  TypeDef,
          Lists,
          NET_def,
          _L4_def, _FDP_def;


    {$I _L4F_vys.h}       { vyska                 }
    {$I _L4F_plan.h}      { ine udaje             }
    {$I _L4F_9.h}         { typ lietadla          }


implementation

uses  bios, io, mem, keyb, math, str0, utime, sets, prnt,
      _MTK_2, FIR_def, Bod_def, Body;

{$I _L4F_vys.inc}
{$I _L4F_plan.inc}
{$I _L4F_9.inc}
{$I _L4F_9lst.inc}
{$I _L4F_9data.inc}
{$I _L4F_ini.inc}

begin
  init_l4_variables;
end.