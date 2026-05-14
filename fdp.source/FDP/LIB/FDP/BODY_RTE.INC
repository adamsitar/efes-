
{ -------------------
   vyhladanie trate
  -------------------
}
 procedure disp_RTE (var rte: TRTE);
     var   i: int;
     begin
       if rte.rte<>nil then
          begin
            {for i:= 0 to rte.top do strdispose(rte.rte^[i].io);}
            FreeMem(rte.rte,(rte.top+1)*sizeof(TRTE_BOD))
          end;
       rte.top:= -1
     end;


{ odstrani priznak "U"pper
}
 function uni_RTE (kod: string): string;
    begin
      {kod:= l4str(kod);}
      kod:= cut_(kod);
      {$IFDEF URTE_ALLIAS}
       if (length(kod)>1) and (upcase(kod[1])=rte_UPPER) then kod:= copy(kod,2,length(kod)-1);
      {$ENDIF}
      uni_RTE:= kod
    end;


{ najde index R v poli trati RTE
}
 function _RTEind (kod: string; R: PRTEs; max: int): int;
    var   i: int;
    begin
      _RTEind:= -1;
      kod:= uni_RTE(kod);
      if kod<>'' then
         begin
           i:= 0; while (i<max) and (kod<>R^[i].kod) do inc(i);
           if (i>=max) and rte_ALLIAS then
              begin
                i:= 0; while (i<max) and (kod<>R^[i].kodp) do inc(i);
              end;
           if (i<max) then _RTEind:= i
         end
   end;

{ najde, ci bod lezi na trati...
}
 function _RTEbod_ind (bod: string; R: TRTE): int;
    var   i : int;
    begin
      {bod:= l4str(bod);}
      bod:= cut_(bod);
      i:= 0; while (i<=R.top) and (R.rte^[i].kod<>bod) do inc(i);
      if (i<=R.top) then _RTEbod_ind:= i else _RTEbod_ind:= -1
    end;

{  najde trat v poli vsetkych trati

function get_RTE(kod: string): PRTE;
   var   r: int;
   begin
     get_RTE:= nil;
     r:= get_RTEind(kod, RTE, RTEs);
     if r>=0 then get_RTE:= @RTE^[r]
     else begin
            r:= get_RTEind(kod, RTE_IO, RTEs_IO);
            if r>=0 then get_RTE:= @RTE_IO^[r]
          end
   end;

function get_BOD_RTEind(kodB,kodR: string; R: PRTEs; max: int): int;
   var   i: int;
   begin
     kodB:= uni_str(kodB);
     i:= get_RTEind(kodR, R,max);
     if i>=0 then get_BOD_RTEind:= _get_BOD_RTEind(kodB,R^[i])
     else get_BOD_RTEind:= -1
   end;
}
(*
function najblizsi_bod_pola(kod: string; _OB: PBODY; _OBs: int; dR: real): string;
   var   i     : int;
         B     : TOBxy;
         r1,r2 : real;
         k1,k2 : string;
   begin
     najblizsi_bod_pola:= '';
     if (_OB=nil) or (_OBs=0) or (not get_BOD_XY(kod, B)) then Exit;

     i:= 0; k1:= ''; r1:= dR+1; k2:= ''; r2:= 50000;
     while (i<_OBs) do
       begin
         r1:= vzdialenost(B.x,B.y,_OB^[i].x,_OB^[i].y);
         {$IFDEF DEBUG}
          if r1<=r2 then begin k2:= _OB^[i].kod; r2:= r1 end;
         {$ENDIF}
         if r1<=dR then begin k1:= _OB^[i].kod; dR:= r1 end;
         if r1=0 then break;
         inc(i)
       end;
     najblizsi_bod_pola:= k1
   end;
*)

{ vojenske trate
}
 function _is_RT(kod: string; var ind: int): bool;
    begin
      if ind<0 then ind:= _RTEind(kod, RTE_M, RTEs_M);
      _is_RT:= (ind>=0) and (copy(kod,1,length(hd_RT))=hd_RT)
    end;

 function _is_PT(kod: string; var ind: int; var let,tsa: string): bool;
    var   p: int;
    begin
      _is_PT:= false; let:= ''; tsa:= '';
      if ind<0 then ind:= _RTEind(kod, RTE_M, RTEs_M);
      if (ind>=0) and (copy(kod,1,length(hd_PT))=hd_PT) then
         begin
           let:= copy(kod,length(hd_PT)+1,kod_PTdep);
           while (let<>'') and (let[1]='0') do let:= copy(let,2,length(let)-1);
           let:= inschar(let,kod_APM,'0',1);
           tsa:= hd_TSA + copy(kod,length(hd_PT)+kod_PTdep+1,length(kod)-(length(hd_PT)+kod_PTdep));
           _is_PT:= true
         end;
    end;


{ znama trat ?
}
 function is_RTE(kod: string; var R: TRTE): bool;
    var   res: int;
    begin
      res:= _RTEind(kod, RTE, RTEs);
      if res>=0 then R:= RTE^[res]
      {else begin
             res:= _RTEind(kod,RTE_O, RTEs_O);
             if res>=0 then R:= RTE_O^[res]
           end};
      is_RTE:= res>=0
    end;
