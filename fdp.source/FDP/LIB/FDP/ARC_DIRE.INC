{ --------------------------------------
   vytvorenie nazvu archivacneho subora
  --------------------------------------
}

 function get_PLANfn(den,mes,rok: word): string;
    var   s: string;
    begin
      if den<>not_archive_day then s:= IntToStr(den,2,0)+'-' else s:= '';
      get_PLANfn:= s+IntToStr(mes,2,0)+'-'+IntToStr(rok mod 100,2,0)
    end;

 function get_PLANhod(den,mes,rok, hod: word): string;
    begin
      get_PLANhod:= get_PLANfn(den,mes,rok)+'.'+IntToStr(hod,2,0)
    end;

 function get_prev_HODfn(f_n: string): string;
    const _ : Tcharset = ['-','.'];
    var   h,d,m: byte; r: word;
    begin
      h:= GetInt(f_n,4,_);
      d:= GetInt(f_n,1,_);
      m:= GetInt(f_n,2,_);
      r:= GetInt(f_n,3,_);
      MilleniumDate(r);
      PrevDateH(r,m,d,h);
      get_prev_HODfn:= get_PLANfn(d,m,r)+'.'+IntToStr(h,2,0)
    end;


 function get_ARCHIVfn (path: string): string;
     begin
       get_ARCHIVfn:= path_ARCHIVES + getstr(path,getstritems(path,['\']),['\'])+'\';
     end;

 function get_DBfn_(den,mes,rok: word; path: string; ext: string): string;
    var   d : byte;
    begin
      if den<>not_archive_day then d:= day else d:= not_archive_day;
      if DateToSec(rok,mes,den) < DateToSec(year,month,d) then path:= get_ARCHIVfn(path);
      if (ext<>'') and (ext[1]<>'.') then ext:= '.'+ext;
      get_DBfn_:= path + get_PLANfn(den,mes,rok)+ext
    end;

 function get_DBfn(date: TDate; path: string; ext: string): string;
    begin
      get_DBfn:= get_DBfn_(date.d,date.m,date.r, path, ext)
    end;

 function get_DBfn__(Path,Name, AltFN: string): string;
    var   s: string;
    begin
      s:= najmladsi_subor(Path,Name);
      if s<>'' then get_DBfn__:= s
      else get_DBfn__:= AltFN
    end;


 { -------------------------
    prehlad a vyhladavanie
    - archiv
    - ppl
   -------------------------
 }

 function StrToDate (date: string; var y: word; var m,d: byte): bool;
    begin
      date:= cut_(delchar(date,['-']));
      if length(date)=4 then date:= '01'+date;   { mesacne plany, napr. NOTAMy }
      StrToDate:= GetDateStr(y,m,d,date,false)
    end;

 function  decode_archived_date (date: string; podla_mena: bool; var r: word; var m,d,h: byte): bool;
     var   dt  : DateTime;
           Dir : DirStr; Name: NameStr; Ext: ExtStr;
           c   : int;
     begin
       decode_archived_date:= false;
       if podla_mena then
          begin
            FSplit(date, Dir,Name,Ext);
            if not StrToDate(Name, r,m,d) then Exit;
            {$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
             val(delchar(Ext,['.']),h,c)
            {$IFDEF R}  {$UNDEF R}  {$R+} {$ENDIF}
          end
       else begin
              UnpackTime(_GetFTime(date),dt);
              r:= dt.year; m:= dt.month; d:= dt.day;
              h:= dt.hour
            end;
       decode_archived_date:= true
     end;


 procedure get_plan_date(var d: Tdate; s: string);
    begin
      s:= GetStr(s,GetStrItems(s,['\']),['\']); { s:= delchar(s,setPism+['.','\',':']); }
      d.d:= getint(s,1,['-']);
      d.m:= getint(s,2,['-']);
      d.r:= getint(s,3,['-','.']);
      MilleniumDate(d.r)
    end;

 function get_plan_date_real(s: string): real;
    var   r: word;
          m,d,h, i: byte;
    begin
      h:= getint(s,2,['.']);
      s:= delchar(getstr(s,1,['.']),['-',',','''']);
      if length(s)=4 then begin d:= not_archive_day; i:= 1 end
      else begin d:= scis(s,1,2); i:= 3 end;
      m:= scis(s,i,2); inc(i,2);
      r:= scis(s,i,2); MilleniumDate(r);
      get_plan_date_real:= DTtoSec(r,m,d,h,0,0)
    end;


 function comp_fd1(p1,p2: PFileAttr): bool;
    begin
      comp_fd1:= get_plan_date_real(p1^.name)<get_plan_date_real(p2^.name)  {strcomp(p1,p2)<=0}
    end;

 function comp_fd2(p1,p2: PFileAttr): bool;
    begin
      comp_fd2:= get_plan_date_real(p1^.name)>get_plan_date_real(p2^.name)  {strcomp(p1,p2)>=0}
    end;


 function get_ARCH_FN_(path, ext: string; p_filter: PBFunc_s; title: string): string;
    var   fn : string;
          p  : pointer;
    begin
      fn:= '';
      if path[length(path)]<>'\' then path:= path+'\';
      ext:= delchar(ext,['.']);
      if p_filter<>nil then p:= nil else p:= @decode_date_fn;
      if Exists(path+'*.'+ext)<>0 then Say2(title, msgARCH_EMPTY+'.')
      else fn:= scroll_DIR(path,'*.'+ext, title, '',
                           p_filter,p,false,0,
                           @comp_fd2,0,nil,
                           nil
                          );
      get_ARCH_FN_:= fn
    end;

 function get_ARCH_FN(path, ext, title: string): string;
    begin
      get_ARCH_FN:= get_ARCH_FN_(path,ext,nil, title)
    end;


 function get_PPL_FN_ (path,ext: string; p_filter: PBFunc_s; title: string): string;
    var   fn,name : string;
          p  : pointer;
          k  : int;
    begin
      fn:= '';
      if path[length(path)]<>'\' then path:= path+'\';
      k:= getstritems(ext,['.']);
      if k>1 then
         begin
           name:= getstr(ext,k-1,['.']);
           ext:= '.'+getstr(ext,k,['.']);
         end
      else begin
             name:= fn_all;
             if (ext<>'') and (ext[1]<>'.') then ext:= '.'+ext;
           end;
      if p_filter<>nil then p:= nil else p:= @decode_date_fn;
      if Exists(path+name+ext)<>0 then Say2(title, msgDATA_NOT_FOUND)
      else fn:= scroll_DIR(path,name+ext, title, '',
                           p_filter,p,false,0,
                           @comp_fd1,0,nil,
                           nil
                          );
      get_PPL_FN_:= FN
    end;

 function get_PPL_FN (path, ext, title: string): string;
    begin
      get_PPL_FN:= get_PPL_FN_(path,ext,nil, title);
    end;
