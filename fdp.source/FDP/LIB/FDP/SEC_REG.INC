{$IFDEF SECTORS}

  { je niektory z bodov v sektore alebo pretina usek trate sektor ?
    - vypocet pre niektory zo sektorov
  }
  function cez_sektor(x0,y0 : real; v0: word; v0_: char;
                      x1,y1 : real; v1: word; v1_: char;
                      var x,y : real
                     ): bool;

     var   i,p : int;
           v0s,v1s : word;
           patri, is_v0,is_v1, is_b0,is_b1,is_p : bool;
           dr,dr0,dr1 : real;

     begin
       patri:= false;
       i:= 0; while (i<=nsec) and (not patri) do
         begin
           if (SECTORs^[i]<>nil) and (SECTORs^[i]^.is) then
              begin
               {sec := PathToSEC+SECTORs^[i]^.nazov+ext_MAP};

                v0s := SECTORs^[i]^.vys_0;
                v1s := SECTORs^[i]^.vys_1;

                v0  := get_altM(v0_,v0) div m_S;
                v1  := get_altM(v1_,v1) div m_S;

                is_v0 :=    ((v0s=0) and (v1s=0))      { bez obmedzenia     }
                         or (v0=0)                     { nepyta sa na vysku }
                         or (inRange(v0, v0s,v1s));    { pyta sa            }

                is_v1 :=    ((v0s=0) and (v1s=0))
                         or (v1=0)
                         or (inRange(v1, v0s,v1s));


                with SECTORs^[i]^ do
                  begin
                    is_b0 := ((x0<>0) and prienik_bod (mapa,nazov, x0,y0));
                    is_b1 := ((x1<>0) and prienik_bod (mapa,nazov, x1,y1));
                    is_p  := ((x0<>0) and (x1<>0) and prienik_useciek (mapa,nazov, x0,y0,x1,y1, x,y));

                    if (not is_p) {and patri} then
                       if is_b0 then begin x:= x0; y:= y0 end
                       else if is_b1 then begin x:= x1; y:= y1 end;

                    {if is_p and is_b0 and (not is_b1) then dr0:= vzdialenost (x0,y0, x,y) else dr0:= 0;
                    if is_p and is_b1 and (not is_b0) then dr1:= vzdialenost (x1,y1, x,y) else dr1:= 0;
                    dr:= S_IN_KM; dr:= dr*1000;

                    Nemozem takto kontrolovat, lebo sektory mozu susedit
                    a bod1 nemusi byt vstupny ale vnutorny...
                    }
                    patri :=    ((is_p or (is_b0 and is_b1)) and (is_v0 or is_v1))
                             or (is_b0 and is_v0 and (not is_b1) {and (dr0>=dr)})
                             or (is_b1 and is_v1 and (not is_b0) {and (dr1>=dr)})
                             ;
                  end
              end;
           inc(i)
         end;
       cez_sektor:= patri
     end;


  function v_sektore( x0,y0 : real; vys0: word; vys0_: char;
                      x1,y1 : real; vys1: word; vys1_: char
                    ): bool;
     var   x,y: real;
     begin
       v_sektore:= cez_sektor(x0,y0,vys0,vys0_, x1,y1,vys1,vys1_, x,y)
     end;


  function vyska_v_sektore (x,y : real; v: word; v_: char; xi,yi : real): bool;
     var   i,p : int;
           v0s,v1s : word;
           patri, is_v,is_b0,is_p : bool;
           xp,yp : real;
     begin
       patri:= false;
       i:= 0; while (i<=nsec) and (not patri) do
         begin
           if (SECTORs^[i]<>nil) and (SECTORs^[i]^.is) then
              begin
                v0s := SECTORs^[i]^.vys_0;
                v1s := SECTORs^[i]^.vys_1;
                v   := get_altM(v_,v) div m_S;

                is_v:=     ((v0s=0) and (v1s=0))     { bez obmedzenia     }
                        or (v=0)                     { nepyta sa na vysku }
                        or (inRange(v, v0s,v1s));    { pyta sa            }

                if is_v then with SECTORs^[i]^ do
                  begin
                    is_b0 := ((x<>0) and prienik_bod (mapa,nazov, x,y));
                    is_p  := ((x<>0) and (xi<>0) and prienik_useciek (mapa,nazov, x,y,xi,yi, xp,yp));

                    patri := (is_p or is_b0)
                  end
              end;
           inc(i)
         end;
       vyska_v_sektore:= patri
     end;



  { dynamicke nastavenie/vrati, ci len bude/je/este je v riadenom sektore
  }(*
  function let_v_sektore(plan: pointer; func: TFunc_Txy; T0,T1: real): bool;
     var   x0,y0, x1,y1 : real;
     begin
       let_v_sektore:= true;
       if {(func=nil) or} (plan=nil) then Exit;
       if (not func(plan, T0,x0,y0)) or (not func(plan, T1,x1,y1)) then Exit;
       let_v_sektore:= v_sektore(x0,y0,x1,y1);
     end;
  *)

  { vrati, ci len pretina riadeny sektor
  }
  function let_cez_sektor(trat: pointer; bodov: int;
                          trat_x,trat_y: PRFunc_p; vys_S: PWFunc_p
                         ): bool;
     var   x0,y0,x1,y1 : real;
           v0,v1       : word;
           v0_,v1_     : char;
           patri       : bool;
           i           : int;
     begin
       let_cez_sektor:= true;
       if (trat=nil) or (trat_x=nil) or (trat_y=nil) then Exit;

       i:= 0; patri:= false;
       while (not patri) and (i<bodov) do
         begin
           x0 := TRFunc_pi(trat_x)(trat,i);
           y0 := TRFunc_pi(trat_y)(trat,i);
           v0 := TWFunc_pi(vys_S) (trat,i) div m_S;
           v0_:= altS;
           if (i<bodov-1) then
              begin
                x1 := TRFunc_pi(trat_x)(trat,i+1);
                y1 := TRFunc_pi(trat_y)(trat,i+1);
                v1 := TWFunc_pi(vys_S) (trat,i+1);
                v1_:= altS;
              end
           else begin
                  x1 := 0;
                  y1 := 0;
                  v1 := high(word);
                  v1_:= altS
                end;
           patri:= v_sektore(x0,y0,v0,v0_, x1,y1,v1,v1_);
           inc(i)
         end;

       let_cez_sektor:= patri
     end;

{$ENDIF}