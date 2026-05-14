{ -----------------
   TPoly
  -----------------
}

destructor TPoly.Done;
  begin
    if ZozBod<>nil then Dispose(ZozBod,Done);
    if GP <> nil then Dispose(GP,Done)
  end;

procedure RW_Poly(RW: byte; var f: File; var Zd,Zs: TZdZs);
    var   res : word;
    begin
      _BlockRW(RW, f,Zd, Sizeof(TZdZs),res);
      _BlockRW(RW, f,Zs, Sizeof(TZdZs),res)
    end;

procedure TPoly.readGrOb(var _InF: file);
    var   PB    : PGBod;
          Zd,Zs : TZdZs;
          res   : word;
          pom   : int;
    begin
      inherited readGrOb(_InF);
      ZozBod:= nil;
      BlockRead(_InF,pocet,SizeOf(pocet),res);

      if pocet>=1 then
         begin
           ZozBod:= New(PZozBod,Init);
           pom:= 0;
           with ZozBod^ do
             repeat
               New(PB);
               RW_Poly(0, _InF, Zd,Zs);
               ZdZs_xy(Zd,Zs, PB^.X,PB^.Y);

               if pom=0 then
                  begin { inicializacia na zaciatku }
                    Bmax.X:= PB^.X; Bmax.Y:= PB^.Y;
                    Bmin.X:= PB^.X; Bmin.Y:= PB^.Y
                  end
               else begin  { zistenie maximalneho a minimalneho bodu }
                     if PB^.X > Bmax.X then Bmax.X := PB^.X;
                     if PB^.Y > Bmax.Y then Bmax.Y := PB^.Y;
                     if PB^.X < Bmin.X then Bmin.X := PB^.X;
                     if PB^.Y < Bmin.Y then Bmin.Y := PB^.Y
                   end;
               PridejNaKonec(PB);

               inc(pom)
             until pom>=pocet
           end
    end;

procedure TPoly.writeGrOb(var _OuF: file; _header: bool);
    var   PB     : PGBod;
          Zd,Zs  : TZdZs;
          res    : word;
          i      : int;
          koniec : bool;
    begin
      if _header then
         begin
           inherited writeGrOb(_OuF,_header);
           BlockWrite(_OuF,pocet,SizeOf(pocet),res);
         end;
      ZozBod^.JdiNaZacatek;
      for i:= 0 to pocet-1 do
        begin
          PB:= ZozBod^.DejAktPrvek;
          xy_ZdZs(PB^.X,PB^.Y,Zd,Zs);
          RW_Poly(1, _OuF, Zd,Zs);
          ZozBod^.JdiNaDalsi(koniec);
        end
    end;

{
  Ak som v ploche, polpriamka pretne jej hranice
  neparnypocetkrat :
}
function TPoly.is_in(_Zd,_Zs : TZdZs): bool;
  var    koniec, prienik       : bool;

         i, usecky, prienikov  : int;
         polA, polB            : int;

         PA,PB, bodm  : TGBod;
         PPB,PP0      : PGBod;

         pomx,dx      : real;

  function pocitaj_prienik: bool;
     begin
       pocitaj_prienik:= false;
       if ZozBod=nil then Exit;

       PPB := ZozBod^.DejAktPrvek;
       PB.X:= PPB^.X-Bodm.X;
       PB.Y:= PPB^.Y-Bodm.Y;
       if (PB.X=0) and (PB.Y=0) then
          begin
            pocitaj_prienik:= true;
            Exit
          end;

       polB:= 0;
       if PB.X>=0. then polB := polB or $0001;
       if PB.Y>=0. then polB := polB or $0010;

       if ((polA+polB) and $0010) = $0010 then
          begin
          { body v opacnych polrovinach "y"
          }
            if ((polA and $0001)=$0001) and ((polB and $0001)=$0001) then
                 begin
                  { A, B v kladnej polrovine X, v opacnej Y }
                    inc(prienikov)
                 end
            else begin
                   pomx := (PB.Y-PA.Y);
                   if pomx<>0 then pomx := PA.Y*(PB.X-PA.X)/pomx else pomx:= 0;
                   if (((polA and $0001)=$0001) or ((polB and $0001)=$0001))
                      and (PA.x >= pomx) then { existuje prienik v x+ }
                          inc(prienikov)
                 end
          end;

       PA:= PB; polA:= polB
     end;

  begin
    is_in:= False;
    if ZozBod=nil then Exit;

    ZdZs_xy(_Zd,_Zs, bodm.X,bodm.Y);
    if (pocet<3) or (Bodm.X>Bmax.X) or (Bodm.X<Bmin.X) or (Bodm.Y>Bmax.Y) or (Bodm.Y<Bmin.Y) then Exit;

    prienikov:= 0;
    prienik:= false;

    ZozBod^.JdiNaZacatek;
    PP0:= ZozBod^.DejAktPrvek;
    ZozBod^.JdiNaKonec;
    PPB:= ZozBod^.DejAktPrvek;
    if (PPB^.X<>PP0^.X) or (PPB^.Y<>PP0^.Y) then usecky:= pocet+1
    else usecky:= pocet;

    ZozBod^.JdiNaZacatek;
    PPB:= ZozBod^.DejAktPrvek;
    PP0:= PPB;
    PA.X := PPB^.X-Bodm.X;
    PA.Y := PPB^.Y-Bodm.Y;
    if (PA.X=0) and (PA.Y=0) then prienik:= true;
    polA := 0;
    if PA.X>=0. then polA := polA or $0001;
    if PA.Y>=0. then polA := polA or $0010;
    ZozBod^.JdiNaDalsi(koniec);

    i:= 1; koniec:= false;
    while (i<usecky) and (not prienik) {and (not koniec)} do
      begin
        if i=pocet then ZozBod^.JdiNaZacatek;
        prienik:= pocitaj_prienik;
        ZozBod^.JdiNaDalsi(koniec);
        inc(i)
      end;

    is_in:= (prienik) or ((prienikov and $0001)=$0001)
  end; { is_in }

(*
// ak p sa nachadaza v polygone funkcia vrati 1, inac vrati 0
int Ppolygon::is_in(Bodm &p)
{
   if(poc<3) return 0;
   if(p.x>=Bmax.x  ||
      p.x<=Bmin.x  ||
      p.y>=Bmax.y  ||
      p.y<=Bmin.y   )
      return 0;

   int i,usecky,prienik=0;
   uint polA,polB;  // polohy bodov
   #ifndef MEM_POLY
   //pbm.FileOpen();
   pbm.Open("rb");
   #endif  RAMDISK_POLY

   if(pbm[0].x!=pbm[poc-1].x || pbm[0].y!=pbm[poc-1].y)
      usecky=poc+1;
   else
      usecky=poc;

   TVectorXY PA(pbm[0].x-p.x,pbm[0].y-p.y),PB;
   polA=0;
   if(PA.x>=0) polA |= 0x0001;
   if(PA.y>=0) polA |= 0x0010;

   for(i=1;i<usecky;i++)
   {
      if(i==poc)
      {
         PB.x=pbm[0].x-p.x;
         PB.y=pbm[0].y-p.y;
      }
      else
      {
         PB.x=pbm[i].x-p.x;
         PB.y=pbm[i].y-p.y;
      }
      polB=0;
      if(PB.x >= 0.)
         polB |= 0x0001;
      if(PB.y >= 0.)
         polB |= 0x0010;
      if((polA+polB)&0x0010)   // body A,B v opacnych polrovinach y
      {
         if((polA&0x0001) && (polB&0x0001))     // A, B v kladnej polrovine x
            prienik++;
         else if (((polA&0x0001) || (polB&0x0001)) &&  PA.x >= PA.y*(PB.x-PA.x)/(PB.y-PA.y))
            prienik++;
      }

      PA   = PB;
      polA = polB;
   }
   #ifndef MEM_POLY
   //pbm.FileClose();
   pbm.Close();
   #endif  RAMDISK_POLY
   if(prienik&0x0001)  // neparny
      return 1;
   else
      return 0;
}
*)

{ ZdZs1 - suradnice zaciatocneho bodu,
  ku ktoremu je hladany prienik
}
function TPoly.is_cut(zdA,zsA,zdB,zsB: TZdZs;
                      var in1,in2, is1,is2: bool;
                      var zd1,zs1,          { prvy prienik }
                          zd2,zs2: TZdZs    { dalsi prienik }
                     ): bool;

   var   koniec, prienik : bool;
         i, usecky : int;
         PP0,PPB : PGBod;
         A,B,X1,X2,Xi,X : TGBod;
         U : TOLine;

   begin
     is_cut:= TGrOb.is_cut(zdA,zsA,zdB,zsB, in1,in2,is1,is2, zd1,zs1,zd2,zs2);
     if (ZozBod=nil) or (pocet<2) then Exit;

     zdzs_xy (zdA,zsA, A.x,A.y);
     zdzs_xy (zdB,zsB, B.x,B.y);
     U.Init  (A.x,A.y, B.x,B.y);

     fillchar(X1,sizeof(X1),0);
     fillchar(X2,sizeof(X2),0);

     ZozBod^.JdiNaZacatek;
     PP0:= ZozBod^.DejAktPrvek;
     ZozBod^.JdiNaKonec;
     PPB:= ZozBod^.DejAktPrvek;
     if (PPB^.X<>PP0^.X) or (PPB^.Y<>PP0^.Y) then usecky:= pocet+1
     else usecky:= pocet;

     ZozBod^.JdiNaZacatek;
     PP0:= ZozBod^.DejAktPrvek;
     ZozBod^.JdiNaDalsi(koniec);
     i:= 1; koniec:= false; prienik:= false;
     while (i<usecky) {and (not koniec)} do
       begin
         if i=pocet then ZozBod^.JdiNaZacatek;
         PPB:= ZozBod^.DejAktPrvek;
         if U.pretina(PP0^.x,PP0^.y,PPB^.x,PPB^.y, @Xi.x,@Xi.y) = pgo_prienik then
            begin
              if is1 then is2:= true
              else is1:= true;
              if is2 then
                 if blizsi_bod_xy(A.x,A.y, Xi.x,Xi.y,X1.x,X1.y, X.x,X.y) then
                    begin
                      X2:= X1;
                      X1:= Xi
                    end
                 else X2:= Xi
              else X1:= Xi;
              prienik:= true
            end;
         PP0:= PPB;
         ZozBod^.JdiNaDalsi(koniec);
         inc(i)
       end;

     if prienik then
        begin
          if is1 then xy_ZdZs(X1.x,X1.y, zd1,zs1);
          if is2 then xy_ZdZs(X2.x,X2.y, zd2,zs2);
        end;

     in1:= is_in(zdA,zsA);
     in2:= is_in(zdB,zsB);

     U.Done;

     is_cut:= prienik
   end;


{$IFDEF DRAW}
   procedure TPoly.mapa_draw;
       var   PB  : PGBod;
             X,Y : long;
       begin
         if ZozBod=nil then Exit;

         ZozBod^.JdiNazacatek;
         PB:= ZozBod^.DejAktPrvek;
         BodXY(PB, X,Y);
         MoveTo(X,Y);
         repeat
           PB := ZozBod^.DejAktPrvek;
           BodXY(PB, X,Y);
           LineTo(X,Y);
           {getkey;}
         until ZozBod^.JdiNaDalsi_
       end;

  procedure TPoly.mapa_fill;
      var   PB       : PGBod;
            Poly     : Pints;
            Points,i : int;
            X,Y      : long;
      begin
        if ZozBod=nil then Exit;

        ZozBod^.JdiNazacatek;
        Points:= Minimum(max_FillPoly,ZozBod^.DejPocet);
        GetMem(Poly,sizeof(int)*Points*2);
        i:= 0;
        repeat
          PB:= ZozBod^.DejAktPrvek;
          BodXY(PB, X,Y);
          Poly^[i]:= X; Poly^[i+1]:= Y;
          inc(i,2)
        until ZozBod^.JdiNaDalsi_ or (i>=Points*2);
        FillPoly(Points, Poly^);
        FreeMem(Poly,sizeof(int)*Points*2)
      end;
{$ENDIF}



{ -----------------
   TFillPoly
  -----------------
}
procedure TFillPoly.readGrOb(var _InF: file);
    begin
      inherited readGrOb(_InF);
      fill:= _fill_
    end;



{ -----------------
   TTPoly
  -----------------
}
constructor TTPoly.Init(_Trat: POBxys; _pocet: int; _MapCl: byte);
      var   PB    : PGBod;
            Zs,Zd : TZdZs;
            res   : word;
            pom   : int;
      begin
        GP := nil;
        kod:= gr_TPoly; fill:= _draw_;
        SetGrObPar(0,_MapCl,0);
        pocet:= _pocet;
        ZozBod:= nil;

        if pocet>=1 then
           begin
             ZozBod:= New(PZozBod,Init);
             pom:= 0;
             with ZozBod^ do
               repeat
                 New(PB);
                 PB^.X:= _Trat^[pom].x;
                 PB^.Y:= _Trat^[pom].y;
                 if pom=0 then
                    begin { inicializacia na zaciatku }
                      Bmax.X:= PB^.X; Bmax.Y:= PB^.Y;
                      Bmin.X:= PB^.X; Bmin.Y:= PB^.Y
                    end
                 else begin  { zistenie maximalneho a minimalneho bodu }
                       if PB^.X > Bmax.X then Bmax.X := PB^.X;
                       if PB^.Y > Bmax.Y then Bmax.Y := PB^.Y;
                       if PB^.X < Bmin.X then Bmin.X := PB^.X;
                       if PB^.Y < Bmin.Y then Bmin.Y := PB^.Y
                     end;
                 PridejNaKonec(PB);

                 Inc(pom)
               until pom>=pocet
           end
      end; { Init }
