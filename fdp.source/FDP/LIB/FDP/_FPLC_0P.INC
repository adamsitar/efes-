 procedure new_cFPL (FPL1,FPL2: PDcFPL);
     begin
       FillChar(FPL2^,SizeOf(DcFPL),0);
       if FPL1<>nil then
          begin
            FPL2^:= FPL1^;
          end
     end;

 function new_cFPL_ (FPL1: PDcFPL; var FPL2: PDcFPL): PDcFPL;
    begin
      new(FPL2);
      new_cFPL(FPL1, FPL2);
      new_cFPL_:= FPL2
     end;


 procedure disp_cFPL (FPL: PDcFPL);
     begin
     end;

 procedure disp_cFPL_ (var FPL: PFPLC);
     begin
       if FPL=nil then Exit;
       disp_cFPL(FPL);
       dispose(FPL);
       FPL:= nil
     end;


 procedure copy_cFPL_(FPL1, FPL2: PDcFPL; new_plan: bool);
     begin
       new_cFPL (FPL1,FPL2);
       with FPL2^ do
         begin
           if new_plan then
              begin
               {$IFDEF RDP}
                TRG:= _cor; RDP:= 0;
               {$ENDIF}
                fillchar(przn,sizeof(przn),0);
              end;

           {$IFDEF MAPY}
             mapa:= nil;
           {$ENDIF}

           {$IFDEF NET}
            fillchar(rec,sizeof(rec),0)
           {$ENDIF}
         end
     end;


