{$I comp.h}

{$IFDEF IPX}
  {$R-,O-}
  {$C FIXED PRELOAD PERMANENT}
{$ENDIF}


unit FDP_NETB;


interface


    uses  TypeDef, NET_def;



implementation

uses  BIOS,
      {$IFDEF IPX} IPX_def, _IPX, {$ENDIF}
      ASTERIX, NET_utc;


{$IFDEF CAS_RLI} {$IFDEF IPX} {$IFDEF BROADCAST}

function  decode_asterixUTC (data: pbytes; size: word): bool;
    var   d: TDatum;
          t: byte;
    begin
      decode_asterixUTC:= false;

      if not _decode_asterixUTC(data,size, d.rok,d.mes,d.den, d.h,d.m,d.s,t) then Exit;

      {$IFDEF IPX}
        if d.s>sec then t:= d.s-sec else t:= sec-d.s;
        if (t>dT) or (d.m<>min) or (d.h<>hour) then
      {$ELSE}
        if CheckTime(hour_,min_,sec_) and (dT<abs(absTime-DTtoSec(day,month,day, hour_,min_,sec_))) then
      {$ENDIF}
           begin
             novyDatum:= d;
             nastavDatum:= true;
             decode_asterixUTC:= true
           end
    end;


function isIPXbroadcast(bf: PNETBpkt): bool; far;
   begin
     isIPXbroadcast:= false;
     decode_asterixUTC (@bf^.data,bf^.size)
   end;

begin
  _IPX.isIPXbroadcast:= @isIPXbroadcast
{$ENDIF} {$ENDIF} {$ENDIF}

end.
