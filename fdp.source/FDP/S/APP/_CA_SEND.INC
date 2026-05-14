{$IFNDEF CAMUS_OLDI}

 function  O_CAMUS._send_pkt(typ: byte; adr: string; data: pchars; size: word): bool;
     var   b    : pchars;
           p,pi : word;
           eop  : string;
           cl   : byte;
     begin
     (*
       if not (msOPLdata(typ) in [msHB,msAUP,msRTZ]) then eop:= ETX+check_sum(data,size)
       else eop:= '';
       p:= 1+1+size+length(eop)+1;  { SOH+typp+size+eop+EOT  }
       if p<=size then Exit;        { pretecenie }

       getmem(b,p);
       b^[0]:= SOH;
       if (msOPLdata(typ) in [msAUP,msRTZ]) then b^[1]:= QRY else b^[1]:= MES;
       move(data^,b^[2],size);           pi:= 2+size;
       move(eop[1],b^[pi],length(eop));  inc(pi,length(eop));
       b^[pi]:= EOT;
       SendCOMib(oplCOM, pbytes(b), p, false);
       if (msOPLdata(typ)<>msHB) or writeln_OPL_HeartBeat then
          begin
            writeln_pkt(b,p,arch_PKT_SEND,'',cl_s,false,false)
          end;
       freemem(b,p);
      *)
       _send_pkt:= false
     end;

 procedure O_CAMUS.send_data (adr: string; head,cislo,header_data: string;
                              data: pchars; size: word;
                              key: string; typ: TNETtyp
                             );
     begin
     end;

{$ENDIF}


{ Tohle je opis stavajiciho stavu

  10:17ú49 ùÿH@@@@A@(ESTPR/MI910-SAB267/A7131-...B-F150)
  10:17ú49   H@@@@A@(LAMMI/PR727ESTPR/MI910)

  V LAM by nemela byt identifikace zpravy (EST), mel by vypadat takto:

  10:17ú49   H@@@@A@(LAMMI/PR727PR/MI910)
}

function  O_CAMUS._lam_data(header: string): string;
   begin
     _lam_data:= copy(header,kod_HEAD+1,length(header)-kod_HEAD);
   end;
