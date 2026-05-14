{ ---------------------------------------------------------------
  L4444
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

 תתתתתתתתתתתתתתתתתתתתתתתתת
  (c) ALES 1996,  Kosice,
 תתתתתתתתתתתתתתתתתתתתתתתתת

  Dodatok 3 - obsah a formy sprav letovych prevadzkovych sluzieb

   - kodovanie parametrov FPL podla ICAO (L4444)
   - implementovane funkcie pre spracovanie FPL
}

{$I comp.h}


unit _L4_def;


interface


    uses  TypeDef,
          keyb,
          Lists,
          FIR_def, NET_def;


    {$I _L4_odd.h}
    {$I _L4_head.h}       { typy sprav            }

    { I _L4_cnst.h}       { rozsahy poloziek      }

    {$I _L4_utc.h}        { datum, cas            }
    {$I _L4_vys.h}        { vyska                 }
    {$I _L4_rych.h}       {                       }
    {$I _L4_bod.h}        { zemepisne suradnice   }

    {$I _L4__5.h}         { popis nudze           }
    {$I _L4__7.h}         { identifikacia letu    }
    {$I _L4__8.h}         { typ letu              }
    {$I _L4__9.h}         { typ lietadla          }
    {$I _L4__10.h}        { vybavenie             }
    {$I _L4__14.h}        { vstupny bod           }
    {$I _L4__AP.h}        { 13,16,17              }
    {$I _L4__15.h}        { trat                  }
    {$I _L4__18.h}        { poznamka              }
    {$I _L4__22.h}        { poznamka              }

    {$I _L4_sets.h}       { pripustne mnozienky   }
    {$I _FPL4_arrays.h}   { slovny popis poli FPL }

    {$I _L4_str0.h}
    {$I _L4_func.h}
    {$I _L4_err.h}


implementation

uses  bios, io,mem, math, str0, utime, sets, prnt,
      _MTK_2;


 {$I _L4_head.inc}

 {$I _L4_utc.inc}   { cas, datum  }
 {$I _L4_bod.inc}   { bod, zemsur }
 {$I _L4_vys.inc}   { vyska       }
 {$I _L4_rych.inc}  { rychlost    }

 {$I _L4__5.cod}
 {$I _L4__7.cod}
 {$I _L4__8.cod}
 {$I _L4__9.cod}
 {$I _L4__10.cod}
 {$I _L4__14.cod}
 {$I _L4__AP.cod}
 {$I _L4__18.cod}

 {$I _L4_functions.inc}
 {$I _L4_str0.inc}
 {$I _L4_err.inc}

end.