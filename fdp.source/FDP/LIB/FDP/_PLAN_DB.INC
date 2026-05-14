{ musi byt inicializvana fcia is_to_add
}
function loading_plan(PLAN: PPLAN; p: pointer; _rozosli: bool): bool;
   var   bres,b1,b2 : bool;
         ires : int;
         poz  : TPoz;
   begin
     loading_plan:= false;
     with PLAN^ do
       begin
         bres:= is_to_add(p,poz);
         if bres and (not denny_subor) then ires:= find(p)
         else ires:= -1;
         if bres and ((ires<0) or (not denny_subor) {aby sa zbytocne neopravovalo} ) then
            begin
              b1:= rozoslat;
              if _rozosli then rozoslat:= true
              else rozoslat:= false;
              b2:= tlacit; tlacit:= false;
              preaktivujesa:= true;
              plan_add(p,@ires,@poz);
              preaktivujesa:= false;
              tlacit:= b2;
              rozoslat:= b1
            end
         else if (not bres) and (ires>=0) then Del(ires)
       end;
   end;


function nacitaj_plan(PLAN: PPLAN; p: pointer): bool;
   begin
     nacitaj_plan:= loading_plan(PLAN,p,false)
   end;

function preaktivuj_plan(PLAN: PPLAN; p: pointer): bool;
   begin
     preaktivuj_plan:= loading_plan(PLAN,p,NET_ENABLED)
   end;


procedure TPLAN.LoadDB(FN: string; _rozosli,_append: bool; title: string);
    var   p,p_load : pointer;
          bp  : bool; xl,yl : int;
          i   : int;
    begin
      if (p_decodeDB=nil) or (s_loadDB) then Exit;
      s_loadDB:= true;
      m_off(bp, xl,yl);

      if (FN='') and (p_nameDB<>nil) then FN:= TSFunc(p_nameDB);
      if not _append then for i:= top downto 0 do Del(i);
      GetMem (p,data_size); FillChar(p^,data_size,0);
      if _rozosli then p_load:= @preaktivuj_plan
      else p_load:= @nacitaj_plan;
      DB_prehladaj (p_load, @Self, p, disp_item, FN, riadkovDB,p_decodeDB,p_codekey, false, title);
      FreeMem(p,data_size);

      m_on(bp, xl,yl);
      if fn_ext='' then last_addTime:= absTime;
      s_loadDB:= false
    end;


procedure TPLAN.nacitanie_planov(fn,title: string);
   begin
     LoadDB(fn,true,true,title);
   end;


function  TPLAN.nacitanie_zo_vcera(limit_add: real): bool;
   begin
     nacitanie_zo_vcera:= den_nacitania=0
   end;

function  TPLAN.nacitanie_na_zajtra(limit_add: real): bool;
   begin
     nacitanie_na_zajtra:= (absTime+limit_add*60 > DTtoSec(year,month,day,24,0,0))
   end;

procedure TPLAN.nacitanie_platnych_planov(title: string);

    var   limit_add : real;
          fn  : string;
          d   : TDate;
          z,b : bool;

    begin
     if p_limit_add<>nil then limit_add:= p_limit_add^ else limit_add:= 0;

     { Ak je to denny subor planov, potom je zabezpecene,
       ze v subore sa nachadzaju len jedinecne plany.
       Potom su rychlejsie nacitane, ak sa uvolnia z pamate
       vsetky a znova nacitaju, odpadne tym zdlhave
       vyhladavanie.
     }
       if denny_subor then
          begin
            b:= APP_GUI_INIT; APP_GUI_INIT:= true;
            while top>0 do Del(top);
          end;

     { Pri aktivovani programu mozu byt niektore udaje planovane
       zo vcera...
     } if nacitanie_zo_vcera(limit_add) and (fn_dir<>'') and (fn_ext<>'') then
          begin
            init_date (d, year,month,day);
            PrevDate  (d.r,d.m,d.d);
            fn:= get_DBfn_ (d.d,d.m,d.r, fn_ext,fn_ext);
            if fn<>'' then nacitanie_planov(fn,title)
           end;

     { Nacitanie zo subora
       na dnes...
     } if p_nameDB<>nil then fn:= TSFunc(p_nameDB)
       else if (fn_dir<>'') and (fn_ext<>'') then fn:= get_DBfn_ (day,month,year, fn_ext,fn_ext)
       else fn:= '';

       if fn<>'' then nacitanie_planov(fn,title);

     { Prelom dni ? Potom treba pozriet i do suborov
       na zajtra...
     } if nacitanie_na_zajtra(limit_add) and (fn_dir<>'') and (fn_ext<>'') then
          begin
            init_date(d, year,month,day); NextDate(d.r,d.m,d.d);
            fn:= get_DBfn_ (d.d,d.m,d.r, fn_ext,fn_ext);
            if fn<>'' then nacitanie_planov(fn,title)
          end;

      if denny_subor then APP_GUI_INIT:= b;
    end;
