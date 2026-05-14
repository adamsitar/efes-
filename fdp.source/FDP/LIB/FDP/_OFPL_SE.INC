{$IFDEF PRN}
 { tlaci sa po prijati ?
 }
 function O_FPL.is_to_addP (p: pointer): bool;
    var   res: bool;
    begin
      res:= {$IFDEF EDD}
                 (p_PRN2<>nil)
             and (p_PRN2^)
             and (PRN_HIDDEN_PLAN or get_on_board(p))
             and
            {$ENDIF}
                  tlacit
             and ((not S_PRINT) {$IFDEF SECTORS} or _is_to_addS(p,S_P_IN_THROUGH,S_EST_LIMIT) {$ENDIF});
      is_to_addP:= res
    end;

{$ENDIF}


 {
  Tlac stripov sa da nastavit na tlac vsetkych prichadzajucich
  stripov, alebo len na tie, ktore prilietaju na dany sektor.

  Obdobne je to so zobrazenim stripov, zobrazuju sa vsetky stripy,
  stripy prelietavajuce dany sektor alebo stripy prilietavajuce
  a nachadzajuce sa v nom.

  Rozdiel medzi tlacou a zobrazenim je ten, ze pri ak sa povoli
  zobrazenie podla menej selektivneho kriteria, povolene stripy
  sa zobrazia, ale uz nevytlacia.
  Tlacit sa budu len prichadzajuce, vyhovujuce nastavenym
  kriteriam sektorizacie.
  Stripy, ktore pre nastavenie systemu neboli vytlacene, je mozne
  vytlacit jednotlivo cez funkcie stripu.

  a) Zobrazennie vsetkych stripov - vsetky stripy letov vo FIRe
  b) Through sector - stripy s planovanou tratou cez dany sektor.
  c) In sector - stripy v sektore, alebo nachdzajuce sa pred
     sektorom v nastavenom casom limite

  !) Pri zmene nastavenia sektorizacie, treba volat funkciu
     pre prepocet urcenych parametrov sektorizacie
 }

{ ------------------------------------
  a) Nastavenie parametrov spracovania
  ------------------------------------
}

{$IFDEF SECTORS}

{ ------------------------------------
  b) vypis/zmazanie/tlac
  ------------------------------------
  - nastavi priznaky, ze je
    vypisany/vytlaceny
}


{ ------------------------------------
  c) vypocet platnosti v sektore
  ------------------------------------
}
 { vypocita, ci let patri na sektor
   a pripadne nastavi jeho parametre
   pre spracovanie (T0,T1, B0,B1 - cas vstupu/vystupu; index bodu vstupu/vystupu)
 }
  function O_FPL.urc_platnostS(p: pointer): bool;
     begin
       urc_platnostS:= true {is_to_addS(p)}
     end;


  function  O_FPL.let_cez_sektor(p: pointer): bool;
     begin
       let_cez_sektor:= inherited is_to_addS(p)
     end;

 { vrati, ci len bude/je v riadeni
 }
  function  O_FPL.let_v_sektore(p: pointer; _limit: real): bool;
     begin
       let_v_sektore:= true {sector.let_v_sektore(p,@bodTxy,absTime,absTime+_limit)}
     end;

 { vrati, ci vyprsal limit po vystupe zo sektora
  function  O_FPL.let_zo_sektora(p: pointer; _limit: real): bool;
     begin
       let_zo_sektora:= sector.let_v_sektore(p,bodTxy,absTime-_limit,absTime)
     end;
 }

  function  O_FPL.platnost_letu_v_sektore(p: pointer; zmena_sektorizacie: bool): bool;
     begin
       platnost_letu_v_sektore:= false
     end;


 { spada do oblasti riadenia ?
 }
  function O_FPL._is_to_addS(p: pointer; _S_IN_THROUGH: bool; _S_EST_LIMIT: real): bool;
     var   {$IFDEF RDP_ACCEPT}
             acpt: TTRG_stat; rdp: word;
           {$ENDIF}
           bres: bool;
     begin
       bres:=  {$IFDEF SECTORS}
                 {$IFDEF RDP_ACCEPT}
                        (get_accept(p, acpt,rdp)=_acc) { bol let acceptovany a prisla zmena ? }
                    or
                 {$ENDIF}
                       (_S_IN_THROUGH and ((let_v_sektore(p,_S_EST_LIMIT*60) {or let_zo_sektora(p,_S_EST_LIMIT*60)})))
                   or  ((not _S_IN_THROUGH) and (let_cez_sektor(p)))
               {$ELSE}
                 true
               {$ENDIF};
       _is_to_addS:= bres
     end;

  function O_FPL.is_to_addS(p: pointer): bool;
     begin
       is_to_addS:= (not S_DISPLAY) or _is_to_addS(p,S_D_IN_THROUGH,S_EST_LIMIT)
     end;


{ ------------------------------------
  d) dynamicka sektorizacia
  ------------------------------------
}
 { Ak sa pouziva dynamicke radenie na sektor,
   a zaradi na zobrazenie/tlac tie, ktore vstupuju na sektor.
   Prekontroluje vsetky plany, kazdu minutu,
   pretoze casy na bodoch su pocitane po minutach
 }
  function  O_FPL.nastavenie_platnosti_v_sektore: bool;
     var    i, co : int;          { 0 - nic, 1 - zarad, 2 - zmaz }
            on,bdat,bcas : bool;
            dTlimit : real;
     begin
       nastavenie_platnosti_v_sektore:= semaphorS;

       if S_UPDATE<>updateS then
          begin
            updateS:= S_UPDATE;
            for i:= 0 to top do
                begin
                  platnost_letu_v_sektore(ap^[i],true);
                  if (S_DISPLAY) then
                      begin
                        on:= get_on_sector(ap^[i]) and get_on_board(ap^[i]);
                        if (is_to_addS(ap^[i])) then
                           begin
                             if not on then vypis_plan(i,false,true)
                           end
                        else begin
                               if on then zmaz_plan(i,false)
                             end
                      end
                end;
            Exit
          end;

       bdat:= (dayS<>day) or (monthS<>month) or (yearS<>year);
       bcas:= (minS<>min) or (hourS<>hour);

       if    ((not S_DISPLAY) and (not S_PRINT))
          or (not (bdat or bcas))
          or semaphorS then Exit;

       semaphorS:= true;

       for i:= 0 to top do
         begin
           co:= 0;

           {if platnost_letu_v_sektore(ap^[i],false) then
              begin
                set_printed(ap^[i],false);
                vypis_plan(i,false,false)
              end;
           }

          {$IFDEF PRN}
           if tlac_en then
              if (S_PRINT) and S_P_IN_THROUGH and (not get_printed(ap^[i])) then
                 begin
                   dTlimit:= S_EST_LIMIT;
                   if let_v_sektore(ap^[i],dTlimit*60) then
                      begin
                        co:= 1;
                        tlac(ap^[i],false)
                      end
                 end;
          {$ENDIF}

           if (S_DISPLAY) and S_D_IN_THROUGH then
              begin
                dTlimit:= S_EST_LIMIT;
                if (co=0) and let_v_sektore(ap^[i],dTlimit*60) then co:= 1;
                if get_on_sector(ap^[i]) and get_on_board(ap^[i]) then
                   begin
                     if (co=0) then zmaz_plan(i,false)
                   end
                else begin
                       if (co<>0) then vypis_plan(i,false,true)
                     end
                {draw_plan (i, is_to_board(i),co<>0);}
              end
         end;

       dayS:= day; monthS:= month; yearS:= year;
       secS:= sec; minS:= min; hourS:= hour;
       semaphorS:= false
     end;

{$ENDIF}