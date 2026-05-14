
 { vrati kolko znakov ma mat prislusna vyska
 }
 function get_rych__(rych_: char): int;
    begin
      case rych_ of
        spdK  : get_rych__:= spdK_;
        spdN  : get_rych__:= spdN_;
        spdM  : get_rych__:= spdM_
        else    get_rych__:= spdK_
      end
   end;

 function get_rych_kmh(rych: real; rych_: char;
                       vys : word; vys_ : char
                      ): real;
    var   r: real;
    begin
      r:= rych;
      if upcase(rych_)=spdN then r:= r * N_K;
      if upcase(rych_)=spdM then r:= r * M_K;
      get_rych_kmh:= trunc(0.5+r)
    end;



{ RYCH
}
 function code_l4_rych (rych: single; rych_: char): string;
    var   s: string;
    begin
      if rych_=' ' then rych_:= spdK;
      {if rych<>0 then}
         begin
           if rych_<>spdM then str(rych:get_rych__(rych_):0,s)
           else begin
                  str(rych:1:(spdM_-1),s);  { -1 = - bodka }
                  s:= delchar(s,['.'])
                end;
           s:= rych_+replchar(s,[' '],'0')
         end
      {else s:= inschar(spdK,1+spdK_,' ',1)};
      code_l4_rych:= s;
    end;

 function code_l4_rychkmh (rych: single; rych_: char; _in_km: bool): string;
    begin
      if _in_km then
         begin
           rych:= get_rych_kmh(rych,rych_,0,' ');
           rych_:= spdK
         end;
      code_l4_rychkmh:= code_l4_rych (rych,rych_)
    end;


 function decode_l4_rych_(s: string; var rych: single; var rych_: char; var dlzka: int): bool;
    var   p    : int;
          bres : bool;
    begin
      s:= cut_(mtks_rus_to_lat(uni_str(s)));
      if s<>'' then
         begin
           rych_:= s[1];
           dlzka:= get_rych__(rych_)+1;
           s:= copy(s,2,dlzka-1);                                        { s:= getstr(s,1,setPism_);}
           if rych_=spdM then s:= copy(s,1,1)+'.'+copy(s,2,length(s)-1);
           val(s,rych,p);
           bres:= ({rych<>0}p=0) and (rych_ in setRych_);
           {if not bres then rych:= 0;}
         end
      else bres:= false;
      decode_l4_rych_:= bres
    end;


 function decode_l4_rych(s: string; var rych: single; var rych_: char): bool;
    var   p: int;
    begin
      decode_l4_rych:= decode_l4_rych_(s, rych,rych_, p) and (p=length(s))
    end;



{ RYCHVYS
}
 function code_l4_rych_vys(rych: single; rych_: char; vys: word; vys_: char; ft_od: word; in_VFR: bool): string;
    begin
      code_l4_rych_vys:= code_l4_rych(rych,rych_)+code_l4_vys_(vys,vys_, ft_od,in_VFR)
    end;


 function decode_l4_rych_vys_ (s: string;
                               var rych: single; var rych_: char; var sr: string; var rres: bool;
                               var vys: word; var vys_: char;     var sv: string; var vres: bool
                              ): bool;
    var   t: string; p : int;
    begin
      t:= cut_(s); s:= l4str(s);
      rres:= decode_l4_rych_(s,rych,rych_,p); sr:= copy(t,1,p);
      sv:= copy(s,p+1,length(s)-p);
      vres:= (sv<>'') and decode_l4_vys(sv, vys,vys_);
      decode_l4_rych_vys_:= rres and vres;
    end;

 function decode_l4_rych_vys (s: string; var rych: single; var rych_: char; var vys: word; var vys_: char): bool;
    var   sr,sv: string; rres,vres : bool;
    begin
      decode_l4_rych_vys:= decode_l4_rych_vys_ (s,rych,rych_,sr,rres, vys,vys_,sv,vres)
    end;


 function decode_l4_rych_vys2_(s: string;
                               var rych: single; var rych_: char;   var rres : bool;
                               var vys: word; var vys_,vys_a: char; var vres : bool;
                               var vys2: word; var vys2_: char;     var v2res: bool
                              ): bool;
    var   p : int;
    begin
      s:= l4str(s);
      p:= get_rych__(rych_);
      rres:= decode_l4_rych_(copy(s,1,1+p),rych,rych_,p);
      s:= copy(s,p+1,length(s)-p);
      vres:= (s<>'') and decode_l4_vys_(s, vys,vys_,nil,p,true);
      v2res:= true;
      if vres then
         if p<length(s) then
            begin
              s:= copy(s,p+1,length(s)-p);
              if s=altPLUS then vys_a:= altA
              else v2res:= decode_l4_vys_ (s, vys2,vys_,nil,p,true) and (p=length(s));
            end;
      decode_l4_rych_vys2_:= rres and vres and v2res
    end;


 function decode_l4_rych_vys2 (s: string;
                               var rych: single; var rych_: char;
                               var vys: word; var vys_,vys_a: char;
                               var vys2: word; var vys2_: char
                              ): bool;
    var   rres,vres,v2res : bool;
    begin
      decode_l4_rych_vys2:= decode_l4_rych_vys2_(s, rych,rych_,rres, vys,vys_,vys_a,vres, vys2,vys2_,v2res)
    end;