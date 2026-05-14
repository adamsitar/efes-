; -------------------------------------------------------------------
; File contains possible directions or departures of inbound flights
; through input/output points
; -------------------------------------------------------------------

; -------------
; File format :
; תתתתתתתתתתתתתתת--------------------------------------------------------------------
; POINT  (RTE)  ; ANOTHER POINT + ANOTHER POINT DIRECTION1 DIRENCTIONS2, DIRECTIONS3
; -----------------------------------------------------------------------------------
; -------
; Rules :
; תתתתתתת
;
; - ANOTHER POINT is PREVIOUS ANOTHER POINT
; - There is necessary one space on the start of the third array (; ).
;



; ------------
; Belorus FIR
; ------------

  ABROK  (A263) ; UL UM UU  B C E       ;

  BORAT  (G38D) ; ABROK                 ; ~FLI
  LAKTA  (A68)  ; BORAT                 ; ~FLI
         (W544) ;
         (W569) ;

  LOVIK  (W531) ; BORAT                 ;


; ------------
; Russian FIRs
; ------------

  SM     (R22)  ; UE UH UI UL UM UN UO UR US UU UV UW 
         (W591) ;
  PIMEN  (R22)  ; SM                    ; ~FLI  ƒ’‚
  BUGOR         ; SM                    ; ~FLI


; -------------------
; UKHH [FIR Kharkiv]
; -------------------

  RAPAN  (W560) ; UKC UKD UKH UKF  SM  UT  A N G H N O P R S V W Z
  ERBIS  (W560) ; RAPAN
  RS     (A137) ; ERBIS UA UB UG                                     ; MATEG UKKH KUBOK KUROK NALEG FORMA SFERA FAZAN
  UKHP   (W672) ; RS


; -----------
; UKHH/UKDD
; -----------

  PEKIT  (A83)  ; UKC UKD UKH UKF UKO  UA UB UE UG UH UI UN UM UR US UT UU UV UW  A F H O N R P S V W Z ; DOMEK SONEP UKFF TIMOS UKDD LUGAT TAMAK NALEM GAWOL FUROR ODRAL KIMBA KIROW BURDA HORTA


; --------------------------
; UKDD [FIR Dnipropetrovsk]
; --------------------------

  KU     (W630) ; RAPAN
  UKHH   (W531) ; RAPAN

; ----------
; UKDD/UKKG
; ----------

  DEKAD  (A87)  ; RAPAN    ; DOMEK SONEP UKFF TIMOS UKDD LUGAT TAMAK NALEM GAWOL FUROR ODRAL KIMBA KIROW BURDA HORTA


; -----------------
; UKOO [FIR Odesa]
; -----------------

  SADKO  (A28)  ; UKH UKI UKF UKO  UA UB UE UG UH UI UR US UT  A D F G H L N O P R S T V W Z  ; REMBO UKOO BAGAN GINDA IRMAL KIWOK SH
  SAVOR  (W575) ; SADKO                                                                       ; REMBO UKOO BAGAN GINDA IRMAL KIWOK SH
  DILOR  (W575) ; SADKO                                                                       ; REMBO UKOO BAGAN GINDA IRMAL KIWOK SH


; ------------------
; UKKG [Kirovograd]
; ------------------

  ERKAD  (W691) ; RAPAN
  ELDOP  (W675) ; ERKAD UKH UKI UKF UKO  UA UB UE UG UH UI UR US UT  A D F G H L N O P R S T V W Z
  RAHMA  (W673) ; UKH UKI UKF UKO  UA UB UE UG UH UI UR US UT  A D F G H L N O P R S T V W Z

  KESAM  (W570) ; RAHMA                                   ; PESON
  BRATY  (A230) ; KESAM                                   ; PESON

  MILKY  (W670) ; SADKO BRATY
  AKROS  (W671) ; MILKY

  SITNA  (A142) ; DEKAD SADKO                             ; DOMEK SONEP UKFF TIMOS UKDD LUGAT TAMAK NALEM GAWOL FUROR ODRAL KIMBA KIROW EKTIN BURDA HORTA
  ROTMA  (W669) ; SITMA                                   ; EKTIN

  UKKG   (W672) ; UKK ROTMA


; -----------------
; UKKL [FIR Lviv]
; -----------------

  POLOS  (W571) ; UKL UKI B C D E F G H K L M O S T       ; LONLA LUGIR UKLL MALBE TAKON IZMAL VI IVF DIBED LURIK HIMIK
  SW     (R22)  ; POLOS                                   ; LONLA LUGIR UKLL MALBE TAKON IZMAL VI IVF DIBED
  BANAR  (A87)  ; UKL  B C D E F G H K L M P S T          ; ABRAD USTIL
  KORES  (W612) ; BANAR                                   ; ABRAD

; ------------
; Vinnytsia
; ------------

; MISSING POINT (W671) ! ! !

  GAWOR  (G38)  ; POLOS SADKO
  KEFIR  (G38)  ; LOKAR PS GAWOR ƒ’‚

  POGER  (G38)  ; POLOS SADKO LU UKL UKO UKB              ; NE KEFIR LURIK
  KAZAT         ; POGER                                   ; NE KEFIR

