{ --------------------
  Zoznamy typov
  --------------------
}
 constructor TList_9b_icao.Init(_lst: PListDesc; _fn: string; _init: bool);
       begin
         p_code  := 0;
         p_icao  := 0;
         p_wtc   := 0;
         p_cat   := 0;
         p_speed := 0;
         p_fl    := 0;
         p_name  := 0;
         p_rmk   := 0;
         inherited Init(_lst,_fn, [],lst_cely_riadok_,false,nil,_init);
       end;


 function  TList_9b_icao.read_header(line,prev: string): bool;
    begin
      read_header:= false;
      if not ((prev[1] in setKomen) and (system.pos(tit_9b_HEADER,prev)>0)) then Exit;

      read_header:= true;
      p_code  := system.pos(tit_9b_CODE,line);
      p_icao  := system.pos(tit_9b_ICAO,line);
      p_wtc   := system.pos(tit_9b_WTC,line);
      p_cat   := system.pos(tit_9b_CAT,line);
      p_speed := system.pos(tit_9b_SPEED,line);
      p_fl    := system.pos(tit_9b_FL,line);
      p_name  := system.pos(tit_9b_NAME,line);
      p_rmk   := system.pos(tit_9b_RMK,line);
    end;


 function  TList_9b_icao.data_write (i: int): string;
    var    s: string;
    begin
      s:= get(i);
      data_write:= _icao(s) + icao_NXIT + _name(s)
    end;

 function  TList_9b_icao.find (_type: string; var line: string; var ind: int): int;
    var    ini : bool;
    begin
      ini:= is_initialized;
      if not ini then InitList;

      line:= ''; ind:= 0;
      _type:= cut_(mtks_rus_to_lat(_type));
      if top>-1 then
        if p_code>0 then while (ind<=top) and (_type<>l4str(_code(get(ind)))) do inc(ind)
        else while (ind<=top) and (_type<>_icao(get(ind))) do inc(ind);
      if ind>top then ind:= -1
      else line:= get(ind);
      find:= ind;

      if not ini then DoneList;
    end;


 function  TList_9b_icao._data_item (s: string; zac,kon: int): string;
    begin
      _data_item:= str_item (s, zac,kon)
    end;

 function  TList_9b_icao._code (s: string): string;
    begin
      _code:= _data_item (s,p_code,p_icao)
    end;

 function  TList_9b_icao._icao (s: string): string;
    begin
      _icao:= _data_item (s,p_icao,p_wtc)
    end;

 function  TList_9b_icao._wtc (s: string): string;
    var    p: int;
    begin
      if p_cat<>0 then p:= p_cat else p:= p_name;
      _wtc:= _data_item (s,p_wtc,p)
    end;

 function  TList_9b_icao._cat (s: string): string;
    var    p: int;
    begin
      if p_speed<>0 then p:= p_speed else p:= p_name;
      _cat:= _data_item (s,p_cat,p)
    end;


 function  TList_9b_icao._speed_(s: string): string;
    var    p: int;
    begin
      if p_fl<>0 then p:= p_fl else p:= p_name;
      _speed_:= _data_item (s,p_speed,p);
    end;

 function  TList_9b_icao._speed (s: string;
                                 var rych: single; var rych_: char;
                                 var minkmh,maxkmh: single
                                ): string;
    var    cest,min,max: string;
           r_: char;
           p: int;
    begin
      if p_fl<>0 then p:= p_fl else p:= p_name;
      s := _data_item (s,p_speed,p);

      cest := getstr(s,1,[icao_NXIT]);
      min  := getstr(s,2,[icao_NXIT]);
      max  := getstr(min,2,[icao_ARR]);
      if max<>'' then min := getstr(min,1,[icao_ARR])
      else max:= min;

      decode_l4_rych (cest, rych,rych_);
      decode_l4_rych (min, minkmh,r_);
      minkmh:= get_rych_kmh(minkmh,r_, 0,altS);
      decode_l4_rych (max, maxkmh,r_);
      maxkmh:= get_rych_kmh(maxkmh,r_, 0,altS);

      _speed:= cest
    end;


 function  TList_9b_icao._fl_(s: string): string;
    begin
      _fl_:= _data_item (s,p_fl,p_name);
    end;

 function  TList_9b_icao._fl (s: string;
                              var vys: word; var vys_: char;
                              var minS,maxS: word
                             ): string;
    var    cest,min,max: string;
           v_: char;
           p : int;
    begin
      s := _data_item (s,p_fl,p_name);

      cest := getstr(s,1,[icao_NXIT]);
      min  := getstr(s,2,[icao_NXIT]);
      max  := getstr(min,2,[icao_ARR]);
      if max<>'' then min := getstr(min,1,[icao_ARR])
      else max:= min;

      decode_l4_vyss (cest, vys,vys_,nil);
      decode_l4_vyss (min, minS,v_,nil);
      minS:= get_altM(v_,minS) div m_S;
      decode_l4_vyss (max, maxS,v_,nil);
      maxS:= get_altM(v_,maxS) div m_S;

      _fl:= cest
    end;

 function  TList_9b_icao._name (s: string): string;
    begin
      _name:= _data_item (s,p_name,p_rmk)
    end;

 function  TList_9b_icao._rmk (s: string): string;
    begin
      _rmk:= _data_item (s,p_rmk,0)
    end;


 {$IFDEF DEBUG}
  procedure TList_9b_icao.item_test (s: string);
      var   u, min,max : string;
      begin
        u:= _code  (s);
        u:= _icao  (s);
        u:= _wtc   (s);
        u:= _cat   (s);
        {u:= _speed (s,u, min,max);
        u:= _fl    (s,u, min,max);}
        u:= _name  (s);
     end;
 {$ENDIF}


 function  TList_9b_ine.data_write (i: int): string;
    var    s: string;
    begin
      s:= get(i);
      data_write:= _code(s) + icao_NXIT + _icao(s) + icao_NXIT + _name(s)
    end;

 function TList_9b_mil._mil (s: string): bool;
    begin
      _mil:= system.pos(idMIL,_rmk(s))<>0
    end;
