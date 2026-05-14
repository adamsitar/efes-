   type  TPolozka = record
           J: string{[3]};
           T: string{[4]};
           E: string{[5]};
           s: string{[20]};
         end;


   function JeToOna(P: Tpolozka; J,T: string): bool;
      begin
        if (P.J=J) and (P.T=T) then JeToOna:= true
        else JeToOna:= false
      end; { JeToOna }


   function get_nextstr(const mess_: TASTA_PRNpacket; var ii,_1,_2: int): string;
      var   s: string;
            i: integer;
      label loop;
      begin
        loop: Inc(ii);
              while
                (mess_.t>ii) and (not(mess_.b[ii] in['^']))
              do inc(ii);
              {Inc(_pos);
              if pos=_pos+1 then _1:= ii;
              if pos<>_pos then goto loop;}
        _2:= ii-1;
        s:= ''; for i:= _1 to _2 do if not(ord(mess_.b[i]) in Skip) then s:= s+mess_.b[i];
        _1:= _2 + 2;
        get_nextstr:= s
      end; { get_nextstr }


   procedure get_nextitem(var P: TPolozka; const mess_: TASTA_PRNpacket; var ii,_1,_2: int);
       var   s: string;
       begin
         P.J:= get_nextstr(mess_, ii,_1,_2);
         P.T:= get_nextstr(mess_, ii,_1,_2);
         s  := get_nextstr(mess_, ii,_1,_2);
         P.E:= Copy(s,1,5);
         P.s:= Copy(s,6,Length(s)-5)
       end;


   procedure get_nextNDB(var B: TOB; J,T: string;
                         var P: TPolozka; const mess_: TASTA_PRNpacket;
                         var ii,_1,_2: int
                        );
       var   s   : string;
             err : integer;
       begin
         if JeToOna(P,J,T) then with B do
            begin
              kod:= P.s;
              get_nextitem(P, mess_, ii,_1,_2);
              Val(Copy(P.s,1,2),h{p},err);
              Val(Copy(P.s,3,2),m{p},err);
              vys := 0; vysab:= ' ';
              {h:= hp; m:= mp;}
              get_nextitem(P, mess_, ii,_1,_2)
            end
       end; { get_nextNDB }



   function dobre_data(const mess_: TASTA_PRNpacket): bool;
      var   _ulp,_rmk : bool;
            s : string;
            i : int;
      begin
        _ulp:= false; _rmk:= false;
        for i:= 0 to mess_.t-2 do
            begin
              s:= mess_.b[i]+mess_.b[i+1]+mess_.b[i+2];
              if s='ULP' then _ulp:= true;
              if s='RMK' then _rmk:= true;
              if _ulp and _rmk then
                 begin
                   dobre_data:= false;
                   exit
                 end;
            end;
        dobre_data:= true
      end;


  {^A^T011^J10^L010690001^T021^J10^L040410001^T032
    ^J10^L040690001^T001^J04^L040010217^T057
    ^J08^L210010155^J08^T045^L000430001^J10^T057^L000700001

    ^J03^T002^E0201OEFDM                                 idn
    ^J06^T002^E0101LOWW^J06^T006^E01010615               ETD
    ^J08^T002^E0101EPWA^J08^T006^E01010735               ETA
    ^J09^T070^E0201A7307                                 ssr0
    ^J03^T013^E0201A4410                                 ssr
    ^J06^T013^E0101S^J06^T014^E02010455                  vys (S0455)
    ^J08^T013^E0101S^J08^T014^E02010030^J08^T019^E0101A  vys1
    ^J03^T020^E01010630                                  rych
    ^J03^T026^E0101C501                                  typ
    ^J03^T034^E0101OKR^J03^T040^E01010651                trat
    ^J05^T034^E0101SWCN^J05^T040^E01010656
    ^J07^T034^E0101ABKOL^J07^T040^E01010704
    ^J09^T034^E0101JAB^J09^T040^E01010711
    ^J05^T059^E0101100 200 300 500
    ^J07^T059^E0101U  1  S^J09^T059^E0101-  *  *
    ^J02^T059^E0101200696 0640
    ^J02^T076^E010174                                    ssn
    ^J03^T065^E0201A7307                                 ssr0
    ^J06^T023^E0101S^J06^T024^E02010885                  vys3
    ^,
    ^X
  }
   function decode_ASTA_PRN(const mess_: TASTA_PRNpacket; var FPL: DcFPL; var msg: string): bool;
      var   s,s1,v_ : string;
            i,j,err : int;
            next    : bool;
            mm,dd, cislo: word;
            ii, pos, _pos, _1,_2, v : int;
            P : TPolozka;
            b : byte;

      begin
         decode_ASTA_PRN:= false; msg:= 'ASTA DECODE ERROR... ';
         {if not dobre_data(mess_) then Exit;}
         FillChar(FPL,sizeof(FPL),0);

         _1:= 2; _2:= 2; ii:= 1; { pos := 0; _pos:= 0; }
         with FPL do
             begin
             { konverzia formatu stripu --------------------------- }
               stt:= hd_EST; {fpl_EST;}
             { -------------------------- }
               s:= get_nextstr(mess_, ii,_1,_2);
               i:= 0; while (i<=20) and (s<>'L000700001') do
                 begin
                   s:= get_nextstr(mess_, ii,_1,_2);
                   inc(i)
                 end;
             { -------------------------- }
               get_nextitem(P,mess_, ii,_1,_2);
               if JeToOna(P,'J03','T002') then
                  begin
                    idn:= P.s;
                    get_nextitem(P,mess_, ii,_1,_2)
                  end
               else Exit;
               if JeToOna(P,'J06','T002') then
                  begin
                    start.kod:= P.s;
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J06','T006') then
                  begin
                    with start do
                      begin
                        Val(Copy(P.s,1,2),h,err);
                        Val(Copy(P.s,3,2),m,err);
                        start_.h:= h; start_.m:= m
                      end;
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J08','T002') then
                  begin
                    prist.kod:= P.s;
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J08','T006') then
                  begin
                    with prist do begin
                      Val(Copy(P.s,1,2),h,err);
                      Val(Copy(P.s,3,2),m,err);
                    end;
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
              {$IFDEF BLAVA}
               if JeToOna(P,'J09','T070') then
                  begin
                    ssr0:= Copy(P.s,2,4);
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
              {$ENDIF}
               if JeToOna(P,'J03','T013') then
                  begin
                    s1:= P.s;
                    ssr:= Copy(P.s,2,4);
                    get_nextitem(P,mess_, ii,_1,_2);
                    if (system.pos('ULP',s1)<>0) or (system.pos('ULP',P.s)<>0) then
                       begin
                         msg:= 'ULP IS NOT PROCESSED.';
                         Exit
                       end;
                  end;
               if JeToOna(P,'J06','T013') then get_nextitem(P,mess_, ii,_1,_2);
               if JeToOna(P,'J06','T014') then
                  begin
                    Val(P.s,vys,err);
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J06','T019') then
                  begin
                    b{vys_a}:= ord(getcharu(P.s[1]));
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J08','T013') then get_nextitem(P,mess_, ii,_1,_2);
               if JeToOna(P,'J08','T014') then
                  begin
                    Val(P.s,vys1,err);
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J08','T019') then
                  begin
                    vys1_a:= getcharu(P.s[1]);
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J03','T020') then
                  begin
                    Val(P.s,rych,err); rych_:= 'K';
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               if JeToOna(P,'J03','T026') then
                  begin
                    typ:= P.s;
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;
               get_nextNDB(Trat[0],'J03','T034', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[1],'J05','T034', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[2],'J07','T034', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[3],'J09','T034', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[4],'J03','T046', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[5],'J05','T046', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[6],'J07','T046', P,mess_, ii,_1,_2);
               get_nextNDB(Trat[7],'J09','T046', P,mess_, ii,_1,_2);

              {$IFDEF PRAHA}
               if JeToOna(P,'J03','T065') then
                  begin
                    ssr0:= DelChar(P.s,['A'])
                  end;
              {$ENDIF}

               get_nextitem(P,mess_, ii,_1,_2); { 07 59 - U 1 S       }
               get_nextitem(P,mess_, ii,_1,_2); { 09 59 - * N -       }

              {$IFDEF BLAVA}
               get_nextitem(P,mess_, ii,_1,_2);

               if JeToOna(P,'J02','T059') then  { 090496 0836 }
                  begin
                   { datum a cas odoslania podla ASTA
                    GetDateStr(date.r,date.m,date.d, getstr(P.s,1,set_),false);
                   }
                    {GetTimeStr(time.h,time.m,b, getstr(P.s,2,set_));}
                    get_nextitem(P,mess_, ii,_1,_2);
                  end;

               if JeToOna(P,'J02','T076') then  { 52 }
                  begin
                    val(P.s,cislo,v);
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;

               if JeToOna(P,'J03','T065') then
                  begin
                    ssr0:= DelChar(P.s,['A']);
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;

               if JeToOna(P,'J06','T023') then
                  begin
                    get_nextitem(P,mess_, ii,_1,_2)
                  end;

               if JeToOna(P,'J06','T024') then
                  begin
                    Val(P.s,v,err);
                    if err=0 then
                       begin
                         vys1:= vys; {vys1_a:= vys_a;}
                         vys := v;   {vys_a:= ' ';}
                         {
                         for i:= 0 to c_max_bod-1 do with Trat[i] do
                             begin
                               Trat[i].vys := v;
                               Trat[i].vys_:= v_[1]
                             end
                         }
                       end
                  end;
              {$ENDIF}

               {init_time(time, BIOS.hour,BIOS.min,BIOS.sec);}
               if date.r=0 then
                  begin
                    {with date do
                       if GetDateStr (r,m,d, GetStr(P.s,1,set_)) then
                       else} init_date(date,BIOS.year,BIOS.month,BIOS.day)
                  end;

               { neprisiel plan pred polnocou na zajtra ?
               }
               {if     ((hour>=22))
                  and ((trat[0].kod<>'') and (trat[0].h<=1))
                  and ((date.d=day) and (date.m=month))
                      then NextDate(date.r,date.m,date.d);}
               datum_cFPL(FPL);
             end;

        {$IFDEF ASTA_FDP_ACK}
         ???
         cislo:= GetInt(s,1,setPism+['/']);
         { ---------------------------------------------------- }
         { Vyslanie potvrdenia ku ASTE ...                      }
         {   (ESTPR/MI024-CSA124/5213- ...                      }
         {   (LAMMI/PR012PR/MI024)                              }
         { .................................................... }
         s1:= Copy(s,4,2);
         SendCOMi_str(comASTA,'(LAMMI/'+s1+IntToStr(topACC+2,3,true)+s1+'/'+GetStr(s,2,['/'])+')',Main0);
        {$ENDIF}

         format_cFPL(@FPL);
         oprava_casu_pristatia_cFPL(@FPL);
         if FPLC_ARR then pristatie_cFPL(@FPL);

         decode_ASTA_PRN:= true
      end;

