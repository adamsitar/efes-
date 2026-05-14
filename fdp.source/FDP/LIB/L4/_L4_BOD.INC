{ ZEMSUR

  Tvar podla L444 :

    4905N01920E
    49N019E

           alt_ZS   = [zsN,zsS];
           kod_ZS_  = 4;            stupne a minuty...
           kod_ZS   = 2;

           alt_ZD   = [zdE,zdW];
           kod_ZD_  = 5;
           kod_ZD   = 3;

}

 { Podla prepisu L4444,
   nekontroluje sa pretecenie...
 }
 function decode_l4_ZemSur(kod: string; var zdst,zdmn,zdse, zsst,zsmn,zsse: byte): bool;
    var   s1,s2 : string;
          p1,p2 : char;
          x,y   : real;
          i,j   : int;
    begin
      kod:= mtks_rus_to_lat(kod);
      decode_l4_ZemSur:= false;
      if not ((length(kod) in [kod_ZS+1+kod_ZD+1,kod_ZS_+1+kod_ZD_+1])) then Exit;

      s1:= getstr(kod,1,setPism); s2:= getstr(kod,2,setPism);
      if not (    (length(s1) in [kod_ZS_,kod_ZS])
              and (kod[length(s1)+1] in [zsN,zsS])
              and (length(s2) in [kod_ZD_,kod_ZD])
              and (kod[length(s1)+1+length(s2)+1] in [zdE,zdW])
             ) then Exit;

      zsst:= scis(s1,1,2); zsmn:= scis(s1,3,2); zsse:= 0;
      zdst:= scis(s2,1,3); zdmn:= scis(s1,4,2); zdse:= 0;

      decode_l4_ZemSur:=     inRange(zsst,0,89) and inRange(zsmn,0,59)
                         and inRange(zdst,0,89) and inRange(zdmn,0,59)
    end;

 function code_l4_ZemSur(zdst,zdmn,zdse, zsst,zsmn,zsse: byte; short: bool): string;
    var   s: string;
    begin
      s:= inttostr(zsst,2,0);
      if not short then s:= s + inttostr (zsmn+trunc(0.5+zsse/60),2,0);
      s:= s + firZS + inttostr(zdst,3,0);
      if not short then s:= s + inttostr(zdmn+trunc(0.5+zdse/60),2,0);
      code_l4_ZemSur:= s
    end;

 function decode_l4_zs (kod: string; var zd,zs: TZdZs): bool;
    begin
      decode_l4_zs:= decode_l4_ZemSur(kod, zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se);
    end;

 function code_l4_zs (zd,zs: TZdZs; short: bool): string;
    begin
      code_l4_zs:= code_l4_ZemSur(zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se, short);
    end;


{ BOD
}

 function code_l4_bod_(kod: string; h,m: byte; vys: word; vys_,vys_a: char;
                       var vysp: word; var vysp_,vysp_a: char
                      ): string;
    begin
      kod:= kod + icao_NXT + code_l4_utc(h,m);
      if    (get_altM (vys_,vys) <> get_altM (vysp_,vysp))
         or (vys_a<>vysp_a)
            then kod:= kod + icao_NXT + code_l4_vys(vys,vys_{,ft_od,in_VFR});
      vysp:= vys; vysp_:= vys_; vysp_a:= vys_a;
      code_l4_bod_:= kod
    end;

 function decode_l4_bod_ (s: string;
                          var kod: string; var h,m: byte; var vys: word; var vys_,vys_a: char;
                          var vysp: word; var vysp_,vysp_a: char
                         ): bool;
    var   t : string;
          p : int;
          res : bool;
    begin
      kod:= getstr(s,1,[icao_NXT]);
      res:= decode_l4_utc(getstr(s,2,[icao_NXT]), h,m);
      t:= getstr(s,3,[icao_NXT]);
      if t<>'' then
         begin
           res:= decode_l4_vys_(t, vys,vys_,@vys_a,p, true) and res;
           vysp:= vys; vysp_:= vys_; vysp_a:= vys_a
         end
      else begin
             vys:= vysp; vys_:= vysp_; vys_a:= vysp_a
           end;
      decode_l4_bod_:= res
    end;


 function code_l4_bod(kod: string; vys: word; vys_: char; ft_od: word; in_VFR: bool; h,m: byte): string;
    begin
      code_l4_bod:= kod+icao_NXT+code_l4_vys_(vys,vys_,ft_od,in_VFR)+icao_NXT+TimeToStr(h,m,'')
    end;
