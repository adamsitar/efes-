
function O_CAMUS._code_bod_trate (kod: string;
                                  x,y: real;   { ak su to ZemSur }
                                  fn: string
                                 ): string;
   var   zd,zs : Tzdzs;
         B  : TOBxy;
         Bi : TsBod;
         k1 : string;
   begin
     k1:= getstr(l4str(kod),1,[icao_NXT]);
     if      get_OB_XY(k1,B) then
     else if is_VOR(k1,Bi.x,Bi.y) then
     else if _OBind (kod, LK_m)>-1 then kod:= _cairbase(kod)
     else if _OBind (kod, OB_m)>-1 then kod:= _cairbase(kod)
     else if decode_l4_ZemSur(k1, zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se) then
     else if is_LDM(kod) then
          begin
            LDMtoZemSur(kod, zd,zs);
            kod:= code_l4_ZemSur(zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se, true)
          end
     else if (    (((kod=kod_ZSxy) or (kod='')) and (x<>0) and (y<>0))
               or (is_ZemSur(kod) and decode_l4_ZemSur(kod, zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se))
             ) then
          begin
            if ((kod=kod_ZSxy) or (kod='')) and (x<>0) and (y<>0) then xy_ZdZs(x,y, zd,zs);
            kod:= code_l4_ZemSur(zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se, true)
          end;
     _code_bod_trate:= kod
   end;
