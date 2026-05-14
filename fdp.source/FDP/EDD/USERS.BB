; ===============================================
; NET configuration
; ATCC Kiev
; EDD K2/DNEPROPETROVSK
; -----------------------------------------------

; -----------------------------------------------------------------------------------------------------------------------
; Workplace Name            ; Address : Logical, RTR, IP    ; Protocol ; Workstation  ; Information
; -----------------------------------------------------------------------------------------------------------------------

; -------------------------
; SERVER positions
; -------------------------

  AFTN1                     ; S1      , $0032               ; ~RTI ~L ; @SERVER ~NX @PRN ; -master  FPLC
  AFTN2                     ; S2      , $0033,              ; ~RTI ~L ; @BSERVER         ; -master  FPLC

  server PRN  [BGU/MPU]     ; PRN     , $0034,              ; ~RTI    ; @STRIPPRN     ;        FPLC FPLM FPLO


; -------------------------
; SECTOR positions
; -------------------------

; K4 RDP - KIEV APP         ; K4_RDP  , $0005,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS
  K4/KIEV APP               ; K4      , $0006,              ; ~RTI ~L  ; @EDD         ;        MSG

; K3 RDP - LVOV             ; K3_RDP  , $0007,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS
  K3/LVOV                   ; K3      , $0008,              ; ~RTI ~L  ; @EDD         ;        MSG

; PSP                       ; PSP     , $0009,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS

; K1 RDP - MOSKVA,KHARKIV   ; K1_RDP  , $000A,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS
  K1/MOSKVA,KHARKIV         ; K1      , $000B,              ; ~RTI ~L  ; @EDD         ;        MSG

; P1 RDP                    ; P1_RDP  , $000C,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS
  P1 EDD                    ; P1      , $000D,              ; ~RTI ~L  ; @EDD         ;        MSG

  K2 RDP - DNEPROPETROVSK   ; K2_RDP  , $000F,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS
  K2/DNEPROPETROVSK         ; K2      , $0010,              ; @THIS

; K5 RDP - ODESSA           ; K5_RDP  , $0011,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS   @SECTOR
  K5/ODESSA                 ; K5      , $0012,              ; ~RTI ~L  ; @EDD         ;        MSG

; MIL RDP                   ; MIL_RDP , $0013,              ; ~RTI     ; @RDP         ; -slave FPLC FPLM FPLO PRS
  MIL                       ; MIL     , $0014,              ; ~RTI ~L  ; @EDD         ;        MSG
