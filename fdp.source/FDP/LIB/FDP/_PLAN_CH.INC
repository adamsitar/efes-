{ ---------------------------------
   prekontrolovanie vsetkych plany
   na aktualnost, pri zmene casu
   o minutu
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
function TPLAN.zmena_platnosti(z0,z1: Tpoz): bool;
   begin
    { ak sa v ramci objektu delia udaje do dalsich skupin podla stavu
      spracovania, potom je potrebne vyhodnotit prechody stavu medzi
    }
     zmena_platnosti:= false
   end;

function  TPLAN.nastavenie_platnosti(zmena: bool): bool;
    const T : real = 0;
          m : byte = 1;
    var   z0,z1 : TPoz;
          i : int;
    begin
      nastavenie_platnosti:= false;
      zmena:= zmena or ((T<>absTime) and (m<>min));
      if s_pocitam or (not zmena) then Exit;

      s_pocitam:= true;
      nastavenie_platnosti:= true;
      T:= absTime;
      m:= min;

      i:= 0; while i<=top do
        begin
          z0:= get_poz(ap^[i]);
          z1:= stav_planu(ap^[i], absTime, zmena);
          {if (z<poz_HANGAR) and ((z in add_pos) or is_to_add(ap^[i],z)) then}
          if is_to_add(ap^[i],z1) and (z1<poz_HANGAR) then
             begin
               if zmena then
                  begin
                    vypis_plan(i, false,false);
                    if zmena_platnosti(z0,z1) then set_chg
                  end;
               inc(i)
             end
          else zrus(ap^[i],false);
          CheckProcesses0
        end;

      s_pocitam:= false
    end;


{ ---------------------------------
   priebezna aktivacia nacitanie/
   zrusenie uz neplatnych planov
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function TPLAN.zmenene_parametre_platnosti: bool;
    var   bres: bool;
    begin
      bres:= false;

      if (p_limit_cnl<>nil) and (last_limit_cnl>p_limit_cnl^) then
         begin
           last_limit_cnl:= trunc(p_limit_cnl^);
           bres:= true;
         end;

      if (p_limit_del<>nil) and (last_limit_del>p_limit_del^) then
         begin
           last_limit_del:= trunc(p_limit_del^);
           bres:= true;
         end;

      zmenene_parametre_platnosti:= bres
    end;


 function TPLAN.spolocna_preaktivacia: bool;
    begin
      spolocna_preaktivacia:= (not preaktivovanie_planu) or (p_act=nil)
    end;

 function TPLAN.cas_pre_preaktivaciu_planov: bool;
    var   limit_add : real;
    begin
      cas_pre_preaktivaciu_planov:= false;

      if spolocna_preaktivacia then
         begin
           if p_limit_add<>nil then limit_add:= p_limit_add^ else limit_add:= 0;
           if (limit_add<>0) and (abs(absTime-last_addTime)>60*limit_add{/2})
           then begin
                  cas_pre_preaktivaciu_planov:= true;
                  last_limit_add:= trunc(p_limit_add^);
                  last_addTime:= absTime
                end;
         end;
    end;

 function TPLAN.cas_pre_preaktivaciu_planu: bool;
    var   bres: bool;
    begin
      bres:= (p_act<>nil) and (next_addTime<>0) and (absTime>=next_addTime);
      cas_pre_preaktivaciu_planu:= bres
    end;


 procedure TPLAN.preaktivovanie_planov;
     begin
       if zmenene_parametre_platnosti then
          begin
            nastavenie_platnosti(true);
          end;

       if     (not s_loadDB)
          and preaktivovanie
          and (   (spolocna_preaktivacia and cas_pre_preaktivaciu_planov)
               or ((not spolocna_preaktivacia) and cas_pre_preaktivaciu_planu)
              )
              then
          begin
            nacitanie_platnych_planov(tit_preactivate);
            den_nacitania:= day
          end;
     end;


{ ---------------------------------
   zadne dvierka
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure TPLAN.spracovanie_planov;
     begin
     end;


{ ---------------------------------
   hlavna fcia pre volanie
   fcii mozneho spracovania
   objektu
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 procedure TPLAN.Check(zmena: bool);
     begin

     { Kontrola stavu a platnosti planov
     } nastavenie_platnosti(zmena);

     { Zmenili sa parametre spracovania
     } preaktivovanie_planov;

     { Vypocty: schvalenie, zobrazenie,...
     } spracovanie_planov;

     { Zobrazenie planov
     }
       if (viewer<>nil) and (OpenWins=1) and (viewer^.ma_sa_prekreslit) then viewer^.Prekreslit;
     end;
