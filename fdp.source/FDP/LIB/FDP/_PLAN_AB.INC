function TPLAN.is_plan(p: pointer): bool;
   begin
     is_plan:= true
   end;


function TPLAN.sort: bool;
   begin
     sort:= false
   end;


function TPLAN.get_id(p: pointer): string;
   begin
     if (p_id<>nil) then get_id:= TSFunc_p(p_id)(p)
     else get_id:= ''
   end;

function TPLAN.get_key(p: pointer): string;
   begin
     if (p_codekey<>nil) then get_key:= TSFunc_p(p_codekey)(p)
     else get_key:= get_id(p)
   end;


function TPLAN.get_poz(p: pointer): Tpoz;
   var   zmena: bool;
   begin
     get_poz:= urc_platnost(p, zmena, false)
   end;


{$IFDEF NET}
  function TPLAN.get_rec(p: pointer): Pplan_rec;
     begin
       get_rec:= nil
     end;
{$ENDIF}



{ ----------------------------------------
   nastavenie priznakov spracovania planu
  ----------------------------------------
}

{ data su vkladane cez Add a vyberanie cez Del, preto nevolam ostatnie dristy z Add,
  ten nestastnik je definovany len kvoli zobrazeni na planzete
}
procedure TPLAN.set_cor(p: pointer; cor: int);
   begin
   end;

function  TPLAN.get_cor(p: pointer): int;
   begin
     get_cor:= -1;
   end;

procedure TPLAN.cl_cor(p: pointer);
    var   ind: int;
    begin
      {zmen_plan(p)}
      uloz(p);
      ind:= find(p); if ind<0 then Exit;
      set_cor(ap^[ind],0);
      vypis_plan(ind, false, false);
    end;


function  TPLAN.get_flag (p: pointer; group: byte): byte;
    begin
      get_flag:= 0
    end;

procedure TPLAN.set_flag (p: pointer; group,flag: byte);
    begin
    end;


function TPLAN.get_priznak (p: pointer): byte;
   begin
     get_priznak:= 0
   end;

procedure TPLAN.set_priznak (p: pointer; przn: byte; save: bool);
    begin
      if save then uloz(p)
    end;
