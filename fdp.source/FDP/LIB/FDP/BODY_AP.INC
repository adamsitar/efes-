{ index vojenskeho letiska
}
 function _LKmind (kod: string): int;
    var   Bi   : TsBod;
          ires : int;
    begin
      ires:= _OBind_(kod, LK_m,Bi);
      {i:= 0; while (i<poc_AIRBASE) and (not eq_airbase(kod,LK_m^[i].kod)) do inc(i);}
      if ires>=poc_AIRBASE then ires:= -1;
      _LKmind:= ires
    end;


{ ---------------------------------------
   Najdenie adresy letiska, pre ktore
   je system konfigurovany
  ---------------------------------------
}
 function read_this_airbase: string;
    var   s: string;
    begin
      if not read_cfg_str(SYSTEMcfg,cfg_AIRBASE, airbase) then
         begin
           s:= __read_cfg(SYSTEMcfg,nd_AIRBASE, -1);
           if s<>'' then airbase:= uni_str(getstr(s,2,['=']))
           else begin
                  s:= __read_cfg(NETcfg,nd_THIS,lst_cely_riadok);
                  if s<>'' then
                     begin
                       s:= s+NULL;
                       airbase:= _item_18 (@s[1], nd_AIRBASE, 1)
                     end
                end
         end;
      read_this_airbase:= airbase
    end;

 { Povodna poznamka :

   Funkcie pre spracovanie vojenskych planov.
   Kod letiska je jednou z klucovych poloziek pre spracovanie planu.

   Zatial sa ziskava z X25.cfg a moze byt len jeden, ciselny kod,
   kvoli kontrole na spravnost identifiklacie letu.
   Neskor definovat subor alias mien podla AIPu i prepocet pre vyssie uvedene.
 }

 function this_airbase: string;
    begin
      this_airbase:= airbase
    end;


{ ---------------------------------------
   Adresy letisk
  ---------------------------------------
}
{ Najde adresu podla mena letiska
}
 function adr_airbase(let: string): TNETadr;
    var   i : int;
          a1,a2,adr : string;
          p : pchar;
    begin
      adr_airbase:= '';
      adr:= uni_str(let);
      i:= 0; while (i<NODEpoc) do
        begin
          a1:= StrPas(NODEs^[i].desc.name);
          if (a1<>adr) and (a1<>_cairbase(adr)) and (a1<>_mairbase(adr)) then inc(i)
          else break
        end;
      if (i<NODEpoc) then adr_airbase:= NODEs^[i].desc.adr
    end;


 function aftn_airbase (let: string): string;
    var   adr : string;
    begin
      adr:= _get_comment_(let,pathDATA+strpas(fnMLet.fn),setKomen+[icao_NXIT],pos_body_KOD);
      if adr='' then adr:= _get_comment_(let,pathDATA+strpas(fnMLet.fn),setKomen+[icao_NXIT],pos_body_KOD);
      aftn_airbase:= adr
    end;


{ ---------------------------------------------------------
   KONVERZIE MEDZI CIVILNYM A VOJENSKYM
   SPOSOBOM KODOVANIA LETISK
  ---------------------------------------------------------
}

 function eq_airbase(let1,let2: string): bool;
    begin
      let1:= mtks_rus_to_lat(cut_(let1));
      let2:= mtks_rus_to_lat(cut_(let2));
      eq_airbase:=    (let1 = let2)
                   or (let1 = _mairbase(let2))
                   or (let1 = _cairbase(let2))
    end;

 function _letisko (kod,letisko: string): bool;
    begin
      _letisko:= (cut_(kod)='') or eq_airbase(kod,letisko)
    end;

 function toto_letisko (kod: string): bool;
    begin
      toto_letisko:= _letisko(kod,this_airbase)
    end;



{ ---------------------------------------------------------
   URCENIE TYPU LETISKA
  ---------------------------------------------------------

  - sada <> testov, ktore bude vhodne este
    prehodnotit/unifikovat/zjednodusit
}

{ hlada, ci nazov "let", ktory nie je v zozname AIP,
  nie je inym (civilnym) nazvom letiska, napr. LZKZ
  je civilne oznacenie 500, vrati 500
}

 function _airbase_c (let: string; icao: bool): string;
    var   Bi: TsBod;
    begin
      if _OBind_(let, LK_m,Bi)>-1 then
         begin
           if icao then let:= Bi.ine.icao_kod
           else let:= Bi.kod
         end
      else let:= let;
      _airbase_c:= let
    end;

{ vrati vojensky kod letiska
}
 function _mairbase(let: string): string;
    begin
      _mairbase:= _airbase_c(let, false)
    end;


{ vrati civilny kod letiska
}
 function _cairbase(let: string): string;
    begin
      if civilne_letisko(let) then _cairbase:= let
      else _cairbase:= _airbase_c(let, true)
    end;


 function civilne_letisko (let: string): bool;
    var   i: int;
    begin
     { civilne nemusi byt konfigurovane v popise FIR,
      preto sa testuje podla vseobecnejsich pravidiel
     }
      let:= cut_(let);
      civilne_letisko:= (length(let)=kod_AP) and (copy(let,1,kod_FIR)=FIR)
                        {or  ((i>-1) and (not (LK_m^[i].typ in[sym_MLet,sym_ALet))}
    end;

 function vojenske_letisko (kod: string): bool;
    var   Bi: TsBod;
    begin
      vojenske_letisko:= (_OBind_(kod, LK_m,Bi)>-1) and (Bi.typ=sym_MLet)
    end;

 function ine_letisko (kod: string): bool;
    var   Bi: TsBod;
    begin
      ine_letisko:= (_OBind_(kod, LK_m,Bi)>-1) and (Bi.typ=sym_ALet)
    end;



{ Pre vojenske letiska
}
 function podriadene_letisko (kod: string): bool;

    function podriadene(kod: string): bool;
       var   Bi: TsBod;
       begin
         podriadene:= (_OBind_(kod, LK_m,Bi)>-1) and (Bi.ine.podriadene)
       end;

    begin
      podriadene_letisko:=    (kod='')
                           or eq_airbase(kod,this_airbase)
                           or podriadene(kod)
                           or podriadene(_mairbase(kod))
                           or podriadene(_cairbase(kod))
    end;


 (*{ Vrati vojenske letisko, pod ktore let patri.
   Funguje podla AIP-OPL:
    - riadiace letiska su oznacene "!",
    - vsetky pod nim, az po dalsi "!" su jeho podriadene
 }
 function nadriadene_letisko (let: string): string;
    var   L   : PList;
          r,s : string;
          i,p : int;
    begin
      i:= _OBind(let, kod: string; B: PBODY; max: int): int;

      i:= 0;

      L:= New(PList,Init(@fnLetOPL,[],-3, false)); r:= '';
      i:= 0;

    { najde letisko v zozname OPL letisk }
      while (i<=L^.top) do
        begin
          if not L^.is_nil(i) then
             if (GetStr(StrPas(L^.str^[i]),1,setOddel) = let) then break;
          inc(i);
        end;

      s:= StrPas(L^.str^[i]); p:= pos(cnst_superior_airb,s);
      if i<=L^.top then
         if p<>0 then
            begin
              r:= delchar(copy(s,p,length(s)-p+1),['!']);
              r:= GetStr(r,1,setOddel+setKomen)
            end
         else r:= let;

      Dispose(L,Done);
      nadriadene_letisko:= r
    end;
 *)
