{$IFDEF PROCESS_PRS}
 {
 procedure TOPRS.Spracovanie_(tit: string; _data_filter: string;
                              _handler_type: TScrollAct_handler_type;
                              _handler: pointer;
                              _handler_par : pointer;
                              _hlpXXX: Pchar
                             );
      begin
        Spracovanie(tit, @_data_filter,@_is_this_airbase,
                    _handler_type,_handler,_handler_par,
                    nil,nil,
                    _hlpXXX
                   )
      end;
 }
{$ENDIF}

{ -------------------------------
   VYKRESLENIE NA MAPE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{$IFDEF MAPY} {$IFNDEF MAPY_1.0}

  function TOPRS.get_id_map(p: pointer; count: int; var naz: string): bool;
     var   dalsi : bool;
     begin
       dalsi:= false;
       naz:= _unique_area_code(idn_PRS(p));
       if not is_TSA(naz) then
          begin
            case count of
              0 : ;
              1 : naz:= FIR+naz;
              2 : naz:= FIR+'-'+naz;
              3 : naz:= FIR+'_'+naz
              else naz:= ''
            end
          end;
       get_id_map:= naz<>'' {dalsi}
     end;

   procedure TOPRS._zobraz_plan_na_mape(p: pointer; PIS: bool);
       var   Map        : PMapData;
             boli       : bool;
             s,naz,spc  : string;
             c          : char;
             i          : int;
             L          : PList;
       label X;

       begin
         if (Mapa=nil) or (not is_map) {$IFDEF MAPY_1.0} or true {$ENDIF} then Exit;

         s:= _unique_area_code(idn_PRS(p));
         if not is_TSA(s) then
            begin
              inherited _zobraz_plan_na_mape(p,PIS);
              Exit
            end;

        { Priestor TSA, koduje sa inak...
           TSA??a..z, kde  ??    je kodove oznacenie priestoru...
                           a..z  oznacenie casti, ak nie je, pocita sa
                                 cely priestor
        } boli:= false; Map:= nil;
          naz:= _TSA_kod(s);
          spc:= copy(s,length(naz)+1,length(s)-length(naz));

        { urcenie, ktore casti priestorov patria do mapy
        }
          if spc='' then
             begin
               Map:= _zapni_mapu(p,naz,nil,PIS);
               if Map=nil then
                  begin
                    L:= New(PList,Init(@fnTSA,'',[],1,false,nil,true));
                    for c:= 'A' to 'Z' do if L^.is_in(naz+c)>-1 then spc:= spc+c;
                    Dispose(L,Done)
                  end;
               if (Map=nil) and (spc='') then
                  begin
                    _nenajdena_mapa_pre_plan(p,naz,tit_GrOb);
                    Exit
                  end
             end;

        { vykreslenie jednotlivych casti priestorov
        }
          for i:= 1 to length(spc) do
            begin
              Map:= _zapni_mapu(p,naz+spc[i],nil,PIS);
              if Map=nil then _nenajdena_mapa_pre_plan(p,naz+spc[i],tit_GrOb)
            end
       end;
{$ENDIF} {$ENDIF}


{ -------------------------------
   ZARADENIE NA PLANZET EDD
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{$IFDEF TABLET_PRS}

  function TOPRS.ETO(ind: int): real;
     begin
       ETO:= ETD(ind)
     end;

  function TOPRS.ETD(ind: int): real;
     begin
       with PPRS(ap^[ind])^ do
         ETD:= DTToSec(zac.rok,zac.mes,zac.den, zac.h,zac.m,0)
     end;

  function TOPRS.ETA(ind: int): real;
     begin
       with PPRS(ap^[ind])^ do
         ETA:= DTToSec(kon.rok,kon.mes,kon.den, kon.h,kon.m,0)
     end;

  function TOPRS.FL (ind: int): real;
     var   v1,v2   : word;
           v1_,v2_ : char;
     begin
       with PPRS(ap^[ind])^ do
         begin
           decode_l4_vyss (vys1, v1,v1_,nil);
           decode_l4_vyss (vys2, v2,v2_,nil);
           FL:= maximum(get_altM (v1_,v1),get_altM (v2_,v2))
         end;
     end;

{$ENDIF}
