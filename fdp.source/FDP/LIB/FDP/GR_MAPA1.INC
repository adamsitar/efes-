
 function transformacia_priority(naz: string; typ: word): word;
    begin
     { Povodne hodnoty,
       nenastavene spravne sa musia transformovat
       kvoli spravnemu poradiu map
     }
      if PRTY0 then
        if (typ=map_P) or (is_P(naz) and ((typ=_map_P) or (typ=_map_Pf))) then typ:= map_Pf
        else case typ of
          _map_FIRf   : typ:= map_FIRf;
          _map_FIR    : typ:= map_FIR;

          {_map_ACCf   : typ:= map_ACCf;
          _map_ACC    : typ:= map_ACC;
          _map_ACCsecf: typ:= map_ACCsecf;
          _map_ACCsec : typ:= map_ACCsec;

          _map_APPf   : typ:= map_APPf;
          _map_APP    : typ:= map_APP;
          _map_APPsecf: typ:= map_APPsecf;
          _map_APPsec : typ:= map_APPsec;}

          _map_AWYf   : typ:= map_AWYf;
          _map_AWY    : typ:= map_AWY;
          _map_ILS_   : typ:= map_ILS_;
          _map_AWY_   : typ:= map_AWY_;


          _map_TMAf   : typ:= map_TMA;  { naschval }
          _map_TMA    : typ:= map_TMA;

          _map_CTRf   : typ:= map_CTR;  { naschval }
          _map_CTR    : typ:= map_CTR;

          _map_Rf     : typ:= map_Rf;
          _map_R      : typ:= map_R;

          _map_Pf     : typ:= map_Pf;
          _map_P      : typ:= map_Pf;   { naschval }


          {_map_PAV0   : typ:= map_PAV0;
          _map_PAV1   : typ:= map_PAV1;}

          _map_LDM2   : typ:= map_LDM2;
          _map_LDM1   : typ:= map_LDM1;
          _map_LDM0   : typ:= map_LDM0;


          _map_MARK   : typ:= map_MARK;
        end;

      transformacia_priority:= typ
    end;


function new_MapOb(naz: string; typ,prior,ciar,cl: word; zobraz,kr: bool): PTMapOb;
   var   MapOb : PTMapOb;
   begin
     New(MapOb); FillChar(MapOb^,sizeof(MapOb^),0);

     MapOb^.naz   := naz;
     MapOb^.key   := nil;
     MapOb^.plan  := false;
     MapOb^.GP    := nil;

     MapOb^.kr_   := zobraz;
     if zobraz then MapOb^.kr:= true else MapOb^.kr:= kr;

     MapOb^.typ   := transformacia_priority(naz,typ);
     MapOb^.prior := transformacia_priority(naz,typ);
     MapOb^.ciar  := ciar;

     if cl<>0 then MapOb^.cl := cl
     else MapOb^.cl := mapa_farba(MapOb^.prior);
     {MapOb^.pocet := 0;}

     new_MapOb := MapOb
   end;


procedure dispose_MapOb(var MapOb: PTMapOb);
    begin
      if MapOb<>nil then
         begin
           if MapOb^.key<>nil then StrDispose(MapOb^.key);
           if MapOb^.GP<>nil then Dispose(MapOb^.GP,Done);
           Dispose(MapOb); MapOb:= nil
         end
    end;


{ --------------------
   Inicializacia map
  --------------------
}
constructor TMapy.Init;
      begin
        Mapy:= New(PZozMap,Init)
      end; { Init }


constructor TMapy.Init0;
      begin
        Mapy:= nil
      end; { Init }


destructor TMapy.Done;
     begin
       if Mapy<>nil then Dispose(Mapy,Done)
     end; { Done }



{ -----------------------------------------------------------

}
procedure TMapy.zotried_mapy;
    begin
      mapy_zotried_mapy(Mapy)
    end;

procedure TMapy.nacitaj_suradnice(var _InF: file; var _MapOb: TMapOb; var _lastGrOb: PTGrOb);
    var   kod : TtypGRP;
    begin
      mapy_nacitaj_suradnice(_InF,_MapOb,_lastGrOb,kod)
    end;

function  TMapy.nacitaj_subor(subor: string): PTMapOb;
    begin
      nacitaj_subor:= mapy_nacitaj_subor(subor, Mapy, false);
      zotried_mapy
    end;

function  TMapy.najdi_a_nacitaj_subor(subor: string): PTMapOb;
   begin
     najdi_a_nacitaj_subor:= mapy_najdi_a_nacitaj_subor(subor, Mapy, false)
   end;



{ --------------------
   spracovanie map
  --------------------
}

{
  zisti, ci suradnice patria do mapy (moze byt tvorena viacerymi mapami)
  ----------------------------------
}
function TMapy.patri_zs(_Zd,_Zs: TZDZS): bool;
   var   MapOb : PTMapOb;
         res   : bool;
   begin
     res:= false;
     if Mapy^.DejPocet > 0 then
        begin
          Mapy^.JdiNaZacatek;
          repeat
            MapOb:= Mapy^.DejAktPrvek;
            res:= (MapOb^.GP<>nil) and (MapOb^.GP^.patri(_Zd,_Zs))
          until res or Mapy^.JdiNaDalsi_
        end;
     patri_zs:= res
   end;

function TMapy.patri_xy(x,y: real): bool;
   var   Zd,Zs : TZDZS;
   begin
     xy_ZdZs(x,y, Zd,Zs);
     patri_xy:= patri_zs(Zd,Zs)
   end;


{
  ak je bodov viac, vrati najblizsi bod ku pociatocnemu x1,y1
  -----------------------------------------------------------
}
function TMapy.priesecnik_xy(Ax,Ay,Bx,By: real;
                             var in1,in2, is1,is2: bool;
                             var X1,Y1, X2,Y2: real
                            ): bool;

   var   zdA,zsA,zdB,zsB, zd1,zs1,zd2,zs2: TZdZs;
         MapOb : PTMapOb;
         res   : bool;

   begin
     in1:=  false; in2:=  false;
     is1:=  false; is2:=  false;
     X1:= 0; Y1:= 0; X2:= 0; Y2:= 0;

     xy_ZdZs(Ax,Ay, zdA,zsA);
     xy_ZdZs(Bx,By, zdB,zsB);
     res:= false;
     if Mapy^.DejPocet > 0 then
        begin
          Mapy^.JdiNaZacatek;
          repeat
            MapOb:= Mapy^.DejAktPrvek;
            res:=     (MapOb^.GP<>nil)
                  and MapOb^.GP^.priesecnik(zdA,zsA,zdB,zsB,
                                            in1,in2,is1,is2,
                                            zd1,zs1, zd2,zs2
                                           )
          until res or Mapy^.JdiNaDalsi_;
          if res then
             begin
               X1:= dlzka(zd1.st,zd1.mn,zd1.se);
               Y1:= sirka(zs1.st,zs1.mn,zs1.se);
               X2:= dlzka(zd2.st,zd2.mn,zd2.se);
               Y2:= sirka(zs2.st,zs2.mn,zs2.se);
             end;
        end;
     priesecnik_xy:= res
   end;


{
  este nerobi nic
  ---------------
}
procedure TMapy.najblizsi_bod(xi,yi: real; var X,Y: real);
    begin
    end;
