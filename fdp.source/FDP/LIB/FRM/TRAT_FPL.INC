{$IFDEF FPL4}

{ pomocna funkcia pre vypocet bodov trate bez ohladu
  na spravnost zadania vysky, rychlosti
}
 function _decode_15 (dep: TAP; dep_: TCas;
                      arr: TAP;

                      eet: TCas;
                      dat: TDate;

                      var typ  : string;                   { vstupne hodnoty }
                      var rych : single; var rych_: char;  { mozu byt priradene }
                      var vys  : word;   var vys_: char;   { ak nie su inicializovane }

                      strat : string;                      { priradena trat }
                      trat  : string;

                      var rte   : POBxys;                  { dekodovana trat       }
                      var bodov : int;                     { pocet bodov trate     }

                      var res: string
                     ): bool;

    var   FPL   : DFPL4;
          FDR   : DFDR;
          dd    : TFDR_decoded_data;
          s     : string;
          pomb  : bool;

          ry    : single;
          ry_   : char;
          v     : word;
          v_    : char;

    begin
      rte:= nil; bodov:= 0;

      fillchar(FPL,sizeof(FPL),0);
      fillchar(FDR,sizeof(FDR),0);
      new(FDR.fpl);
      fillchar(dd,sizeof(dd),0);

      ry:= rych; ry_:= rych_;
      v:= vys;  v_:= vys_;
      _9b_rychvys_fl(typ, code_l4_rych_vys(rych,rych_,vys,vys_,0,false),
                     getstr(trat,1,[icao_NXIT]), getstr(trat,getstritems(trat,[icao_NXIT]),[icao_NXIT]),
                     ry,ry_, v,v_
                    );
      if rych=0 then begin rych:= ry; rych_:= ry_ end;
      if vys =0 then begin vys := v;  vys_ := v_  end;

     { musim manualne naplnit hodnoty priebezne naplnane algotrimom
       dekodovania FPL4, ak ho chem pouzit v polovici, somar.
       NEskor prepisat spravne >>>>>>>>>>>>>>>>>>>>>>
     }
      FDR.date:= dat;
      AP_to_OBxy(dep,dd.dep);
      AP_to_OBxy(arr,dd.arr);
      FDR.fpl^.date:= dat;
      FDR.fpl^.start:= dep; FDR.fpl^.start_:= dep_;
      FDR.fpl^.prist:= arr;

      FPL._14:= code_l4_14 (getstr(trat,1,[icao_NXIT]),eet.h,eet.m,v,v_,0,' ',' ');
      FPL._15:= StrPasNew(code_l4_rych_vys(rych,rych_, vys,vys_,0,true)+icao_NXIT+trat);

      pomb:= _15_DCT_POINTS; _15_DCT_POINTS:= false;
      _decode_FPL4_15 (FPL,FDR,dd,res);
      _15_DCT_POINTS:= pomb;

      if res='' then
         begin
           bodov:= FDR.bodov;
           rte:= FDR.rte;
           FDR.rte:= nil;
           FDR.bodov:= 0;
         end;

      _decode_15:= res<>'';
      disp_FDR(@FDR);
      disp_FPL4(@FPL)
    end;


{ priradenie standartnej trate na zaklade 1 a n-teho bodu
}
 function _prirad_trat_FPL4 (bd0,bdl: string;
                             var ntrat,trat: string;
                             fT: PText
                            ): bool;

    var   s, s1,s2,s3, bd0s,bdls, b0,bl: string;
          i,j,k,c, p,p1,p2 : int;
          is_,_is : bool;
          is : int;
          R  : TRTE;
          B  : TOBxy;
          Bi : TsBod;
          L  : PList;
          ld : TListDesc;

    label E;

    begin
      _prirad_trat_FPL4:= false;
      bd0:= mtks_rus_to_lat(getstr(bd0,1,[icao_NXT]));
      bdl:= mtks_rus_to_lat(getstr(bdl,1,[icao_NXT]));
      ntrat:= '';
      trat:= bd0 + icao_NXIT + bdl;
      if is_RTE(bd0,R) or is_RTE(bdl,R) or (Exists(pathDATA+_fnRTE_fir+FIRext)<>0) then Exit;

      bd0s:= bd0; b0:= bd0+NULL;
      bdls:= bdl; bl:= bdl+NULL;
      for i:= 0 to OBs_io-1 do
        begin
          if (strpos(OB_io^[i].pozn,@b0[1])<>nil) then bd0s:= bd0s+icao_NXIT+OB_io^[i].kod;
          if (strpos(OB_io^[i].pozn,@bl[1])<>nil) then bdls:= bdls+icao_NXIT+OB_io^[i].kod;
        end;

      if get_OB_XY (bd0,B) then
         begin
           for i:= 0 to OB^.pocet-1 do
             begin
               OB^.read(i,Bi);
               if (B.x=Bi.x) and (B.y=Bi.y) and (pos(Bi.kod,bd0s)=0) then bd0s:= bd0s+icao_NXIT+Bi.kod;
             end;
           for i:= 0 to LK^.pocet-1 do
             begin
               LK^.read(i,Bi);
               if (B.x=Bi.x) and (B.y=Bi.y) and (pos(Bi.kod,bd0s)=0) then bd0s:= bd0s+icao_NXIT+Bi.kod;
             end;
         end;

      if get_OB_XY (bdl,B) then
         begin
           for i:= 0 to OB^.pocet-1 do
             begin
               OB^.read(i,Bi);
               if (B.x=Bi.x) and (B.y=Bi.y) and (pos(Bi.kod,bdls)=0) then bdls:= bdls+icao_NXIT+Bi.kod;
             end;
           for i:= 0 to LK^.pocet-1 do
             begin
               LK^.read(i,Bi);
               if (B.x=Bi.x) and (B.y=Bi.y) and (pos(Bi.kod,bdls)=0) then bdls:= bdls+icao_NXIT+Bi.kod;
             end;
         end;

      fillchar(ld,sizeof(ld),0); ld.fn:= strpasnew(pathDATA+_fnRTE_fir+FIRext);
      L:= New(PList,Init(@ld,'',setKomen,1,false,nil,true));

      p1:= getstritems(bd0s,[icao_NXIT]);
      p2:= getstritems(bdls,[icao_NXIT]);
      is:= 0;
      j:= 1; while (j<=p1) do
        begin
          b0:= getstr(bd0s,j,[icao_NXIT]);
          k:= 1; while (k<=p2) do
            begin
              bl:= getstr(bdls,k,[icao_NXIT]);
              i:= 0; while (i<=L^.top) do
                begin
                  s := mtks_rus_to_lat(L^.get(i));
                  p := getstritems(s,[icao_NXIT]);
                  s1:= getstr(s,1,[icao_NXIT]);
                  s2:= getstr(s,p,[icao_NXIT]);
                  _is:= (s1=b0) and (s2=bl);
                  is_:= (s1=bl) and (s2=b0);
                  if _is or is_ then
                     begin
                       inc(is);
                     { urcenie trate
                     } ntrat:= s; trat:= s;
                       if is_ then
                          begin
                          { urcenie smeru letu
                          } trat:= '';
                            for c:= p downto 1 do trat:= trat + getstr(s,c,[icao_NXIT]) + icao_NXIT
                          end;
                       if (fT<>nil) then writeln(fT^,trat);
                       if (fT=nil) and (is>1) then
                          begin
                            trat:= bd0 + icao_NXIT + bdl;
                            goto E
                          end
                     end;
                  inc(i);
                end;
              inc(k)
            end;
          inc(j)
        end;

      E :

      Dispose(L,Done);
      strdispose(ld.fn);

      _prirad_trat_FPL4:= ((trat<>'') and (trat<>bd0+icao_NXIT+bdl)) or ((fT<>nil) and (is>0))
    end;


{ Vyber z mnoziny standartnych trati
}
 function  prirad_trat_FPL4 (x,y   : int;

                             _1,_n : string;      { vstupny bod           }
                             FPL   : PDcFPL;

                             var rte   : POBxys;  { dekodovana trat       }
                             var bodov : int;     { pocet bodov trate     }

                             var res   : string
                            ): string;

    var    s,s1, sn,sl, b1,bn, fl,fn, ntrat,trat, dirA,dirD : string;

           Bi,Bi1,Bin : TsBod;
           t1,t2      : text;

           i,p,smer : int;

           dep,arr  : TAP;
           dep_,eet : TCas;
           dat      : TDate;
           ti       : TTime;

           ry,minr, maxr : single;
           ry_,v_,vys_   : char;
           v,minv, maxv  : word;

           M : PWinMenu;
           E : TEvent;

    function _obrat_trat(sn: string): string;
       var   sl: string; i,p: int;
       begin
         sl:= ''; p:= getstritems(sn,[icao_NXIT]);
         for i:= p downto 1 do sl:= sl+getstr(sn,i,[icao_NXIT])+icao_NXIT;
         _obrat_trat:= sl
       end;

    begin
      prirad_trat_FPL4:= '';
      rte:= nil; bodov:= 0;
      res:= '';
      if Exists(pathDATA+_fnRTE_fir+firext)<>0 then Exit;

    { a) priprava dat
    }
      init_date(dat, year,month,day);
      fillchar(dep,sizeof(dep),0);
      fillchar(arr,sizeof(arr),0);
      fillchar(eet,sizeof(eet),0);

      sl:= ''; sn:= '';

      if FPL<>nil then
         begin
           if (_1='') and (bodov>0) then with FPL^.trat[0] do
              begin
                _1:= l4str(kod);
                cas_init(eet,h,m);
              end
           else cas_init(eet,FPL^.eet.h,FPL^.eet.m);
           if (_1='') and (bodov>1) then _n:= l4str(FPL^.trat[FPL^.bodov-1].kod);

           dep := FPL^.start;
           dep_:= FPL^.start_;
           arr := FPL^.prist;
         end;


    { b) Priprava podmnoziny moznych trati
    }
      i:= 0;
      fl:= pathDATA+_fnRTE_fir+FIRext;
      fn:= pathTMP+_fnRTE_fir+'.@@@';
      if (_1<>'') or (_n<>'') then
         begin
           assign(t2,fn);
           rewrite(t2);
           if (FPL=nil) and (_1<>'') and (_n<>'') and _prirad_trat_FPL4(_1,_n, ntrat,trat, @t2) then writeln(t2,'');

           assign(t1,fl);
           reset(t1);
           while not eof(t1) do
             begin
               readln(t1,s); s:= uni_str(s);
               if (s='') or (s[1]=';') then continue;
               s:= uni_str(getstr(s,1,[';']));

               s1:= getstr(s,1,[icao_NXIT]);
               sn:= getstr(s,getstritems(s,[icao_NXIT]),[icao_NXIT]);
               if (s1=_1) or (sn=_1) {or (s1=_n) or (sn=_n)} then
                  begin
                    if (_1=sn) {or (s1=_n)} then sl:= _obrat_trat(s)
                    else sl:= s;
                    writeln(t2,sl);
                    inc(i)
                  end
             end;
           close(t1);
           close(t2)
         end;


    { c) Vyber z ponuky, ak existuje;
    }
      if (i>1) then sl:= _get_item_(x,y, fn,[], lst_vsetky_polozky,false,nil)
      else if i=1 then {sl:= sl}
      else sl:= _get_item_(x,y, fl,[], lst_vsetky_polozky,false,nil);
      delfile(fn);
      if sl='' then Exit;


    { d) Urcenie smeru letu;

      ak existuje vstupny bod, automaticky, inak sa musi definovat
      (bud na zaklade stotoznenia vstupneho bodu a letiska startu
       alebo upresnenia uzivatela
      )
    }
      b1:= l4str(getstr(sl,1,[icao_NXIT]));
      is_OB(b1,Bi1,true);
      bn:= l4str(getstr(sl,getstritems(sl,[icao_NXIT]),[icao_NXIT]));
      is_OB(bn,Bin,true);

      if (_1=b1) or (_n=bn) then smer:= 1
      else if (_1=bn) or (_n=b1) then smer:= -1
      else smer:= 0;

      if smer=0 then
         if (dep.kod<>'') then
            if is_OB(dep.kod,Bi,true) then
               if (Bi.x=Bi1.x) and (Bi.y=Bi1.y) then smer:= 1
               else if (Bi.x=Bin.x) and (Bi.y=Bin.y) then smer:= -1
            else if is_iobod_dir(b1,dep.kod, dirD) then smer:= 1
            else if is_iobod_dir(bn,dep.kod, dirD) then smer:= -1;

      if smer=0 then
         if (arr.kod<>'') then
            if is_OB(arr.kod,Bi,true) then
               if (Bi.x=Bi1.x) and (Bi.y=Bi1.y) then smer:= -1
               else if (Bi.x=Bin.x) and (Bi.y=Bin.y) then smer:= 1
            else if is_iobod_dir(b1,arr.kod, dirA) then smer:= 1
            else if is_iobod_dir(bn,arr.kod, dirA) then smer:= -1;


      if smer=0 then
         begin
           M:= WinMenu(mnufrm_SMER_LETU,nil,
                       Item(' ~a~) '+mnufrm_TRAT_SMER+' ('+b1+'->'+bn+') ',cmEST_NEXT,
                       Item(' ~b~) '+mnufrm_TRAT_OPAK+' ('+bn+'->'+b1+') ',cmEST_LAST,
                       nil ) )
                      );
           M^.MoveRel(x-M^.x0,y-M^.y0);
           M^.Run(E);
           Dispose(M, Done);
           if ((E.What and evMessage)<>0) then
              case E.Command of
                cmEST_NEXT : smer:= 1;
                cmEST_LAST : smer:= -1
                else Exit
              end
         end;

      sn:= sl;
      if smer=0 then Exit
      else if smer=-1 then sl:= _obrat_trat(sn);
      if not (length(sl)<sizeof(sl)-1) then sl[0]:= chr(sizeof(sl)-2);

      if (FPL<>nil) then
         begin

         { e) Urcenie vstupneho casu
         }
           if (FPL^.bodov=0) or ((eet.h=0) and (eet.m=0)) then
              if formular_CAS(ti, hour,min, x,y, 'EET/'+getstr(sl,1,[icao_NXT]),nil)
                 then cas_init(eet,ti.h,ti.m)
              else Exit;

         { f) Dekodovanie trate do postupnosti bodov
         }
            vys_:= altS;
           _decode_15 (dep,dep_,arr, eet,dat,
                       FPL^.typ,
                       FPL^.rych,FPL^.rych_,
                       FPL^.vys,vys_,
                       sn,sl,
                       rte,bodov,
                       res
                      );
           FPL^.vys:= get_altM(vys_,FPL^.vys) div m_S;

           sn:= '';
           if res='' then for i:= 0 to bodov-1 do sn:= sn+rte^[i].kod+icao_NXIT
         end
      else sn:= sl;

      prirad_trat_FPL4:= sn
    end;

(*
{ pomocna funkcia pre vypocet bodov trate bez ohladu
  na spravnost zadania vysky, rychlosti
}
 function _decode_15 (dep: TTBOD; dep_: TTime; arr: TTBOD;
                      eet: TTime; dat: TDate;

                      var typ  : string;                   { vstupne hodnoty }
                      var rych : single; var rych_: char;  { mozu byt priradene }
                      var vys  : word; var vys_: char;     { ak nie su inicializovane }

                      strat : string;                      { priradena trat }
                      trat  : string;

                      var rte   : PTBODy;                  { dekodovana trat       }
                      var bodov : int;                     { pocet bodov trate     }

                      var res: string
                     ): bool;


    begin
    end;
*)

{$ENDIF}
