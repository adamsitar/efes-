DOC

- ak je vo frmulari zapisany ssr patciferne, vyhodnocuje sa ako uvd
-




ULOHY --============================================

- prejde 7c do ssr ?


#
7a-10 ; Aircraft identification has been changed from
7a-11 ; to
7a-12 ; Cancel and delete previous plan ? If not plan will be processed as new one.
#

RTE-34  ; Podla zadanych parametrov let bol uz let ukonceny, alebo preletel cez riadenu oblast. Su spravne ?


 - prevrit rec, spracovanie potvrdenia...

 - ak pride synchronizacia casu ina, ako je nastaveny datum alebo lisiaca sa
   o viac ako nastaveny limit... vyziadanie potvrdenia :
        "ano,nie,vypnut synchronizaciu"...

 - doplnit aip do err....

 - nezname "MATEG"... body maju vyhodene len kvoli tomu, ze ich je
   v stripe vela? Maju vela bodov v karte, ktore nie su v cfg...

 - synchoniozacia/rozosielanie rpl...

 ===================
 - zrychlenie zapisovania ack -> pri ack pocka par sec, nacita vsetky od daneho pkt, len rec update...
 ===================

 - date v PLN sa tyka datumu EET alebo DEP ?

 - odmazanie vyrovanynych paketov ESXT synchronizacia sprav...

 - pln,y2k

 - act

 - skontrolvat, aby updateovat FPL4 a distribuovat mohla len master, ak vobec

 - najdenie pln/pre FPL

 - vyhladanie ssr nie podla indexu, ale podla kluca  "ssr:= ssr_of_idn (idn,'');"  = ALR

 - zakazanie rusenia stripa na edd-cku : DECLINE.... HIDE...

 -
====================================================


KACO


 - protected mode ... !!!


STAT

 - radit do... , len ak sa zmeni plan...
 - menu alloc

 - UKBB zakazat rusenie stripu na EDDcku, ak je manualne trekovanie,
   nezrusi sa, len sa skryje...

 - zobraz zodpovedajuci "PLN"


TESTOVAT

 - fpl v strukture FDR
 - nemam istotu v spravnom nastaveni vsetkych premmennych eet,date...
 - spracovanie/prehlad FPL/FDR
 - oFDR, vypisy

 - preverit "fplsrci_update", aby nedoslo ku vkladaniu poznamok "rpl/ pln/ rpl/ pln/ ..."


UPRAVY

 - odsuvanie textu na novy riadok pri exitacii

 - FPL PERM...

 - dbchg sposobi znovu nacitanie planov, co je pomale, preto,
   kazdy fdp viewer by mal nechat odkaz na seba a pri zaradzovani
   planu sa fdp-ecko pokusi ho add: pridat, nasledne opravit alebo
   zmazat a tym nebude db znova reinicialzovana

 - funguje uz rychle vyhladanie ? cez header
 - zapis potvrdenia: specialne dekodovacie fcie pre updating riadku:
   podla head najde, nacita a prepise len danu cast riadka



 - alokacia struktura pre spracovanie ocakavanych povtrdeni
   - po timeoute sa zapise podla nej do udajov....

 - vyrovavanie udajov medzi AFTN1 a AFTN2

 - RPL bin a s novou strukturou...

 - SSR mangement

 - RPL/PLN -> start/pause...


EDD

 - zobrazit parameter lietadla po kliknuti


UROBENE

 - implementovany novy cislenik typov ICAO, s tym urobene potrebne upravy,
   pretoze db sa mohutne nafukla
 - konverzie typov tsga,mil,zzzz na icao
 - preprogramovanie struktur FPL4,PLN do ICAO formatu, spolu s tym
   upravene a zrychlene dekodovanie a spracovanie
 - doplnenie moznosti nastavenia dekodovania a spracovania FPL4
 - binarne databazy
 - zrusenie db a spracovania "FPD"
 - sprehladnenie nastavovavania a moznosti ponukanych menu
 - zrychlena statistiak preletov, odmazanie zruseneho letu
 - uprava spracovania priznakov zdrojov informacii

 - fli sa spracovava miestne a udaje o jeho rozoslani sa posielaju
   na stanice oznacene fli



           {$IFDEF FPL}
    const   FULL_RTE     : bool = true;         { AFTN dekoduje trat so sickymi bodmi    }
            UNKN_RTE     : bool = false;        { AFTN dekoduje trat i z neznamymi bodmi }

            {SSR_DISABLE : bool = true;}        { ? }

            AFTN_cfg     = 'AFTN.cfg';
            SAVE_AFTN_MSG     : bool = true;
            SAVE_ALL_AFTN_MSG : bool = false;
           {$ENDIF}
