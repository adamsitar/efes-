 procedure error_vys (fn, s: string);
     begin
       RunError(fn+' -> Invalid value of area altitude profile ('+s+').');
     end;

{ Inicializacia udajov o riadenych oblastiach
}
 function  _nacitanie_oblasti_riadenia(fn,s: string): pointer;
    var    r : TsectorOB;
           p : PsectorOB;
           t : string;
           i : int;

    function decode_vys(s: string): word;
       var   v: word; v_: char;
             bres: bool;
       begin
         bres:= decode_l4_vyss (s, v,v_, nil);
         if not bres then error_vys (fn,s);
         decode_vys:= get_altM(v_,v)
       end;

    begin
      _nacitanie_oblasti_riadenia:= nil;
      fillchar(r,sizeof(r),0);
      s:= s+NULL; r.nazov:= _item_18 (@s[1],cfg_SEC,1);
      if r.nazov='' then Exit;

      r.mapa:= New(PMapy,Init);
      r.mapa^.najdi_a_nacitaj_subor(PathToMAPs+r.nazov+ext_MAP);

      r.v0:= alt_GND; r.v1:= alt_UNL;
      t:= _item_18 (@s[1],cfg_ALT,1);
      i:= getstritems(t,odd_ICAO_);
      case i of
        2 : begin
              r.v1:= decode_vys(getstr(t,2,odd_ICAO_));
              r.v0:= decode_vys(getstr(t,1,odd_ICAO_));
              if r.v1<r.v0 then error_vys(fn,t);
            end;
        1 : r.v1:= decode_vys(getstr(t,1,odd_ICAO_))
      end;
      new(p); p^:= r;
      _nacitanie_oblasti_riadenia:= p
    end;

 procedure _odalokovanie_oblasti_riadenia(var p: pointer);
     begin
       if p=nil then Exit;
       if PsectorOB(p)^.mapa<>nil then Dispose(PsectorOB(p)^.mapa,Done);
       dispose(PsectorOB(p));
       p:= nil;
     end;


 procedure _read_sectors (fn: string; B: PaBody; top: int);
     var   f : text;
           s,t : string;
           p,ires : int;
           Bi  : TsBod;
     begin
       if (Exists(fn)<>0) or (B=nil) then Exit;

       Assign(f,fn); Reset(f); p:= 0;
       while (not Eof(f)) and (p<top+1) do
         begin
           if not read_line (f,s,['"',';'],true) then continue;
           s:= upstring(uni_str(mtks_rus_to_lat(s)));

           ires:= _OBind_ (GetStr(s,pos_kod,odd_body+[' ']),B,Bi);
           if (ires>-1) and (Bi.ine.sector=nil) then
              begin
                Bi.ine.sector:= _nacitanie_oblasti_riadenia(fn,s);
                B^.write(ires,Bi);
                inc(p);
              end
         end;
       ResetIOError;
       Close(f)
     end;

 procedure _done_sectors (B: PaBody);
     var   Bi : TsBod;
           i  : int;
     begin
       if (B=nil) then Exit;
       for i:= 0 to B^.pocet-1 do
         begin
           B^.read(i,Bi);
           if Bi.ine.sector<>nil then
              begin
                _odalokovanie_oblasti_riadenia(Bi.ine.sector);
                B^.write(i,Bi)
              end;
         end;
     end;


 procedure nacitanie_oblasti_riadenia;
     var   i: int;
     begin
       {p_nacitanie_oblasti_riadenia:= nacitanie_oblasti_riadenia;
       p_odalokovanie_oblasti_riadenia:= odalokovanie_oblasti_riadenia;}
       _read_sectors (pathDATA+strpas(fnMLet.fn),LK_m,poc_AIRBASE-1);
     end;

 procedure odalokovanie_oblasti_riadenia;
     begin
       _done_sectors (LK_m);
     end;

