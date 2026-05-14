 function  init_pole_to_print (var s: array of string; max,poc: int; pole: pchar; _end: bool): int;
     var   i,p : int;
           odd : char;
     begin
       if pole<>nil then
          begin
            p:= getPstritems(pole,setNL+setNL_);
            i:= 0; while (i<p) and (poc+i<max) do
              begin
                s[poc+i]:= _PRN_TAB;
                if i=0 then odd:= icao_ARR else odd:= icao_NXIT;
                s[poc+i]:= s[poc+i] + odd + getPstr(pole,i+1,setNL+setNL_);
                if (i=p-1) and _end then s[poc+i]:= s[poc+i]+icao_END;
                inc(i)
              end;
            inc(poc,i)
          end;
       init_pole_to_print:= poc
     end;


 function decode_code_to_hd(kod: TNETtyp): Thead_ICAO;
    var   hd: Thead_ICAO;
    begin
      case kod of
        0 :  hd:= '   '
        else hd:= '   '
      end;
      decode_code_to_hd:= hd
    end;

 function code_hd_to_code(hd: Thead_ICAO): TNETtyp;
    begin
      code_hd_to_code:= 0
    end;


 function frame_l4_pkt(var data: pchars; var size: TNETdlz; var res: string): bool;
    begin
      res:= '';
      if data^[0]=icao_STD then begin data:= @data^[1]; dec(size) end
      else l4_err(a_L4, '', 0,1, res);
      if (size>0) and (data^[size-1]=icao_END) then dec(size)
      else l4_err(a_L4, '', 0,2, res);
      frame_l4_pkt:= res=''
    end;


{ --------
   kluc
  --------
}
 function  codekey_fpl(_7a,_13a: string; _D: TDate): string;
    begin
      codekey_fpl:= mtks_rus_to_lat(
                                  l4_format_s(_7a)
                     + icao_ARR + l4_format_s(_13a)
                     + icao_ARR + code_l4_date(_D)
                    )
    end;

 procedure decodekey_fpl(s: string; var _7a,_13a: string; var _D: TDate);
     begin
       _7a := {delchar(}decode_l4_s(getstr(s,pos_key_7a,[icao_ARR]),true){,[' '])};
       _13a:= {delchar(}decode_l4_s(getstr(s,pos_key_13a,[icao_ARR]),true){,[' '])};
       decode_l4_date(getstr(s,pos_key_DATE,[icao_ARR]),_D)
     end;
