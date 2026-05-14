
{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  kodovanie bodu trate
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

  kodovanie bodu trate medzi OPL/CAMUS a povodnym formatom pouzivanym v LETVISe
}
function O_OPL._decode_bod_trate (kod : string;
                                  fn  : string
                                 ): string;
   var   B          : TOBxy;
         zd,zs      : TZDZS;
         x,y        : real;
         iOB        : PaBody;
         Bi         : TsBod;
         ires,bodov : int;
         bod,act    : string;

   begin
     (*
     bod:= getstr(kod,1,[icao_NXT]);
     act:= copy(kod,length(bod)+2,length(kod)-length(bod)-1);
     kod:= bod;
     if kod<>'' then
        begin
          ires:= 0; while (ires<max_rte_DESC) and (kod<>rte_DESC[ires]) do inc(ires);

          if ires<max_rte_DESC then

          else if get_OB_XYM(kod,B) then

          else if is_LDM(kod) then
                  begin
                    if (kod[1]=MIL_POINT) and (kod[2] in setL) then kod:= copy(kod,2,length(kod)-1) {MIL_POINT+kod}
                  end

          else if ZemSurToReal(kod, x,y) then
                  begin
                    xy_ZdZs(x,y, zd,zs);
                    kod:= code_l4_ZemSur(zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se, true)
                  end

          else if (fn<>'') then
                  begin
                    bodov := get_items_OB(pathDATA+fn,0,maxOBs,[],false);
                    if bodov<>0 then
                       begin
                         iOB -> ak, tak musi byt globalna premmenna !!!
                         iOB := New(PaBody,Init(bodov,sizeof(TsBod),true));
                         read_OBs(pathDATA+fn,iOB,0,bodov,nil,true);
                         ires:= _OBind_(kod, iOB,Bi);
                         if (ires=-1) and (copy(kod,1,2)=MIL_POINT+MIL_OB) then
                             ires:= _OBind_(copy(kod,3,length(kod)-2), iOB,Bi);
                         if ires>-1 then
                            begin
                              xy_ZdZs(Bi.x,Bi.y, zd,zs);
                              kod:= code_l4_ZemSur(zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se, true)
                            end;
                         Dispose(iOB,Done)
                       end
               end
        end;
     if act<>'' then kod:= kod+icao_NXT+act;
     *)
     _decode_bod_trate:= kod
   end;
