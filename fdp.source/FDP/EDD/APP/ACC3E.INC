procedure TwinACC.posun_zoznamy_v_stlpci(stl,od, o: int);
    var   i: int;
    procedure posun;
        begin
          if is_active(stl,i) then Tablet[stl,i]^.zmen_polohu(o);
        end;
    begin
    { vsetky vypisy nad posunut o "o" riadkov }
      if o>0 then for i:= max_skupin-1 downto od do posun;
      if o<0 then for i:= od to max_skupin-1 do posun
    end;


{ --------------------
  Zvacsenie
  --------------------
}
function TwinACC.zvacsi_zoznam_v_stlpci(stl,ind: int; novy: bool): bool;
   var   o,uz_o,volnych,ind_i, r : int;
         p : PlstACC;
   begin
     zvacsi_zoznam_v_stlpci:= false;
     if (Tablet[stl,ind]=nil) then Exit;

     r:= Tablet[stl,ind]^.sk_riadkov;
     p:= Tablet[stl,ind];
     if (p^.top=0) and (not NDB_NULL) then o:= 2
     else begin
            o:= 1;
            if novy and (p^.top>=0) then
               begin
                 inc(o,p^.hi-p^.lo+1);
                 Tablet[stl,ind]:= nil { aby sa v zmensovani neposuval i tento este nevykresleny, moze byt mimo rozsah }
               end
          end;

   { je volne miesto pre zaradenie stripu ? }
     uz_o := 0;
     while (riadkov(stl, 0,max_skupin-1)+o > max_rdk) and (uz_o < o) do
        begin
          if     najdi_najvacsi_zoznam(stl,ind, ind_i)
             and (p^.sk_riadkov+1 < Tablet[stl,ind_i]^.sk_riadkov)
                 then { nema zmysel menit rozmery 4,5 na 5,4 }
             begin
             { nasli }
               zmensi_zoznam(Tablet[stl,ind_i]);
               inc(uz_o)
             end
          else Exit
        end;
     uz_o:= o;
     Tablet[stl,ind]:= p;

   { je prazdne miesto nad ? odsunutie hornych stripov }
     if riadkov(stl, ind+1,max_skupin-1)<>0 then posun_zoznamy_v_stlpci(stl,ind+1, uz_o);

   { urcenie pozicie, ak p nebol zobrazeny }
     if not Tablet[stl,ind]^.visible then Tablet[stl,ind]^.rdk:= riadkov(stl, 0,ind-1);
     if novy then
        begin
          volnych:= max_rdk - (riadkov(stl, 0,ind-1) + riadkov(stl, ind+1,max_skupin-1));
          with Tablet[stl,ind]^ do
            if top>=0 then o:= Minimum(volnych - (hi-lo+1) - 1, top{+1} - (hi-lo {+1}))
            else o:= 0;
        end
     else begin
            volnych:= max_rdk - riadkov(stl, 0,max_skupin-1);
            o:= 1
          end;
     Tablet[stl,ind]^.zmen_rozmer(o,volnych);

     zvacsi_zoznam_v_stlpci:= Tablet[stl,ind]^.sk_riadkov > r {= Tablet[stl,ind]^.pl_riadkov}
   end;


function TwinACC.zvacsi_zoznam(p: PlstACC): bool;
   var   stl,ind, o : int;
   begin
     zvacsi_zoznam:= false;
     if p=nil then Exit;

     if najdi_polohu(p, stl,ind) then
        begin
          zvacsi_zoznam_v_stlpci(stl,ind, false);
          zvacsi_zoznam:= p^.sk_riadkov = p^.pl_riadkov
        end;
   end;


function TwinACC.zvacsil_sa_zoznam(p: PlstACC): bool;
   begin
     zvacsil_sa_zoznam:= zvacsi_zoznam(p)
   end;



{ --------------------
  Zmensenie
  --------------------
}

procedure TwinACC.zmaz_plochu_nad_zoznammi(p: PlstACC; stl: int);
    var   zmaz_vrch : bool;
          i,x,_y1, xlm,ylm: int;
          bp : bool;
    begin
    { ak je posledny_zoznam, odmazanie nad
    } zmaz_vrch:= false;
      if (p<>nil) and NDB_NULL then
         begin
           if p=najdi_posledny_zoznam(stl) then
              begin
                zmaz_vrch:= true;
                _y1:= p^.y0-1
              end
         end
      else begin
           { hlada najvrchnejsiu suradnicu
           } zmaz_vrch:= true;
             _y1:= MaxY;
             for i:= max_skupin-1 downto 0 do
               if is_active(stl,i) and ((NDB_NULL) or (Tablet[stl,i]^.top<>-1)) then
                  begin
                    _y1:= Tablet[stl,i]^.y0-1;
                    break
                  end
           end;
      if zmaz_vrch and (not APP_GUI_INIT) then
         begin
           x:= stlpec_xi(stl);
           m_off (bp, xlm,ylm);
           {FillWin(x+2,y0+1,x+dx_lista-2,_y1, clTABLET);}
           inc(x,dxof_strip-dxof_stlpec);
           FillWin(x,y0,x+dx_strip,_y1, bgTABLET);
           for i:= 0 to stlpcov do _stlpec_i(i);
           m_on (bp, xlm,ylm);
         end;
    end;

function TwinACC.zmensi_zoznam_v_stlpci(p: PlstACC; stl,ind: int; posun: bool; posun_o: int): bool;
   var   zmaz_vrch : bool;
         o,i,x,_y1 : int;
         bp : bool; xlm,ylm: int;
   begin
   { posun vsetkych, co su nad o "o" dole
   }
     if ((p<>nil) and (p^.top<0) and (not NDB_NULL)) then o:= -2
     else o:= -1;
     if p=nil then o:= o-posun_o;
     posun:= posun or (p=nil);
     if posun then posun_zoznamy_v_stlpci(stl,ind+1,o);

     zmaz_plochu_nad_zoznammi(p,stl);

     zmensi_zoznam_v_stlpci:= posun
   end;


function TwinACC.zmensi_zoznam(p: PlstACC): bool;
   var   stl,ind : int;
         sk_r,o  : int;
   begin
     if (p=nil) or (not najdi_polohu(p, stl,ind)) then Exit;
     sk_r:= p^.sk_riadkov;
     p^.zmen_rozmer(-1,0);
     zmensi_zoznam:= zmensi_zoznam_v_stlpci(p, stl,ind, sk_r<>p^.pl_riadkov,0)
   end;


function TwinACC.zmensil_sa_zoznam(p: PlstACC): bool;
   var   stl,ind     : int;
         i,min,min_i : int;
         pocet, o    : int;
         res,vis     : bool;
   label LOOP;
   begin
     if p=nil then Exit;

     res:= zmensi_zoznam(p);
     if (p^.top=-1) and (not NDB_NULL) then o:= 2 else o:= 1;
   { prehlada, ci sa nezide niekde zoznam zvacsit }
     if res and najdi_polohu(p, stl,ind) then
        begin
          LOOP:
          min:= max_rdk; min_i:= -1;
          i:= 0;
          while (i<max_skupin) do
             begin
               if (Tablet[stl,i]<>nil) then with Tablet[stl,i]^ do
                  if is_scroll and (hi-lo+1<min) then
                     begin
                       min:= hi-lo+1;
                       min_i:= i
                     end;
               inc(i)
             end;
          if (min_i<>ind) and (min_i<>-1) then
             begin
               vis:= p^.visible; if (p^.top=-1) and (not NDB_NULL) then p^.visible:= false;
               if (Tablet[stl,min_i]<>nil) then zvacsi_zoznam(Tablet[stl,min_i]);
               p^.visible:= vis;
               if (Tablet[stl,min_i]<>nil) then Tablet[stl,min_i]^.List;
               dec(o);
               if o>0 then goto LOOP
             end
        end;
     zmensil_sa_zoznam:= res
   end;
