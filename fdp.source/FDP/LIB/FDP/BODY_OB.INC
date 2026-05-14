{ -------------------
   vyhladanie bodu
  -------------------
}

{ body trati LPS, ich oddelenie je uz archaizmom
}

 function is_NDB_EQ(kod_X, kod: string): bool;
    var   i1,i2 : int;
          bres  : bool;
    begin
      is_NDB_EQ:=     (kod<>'')
                  and (   (kod_X = kod)
                       {$IFDEF FIND_EQ_NDB}
                        or (     (NDB_EQ)
                             and (delchar(kod_X,setPism)='') { nebol to OB (302) ani kod LDM (V545) }
                             and ((pos(kod_X,kod)>0) or (pos(kod,kod_X)>0))
                           )
                       {$ENDIF}
                      )
                  ;
    end;

 function is_OB_EQ(kod_X, kod: string): bool;
    var   B1,B2 : TOBxy;
          bres  : bool;
    begin
      bres:=      (kod<>'')
              and (   is_NDB_EQ(kod_X,kod)
                   or (    get_OB_XYM(kod_X,B1)
                       and get_OB_XYM(kod,B2)
                       and (B1.x=B2.x)
                       and (B1.y=B2.y)
                      )
                  )
            ;
      is_OB_EQ:= bres
    end;


 function TaBody._OBind(kod: string; var Bi: TsBod): int;
    var   i : int;
    begin
      _OBind:= -1;
      kod:= l4str(kod);
      if kod='' then Exit;
      for i:= 0 to pocet-1 do
        begin
          read(i,Bi);
          if    (Bi.kod=kod)
             or (Bi.ine.icao_kod=kod)
             or is_NDB_EQ(kod,Bi.kod) then
             begin
               _OBind:= i;
               Exit
             end
        end
    end;

 function _OBind_ (kod: string; B: PaBody; var Bi: TsBod): int;
    begin
      if (B<>nil) then _OBind_:= B^._OBind(kod,Bi)
      else _OBind_:= -1
    end;

 function _OBind (kod: string; B: PaBody): int;
    var   Bi: TsBod;
    begin
      if (B<>nil) then _OBind:= B^._OBind(kod,Bi)
      else _OBind:= -1
    end;


 function _OBindBi (ind: int; B: PaBody; var Bi: TsBod): bool;
    begin
      if (ind>-1) and (B<>nil) then
         begin
           _OBindBi:= true;
           B^.read(ind, Bi);
         end
      else begin
             _OBindBi:= false;
             fillchar(Bi,sizeof(Bi),0)
           end;
    end;


{ vyhladania
}
 function is_OBind(kod: string): bool;
    var   B: TOBxy;
    begin
      fillchar(B,sizeof(B),0);
      is_OBind:= get_OB_XY(kod, B)
    end;


{ najdenie civilneho bodu
}

 function is_OB (kod: string; var B: TsBod; vsetky: bool): bool;
    var   ires : int;
    begin
      kod:= l4str(getstr(kod,1,[icao_NXT]));
      fillchar(B,sizeof(B),0);                           { musi ostat }

      ires:= _OBind_(kod, OB,B);
      if ires<0 then ires:= _OBind_(kod, LK,B);
      if (ires<0) and vsetky and is_VOR_or_ZS (kod,B) then ires:= 0;

      is_OB:= ires>=0
    end;


 function get_OB_XY(kod: string; var B: TOBxy): bool;
    var   Bi   : TsBod;
          ires : int;
          o    : bool;
    begin
      o:= NDB_EQ;

      {fillchar(B,sizeof(B),0); -> nesmie, bod uz moze byt spracovavany... }
      B.kod:= kod;
      B.x:= 0; B.y:= 0;

     { NDB ?
     }
      ires:= _OBind_(kod, OB,Bi);      { bolo LK, ale OB obsahuje i LK }
      if ires>=0 then
         begin
           B.x:= Bi.x;
           B.y:= Bi.y
         end;


     { AIP-C ?
     }
      if ires<0 then
         begin
           ires:= _OBind_(kod, LK,Bi);
           if ires>=0 then
              begin
                B.x:= Bi.x;
                B.y:= Bi.y
              end
         end;

      {$IFDEF FIND_EQ_NDB}
       if (ires<0) and (not NDB_EQ) then
          begin
            NDB_EQ:= true;
            ires:= _OBind_(kod, OB,Bi);
            if ires>=0 then
               begin
                 B.x:= Bi.x;
                 B.y:= Bi.y
               end
          end;
      {$ENDIF}


     { VOR ?
     }
      if (ires<0) and is_VOR (kod,B.x,B.y) then ires:= 0;

      get_OB_XY:= ires>=0;

      NDB_EQ:= o
    end;


{ najdenie vojenskeho bodu
}
 function get_OB_XYM(kod: string; var B: TOBxy): bool;
    var   Bi   : TsBod;
          ires : int;
    begin

     { NDB, AIP-C, VOR ?
     }
      if get_OB_XY(kod,B) then ires:= 0
      else ires:= -1;

     { AIP-M ?
     }
      if ires<0 then
         begin
           ires:= _OBind_(kod, LK_m,Bi);
           {if ires<0 then ires:= _OBind_(_cairbase(kod), LK_m,Bi);
           if ires<0 then ires:= _OBind_(_mairbase(kod), LK_m,Bi);}
           if ires>=0 then
              begin
                B.x:= Bi.x;
                B.y:= Bi.y
              end
         end;

     { OB ?
     }
      if ires<0 then
         begin
           ires:= _OBind_(kod, OB_m,Bi);
           if ires>=0 then
              begin
                B.x:= Bi.x;
                B.y:= Bi.y
              end
         end;


      if ires<0 then

     { LDM ?
     }
        if is_LDM(kod) then
           begin
             LDMtoReal(kod, B.x,B.y);
             B.kod:= kod;
             ires:= 0
           end

     { ZemSur ?
     }
        else if ZemSurToReal(kod, B.x,B.y) then
           begin
             B.kod:= kod_ZSxy;
             ires:= 0
           end;

      get_OB_XYM:= ires>=0
    end;


{ function get_BOD_XY(kod: string; var BOD: TOBxy): bool;
    var   r: bool;
    begin
      r:= get_OB_XYM(kod, BOD);
      get_BOD_XY:= r
    end;
}

