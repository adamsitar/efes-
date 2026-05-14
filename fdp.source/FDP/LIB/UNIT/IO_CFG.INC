function read_cfg_line(var f: text): string;
   var   s: string;
   begin
     readln(f,s);
    {$IFNDEF DEBUG}
     write_err_log(s);
    {$ENDIF}
     read_cfg_line:= s
   end;


function __read_cfg_line(fn,key: string;
                         _ind : int;       { index opakovanej premennej }
                         _pos : int        { na pozicii v riadku        }
                        ): string;
   var   t   : text;
         s,r,res : string;
         i,ktory : int;
   begin
      __read_cfg_line:= '';
      if Exists(fn)<>0 then Exit;

      ktory:= 0; s:= ''; key:= uni_str(key);
      Assign(t,fn); Reset(t);
      while not Eof(t) do
        begin
          readln(t,s);
          s:= cut_(s);
          if ((s='') or (s[1]=';')) then continue;

          res:= '';
          {if _pos>0 then s:= getstr(s,_pos,[';']); nezmysel}
          if (pos(key,uni_str(s))<>0) then
             begin
               if _pos<0 then
                  begin
                    i:= 1;
                    while (i<=getstritems(s,odd_cfg-[odd_CFG_EQ])) do
                      begin
                        r:= getstr(s,i,odd_cfg-[odd_CFG_EQ]);
                        if pos(key,uni_str(r))>0 then break;
                        inc(i)
                      end;
                    if _pos=lst_aspon_1_polozka then s:= r;
                    res:= s
                  end
               else begin
                      r:= getstr(s,1,[odd_CFG_EQ]); r:= cut_(r);
                      if uni_str(r)=key then res:= s
                    end;

               if (res<>'') then
                  begin
                    inc(ktory);
                    if ktory=_ind then
                       begin
                         __read_cfg_line:= s;
                        {$IFNDEF DEBUG}
                         write_err_log(s);
                        {$ENDIF}
                         break
                       end
                  end
             end;
        end;
      Close(t)
    end;


function _read_cfg_line(fn,key: string; _ind,_pos: int): string;
   var   s : string;
   begin
     s:= __read_cfg_line(fn,key,_ind,_pos);
     _read_cfg_line:= getstr(s,_pos,odd_cfg)
   end;


function __read_cfg(fn,key: string; _pos: int): string;
   begin
     __read_cfg:= __read_cfg_line(fn,key,_pos,1)
   end;


function _read_cfg(fn,key: string; upcas: bool): string;
   var   s: string;
   begin
     s:= __read_cfg(fn,key,1);
     s:= getstr(s,2,odd_cfg);
     if upcas then s:= uni_str(s) else s:= cut_(s);
     _read_cfg:= s
   end;


function _read_cfg_i(fn,key: string; _ind: int; _pos: int; upcas: bool): string;
   var   s: string;
   begin
     s:= getstr(__read_cfg_line(fn,key,_ind,_pos),_pos,odd_cfg);
     if upcas then s:= uni_str(s) else s:= cut_(s);
     _read_cfg_i:= s
   end;


function read_cfg_str(fn,key: string; var s: string): bool;
   var   t: string;
   begin
     t:= _read_cfg(fn,key,true);
     if t<>'' then s:= t;
     read_cfg_str:= t<>''
   end;

function read_cfg_str_(fn,key: string; s: string): string;
   var   t: string;
   begin
     t:= s;
     if read_cfg_str (fn,key, s) then read_cfg_str_:= s
     else read_cfg_str_:= t
   end;


function read_cfg_pch(fn,key: string): pchar;
   var   t: string;
   begin
     t:= _read_cfg(fn,key,true);
     if t<>'' then read_cfg_pch:= StrPasNew(t)
     else read_cfg_pch:= nil
   end;


function read_cfg_real(fn,key: string; i: real): real;
   var   t: string;
         c: int;
   begin
     read_cfg_real:= i;
     t:= _read_cfg(fn,key,true);
     if t<>'' then
        begin
          val(t, i,c);
          if c=0 then read_cfg_real:= i
        end
   end;


function read_cfg_word(fn,key: string; i: word): word;
   var   t: string;
         c: int;
   begin
     read_cfg_word:= i;
     t:= _read_cfg(fn,key,true);
     if t<>'' then
        begin
          val(t, i,c);
          if c=0 then read_cfg_word:= i
        end
   end;


function read_cfg_bool(fn,key: string; b: bool): bool;
   var   t: string;
   begin
     t:= _read_cfg(fn,key,true);
     if (t=_ON) or (t=_YES) or (copy(t,1,2)=copy(_EN,1,2)) or (t=_TRUE) then b:= true
     else if (t=_OFF) or (t=_NO) or (copy(t,1,3)=copy(_DIS,1,3)) or (t=_FALSE) then b:= false;
     read_cfg_bool:= b
   end;


function  read_line (var f: text; var s: string; skip: TCharSet; skip_comment: bool): bool;
   begin
     readln(f,s);
     s:= ReplChar(s, [#0..#31], ' ');
     s:= cut_(s);
     if skip_comment then skip:= skip+[';','~','"'];
     read_line:= (s<>'') and (not (s[1] in skip))
   end;
