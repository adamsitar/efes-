{ ----------------------------

  תתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
procedure _info_SLNKO;
    var   dt  : TDate;
          fl  : TListDesc;
          f   : text;
          s,t,d : string;
          i   : int;
    begin
      if (not formular_DATUM(dt, initX,initY, tit_slnko_dna )) then Exit;

      d:= DateToStr2(dt.d,dt.m,0);
      s:= _get_line_(d,pathLST+fnSLNKO,[' '],1,lst_cely_riadok);
      if s<>'' then
         begin
           assign(f,pathLST+fnSLNKO);
           reset(f); for i:= 1 to 3 do readln(f,t); close(f);
           t:= cut_(getstr(t,1,[hlp_const_h1]));
           if t<>'' then t:= tit_slnko_dna +' ('+d+')' else t:= tit_slnko_dna;
           Say2(t,d+' - '+tit_vychod+' '+getstr(s,2,[' '])+', '+tit_zapad+' '+getstr(s,3,[' '])+'.')
         end
      else Say2(msgSORRY,tit_slnko_dna+' - '+msgNOT_FOUND)
    end;


function get_ind(var s: string; tit: string): bool;
    begin
      s:= '';
      get_ind:= formular_s(s,1, tit,nil{@fnIdn_},0,@setABC,@setNil, 0,nil,false,true,true,nil);
    end;


procedure _info_TYP(_9: string; _dxm,_dym: int);
    var   _9a,_9b,_9c, res,s,u,v, fn : string;
          txt : text;
          i,p,ires : int;
          ini,bres : bool;
    label X;
    begin
      if lst_9bICAO=nil then Exit;

      if (_9='') and (not formular_s(_9,kod_9b, tit_typ_data,@fn_9b,1,@setABC,@setNil, 0,nil,false,true,true,nil)) then Exit;

      ini:= lst_9bICAO^.is_initialized;
      if not ini then lst_9bICAO^.InitList;

      decode_l4_9 (_9, _9a,_9b,_9c);
      bres:= _check_9_by8643 (_9b,res,true,true)<>0;
      bres:=     (lst_9bICAO^.find(_9b,res,ires)>-1)
             and (cut_(res)<>'')
             and (lst_9bICAO^._icao(res)<>ZZZZ);
      if (not bres) then goto X;

      fn:= pathTMP+'_9b.$$$';
      assign(txt,fn); rewrite(txt);
      with lst_9bICAO^ do
        begin
          writeln(txt,'');
          writeln(txt,rightchar(tit_9b_ICAO,  9,' '),': '+_icao(res));
          writeln(txt,rightchar(tit_9b_WTC ,  9,' '),': '+_wtc (res));
          writeln(txt,rightchar(tit_9b_CAT ,  9,' '),': '+_cat (res));
          writeln(txt,rightchar(tit_9b_SPEED, 9,' '),': '+_speed_(res));
          writeln(txt,rightchar(tit_9b_FL,    9,' '),': '+_fl_(res));
          i:= 1;
          while ires<>-1 do
            begin
              s:= _name (res);
              while s<>'' do
                begin
                  p:= minimum(55,length(s));
                  if length(s)>55 then
                     begin
                       while (p>0) and (not (s[p] in [' ',',','/'])) do dec(p);
                       if p=0 then p:= 40;
                       u:= copy(s,1,p)
                     end
                  else u:= s;
                  if i>1 then v:= rightchar(' ',  9,' ')+'  '+cut_(u)
                  else v:= rightchar(tit_9b_NAME,  9,' ')+': '+cut_(u);
                  writeln(txt,v);
                  s:= copy(s,length(u)+1,length(s)-length(u));
                  inc(i);
               end;

               inc(ires);
               while (ires<=top) and (_9b<>_icao(get(ires))) do inc(ires);
               if ires>top then ires:= -1
               else res:= get(ires)
             end;
          writeln(txt,''+kbNL+#255);
        end;

      close(txt);
      _infop(fn, tit_typ_data+' '+_9, _dxm,_dym, true,false,nil);
      del(fn);

      X: if not ini then lst_9bICAO^.DoneList;
    end;

