; -------------------------
; File format describtion :
; -------------------------
;
; NDB ; *  ... FIR I/O point
; RTE ; *  ... AWY used by CIS
;
; Route is described by name and points sequence between "(" and ")".
; Input/Output points have assigned possible direction of flight departure/arrival
; according to icao flight zones.



; -------------------------
; ATS ROUTES              :
; -------------------------

 A28
     (
      UKBB
      PI
      SV
      SADKO
     )


 A68
     (
      UKKK
      UKBB
      BG
      MABAT
      LAKTA
     )


 A83        ; "W510"
     (
      PEKIT
      LABOG
      GE
      CY
      UKBB
     )


 A87        ; "W521"
     (
      BANAR
      UKSAT
      CH
      SL
      PI
      KA
      UKKE
      DEKAD
     )


 A137       ; "W517"
     (
      UKBB
      JA
      BABEN
      RS
     )


 A142       ; "W515"
     (
      SV
      SITNA
     )


 A230       ; "W527"
     (
      SV
      MILKY
     )


 A263       ; "W522"
     (
      ABROK
      KR
      KORUN
      SL
     )


 G38        ; "G38D"
     (
      BORAT
      LT
      UKKK
      SL
      POGER
     )


 R22
     (
      SW
      CH
      KR
      PISOK ; -
      KO
      SORNA ; -
      SM
      PIMEN
     )


 W511
     (
      KR
      UKKK
      PI
     )


 W520
     (
      UKKK
      KO
     )


 W523
     (
      BG
      KO
     )


 W525
     (
      UKBB
      DA
      SORNA
     )


 W531
     (LOVIK
      UKHH
     )


 W591       ;**
     (
      SM
      NAPOR
      SV
     )


; -------------------------
; AWY CIS                 :
; -------------------------


 W526
     (
      BG
      PI
     )

 W529
     (
      DA
      CY
      KA
      SV
     )

 W537
     (
      GE
      UKKE
     )

 W539
     (
      BABEN
      POBAN
      BG
     )

 W540
     (
      BABEN
      RILSU
      CY
     )

 W544
     (
      PI
      LT
      LAKTA
     )

 W553
     (
      LT
      UKBB
      KA
     )

 W560       ;**
     (
      JA
      RAPAN
     )

 W569       ;**
     (
      LAKTA
      UKBB
     )

 W571       ;**
     (
      POLOS
      SL
      KO
     )

 W575       ;**
     (
      CH
      KORUN
      UKKK
      TOBON
      SETUR
      DILOR
     )

 W590       ;**
     (
      BORAT
      SL
      SAWRA
     )

 W591       ;**
     (
      SM
      SV
     )

 W610
     (
      LT
      LETOR
      KO
     )

 W611
     (
      TR
      UKKK
      PISOK
     )

 W612
     (
      CH
      KORES
     )

 W613
     (
      SL
      POGER
     )

 W622
     (
      LETOR
      MABAT
     )

 W624
     (
      PEKIT
      OWIDA ; -
      UKKE
      KORNA
      SV
     )

 W630
     (
      KU
      MUKUN ; -
      UKKE
     )

 W660
     (
      KO
      UKBQ
     )

 W661       ; --
     (
      KOLYK
      KOWAR
      SORNA
     )

 W662       ; --
     (
      SORNA
      STOWA
     )

 W667
     (
      CH
      UKKV
      KAZAT
     )

 W668       ;**
     (
      MAPTA
      UKKV
      SL
     )

 W669
     (
      TR
      SV
      ROTMA
     )

 W670
     (
      UKBB
      SV
     )

 W671       ;**
     (
      DEKAD
      AKROS
            ; MISSING IO POINT UKWW-UKBB
     )

 W672       ;**
     (
;     AKROS
      UKKG
      UKKE
      UKHP
     )

 W676       ;**
     (
      GE
      DEKAD
     )

 W680       ;**
     (
      KO
      MABAT
     )

 W696       ;**
     (
      DA
      SM
     )