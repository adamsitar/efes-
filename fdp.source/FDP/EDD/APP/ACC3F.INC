procedure TwinACC.vyber_zoznam(stl,ind : int; var p: PlstACC; var bol_act: bool);
    var   rdk, i,min,pocet, ind_i : int;
          p_ : PlstACC;
    begin
      p:= Tablet[stl,ind];
      if Tablet[stl,ind]=nil then Exit;

    { a) vybratie zoznamu zo stlpca }
      bol_act:= (stl=act_stl) and (ind=act_ind);
      if bol_act then vypni_zoznam(true);

      rdk:= Tablet[stl,ind]^.sk_riadkov;
      Tablet[stl,ind]:= nil;
      zmensi_zoznam_v_stlpci(Tablet[stl,ind], stl,ind, true, p^.sk_riadkov-1); {p^.hi-p^.lo+p^.top+1}
      disp_Popis(STablet^[stl,ind]);    { odalokuje, lebo bude prepisany inym }
      for i:= ind+1 to max_skupin-1 do
          begin
            Tablet  [stl,i-1]:= Tablet  [stl,i];
            STablet^[stl,i-1]:= STablet^[stl,i]
          end;
      Tablet[stl,max_skupin-1]:= nil;
      FillChar(STablet^[stl,max_skupin-1],sizeof(STablet^[stl,max_skupin-1]),0);

    { b) najdenie zoznamu, ktory je stlaceny a jeho zvacsenie }
      repeat

      { najdeme najviac utlacany zoznam }
        ind_i:= -1; min:= max_rdk;
        for i:= 0 to max_skupin-1 do
          if (Tablet[stl,i]<>nil) then
             begin
               pocet:= Tablet[stl,i]^.sk_riadkov;
               if (pocet<min) and (Tablet[stl,i]^.is_scroll) then begin min:= pocet; ind_i:= i end
             end;

      { pocvicime s nim }
        if (ind_i<>-1) then
           begin
             if zvacsi_zoznam(Tablet[stl,ind_i]) then Tablet[stl,ind_i]^.List
             else ind_i:= -1
           end

      until (ind_i=-1) or (riadkov(stl, 0,max_skupin)>=max_rdk)
    end;


procedure TwinACC.zrus_zoznam(p: PlstACC);
    begin
      RemoveObject(PObject(p),true)
    end;


procedure TwinACC.vloz_zoznam(p: PlstACC; stl,pstl: int; bol_act: bool);
    var   i,ind, max, pocet : int;
          p_: PlstACC;
          bol_act1 : bool;
    begin
      if p=nil then Exit;

    { a) najde posledny nil, ak nie je nil, presunie ho na pstl alebo zrusi }
      p_:= najdi_posledny_zoznam(stl);
      if (p_<>nil) then
         begin
           najdi_polohu (p_, i,ind);
           if ind=max_skupin-1 then
              begin
                vyber_zoznam(stl,ind, p_, bol_act1);
                vloz_zoznam (p_, pstl,stl, bol_act1)  { miesto je volne, lebo uvolneny zoznam je vkladany sem }
              end
           else inc(ind)
         end
      else ind:= 0;

    { b) vlozi zoznam a jeho popis }
      Tablet[stl,ind]:= p;
      new_Popis(@p^.popis,@STablet^[stl,ind]);

      Tablet[stl,ind]^.stl:= stl;
      Tablet[stl,ind]^.visible:= false;
      with Tablet[stl,ind]^ do reinit_({hi-lo+}1,riadkov(stl, 0,ind-1));  { max_skupin-1 - p^.sk_riadkov-1 }
      zvacsi_zoznam_v_stlpci(stl,ind, true);
      Tablet[stl,ind]^.visible:= true;
      Tablet[stl,ind]^.Draw;

    { c) ak je miesto, zvacsenie }
      if Tablet[stl,ind]^.is_scroll then
         begin
         { ak je zoznam stlaceny a je miesto ? rozsiri sa }
           while Tablet[stl,ind]^.is_scroll and zvacsi_zoznam_v_stlpci(stl,ind, false) do Tablet[stl,ind]^.Draw;
           if Tablet[stl,ind]^.is_scroll and bol_act then zapni_zoznam(stl,ind)
         end
    end;


{
  preunutie skupiny do ineho stlpca
}
procedure TwinACC.presun_zoznam(var _Event: TEvent);
    var   x0m,y0m,x1m,y1m : int;
          stl,ind,i       : int;
          Pxy             : TPoint;
          p               : PlstACC;
          res, bol_act    : bool;
    begin
      p:= _Event.From;
      ClearEvent(_Event);
      if not najdi_polohu(p, stl,ind) then Exit;

      Move(MailBox^,Pxy,SizeOf(Pxy));

      i:= 0; { Kontrola, ci bolo trafene do stlpca v povolenom rozsahu, alebo je letovod opity }
      while i<stlpcov do
        begin
          if (stlpec_xi(i)+dx_lista div 4 <= Pxy.x) and (Pxy.y <= stlpec_xi(i)+dx_lista+dx_strip+dx_lista {div 2}) then break;
          inc(i)
        end;
      if (i>=stlpcov) or (stl=i) then Exit;

      vyber_zoznam(stl,ind, p, bol_act);
      vloz_zoznam (p, i,stl, bol_act);

      save_tablet_cfg (APP_TABLET_CFG)
    end;