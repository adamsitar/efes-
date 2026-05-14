 function typ_PRS(PRS: PPRS): string;
    begin
      if is_strelnica(PRS) then typ_PRS:= PRIESTOR_STRELNICA {rmk_ACTgnd}
      else if is_TSA (PRS^.kod) then typ_PRS:= hd_TSA
      else if is_P   (PRS^.kod) then typ_PRS:= hd_P
      else {is_P(PRS^.kod)} typ_PRS:= hd_R
    end;


 function is_strelnica (PRS: PPRS): bool;
    begin
      is_strelnica:=     (PRS^.typ=PRIESTOR_STRELNICA)
                      or (_item_18_i(PRS^.pozn,rmk_ACT,1,1)=rmk_ACTgnd)
                      or (_item_18_i(PRS^.pozn,rmk_TYP,1,1)=rmk_ACTgnd)
    end;


{ Kod TSA priestoru, pretoze sa moze skladat z viacerych,
  napr: TSA09c, TSA09d,...
}
  function _TSA_kod(kod: string): string;
     begin
       while (length(kod)>length(hd_TSA)) and (kod[length(kod)] in setPism) do kod:= copy(kod,1,length(kod)-1);
       _TSA_kod:= kod
     end;


{ Zisti, ci to nie su TSA z tej istej oblasi : master (TSA09) a cast (TSA09b)
}
  function in_TSA(kod1,kod2: string): bool;
     var   k1,k2: string;
     begin
       in_TSA:= false;
       if (not is_TSA(kod1)) or (not is_TSA(kod2)) then Exit;

       k1:= _TSA_kod(kod1); k2:= _TSA_kod(kod2);
       if k1<>k2 then Exit;

       in_TSA:= ((k1=kod1) and (pos(k2,kod1)=1)) or ((k2=kod2) and (pos(k1,kod2)=1))
     end;
