function isX25adr(adr: TX25name; svc: byte): int;
   begin
     if X25nodes<>nil then isX25adr:= X25nodes^.isX25adr(adr,svc)
     else isX25adr:= -1
   end; { isX25adr }

function isX25name(var name: TX25name): int;
   begin
     if X25nodes<>nil then isX25name:= X25nodes^.isX25name(name)
     else isX25name:= -1
   end; { isX25name }

function isX25chan(chan: U16BIT; svc: byte): int;
   begin
     if X25nodes<>nil then isX25chan:= X25nodes^.isX25chan(chan,svc)
     else isX25chan:= -1
   end; { isX25chan }


{ Hlada, ci "adr" je adresa tohto uzla X25 podla logickej/fyzickej adresy...
}
function is_this_X25node(adr: TX25name): bool;
   var   r : bool;
         i : int;
   begin
     adr:= uni_str(NETadr_wan(adr));
     r:=  (adr=X25address) or (adr=NETadr_wan(NETaddress));  { nazov uzla ? (napr. 100,100) }
     if not r then
        begin
          i:= isX25name(adr);
          if (i>-1) and (X25node>-1) then
             r:= X25nodes^.NODE^[i]^.ADR = X25nodes^.NODE^[X25node]^.ADR {  adresa ? ( napr #105,#105) }
         end;
     is_this_X25node:= r
   end;

{ funkcia zisti z glob.premennej podla zadanej adresy cislo kanalu
  ako vyst.hodnotu vracia hodnotu open
}
function is_open_X25channel(adr: TX25name; var CHAN: S16BIT): bool;
   var   i : int;
   begin
     i:= isX25adr(adr,0);
     if i>=0 then
        begin
          CHAN:= X25nodes^.NODE^[i]^.CHAN;
          is_open_X25channel:= X25nodes^.NODE^[i]^.OPEN
        end
     else begin
            CHAN:= 0;                     { <>'97 }
            is_open_X25channel:= false
          end;
   end; { is_open_X25channel }


{$IFDEF _X25}

  { funkcia nastavi v globalnej premennej podla zadanej adresy
    cislo kanala a premennu open = TRUE
  }
  function set_chan(adr: TX25name; CHAN: S16BIT): bool;
     var   i : int;
     begin
       i:= isX25adr(adr,0);
       if i>=0 then X25nodes^.NODE^[i]^.CHAN:= CHAN;
       set_chan:= i>=0
     end; { set_chan }


  { funkcia nastavi v globalnej premennej podla zadanej adresy
    cislo kanalu a premennu open = TRUE
  }
  function set_open(adr: TX25name; CHAN: S16BIT): bool;
     var   i : int;
     begin
       i:= isX25adr(adr,0);
       if i>=0 then
          begin
            X25nodes^.NODE^[i]^.CHAN:= CHAN;
            X25nodes^.NODE^[i]^.OPEN:= true
          end;
       set_open:= i>=0
     end; { set_open }


  { funkcia znuluje v glob. premennej podla zadanej adresy cislo kanalu
    a premennu open na FALSE
  }
  function set_not_open(var adr: TX25name): bool;
     var   i : int;
     begin
       i:= isX25adr(adr,0);
       if i>=0 then
          begin
            X25nodes^.NODE^[i]^.CHAN:= 0;
            X25nodes^.NODE^[i]^.OPEN:= false
          end;
       set_not_open:= i>=0
     end; { set_not_open }

{$ENDIF}