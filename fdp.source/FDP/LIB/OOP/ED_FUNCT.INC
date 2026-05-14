const form_s: PForm = nil;

function s_check(form: PSingleForm; s: Pstring): bool;
   begin
     s^:= '';
     if form_s<>nil then
        begin
          s^:= strpas(form_s^.item); s^:= cut_(s^);
          if form^.upcas then s^:= cs_ascii_str(s^)
        end;
     s_check:= true {s^<>''}
   end;

function formular_s(var _res : string;
                    _max_len : byte;

                    _title   : string;
                    _lst     : PListDesc; { ponuka moznych poloziek }
                    _pos     : int;       { pozicia v polozkach     }
                    _legal   : PCharSet;  { povolene znaky          }
                    _skip    : PCharSet;  { zakazane znaky          }
                    _titpos  : int;       { pozicia popisu          }

                    _s_check : pointer;
                    _pswrd   : bool;
                    _upcas   : bool;
                    _init    : bool;

                    _hlpXXX  : Pchar
                   ): bool;

   var   form   : PSingleForm;
         s      : string;
         E      : TEvent;
   const f : Tcentr = (x: initX; y: initY; m: 1);
   begin
     if _s_check=nil then _s_check:= @s_check;
     _title:= _title+#0;
     _max_len:= maximum(maximum(_max_len,length(_title)),1);
     s:= ''; s:= inschar('',_max_len,' ',1);
     new(form_s); fillchar(form_s^,sizeof(form_s^),0);
     with form_s^ do
       begin
         title:= @_title[1]; lst:= _lst; pos:= _pos; legal:= _legal; skip:= _skip;
         getmem(item,_max_len+1); fillchar(item^,_max_len+1,' '); item[_max_len]:= #0;
         move(s[1],item^,minimum(length(s),_max_len))
       end;

     form:= New(PSingleForm,Init(nil, f.x,f.y, f.m,
                kbEnter,cmOK, _title, form_s,
                clGR2,cfText, 0,
                @s, nil,_s_check,nil, _hlpXXX,false)
               );
     form^.tit:= _titpos;
     if _pswrd then with form^ do begin pswrd:= true {; atext:= 0; abg:= clBUTTON_COLOR+2} end;
     if _init then form^._in(0,_res);

     form^.upcas:= _upcas;
     form^.Run(E);
     formular_s:= form^.corr_res;
     if form^.corr_res then _res:= s else _res:= '';
     Dispose(form,Done);
     freemem(form_s^.item,_max_len+1);
     dispose(form_s)
   end;
