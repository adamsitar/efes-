const DBFdesc_sta_fplc : array[0..2] of TDBFfdesc =
      ((name:'FLIGHT';typ:dbfSTRING;dlz:7),
       (name:'DEP';   typ:dbfSTRING;dlz:4),
       (name:'ARR';   typ:dbfSTRING;dlz:4)
      );


procedure code_dbf_STRING(s: string; buff: PDBF_buff; var pos: int; dlz,size: int);
    var   l : int;
    begin
      if pos+dlz <= size then
         begin
           l:= minimum(length(s),dlz);
           move(s[1],buff^[pos],l)
         end;
      inc(pos,dlz);
    end;


procedure code_dbf_sta_fplc(p: pstring; buff: PDBF_buff; size: int);
    var   s1,s2,s3: string;
          pos: int;
    begin
      pos:= 0;
      code_dbf_STRING(getstr(p^,1,['-']),buff,pos,DBFdesc_sta_fplc[0].dlz,size);
      code_dbf_STRING(getstr(p^,2,['-']),buff,pos,DBFdesc_sta_fplc[1].dlz,size);
      code_dbf_STRING(getstr(p^,3,['-']),buff,pos,DBFdesc_sta_fplc[2].dlz,size);
    end;

procedure decode_dbf_sta_fplc(buff: PDBF_buff; p: pstring; size: int);
    begin
    end;

var  s: string;
     d: PDBF;

  d:= new(pdbf,init('1.dbf',false,
                    @DBFdesc_sta_fplc,3,
                    @code_dbf_sta_fplc,@decode_dbf_sta_fplc,-1
                   ));
  s:= 'KLM3333-LKPR-LZIB';
  d^.zapis(@s,-1,false);
  s:= 'AFL123 -UUEE-EEWW';
  d^.zapis(@s,-1,false);
  s:= 'MIL    -300 -500 ';
  d^.zapis(@s,-1,false);
  dispose(d,done);
}