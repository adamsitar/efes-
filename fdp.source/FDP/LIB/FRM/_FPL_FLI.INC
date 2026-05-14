 const size_FLI = 9;
       form_FLI : array [0..size_FLI-1] of TForm =

         (( item : 'FLI-'; title : tit_3;
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:10; dy:10; font:0; color: white
          ),

          ( {$IFDEF GOST}item : '7a      '{$ELSE}item : '7a     '{$ENDIF};
            title : tit_7a;
            lst : nil; pos : 1; legal : @setABC; skip : @setNil;
            dx:48; dy:10; font:0; color: white{clGRe}
          ),

          ( item : '13 1'; title : tit_13a;
            lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
            dx:125; dy:10; font:0; color:0
          ),

          ( item : '17 1'; title : tit_17a;
            lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
            dx:165; dy:10; font:0; color:0
          ),
          ( item : '17 2'; title : tit_17b;
            lst : @fn_13a; pos : 1; legal : @setCisl;  skip : @setNil;
            dx:199; dy:10; font:0; color:0
          ),

          ( item : '18 2                                                                 ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_DATA; skip : @setNil;
            dx:10; dy:25; font:0; color:0
          ),
          ( item : '18 3                                                                 ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_DATA; skip : @setNil;
            dx:10; dy:35; font:0; color:0
          ),
          ( item : '18 4                                                                 ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_DATA; skip : @setNil;
            dx:10; dy:45; font:0; color:0
          ),
          ( item : '18 5                                                                 ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_DATA; skip : @setNil;
            dx:10; dy:55; font:0; color:0
          )
         );



 type   PFLIform = ^TFLIform;
        TFLIform = object(TRCFform)
          procedure  init_formular; virtual;

          function   read_formular: bool;  virtual;
          function   check_formular: bool; virtual;
        end;


 procedure image_FLI (x0,y0,x1,y1: int); far;
     begin
       image_TLG (x0,y0,x1,y1);
     end;


 { ---------------
   Naplnenie
   ---------------
 }
 procedure TFLIform.init_formular;
     var   s,t,u : string;
     begin
       TTLGform.init_formular;

     { a) Naplnenie FPL
     }
       with FPL do if cut_(getstr(_7,1,[icao_NXT]))<>'' then
         begin
           with itemd^[o_f+1] do StrPICopy(item, _lat_FPL(getstr(_7,1,[icao_NXT])), strlen(item));
           with itemd^[o_f+2] do StrPICopy(item, _lat_FPL(copy(_13,1,KOD_AP)), strlen(item));

           with itemd^[o_f+3] do StrPICopy(item, _lat_FPL(getstr(_16,2,[icao_NXIT])), strlen(item));
         end;

      with itemd^[o_f+4] do StrPICopy(item, TimeToStr (hour,min,''), strlen(item));

      t:= _item_18(FPL._18,rmk_REG,1);
      if t='' then t:= icao_NXIT;
      s:= icao_ARR+rmk_REG+icao_NXT+t;
      with itemd^[o_f+5] do StrPICopy(item, s, strlen(item));

      s:=   icao_ARR+rmk_DATE+icao_NXT+IntToStr(day,2,0)+IntToStr(min,2,0)
           +icao_ARR+TimeToStr (hour,min,'');
      with itemd^[o_f+6] do StrPICopy(item, s, strlen(item));

      s:= icao_ARR+rmk_RMK+icao_NXT;
      with itemd^[o_f+7] do StrPICopy(item, s, strlen(item));

     { b) Naplnenie adresatov
     } init_tlg_adr(head,@Self,0)
     end;



 { ---------------
   Spracovanie
   ---------------
 }
 function TFLIform.read_formular: bool;
    var   i : int;
    begin
     { a) nacitanie adries
     }

     { b) nacitanie dat
     }
      with FPL do
        begin
          StrDispose(_21);
          for i:= 2 to size_FLI do _21:= StrNPCopy(_21,_it(o_f+i)+kbNL,true,true);
       end;

      read_formular:= true
    end;

 function TFLIform.check_formular: bool;
    begin
      check_formular:= true;
      read_formular;
    end;



 procedure  formular_FLI(FPL : PFPL4);
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PFLIform;
            Ev    : TEvent;
            tit   : string;
     begin
       form:= New(PFLIform,Init(ht_FLI,f,
                                ht_FLI, @form_FLI,size_FLI, FPL,
                                nil,nil,nil,@image_FLI,nil)
                               );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;
