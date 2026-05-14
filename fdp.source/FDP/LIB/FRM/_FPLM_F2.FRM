function _mFPL_trat_read(form : PmFPLform; var _15 : pchar): bool;
   begin
     _mFPL_trat_read:= true;
     _15:= nil;
     {$IFDEF FPLM_L}  form^.read_pole (i_15M,_15);
     {$ELSE} _15:= StrPasNew(  mtks_rus_to_lat (cut_(form^._it_i(i_15M)))
                             + kbCRLF
                             + mtks_rus_to_lat (cut_(form^._it_i(i_15M+1)))
                            );
     {$ENDIF}
   end;


function _mFPL_check(form: PmFPLform; FPL: PDmFPL; syntax,vlastne,prepocet: bool): bool;
   var   FPLp : PDmFPL;
         res  : string;
         ires : int;

         podany : real;
         prist_zadany,prist_vyp : TAP;
         KRIDLO : bool;

         s : string;
         i : int;
         b : byte;

   label X,E;

   begin
     _mFPL_check:= false;
     if form=nil then Exit;

     res:= ''; ires:= -1;
     disp_mFPL(FPL);
     FPLp:= PDmFPL(form^.adr_data);

     with FPL^ do
       begin

       { --------------
         identifikacia
         --------------
       }
         idn:= cut_(form^._it_i(i_7Ma));
         {$IFNDEF L4444M}
          idn_:= getchar(form^._it_i(i_7Ma2));
         {$ENDIF}

         KRIDLO:= false;
         if (form^.itemd^[i_7Ma].legal<>@setNil) then
            begin
             {$IFDEF PROCESS_KRL}
               if cut_(idn)='' then KRIDLO:= form^.Ask(i_7Ma,msgVERIPHY,ask_kridlo)=ansAno;
             {$ENDIF}
             if (not KRIDLO) and (length(cut_(idn))=0) then
                begin
                  ires:= l4_err(a_FPLM,idn,i_7Ma,err_FPLM_7a_chyba, s);
                  if form^.Ask(i_7Ma,msgVERIPHY,s)<>ansAno then goto X
                end;
            end;

       { --------------
         ssr
         --------------
       }
         ssr_:= getchar(form^._it_i(i_7Mb));
         ssr := cut_(form^._it_i(i_7Mc));

       { --------------
         typy letunov
         --------------
       }
         typ:= mtks_rus_to_lat(cut_(form^._it_i(i_9Mb)));
         typ2:= mtks_rus_to_lat(cut_(form^._it_i(i_9Me)));

       { --------------
         typ letu
         --------------
       }
         _8a:= getchar(form^._it_i(i_8Ma));
         {$IFDEF L4444M}
          _8b:= getcharu(form^._it_i(i_8Mb));
         {$ELSE}
          { docasne urcenie typu planu podla typu : }
           _8b:= getchar(_8b);
         {$ENDIF}

       { ------------
          rychlost
         ------------
       }
         s:= form^._it_i(i_15Ma_);
         rych_:= s_prizn(s);
         if rych_= ' ' then rych_:= spdK; rych:= s_real(s);
         s:= form^._it_i(i_15Ma);
         if     (not decode_l4_rych(rych_+s,rych,rych_))
            and (   (s<>'')        { bola zadana rychlost }
                 or (not KRIDLO)   { pre kridlo nemusi byt zadana rychlost }
                )
            then
            begin
              ires:= l4_err(a_L4,s,i_15Ma,err_l4444_rych_chyba, res);
              goto X
            end;

       { -----------------
          letisko startu
         -----------------
       }
         start.kod:= mtks_rus_to_lat(form^._it_i(i_13Ma));
         s:= form^._it_(i_13Mb);
         if     (start.kod<>'')
            and (   (s<>'  :  ')   { bol zadany cas }
                 or (not KRIDLO)   { pre kridlo nemusi byt zadany cas }
                )
            and (not GetTimeStr(start.h,start.m,b, s))
            then
            begin
              ires:= l4_err(a_L4,start.kod,i_13Mb,err_l4444_time,res);
              goto X
            end;


       { -------------------
          letisko pristatia
         -------------------
       }
         prist_zadany.kod:= mtks_rus_to_lat(form^._it_i(i_16Ma));
         s:= form^._it_(i_16Mb);
         if (not GetTimeStr(prist_zadany.h,prist_zadany.m,b, s)) then
            begin
              if (s<>'  :  ') then
                 begin
                   ires:= l4_err(a_L4,idn,i_16Mb,err_l4444_time,res);
                   goto X
                 end;
              prist_zadany.h:= start.h; prist_zadany.m:= start.m;
            end;
         prist:= prist_zadany;


       { -------------------
          vyska
         -------------------
       }
         s:= cut_(form^._it_i(i_15Mb1));
         if      ((s<>'') or (not KRIDLO))
             and (not decode_l4_vys(s, vys,vys_))
             then
             begin
               ires:= l4_err(a_L4,s,i_15Mb1,err_l4444_vyska_chyba,res);
               goto X
             end;

         s:= cut_(form^._it_i(i_15Mb2));
         if ((s<>'') and (not decode_l4_vys(s, vys2,vys2_))) then
            begin
              ires:= l4_err(a_L4,s,i_15Mb2,err_l4444_vyska_chyba,res);
              goto X
            end;


       { -------------------
          VU
         -------------------
       }
         VU:= cut_(form^._it_i(i_OPM));


       { -------------------
          Ulohy
         -------------------
       }
         s:= cut_(form^._it_i(i_TSKM));
         for i:= 0 to max_ulohy_FPLm-1 do ulohy[i]:= getstr(s,i+1,[' ']);


       { -------------------
          Trat
         -------------------
       }
         _mFPL_trat_read(form, trat);


       { -------------------
          Poznamka
         -------------------
       }
        {$IFDEF FPLM_L} form^.read_pole (i_18M,pozn);
        {$ELSE}         pozn:= StrPasNew (  mtks_rus_to_lat (cut_(form^._it_i(i_18M)))
                           + kbCRLF
                           + mtks_rus_to_lat (cut_(form^._it_i(i_18M+1)))
                          );
        {$ENDIF}

       { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
          Datum platnosti by sa mal
          naplnit z poznamky
          DATE/1203
       }
         {$IFDEF PPL}
           form^.decode_DATE(i_18M, date, res,ires);
         {$ELSE}
           if date.r=0 then
              begin
                init_date(date, year,month,day);
                podany:= TimeToSec(hour,min,0);
                if    {((start.h<>0) or (start.m<>0) or (prist.h<>0) or (prist.m<>0))}
                       (     (TimeToSec(start.h,start.m,0) < podany)
                         and (TimeToSec(prist.h,prist.m,0) < podany)
                       )
                    then
                      begin
                        s:= tit_ESTIMATED_ARR+TimeToStr(prist.h,prist.m,':')+'. '+ask_REALIZED_PLAN;
                        if form^.Ask(i_16Mb,msgVeriphy,s)<>ansAno then
                           begin
                             date.r:= 0;
                             goto E
                           end
                      end
              end
           else form^.is_date:= true;
         {$ENDIF}
         if (res<>'') then goto X;

       { -----------------------------------------------
          Nastavenie remenne, identifikacia planu, kluc
         -----------------------------------------------
       }


       { -----------------------------------------------
          Kontrola na syntax
         -----------------------------------------------
       }
        if syntax and (not syntax_mFPL(FPL,FPLp, KRIDLO, vlastne,true, res,ires, form)) then goto X;


       { -----------------------------------------------
          Kontrola na regularitu hranic a xxP
         -----------------------------------------------
       }
        if not regularita_mFPL(FPL,FPLp, form^.novy,true,false, res,ires, form) then goto X;


       { -----------------------------------------------
          Dopocitanie parametrov datumu/pristatia
         -----------------------------------------------
       }
        { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
           Zadanie casu pristatia; ak vo formulari nebola polozka
           16b prazdna, overi si zadanu hodnotu
        }
         prist_vyp:= FPL^.prist;
         FPL^.prist:= prist_zadany;

         with FPL^ do
          if     prepocet
             (*
             and (   form^.novy
                  or (   ({ Tato kontrola tu existuje kvoli tomu, ze je
                             zvykom zadat cas pristatia iny, ako je
                             vypocitany, pretoze masinka este moze
                             vylietavat palivo v TMA/CTR
                           }
                               (zmenena_trat_FPLm(FPLp,FPL,true,false,false))
                           and (   (prist_zadany.h<>prist_vyp.h)
                                or (prist_zadany.m<>prist_vyp.m)
                               )
                          )
                     )
                 )
             *)
             and (    (     (not form^.novy)
                        and zmenena_trat_FPLm(FPLp,FPL,true,false,false)
                      )
                  or  (   (prist_zadany.h<>prist_vyp.h)
                       or (prist_zadany.m<>prist_vyp.m)
                      )
                 )
                then
                 begin
                   if (rych<>0) then
                      case form^.Ask(i_16Mb,tit_ETA,ask_ETA) of
                        ansAno  : begin
                                    prist:= prist_vyp;
                                    form^.UpDateItem(i_16Mb,TimeToStr(prist.h,prist.m, ':'));
                                  end;
                        ansNie  : prist:= prist_zadany;
                        else {ansZrus } goto E
                      end;
                 end
          else prist:= prist_zadany;


       { -----------------------------------------------
          Kontrola na regularitu ASM/FUA
         -----------------------------------------------
       }
        if not regularita_mFPL(FPL,FPLp, form^.novy,false,true, res,ires, form) then goto X;


        if (dap.rok=0) or (not is_KRL(FPL)) then datum_init(dap, day,month,year, hour,min,sec);


       { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
          Zdroj planu
       }
        if let='' then
           begin
             let:= _mairbase(start.kod);
             {$IFDEF AIRBASE}
              let:= this_airbase;
             {$ELSE}
              {let:= nadriadene_letisko(kod);}
             {$ENDIF}
           end;

     end;

     format_mFPL(FPL);
     _mFPL_check:= true;
     Exit;

     X : if (res<>'') then
            begin
              if (ires<0) then ires:= 0;
              form^.errors(ires,res)
            end;

     E : disp_mFPL(FPL)
   end;


function mFPL_check(form: PmFPLform; FPL: PDmFPL): bool;
   begin
     mFPL_check:= _mFPL_check(form,FPL,true,true,true)
   end;


function mFPL_date(FPL: PDmFPL; FPLp: PDmFPL; dt: PDate): bool; far;
   begin
     if (dt<>nil) then FPL^.date:= dt^;
     mFPL_date:= true
   end;
