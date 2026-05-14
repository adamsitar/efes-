 function is_file_FUA(FN: string): bool; far;
    var   P   : PathStr;
          D   : DirStr;
          N   : NameStr;
          E   : ExtStr;
          cis : long;
    begin
      FSplit(FN, D,N,E);
      is_file_FUA:= is_scish_(delchar(E,['.']),cis,false)
    end;


{$IFDEF PROCESS_FUA}

 procedure podanie_AUP(fn: string);
     const  f  : Tcentr = (x: initX; y: initY; m:1);
     var    E  : PAUPed;
            Ev : TEvent;
     begin
       {NextDate   (var _year: word; var _month, _day: byte);
       fn:= get_DBfn_ (day,month,year, rok: word; path: string; ext: str3): string;
       fn:= '';
       _formular_FUA(fn,AUP_ini, delchar(tit_AUP,['~']), true);
       }
       E:= New(PAUPed,Init(f.x,f.y,f.m, tit_AUP, false, fn,AUP_kod,AUP_ini, spr_AUP,key_aup,pathAUP, hlp_AUP));
       E^.RunLocalFunc(Ev,FORM_INFO);
       Dispose(E,done)
     end;

 procedure podanie_UUP(fn: string);
     const  f  : Tcentr = (x: initX; y: initY; m:1);
     var    E  : PUUPed;
            Ev : TEvent;
     begin
       E:= New(PUUPed,Init(f.x,f.y,f.m, tit_UUP, false, fn,UUP_kod,UUP_ini, spr_UUP,key_uup,pathUUP, hlp_UUP));
       E^.RunLocalFunc(Ev,FORM_INFO);
       Dispose(E,done)
     end;


 procedure oprava_AUP;
     var   fn : string;
     begin
       fn:= get_PPL_FN_(pathAUP,ext_all,@is_file_FUA, delchar(mnu_AUP_CHG,[cnst_HotKey]));
       if fn<>'' then podanie_AUP(fn)
     end;

 procedure oprava_UUP;
     var   fn : string;
     begin
       fn:= get_PPL_FN_(pathUUP,ext_all,@is_file_FUA, delchar(mnu_UUP_CHG,[cnst_HotKey]));
       if fn<>'' then podanie_UUP(fn)
     end;

{$ENDIF}
