function  OmFPL.is_plan(p: pointer): bool;
   begin
     is_plan:= is_mFPL(PDmFPL(p))
   end;

function OmFPL.get_poz(p: pointer): Tpoz;
   begin
     get_poz:= PDmFPL(p)^.poz
   end;


procedure OmFPL.set_cor(p: pointer; cor: int);
   begin
     PDmFPL(p)^.cor_:= cor
   end;

function OmFPL.get_cor(p: pointer): int;
   begin
     if PDmFPL(p)^.cor_>0 then get_cor:= 1
     else get_cor:= 0{-1}
   end;

procedure OmFPL.cl_cor(p: pointer);
    begin
      PDmFPL(p)^.cor_:= 0;
      inherited cl_cor(p)
    end;


{$IFDEF NET}
   function OmFPL.get_rec(p: pointer): Pplan_rec;
      begin
        get_rec:= @DmFPL(p^).rec
      end;
{$ENDIF}

{
  pocitana poloha, skutocnu urcuje stat,
  trat musi mat aspon 2 body - start a prist
}
function OmFPL.urc_platnost(p: pointer; var zmena: bool; kresli: bool): Tpoz;
   var   z : Tpoz;
         i : int;
   begin
     z:= stav_planu(p, absTime, zmena);
     urc_platnost:= z;

    {$IFDEF REPORT_FPLM_ARW}
     isFPLM_ARW:= isFPLM_ARW or ((zmena) and (z=poz_PATRAT) and _is_FPLM_ARW(p,nil));
    {$ENDIF}

    {$IFDEF MAPY}
 {!}  if     (kresli)
         and (   (z in [poz_SEDI,poz_HANGAR])
              or ((not draw_MZP) and (z=poz_MZP))
              or ((not draw_PATRAT) and (z=poz_PATRAT))
             )
            then zmaz_plan_na_mape(p,true)
    {$ENDIF}
   end; { urc_poziciu }



{$IFDEF EDD}
  {
   zaradenie stripu na tablet podla nastavenia: vstupny<->aktualny:
    - vstupny  : zaradi sa na prvy vstupny majak
                 IDD
                  - DEP : ak este neostartoval z tohoto letiska
                  - ARR : ak pristava na tomto letisku
    - aktualny : zaradi na aktualny majak, na ktory leti (alebo posledny)
                 IDD umoznuje zaradit na
                  - DEP : ak este neostartoval z tohoto letiska
                  - ARR : cas je vacsi ako na poslednom bode,

   Tyka sa i MZP (Rozdiel oproti mFPL). Teraz sa neviem rozhodnut,
   ci MZP brat podla stavu letu alebo podla casov. Zrejme podla casov
   bude lepsie, lebo stav je len premenna pre spracovanie v OPL a tu
   predpokladame, ze mame spravne spracovane data.
    - pri triedeni na aktualny bod kontroluje, ci predchadzajuci
      alebo nasledujuci bod nie su tymto letiskom MZP
    - pri triedeni na vstupny najde bod MZP, ktory je identicky
      s tymto letiskom a casovo to sedi, pretoze sa moze opakovat
  }
  function OmFPL.zarad (ind: int; is: TSpecGroups): string;
     var   i : int;
     begin
       zarad:= '';
       if PDmFPL(ap^[ind])^.poz<poz_COORDINATED {poz_START} then Exit;

       if _let_do_TSA (PDmFPL(ap^[ind])) then zarad:= fplTSA
       else zarad:= fplMIL;


      {$IFDEF TABLET_DEP_ARR}
       with PDmFPL(ap^[ind])^ do
         begin

          { DEP ?
          }
           if is.is_dep and (poz<=poz_START) then
              begin
                {$IFDEF AIRBASE} if toto_letisko(start.kod) then {$ENDIF}
                zarad:= fplDEP
              end

          { ARR ?
          }
           else if is.is_arr and ({(NDB_INP) or} (poz>=poz_PRIST)) and (poz>=poz_START) then
              begin
                {$IFDEF AIRBASE} if toto_letisko(start.kod) then {$ENDIF}
                zarad:= fplARR
              end

          { MZP ?
          }
          {$IFDEF AIRBASE}
           else if NDB_INP then
              begin
              { hlada, ci let nema MZP na danom letisku,
                alebo nasledujuci bod nie je bodom MZP
              }
                for i:= 0 to bodov-1 do with trat_^[i] do
                    if     ((pozn and OBxy_MZP)<>0)
                       and (toto_letisko(kod))
                       and (absTime<casD) then
                            begin
                              if is.is_arr and (absTime<casA) then zarad:= fplARR
                              else if is.is_dep and (absTime<casD) then zarad:= fplDEP;
                              break
                            end
              end
          {$ENDIF}
           else with trat_^[na_bod] do
                  begin
                    if ((pozn and OBxy_MZP)<>0) {$IFDEF AIRBASE} and (toto_letisko(kod)) {$ENDIF} then
                      if is.is_arr and (absTime<casA) then zarad:= fplARR
                      else if is.is_dep and (absTime<casD) then zarad:= fplDEP
                    end
         end;
      {$ENDIF}
     end;

  function OmFPL.smer(ind: int): Ts_dir;
     begin
       smer:= dir_fpm{_dir_mFPL(PDmFPL(ap^[ind])^)}
     end;


  function OmFPL.ETO(ind: int): real;
     begin
       with PDmFPL(ap^[ind])^ do ETO:= start.cas
     end;

  function OmFPL.ETD(ind: int): real;
     begin
       with PDmFPL(ap^[ind])^ do ETD:= start.cas
     end;

  function OmFPL.ETA(ind: int): real;
     var   i: int;
     begin
       with PDmFPL(ap^[ind])^ do
         begin
          ETA:= prist.cas;
           {if toto_letisko(prist.kod) and (STRIP_INP or (poz >= poz_PRIST)) then
           else}if NDB_INP then
                   begin
                     for i:= 0 to bodov-1 do with trat_^[i] do
                         if     (((pozn and OBxy_MZP)<>0) and (toto_letisko(kod)))
                            and (absTime<casD)
                            then begin
                                   if absTime<casA then ETA:= casD
                                   {else if absTime<casD then zarad:= fplDEP};
                                   break
                                 end
                     end
                  else with trat_^[na_bod] do
                       if ((pozn and OBxy_MZP)<>0) and (toto_letisko(kod)) then
                          if absTime<casA then ETA:= casA
                         {else if absTime<casD then zarad:= fplDEP}
         end
     end;

  function OmFPL.FL(ind: int): real;
     begin
       with PDmFPL(ap^[ind])^ do
         if NDB_INP or (bodov=0) or (trat_=nil) then FL:= vys
         else FL:= trat_^[na_bod].vys
     end;

{$ENDIF}


{$IFDEF RDP_ACCEPT}
   function  OmFPL.get_accept(p: pointer; var ACPT: TTRG_stat; var RDP: TRTRadr): TTRG_stat;
      begin
        ACPT:= PDmFPL(p)^.TRG;
        RDP:= PDmFPL(p)^.RDP;
        get_accept:= ACPT
      end;

  procedure OmFPL.set_accept(p: pointer; TRG: TTRG_stat; RDP: TRTRadr);
      begin
        PDmFPL(p)^.TRG:= TRG;
        PDmFPL(p)^.RDP:= RDP
      end;
{$ENDIF}


{$IFDEF OPL}

  { ------------------------------------
    triedenie podla stavu a casu startu
    ------------------------------------
  }

  function is_those_FPL(FPL: PDmFPL; stat: string; vlastne: bool): bool;
     var   v,s : bool;
     begin
       v := {$IFDEF AIRBASE} _plan_pre(FPL^.let) {$ELSE} true {$ENDIF};
       s := _is_stat(FPL^.stat,stat,false);
       is_those_FPL:=  s and ((vlastne and v) or (not vlastne and not v))
     end;


  function sort_mFPLs(const mFPLs: PmFPLs; var _lo: int; _hi: int; stat: string; vlastne: bool): bool;
     var   FPL,FPLi  : PDmFPL;
           __lo,__hi : int;
           i,j       : int;
           r         : bool;
     label L;
     begin
       r:= false; __lo:= _lo; __hi:= _hi;

     { a) presun stat a vlastne, ustanovenie _lo,_hi
     } i:= __lo;
       while i<=__hi do
         begin
           FPL:= mFPLs^[i];
           if is_those_FPL(FPL, stat,vlastne) then
              begin
                inc(__lo);
                inc(i)
              end
           else begin
                  j:= i+1;
                  while j<=__hi do
                     if is_those_FPL(mFPLs^[j], stat,vlastne) then break
                     else inc(j);
                  if j<=__hi then
                     begin
                       FPL:= mFPLs^[i]; mFPLs^[i]:= mFPLs^[j]; mFPLs^[j]:= FPL;
                       r:= true
                     end
                  else __hi:= i-1
                end
           end;

     { b) zotriedenie v _lo,_hi podla casu - startu (vlastne) - pristatie (ine)
     } i:= _lo;
       while i<=__lo do
         begin
           L: FPLi:= mFPLs^[i];
           if (FPLi^.trat_<>nil) then
              begin
                j:= i+1;
                while j<=__hi do
                  begin
                    FPL:=  mFPLs^[j];
                    if (FPL^.trat_<>nil) and (FPL^.trat_^[0].casD<FPLi^.trat_^[0].casD) then
                       begin
                         mFPLs^[i]:= mFPLs^[j]; mFPLs^[j]:= FPLi;
                         r:= true;
                         goto L
                       end
                    else inc(j)
                  end
              end;
           inc(i)
         end;

       _lo:= __lo;
       sort_mFPLs:= r
     end;


  function triedenie_mFPLs(const mFPLs: PmFPLs; top: int): bool;
     var   _lo,_hi : int;
           res : bool;
     begin
       if tab_mFPL_abc then res:= QuickSort(Pptrs(mFPLs),@comp_idn_mFPL,nil{@swap_mFPL},0,top, false)
       else begin
              res:= false; _lo:= 0; _hi:= top;
            { cnst_disk }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_disk, true) or res ;
            { cnst_sended }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_sended, true) or res ;
            { cnst_prop }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_prop, true) or res ;
            { cnst_acc  }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_acc, true) or res ;
            { prijimane ostatnie }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_disk+cnst_sended+cnst_prop+cnst_acc, false) or res ;
            { active nase    }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_stat_act, true) or res ;
            { active ostatne }
              res:= sort_mFPLs(mFPLs, _lo,_hi, cnst_stat_act, false) or res
            end;
       triedenie_mFPLs:= res
     end;


  function OmFPL.sort: bool;
     begin
       sort:= triedenie_mFPLs(PmFPLs(ap), top) { neskor prehodit triedenie len do scrollera }
     end;

{$ENDIF}