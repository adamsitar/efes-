    { Zaradenie planu do zoznamu aktivnych alebo aktivovatelnych planov
      Pre zaradenie existuju dva pristupy:

      - v pravidelnych intervaloch sa prehliadava databaza planov,
        ktore sa maju preaktivovat - a dostat na obrazovku.

                             A-dA     A             K   H
                             ÃÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÅ...´

        ...ÅÄ...ÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÅÄ...

           T-dA   T            T+dA


           T  .. aktualny cas
           dA .. interval preaktivacie
           A  .. aktivacia (poz_LETI)
           K  .. koniec    (poz_PRIST)
           H  .. zrusenie  (poz_HANGAR)

         if A-dA<=T+dA         => preactived
         if A-dA<=T            => proposed/coordinated
         if A<=T and stat>=dep => actived     -> EST


      - zapamata sa najblizsi planovany cas preaktivacie. Nevyhodou je to, ze
        plany sa mozu preaktivovat kazdu minutu. Preto je definovana tolerancia,
        o ktoru je mozne uvedeny limit "predlzit". Objekt musi rozlisovat medzi
        proposed a preaktived - az tieto sa zobrazia na tablete a planzete, vo
        vypise su obsiahnute vsetky.
    }
