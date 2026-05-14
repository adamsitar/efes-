(*-------------------------------------------------------------------*)
(* LETVIS FDP - NET 3.0                                              *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$I comp_NET.h}


unit NET_utc;


interface


     uses  TypeDef,
           Kody,
           NET_def, RTR_def;


     const  UTC_SYNCHRONIZE : bool = true;
            UTC_dt          : int  = 1;
            cfg_UTC_dt      = 'TIME';


     procedure internal_UTC;
     const  int_UTC: TProc = internal_UTC;

    { Fcie nepouzitelne v intr...
    }
     function  decode_rliUTC(data: pbytes; size: word): bool;
     function  decode_rtrUTC(data: pchars; size: word): bool;
     function  decode_netUTC(data: pchars; size: word): bool;

     procedure code_UTC(d: PDatum; var pkt: TNETpkt); far;


implementation

 uses  Crt, Dos, BIOS,
       utime, mem, io,
       ASTERIX;


 procedure internal_UTC;
     begin
       { predefinovana inde }
     end;


 function  synchronize_UTC_(var d: TDatum): bool;
     begin
       if      UTC_SYNCHRONIZE
          and  CheckTime(d.h,d.m,d.s)
          and  (UTC_dt < abs(TimeToSec(hour,min,sec)-TimeToSec(d.h,d.m,d.s))) then
               begin
                 novyDatum:= d;
                 nastavDatum:= true;
                 int_UTC;
                 synchronize_UTC_:= true
               end
       else synchronize_UTC_:= false
     end;


 function  synchronize_UTC(var d: TDatum): bool;
     begin
       if      UTC_SYNCHRONIZE
          and  CheckTime(d.h,d.m,d.s)
          and  CheckDate(d.rok,d.mes,d.den, false)
          and  (UTC_dt < abs(absTime-DTtoSec(d.rok,d.mes,d.den, d.h,d.m,d.s))) then
               begin
                 novyDatum:= d;
                 nastavDatum:= true;
                 int_UTC;
                 synchronize_UTC:= true
               end
       else synchronize_UTC:= false
     end;


 function  decode_rliUTC (data: pbytes; size: word): bool;
     var   d: TDatum;
           t: byte;
     begin
       decode_rliUTC:=
            _decode_asterixUTC(data,size, d.rok,d.mes,d.den, d.h,d.m,d.s,t)
        and synchronize_UTC_(d)
     end;


 function  decode_rtrUTC(data: pchars; size: word): bool;
     begin
       {if (rspr = rsprCAS) then} decode_rtrUTC:= decode_netUTC(data,size)
       {else decode_rtrUTC:= false};
     end;


 function  decode_netUTC(data: pchars; size: word): bool;
     var   p : pointer;
           d : TDatum;
     begin
       p:= data;
       move(p^,d.rok,sizeof(d.rok)); incptr(p,sizeof(d.rok));
       move(p^,d.mes,sizeof(d.mes)); incptr(p,sizeof(d.mes));
       move(p^,d.den,sizeof(d.den)); incptr(p,sizeof(d.den));
       move(p^,d.h,  sizeof(d.h));   incptr(p,sizeof(d.h));
       move(p^,d.m,  sizeof(d.m));   incptr(p,sizeof(d.m));
       move(p^,d.s,  sizeof(d.s));   incptr(p,sizeof(d.s));

       decode_netUTC:= synchronize_UTC(d)
     end;


 procedure code_UTC(d: PDatum; var pkt: TNETpkt);
     var   s: string; dlz: int;
     begin
       s:= ''; dlz:= 0;
       move(d^.rok,s[dlz+1],sizeof(d^.rok)); inc(dlz,sizeof(d^.rok));
       move(d^.mes,s[dlz+1],sizeof(d^.mes)); inc(dlz,sizeof(d^.mes));
       move(d^.den,s[dlz+1],sizeof(d^.den)); inc(dlz,sizeof(d^.den));
       move(d^.h,  s[dlz+1],sizeof(d^.h));   inc(dlz,sizeof(d^.h));
       move(d^.m,  s[dlz+1],sizeof(d^.m));   inc(dlz,sizeof(d^.m));
       move(d^.s,  s[dlz+1],sizeof(d^.s));   inc(dlz,sizeof(d^.s));
       s:= chr(dlz);

       new_NETpkt_data(@s[1],dlz, pkt.pkt)
     end;

begin
  UTC_dt:= read_cfg_word(SYSTEMcfg,cfg_UTC_dt, UTC_dt);
end.
