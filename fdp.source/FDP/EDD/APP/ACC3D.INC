{ ------------------------------------
   PREPINANIE MEDZI lstACC z winACC
  ------------------------------------ }


{ funkcie pre winACC ---------------------------------- }

procedure TwinACC.zapni_zoznam(stl,ind: int);
    begin
      if (stl=-1) and (ind=-1) then vypni_zoznam(true)
      else if (is_poloha(stl,ind) and (Tablet[stl,ind]<>nil) and Tablet[stl,ind]^.is_scroll) then
        begin
          if not is_poloha(act_stl,act_ind) then Mail(winPROP,hl_zap_winACC, one,nil,0) { ziadost o vypnutie winPROP }
          else vypni_zoznam(false);
          Tablet[stl,ind]^.ActiveOn
        end;
      act_stl:= stl; act_ind:= ind
    end;

procedure TwinACC.vypni_zoznam(_sprava: bool);
    begin
      if is_poloha(act_stl,act_ind) and (Tablet[act_stl,act_ind]<>nil) then
         begin
           Tablet[act_stl,act_ind]^.ActiveOff;
           _stlpec_i(act_stl)
         end;
      act_stl:= -1; act_ind:= -1;
      if _sprava then Mail(winPROP,hl_vyp_winACC, one,nil,0)
    end;


{ funkcie volane z GUI -------------------------------- }

function TwinACC.najdi_zoznam_sc(var stl,ind: int;
                                 zac_stl,kon_stl : int; { zaciatocny a koncovy stlpec }
                                 zac_ind         : int; { zaciatocny riadok }
                                 smer_ind        : int  { -1 alebo 1 }
                                ): bool;
   begin
     stl:= zac_stl;
     while    ((smer_ind<0) and (stl>=zac_stl) and (stl<=kon_stl))
           or ((smer_ind>0) and (stl>=kon_stl) and (stl<=zac_stl))
     do begin
          if stl=zac_stl then ind:= zac_ind
          else if smer_ind=-1 then ind:= max_skupin-1 { 0,1,2 -> ind v opacnom smere }
               else ind:= 0;
          while (ind>=0) and (ind<max_skupin) do
            begin
              if (Tablet[stl,ind]<>nil) and (Tablet[stl,ind]^.is_scroll) then begin najdi_zoznam_sc:= true; exit end;
              ind:= ind + smer_ind
            end;
          stl:= stl+(-smer_ind);
        end;
     stl:= -1; ind:= -1; najdi_zoznam_sc:= false
   end;


{
  Funkcie prepinania volane z GUI
}
procedure TwinACC.zapni;
    var   stl,ind: int;
    begin
      najdi_zoznam_sc(stl,ind, 0,stlpcov-1, max_skupin-1,-1);
      zapni_zoznam(stl,ind)
    end;


procedure TwinACC.vypni;
    begin
      vypni_zoznam(true)
    end;


procedure TwinACC.dalsi;
    var   stl,ind: int;
    begin
      if (act_stl<>-1) and (act_ind<>-1) then
         begin
           najdi_zoznam_sc(stl,ind, act_stl,stlpcov-1, act_ind-1,-1);
           zapni_zoznam(stl,ind)
         end
      else zapni
    end;

procedure TwinACC.predch;
    var   stl,ind: int;
    begin
      if (act_stl=-1) and (act_ind=-1) then stl:= stlpcov-1
      else stl:= act_stl;
      najdi_zoznam_sc(stl,ind, stl,0, act_ind+1,1);
      zapni_zoznam(stl,ind)
    end;

