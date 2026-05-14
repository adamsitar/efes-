(*-------------------------------------------------------------------*)
(* LETVIS FDP - ROUTER 3.0                                           *)
(* 1993,95                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_RTR.h}

{ Odporucanie, aby sprava nebola dlhsia ako 500 byte, pretoze
  pri prenose ROUTERom sa skrati okrem hlavicky o 4 byty
  (kod + cislo spravy) a o dalsie byty, ak sa rozosiela
  na viacero smerov naraz...

  Preto je protokol RTR vhodny len na prenos sprav kratsich
  ako 500 byte.


  [1]- Kodovanie sprav sieti RTR2 je nasledovne:
       0-100        ... systemove spravy
       100  ->10000 ... RDP kody
       20000->29999 ... FDP kody
       50000->      ... kody RDP<->FDP

}


unit RTR_def;


interface


    uses   TypeDef;


    const  ast_RLI       = $03;

           ast_RTR_CALL  = $A0;   { kod vyzvy od RTR    }
           ast_RTR_ACK   = $B0;   { kod odpovede ku RTR }

           ast_RTR_PKT   = $F0;   { cz }
           ast_CISCO_PKT = $F1;   { sk }
           ast_SIM_PKT   = $BE;

           ast_utcALas03 = $F2;


    const  rsprACK       =  03;
           rsprERR       =  04;
           rsprGID       =  05;
           rsprGIO       =  06;
           rsprLID       =  07;
           rsprLIO       =  08;
           rsprCAS       =  09;   { casova hlaska }

           rspr_SYS      = 198;   { systemova sprava od routera   }

           rspr_RTR      = 200;   { sprava typu RTR, RTI          }
           rspr_RTB1     = 201;   { sprava RBRIDGE s kodom adresy }
           rspr_RTB2     = 202;   { -//-   RBRIDGE s adresou      }
           rspr_RT_      = 203;   { sprava typu RTR od ineho pocitaca s jeho adresou }

          {$IFDEF UK}
           rspr_LONGoffs = 50;

           rspr_LRTR     = 250;   { dlha sprava typu RTR, RTI          }
           rspr_LRTB1    = 251;   { dlha sprava RBRIDGE s kodom adresy }
           rspr_LRTB2    = 252;   { dlha -//-   RBRIDGE s adresou      }
           rspr_LRT_     = 253;   { dlha sprava typu RTR od ineho pocitaca s jeho adresou }
          {$ELSE}
           rspr_LONGoffs = 20;

           rspr_LRTR     = 220;   { dlha sprava typu RTR, RTI          }
           rspr_LRTB1    = 221;   { dlha sprava RBRIDGE s kodom adresy }
           rspr_LRTB2    = 222;   { dlha -//-   RBRIDGE s adresou      }
           rspr_LRT_     = 223;   { dlha sprava typu RTR od ineho pocitaca s jeho adresou }
          {$ENDIF}

           rspr_FDP_lo   = 200;
           rspr_FDPL_lo  = 220;
           rspr_FDP_hi   = 250;


   const   set_rspr_FDP_L  = [rspr_LRTR,rspr_LRTB1,rspr_LRTB2,rspr_LRT_];

          { typ sprav spracovavanych UDP-CISCO protokolom
          } set_rspr_CISCO = [rspr_RTR, rspr_LRTR, rspr_RT_, rspr_LRT_];


   {$I net_def0.h}

   {$IFDEF RTR1}  {$I rtr.h}
   {$ELSE}        {$I rtr2.h}
   {$ENDIF}

   function is_in_RTRadr(adr: string {TNETadr}): TRTRadr;



implementation

function is_in_RTRadr(adr: string {TNETadr}): TRTRadr;
   var   adrr : TRTRadr;
         code : int;
         nd   : int;
   begin
    {$IFDEF RTR}
     val(adr, adrr, code);
     if not ((adrr>0) and (adrr<high(TRTRadr))) then adrr:= 0;
    {$ELSE}
     adrr:= 0;
    {$ENDIF}
     is_in_RTRadr:= adrr
   end;


{ function is_FDP_pkt(typ: word): bool;
    begin
      is_FDP_pkt:= inRange(typ,rspr_FDP_lo,rspr_FDP_hi) and (typ in set_rspr_udp)
                  ) then Exit;
    end;
}
end.