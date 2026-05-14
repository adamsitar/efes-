
 function  _check_8_by4444 (_8: string; var _8a,_8b: char; var res: string): int;
    var    ires : int;
    begin
      ires:= 0; res:= ''; _8a:= ' '; _8b:= ' ';
      _8:= l4str(_8);
      if _8='' then ires:= l4_err(a_ICAO,a_8a,i_8a,err_icao_iny_udaj, res)
      else if length(_8)<>kod_8 then ires:= l4_err(a_ICAO,a_8a,i_8a,err_icao_ina_dlzka, res);

      if ires=0 then
         begin
           decode_l4_8 (_8, _8a,_8b);
           if (not (_8a in set_8a)) then ires:= l4_err(a_8a,_8a,i_8a,err_8a, res)
           else if (not (_8b in set_8b)) then ires:= l4_err(a_8b,_8b,i_8b,err_8b, res)
         end;
      _check_8_by4444:= ires;
    end;


 function  _check_10_by4444 (_10: string; var _10a,_10b: string; var res: string): int;
    var    ires, i,k : int;
           is,isn : bool;
           s : string;

    label  X;

    begin
      ires:= 0; res:= '';
      _10:= l4str(_10);

     { 10
     }
      decode_l4_10 (_10, _10a,_10b);

      if (_10='') then ires:= l4_err(a_ICAO,a_10,i_10a,err_icao_iny_udaj, res)
      else if (_10a='') then ires:= l4_err(a_ICAO,a_10a,i_10a,err_10a_nezname, res)
      else if (_10b='') then ires:= l4_err(a_ICAO,a_10b,i_10b,err_10b_nezname, res);
      if ires<>0 then goto X;

     { 10a
       test, ci neobsahuje udaj 'N' spolu s inymi,
             ci neobsahuje nedovolenu kobinaciu znakov
     }
      if _10a_CHECK then
         begin
           s:= mtks_rus_to_lat(_10a);

           isn:= false; is:= false;
           k:= 1; i:= 1;
           while (i<=length(s)) do
             begin
               isn:= isn or (s[i] in set_10aN);
               if (s[i] in set_10aS) then
                  begin
                    is:= true;
                    inc(k)
                  end;
               if (s[i]=' ') then inc(k);
               inc(i)
             end;

           if isn and is then
              begin
                ires:= l4_err(a_10a,_10,i_10a,err_10a_N, res);
                goto X
              end;

           if is and (k<length(s)) then
              begin
                ires:= l4_err(a_10a,_10,i_10a,err_10a_kombinacia, res);
                goto X
              end;
         end;

     { 10b
     }
      s:= mtks_rus_to_lat(_10b);
      if _10b_CHECK then
         begin
           if length(s)>kod_10b then ires:= l4_err(a_10b,_10b,i_10b,err_10b_dlzka, res)
           else if   (not (s[1] in set_10b))
                  or (((length(s)>1) and (not (s[2] in set_10b_))))
              then ires:= l4_err(a_10b,_10b,i_10b,err_10b_popis, res);
         end;

      X: _check_10_by4444:= ires;
    end;


 function  _check_13_by4444 (_13: string;
                             var _13a: string; var h,m,h_,m_: byte;
                             var res: string
                            ): int;
    var    r13a,r13b,r13c : bool;
           _13b,_13c : string;
           ires : int;
    begin
      res:= '';
      _13:= l4str(_13);
      _check_13_by4444:= 0;
      if not decode_l4_13_ (_13,
                            _13a, h,m,h_,m_,
                            _13b,_13c,
                            r13a,r13b,r13c
                           ) then
         begin
           if (not r13a) or (length(_13a)<>kod_AP) then ires:= l4_err(a_13a,_13,i_13a,err_13a_neznamy, res)
           else if not r13b then ires:= l4_err(a_13b,_13b,i_13b,err_13b_neznamy, res)
           else if not r13c then ires:= l4_err(a_13c,_13c,i_13c,err_13c_chybny, res)
           else ires:= l4_err(a_ICAO,a_13,i_13a,err_icao_iny_udaj, res);
           _check_13_by4444:= ires
         end
    end;


 function  _check_16_by4444 (_16: string; hs,ms: byte;
                             var _16a: string; var h,m : byte;
                             var _16cd: string;
                             var res: string
                            ): int;
    var    _16b  : string;
           ires  : int;
           hl,ml : byte;
           r16a,r16b,r16c : bool;
    begin
      _16:= l4str(_16);
      _check_16_by4444:= 0;
      if not decode_l4_16_
                       (_16,hs,ms,
                        _16a,_16b,h,m,hl,ml,
                        _16cd,
                        r16a,r16b,r16c
                       )
         then
         begin
           if (not r16a) or (length(_16a)<>kod_AP) then ires:= l4_err(a_16a,_16,i_16a,err_16a_neznamy, res)
           else if not r16b then ires:= l4_err(a_16b,_16b,i_16b,err_16b_neznamy, res)
           else if not r16c then ires:= l4_err(a_16c,_16cd,i_16c,err_16c_chybne, res)
           else ires:= l4_err(a_ICAO,a_16,i_16a,err_icao_iny_udaj, res);
           _check_16_by4444:= ires
         end
    end;


 function _check_17_by4444 (_17: string;
                            var kod: string; var h,m: byte;
                            var name: string;
                            var res: string
                           ): int;
    var   _17b : string;
          ires : int;
          r17a,r17b,r17c: bool;
    begin
      res:= '';
      _17:= l4str(_17);
      if not decode_l4_17_ (_17, kod,_17b, h,m, name, r17a,r17b,r17c) then
         begin
           if not r17a then ires:= l4_err(a_17a,_17,i_17a,err_17a_neznamy, res)
           else if not r17b then ires:= l4_err(a_17b,_17b,i_17b,err_17b_neznamy, res)
           else if not r17c then ires:= l4_err(a_17c,_17,i_17c,err_17c_chybne, res)
           else ires:= l4_err(a_ICAO,a_17,i_17a,err_icao_iny_udaj, res);
           _check_17_by4444:= ires
         end
      else _check_17_by4444:= 0
    end;


 function  _check_14_by4444 (_14: string;
                             typ: string;

                             var kod1    : string;      { vstupny bod FIR/oblasti}
                             var h1,m1   : byte;        { vypocitany cas na bode  }
                             var vys1    : word;        { vyska na bode           }
                             var vys1_   : char;

                             is_vysI     : bool;        { dekodovat vysku I ? }
                             var vysI    : word;        { vyska na hranici do FIR (oblasti) }
                             var vysI_,
                                 vysI_ab : char;

                             var res: string
                            ): int;

    var   b14a,b14b,b14c,b14de : bool;
          _14b,_14c,_14d,_14e  : string;
          ires : int;
          B : TsBod;
    begin
      res:= ''; ires:= 0;
      if decode_l4_14_ (_14,kod1, h1,m1,vys1,vys1_, is_vysI,vysI,vysI_,vysI_ab, b14a,b14b,b14c,b14de, _14b,_14c,_14d,_14e) then
         begin
           if (not is_OB(kod1, B,true)) then ires:= l4_err(a_14a,_14,i_14a,err_14a_neznamy,res);
         end
      else begin
             if not b14a  then ires:= l4_err(a_14a,_14,i_14a,err_14a_neznamy,res)
             else if not b14b  then ires:= l4_err(a_14b,_14,i_14b,err_14b_neznamy,res)
             else if not b14c  then ires:= l4_err(a_14c,_14,i_14c,err_14c_neznamy,res)
             else if not b14de then
                if not (vysI_ab in set_alt_) then ires:= l4_err(a_14e,_14,i_14d,err_14e_neznamy,res)
                else ires:= l4_err(a_14d,_14,i_14d,err_14d_neznamy,res)
           end;
      _check_14_by4444:= ires
    end;
