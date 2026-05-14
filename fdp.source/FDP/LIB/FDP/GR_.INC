procedure TZozBod.ZrusPointer(P: pointer);
    begin
      Dispose(PGBod(P))
    end;

procedure TZozText.ZrusPointer(P: pointer);
    begin
      StrDispose(PGText(P)^.vet);
      Dispose(PGText(P))
    end;

procedure TZozMap.ZrusPointer(P : pointer);
    begin
      dispose_MapOb(PTMapOb(P))
    end;


{$IFDEF MAPY}
  procedure _BodXY_(Bod: PGBod; var X,Y: long);
      begin
        X:= 0; Y:= 0
      end;
{$ENDIF}


function mapa_farba(prior: word): word;
   begin
     case prior of
       map_FIRf    : mapa_farba :=  cl_FIRf;
       map_FIR     : mapa_farba :=  cl_FIR;

       map_ACCf    : mapa_farba :=  cl_ACCf;
       map_ACC     : mapa_farba :=  cl_ACC;
       map_ACCsecf : mapa_farba :=  cl_ACCsecf;
       map_ACCsec  : mapa_farba :=  cl_ACCsec;

       map_APPf    : mapa_farba :=  cl_APPf;
       map_APP     : mapa_farba :=  cl_APP;
       map_APPsecf : mapa_farba :=  cl_APPsecf;
       map_APPsec  : mapa_farba :=  cl_APPsec;

       map_AWYf    : mapa_farba :=  cl_AWYf;
       map_AWY     : mapa_farba :=  cl_AWY;
       map_AWY_    : mapa_farba :=  cl_AWY_;
       map_ILS_    : mapa_farba :=  cl_ILS_;

       map_TMAf    : mapa_farba :=  cl_TMAf;
       map_TMA     : mapa_farba :=  cl_TMA;

       map_CTRf    : mapa_farba :=  cl_CTRf;
       map_CTR     : mapa_farba :=  cl_CTR;

       map_ZAMp    : mapa_farba :=  cl_ZAMp;
       map_ZAMa    : mapa_farba :=  cl_ZAMa;

       map_Rf      : mapa_farba :=  cl_Rf;
       map_R       : mapa_farba :=  cl_Rf;

       map_TSAp    : mapa_farba :=  cl_TSAp;
       map_TSAa    : mapa_farba :=  cl_TSAa;

       map_PRSp    : mapa_farba :=  cl_PRSp;
       map_PRSa    : mapa_farba :=  cl_PRSa;

       map_Pf      : mapa_farba :=  cl_Pf;
       map_P       : mapa_farba :=  cl_P;

       map_PAV0    : mapa_farba :=  cl_PAV0;
       map_PAV1    : mapa_farba :=  cl_PAV1;

       map_LDM0    : mapa_farba :=  cl_LDM0;
       map_LDM1    : mapa_farba :=  cl_LDM1;
       map_LDM2    : mapa_farba :=  cl_LDM2;

       map_MARK    : mapa_farba :=  cl_MARK;
       map_DESC    : mapa_farba :=  cl_DESC

       else          mapa_farba :=  cl_MARK
     end
   end;


function  new_GP_KruhPriestor(idn: string; polomer: int): PTMapOb;
    var   UserKruz  : TUserKruz;
          MapOb     : PTMapOb;
          B         : TOBxy;
    begin
      new_GP_KruhPriestor:= nil;
      if not get_OB_XYM(idn, B) then Exit;

      UserKruz.prior := gr_Kruz;
      UserKruz.farba := cl_R;
      UserKruz.typc  := 1;
      UserKruz.X:= B.x;
      UserKruz.Y:= B.y;
      UserKruz.R:= polomer*1000;

      MapOb:= new_MapOb(idn,map_TMA, 0,0,cl_R, true,true);
      MapOb^.GP:= New(PTKruz,Define(0,@UserKruz,0,0));
      new_GP_KruhPriestor:= MapOb
    end;
