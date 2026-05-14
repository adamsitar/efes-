 { ==============================
    Spracovanie sprav FPL4...
   ------------------------------

   FPL4 :

   1. EDITOR -> zaradenie FPL4->FDR,
                ak je FDR aktivny alebo sa tyka aktivnej spravy FPLC,
                tak sa zaradi a rozosle i nova/opravena sprava FPLC.
                [FPL4,FPLC -> NET]

   2. NET    -> zaradenie FPL4->FDR,
                ak sa sprava tyka aktivnej spravy FPLC, tak ze ju zrusi
                alebo ukonci, tak sa zaradi i opravena sprava FPLC,
                ale nerozosiela. Inak FPLC pride od zdroja spracovania.
                [NET->FPL4,FPLC]

   3. EXT    -> zaradenie FPL4->FDR, ak je bez chyb, inak sa vlozi do
                chyboveho radu. Ak sa sprava tyka aktivnej spravy FPLC,
                alebo spravy, ktora by sa uz mala aktivovat, tak sa
                objavi okno s opravenym planom - vid "EDIT".

 }


{ Povodna analyza :

  ----------------------------------------------------
   I. CASOVA NASLEDNOST SPRACOVANIA PLANOV
  ----------------------------------------------------

    1. Vsetky spravy FPL (*)

    ³
    ֳִִִִ PLAN
    ³
  P ³   -prijate              - AFTN, server,...
    ³   -nacitane             - inicializacia programu alebo dat z DB FPL a RPL
    ³   -podane spravy o FPL  - vstup z editora
  L ³
    ³   dekodovanie trate
    ³   pripadne schvalenie
  A ³
       Prechadzaju cez objekt FPD, ktory rozhodne o ich dalsom spracovani.
    ³
  N ³

    2. FPL na dalsie dni ostavaju ulozene v subore.
  ת
    ³

  ת 3. FPL na dany den sa kontoluju na  ת povolenie ku realizacii letu
                                        ת cas aktivacie/upresnujuce spravy
    ³
  ת ³
    ³   a) povolenie ku realizacii letu :
    ³   ---------------------------------
  ת ³    Zahranicni dopravcovia (okrem preletov) startujuci a pristavajuci
    ³    na uzemi sektoru FIRu musia dostat povolenie. To chodi na 24 hodin
    ³    vo formate PLN.
  ת ³
    ³
    ³   b) zivotne cykly planu :
  ת ³   -------------------------
    ³    Plan letu sa vyvvija nasledujucim sposobom :
    ³
    ³
  P ֳִִִִ INACTIVE     : Plan vytvoreny (*), pristupny vsetkym operatorom.
  R ³                    Plan je na disku/v pamati ako plan na den
  E ³
  A ֳִִִִ PROPOSED     : Plan je zaradeny ako ocakavany,
  C ³                    moze byt poskytnuty i proceduralnym riadiacim (v prvej verzii programu nie).
  T ³                    Zaradi sa do okna ocakavanych planov.
  I ³                    T_FPL_PROPOSED
  V ³
  E ֳִִִִ COORDINATED  : Prechodny stav pre oznacenie casoveho obdobia, ked sa
    ³                    a) automaticky aktivuje (ak je schvaleny a nadisiel cas EET/DEP-limit)
    ³                       (T_FPL_COORDINATED)
    ³                    b) manualnej aktivacii/koordinacii
    ³                       (prijate spravy CPL,EST, ACT,ABI, DEP pre lety z FIRu...)
    ³                    c) aktivacii z EDD/RDP
    ³
    ³                    Plan je v stave do casu EET/DEP, do stavu ACTIVE prejde
    ³                    na zaklade aktivacie do stavu ACTIVE, t.z. rozosiela sa.
    ³
    ³                    Priradzuje sa SSR kod automaticky/manualne podla nastavenia programu.
    ³
    ³
  A ֳִִִִ ACTIVE       : Plan zaradeny v riadiacom systeme EDD/RDP
  C ³                    Plan je opravovany len sektorom, ktory ho riadi alebo pracoviskom FDO.
  T ³
  I ³                    Zahrna vsetky stavy letu : start, leti, MZP, pristatie
  V ³
  E ³
    ³
    ³
    ֳִִִִ CANCELED
          FINISHED     : Zrusene plany alebo realizovane lety


    4. O planoch sa vedie informacia v DB subore, sluzi pre spracovanie
       zaverecnej statistiky a pomaha rychlejsiemu nabehu programu.


    Pozn. Typ DcFPL sa pouziva ako overeny starsi typ,
          FDR je medzistupnom,
          pretoze ho este nestihol nahradit...

  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת


  ----------------------------------------------------
   II. SPRACOVANIE PLANOV
  ----------------------------------------------------

   Akykolvek prijaty zdojovy plan (FPL,PLN,...) alebo
   ina sprava sa transformuje na FPL.

   ( FPL su ulozene v subore, v pamati su len referencie
     na preaktivovane, aktivovane, ...
   )

}
