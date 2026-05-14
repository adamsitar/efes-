{ vyhladanie a triedenie
}
 { vyhlada plan podla ind -exu v poli
 }
 function TPLAN.find(p: pointer): int;
    var   i : int;
    begin
      find:= -1;
      if (p<>nil) then
         begin
           i:= 0; while (i<=top) and (not (eq_plan(ap^[i],p))) do inc(i);
           if i<=top then find:= i
         end
    end;

 { najde plan podla identifikacie
 }
 function TPLAN.find_id(id: string): int;
    var   i : int;
    begin
      i:= 0; id:= uni_str(id);
      while (i<=top) and (id <> uni_str(get_id(ap^[i]))) do inc(i);
      if i<=top then find_id:= i
      else find_id:= -1
    end;

 { najde plan podla kluca
 }
 function TPLAN.find_key(key: string): int;
    var   i : int;
    begin
      i:= 0; key:= uni_str(key);
      while (i<=top) and (key <> {uni_str}(get_key(ap^[i]))) do inc(i);
      if i<=top then find_key:= i
      else find_key:= -1
    end;


 function  TPLAN.eq_plan(pi, p: pointer): bool;
    begin
      if (p_eq<>nil) and (pi<>nil) and (p<>nil) then eq_plan:= TBFunc_p2(p_eq)(pi, p)
      else eq_plan:= false
    end;

 function  TPLAN.chg_plan(pi, p: pointer): bool;
    begin
      if (p<>nil) and (p_chg<>nil) then chg_plan:= TBFunc_p2(p_chg)(pi, p)
      else chg_plan:= false
    end;


{ Zaradenie
}
 { - ak je plan aktivny, nesmie vratit stav planu, i ked je pred startom...
   - spravne by mal spravit kopiu dat a az nad tou pracovat.
 }
 function TPLAN.is_to_add(p: pointer; var poz: TPoz): bool;
    var   bres : bool;
          rres,rt,rd: real;
    begin
      is_to_add:= false;
      poz:= poz_PLAN;
      if not is_plan(p) then Exit;

     { vypocet stavu/platnosti planu
     }
      poz:= stav_planu(p, absTime, bres);
      if (p_est<>nil) then bres:= TBFunc_p(p_est)(p)
      else bres:= poz in add_pos;

     { ma sa plan preaktivovat ?
     }(*
      if (not bres) and (poz<poz_LETI) and (not spolocna_preaktivacia) then
         begin
         { vypocet, kedy bude plan zaradeny na spracovanie
         }
           rres:= TRFunc_p(p_act)(p);
           if limit_act<>nil then rt:= _limit_act^ else rt:= 0;
           if limit_add<>nil then rd:= _limit_add^ else rd:= 0;
           rres:= rres

           if (rres>absTime) and (rres<next_addTime) then

           bres:= rres>absTime;
         end;*)

      is_to_add:= bres
    end;

 { - patri na rdp
 function TPLAN.is_to_rdp(p: pointer): bool;
    var   zmena: bool;
    begin
      is_est:= (p_est=nil) or (TBFuncp_p(p_est)(p))
    end;
 }

 { - spada do oblasti riadenia ?
 }
 function TPLAN.is_to_addS(p: pointer): bool;
    begin
      is_to_addS:= {$IFDEF SECTORS}
                     (p_is_in_S=nil) or ((p_is_in_S<>nil) and (TBFunc_p(p_is_in_S)(p)))
                   {$ELSE}
                     true
                   {$ENDIF}
    end;

 { - vytlacit po prijati ?
 }
 function  TPLAN.is_to_addP(p: pointer): bool;
    begin
      {$IFDEF PRN}
        is_to_addP:=     ((p_PRN=nil) or (p_PRN^))
                     and (tlacit)
                     and (   (not S_PRINT)
                          {$IFDEF SECTORS} or is_to_addS(p) {$ENDIF}
                         )
      {$ELSE}
        is_to_addP:= false
      {$ENDIF}
     end;

 function TPLAN.is_to_chg(p1,p2: pointer): bool;
    begin
      is_to_chg:= false
    end;


 procedure TPLAN.plan_added(p: pointer);
     begin
     end;

 function TPLAN.plan_add(p: pointer; _ires: pint; _poz: ppoz): int;
    var   ind, is : int;
          poz : Tpoz;
          bres,novy,wasp,isp,b : bool;
    label X;
    begin
      plan_add:= -1;
      if not is_plan(p) then Exit;

      ind:= -1;  { existuje uz ? }
      if _ires<>nil then is:= _ires^
      else is:= find(p);

      if _poz<>nil then
         begin
           bres:= true;
           poz:= _poz^
         end
      else bres:= is_to_add(p,poz);

      format_data(p);

      if bres and (poz>poz_PLAN) {poz_COORDINATED} then
         begin
           ind  := is;
           novy := ind<0;

           if not (novy and (poz>=poz_HANGAR)) then
              begin

               {$IFDEF PRN_STRIP}
                { odpamatanie si, ci sprava uz bola vytlacena
                  a zistenie, ci ju bude potrebne znova tlacit
                }
                 {$IFDEF PRN}
                   wasp:= get_printed (p) or ((is>-1) and get_printed (ap^[is]));
                   {IFDEF DEBUG wasp:= false; ENDIF}
                   {isp:=  (is<0) or ((is>-1) and PRN_CHG and (is_to_chg(p,ap^[is])));}
                   isp:=  (not wasp) or ((is>-1) and PRN_CHG and (is_to_chg(p,ap^[is])));
                 {$ELSE}
                   isp:= false;
                 {$ENDIF}
               {$ENDIF}

               { ------------------------------------------------
                 vymena alebo vlozenie hodnoty (ak nie je miesto,
                 odmazanie najstarsej...
                 ------------------------------------------------
               }
                 if (is>-1) then Eq(is,p)
                 else begin
                        if not (top < items-1) then
                           begin
                             b:= rozoslat; rozoslat:= false;
                             Del(0);   { zatial prvy plan, lepsie by bolo vyhladat ten, co to ma "za par" }
                             rozoslat:= b
                           end;
                        b:= is_eq; is_eq:= false;
                        ind:= inherited Add(p);
                        is_eq:= b;
                        if ind<0 then goto X;
                        rozosli(p,@c_true)
                      end;

               { ----------------------
                 zaradenie, zobrazenie
                 a pripadna tlac planu
                 ----------------------
               }
                 if {(not preaktivujesa) and} (ind>-1) then
                   begin
                     p:= ap^[ind];   { aby ho bolo podla coho najst, ak p bolo ap^[ind]
                                       a bolo opravene, teraz uz je odalokovanie

                     Mal som tu taku blbu chybu, ze v jednej nasledujucich fcii
                     bol plan zruseny a ap^[ind] sa zmenilo na nil...
                    }
                     {$IFDEF SECTORS}
                       urc_platnostS(ap^[ind]);
                       set_on_sector(ap^[ind],false);
                     {$ENDIF}

                     if (not preaktivujesa) then
                        begin
                          spracuj(p);                  { zmena stavu planu }
                          bres:= sort;
                          if bres then ind:= find(p);  { najdi novu polohu planu p v poli ind }
                          if ind=-1 then goto X;       { len pre istotu, nestane sa }
                        end;

                     { zobrazenie : ak je sektorizacia :
                     } vypis_plan(ind, bres, novy);

                     {$IFDEF MAPY}
                      { zaradenie noveho planu na mapu
                      } if (is<0) then zobraz_plan_na_mape(ap^[ind]);
                     {$ENDIF}

                     {$IFDEF PRN_STRIP} {$IFDEF PRN}
                      { tlac :
                         - to ze sa netlaci po starte programu, zabezpeci podmienka "tlacit"
                         - prijaty strip sa vytlaci, ak je nastavena tlac vsetkych stripov,
                           alebo ak vyhovuje podmienke pre polohu v sektore
                           alebo pre prienik so sektorom (fcia "is_to_addP")
                         - ak strip nebol vtlaceny, lebo nevyhovuje tymto kriteriam
                           (pre polohu alebo ich nastavenie),
                           periodicky sa kontroluje sa poloha voci sektoru,
                           az kym nebude vytlaceny...
                      } if PRN_REC and isp and is_to_addP(ap^[ind]) then tlac(ap^[ind],false)
                        else set_printed(ap^[ind],wasp);
                     {$ENDIF} {$ENDIF}

                     set_chg
                   end;
              end;

           if (ind>-1) and (poz>=poz_HANGAR) then
              begin
                Del(ind);
                ind:= -1
              end
         end

      else if is>=0 then Del(is);

      X: plan_add:= ind;

      plan_added(p);
    end;

 function TPLAN.Add(p: pointer): int;
    begin
      Add:= plan_add(p,nil,nil);
    end;


 function TPLAN.Eq(ind: int; p: pointer): bool;
    var   przn,przn2 : byte;
          b : bool;
    begin
     { Predpokladam, ze na aplikacnej urovni odfiltruejem
       opakovane priakte data, preto sa tu spracovava plan,
       i ked je identicky - ale vypoctove premenne moze
       mat rozne. Napr niektore aplikacie zobrazuju
       povtrdenie spravy - pole rec...
     }

     { odpamatanie si priznakov spracovania planu
     } przn:= get_priznak (ap^[ind]);

     {$IFDEF MAPY}
       zmaz_plan_na_mape(ap^[ind],true);
     {$ENDIF}
      if chg_plan(ap^[ind],p) then rozosli(p,@c_true);
      set_cor(p,get_cor(ap^[ind])+1);
      b:= inherited Eq(ind,p);
      Eq:= b;

     { opatovne nastavenie nastavenie predtym nastavenych parametrov
     } set_priznak (ap^[ind],przn,false);

     {$IFDEF MAPY}
       if b then
          begin
            map_wrng:= false;
            zobraz_plan_na_mape(ap^[ind])
          end;
     {$ENDIF}
    end;


 procedure TPLAN.plan_deleted;
     begin
     end;

 procedure TPLAN.Del(ind: int);
     begin
       if (ind<0) or (top<0) then Exit;

       (*{$IFNDEF DEBUG} uloz(ap^[ind]); {$ENDIF} { ulozi povtrdenia, zatial to funguje len na civilne stripy }*)
       rozosli(ap^[ind],@c_false);
       {$IFDEF MAPY} zmaz_plan_na_mape(ap^[ind],true); {$ENDIF}
       inherited Del(ind);
       zmaz_plan(ind,true);  { toto zvrhle poradie je kvoli EDD... }

       plan_deleted;
     end;
