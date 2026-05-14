function is_proL (adr: TNETadr): bool;
   var   ind: int;
   begin
     ind:= is_NETadr(adr);
     is_proL:= (ind>-1) and (NODEs^[ind].desc.proL)
   end;


{ adresa:= wan_adr + lan_adr

    TCP      :
    X25      :  x25  + ipx   500  OPL
    RTR,RTRI :  meno + kod   77   UVS

}

function format_NETadr(adr: string): string;
   begin
     format_NETadr:= replchar(adr,odd_L4,repl_l4)
   end;


function NETadr({kod: word;} wan_adr,lan_adr: string): TNETadr;
   var   a: TNETadr;
   begin
     {
     if kod<>0 then
        begin
          str(kod:(sizeof(TRTRadr)*2),a);
          a:= '$'+a+odd_NETadr;
        end
     else a:= '';}
     a:= {a +} wan_adr+odd_NETadr+lan_adr;
     NETadr:= uni_str(a)
   end;


function NETadr_lan(adr: TNETadr): TNETadr;
   begin
     NETadr_lan:= getstr(adr,2,[odd_NETadr])
   end;

function NETadr_lan_(adr: TNETadr): TNETadr;
   begin
     if getstritems(adr,[odd_NET_ADR])>1 then NETadr_lan_:= getstr(adr,2,[odd_NETadr])
     else NETadr_lan_:= adr
   end;

function NETadr_wan(adr: TNETadr): TNETadr;
   begin
     NETadr_wan:= getstr(adr,1,[odd_NETadr])
   end;


{
  kontroluje, ci dana adresa je v NODEs
}
function is_NETadr(adr: TNETadr): int;
   var   i : int;
   begin
     adr:= uni_str(adr);
     i:= 0; while (i<NODEpoc) and (NODEs^[i].desc.adr<>adr) do inc(i);
     if (i>=NODEpoc) then i:= -1;
     is_NETadr:= i
   end;

{
  kontroluje, ci dana adresa je v NODEs
}
function is_NETname(var adr: TNETadr): int;
   var   i : int;
   begin
     adr:= uni_str(adr);
     i:= 0; while (i<NODEpoc) and (StrPas(NODEs^[i].desc.name)<>adr) do inc(i);
     if (i<NODEpoc) then adr:= NODEs^[i].desc.adr
     else i:= -1;
     is_NETname:= i
   end;

function is_NODEname(adr: TNETadr): string;
   var   i : int;
   begin
     i:= is_NETadr(adr);
     if i>-1 then is_NODEname:= strpas(NODEs^[i].desc.name)
     else is_NODEname:= adr
   end;

function is_NETnode(adr: TNETadr): int;
   var   nd : int;
   begin
     nd:= is_NETadr(adr);
     if nd=-1 then nd:= is_NETname(adr);
     is_NETnode:= nd
   end;


{
  vrati adresu pre protokol podla typu protokolu na smer _adr
}
function self_NETadr(adr: TNETadr): TNETadr;
   begin
     case NETprotocol(adr) of
       TCP                : self_NETadr:= '';
       RTR,RTI,RTU        : self_NETadr:= RTRaddress;
       COM                : self_NETadr:= COMaddress;
       else { i X25_LAN }   self_NETadr:= NETaddress
     end
   end;


function NETprotocol(adr: TNETadr): Tprotocol;
   var   nd : int;
   begin
     nd:= is_NETadr(adr);
     if (nd>-1) then NETprotocol:= NODEs^[nd].desc.pro
     else begin
           {$IFDEF RTR}
            if is_in_RTRadr(adr)>0 then NETprotocol:= RTR
             { IFDEF PCTCP    IFNDEF TRENAZER
             else if nm_prs_addr(adr)<>0 then NETprotocol:= RTU
              ENDIF    ENDIF}
            else
            {$ENDIF}
            if (adr<>'') then
               {$IFDEF PCTCP}
                 if adr=BROADCASTaddress then NETprotocol:= UDC
                 else if nm_prs_addr(adr)<>0 then NETprotocol:= UDC {UD_}
                 else
               {$ENDIF}
                      NETprotocol:= X25
            else NETprotocol:= no_pro
          end;
   end;


function NETtype(adr: TNETadr): Tnd_typ;
   var   nd: int;
   begin
     nd:= is_NETadr(adr);
     if nd>-1 then NETtype:= NODEs^[nd].desc.typ
     else NETtype:= no_typ
   end;


function NETrtr_adr(adr: TNETadr): TRTRadr;
   var   nd: int;
   begin
     nd:= is_NETadr(adr);
     if nd>-1 then NETrtr_adr:= NODEs^[nd].desc.adrr
     else NETrtr_adr:= 0
   end;
