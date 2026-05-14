{$IFDEF TRENAZER_IPX}

  procedure get_trenazer_pos(adr: byte);
      var   i : int;
      begin
        for i:= 0 to max_TRENAZER_POS-1 do TRENAZER_POSs[i]:= (adr and ( 1 shl i )) <> 0
      end;

  function get_trenazer_adr: byte;
     var   adr : byte;
           i : int;
     begin
       adr:= 0;
       for i:= 0 to max_TRENAZER_POS-1 do adr:= adr or ( ord(TRENAZER_POSs[i]) shl i );
       get_trenazer_adr:= adr
     end;


  const trn_STRIP = $d0;

        trn_TIME  = $d1;
        trn_STOP  = $d2;
        trn_SET   = $d3;


  type  TIdentMask = record
           code: byte;  { priznak PSP-paketu - vzdy nastaveny na 0xA0 }
           mask: word;  { maska zdrojovej stanice }
        end;

  type  TMatoCas = record
           r: int; e,d, h,m,s: byte;
        end;


  function is_IPXBpacket(packet: PNETBpacket): bool;
     var   IdentMask: TIdentMask;
           res,is: bool;
           i: int;
     begin
       move(packet^.data,IdentMask,sizeof(IdentMask));
       res:= IdentMask.code=$A0;
       i:= 0; is:= false;
       while (i<max_TRENAZER_POS) do
         begin
           is:= is or (TRENAZER_POSs[i] and (IdentMask.mask and (1 shl i) <>0));
           inc(i)
         end;
     { is_IPXBpacket:= ... and ((IdentMask.mask and (1 shl TRENAZER_ADR))<>0) }
       is_IPXBpacket:= res and is
     end;


  procedure receive_TIMEpkt(packet: PNETBpacket);
      var   m: TMatoCas;
      begin
        Move(packet^.data[4],m,sizeof(TMatoCas));
        SetDatem(m.r,m.e,m.d);
        SetTimem(m.h,m.m,m.s)
      end;


  function get_word(s: string; pos: int): word;
     var   w: word;
     begin
       s:= copy(s,pos,2);
       w:= ord(s[2]) shl 8 + ord(s[1]);
       get_word:= w
     end;

  function get_byte(s: string; pos: int): word;
     var   b: byte;
     begin
       s:= copy(s,pos,2);
       b:= byte(s[1]);
       get_byte:= b
     end;


  procedure receive_FPLpkt(packet: PNETBpacket);
      var   strip  : string;
            FPL1   : DcFPL;
            FPL2   : DmFPL;
            p,i,_1 : int;
            kod1,kod2 : string;
            vys_   : char;
      begin
        {lan_done;}

        strip[0]:= chr(Minimum(packet^.size-4,sizeof(strip)-1));
        Move(packet^.data[4],strip[1],ord(strip[0]));
        fillchar(FPL1,sizeof(FPL1),0);
        fillchar(FPL2,sizeof(FPL2),0);

        case upcase(strip[1]) of

          'C': with FPL1 do
                 begin
                   est_:= fpl_EST;
                   idn := copy(strip,2,10);
                   p   := get_word(strip,12);
                   str(p,ssr);
                   p   := get_word(strip,14);
                   if p=0 then ssr0:= '' else str(p,ssr0);
                   typ := copy(strip,16,4);

                   start.kod := copy(strip,20,4);
                   start.h := get_byte(strip,24); start_.h:= start.h;
                   start.m := get_byte(strip,25); start_.m:= start.m;

                   prist.kod:= copy(strip,26,4);
                   prist.h := get_byte(strip,30);
                   prist.m := get_byte(strip,31);

                   vys   := get_word(strip,32);
                   vys_  := vysOB; {getchar(copy(strip,34,1));}
                   vys1  := get_word(strip,35);
                   vys1_a:= getchar(copy(strip,37,1));

                   rych := get_word(strip,38);
                   rych_:= getchar(copy(strip,40,1));

                 { Mato mi posle prvy bod na trati ako letisko startu,
                   i ked je to len otocny bod. To iste plati
                   i pre letisko pristatia
                 }
                   if _OBind(start.kod, LK, LKs)>=0 then _1:= 0
                   else begin
                          _1:= 1;
                          i:= 0; while (i<OBs) and (pos(start.kod,OB^[i].kod)=0) do inc(i);
                          if (i<OBs) then trat[0].kod:= OB^[i].kod
                          else trat[0].kod:= start.kod;
                          start.kod:= '';

                          trat[0].h   := start.h;
                          trat[0].m   := start.m;
                          trat[0].vys := vys;
                          {trat[0].vys_:= vys_}
                        end;

                   p:= get_byte(strip,41);
                   bodov:= _1;
                   i:= 0;
                   while (i<p) and (bodov<strip_max_bod) do
                     with trat[_1+i] do
                       begin
                         kod := cut_(copy(strip,42+i*10,5));
                         h   := get_byte(strip,47+i*10);
                         m   := get_byte(strip,48+i*10);
                         vys := get_word(strip,49+i*10);
                         vys_:= getchar(copy(strip,51+i*10,1));

                         inc(i);
                         inc(bodov)
                       end;

                   if _OBind(prist.kod, LK, LKs)<0 then
                      begin
                        if (bodov<strip_max_bod-1) then
                           begin
                             i:= 0; while (i<OBs) and (pos(prist.kod,OB^[i].kod)=0) do inc(i);
                             if (i<OBs) then trat[bodov].kod:= OB^[i].kod
                             else trat[bodov].kod:= prist.kod;
                             prist.kod:= '';

                             trat[bodov].h := start.h;
                             trat[bodov].m := start.m;
                             inc(bodov);
                          end
                        end;

                   init_time(time, BIOS.hour,BIOS.min,0);
                   init_date(date, BIOS.year,BIOS.month,BIOS.day);

                   format_cFPL(@FPL1);
                   add_prop_FPLc(@FPL1)
                 end;

          'M': with FPL2 do
                 begin
                   idn := copy(strip,2,10);
                   p   := get_word(strip,12);
                   str(p,ssr);
                   prav:= 'P';

                   typ := copy(strip,16,4);

                   kod1:= copy(strip,20,4);
                   if _OBind(kod1, LK, LKs)>=0 then begin start.kod:= kod1; kod1:= '' end
                   else kod1:= kod1+' ';
                   start.h := get_byte(strip,24);
                   start.m := get_byte(strip,25);

                   kod2:= copy(strip,26,4);
                   if _OBind(kod2, LK, LKs)>=0 then begin prist.kod:= kod2; kod2:= '' end
                   else kod2:= ' '+kod2;
                   prist.h := get_byte(strip,30);
                   prist.m := get_byte(strip,31);

                   vys  := get_word(strip,32);
                   vys_ := getchar(copy(strip,34,1));

                   rych := get_word(strip,38);
                   rych_:= getchar(copy(strip,40,1));

                   p:= get_byte(strip,41);
                   trat:= strpasnew(delchar(kod1+copy(strip,42,length(strip)-41)+kod2,[#0]));

                   init_time(time, BIOS.hour,BIOS.min,0);
                   init_date(date, BIOS.year,BIOS.month,BIOS.day);

                   VU:= ' ';
                   for i:= 0 to max_ulohy_FPLm-1 do ulohy[i]:= ' ';

                   format_mFPL(@FPL2);
                   save_mFPL(@FPL2);
                   add_prop_FPLm(@FPL2);

                   disp_mFPL(@FPL2)
                 end
        end

      end;


  procedure receive_broadcast(packet: PNETBpacket);
      begin
        case packet^.data[3] of
          trn_TIME  : receive_TIMEpkt(packet);
          trn_STOP  : Clock^.zastav;
          trn_SET   : Clock^.pust;

          trn_STRIP : receive_FPLpkt(packet)
        end
      end;


  function  TRENAZERmenu_init(title: string): PSubmenu;
     var    TRENAZER_menu : PSubMenu;
            i : int;
     begin
       TRENAZER_menu:= SubMenu(title, OptMenu('POSITIONs',nil,cmDefault,nil),nil);
       for i:= 0 to max_TRENAZER_POS-1 do
         begin
           AddItemToMenu(TRENAZER_menu,Switch2(' ~'+cstr(i+1,1)+'~. POSITION ',@TRENAZER_POSs[i],nil));
         end;
       TRENAZERmenu_init:= TRENAZER_menu
     end;

{$ENDIF}