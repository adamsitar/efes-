
  { ------------------------
     Prienik bodov
    תתתתתתתתתתתתתתתתתתתתתתתת
  }
  { Ak MapNaz='' vrati false.
  }

  function prienik_bod(Mapy: PMapy; MapNaz: string; x,y: real): bool;
     var   patri,init,is : bool;
     begin
       init:= Mapy=nil;
       if init then
          begin
            Mapy:= New(PMapy,Init);
            is:= (Mapy^.najdi_a_nacitaj_subor(MapNaz)<>nil)
          end
       else is:= true;
       patri:= is and (Mapy^.patri_xy(x,y));
       if init then Dispose(Mapy,Done);
       prienik_bod:= patri
     end;


  function prienik_usecka(Mapy: PMapy; MapNaz: string; x1,y1, x2,y2: real): bool;
     var   x,y : real;
     begin
       prienik_usecka:= prienik_useciek(Mapy, MapNaz, x1,y1, x2,y2, x,y)
     end;


  function prienik_useciek(Mapy: PMapy; MapNaz: string; x1,y1, x2,y2: real; var x,y : real): bool;
     var   patri,init,is, in1,in2, is1,is2 : bool;
           xn,yn: real;
     begin
       init:= Mapy=nil;
       if init then
          begin
            Mapy:= New(PMapy,Init);
            is:= (Mapy^.najdi_a_nacitaj_subor(MapNaz)<>nil)
          end
       else is:= true;
       patri:= Mapy^.priesecnik_xy(x1,y1,x2,y2, in1,in2,is1,is2, x,y,xn,yn);
       if init then Dispose(Mapy,Done);
       prienik_useciek:= patri
     end;


  { Kontrola, ci polygon prechadza oblastou definovanou primitivami.
     - patri niektory z bodov polygonu do oblasti ?
     - pretina nieketora usecka oblast ? (Body mozu byt definovane mimo oblasti).
  }

  function prienik_trat (Mapy: PMapy; MapNaz: string;
                         trat: pointer; bodov: int;
                         trat_x,trat_y: pointer
                        ): bool;
     var   patri,init,is : bool;
           in1,in2, is1,is2 : bool;
           x,y,xn,yn: real;
           i : int;
     begin
       prienik_trat:= false;
       if (trat=nil) or (trat_x=nil) or (trat_y=nil) then Exit;

       init:= Mapy=nil;
       if init then
          begin
            Mapy:= New(PMapy,Init);
            is:= (Mapy^.najdi_a_nacitaj_subor(MapNaz)<>nil)
          end
       else is:= true;
       patri:= false;
       if is then
          begin
            i:= 0;
            while (not patri) and (i<bodov) do
              begin
              { a) nelezi niektory z bodov v priestore polygonu ?
              } patri:= Mapy^.patri_xy(TRFunc_pi(trat_x)(trat,i),TRFunc_pi(trat_y)(trat,i));
                inc(i)
              end;
            if not patri then
               begin
               { b) nepretina trat v priestor ?
               } i:= 0; while (not patri) and (i<bodov-1) do
                   begin
                     patri:= Mapy^.priesecnik_xy(TRFunc_pi(trat_x)(trat,i),  TRFunc_pi(trat_y)(trat,i),
                                                 TRFunc_pi(trat_x)(trat,i+1),TRFunc_pi(trat_y)(trat,i+1),
                                                 in1,in2, is1,is2,
                                                 x,y,xn,yn
                                                );
                     inc(i)
                   end
               end;
          end;
       if init then Dispose(Mapy,Done);
       prienik_trat:= patri
     end;


  function prienik_priestorov(Mapy: PMapy; MapNaz1,MapNaz2: string): bool;
     var   patri,init : bool;
           x,y : real;
           i : int;
     label E;

     begin
       prienik_priestorov:= false;
       if (MapNaz1='') or (MapNaz2='') then Exit;
       (*
       init:= Mapy=nil;
       if init then
          begin
            Mapy:= New(PMapy,Init);
            if    (Mapy^.najdi_a_nacitaj_subor(MapNaz1)=nil)
               or (Mapy^.najdi_a_nacitaj_subor(MapNaz2)=nil)
               then goto E
          end;

       patri:= false; i:= 0;
       while (not patri) and (i<bodov) do
         begin
         { a) nelezi niektory z bodov v priestore polygonu ?
         } patri:= Mapy^.patri_xy(TRFunc_pi(trat_x)(trat,i),TRFunc_pi(trat_y)(trat,i));
           inc(i)
         end;

       if not patri then
          begin
          { b) nepretina trat v priestor ?
          } i:= 0; while (not patri) and (i<bodov-1) do
              begin
                patri:= Mapy^.priesecnik_xy(TRFunc_pi(trat_x)(trat,i),  TRFunc_pi(trat_y)(trat,i),
                                            TRFunc_pi(trat_x)(trat,i+1),TRFunc_pi(trat_y)(trat,i+1),
                                            x,y
                                           );
                inc(i)
              end
          end;

       if init then Dispose(Mapy,Done);
       prienik_trat:= patri
       *)
     end;


  { ------------------------
     Vypocet blizsieho bodu
    תתתתתתתתתתתתתתתתתתתתתתתת
  }
  function  blizsi_bod_xy(X,Y, x1,y1,x2,y2: real; var Xi,Yi: real): bool;
     begin
       if vzdialenost(x,y, x1,y1) <= vzdialenost(x,y, x2,y2) then
          begin
            blizsi_bod_xy:= true;
            Xi:= x1;
            Yi:= y1
          end
       else begin
              blizsi_bod_xy:= false;
              Xi:= x2;
              Yi:= y2
            end
     end;

  function  blizsi_bod_zs(Zd,Zs, Zd1,Zs1,Zd2,Zs2: TZdZs; var _Zd,_Zs: TZdZs): bool;
     var   x,y: real;
     begin
       x:= dlzka(Zd.st,Zd.mn,Zd.se);
       y:= sirka(Zs.st,Zs.mn,Zs.se);
       if    vzdialenost(x,y, dlzka(Zd1.st,Zd1.mn,Zd1.se), sirka(Zs1.st,Zs1.mn,Zs1.se))
          <= vzdialenost(x,y, dlzka(Zd2.st,Zd2.mn,Zd2.se), sirka(Zs2.st,Zs2.mn,Zs2.se)) then
          begin
            blizsi_bod_zs:= true;
            _Zd:= Zd1;
            _Zs:= Zs1
          end
       else begin
              blizsi_bod_zs:= false;
              _Zd:= Zd2;
              _Zs:= Zs2
            end
     end;
