{
   -  odvodeny objekt aplikacie riesi konkretne pripojenie na vstup dat,
      buffrovanie a vstup do dekodovacej rutiny
   -  obmedzenie: ak posielam data cez IPX, ich dlzka je obmedzena
   -> implementacia SaveMain do objektu predpoklada, ze objekt
      po inicializacii zostane <> nil (zit) az do konca programu !
   -> pouzivany kruhovy buffer zatial (skoda) nedrzi informaciu
      o dlzke bufferov, a rutina pre spracovanie musi poznat dlzku.
      Aby som teraz nevymyslal novy buffer (je 21.15), tak kazdy objekt
      dediaci vlastnost citania buffera, definuje funkciu get_pkt_size
      a get_pkt_data.
        Treba dat pozor, ak je obsahom buffera i ina polozka ako pole dat,
      napriklad pocet prvkov, pri nacitavani do ibuff treba pocitat s tymto
      javom...

      NEPOUZIVAT PRIAMO v interrupt fukciach..., je linkovany do OVR !
}

{
     úúúúúúúúúúúúúúúúúúúúúúúúúúúúú
      algoritmus spracovania dat:
     .............................

                          ³
            prijem dat zo vstupneho buffera
                          ³
      ak je definovana adresa a nesuhlasi adresa ÄÄÄÄÄ> Exit
                          ³
                identifikacia hlavicky (hlada icao_STD...)
                    ³             ³
              pozna, prepusti   nepozna, alebo nie je v poriadku,
              na spracovanie    zaradi sa do radu nespracovatelnych
              (pripadny vypis)  sprav (zobrazi sa na obrazovke)

                   (LAM sa nevysiela)

                    ³             ³
                    ³            Exit
                    ³
       - Dekodovanie sprav tykajucich sa FPL a ich nasledne spracovanie.
         V pripade chyby odoslanie do radu nespracovatelnych sprav...

       - chyby a vystrahy sa radia do specialnych radov na obsluzenie
          ( ulozenie spravy do subora aftn_err.* (cis)
                                      aftn_alr.*
          )

}