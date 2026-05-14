{$IFDEF PROCESS_ZAM}
  procedure TOZAM.Spracovanie_(tit: string; _data_filter: string;
                               _handler_type: TScrollAct_handler_type; _handler: pointer; _handler_par : pointer;
                               _hlpXXX: Pchar
                              );
      begin
        Spracovanie(tit, @_data_filter,@_is_stat_ZAM, _handler_type,_handler,_handler_par, nil,nil, _hlpXXX)
      end;
{$ENDIF}

{ -------------------------------
   VYKRESLENIE NA MAPE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{$IFDEF MAPY} {$IFNDEF MAPY_1.0}

  function TOZAM.get_id_map(p: pointer; count: int; var naz: string): bool;
     var   dalsi : bool;
           s     : string;
     begin
       dalsi:= false;
       s:= _cairbase(PZAM(p)^.kod);
       case count of
         0 : naz:= PZAM(p)^.kod;
        {1 : naz:= map_AREA+PZAM(p)^.let_;}
         1 : naz:= map_TMA+s;
         2 : naz:= map_CTR+s;
         else naz:= ''
       end;
       get_id_map:= dalsi
     end;

{$ENDIF} {$ENDIF}


{ -------------------------------
   ZARADENIE NA PLANZET EDD
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{$IFDEF TABLET_ZAM}

  function TOZAM.ETO(ind: int): real;
     begin
       ETO:= ETD(ind)
     end;

  function TOZAM.ETD(ind: int): real;
     begin
       with PZAM(ap^[ind])^ do ETD:= DTToSec(zac.rok,zac.mes,zac.den, zac.h,zac.m,0)
     end;

  function TOZAM.ETA(ind: int): real;
     begin
       with PZAM(ap^[ind])^ do ETA:= DTToSec(zac.rok,zac.mes,zac.den, kon.h,kon.m,0)
     end;

  function TOZAM.FL (ind: int): real;
     begin
       FL:= decode_l4_vys_M(PZAM(ap^[ind])^.vys)
     end;

{$ENDIF}
