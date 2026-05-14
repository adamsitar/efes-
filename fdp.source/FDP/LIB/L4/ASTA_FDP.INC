   function get_nextstr_FDP(const mess_: TASTA_FDPpacket; var ii,_1,_2: int): string;
      const Skip : Set of byte = [];
      var   s: string;
            i: int;
      label loop;
      begin
        s:= '';
        loop: Inc(ii);
              while
                (mess_.t>ii) and (not(mess_.b[ii] in['-',' ',')','']))
              do Inc(ii);
              {Inc(_pos);if pos=_pos+1 then _1:= ii; if pos<>_pos then goto loop;}
        _2:= ii-1;
        for i:= _1 to _2 do
            if not(ord(mess_.b[i]) in Skip) then s:= s + mess_.b[i];
        _1:= _2 + 2;
        get_nextstr_FDP:= s
      end; { get_nextstr_FDP }


   procedure get_nextNDB_FDP(var bod: TOB; const mess: TASTA_FDPpacket; var ii,_1,_2: int; typ_vys: char);
       var   s   : string;
             err : int;
       begin
         s:= get_nextstr_FDP(mess, ii,_1,_2);
         with bod do
            begin
              kod  := GetStr(s,1,['/']);
              vys  := get_altM (typ_vys, GetInt(s,2,['/'])) div m_S;
              vysab:= ' ';
              s:= GetStr(s,3,['/']);
              Val(Copy(s,1,2),h{p},err);
              Val(Copy(s,3,2),m{p},err);
              {h:= hp; m:= mp}
            end
       end; { get_nextNDB_FDP }


   function decode_ASTA_FDP(const mess: TASTA_FDPpacket; var FPL: DcFPL): bool;
      var   s,s1,ack: string;
            i, ii,j, _1,_2: int;  { vypoctove premenne }
            typ_vys : char;
            mm,dd   : word;
      begin
         decode_ASTA_FDP:= false;

         _1:= 2; _2:= 2; ii:= 1; { pos := 0; _pos:= 0; }
         FillChar(FPL,sizeof(DcFPL),0);

         ack:= get_nextstr_FDP(mess, ii, _1,_2);
         with FPL do
           begin
             stt := copy(ack,1,kod_HEAD);

            { -------------------------- }
              s  := get_nextstr_FDP(mess, ii, _1,_2);
              idn:= GetStr(s,1,['/']);
              ssr:= GetStr(s,2,['/']);

              if (stt<>hd_EST) and (stt<>hd_CPL) then Exit;

            { -------------------------- }
              typ:= get_nextstr_FDP(mess, ii, _1,_2);
            { -------------------------- }
              with start do
                begin
                  kod:= get_nextstr_FDP(mess, ii, _1,_2);
                  h := 0; m := 0;
                  start_.h:= h; start_.m:= m
                end;
            { -------------------------- }
              if stt=fpl_EST then
                 begin
                  { nevyuzivam celu informaciu - vstupny bod pri EST }
                   s:= GetStr (get_nextstr_FDP(mess, ii, _1,_2),2,['/']);
                   s:= copy(s,5,length(s)-4); { - cas }

                  { vys1 }
                   s1:= s[1];
                   i:= 2; while (i<=length(s)) and (not (s[i] in set_alt)) do
                     begin
                       s1:= s1+s[i];
                       inc(i)
                     end;
                   vys1:= get_altM(s1[1], GetInt(s1,1,setPism)) div m_S;
                   if s1[length(s1)] in set_alt_ then vys1_a:= s1[length(s1)];

                  { vys  }
                   s1:= copy(s,length(s1)+1,length(s)-length(s1)+1);
                   vys:= get_altM(s1[1], GetInt(s1,1,setPism)) div m_S;
                   {if s1[length(s1)] in set_alt_ then vys_a:= s1[length(s1)];}
                   if vys=0 then vys:= vys1;
                 end;

            { -------------------------- }
              s:= get_nextstr_FDP(mess, ii, _1,_2);
              rych_:= s[1];
              rych := GetInt(s,1,setPism);

              j:= 2; while (s[j] in setCisl) and (j<=length(s)) do inc(j);
              s1:= copy(s,j,length(s)-j+1);
              typ_vys:= s1[1];
              vys:= get_altM(typ_vys, GetInt(s1,1,setPism)) div m_S;
              {if s1[length(s1)] in set_alt_ then vys_a:= s1[length(s1)];}

            { -------------------------- }
              with prist do
                begin
                  kod:= get_nextstr_FDP(mess, ii, _1,_2);
                  h := 0; m := 0;
                end;
            { -------------------------- }
              for i:= 0 to strip_max_bod-1 do get_nextNDB_FDP(trat[i], mess, ii, _1,_2, typ_vys);
            { -------------------------- }

              eet.h  := BIOS.hour;
              eet.m  := BIOS.min;
              eet.s  := BIOS.sec;

            { neprisiel plan pred polnocou na zajtra ?
            }
              init_date(date,BIOS.year,BIOS.month,BIOS.day);
              {if     ((hour>=22))
                 and ((trat[0].kod<>'') and (trat[0].h<=1))
                 and ((date.d=BIOS.day) and (date.m=BIOS.month))
                     then NextDate(date.r,date.m,date.d);}
              datum_cFPL(FPL);
            end;

        {$IFDEF ASTA_FDP_ACK}
         cislo:= GetInt(ack,1,setPism+['/']);
         { ---------------------------------------------------- }
         { Vyslanie potvrdenia ku ASTE ...                      }
         {   (ESTPR/MI024-CSA124/5213- ...                      }
         {   (LAMMI/PR012PR/MI024)                              }
         { .................................................... }
         s1:= Copy(ack,4,2);
         SendCOMi_str(comASTA,'(LAMMI/'+s1+IntToStr(topACC+2,3,true)+s1+'/'+GetStr(s,2,['/'])+')',Main0);
        {$ENDIF}

         { Pretoze casy startov a pristatia nechodia korektne, prepocet... }

         format_cFPL(@FPL);
         oprava_casu_pristatia_cFPL(@FPL);
         if FPLC_ARR then pristatie_cFPL(@FPL);

         decode_ASTA_FDP:= true
      end;
