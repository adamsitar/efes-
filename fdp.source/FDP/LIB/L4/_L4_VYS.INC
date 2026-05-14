{ -------------------------
   Kodovanie
  תתתתתתתתתתתתתתתתתתתתתתתתת
}

{ vrati kolko znakov ma mat prislusna vyska
}
 function get_alt__(vys_: char): int;
    begin
      case vys_ of
        altG  : get_alt__:= altG_;
        altA  : get_alt__:= altA_;
        altFL : get_alt__:= altFL_
        else    get_alt__:= altS_  { altM, altH }
      end
   end;

 function alt_ab_(ab: char): char;
    begin
      if ab=altAbove then ab:= #24
      else if ab=altBellow then ab:= #25;
      alt_ab_:= ab
    end;

 function check_alt_(vys: word; vys_: char): char;
    begin
      if (vys_ in [altA,altFL]) then
         begin
           if vys<lo_FL then vys_:= altA
         end
      else if (get_altM(vys_,vys) <= alt_VFR) then
              if alt_VFR_G then vys_:= altG
              else vys_:= altM;
      check_alt_:= vys_
    end;


{ ---------------------
   Kodovanie vysky
  ---------------------
}
 { nastavi priznak vysky tak, aby zodpovedal predpisu
   a nastaveniu systemu
 }
 function code_l4_vys (vys: word; vys_: char): string;
    begin
      code_l4_vys:= vys_+IntToStr(vys,get_alt__(vys_),0);
    end;

 function alt_to_str_(vys: word; vyska_, ab: str3; in_FL,in_VFR,in_EDD: bool): string;
    var   s   : string;
          i   : int;
          vys_: char;
    begin
      {if vys<>0 then}
         begin
           if vyska_<>'' then vys_:= vyska_[1] else vys_:= ' ';
          { IFDEF FPL}
           if (vys<>0) and (get_altM(vys_,vys) <= alt_VFR) and (in_VFR) then s:= vys_VFR
           else
          { ENDIF}
             begin
               if in_FL and (not (vys_ in [altA,altFL])) then
                  begin
                    vys:= minimum(MtoFL(get_altM(vys_,vys)),high(vys));
                    vys_:= altFL
                  end;
               if (not in_FL) and (vys_ in [altA,altFL]) then
                  begin
                    vys:= MtoS(FLtoM(vys));
                    vys_:= altS
                  end;
               vys_:= check_alt_(vys,vys_);
               s:= code_l4_vys (vys,vys_);
               if cut_(ab)<>'' then
                  begin
                    if in_EDD then ab:= alt_ab_(getchar(ab));
                    s:= s+ab;
                  end;
             end
         end
      {else s:= inschar(altS,1+altS_,' ',1)};
      alt_to_str_:= s
    end;

 function alt_to_str(vys: word; vyska_, ab: str3; in_FL,in_VFR: bool): string;
    begin
      alt_to_str:= alt_to_str_(vys, vyska_, ab, in_FL,in_VFR,false)
    end;


 function code_l4_vys_(vys: word; vys_: char; ft_od: word; in_VFR: bool): string;
    begin
      code_l4_vys_:= alt_to_str(vys,vys_,'', in_FL and (ft_od>0) and (MtoFL(get_altM(vys_,vys))>=ft_od), in_VFR)
    end;

 { Vyska sa zadava podla L4444 spolu s rozsirenim o zapis GND,VFR,UNL
 }
 function code_l4_vyss_(vys: long; vys_: char; ab: str3; in_FL,in_VFR,in_EDD: bool): string;
    var   s: string;
    begin
      if vys=alt_GND then s:= vys_GND
      else if vys>=alt_UNL then s:= vys_UNL
      else s:= alt_to_str_(vys,vys_,ab,in_FL,in_VFR,in_EDD);
      code_l4_vyss_:= s
    end;

 function code_l4_vyss (vys: long; vys_: char): string;
    var   s: string;
    begin
      if vys=alt_GND then s:= vys_GND
      else if vys>=alt_UNL then s:= vys_UNL
      else s:= code_l4_vys (vys,vys_);
      code_l4_vyss:= s
    end;


{ ---------------------
   Dekodovanie vysky
  ---------------------
}
 function decode_l4_vys_ (s: string; var vys: word; var vys_: char; vys_a: pchar; var dlzka: int; range: bool): bool;
    var   i,p,c : int;
          v : long;
    begin
      decode_l4_vys_:= false;
      vys:= 0; vys_:= vysOB; if vys_a<>nil then vys_a^:= ' '; dlzka:= 0;
      s:= l4str(s);
      if s='' then Exit;

      if copy(s,1,length(rte_VFR))=rte_VFR then
         begin
           vys := MtoS(alt_VFR);
           vys_:= altG;
           dlzka:= length(rte_VFR);
           decode_l4_vys_:= true;
           Exit
         end;

      if (length(s)>0) and (s[1] in setPism) then begin vys_:= s[1]; i:= 2 end
      else begin vys_:= vysOB {altS}; i:= 1 end;
      p:= get_alt__(vys_);
      val(copy(s,i,p),v,c);
      if (vys_a<>nil) and (p+(i-1)<length(s)) and (s[i+p] in (set_alt_-[' '])) then
         begin
           vys_a^:= s[i+p];
           dlzka:= p+i
         end
      else dlzka:= p+(i-1);

      if     (c=0)
         and ((not range) or (v<>0))
         and (get_altM(vys_,v)<=high(vys))
         and (vys_ in set_alt)
         then begin
                decode_l4_vys_:= true;
                vys:= v;
              end
    end;

 { Vyska musi byt podla ICAO predpisov vcitane dlzky
 }
 function decode_l4_vys (s: string; var vys: word; var vys_: char): bool;
    var   dlzka : int;
    begin
      decode_l4_vys:= decode_l4_vys_(cut_(s), vys,vys_,nil, dlzka,true) and (dlzka=length(s))
    end;

 function decode_l4_vyss (vyss: string; var vys: word; var vys_: char; vys_ab: pchar): bool;
    var   bres: bool;
          m: long;
          p: int;
    begin
      vys:= 0; { vys_:= altM; }
      decode_l4_vyss:= true;

      if      vyss=vys_GND then vys:= alt_GND
      else if vyss=vys_VFR then begin vys:= MtoS(alt_VFR); vys_:= altG end
      else if vyss=vys_UNL then vys:= trunc(alt_UNL)
      else decode_l4_vyss:= (*decode_l4_vys{_} (vyss, vys,vys_{,vys_ab,p, false})*)
                                decode_l4_vys_(vyss, vys,vys_,nil, p,false)
                            and (p=length(vyss))
    end;


 { VYS1VYS2
 }
 function decode_l4_vys2 (s: string;
                          var vys: word; var vys_,vys_a: char;
                          var vys2: word; var vys2_,vys2_a: char
                         ): bool;
    var   bres  : bool;
          p     : int;
    begin
      s:= l4str(s);
      bres:= decode_l4_vys_ (s, vys,vys_,nil,p,true);
      if bres then
         if p<length(s) then
            begin
              s:= copy(s,p+1,length(s)-p);
              if s=altPLUS then vys_a:= altA
              else bres:=     decode_l4_vys_ (s, vys2,vys_,@vys2_a,p,true)
                          and (p=length(s));
            end;
      decode_l4_vys2:= bres
    end;


{ -------------------------
   Prepocty
  תתתתתתתתתתתתתתתתתתתתתתתתת
}

 function decode_l4_vys_M (s: string): word;
    var   vys  : word;
          vys_ : char;
    begin
      if decode_l4_vyss (s,vys,vys_,nil) then
         begin
           vys:= minimum(get_altM (vys_,vys),high(vys));
           decode_l4_vys_M:= vys
         end
      else decode_l4_vys_M:= 0
    end;

 function _vys_OB (vys: word; vys_: char): word;
    begin
      _vys_OB:= minimum(get_altM(vys_,vys) div m_S,high(vys))
    end;

 function decode_l4_vys_OB (s: string; var vys: word; var vys_a: char): bool;
    var   vys_  : char;
          dlzka : int;
    begin
      if decode_l4_vys_ (s,vys,vys_,@vys_a,dlzka,true) then
         begin
           decode_l4_vys_OB:= true;
           vys:= _vys_OB(vys,vys_)
         end
      else decode_l4_vys_OB:= false
    end;


 { vrati vysku v desiatkach metrov ako S alebo G
   - prepocet chyby pri rozvrstveni hladin an UK je medziach
     tolerancie 900m
 }
 function FLtoM(FL: long): long;
    var   FLr: real;
    begin
      FLr:= FL;
      FLr:= Zaokruhli(FLr*100*m_ft, 50);
      FLtoM:= trunc(FLr)
    end;

 { vrati vysku ako FL alebo A (ak je pod minimalnou FL=60)
 }
 function MtoFL(M: long): long;
    var   Mr: real;
    begin
      Mr:= M;
      Mr:= Zaokruhli(trunc(Mr/m_ft/m_S),100) / m_S;
      {$IFDEF LK}
      { Letova hladina doplnena podla ziadosti z r.2001
        Zdenka Peterku o F125
        a Radka Matouska o F135 a F145
      }
       {if (M > 3650) and (Mr < 4550) then}
       if     (alt_FL5min<>0) and (alt_FL5max<>0)
          and (M > FLtoM(alt_FL5min)) and (Mr < FLtoM(alt_FL5max))
          then
          begin
            Mr:= M;
            Mr:= Zaokruhli(trunc(Mr/m_ft/m_S),50) / m_S;
          end;
      {$ENDIF}
      MtoFL:= trunc(Mr)
    end;

 function MtoS(M: long): long;
    begin
      MtoS:= M div m_S
    end;

 function StoM(S: long): long;
    begin
      StoM:= S * m_S
    end;


 { vrati vysku letu v metroch
 }
 function get_altM(vys_: char; vys: long): long;
    begin
      case upcase(vys_) of

        altG,
        altS,altH,altM  : get_altM:= StoM (vys);

        altFL,altA : get_altM:= FLtoM(vys)

        else get_altM:= vys
      end;
    end;
