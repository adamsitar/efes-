
 function OTLG_form._read_formular_data(var res: string; var ires: int): string;
    var   a,s,t : string; p: char;
          c,i   : int;
          d     : pchars;
    begin
      res:= '';

      (*i:= o_f; p:= ' ';  { to bolo inherited }
      while i<items do
        begin
          s:= _it(i); t:= cut_(s);
          if s<>'' then p:= s[length(s)] else p:= ' ';
          if (i>=o_f) then
             begin
               if (is_polex(i,i+1) or is_poley(i,i+1)) then a:= n_a
               else if t<>'' then a:= icao_ARR
               else a:= '';
               {
               if      (a=icao_ARR)
                   and (    ((strlen(data)>0) and (data[strlen(data)-1]=icao_ARR))
                         or ((t<>'') and (t[length(t)]=icao_ARR))
                       ) then a:= '';
               }
             end
          else a:= '';
          data:= StrNPCopy(data,s+a,true,true);
          inc(i)
        end;

      if res='' then
         begin
           c:= strlen(data)-1;
           while (c>=0) and (data[c] in [' ',kbLF,kbCR]) do dec(c);
           if (c<0) or (c=strlen(data)-1) then Exit;
           inc(c); getmem(d,c+1); fillchar(d^[0],c+1,0);
           move(data[0],d^[0],c);
           strdispose(data);
           data:= pchar(d)
         end;*)

       read_pole(o_f,data);
      _read_formular_data:= res
    end;


 procedure  formular_TLG;
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PTLG_form;
            Ev    : TEvent;
     begin
       form:= New(PTLG_form,Init(tit_TLG, f,
                  'TLG' (*{$ifdef debug}  {$else} '' {$endif}*), kbNL,
                  nil,0, form_TLGaftn,size_TLGaftn, 0,
                  nil{@data}, nil,nil{@check},nil,nil, 10,nil)
                 );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;