
      type   TProc_BodXY = procedure(Bod: PGBod; var X,Y: long);

      function  new_GP_KruhPriestor(idn: string; polomer: int): PTMapOb; far;

      {$IFDEF MAPY}
       var  BodXY: TProc_BodXY;
      {$ENDIF}


      type  TPolohaGrObs = (pgo_mimo,pgo_rovnobezne,pgo_totozne,pgo_prienik,pgo_prienik_mimo);


      function  prienik_bod       (Mapy: PMapy; MapNaz: string;
                                   x,y: real
                                  ): bool;

      function  prienik_usecka    (Mapy: PMapy; MapNaz: string;
                                   x1,y1, x2,y2: real
                                  ): bool;

      function  prienik_useciek   (Mapy: PMapy; MapNaz: string;
                                   x1,y1, x2,y2: real;
                                   var X,Y: real
                                  ): bool;

      function  prienik_trat      (Mapy: PMapy; MapNaz: string;
                                   trat: pointer; bodov: int;
                                   trat_x,trat_y: pointer
                                  ): bool;

      function  prienik_priestorov (Mapy: PMapy; MapNaz1,MapNaz2: string): bool;


      function  blizsi_bod_xy  (X,Y, x1,y1,x2,y2: real; var Xi,Yi: real): bool;
      function  blizsi_bod_zs  (Zd,Zs, Zd1,Zs1,Zd2,Zs2: TZdZs; var _Zd,_Zs: TZdZs): bool;

