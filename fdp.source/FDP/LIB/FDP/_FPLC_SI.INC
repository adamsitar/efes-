{$IFDEF SECTORS}

{ ------------------------------------
  a) Nastavenie parametrov spracovaia
  ------------------------------------
}
  function OcFPL.get_on_sector (p: pointer): bool;
     begin
       get_on_sector:= (PDcFPL(p)^.sec and s_on)<>0
     end;

  procedure OcFPL.set_on_sector (p: pointer; _on_sector: bool);
      begin
        if _on_sector then PDcFPL(p)^.sec:= PDcFPL(p)^.sec or s_on
        else PDcFPL(p)^.sec:= PDcFPL(p)^.sec and ($FF xor s_on)
      end;

  {$IFDEF PRN}
   function  OcFPL.get_printed (p: pointer): bool;
      begin
        get_printed:= (PDcFPL(p)^.sec and s_prn)<>0
      end;

   procedure OcFPL.set_printed (p: pointer; was: bool);
      begin
        if was then PDcFPL(p)^.sec:= PDcFPL(p)^.sec or s_prn
        else PDcFPL(p)^.sec:= PDcFPL(p)^.sec and (($FF xor s_prn));
        inherited set_printed (p,was)
      end;
  {$ENDIF}



{ ------------------------------------
  b-1) vypocet platnosti v sektore
  ------------------------------------
}
 function OcFPL.urc_platnostS(p: pointer): bool;
    begin
      urc_platnostS:= sektor_FPLc(p)
    end;


 { Funkcie predpokladaju volanie urc_platnost
   po zaradeni planu alebo prenastaveni
   sektorizacie
 }
 function  OcFPL.let_cez_sektor(p: pointer): bool;
    begin
      with PDcFPL(p)^ do let_cez_sektor:= ((sec and s_th)<>0) or ((sec and s_is)<>0)
    end;

 function  OcFPL.let_v_sektore(p: pointer; _limit: real): bool;
    var    dTdel : real;
    begin
      dTdel:= minimum(S_DEL_LIMIT,dT_deactive_FPLC);
      with PDcFPL(p)^ do
         let_v_sektore:=     ((sec and s_is)<>0)
                         and ((T1=0) or (T1-_limit<=absTime))
                         and ((not accepted) or ((Tn=0) or (absTime<Tn+dTdel*60)))
    end;



 function  OcFPL.platnost_letu_v_sektore(p: pointer; zmena_sektorizacie: bool): bool;
    var    FPL     : PDcFPL;
           _T1,_Tn : real;
           _B1,_Bn : byte;
           _sec    : byte;
    begin
      FPL:= PDcFPL(p);
      with FPL^ do
        begin
          _sec:= sec; _T1:= T1; _Tn:= Tn; _B1:= B1; _Bn:= Bn
        end;
      sektor_FPLc(FPL);
      with FPL^ do
        begin
          platnost_letu_v_sektore:=    (_sec<>sec)
                                    or (_T1<>T1) or (_Tn<>Tn)
                                    or (_B1<>B1) or (_Bn<>Bn)
        end
    end;


{ ------------------------------------
  b-2) vypocet platnosti v sektore
  ------------------------------------
}

function  sektor_FPLc (FPL: PDcFPL): bool;

    var   bres,is_d,is_a, is,was, idaleko,odaleko : bool;
          i, ind, _b1,_bn : int;
          x1,y1, xn,yn : real;

          Ta    : array[0..1+max_OB-1+1] of TOB;
          Bo,Na : int;
          OBi   : TOBxy;


    function let_cez_sektor(b1,b2 : int; var x,y: real): bool;
       var   bod1,bod2: TsBod;
       begin
         b1:= Minimum(N(b1),Bo-1);
         b2:= Minimum(N(b2),Bo-1);
         let_cez_sektor:=
                (not (_OBindBi (Ta[b1].ind,OB,bod1) and _OBindBi (Ta[b2].ind,OB,bod2)))
             or cez_sektor ( bod1.x,bod1.y, Ta[b1].vys,vysOB,
                             bod2.x,bod2.y, Ta[b2].vys,vysOB,
                             x,y
                           )
       end;

    function let_v_hladine(b1,b2 : int): bool;
       var   bod1,bod2: TsBod;
       begin
         b1:= Minimum(N(b1),Bo-1);
         b2:= Minimum(N(b2),Bo-1);
         let_v_hladine :=
               (not (_OBindBi (Ta[b1].ind,OB,bod1) and _OBindBi (Ta[b2].ind,OB,bod2)))
             or vyska_v_sektore
                       ( bod1.x,bod1.y, Ta[b1].vys,vysOB,
                         bod2.x,bod2.y
                       )
       end;

    procedure podla_casu(var b1,b2: int; inp: bool);
        var   bod1,bod2: TsBod;
              b: int;
        begin
          b1:= Minimum(N(b1),Bo-1);
          b2:= Minimum(N(b2),Bo-1);
          if      (inp       and (Ta[b2].cas < Ta[b1].cas))
               or ((not inp) and (Ta[b1].cas < Ta[b2].cas))
               then
                 begin
                   b:= b2; b2:= b1; b1:= b
                 end;
        end;


    { vypocet casu na x,y od bodu Ta[bn]: vzdialenost / rychlost,
      pretoze cas na prvom/poslednom bode je nulovy
    }
    function cas_pred_za_bodom (b1,b2: int; x,y: real; rych: single; rych_: char; inp: bool): real;
       var   ds,dn,dt, T : real;
             h,m,s : byte;
             bod : TsBod;
       begin
         podla_casu(b1,b2, inp);
         cas_pred_za_bodom:= 0.;                       { alebo _bi.cas, je to jedno }
         rych:= get_rych_kmh(rych,rych_, 0,vysOB);
         if (rych=0) or (x=0) or (y=0) then Exit;      { predpoklad, ze _bi.ind>=0  }

         if _OBindBi (Ta[b2].ind,OB,bod) then
            begin
              ds:= vzdialenost(bod.x,bod.y, x,y); { [m] }
              dt:= secHOUR*ds/(rych*1000);                                { [s] }
            end
         else dt:= 0;
         if inp then dt:= -dt;  { cas sa pocita od druheho bodu pri vstupe a opacne }
         T:= Ta[b2].cas-dt;
         if T<0 then T:= 0;

         cas_pred_za_bodom:= T  {$IFDEF DEBUG}; TimeFromSec(T, h,m,s) {$ENDIF}
       end;


    { vypocet casu na x,y, ktore je priesecnikom spojnice _bi/_bn a sektora :
      mensi_cas + (vzdialenost_od_neho/celkova_vzdialenost)*rozdiel_casov
    }
    function cas_na_bode_hranici (b1,b2: int; x,y: real; inp,point: bool; var daleko: bool): real;
       var   dr,ds,dn,dt,dx, T : real;
             patri : bool;
             h,m,s : byte;
             bod1,bod2 : TsBod;
       begin
         daleko:= false;
         podla_casu(b1,b2, inp);
         cas_na_bode_hranici:= Ta[b1].cas;
         if (x=0) or (y=0) then Exit;

        {
         Ak je b1 (vstupny/vystupny [podla casu]) mimo sektoru,
         a jeho vzdialenost od neho je mensia ako nastavena
         maximalna vzdialenost io bodu od hranice, priradi sa
         cas na bode.
         Ak je vzdialenost vacsia ako nastavena a druhy bod
         lezi v sektore a takejto vzdialenosti od hranice,
         nastavi sa priznak daleko.
        }
         dt:= 0;

         patri:=    (not _OBindBi (Ta[b1].ind,OB,bod1))
                 or v_sektore(bod1.x,bod1.y, 0,vysOB, 0,0,0,vysOB);
         if (not patri) then
            begin
              if (not _OBindBi (Ta[b2].ind,OB,bod2)) then dr:= 0
              else dr:= vzdialenost(bod1.x, bod1.y, bod2.x,bod2.y);
              if dr<>0 then
                 begin
                   ds:= vzdialenost(bod1.x,bod1.y, x,y);
                   dn:= vzdialenost(bod2.x,bod2.y, x,y);
                   dx:= S_IN_KM; dx:= dx*1000;
                   daleko:= (dn=0) or (ds>dx);
                   if daleko then
                      begin {or (not inp)}
                        dt:= (Ta[b2].cas-Ta[b1].cas)*(ds/dr);
                      end;
                   daleko:= dn<ds
                 end
            end;
         T:= Ta[b1].cas;
         if not point then T:= T+dt;

         cas_na_bode_hranici:= T {$IFDEF DEBUG}; TimeFromSec(T, h,m,s) {$ENDIF}
       end;


    procedure  null_sec(FPL: PDcFPL);
        begin
          with FPL^ do
            begin
              T1:= 0; Tn:= 0; B1:= 0; Bn:= N(FPL^.bodov-1);
              sec:= sec and ($FF xor s_th) and ($FF xor s_is) and ($FF xor s_err);
              sektor_FPLc:= false
            end;
        end;

   { sektor_FPLc :
   }
    begin

      null_sec(FPL);

    { a) existuje neznamy bod na trase, potom sa zaradi,
         pretoze sa nevieme rozhodnut, ci patri...
    }
      i:= 0; while (i<FPL^.bodov) and (FPL^.Trat[i].ind>=0) do inc(i);
      if (i<FPL^.bodov) then
         begin
           sektor_FPLc:= true;
           FPL^.sec:= FPL^.sec or s_err or s_is or s_th;
           Exit
         end;

    { b) leti cez sektor ?
    }
      fillchar(Ta,sizeof(Ta),0);
      with FPL^ do
        begin
          Bo:= 0; Na:= na_bod;
          ind:= _OBind(start.kod,OB);
          is_d:= ind>=0;
          if is_d then
             begin
               Ta[0].kod:= start.kod;
               Ta[0].cas:= start.cas;   { vyska je vynulovana fillchar-om }
               Ta[0].ind:= ind;
               Ta[0].vys:= 1;
               inc(Bo);
             end;
          Move(Trat[0],Ta[Bo],bodov*sizeof(TOB));
          inc(Bo,bodov);
          ind:= _OBind(prist.kod, OB);
          is_a:= ind>=0;
          if is_a then
             begin
               Ta[Bo].kod:= prist.kod;
               Ta[Bo].cas:= prist.cas;
               Ta[Bo].ind:= ind;
               Ta[Bo].vys:= 1;
               inc(Bo)
             end;
        end;

      _b1:= 0; while (_b1<Bo)  and (not let_cez_sektor(_b1,_b1+1, x1,y1)) do inc(_b1);
      if _b1>=Bo then Exit;
      _bn:= Bo-1; while (_bn>_b1) and (not let_cez_sektor(_bn,_bn-1, xn,yn)) do dec(_bn);

      FPL^.B1:= _b1;
      FPL^.Bn:= _bn;
      FPL^.sec:= FPL^.sec or s_th; { zatial sa priradia atributy "through" i "in" }


    { c) dotyka sa ineho sektora ?
         Moze ho suchnut, prienik jednym bodom sa ignoruje,
         i ked by bolo spravnejsie detekovat naozaj len dotyk...
    }
      if not S_TOUCH then
         begin
         end;


    { e) kontrola na dodrzanie vysky v sektore...
    }
      if (FPL^.sec and s_th <> 0) and check_ALTSEC then
         begin
           _b1:= FPL^.B1;
           _bn:= FPL^.Bn;
           while (_b1<_bn) and (not let_v_hladine(_b1,_b1+1)) do inc(_b1);
           while (_bn>_b1) and (not let_v_hladine(_bn,_bn-1)) do dec(_bn);
           if (_b1=_bn) and (not let_v_hladine(_b1,_bn)) then
              begin
                null_sec(FPL)
              end
           else begin
                 FPL^.B1:= _b1;
                 FPL^.Bn:= _bn
                end
         end;


    { d) Ak su vstupne/vystupne body pridaleko, ich odfiltrovanie
         - vypocet vstupno/vystupnych casov
           (na bode alebo hranici (priesecniku so sektormi))
    }
      if (FPL^.sec and s_th <> 0) then with FPL^ do
         begin

           _b1:= B1;
           _bn:= Bn;

         { d1) cas prieniku hranice na prvom vstupe do sektora
         }
           idaleko:= false;
           if (_b1=0) and is_d then
              begin
                if (start.h<>0) or (start.m<>0) then T1:= start.cas  { cas startu je uvedeny }
                else T1:= cas_pred_za_bodom(_b1,_b1+1, x1,y1, rych,rych_, true)
              end
           else T1:= cas_na_bode_hranici(_b1,_b1+1, x1,y1, true,S_INP_POINT_TIME, idaleko);

         { d2) posledny vystup zo sektora
         }
           odaleko:= false;
           if (_bn=Bo-1) and is_a then
              begin
                if (prist.h<>0) or (prist.m<>0) then Tn:= prist.cas
                else Tn:= cas_pred_za_bodom(_bn-1,_bn, xn,yn, rych,rych_, false)
              end
           else Tn:= cas_na_bode_hranici(_bn-1,_bn, xn,yn, false,S_OUT_POINT_TIME, odaleko);

           if odaleko and (FPL^.Bn>FPL^.B1) then dec(FPL^.Bn);
           if idaleko and (FPL^.Bn>FPL^.B1) then inc(FPL^.B1);

         { su urcene iobody pridaleko od hranice ?
           a su za nou ine, ak nie -> nebude vstup na bode...;
           preto to zakomentujem :
         }
           {if (T1<>0) and (Tn<>0) then} sec:= sec or s_is;
        end;


    { f) Odfiltrovanie letisk z pola
    }
      if (FPL^.sec and s_th <> 0) then
         begin
           if is_a and (FPL^.Bn=Bo-1) then
              begin
                dec(FPL^.Bn)
              end;
           if is_d then
              begin
                if (FPL^.B1>0) then dec(FPL^.B1);
                if (FPL^.Bn>0) then dec(FPL^.Bn);
              end;
         end;

      sektor_FPLc:= FPL^.sec and s_th <> 0
    end;

{$ENDIF}
