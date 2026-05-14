function TPLAN.stav_planu(p: pointer; cas: real; var zmena: bool): Tpoz;
   begin
     if (p_poz<>nil) then stav_planu:= TPozFunc_prvb(p_poz)(p,cas,zmena)
     else begin
            zmena:= false;
            stav_planu:= poz_LETI
          end
   end;

function TPLAN.urc_platnost(p: pointer; var zmena: bool; kresli: bool): Tpoz;
   begin
     urc_platnost:= stav_planu(p, AbsTime, zmena)
   end;

{$IFDEF SECTORS}
 { urci paramatere planu na sektore
 } function TPLAN.urc_platnostS(p: pointer): bool;
      begin
        urc_platnostS:= is_to_addS(p)
      end;
{$ENDIF}


{function TPLAN.zrusit_plan(poz: Tpoz): bool;
   begin
     zrusit_plan:= not ->!is_to_add(p) namiesto (poz>=poz_HANGAR)
   end;}
