(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 4.2                                              *)
(* (c) Ales Kosice 19(89)93,99  (ab)                                 *)
(* Vytvorenie a spracovanie statistiky                               *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

{
  Algoritmus
  --------------

  Sposob vedenia statistiky je mozny dvoma sposobmi:
   - po ukonceni sledovaneho obdobia sa vytvori sucet za toto obdobie
   - a navyse priebezne, aby bolo mozne priebezne sledovat i dane obdobie

  Tento model statistiky je postaveny na autonommnom vyhodnocovani
  na kazdej pracovnej stanici.

  Algoritmus statistiky predpoklada, ze pocitac musi byt zapnuty neustale,
  aby dokazal vyhodnotit vsetky zmeny stavov udajov (napr. sprava o lete
  moze byt vydana omylom, takze moze byt zrusena). V pripade vypadku sa
  k nemu dostanu len konecne udaje, nie stav ich spracovania.


  Vystupne udaje
  --------------

  Kazdy datovy typ si vytvara pracovny subor "data" s nazvom
  podla obdobia a 'ð'xt, kde sa ukladaju priebezne vysledky
  jeho spracovania za den.

  V subore "suma" s nazvom podla obdobia a 'ä'xt sa ukladaju priebezne
  a po uzatvoreni obdobia konecne numericke vysledky spracovania.

  Kazdy datovy modul vytvara docasne textove subory "work" s nazvom
  podla obdobia a '÷'xt, kde su uvedene vysledky spracovania
  v textovej forme.

  Po uzatvoreni statistiky za dane obdobie maju ext=STD pre den
  a ext=STM pre mesiac, pokial je ich vytvorene dovolene.

  Externy vystup pre Excel je vo formate "CSV" s oddelovacmi poli ";".


  Poznamka
  ----------

  Tento modul sa casom zmenil na abstraktny, pretoze kontretne
  poziadvky sa zmenili zo statistiky jednotlivych tabuliek
  na sumarne tabulky. Novy objekt vyuziva niektore vseobecne
  vlastnosti tohto, najma spravu statisitky jednotlivych
  modulov.s


  Uvaga !
  ----------

  Nesmie byt rozsirovany fciami s konkretnymi datami,
  pretoze by mohli nastat kruhove referencie

}

unit Sta_obj;


interface

    uses  TypeDef, IO,
          {$I unit_oop.h},
          _L4_def,
          Archiv,
          Bod_def, Body,
          _FDP_def, _FPL_def,
          STA_def;


    {$I sta.h}               { konstanty, datove typy }
    {$I sta_cfg.h}           { identifikatory konfigurovatelnych konstant }
    {$I sta_title.h}

    {$I sta_FDP.h}           { vseobecny statistiky objekt datoveho typu  }
    {$I sta_APP.h}           { vseobecny objekt pre vedenie statistiky    }


    {$IFDEF STATISTIKA}
     const  StatistikaAPP : POStaAPP = nil;
    {$ENDIF}


implementation

uses  _Check,
      DOS, BIOS, DB, keyb, str0, math, mem, mess, prnt, utime, sets,
      Hodiny,
      {$I unit_map.h},
      NET_utc, NET_def,
      FDP_msg, FDP_fun2;


{$IFDEF STATISTIKA}

 const _p_handle_event_STATISTIKA : p_proc_handle_object_event = nil;

 {$I sta.inc}             { zakladne fcie pre spracovanie }
 {$I sta_FDP.inc}

 {$I sta_ini.inc}
 {$I sta_APP.inc}
 {$I sta_handle.inc}

begin
  _p_handle_event_STATISTIKA:= p_handle_event_STATISTIKA;
  p_handle_event_STATISTIKA:= @_handle_event_STATISTIKA;
  movefile('STA.kod',kodSTA);
{$ENDIF}
end.