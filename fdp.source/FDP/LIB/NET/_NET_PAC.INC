{ Datove pakety <spr_DATAlo,spr_DATAhi> musia byt ukoncene
  znakom KON_SPR, to mi signalizuje, ze sa nist nestraciuo
}
function TNET.is_correct_pkt(const pkt: TNETpkt): bool;
   begin
    {if     (not is_ack_pkt(pkt))
        and (pkt^.head.dlz > 1)
        and (pkt^.head.typ >= spr_DATAlo)
        and (pkt^.head.typ <= spr_DATAhi)
            then is_correct_pkt:=     (pkt^.data[0]              =ord(ZAC_SPR))
                                  and (pkt^.data[pkt^.head.dlz-1]=ord(KON_SPR))
     else} is_correct_pkt:= true
   end;


{ urcuje, ci pkt zaradi do TNETack sa bude potvrdzovat
}
function TNET.is_data_to_ack(const pkt: TNETpkt{; received: bool}): bool;
   begin
     is_data_to_ack:=     (not is_ack_pkt(pkt))
                      and ( (pkt.head.typ>=spr_MESlo)
                            {$IFDEF DATA_BIN} or (pkt.head.typ>=spr0_SPR) {$ENDIF}
                          )
                      {and (pkt.head.typ<spr_SIMlo)}
   end;


{ urcuje, ci pkt zaradi do TNETack sa bude potvrdzovat

function TNET.is_previous_pkt(const pkt: TNETpkt): bool;
   var   res: string;
   begin
     res:=  (pkt.head.poc=0) or is ind

     - NETpkt_id - -> NETack  alebo opacne

     - zaradenie i/m do takeho radu, v kluci je nazov subora,
       ulozeny v .\tmp, po dokonceni sa skopiruje do prislusneho adresara
       alebo spracuje ako datovy paket

     - musi si odpamatat posledny prijaty a prijaty ho nahradzuje...
       ak je, potom... is_previous


     is_data_to_ack:= res
   end;
}