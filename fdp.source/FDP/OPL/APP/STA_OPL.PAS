(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 4.2                                              *)
(* (c) Ales Kosice 19(89)93,99  (ab)                                 *)
(* - 00: oprava pre prs                                              *)
(* Vytvorenie a spracovanie statistiky                               *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

{ Sposob vedenia statistiky je mozny dvoma sposobmi:
   - po ukonceni sledovaneho obdobia sa vytvori sucet za toto obdobie
   - a navyse priebezne, aby bolo mozne priebezne sledovat i dane obdobie

  Tento model statistiky je postaveny na autonommnom vyhodnocovani
  na kazdej pracovnej stanici.

  Algoritmus statistiky predpoklada, ze pocitac musi byt zapnuty neustale,
  aby dokazal vyhodnotit vsetky zmeny stavov udajov (napr. sprava o lete
  moze byt vydana omylom, takze moze byt zrusena). V pripade vypadku sa
  k nemu dostanu len konecne udaje, nie stav ich spracovania.

=> PREPRACOVAT NA CENTRALNU STATISTIKU NA SERVERI
    -> odoslanie ziadosti a spracovanie subora
    -> vystup podla zdroja ziadosti

}

unit Sta_OPL;


interface

    uses  TypeDef, IO,
          _L4_def, _MTK_2,
          Archiv,
          FIR_def, Bod_def, Body,
          _FDP_def,
          Sta_def, Sta_obj;


    {$IFDEF STATISTIKA_OPL}
     {$I sta_opl.h}
    {$ENDIF}


implementation

uses  _Check, DOS, BIOS, DB, keyb, str0, math, mem, mess, prnt, utime, sets, msg, crt, bgigraph,
      {$I unit_oop.h},
      {$I unit_map.h},
      NET_utc, NET_def,
      {$I unit_fdp.h}
      FDP_msg, FDP_fun2{,
      Hodiny};


{$IFDEF STATISTIKA_OPL}

  type   TFPLM_letov_ = record
          planov    : word;              { podanych planov daneho typu }
          letov     : word;              { realizovanych planov daneho typu }
          riadenych : word;              { riadenych letov inych uzivatelov daneho typu }
         end;
         TFPLM_letov  = array[0..max_AIRBASE] of TFPLM_letov_;


  procedure inc_FPLM_letov(var l1,l2: TFPLM_letov);
      var   i : int;
      begin
        for i:= 0 to max_AIRBASE do
          begin
            inc(l1[i].planov,    l2[i].planov);
            inc(l1[i].letov,     l2[i].letov);
            inc(l1[i].riadenych, l2[i].riadenych);
          end;
      end;


 {$IFDEF FPL0}
  {$I sta_FPLC.h}
  {$I sta_FPLM.h}
 {$ENDIF}
 {$IFDEF PRS}
  {$I sta_PRS.h}
 {$ENDIF}
 {$IFDEF ZAM}
  {$I sta_ZAM.h}
 {$ENDIF}

 {$IFDEF FPL0}            { instancie statistiky datovych typov        }
  {$I sta_FPLC.inc}
  {$I sta_FPLM.inc}
 {$ENDIF}
 {$IFDEF ZAM}
  {$I sta_ZAM.inc}
 {$ENDIF}
 {$IFDEF PRS}
  { I sta_PRS0.inc}
  {$I sta_PRS.inc}
 {$ENDIF}

 {$I sta_ini_.inc}
 {$I sta_tab.inc}
 {$I sta_lsrlp.inc}
 {$I sta_srlp.inc}
 {$I sta_opl.inc}


begin
 StatistikaAPP:= New(POStaOPL,Init(cfgSTA,kodSTA));
 if is_paramstr('%SUMAPRS%')<>'' then konverzia_prs;
{$ENDIF}
end.