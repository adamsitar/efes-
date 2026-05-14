{ identifikuje Tablet, ku ktoremu typu zaradit: mFPL-> MIL; aFPL->AERO; cFPL->NDB
}
function TwinACC.zarad(_iFPL: PSTRIP; _ind: int;
                       var NDB: string;
                       var stl,ind: int
                      ): bool;
   var   i,j : int;
   begin
     NDB:= upstring(cut_(_iFPL^.zarad(_ind,SpecGroups)));
     if (not najdi_zoznam(NDB, stl,ind)) then
        begin
          NDB:= upstring(cut_(_iFPL^.zarad_inde(_ind,SpecGroups, NDB)));
          if not najdi_zoznam(NDB, stl,ind) then NDB:= ''
        end;
     zarad:= NDB<>''
   end;


procedure TwinACC.add(_iFPL: PSTRIP; _ind: int; _hladaj: bool);
    var   stl,ind, s1,i1,s2,i2: int;
          je,bude,ten_isty: bool;
          NDB  : string;
          TempWinReg : PWinReg;
    begin
    { Prehlada, ci strip je uz zaradeny v nejakom zozname.
      Ak ano, zisti ci bude i nadalej patrit do toho isteho zoznamu.
      Ak ano, opravi strip v danom zozname,
      ak nie, odmaze ho z povodneho zoznamu a zaradi do noveho
    }

    { nachadza sa na planzete a ma byt kam zaradeny ?
    } s1:= 0; i1:= 0; s2:= 0; i2:= 0;
      je:= _hladaj and najdi_zoznam_s_planom(_iFPL,_ind, s1,i1);
      bude:= zarad(_iFPL,_ind, NDB, s2,i2);
      if not (je or bude) then Exit;          { ani sa neodmaze, ani neprepise, ani nezaradi }
      ten_isty:= je and bude and (s1=s2) and (i1=i2);

      if je and ((not bude) or (not ten_isty)) then
         begin
           PIS:= vypis_do_okna(Tablet[s1,i1]^.x0,y0,Tablet[s1,i1]^.x1,y1, TempWinReg,-1,ScreenDesc);
           if not PIS then PREPIS:= absTime;

           Tablet[s1,i1]^.del(_iFPL,_ind, false);

           obnov_okna(TempWinReg, true)
         end;

      if bude then
         begin
           PIS:= vypis_do_okna(Tablet[s2,i2]^.x0,y0,Tablet[s2,i2]^.x1,y1, TempWinReg,-1,ScreenDesc);
           if not PIS then PREPIS:= absTime;

           if ten_isty then Tablet[s2,i2]^.chg(_iFPL,_ind)
           else Tablet[s2,i2]^.add(_iFPL,_ind);

           obnov_okna(TempWinReg, true)
         end;

      EDDgui^.edd_status
    end;


procedure TwinACC.del(_iFPL: PSTRIP; _ind: int; _zrus: bool);
    var   stl,ind, i,j, r1,r2 : int;
          bres  : bool;
          TempWinReg   : PWinReg;
    begin
    { prehlada, ci FPL sa uz niekde nachadza, ak ano, zmaze }
      bres:= najdi_zoznam_s_planom(_iFPL,_ind, stl,ind);

    { Prehlada vsetky zoznamy majakov, okrem [stl,ind] (ten spravi(l)
      Tablet[stl,ind]^.del a vsetky indexy pola _iFPL vyssie ako _ind
      znizi o 1. ( Zmensil sa top ).

      Mohol by som to robit i priamo cez smerniky, ale pri meniaciach sa
      dynamickych zoznamoch by mohli vzniknut komplikacie
      a teraz by som to nestihol.
      Viem, je to hrozne riesenie, ale co ked sa prealokovavali
      premenne pri zmene, chce to navrhbnut este raz.
    }
      if _zrus then
         begin
           for i:= 0 to stlpcov-1 do
               for j:= 0 to max_skupin-1 do
                   if (Tablet[i,j]<>nil) and (Tablet[i,j]^.top<>-1) then
                      begin
                        { uz_bol:= res and (i=stl) and (j=ind); }
                        if (not bres) or ((bres) and (i<>stl) or (j<>ind)) then Tablet[i,j]^.zrus(_iFPL, _ind)
                      end
         end;

       if bres then
          begin
            PIS:= vypis_do_okna(Tablet[stl,ind]^.x0,y0,Tablet[stl,ind]^.x1,y1, TempWinReg,-1,ScreenDesc);
            if not PIS then PREPIS:= absTime;
            r1:= Tablet[stl,ind]^.sk_riadkov;
            Tablet[stl,ind]^.del(_iFPL,_ind, _zrus);
            { ak zmenena velkost a vypis do stplca, potom sa nastavi prepis }
            r2:= Tablet[stl,ind]^.sk_riadkov;
            if (r1<>r2) then
               begin
                 PIS:= vypis_do_okna(Tablet[stl,ind]^.x0,y0,Tablet[stl,ind]^.x1,y1, TempWinReg,-1,ScreenDesc);
                 if not PIS then PREPIS:= absTime;
               end;
            obnov_okna(TempWinReg, true)
          end;

      EDDgui^.edd_status
    end;
