{ -----------------
   TGrOb
  -----------------
}

{
  Objekt sa inicializuje pri nacitani zo subora
}
constructor TGrOb.Init(_kod: TtypGRP; var _InF : file; _farba,_typc: TparGP);
      begin
        GP:= nil;
        kod:= _kod;
        fill_en:= true; fill:= _draw_;
        setGrObPar(0,0,0);
        readGrOb(_InF); setGrObPar(-1,_farba,_typc)
      end; { Init }


constructor TGrOb.Define(_kod: TtypGRP; p: pointer; _farba,_typc: TparGP);
      begin
        GP:= nil;
        kod:= _kod;
        fill_en:= true; fill:= _draw_;
        setGrObPar(0,0,0);
        DefineGrOb(p); setGrObPar(-1,_farba,_typc)
      end; { Init }


destructor TGrOb.Done;
     begin
       if GP<>nil then Dispose(GP,Done)
     end;


{
  Naplni parametre objektu
}
procedure TGrOb.readGrOb(var _InF : file);
    var   res: word;
    begin
      fill:= _draw_;
      BlockRead(_InF,prior,SizeOf(prior),res);
      BlockRead(_InF,farba,SizeOf(farba),res);
      BlockRead(_InF,typc ,SizeOf(typc) ,res)
    end;

procedure TGrOb.WriteGrOb(var _OuF : file; _header: bool);
    var   res: word;
    begin
      if not _header then Exit;
      BlockWrite(_OuF,prior,SizeOf(prior),res);
      BlockWrite(_OuF,farba,SizeOf(farba),res);
      BlockWrite(_OuF,typc ,SizeOf(typc) ,res)
    end;


procedure TGrOb.DefineGrOb(p: pointer);
    begin
      fill:= _draw_;
    end;


procedure TGrOb.SetGrObPar(_prior,_farba,_typc: int);
    begin
      if _prior>-1 then prior:= _prior;
      if _farba>-1 then farba:= _farba;
      if _typc>-1  then typc := _typc
    end;


procedure TGrOb.SetGP(_GP: PTGrOb);
    begin
      GP:= _GP
    end;
 

{
  urci, ci bod sa nachadza v suradniciach objektu
}
function TGrOb.is_in(_Zd, _Zs: TZdZs): bool;
   begin
     is_in:= false
   end;

function TGrOb.patri(_Zd, _Zs: TZdZs): bool;
   var   p: bool;
   begin
     p:= is_in(_Zd,_Zs);
     if GP<>nil then p:= p or Gp^.patri(_Zd,_Zs);
     patri:= p
   end;


{
  vrati priesecnik usecky s hranicani priestoru
}
function TGrOb.is_cut (zdA,zsA,zdB,zsB: TZdZs;
                       var in1,in2, is1,is2: bool;
                       var zd1,zs1, zd2,zs2: TZdZs
                      ): bool;
   begin
     in1:= false; in2:= false;
     is1:= false; is2:= false;
     fillchar(zd1,sizeof(zd1),0);
     fillchar(zs1,sizeof(zs1),0);
     fillchar(zd2,sizeof(zd2),0);
     fillchar(zs2,sizeof(zs2),0);
     is_cut:= false
   end;


function TGrOb.priesecnik (zdA,zsA,zdB,zsB: TZdZs;
                           var in1,in2, is1,is2: bool;
                           var zd1,zs1, zd2,zs2: TZdZs
                          ): bool;
   var   _zd1,_zs1, _zd2,_zs2 : TZdZs;
         _in1,_in2, _is1,_is2 : bool;
         p1,p2 : bool;
   begin
     p1:= is_cut (zdA,zsA,zdB,zsB, in1,in2,is1,is2, zd1,zs1,zd2,zs2);
     if GP<>nil then
        begin
          p2:= GP^.priesecnik(zdA,zsA,zdB,zsB, _in1,_in2,_is1,_is2, _zd1,_zs1,_zd2,_zs2);
          if p2 then
             begin
               if p1 then
                  begin
                    blizsi_bod_zs(zdA,zsA, zd1,zs1,_zd1,_zd2, zd1,zs1);
                    blizsi_bod_zs(zdA,zsA, zd2,zs2,_zd2,_zd2, zd2,zs2);
                  end
               else begin
                      zd1:= _zd1; _zs1:= _zs1;
                      zd2:= _zd2; _zs2:= _zs2;
                    end;
               in1:= in1 or _in1;
               in2:= in2 or _in2;
               is1:= is1 or _is1;
               is2:= is2 or _is2;
               p1:= p1 or p2
             end;
        end;
     priesecnik:= p1 or in1 or in2 { or is1 or is2 }
   end;


{$IFDEF DRAW}
  procedure TGrOb.set_fill(_fill: TGRPfill);
      begin
        fill:= _fill
      end;

  procedure TGrOb.mapa_draw;
      begin
      end;

  procedure TGrOb.mapa_fill;
      begin
      end;

  procedure TGrOb.draw;
      var   cl: word;
      begin
        if fill=_act_ then
           begin
             mapa_fill;
             if cl_GRP_act_<>0 then
                begin
                  cl:= getcolor;
                  setcolor(cl_GRP_act_);
                  mapa_draw;
                  setcolor(cl)
                end
           end
        else if (fill=_fill_) and (not MAPSCROLL) then mapa_fill
        else {fill=_draw_} mapa_draw
      end;


  procedure TGrOb.kresli;
      begin
        draw;
        if GP <> nil then Gp^.kresli
      end;
{$ENDIF}
