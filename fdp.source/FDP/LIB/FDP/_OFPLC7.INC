function OcFPL.get_priznak (p: pointer): byte;
   begin
     get_priznak:= PDcFPL(p)^.przn[p_others]
   end;

procedure OcFPL.set_priznak (p: pointer; przn: byte; save: bool);
   begin
     PDcFPL(p)^.przn[p_others]:= przn;
     inherited set_priznak (p,przn,save)
   end;


function OcFPL.is_to_chg(p1,p2: pointer): bool;
   begin
     is_to_chg:= zmenene_udaje_FPLc(p1,p2,false,true)
   end;

function OcFPL.get_poz(p: pointer): Tpoz;
   begin
     get_poz:= PDcFPL(p)^.poz
   end;

procedure OcFPL.set_cor(p: pointer; cor: int);
   begin
     PDcFPL(p)^.cor_:= cor
   end;

function OcFPL.get_cor(p: pointer): int;
   begin
     if PDcFPL(p)^.cor_>0 then get_cor:= 1
     else get_cor:= 0{-1}
   end;

procedure OcFPL.cl_cor(p: pointer);
    begin
      PDcFPL(p)^.cor_:= 0;
      inherited cl_cor(p)
    end;


{$IFDEF NET}
   function OcFPL.get_rec(p: pointer): Pplan_rec;
      begin
        get_rec:= @DcFPL(p^).rec
      end;
{$ENDIF}


{$IFDEF RDP_ACCEPT}
   function  OcFPL.get_accept(p: pointer; var ACPT: TTRG_stat; var RDP: TRTRadr): TTRG_stat;
      begin
        ACPT:= PDcFPL(p)^.TRG;
        RDP:= PDcFPL(p)^.RDP;
        get_accept:= ACPT
      end;

   procedure OcFPL.set_accept(p: pointer; TRG: TTRG_stat; RDP: TRTRadr);
      begin
        PDcFPL(p)^.TRG:= TRG;
        PDcFPL(p)^.RDP:= RDP
      end;
{$ENDIF}


{$IFDEF EDD}
 { zaradenie stripu na tablet podla nastavenia: vstupny<->aktualny:
   - vstupny  : zaradi sa na prvy vstupny majak
                IDD
                 - DEP : ak este neostartoval z tohoto letiska
                 - ARR : ak pristava na tomto letisku

   - aktualny : zaradi na aktualny majak, na ktory leti (alebo posledny)

                IDD umoznuje zaradit na
                 - DEP : ak este neostartoval z tohoto letiska
                 - ARR : cas je vacsi ako na poslednom bode
 }
  function OcFPL.zarad(ind: int; is: TSpecGroups): string;
     var   res : string;
           i,j : int;
     begin
       res:= '';

       with PDcFPL(ap^[ind])^ do
         begin

         { je to poznamka o lete ?
         }
           if Trat[0].kod=no_pl then res:= fplNOPL


         { je to let typu VFR ?
         }
           else if _8a in set_VFR then res:= fplVFR


         { IFR let...  najdenie prislusnej skupiny...
         }
           else if NDB_INP then
             begin
               i:= 0;
               {$IFDEF SECTORS} if S_IN and S_DISPLAY then i:= B1 {$ENDIF};
               res:= Trat[i].kod
             end

           else begin
                  i:= na_bod;
                  {$IFDEF SECTORS} if S_ROUTE then i:= maximum(na_bod,B1) {$ENDIF};
                  res:= Trat[i].kod;
                  if (na_bod=bodov) then
                     if     (absTime>=Trat[na_bod].cas)
                        and (prist.kod<>'') then res:= prist.kod
                end;

          {$IFDEF TABLET_DEP_ARR}
           if          (is.is_dep)
                   and (poz <= poz_START)
                   and (toto_letisko(start.kod))
                        then res:= fplDEP

           else if     (is.is_arr)
                   and (poz >= poz_PRIST)
                   and (toto_letisko(prist.kod))
                        then res:= fplARR;
          {$ENDIF}
         end;

       zarad:= res
     end;


  function OcFPL.zarad_inde(ind: int; is: TSpecGroups; res: string): string;
     begin
       if (res=fplOTHER) or ({(res='') and} NDB_OTHERS) then
         {$IFDEF TABLET_WEST_EAST}
           if (smer(ind)=dir_east) and is.is_east then res:= fplEAST
           else if (smer(ind)=dir_west) and is.is_west then res:= fplWEST
           else
         {$ENDIF}
         res:= fplOTHER;
       zarad_inde:= res
     end;


  function OcFPL.smer(ind: int): Ts_dir;
     begin
       smer:= _dir_cFPL(PDcFPL(ap^[ind]))
     end;

  function OcFPL.NDB(ind: int): string;
     begin
       with PDcFPL(ap^[ind])^ do
         if NDB_INP then NDB:= Trat[0].kod
         else NDB:= Trat[na_bod].kod
     end;


  function OcFPL.ETO(ind: int): real;
     begin
       with PDcFPL(ap^[ind])^ do
         {$IFNDEF EDD_20}
           if mini_strip=miniSTRIP then ETO:= Trat[na_bod].cas
           else
         {$ENDIF}
         if NDB_INP then ETO:= Trat[0].cas
         else ETO:= Trat[na_bod].cas
     end;

  function OcFPL.ETD(ind: int): real;
     begin
       with PDcFPL(ap^[ind])^ do ETD:= start.cas
     end;

  function OcFPL.ETA(ind: int): real;
     begin
       with PDcFPL(ap^[ind])^ do ETA:= prist.cas
     end;

  function OcFPL.FL (ind: int): real;
     begin
       with PDcFPL(ap^[ind])^ do
         if NDB_INP or (bodov=0) then
            if (_OBind(start.kod,LK)>=0) and (vys1<>0) then FL:= vys1
            else FL:= vys
         else FL:= trat[na_bod].vys
     end;

{$ENDIF}


{$IFDEF OPL}
   function OcFPL.sort: bool;
      begin
        sort:= QuickSort(ap, @comp_idn_cFPL,nil{@swap_cFPL}, 0,top, false)
      end;
{$ENDIF}
