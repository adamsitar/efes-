 function formular_ARR (zac,kon : TDatum;
                        var arr : TDatum;

                        sc : PScroller;
                        tit,idn : string;

                        err_pole   : string;
                        err_kratsi : int;
                        dlhsi      : bool;
                        err_dlhsi  : int
                       ): bool;
    var   x,y   : int;
          ires  : int;
          res   : string;
          bres  : bool;
          t0,t1,t2 : real;
          t     : TTime;
    begin
      if sc<>nil then
         begin
           sc^.get_pos_xy(sc^.pos, x,y);
           inc(x,10); inc(y,18)
         end
      else begin
             x:= initX; y:= initY
           end;
      tit:= tit+' '+idn+':'+#0;
      bres:= false; res:= '?';

      while (res<>'') do
        begin
          datum_init (arr, day,month,year,hour,min,sec);
          if zac.den<>kon.den then
               begin
                 bres:= formular_DATUM_CAS(tit_TERMINATE,arr)
               end
          else begin
                 bres:= formular_CAS(t, hour,min, x,y, tit_TERMINATE, @tit[1]);
                 if bres then begin arr.h:= t.h; arr.m:= t.m end
               end;
          if not bres then break;

          arr.s:= sec;
          res:= '';
          with zac do t0:= DTtoSec(rok,mes,den,h,m,0);
          with kon do t1:= DTtoSec(rok,mes,den,h,m,0);
          with arr do t2:= DTtoSec(rok,mes,den,h,m,0);

         { nepise tu dakto bludy ?
         } if t2<t0 then l4_err(err_pole,idn,0,err_kratsi,res)

         { bol prekroceny povoleny limit ukoncenia ?
         } else if (t2>t1) and (not dlhsi) then
             begin
               l4_err(err_pole,idn,0,err_dlhsi,res);
               if t2<=absTime then
                  begin
                    res:= res + ' ('+idn+')';
                    if Ask2(msgWARNING,res,titNO,White,clBUTTON_COLOR,waitASK*18) = ansAno then
                       begin
                         Say2(msgWARNING,res);
                         res:= ''
                       end
                  end
             end;

          if res<>'' then Err2('',res+' ('+idn+')')
          else break
        end;
      formular_ARR:= bres
    end;
