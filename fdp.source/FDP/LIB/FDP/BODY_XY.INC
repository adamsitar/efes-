 procedure cas_suradnice_a_vyska_tratOBxy (trat: POBxys; bodov,bod: int; var cas,x,y: real; var vys: word);
    begin
      suradnice_a_vyska_tratOBxy (trat, bodov,bod, x,y, vys);
      if bod < bodov then cas:= trat^[bod].casA
      else cas:= 0
    end;

 procedure suradnice_a_vyska_tratOBxy (trat: POBxys; bodov,bod: int; var x,y: real; var vys: word);
    begin
      if bod < bodov then
         begin
           x:= trat^[bod].x; y:= trat^[bod].y;
           vys:= get_altM(trat^[bod].vys_,trat^[bod].vys);
         end
      else begin
             x:= 0; y:= 0;
             vys:= alt_UNL
           end;
    end;

 procedure suradnice_a_vyska_tratBOD  (trat: PTrat;  bodov,bod: int; var x,y: real; var vys: word);
    var    Bi: TsBod;
    begin
      x:= 0; y:= 0; vys:= alt_UNL;
      if bod < bodov then
         begin
           if (trat^[bod].ind>-1) then
              begin
                OB^.read(trat^[bod].ind,Bi);
                x:= Bi.x;
                y:= Bi.y;
              end;
           vys:= get_altM(vysOB,trat^[bod].vys);
         end
    end;
