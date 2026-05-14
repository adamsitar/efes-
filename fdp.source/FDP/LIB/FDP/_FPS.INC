 procedure new_FPS (FPS1,FPS2: PFPS); far;
     begin
       FillChar(FPS2^,SizeOf(FPS2^),0);
       if FPS1<>nil then
          begin
            FPS2^:= FPS1^;
            FPS2^.flo:= StrNew(FPS1^.flo);
            FPS2^.opr:= StrNew(FPS1^.opr);
            FPS2^.reg:= StrNew(FPS1^.reg);
          end
     end;

 procedure disp_FPS (FPS: PFPS); far;
     begin
       with FPS^ do
         begin
           StrDispose(flo);
           StrDispose(opr);
           StrDispose(reg)
         end
     end;


 procedure format_FPS(FPS: PFPS); far;
     var   B1,B2: TOBxy;
           x: real;
     begin
       with FPS^ do
         begin
           dr:= 0; dr_:= '';
           (*if is_OB(FPD.dep,B1,true) then dr_:= #24{hd_DEP};
           if is_OB(FPD.arr,B2,true) then
              begin
                {if dr_<>'' then dr_:= dr_+icao_NXT};
                dr_:= dr_+#25{hd_ARR}
              end;
           if dr_='' then*)
           if get_OB_XYM (fdr.eet.kod, B1) and get_OB_XYM (fdr.exi.kod, B2) then
              begin
                x:= vzdialenost(B1.x,B1.y, B2.x,B2.y) / 1000;
                dr:= trunc(x)
              end
           else dr_:= '?'
         end
     end;

 function _valid_FPS(FPS: PFPS; s: Pstring): bool; far;
    begin
      _valid_FPS:= mtks_rus_to_lat(FPS^.fdr.stat)<>hd_CNL
    end;


 function eq_FPS (FPS1,FPS2: PFPS): bool; far;
    begin
      eq_FPS:=      ((FPS1<>nil) and (FPS2<>nil))
                and (codekey_FPS(FPS1) = codekey_FPS(FPS2))
    end;

 function chg_FPS (FPS1,FPS2: PFPS): bool; far;
    begin
      chg_FPS:=
                (   chg_AP_ (FPS1^.fdr.dep,FPS2^.fdr.dep)
                 or chg_OB_ (FPS1^.fdr.eet,FPS2^.fdr.eet)
                 or chg_OB_ (FPS1^.fdr.exi,FPS2^.fdr.exi)
                 or chg_AP_ (FPS1^.fdr.arr,FPS2^.fdr.arr)
                 or (FPS1^.fdr.typ <>FPS2^.fdr.typ)
                 or (FPS1^.fdr.stat<>FPS2^.fdr.stat)
                )
    end;


