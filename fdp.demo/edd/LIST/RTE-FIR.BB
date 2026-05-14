; -------------------------------------------
; Standard AWY/CIS routes over FIR UKBB
; תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
;
; IN_POINT ...AWY1 POINT AWY2... OUT_POINT
;

  BANAR A87 SL G38 UKKK DCT UKBB                    ; >
  BANAR A87 DEKAD                                   ; >
  BANAR A87 SL G38 UKKK                             ; >
  BANAR A87 CH R22 PIMEN                            ; >
  BANAR A87 SL G38 UKKK DCT UKBB A137 RS            ; >
  BANAR A87 PI A28 SADKO                            ; >
  BANAR A87 PI A28 SV A230 MILKY                    ; >

  BORAT G38 UKKK DCT UKBB                           ; >
  BORAT G38 UKKK                                    ; >
  BORAT G38 UKKK W511 PI A87 DEKAD                  ; >
  BORAT G38 UKKK W511 PI A28 SV A230 MILKY          ; >
  BORAT G38 POGER                                   ; >
  BORAT G38 UKKK W511 PI A28 SADKO                  ; >
  BORAT G38 UKKK DCT UKBB A137 RS                   ; >
  BORAT G38 UKKK W511 KR R22 SW                     ; >
  BORAT G38 UKKK W575 DILOR                         ; >
  BORAT SL W590 SAWRA                               ; >

  LAKTA W544 UKKK W575 DILOR                        ; >
                                                    ; >
  SW R22 CH A87 SL G38 UKKK DCT UKBB                ; >
  SW R22 CH A87 SL G38 UKKK                         ; >
  SW R22 CH A87 DEKAD                               ; >
  SW R22 KR W511 UKKK G38 LT W544 LAKTA             ; >
  SW R22 PIMEN                                      ; >
  SW R22 CH A87 SL G38 UKKK DCT UKBB A137 RS        ; >
  SW R22 CH A87 PI DCT SV A230 MILKY                ; >
  SW R22 KR UKKK DCT UKBB                           ; >

  POLOS W571 SL G38 UKKK                            ; >
  POLOS W571 SL G38 UKKK DCT UKBB                   ; >
  POLOS W571 SL G38 UKKK W520 KO R22 PIMEN          ; >
  POLOS W571 SL G38 UKKK DCT BULAP A137 RS          ; >
  POLOS W571 SL A87 DEKAD                           ; >
  POLOS W571 SL A87 PI A28 SV DCT SITNA             ; >

  POGER G38 UKKK DCT UKBB                           ; >
  POGER G38 UKKK                                    ; >
  POGER G38 LT W544 LAKTA                           ; >
  POGER G38 UKKK W520 KO R22 PIMEN                  ; >
  POGER G38 UKKK DCT UKBB A137 RS                   ; >
  POGER G38 SL A87 DEKAD                            ; >


  PIMEN R22 KO UKBB                                 ; <
  PIMEN R22 SORNA DA UKBB                           ; <

  SADKO A28 PI W511 UKKK                            ; <
  MILKY A230 SV A28 PI W511 UKKK                    ; <
  SITNA A142 SV A28 PI W511 UKKK                    ; <

  SADKO A28 UKBB                                    ; <
  MILKY A230 SV A28 UKBB                            ; <
  SITNA A142 SV A28 UKBB                            ; <

  SADKO A28 SV W591 SM R22 PIMEN                    ; <
  SADKO A28 UKBB A68 BG W523 KO R22 PIMEN           ; <
  MILKY A230 SV A28 UKBB A68 BG W523 KO R22 PIMEN   ; <
  SITNA A142 SV A28 UKBB A68 BG W523 KO R22 PIMEN   ; <
  MILKY A230 SV W591 SM R22 PIMEN                   ; <
  SITNA A142 SV W591 SM R22 PIMEN                   ; <

  SADKO A28 PI A87 BANAR                            ; <
  MILKY A230 SV A28 PI A87 BANAR                    ; <
  SITNA A142 SV A28 PI A87 BANAR                    ; <

  SADKO A28 PI A87 CH R22 SW                        ; <
  MILKY A230 SV A28 PI A87 CH R22 SW                ; <
  SITNA A142 SV A28 PI A87 CH R22 SW                ; <

  SADKO A28 UKBB A68 LAKTA                          ; <
  MILKY A230 SV A28 UKBB A68 LAKTA                  ; <
  SITNA A142 SV A28 UKBB A68 LAKTA                  ; <

  SADKO SV NAPOR SM PIMEN                           ; <

  AKROS W671 PS                                     ; <

  PEKIT W624 UKKE A87 PI W511 UKKK                  ; <
  UKKE A87 PI W511 UKKK                             ; <

  PEKIT W624 UKKE A87 CH R22 SW                     ; <
  UKKE A87 CH R22 SW                                ; <

  PEKIT W624 UKKE A87 BANAR                         ; <
  UKKE A87 BANAR                                    ; <

  PEKIT W624 UKKE A87 SL W571 POLOS                 ; <
  UKKE A87 SL W571 POLOS                            ; <

  PEKIT W624 UKKE A87 SL G38 POGER                  ; <
  UKKE A87 SL G38 POGER                             ; <

  PEKIT A83 UKBB                                    ; <
  PEKIT A83 UKBB A68 LAKTA                          ; <

  UKKE W537 GE A83 UKBB A68 LAKTA                   ; <

  UKBB A83 GE DCT UKKE A87 DEKAD                    ; <
  UKKB DCT KR R22 SW                                ; <

  UKKK DCT PI A87 DEKAD                             ; <
  UKKK DCT KR R22 SW                                ; <

  DEKAD A87 UKKE                                    ; <

  RS A137 UKBB                                      ; <
  RS A137 UKBB DCT UKKK                             ; <
  RS A137 UKBB DCT UKKK G38 SL W571 POLOS           ; <
  RS A137 UKBB DCT UKKK G38 POGER                   ; <
  RS A137 UKBB DCT UKKK W511 KR R22 SW              ; <
  RS A137 UKBB DCT UKKK W511 KR R22 CH A87 BANAR    ; <
  RS A137 UKBB A68 LAKTA                            ; <

  RAPAN W560 JA A137 UKBB                                       ; <
  RAPAN W560 JA A137 UKBB DCT UKKK                              ; <
  RAPAN W560 JA A137 UKBB DCT UKKK G38 SL W571 POLOS            ; <
  RAPAN W560 JA A137 UKBB DCT UKKK G38 POGER                    ; <
  RAPAN W560 JA A137 UKBB DCT UKKK W511 KR R22 SW               ; <
  RAPAN W560 JA A137 UKBB DCT UKKK W511 KR R22 CH A87 BANAR     ; <
  RAPAN W560 JA A137 UKBB A68 LAKTA                             ; <
