{ ---------------------------------------------------------------
  EXT
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתתתתתתתתתתתת
  (c) ALES 1996,7 Kosice,
 תתתתתתתתתתתתתתתתתתתתתתתתת
}

{$DEFINE EXTERNAL_NET}
{$IFNDEF EXTERNAL_ASYNC}
 {$X+,I-,S-,P-,F+,O-}
 {$C FIXED PRELOAD PERMANENT}
{$ENDIF}


{$I comp.h}


unit _EXT_def;


interface


    uses   TypeDef,
           Coms, Arrays, Objects;


    const  cfg_POWER          = 'POWER';
           cfg_PKT_SIZE       = 'PKT_SIZE';
           cfg_REC_BUF_SIZE   = 'REC_BUF_SIZE';


           EXT_pkt_size_lo    =  512;
           EXT_pkt_size_hi    = 4096;
           EXT_pkt_size       = 1024;

           _EXT_EN : bool     = false;
           EXT_ENABLED : bool = false;


    const  icao_ERR_DISPLAY : bool = false;        { Zobraz/indikuj chybu spracovania FPL }
           icao_ERR_SYNCHR  : bool = false;        { Ak sa paket vyhodnoti ako chybny, jeho synhronizacia s dalsim AFTN }

           icao_HEAD_ERR     : bool = true;        { zakazane pakety (hlavicky) zobrazi ako chybu }
           icao_HEAD_ERR_TLG : bool = true;        { -//- ako TLG                                  }

           {icao_UNKN_ERR   : bool = true;           nezname pakety (hlavicky) zobrazi ako chybu  }
           {icao_LAM_UNKN_DIS                        potvrdzovat nezname/nepovolene pakety ? }

           icao_REC_UPDATED : bool = {$IFDEF DEBUG} true {$ELSE} true {$ENDIF};


    type   PO_EXT_ibuff = ^O_EXT_ibuff;
           O_EXT_ibuff  = object(TObject)

            { PREMENNE PRE SPRACOVANIE SPRAV EXT }

             p_power   : pbool;
             power     : bool;

            { cfg
            }
             cfg_FN : string;

            { linka
            }
             async : bool;

             asyncCOM, asyncBITs, asyncSTOP_BITs : byte;
             asyncMODE   : word;
             asyncPARITY : PARITY;

            { buffery
            }
             ipkt_size,
             ibuff_size    : word;
             ipkt,rpkt     : pointer;
             ibuff         : PBuffer;
             is_ibuff0     : bool;           { ak ma buffer dynamicku velkost, LEN AK DATA NENACITAVAM V INTR }


             constructor  Init(_Owner   : PObject;
                               _p_power : pbool;
                               _cfg_FN  : string;

                               _async : bool;

                               _ipkt_size, _ibuff_size: word;
                               _is_ibuff0: bool
                              );

             destructor   Done; virtual;

             function     read_cfg(_cfg_FN: string): bool; virtual;

             procedure    save_pkt  (pkt: pointer);
             procedure    save_pkt0 (data: pchars; size: word);
           end;

           PP_EXT_ibuff = ^PO_EXT_ibuff;


implementation

uses  dos, bios, mem, utime, mess, math, str0, keyb, sets, msg;


 constructor O_EXT_ibuff.Init (_Owner   : PObject;
                               _p_power : pbool;
                               _cfg_FN  : string;

                               _async : bool;

                               _ipkt_size, _ibuff_size: word;
                               _is_ibuff0: bool
                              );

       var   s: string; c: int; r: single;

       begin
         inherited Init(_Owner);

         p_power  := _p_power;
         if (p_power<>nil) and (p_power^<>power) then power:= p_power^
         else power:= true;

         ipkt:= nil; ibuff:= nil;
         ipkt_size:= _ipkt_size; ibuff_size:= _ibuff_size;
         is_ibuff0:= _is_ibuff0;

         async          := _async;
         asyncCOM       := 2;
         asyncMODE      := 19200;
         asyncBITs      := 8;
         asyncSTOP_BITs := 0;
         asyncPARITY    := NONE;

         cfg_FN:= _cfg_FN;
         read_cfg(cfg_FN); { NEMENIT PORADIE, PRETOZE CFG MOZE UPRAVIT VELKOST PAKETU }

        { vstupny buffer
        }
         rpkt:= nil;
         GetMem(ipkt,ipkt_size); FillChar(ipkt^,ipkt_size,0);
         ibuff:= nil;
         if _ibuff_size<>0 then
            if is_ibuff0 then ibuff:= New(PBuffer0,Init(ibuff_size))
            else begin
                   ibuff:= New(PBuffer,Init(ibuff_size,ipkt_size, false));
                   GetMem(rpkt,ipkt_size); FillChar(rpkt^,ipkt_size,0);
                 end;
       end;


 destructor O_EXT_ibuff.Done;
      begin
        inherited Done;
        if rpkt <>nil then begin FreeMem(rpkt,ipkt_size); rpkt:= nil end;
        if ibuff<>nil then begin Dispose(ibuff,Done); ibuff:= nil end;
        if ipkt <>nil then begin FreeMem(ipkt,ipkt_size); ipkt:= nil end;
      end;


 function O_EXT_ibuff.read_cfg(_cfg_FN: string): bool;
    begin
      read_cfg:= true
    end;


 procedure O_EXT_ibuff.save_pkt(pkt: pointer);
     begin
       if (ibuff=nil) or (pkt=nil) then Exit;

       ibuff^.save(pkt)
     end;

 procedure O_EXT_ibuff.save_pkt0(data: pchars; size: word);
     begin
       if (ipkt=nil) or (ibuff=nil) then Exit;

       size:= minimum(size,N(ipkt_size-1));
       move(data^,ipkt^,size);
       pbytes(ipkt)^[size]:= 0;
       ibuff^.save(ipkt)
     end;

end.