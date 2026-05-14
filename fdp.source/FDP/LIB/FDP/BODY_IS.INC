{ ak trat obsahuje jednoznacny identifikacny bod, vrati true
}
 function is_iobod (bod: string): int;
    var   i : int;
    begin
      is_iobod:= -1;
      bod:= mtks_rus_to_lat(uni_str(bod));
      i:= 0; while (i<OBs_io) and (bod<>OB_io^[i].kod) do inc(i);
      if (i>=OBs_io) then i:= -1;
      is_iobod:= i
    end;

{ urcenie ci smery uvedene na bode zodpovedaju smeru let-u
}
 function is_iobod_dir (bod,let: string; var dir: string): bool;
    var   i,j,k  : int;
          lets,s : string;
          is     : bool;
    begin
      dir:= '';
      is_iobod_dir:= false;
      i:= is_iobod (bod);
      if i=-1 then Exit;

      let:= mtks_rus_to_lat(uni_str(let));
      lets:= strpas(OB_io^[i].io);
      k:= getstritems(lets,[icao_NXIT]);
      is:= false; j:= 1; while (j<=k) and (dir='') do
        begin
          s:= getstr(lets,j,[icao_NXIT]);
          is:= copy(let,1,length(s)) = s;
          if is then dir:= s
          else inc(j)
        end;
      is_iobod_dir:= is
    end;


{ ------------------------------------------
  Je to znamy bod alebo trat ?
  ------------------------------------------
  Ak sa dodefinuje dalsie pole OB alebo RTE,
  upravit nasledujuce fcie,
  alebo definovat ich pole...
  ------------------------------------------
}

{ Vypocet vzdialenosti od bodu daneho azimutom podla L4444,
  napr. VOR040110, VR001099K
}
 function is_VOR (kod: string; var x,y: real): bool;
    var   azl,ral : long;
          az,ra   : real;
          s       : string;
          i,k     : int;
          km      : bool;
          Bi      : TsBod;
    begin
      is_VOR:= false;
      kod:= l4str(kod);

     { a) kontrola dlzky a poloh udajov
     }
      if not inRange(length(kod), kodl_VOR+kod_VOR_AZ+kod_VOR_RA, kodh_VOR+kod_VOR_AZ+kod_VOR_RA+1) then Exit;
      i:= 1; while (i<=length(kod)) and (kod[i] in setPism) do inc(i);
      if not (i in[kodl_VOR,kodh_VOR]) then Exit;

     { b) nacitanie poloziek
     }
      s:= copy(kod,1,i);
      if not (is_scis(kod,i+1,kod_VOR_AZ, azl) and is_scis(kod,i+1+kod_VOR_AZ,kod_VOR_RA,ral)) then Exit;
      az:= azl; ra:= ral;
      km:= kod[length(kod)] = dstK;

     { c) vypocet vzdialenosti
     }
      i:= _OBind_(s,OB,Bi); if i=-1  then Exit;
      azimut(az,ra, x,y);
      x:= Bi.x+x; y:= Bi.y+y;

      is_VOR:= true
    end;


 function is_VOR_or_ZS (kod: string; var B: TsBod): bool;
    var   zd,zs : Tzdzs;
    begin
      fillchar(B,sizeof(B),0);
      kod:= getstr(l4str(kod),1,[icao_NXT]);

     { Azimut ?
     } if is_VOR(kod, B.x,B.y) then B.kod:= kod{_ZSxy}

     { ZemSur ?
     } else if decode_l4_ZemSur(kod, zd.st,zd.mn,zd.se, zs.st,zs.mn,zs.se) then
         begin
           ZdZs_xy(zd,zs, B.x,B.y);
           B.kod:= kod{_ZSxy};
         end;

      is_VOR_or_ZS:= B.kod<>''
    end;
