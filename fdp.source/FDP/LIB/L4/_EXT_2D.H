{ ----------------------------------------
   ZALOHOVANIE PRACE SERVEROVSKYCH STANIC
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

  1. Zalozny server BACKUP prijima pakety od externeho zdroja paralelne
     s MASTERom. Pakety su prijate, vyhodnoti sa stav spojenia, archivuju
     sa, nie su vsak spracovavane, ale presmerovane na MASTER.

     Na vstupe MASTERA sa odpamatavaju kluce paketov prijatych od externej
     linky EXT. Ak pkt prijaty po sieti od BACKUP nie je v tomto zozname,
     zaradi sa do spracovania.


  2. MASTER spracuje pakety od EXT a BACKUP(ov). Vysledky spracovania
     rozosiela v sulade s konfiguraciou na BACKUP i ostatne pracovne
     stanice :

     a) spracovane udaje o letovych planoch FPL4,FPD,PLN
     b) spravy o chybach v spravach (chybove spravy) (ERROR)
     c) ostatne pakety (TLG,...)
     d) vzajomne sa vymienaju spravy o priebehu spracovania b) c)
        (spracovanie chyby, editacia spravy, spracovnaie spravy/odmazanie spravy)


  3. BACKUP si drzi prijate pakety vo vyrovnavacej pamati, az kym mu na ne
     nepride potvrdenie o ich spracovani alebo nevyprsi ich timeout. V tom
     pripade, ak MASTER nefunguje *, uz ich spracovava a nebufruje. Ak nie,
     tak ich znova odosiela.

  4. V pripade, ze MASTER je O.K., BACKUP spracovava len pakety prichadzajuce
     po sieti a sprava sa tak vlastne, ako ostatne pracoviska na spracovanie
     daneho vstupneho prudu dat.

  *  Informacia o stave hlavnej stanice sa prebera od modulu _NET (SERVERstatus).


  5. Po opatovnom nadviazani spojenia sa musia zosynchronizovat bazy dat.
     - FPL
     - adresare chybovych sprav
     - telegramov,...

}