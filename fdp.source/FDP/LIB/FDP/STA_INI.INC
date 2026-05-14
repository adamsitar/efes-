 var  SaveExit : pointer;
      SaveMain : TProc;


 procedure check_STA; far;
     begin
       if @SaveMain<>nil then SaveMain;
       if StatistikaAPP<>nil then StatistikaAPP^.Check
     end;


 procedure done_STA;
     begin
       ExitProc:= SaveExit;
       if StatistikaAPP<>nil then Dispose(StatistikaAPP,Done);
     end;

 procedure init_STA(p_StaFDP: POStaAPP);
     var   i: int;
     begin
       StatistikaAPP:= p_StaFDP;
       if StatistikaAPP=nil then Exit;

       SaveExit:= ExitProc;
       ExitProc:= @done_STA;

       SaveMain:= ACheckProcessesA;
       ACheckProcessesA:= check_STA;
     end;



(* Povodny cfg subor...

; -----------------------------------------------------
;  N zvy a parametre pre sledovan‚ ¨tatistick‚ hodnoty
; -----------------------------------------------------

;parametre

 FL-LC = M7450
 FL-LM = M7450
 FL-LO = M0300

 O = o
 O_= odoslan˜ch

 P = p
 P_= prijat˜ch

 S = s
 S_= schv len˜ch

 Z = z
 Z_= zamietnut˜ch

 R = r
 R_= realizovan˜ch


;dekodovane sledovane hodnoty

 LC      ; Lety po tratiach LPS
 LC-FL   ;  - z toho nad %FL-LC%
 -
 FPLM    ; Pl ny vojensk˜ch letov
 LM      ; - vykonan‚ vojensk‚ lety
 LM-IFR  ;  - z toho letov IFR
 LM-FL   ;  - z toho letov nad %FL-LM%
 LM-PRS  ;  - z toho letov do LZR a TSA
 LO      ; - vykonan‚ in‚ lety
 LO-FL   ;  - z toho letov nad %FL-LO%
 -
 ZAM     ; Zamestania letiska
 ZAM-O   ; Zamestania podriaden˜ch let¡sk
 -
 QGO     ; Hl senie o zmena schopnost¡
 -
 DVZ-S   ; Diverzie vlastn‚
 DVZ-R   ; Diverzie pre in‚ letisk 
 -
 PRZ     ; ’iadosti o pridelenie priestoru
 PRS     ; Pl ny vyu‘itia vzdu¨n‚ho priestoru
 PRS-R   ;  - z toho priestorov "R"
 PRS-TSA ;  - z toho priestorov "TSA"
 -
 MSG-S   ; Spr vy - odoslan‚
 MSG-R   ; Spr vy - prijat‚
 -
 -
 SERVER  ; Po‡et preru¨en˜ch spojen¡ so SRLP

*)
