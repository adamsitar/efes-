 const size_FLA = 12;
       form_FLA : array [0..size_FLA-1] of TForm =

         (( item : 'FLA-'; title : tit_3;
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:10; dy:10; font:0; color: white
          ),

          ( {$IFDEF GOST}item : '7a       '{$ELSE}item : '7a     '{$ENDIF};
            title : tit_7a;
            lst : nil; pos : 1; legal :    @setABC; skip : @setNil;
            dx:48; dy:10; font:0; color: 0{clGRe}
          ),


          ( item : '13 1'; title : tit_13a;
            lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
            dx:148; dy:10; font:0; color:0
          ),


          ( item : '16 1'; title : tit_16a;
            lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
            dx:190; dy:10; font:0; color:0
          ),
          ( item : '16 2'; title : tit_16b;
            lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
            dx:226; dy:10; font:0; color:0
          ),


          ( item : 'REG/'; title : '';
            lst : nil; pos : 1; legal :    @setNil; skip : @setNil;
            dx:275; dy:10; font:0; color: 0
          ),
          ( item : '          '; title : tit_TLGreg;
            lst : nil; pos : 1; legal :    @set_MTK_2abc; skip : @setNil;
            dx:307; dy:10; font:0; color: 0
          ),


          ( item : 'DATE/'; title : '';
            lst : nil; pos : 1; legal :    @setNil; skip : @setNXTPISM;
            dx:402; dy:10; font:0; color: 0
          ),
          ( item : '    '; title : tit_TLGdat;
            lst : nil; pos : 1; legal :    @setDig; skip : @setNXTPISM;
            dx:444; dy:10; font:0; color: 0
          ),


          ( item : 'RMK/';
            title : '';
            lst : @fn_18; pos : -1; legal : @setNil; skip : @setNil;
            dx:10; dy:22; font:0; color:0
          ),
          ( item : 'r1                                                               ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:42; dy:22; font:0; color:0
          ),
          ( item : 'r2                                                                   ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:32; font:0; color:0
          )
         );


 type   PFLAform = ^TFLAform;
        TFLAform = object(TANPform)
          procedure  init_formular_data; virtual;
          function   _read_formular_data (var res: string; var ires: int): string; virtual;
        end;


 { ---------------
   Naplnenie
   ---------------
 }
 procedure TFLAform.init_formular_data;
     var   s,t,u,r : string; h,m,h_,m_: byte;
     begin
     { a) Naplnenie FPL
     }
       with FPL do if cut_(getstr(_7,1,[icao_NXT]))<>'' then
         begin

          { _7a }
           with itemd^[o_f+1] do StrPICopy(item, _lat_TLG(getstr(_7,1,[icao_NXT])), strlen(item));
           itemd^[o_f+1].legal:= nil;

          { _13 }
           with itemd^[o_f+2] do StrPICopy(item, _lat_TLG(copy(_13,1,kod_AP)), strlen(item));
           if _13<>'' then itemd^[o_f+2].legal:= nil;

          { _16 }
           if decode_l4_16(_16, h,m, s,h,m,h_,m_, u) then
              begin
                t:= TimeToStr(h_,m_,'');
                u:= delchar(u,[icao_NXIT])
              end
           else begin
                  t:= system.copy(_16,KOD_AP+1,KOD_TIME);
                  u:= system.copy(_16,KOD_AP+1+KOD_TIME,length(_16)-(KOD_AP+1+KOD_TIME))
                end;
           with itemd^[o_f+3] do StrPICopy(item, _lat_TLG(s), strlen(item));
           with itemd^[o_f+4] do StrPICopy(item, t, strlen(item));

           with itemd^[o_f+6] do StrPICopy(item, _item_18(FPL._18,rmk_REG,1), strlen(item));
         end;

      with itemd^[o_f+8] do StrPICopy(item,code_l4_date_r(day,month,false), strlen(item));
    end;


 { ---------------
   Spracovanie
   ---------------
 }
 function TFLAform._read_formular_data(var res: string; var ires: int): string;
    var   s,t,u,a: string; i: int; d,m,v: byte; r: word;
    label X;
    begin
      res:= ''; ires:= -1;

      data:= strpasnew(_it(o_f+0));

     { _7a }
      s:= _it(o_f+1);
      if cut_(s)='' then
         begin
           ires:= l4_err(a_7a,'', o_f+1,1, res); goto X
         end;
      data:= StrNPCopy(data,{icao_ARR+}s,true,true);

     { _13a }
      s:= _it(o_f+2);
      if cut_(s)='' then ires:= l4_err(a_TLG,'', o_f+2,10, res)
      else if length(s)<>kod_AP then ires:= l4_err(a_13a,'',o_f+2,err_13a_neznamy, res);
      if res<>'' then goto X;
      data:= StrNPCopy(data,icao_ARR+s,true,true);

     { _16a }
      s:= _it(o_f+3);
      if cut_(s)='' then ires:= l4_err(a_TLG,'', o_f+3,10, res)
      else if length(s)<>kod_AP then ires:= l4_err(a_16a,'',o_f+3,err_16a_neznamy, res);
      if res<>'' then goto X;

      t:= _it(o_f+4);
      if (cut_(t)='') or (length(t)<>kod_TIME) or (not GetTimeStr(d,m,v, t)) then
         begin
           ires:= l4_err(a_TLG,'', o_f+4,12, res); goto X
         end;

      data:= StrNPCopy(data,icao_ARR+s+t,true,true);

     { REG/ }
      s:= _it(o_f+6);
      data:= StrNPCopy(data,icao_ARR+rmk_REG+icao_NXT+s,true,true);

     { DAT/ }
      s:= _it(o_f+8);
      if (s='') or (not  GetDateStr(r,m,d, s, false)) then
         begin
           ires:= l4_err(a_TLG,'', o_f+8,11, res); goto X
         end;
      data:= StrNPCopy(data,icao_ARR+rmk_DATE+icao_NXT+s,true,true);

     { RMK/ }
      s:= cut_(_it(o_f+10));
      t:= cut_(_it(o_f+11));
      if (s='') and (t='') then begin ires:= l4_err(a_TLG,'', o_f+10,10, res); goto X end;
      if strlen(data)+length(s+t)>MTK_2_LINE-20 then a:= kbNL else a:='';
      data:= StrNPCopy(data,a+icao_ARR+rmk_RMK+icao_NXT+s,true,true);
      if t<>'' then data:= StrNPCopy(data,kbNL+t,true,true);

      X: _read_formular_data:= res
    end;



 { ---------------
   Volanie
   ---------------
 }
 procedure  formular_FLA(FPL : PFPL4);
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PFLAform;
            Ev    : TEvent;
            tit   : string;
     begin
       form:= New(PFLAform,Init(tit_fpl_fla,f,
                                ht_FLA, FPL,
                                @form_FLA,size_FLA, 10,
                                nil,nil)
                               );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;
