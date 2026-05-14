{$I comp.h}

unit Demo;


interface


     uses  typedef;

     const cfg_demo = 'demo.ini';
           cfg_utc  = 'UTC';
         {
           Imituje prijem letovych planov od servera.
           Implementuje sa direktivou "DEMO".
         }



implementation


uses  BIOS, _Check, SVGA,
      utime, str0, mess,
      IO, DB,
      {$I unit_net.h},
      _L4_def, _FDP_def, {_FPL, _FPLs,}
      Archiv, _FDP;


type  PImitator = ^TImitator;
      TImitator = object

        d0        : TDatum;
        t0, dt0   : real;
        {ut, st   : long;}

        semaphor  : bool;

        constructor Init;
        destructor  Done;

        procedure   initialize_utc;
        procedure   reinitialize_utc;

        procedure   check;
        procedure   load_net_pkt(hour,min: byte);
        procedure   load_fdp_data;
      end;


var  I: PImitator;

constructor TImitator.Init;
      begin
        initialize_utc;
      end;


procedure TImitator.initialize_utc;
    var   s : string;
          w : word;
          d : TDatum;
    begin
      {ut:= dos2unix(d,t);
      st:= TickCounter;}

      datum_init (d0, day,month,year,hour,min,sec);
      t0:= AbsTime; dt:= 0;

      s:= _read_cfg (cfg_demo,cfg_utc,true);
      if decode_l4_datum (s,d) then
         begin
           SetDatem(d.rok,d.mes,d.den);
           SetTimem(d.h,d.m,0);

           GetTimem(Hour,Min,Sec);
           GetDatem(Year,Month,Day,w);
         end;

      set_absTime;
      dt0:= AbsTime - t0;

      ROZSVIETENE:= absTime
    end;


procedure  TImitator.reinitialize_utc;
    var    i : int;
           d : real;
           k : word;
    begin
      {unix2dos(ut, d,t);
      SetTimem(t.hour,t.min,t.sec);
      SetDatem(d.year,d.month,d.day)
      }

      d:= dt0/secDAY; k:= trunc(abs(d));
      {for i:= 0 to k-1 do
          begin
            if dt0>0 then PrevDate(d0.rok,d0.mes,d0.den,d0.h)
            else NextDate(d0.rok,d0.mes,d0.den);
          end;
      }
      SetDatem(d0.rok,d0.mes,d0.den);

      {d:= dt0 - (trunc(dt0/k))*k;
      d0.h:= trunc(d/secHOUR);
      d0.m:= trunc((d - (trunc(d/secHOUR)) * secHOUR) / 60);
      }
      SetTimem(d0.h,d0.m,0);
    end;

destructor TImitator.Done;
     var   d: DOS_date;
           t: DOS_time;
     begin
       reinitialize_utc
     end;


procedure TImitator.check;
    const lm : byte = 60;
          lh : byte = 25;
          s  : bool = false;
    begin
      if (lm<>min) and (not s) then
         begin
           s:= true;
           if (lm<>60) and (lm>min) and (lh>=hour) then;
           if (lh<>hour) then load_fdp_data;
           lh:= hour; lm:= min;
           load_net_pkt(hour,min);
           s:= false
         end;
    end;

procedure TImitator.load_net_pkt(hour,min: byte);
    var   FN : string;
    begin
      FN:= path_NET+inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+'00'+'.'+extNET;
      {net_pkt_test(FN,hour,min);}
    end;


procedure TImitator.load_fdp_data;
    begin
      initialize_fdp_records:= true;
      PLANY_load
    end;


var  SaveMain : TProc;
     SaveExit : pointer;

procedure Imitator; far;
    begin
      if @SaveMain<>nil then SaveMain;
      I^.check;
    end;

procedure RestoreImitator; far;
    begin
      Dispose(I,Done);
      exitproc:= SaveExit
    end;


{ I demo.inc}

procedure SetImitator;
    var   Hs,Ms,D,M: byte;
          Y,c: int;
          dummy: word;
    begin
      I:= New(PImitator,Init);

      SaveMain:= ACheckProcessesA;
      ACheckProcessesA:= Imitator;

      saveexit:= exitproc;
      exitproc:= @RestoreImitator;
    end;


{$IFDEF DEMO}
begin
  SetImitator
{$ENDIF}
end.

(*
function is_cFPL(last_min: pbyte; FPL: PDcFPL): bool; far;
     begin
       if (FPL^.time.h=hour) and (FPL^.time.m=min) then cFPL^.Load(FPL);
       is_cFPL:= false
     end;

function is_mFPL(last_min: pbyte; FPL: PDmFPL): bool; far;
     begin
       if (FPL^.time.h=hour) and (FPL^.time.m=min) then mFPL^.Load(FPL);
       is_mFPL:= false
     end;

procedure TImitator.load;
    var   cFPL : DcFPL;
          mFPL : DmFPL;
          FN   : string;
    begin
      FN:= pathFPL_C+archiv_HODfn;
      DB_prehladaj(@is_cFPL, @last_min, @cFPL, nil, FN, db_cFPL_RIADKOV, @decodeDB_cFPL);
     {$IFDEF FDP_EDD}
      FN:= get_DBfn_(day,month,year, pathFPL,ext_mFPL);
      DB_prehladaj(@is_mFPL, @last_min, @mFPL, @disp_mFPL, FN, db_mFPL_RIADKOV, @decodeDB_mFPL)
     {$ENDIF}
    end;
*)

procedure set_date(var Hs,Ms,D,M: byte; var Y: int);
    var   s,t: string;
    begin
      Hs:= hour; Ms:= min; D:= day; M:= month; Y:= year;

    { pre OPLko }
    { datum - najstarsi subor v adresari \FPL }
    { cas - podla stripov }
      s:= get_najstarsi_subor(pathFPL,'*.'+ext_mFPL);
      if s<>'' then
         begin
           D:= getint(s,1,['-']);
           M:= getint(s,2,['-']);
           Y:= getint(s,3,['-','.']) + 1900;
         end;
      t:= get_najstarsi_subor(pathFPL_C,'*.*');
      if t<>'' then
         begin
           Hs:= getint(t,2,['.']);
           Ms:= 5;
           {$IFDEF FDP_OPL}
           if s='' then
           {$ENDIF}
              begin
                D:= getint(t,1,['-']);
                M:= getint(t,2,['-']);
                Y:= getint(t,3,['-','.']) + 1900
              end
         end;
    end;