procedure AP_to_OBxy(APi: TAP; var OBxy: TOBxy);
    begin
      fillchar(OBxy,0,sizeof(OBxy));
      OBxy.kod  := APi.kod;
      OBxy.h    := APi.h;
      OBxy.m    := APi.m;
      OBxy.casA := APi.cas;
      OBxy.casD := APi.cas
    end;


procedure BOD_to_OBxy (OBi: TsBod; var OBxy: TOBxy);
    begin
      fillchar(OBxy,0,sizeof(OBxy));
      OBxy.kod := OBi.kod;
      OBxy.x   := OBi.x;
      OBxy.y   := OBi.y
    end;


procedure OB_to_OB_(OB: TOB; var OBi: TOB_);
    begin
      fillchar(OBi,0,sizeof(OBi));
      OBi.kod  := OB.kod;
      OBi.h    := OB.h;
      OBi.m    := OB.m;
      OBi.cas  := OB.cas;
      OBi.vys  := OB.vys;
      OBi.vysab:= OB.vysab;
    end;

procedure OB_to_OBxy(OBi: TOB; var OBxy: TOBxy);
    var   B: TsBod;
    begin
      fillchar(OBxy,0,sizeof(OBxy));
      OBxy.kod  := OBi.kod;
      OBxy.h    := OBi.h;
      OBxy.m    := OBi.m;
      OBxy.casA := OBi.cas;
      OBxy.casD := OBi.cas;
      OBxy.vys  := OBi.vys;
      OBxy.vys_ := vysOB;   {OB.vys_}
      if OBi.ind>=0 then
         begin
           OB^.read(OBi.ind,B);
           OBxy.x:= B.x;
           OBxy.y:= B.y
         end
    end;

procedure OB__to_OBxy(OBi: TOB_; var OBxy: TOBxy);
    begin
      fillchar(OBxy,0,sizeof(OBxy));
      get_OB_XYM (OBxy.kod, OBxy);
      OBxy.kod  := OBi.kod;
      OBxy.h    := OBi.h;
      OBxy.m    := OBi.m;
      OBxy.casA := OBi.cas;
      OBxy.casD := OBi.cas;
      OBxy.vys  := OBi.vys;
      OBxy.vys_ := vysOB;   {OB.vys_}
    end;


procedure OBxy_to_OB(OBxy: TOBxy; var OBi: TOB);
    begin
      fillchar(OBi,0,sizeof(OBi));
      OBi.kod  := OBxy.kod;
      OBi.h    := OBxy.h;
      OBi.m    := OBxy.m;
      OBi.cas  := OBxy.casA;
      OBi.vys  := _vys_OB(OBxy.vys,OBxy.vys_);
      OBi.vysab:= OBxy.vysab;
      OBi.ind  := _OBind (OBxy.kod,OB)
    end;

procedure OBxy_to_OB_(OBxy: TOBxy; var OBi: TOB_);
    begin
      fillchar(OBi,0,sizeof(OBi));
      OBi.kod  := OBxy.kod;
      OBi.h    := OBxy.h;
      OBi.m    := OBxy.m;
      OBi.cas  := OBxy.casA;
      OBi.vys  := _vys_OB(OBxy.vys,OBxy.vys_);
      OBi.vysab:= OBxy.vysab;
    end;

procedure OBxy_to_AP_ (OBxy: TOBxy; var APi: TAP_);
    begin
      fillchar(APi,0,sizeof(APi));
      APi.kod  := OBxy.kod;
      APi.h    := OBxy.h;
      APi.m    := OBxy.m;
    end;


procedure  AP_to_OB_ (APi: TAP; var OB: TOB_);
    begin
      fillchar(OB,sizeof(OB),0);
      OB.kod := APi.kod;
      OB.h   := APi.h;
      OB.m   := APi.m;
      OB.cas := APi.cas;
      OB.vysab := ' '
    end;

