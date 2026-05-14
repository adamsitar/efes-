
 const size_RVM = 8;
       size_RVI = 4;

       form_RVM : array [0..size_RVM-1] of TForm =

         (( item : 'RVM-'; title : tit_3;
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:10; dy:10; font:0; color: white
          ),


          ( item : '2                      ';  title : tit_AREA;
            lst : nil; pos : 1; legal : @set_MTK_2abc; skip : @setNil;
            dx:48; dy:10; font:0; color: 0
          ),


          ( item : 'DATE/'; title : tit_DATb;
            lst : nil; pos : 1; legal : @setNil; skip : @setPism;
            dx:247; dy:10; font:0; color: 0
          ),
          ( item : '3   '; title : tit_DATb;
            lst : nil; pos : 1; legal : @setDig; skip : @setPism;
            dx:287; dy:10; font:0; color: 0
          ),


          (*( item : 'UTC/';  title : tit_UTCb;
            lst : nil; pos : 1; legal : @setNil; skip : @setPism;
            dx:331; dy:10; font:0; color: 0
          ),
          ( item : '1   ';  title : tit_UTCb;
            lst : nil; pos : 1; legal : @setDig; skip : @setPism;
            dx:353; dy:10; font:0; color: 0
          ),
          *)

          ( item : 'RMK/';
            title : '';
            lst : @fn_18; pos : -1; legal : @setNil; skip : @setNil;
            dx:10; dy:25; font:0; color:0
          ),
          ( item : 'r1                                                               ';
            title : tit_RVM;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:42; dy:25; font:0; color:0
          ),
          ( item : 'r2                                                                   ';
            title : tit_RVM;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:35; font:0; color:0
          ),
          ( item : 'r3                                                                   ';
            title : tit_RVM;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:45; font:0; color:0
          )
         );


 type   PRVMform = ^TRVMform;
        TRVMform = object(OTLGi_form)
          procedure   init_formular; virtual;
          function    _read_formular_data(var res: string; var ires: int): string; virtual;
        end;


 { ---------------
   Naplnenie
   ---------------
   Objekt pouziva i RVI - ma mensi pocet poloziek, formular je identicky...
 }

 procedure TRVMform.init_formular;
     begin
       inherited init_formular;

       with itemd^[o_f  ] do StrPICopy(item, head+icao_ARR, strlen(item));
       with itemd^[o_f+3] do StrPICopy(item, code_l4_date_r(day,month,false), strlen(item));
     end;


 { ---------------
   Spracovanie
   ---------------
 }

 function TRVMform._read_formular_data(var res: string; var ires: int): string;
    var   s,t,u: string;
          i: int;
          d,m,v: byte;
          r: word;

    label X;

    begin
      res:= ''; ires:= -1;

      data:= strpasnew(_it(o_f+0)); { obsahuje '-' }

     { DATA }
      s:= cut_(_it(o_f+1));
      if s='' then begin ires:= l4_err(a_TLG,'', o_f+1,10, res); goto X end;
      data:= StrNPCopy(data,s,true,true);

     { DATE/ }
      s:= _it(o_f+3);
      if (s='') or (not  GetDateStr(r,m,d, s, false)) then
         begin ires:= l4_err(a_TLG,'', o_f+3,11, res); goto X end;
      data:= StrNPCopy(data,icao_ARR+rmk_DATE+icao_NXT+s,true,true);

     { UTC/
      s:= _it(o_f+4);
      if (cut_(s)='') or (length(s)<>kod_TIME) or (not  GetTimeStr(d,m,v, s)) then
         begin ires:= l4_err(a_TLG,'', o_f+4,12, res); goto X end;
      data:= StrNPCopy(data,icao_ARR+rmk_UTC+icao_NXT+s,true,true);
     }

      if items-o_f>size_RVI then
         begin
          { RMK/ }
           s:= cut_(_it(o_f+5));
           t:= cut_(_it(o_f+6));
           if (s='') and (t='') then begin ires:= l4_err(a_TLG,'', o_f+5,10, res); goto X end;
           if strlen(data)+length(s+t)>MTK_2_LINE-20 then u:= kbNL else u:='';
           data:= StrNPCopy(data,u+icao_ARR+rmk_RMK+icao_NXT+s,true,true);
           if t<>'' then data:= StrNPCopy(data,kbNL+t,true,true)
         end;

      X: _read_formular_data:= res
    end;


 { ---------------
   RVM
   ---------------
 }
 procedure  formular_RVM;
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PRVMform;
            Ev    : TEvent;
            tit   : string;
     begin
       form:= New(PRVMform,Init(getstr(tit_RVM,1,[icao_NXT,icao_ARR]),f,
                                ht_RVM, icao_ARR,
                                @form_TLGadr,size_TLGadr,
                                @form_RVM,size_RVM, 1,
                                nil,nil,nil,nil,nil, 10,nil)
                               );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;


 { ---------------
   RVI
   ---------------
 }
 procedure  formular_RVI;
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PRVMform;
            Ev    : TEvent;
            tit   : string;
     begin
       form:= New(PRVMform,Init(getstr(tit_RVI,1,[icao_NXT,icao_ARR]),f,
                                ht_RVI, icao_ARR,
                                @form_TLGadr,size_TLGadr,
                                @form_RVM,size_RVI, 1,
                                nil,nil,nil,nil,nil, 10,nil)
                               );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;
