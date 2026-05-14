{
   Mozno by stalo za to, zamysliet sa a mat len jednu vseobecnu proceduru,
   ktora bude vediet, ktore polia dekodovat podla hlavicky a nasledujucich
   tabuliek, kde x - povinne pole
                 o - volitelne pole
                 l - novy riadok.
   Vyznam poli je popisany v _L4fpl.h.


  ------------------
   spravy ICAO
  תתתתתתתתתתתתתתתתתת
  תתתתתתתתתתתתתתתתתת

  תתתתתתתתתתתתתתתתתת
   ALR               - stav nudze
  תתתתתתתתתתתתתתתתתת
   3  5  7  8  9  10 13 15 16 18 19 20
   x  x  xl x  xl x  xl xl xl xl xl xl


  תתתתתתתתתתתתתתתתתת
   RCF               - strata spojenia
  תתתתתתתתתתתתתתתתתת
   3  7  21
   x  x  x


  תתתתתתתתתתתתתתתתתת
   FPL
  תתתתתתתתתתתתתתתתתת
   3a 3b 3c 7a 7b 7c 8a 8b 9a 9b 9c 10a 10b 13a 13b 15a 15c 15c 16a 16b 16c 18 221 22b
   x  o  o  x  o  o  x  o  o  x  x  x   x   x   x   x   x   x   x   x   o   x   x   x

  (FPLPL/MI998
   -6506
   -IF
   -01ZZZZ/L
   -F/C
   -LKPO1200
   -K0500F080 MZ650 MZ260
   -LKPD0040 LKNA
   -OPR/34 RMK/UKOL03 RMK/MNM0112 TYP/L39
   )

  תתתתתתתתתתתתתתתתתת
   CHG
  תתתתתתתתתתתתתתתתתת
   3a 3b 3c 7a 7b 7c 8a 8b 9a 9b 9c 10a 10b 13a 13b 15a 15c 15c 16a 16b 16c 18 22a 22b
   x  o  o  x  o  o                         x                   x               x   x

  (CHGPL/MI6
   -6502
   -LKKV
   -LKKB
   -9/MG21/M 16/LKKB0158 15/K0400F080 MZ140 MZ121 MZ332 9/MG23/M
   -8/V        - poli _22 moze byt i viacej
   -8/I
   )

  תתתתתתתתתתתתתתתתתת
   DLA
  תתתתתתתתתתתתתתתתתת
   3a 3b 3c 7a 7b 7c 8a 8b 9a 9b 9c 10a 10b 13a 13b 15a 15c 15c 16a 16b 16c 18 221 22b
   x  o  o  x  o  o                         x                   x

  (DLAMI/PR680
   -6502
   -LKKV2150
   -LKKB
  )

  תתתתתתתתתתתתתתתתתת
   CNL
  תתתתתתתתתתתתתתתתתת
   3a 3b 3c 7a 7b 7c 8a 8b 9a 9b 9c 10a 10b 13a 13b 15a 15c 15c 16a 16b 16c 18 221 22b
   x  o  o  x  o  o                         x                   x

  (CNLMI/PR680
   -2587
   -LKCV
   -LKCV
   )

{ תתתתתתתתתתתתתתתתתת
   ABI
  תתתתתתתתתתתתתתתתתת
   3a 3b 3c 7a 7b 7c 13a 14a 14b 14c 14d 14e 16a 22-> 8a 8b 9a 9b 9c 10a 10b 15a 15b 15c 18
   x  x     x  x  x  x   x   x   x   o   o   x   o    o  o  o  x  x  o   o   x   x   x   o

{ תתתתתתתתתתתתתתתתתת
   ACT
  תתתתתתתתתתתתתתתתתת
   3a 3b 3c 7a 7b 7c 13a 14a 14b 14c 14d 14e 16a 22-> 8a 8b 9a 9b 9c 10a 10b 15a 15b 15c 18
   x  x     x  o  o  x   x   x   x   o   o   x   o    o  o  o  x  x  o   o   x   x   x   o

  (ACTMI/PR680
   -2587/2474
   -LKCV
   -ML281/1650F180
   -LKCV
   -9/02MG21/L
   -15/K0800F180 ML281 MC631 MC834 MF411 MF711 MB364 ME512 ML264
  )

}
