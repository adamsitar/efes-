 const size_ANP = 12;
       form_ANP : array [0..size_ANP-1] of TForm =

         (( item : 'ANP-'; title : tit_3;
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:10; dy:10; font:0; color: white
          ),

          ( {$IFDEF GOST}item : '7a       '{$ELSE}item : '7a     '{$ENDIF};
            title : tit_7a;
            lst : nil; pos : 1; legal :    @setABC; skip : @setNil;
            dx:48; dy:10; font:0; color: 0{clGRe}
          ),

          ( item : '82  '; title : tit_9b;
            lst : @fn_9b; pos : 1; legal : @setABC ; skip : @setNil;
            dx:148; dy:10; font:0; color:0
          ),


          ( item : 'REG/'; title : '';
            lst : nil; pos : 1; legal :    @setNil; skip : @setNil;
            dx:193; dy:10; font:0; color: 0
          ),
          ( item : '          '; title : tit_TLGreg;
            lst : nil; pos : 1; legal :    @set_MTK_2abc; skip : @setNil;
            dx:227; dy:10; font:0; color: 0
          ),


          ( item : 'DATE/'; title : '';
            lst : nil; pos : 1; legal :    @setNil; skip : @setNXTPISM;
            dx:322; dy:10; font:0; color: 0
          ),
          ( item : '    '; title : tit_TLGdat;
            lst : nil; pos : 1; legal :    @setDig; skip : @setNXTPISM;
            dx:364; dy:10; font:0; color: 0
          ),


          ( item : 'UTC/';  title : '';
            lst : nil; pos : 1; legal :    @setNil; skip : @setNXTPISM;
            dx:405; dy:10; font:0; color: 0
          ),
          ( item : '    ';  title : tit_TLGutc;
            lst : nil; pos : 1; legal :    @setDig; skip : @setNXTPISM;
            dx:436; dy:10; font:0; color: 0
          ),


          ( item : 'RMK/';
            title : '';
            lst : @fn_18; pos : -1; legal : @setNil; skip : @setNil;
            dx:10; dy:22; font:0; color:0
          ),
          ( item : '                                                                 ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:42; dy:22; font:0; color:0
          ),
          ( item : '                                                                     ';
            title : tit_18;
            lst : @fn_18; pos : -1; legal : @set_MTK_2abc; skip : @setNil;
            dx:10; dy:32; font:0; color:0
          )
         );


 type   PANPform = ^TANPform;
        TANPform = object(TRCFform)
          procedure  init_formular_data; virtual;
          function   _read_formular_data (var res: string; var ires: int) : string; virtual;
          function   check_formular_data (var res: string; var ires: int) : string; virtual;
        end;


 { ---------------
   Naplnenie
   ---------------
 }
 procedure TANPform.init_formular_data;
     var   s,t,u,r : string;
     begin
     { a) Naplnenie FPL
     }
       with FPL do if cut_(getstr(_7,1,[icao_NXT]))<>'' then
         begin
           _in(o_f+1,_lat_TLG(getstr(_7,1,[icao_NXT])));
           itemd^[o_f+1].legal:= nil;

           decode_l4_9 (FPL._9, s,t,u);
           _in(o_f+2,_lat_TLG(t));
           if t<>'' then itemd^[o_f+2].legal:= nil;

           {s:=  s + icao_ARR+rmk_DATE+icao_NXT+IntToStr(day,2,0)+IntToStr(month,2,0)
                   + icao_ARR+rmk_UTC +icao_NXT+TimeToStr (hour,min,'');}
           s:= '';

           _in(o_f+4, _item_18(FPL._18,rmk_REG,1));
         end;

      _in(o_f+6, code_l4_date_r(day,month,false));
      _in(o_f+8, code_l4_utc(hour,min));

      {StrPICopy(item, s, strlen(item));}
    end;


 { ---------------
   Spracovanie
   ---------------
 }

 function TANPform._read_formular_data (var res: string; var ires: int): string;
    var   s,t,u,a: string; i: int; d,m,v: byte; r: word;
    label X;
    begin
      res:= ''; ires:= -1;

      data:= strpasnew(_it(o_f+0));

     { _7a }
      s:= _it(o_f+1);
      if cut_(s)='' then begin ires:= l4_err(a_7a,'', o_f+1,err_7a_missing, res); goto X end;
      data:= StrNPCopy(data,{icao_ARR+}s,true,true);

     { _9b }
      s:= _it(o_f+2);
      if cut_(s)='' then begin ires:= l4_err(a_9b,'', o_f+2,1, res); goto X end;
      data:= StrNPCopy(data,icao_ARR+s,true,true);

     { REG/ }
      s:= _it(o_f+4);
      data:= StrNPCopy(data,icao_ARR+rmk_REG+icao_NXT+s,true,true);

     { DAT/ }
      s:= _it(o_f+6);
      if (s='') or (not  GetDateStr(r,m,d, s, false)) then
         begin
           ires:= l4_err(a_TLG,'', o_f+6,11, res); goto X
         end;
      data:= StrNPCopy(data,icao_ARR+rmk_DATE+icao_NXT+s,true,true);

     { UTC/ }
      s:= _it(o_f+8);
      if (cut_(s)='') or (length(s)<>kod_TIME) or (not  GetTimeStr(d,m,v, s)) then
         begin
           ires:= l4_err(a_TLG,'', o_f+8,12, res); goto X
         end;
      data:= StrNPCopy(data,icao_ARR+rmk_UTC+icao_NXT+s,true,true);

     { RMK/ }
      s:= cut_(_it(o_f+10));
      t:= cut_(_it(o_f+11));
      if (s='') and (t='') then
         begin
           ires:= l4_err(a_TLG,'', o_f+10,10, res); goto X
         end;
      if strlen(data)+length(s+t)>MTK_2_LINE-20 then a:= kbNL else a:='';
      data:= StrNPCopy(data,a+icao_ARR+rmk_RMK+icao_NXT+s,true,true);
      if t<>'' then data:= StrNPCopy(data,kbNL+t,true,true);

      X: _read_formular_data:= res
    end;


 function TANPform.check_formular_data(var res: string; var ires: int): string;
    begin
      res:= ''; ires:= -1;
      check_formular_data:= ''
    end;


{ ---------------
  Volanie
  ---------------
}
 procedure  formular_ANP(FPL : PFPL4);
     const  f     : Tcentr = (x: initX; y: initY; m: 1);
     var    form  : PANPform;
            Ev    : TEvent;
            tit   : string;
     begin
       form:= New(PANPform,Init(tit_fpl_anp, f,
                                ht_ANP, FPL,
                                @form_ANP,size_ANP, 10,
                                nil,nil)
                               );
       form^.RunLocalFunc(Ev,FDPFormLocalMenu);
       Dispose(form,Done)
     end;
