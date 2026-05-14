{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  (pre)kodovanie bodu trate
  medzi formatom LETVISu
  a komunikujuceho zaraidenia
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function O_L4_FDP._decode_bod_trate (kod: string;
                                      fn: string
                                     ): string;
    var   x: string;
    begin
      {
      if (kod<>'') and (scis(kod,3,3)<>0) and (kod[1]=MIL_POINT) then
         begin
           if kod[2]=MIL_OB then x:= copy(kod,3,length(kod)-2)
           else x:= copy(kod,2,length(kod)-1);
           if (kod[2]=MIL_OB) or is_LDM(x) then kod:= x
         end;
      }
      _decode_bod_trate:= kod
    end;


 function O_L4_FDP._code_bod_trate (kod: string;
                                    x,y: real;   { ak su to ZemSur }
                                    fn: string
                                   ): string;
    var   B     : TOBxy;
          zd,zs : TZDZS;
          bodik : string;
          iOB   : PBODY;
          iOBs  : int;
    begin
      {
      if get_OB_XY(kod,B) then
         begin
           if (scis(kod,1,KOD_OB)<>0) then kod:= MIL_POINT+MIL_OB+kod
         end
      else if is_LDM(kod) then kod:= MIL_POINT+kod
      else if (   ((kod=kod_ZSxy) and (x<>0) and (y<>0))
               or (is_ZemSur(kod) and decode_L4ZemSur(kod, zd,zs))
              ) then
              begin
                if kod=kod_ZSxy then xy_ZdZs(x,y, zd,zs);
                kod:= code_L4ZemSur(zd,zs)
              end
      else if (fn<>'') then
              begin
                iOBs:= get_items_OB(pathDATA+fn,0,maxOBs,false);
                if iOBs<>0 then
                   begin
                     GetMem(iOB, SizeOf(TBOD)*(iOBs));
                     read_file_OB(pathDATA+fn, iOB,0,iOBs, false);
                     porovnanie bodov ->
                     ak nie suradnice ...
                     if bodik<>'' then kod:= bodik;
                     FreeMem(iOB, SizeOf(TBOD)*(iOBs))
                   end
           end;
      }
      if (   ((kod=kod_ZSxy) and (x<>0) and (y<>0))
          or (is_ZemSur(kod) and decode_l4_zs (kod, zd,zs))
         ) then
              begin
                if kod=kod_ZSxy then xy_ZdZs(x,y, zd,zs);
                kod:= code_l4_zs (zd,zs, false)
              end;
      _code_bod_trate:= kod
    end;

