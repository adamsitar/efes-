 function eq_cFPL(FPL1, FPL2: PDcFPL): bool;
    begin
      eq_cFPL:=      ((FPL1<>nil) and (FPL2<>nil))
                 and (codekey_FPLC(FPL1) = codekey_FPLC(FPL2))
    end;


 function chg_cFPL (FPL1, FPL2: PDcFPL): bool;
    begin
      chg_cFPL:= not(    eq_cFPL (FPL1,FPL2)


                     and (FPL1^.ssr_=FPL2^.ssr_)
                     and (FPL1^.ssr=FPL2^.ssr)
                     and (FPL1^.ssr0=FPL2^.ssr0)

                     and (FPL1^._8a =FPL2^._8a)
                     and (FPL1^._8b =FPL2^._8b)

                     and (FPL1^.typ=FPL2^.typ)
                     and (FPL1^.com_=FPL2^.com_)

                     and (FPL1^.rych=FPL2^.rych)
                     and (FPL1^.rych_=FPL2^.rych_)

                     and (FPL1^.vys1=FPL2^.vys1)
                     and (FPL1^.vys1_a=FPL2^.vys1_a)

                     {$IFDEF FPLC_ION}
                      and (FPL1^.vysO=FPL2^.vysO)
                      and (FPL1^.vysO_a=FPL2^.vysO_a)

                      and (FPL1^.vysH=FPL2^.vysH)
                     {$ENDIF}

                     and (not chg_AP(FPL1^.start,FPL2^.start))
                     and (FPL1^.start_.h=FPL2^.start_.h)
                     and (FPL1^.start_.m=FPL2^.start_.m)
                     and (not chg_AP(FPL1^.prist,FPL2^.prist))

                     and (FPL1^.bodov=FPL2^.bodov)
                     and memcomp(@FPL1^.trat,@FPL2^.trat,FPL1^.bodov*sizeof(TOB))

                     and (FPL1^.stt=FPL2^.stt)

                     {
                     and (FPL1^.TRG=FPL2^.TRG)
                     and (FPL1^.RDP=FPL2^.RDP)
                     }

                     {$IFDEF RVSM}
                      and (FPL1^._80 = FPL2^._80)
                      and (FPL1^._81 = FPL2^._81)
                     {$ENDIF}
                    )
    end;



 function idn_cFPL(FPL: PDcFPL): string;
    begin
      idn_cFPL:= {format_s(}FPL^.idn
    end;

 function ssr_cFPL(FPL: PDcFPL): string;
    begin
      ssr_cFPL:= FPL^.ssr
    end;

 function ssr0_cFPL(FPL: PDcFPL): string;
    begin
      ssr0_cFPL:= FPL^.ssr0
    end;

 function typ_cFPL(FPL: PDcFPL): string; far;
    begin
      typ_cFPL:= FPL^.typ
    end;


 { -------------------------- }
 { save                       }
 { -------------------------- }

 function _arch_fn_cFPL(p: pointer; i: int): string;
    var   FN : string;
          j  : int;
    begin
      _arch_fn_cFPL:= '';
      if i>prehlad_arch_fn_cFPL then Exit;

      FN:= get_PLANhod(day,month,year, hour);
      for j:= 0 to i-1 do FN:= get_prev_HODfn(FN);

      if Exists(pathFPL_C+FN)<>0 then _arch_fn_cFPL:= pathARCH_FPL_C+FN
      else _arch_fn_cFPL:= pathFPL_C+FN
    end;

 {
  hlada FPL v subore za poslednu hodinu
 }
 function _find_cFPL(FPL: PDcFPL): int; far;
    var   FPLi: DcFPL;
          FN  : string;
          ind : int;
    begin
      FN:= pathFPL_C+get_PLANhod(day,month,year, hour);
      ind:= DB_prehladaj(@eq_cFPL, FPL,@FPLi, nil,
                         FN, db_cFPL_RIADKOV, @decodeDB_FPLC,@codekey_FPLC,
                         false,''
                        );
      _find_cFPL:= ind
    end;


 { predpoklada, ze FPL je neinicalizovana struktura !
 }
 function get_fn_cFPL: string;
    begin
      get_fn_cFPL:= pathFPL_C+get_PLANhod(day,month,year{,FPL^.date.d,FPL^.date.m,FPL^.date.r}, BIOS.hour)
    end;

 function read_cFPL(key: string; FPL: PDcFPL): int;
    var   res: int;
    begin
      res:= -1;
      if (FPL<>nil) and (key<>'') then
         begin
           decodekey_FPLC(key, FPL);
           res:= DB_najdi(FPL,get_fn_cFPL,
                          db_cFPL_RIADKOV,@decodeDB_FPLC,@codekey_FPLC,
                          true, @disp_cFPL,''
                         );
         end;
      read_cFPL:= res
    end;

 procedure save_cFPL(_FPL: PDcFPL);
     var   FPL : DcFPL;
           {h : byte;}
     begin
      {$IFNDEF TRENAZER}
       {if (in_list(FPL^.start.kod,@fnCLet,0) and (FPL^.start.h<>0)) then h:= FPL^.start.h
       else if (FPL^.bodov>=0) then h:= FPL^.trat[0].h
       else h:= BIOS.hour;
       FN:= ;}
       FPL:= _FPL^;  { naplnenie buffera, pretoze v nasledujucom prikaze sa caka na spracovanie }
       DB_oprav(@FPL,pathFPL_C+get_PLANhod(day,month,year{,FPL^.date.d,FPL^.date.m,FPL^.date.r}, BIOS.hour),
                db_cFPL_RIADKOV,@codeDB_FPLC,@codekey_FPLC,@dbchg_cFPL, dbattr_FPC
               )
      {$ENDIF}
     end;


 function  _find_FPLCa (key: string; var p: PFPLC; var o: P_OFPL): int;
    var    ires : int;
    begin
      ires:= -1;
      p:= nil;
      o:= nil;
      if cFPL<>nil then
         begin
           ires:= cFPL^.find_key(key);
           if ires>-1 then
              begin
                p:= cFPL^.ap^[ires];
                o:= cFPL;
              end
         end;
      {$IFDEF EDD}
       if (p=nil) and (PROP_cFPL<>nil) then
          begin
            ires:= PROP_cFPL^.find_key(key);
            if ires>-1 then
               begin
                 p:= PROP_cFPL^.ap^[ires];
                 o:= PROP_cFPL
               end;
          end;
      {$ENDIF}
      _find_FPLCa:= ires
    end;

 function  find_FPLCa (key: string): PFPLC;
    var    p : PFPLC;
           o : P_OFPL;
    begin
      _find_FPLCa (key, p,o);
      find_FPLCa:= p
    end;
