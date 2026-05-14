 procedure info_SPRlam(SPR: PSPR);
     var   p,i,n,d,m: int;
           fn,adri : string;
           T : text;

     procedure writelnT(n: int);
         var   s: string;
         begin
           if n<0 then Exit;
           s:= ' '+ inschar(strpas(NODEs^[n].desc.name),sizeof(TNETadr),' ',1) + ' :    ' + _msg_acci(SPR,n)+'   ';
           if s<>'' then writeln(T,s);
         end;

     begin
       fn:= pathTMP+'sprlam.@@@';
       Assign(T,fn);
       Rewrite(T);
       writeln(T);
       p:= GetPStrItems(SPR^.adr,set_SPRadr_odd+setNL+setNL_);

       (*m:= sizeof(TNETadr)-1;
       for i:= 1 to p do m:= {maximum(length(_adri(SPR,i)),m);} {maximum(length(_adri(SPR,i)),m);}*)

       for i:= 1 to p do
         begin
           adri:= _adri_net(_adri(SPR,i));
           if _adrbrc(adri) then
              begin
                for n:= 0 to NODEpoc-1 do if _adri_brc (adri,n) then writelnT(n);
              end
           else begin
                  if _adri_nd (adri,n) then writelnT(n)
                end;
         end;
       writeln(T);
       Close(T);
       _info (fn, tit_SPRlam);
       DelFile(fn);
     end;

