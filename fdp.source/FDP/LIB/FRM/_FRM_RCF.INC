 const  i_21 = 2;

 const  size_RCF = 5;
        form_RCF : array [0..size_RCF-1] of TForm =

         (( item : 'RCF-'; title : tit_3;
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:10; dy:10; font:0; color: white
          ),

          ( {$IFDEF GOST}item : '7a      '{$ELSE}item : '7a     '{$ENDIF};
            title : tit_7a;
            lst : nil; pos : 1; legal : @setABC; skip : @setNil;
            dx:48; dy:10; font:0; color: white{clGRe}
          ),

          ( item : '21 1                                                                 ';
            title : tit_21;
            lst : nil; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:25; font:0; color:0
          ),
          ( item : '21 2                                                                 ';
            title : tit_21;
            lst : nil; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:35; font:0; color:0
          ),
          ( item : '21 3                                                                 ';
            title : tit_21;
            lst : nil; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:45; font:0; color:0
          )
         );



 type   PRCFform = ^TRCFform;
        TRCFform = object(OTLGi_form)

          FPL  : DFPL4;

          constructor Init (_tit  : string; var f : Tcentr;
                            _head : string;
                            _FPLi : PFPL4;
                            _form_XXX : PForms; _size_XXX: int;
                            _first_pos: int; _image_form: pointer;
                            _hlpXXX: Pchar
                           );

          destructor  Done; virtual;

          procedure   init_formular_by_18(_X: pchar; ind_off: int; nl: bool); virtual;
          procedure   init_formular_data; virtual;
          procedure   init_formular; virtual;

          function    _read_formular_data (var res: string; var ires: int): string; virtual;
          function    check_formular_data (var res: string; var ires: int): string; virtual;
        end;



 procedure image_RCF (x0,y0,x1,y1: int); far;
     begin
       image_TLG (x0,y0,x1,y1);
     end;

 constructor TRCFform.Init (_tit : string; var f : Tcentr;
                            _head : string;
                            _FPLi : PFPL4;
                            _form_XXX : PForms; _size_XXX: int;
                            _first_pos: int; _image_form: pointer;
                            _hlpXXX: Pchar
                           );

       var   t: string;
       begin
         head:= _head; new_FPL4(_FPLi,@FPL);
         if _image_form=nil then _image_form:= @image_RCF;

         t:= getstr(FPL._7,1,[icao_NXT]);
         if t<>'' then t:= t+' - ';
         inherited Init (t+_tit, f,_head, '',
                         @form_TLGadr,size_TLGadr,
                         _form_XXX, _size_XXX,
                         _first_pos,
                         nil,nil,nil,nil,_image_form, {_adr_var,_init_form,_check_func,_done_form,}
                         10, _hlpXXX
                        );
       end;

 destructor  TRCFform.Done;
      begin
        inherited Done;
        disp_FPL4(@FPL)
      end;


 { ---------------
   Naplnenie
   ---------------
 }
 procedure TRCFform.init_formular_by_18(_X: pchar; ind_off: int; nl: bool);
     var   i, off: int; s,t,u : string; p: pchar;
     begin
       off:= o_f+ind_off;
       if (cut_(_it(off))='') then
          begin
            s:= icao_ARR+rmk_REG+icao_NXT+_item_18(FPL._18,rmk_REG,1)+icao_NXIT;
            with itemd^[off] do StrPICopy(item, s, strlen(item));

            if nl then begin off:= minimum(off+1,items-1); s:= '' end;
            s:=  s + icao_ARR+rmk_DATE+icao_NXT+IntToStr(day,2,0)+IntToStr(month,2,0)
                   + icao_ARR+rmk_UTC +icao_NXT+TimeToStr (hour,min,'')
                   + icao_NXIT;
            with itemd^[off] do StrPICopy(item, s, strlen(item));

            if nl then begin off:= minimum(off+1,items-1); s:= '' end;
            s:= s + icao_ARR+rmk_RMK+icao_NXT;
            with itemd^[off] do StrPICopy(item, s, strlen(item))
          end
       else if _X<>nil then
            begin
              init_pole(off, _X);
              {p:= strpos(_X,rmk_DATE+icao_NXT);
              if p<>nil then}
            end
     end;


 procedure TRCFform.init_formular_data;
     var   s,t,u : string;
     begin
       with FPL do if cut_(getstr(_7,1,[icao_NXT]))<>'' then
         begin
           with itemd^[o_f+1] do StrPICopy(item, _lat_TLG(getstr(_7,1,[icao_NXT])), strlen(item));
           itemd^[o_f+1].legal:= nil
         end;
       init_formular_by_18(FPL._21, 2, false)
     end;


 procedure TRCFform.init_formular;
     begin
       if cut_(getstr(FPL._7,1,[icao_NXT]))='' then first_pos:= 1+o_f
       else ins:= false;
       inherited init_formular;
       init_formular_data;
     end;


 { ---------------
   Spracovanie
   ---------------
 }
 function TRCFform._read_formular_data(var res: string; var ires: int): string;
    var   i: int;
    begin
      strdispose(FPL._21); read_pole(o_f+i,FPL._21);
      res:= OTLGi_form._read_formular_data(res,ires);
      _read_formular_data:= res
    end;

 function TRCFform.check_formular_data(var res: string; var ires: int): string;
    begin
      res:= ''; ires:= -1;
      if cut_(_it(o_f+1))='' then l4_err(a_7a,'', o_f+1,err_7a_missing, res)
      else if FPL._21=nil then l4_err(a_21,'', o_f+i_21,1, res);
      if (res='') and (FPL._13<>'') and (FPL._15<>nil) then save_FPL4(@FPL);
      check_formular_data:= res
    end;


 { ---------------
   Volanie
   ---------------
 }
 procedure  formular_RCF(FPL : PFPL4);
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PRCFform;
            Ev    : TEvent;
            tit   : string;
     begin
       form:= New(PRCFform,Init(getstr(tit_21,2,[icao_NXT,icao_ARR]),f,
                                hd_RCF, FPL,
                                @form_RCF,size_RCF, 2,
                                nil,nil)
                               );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;
