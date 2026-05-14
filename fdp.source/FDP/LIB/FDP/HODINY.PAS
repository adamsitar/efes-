(*-------------------------------------------------------------------*)
(* LETVIS FDP - Hodiny 1.0                                           *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_FDP.h}

{$X+,I-,S-,P-}


unit Hodiny;


interface


     uses  TypeDef,
           graph_h,
           Events, Views;


     const clCLOCK1 = clGRd;
           clCLOCK2 = clGRa;


           CASOVE_ZNAMENIE : bool = true;
           clock_visible   : bool = true;


     type  PClock = ^TClock;
           TClock = object(TView)
             xh,x_,xm,xs,yt: byte;
             hh,mm,ss: int;

            {$IFDEF EDD}
              xEDD,yEDD : int;
            {$ENDIF}
            {$IFDEF TRENAZER}
              time_en: bool;
              rp,mp,dp, hp,np,sp: int;

              procedure zastav;
              procedure pust;
            {$ENDIF}

             constructor Init(_Owner: PGroup; x,y: int);
             procedure   Draw; virtual;
             procedure   HandleEvent(var _Event: TEvent); virtual;

             procedure   Reinit(x,y,dx,dy: int); virtual;

             private
             procedure   Vypis(h,m,s: int);

             public
             procedure   Check;
           end;


     const Clock: PClock = nil;

     procedure HODINY_init(_Owner: PGroup; x,y: int);



implementation

uses  BIOS, _Check, AStream, Crt,
      mouse, str0, utime, mess, io,
      {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF}, SVGA, BGIgraph,
      NET_utc,
      _FDP_def, form_SYS;


 constructor TClock.Init(_Owner: PGroup; x,y: int);
       var   t: word;
       begin
         {$IFDEF EDD} xEDD:= x; yEDD:= y; {$ENDIF}
         inherited Init(_Owner, x,y,0,0);
         Delay(50);
         SetTextStyle(0, HorizDir, 1);
         xh:= 92; x_:= xh + TextWidth('23') + 2;
         xm:= x_ + TextWidth(':');
         xs:= 5 + xm + TextWidth('59');
         {$IFDEF EDD}
           if not PLANZET_MAPA then XY(x,y,130,68)
           else XY(0,MaxY-16,xs+TextWidth('59')+5,16);
         {$ELSE}
           XY(0,MaxY-16,xs+TextWidth('59')+5,16);
         {$ENDIF}
         MCursor:= RUKA;
         GetTimem(hour,min,sec);
         GetDatem(Year,Month,Day, {$IFNDEF CMOS_TIME} t {$ENDIF})
        {$IFDEF TRENAZER}; time_en:= true {$ENDIF}
       end;

 procedure TClock.Reinit(x,y,dx,dy: int);
     begin
       {visible:= _visible;}
      {$IFDEF EDD}
        if not PLANZET_MAPA then XY(xEDD,yEDD,130,68)
        else XY(0,MaxY-16,xs+TextWidth('59')+5,16);
      {$ENDIF}
      {$IFNDEF EDD}
        Self.MoveRel(x0, (MaxY-16) - y0);
      {$ENDIF}
       {Draw;}
       hh:= -1; mm:= -1; ss:= -1;
       {Check}
     end;

 procedure TClock.Draw;
     begin
       Reinit(0,0,MaxX,MaxY);
       if visible then
          begin
           {$IFDEF EDD} if PLANZET_MAPA then {$ENDIF} BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR, btSmall, btOFF);
            BGIgraph.on_off(x0+2,y0+2,x1-2,y1-2,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall,btON);
            FillWin(x0+3,y0+3,x1-3,y1-3,0);
           {$IFDEF EDD} {$IFDEF UA}
              {if not TABLET_MAPA then
                 on_off(x0,y0,x1,y1,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall,btOFF);
              }
           {$ENDIF} {$ENDIF}
            Vypis(hour,min,sec)
          end
       else {$IFDEF EDD} if PLANZET_MAPA then {$ENDIF} ClrWin(x0,y0,x1,y1,0)
     end;

 procedure TClock.HandleEvent(var _Event: TEvent);
     var   bp: bool; xl,yl : int;
     begin
       if not visible then Exit;
       if isClicked(_Event) then
          begin
            {$IFNDEF EDD}
              m_off(bp, xl,yl);
              on_off(x0,y0,x1,y1,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall,btON);
              m_on(bp, xl,yl);
            {$ENDIF}
             formular_Hodiny;
            {$IFNDEF EDD}
              m_off(bp, xl,yl);
              on_off(x0,y0,x1,y1,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall,btOFF);
              m_on(bp, xl,yl);
            {$ENDIF}
            ClearEvent(_Event)
          end;
     end;

 procedure TClock.Vypis(h,m,s: int);
     var   str,s0 : string;
           font,dow : word;
     begin
       if not visible then Exit;

       {$IFDEF EDD}
         if not PLANZET_MAPA then
            begin
              {$IFDEF SPEA}SetBkColor(black);{$ENDIF}
              font:= SPfont;
              if h<>-1 then
                 begin
                   SetColor(clOFF);
                   GetDatem(year,month,day {$IFNDEF CMOS_TIME},dow {$ENDIF});
                   s0:= rightchar('',(x1-x0) shr 3 - 1,' ');
                   str:= {$IFNDEF CMOS_TIME} Days[dow]+' '+ {$ENDIF} delchar(DateToStr(day,month,year,1,'.'),[' ']);

                   SetColor(clON);
                  {$IFDEF SPEA}
                     if not OverlapWin(x0+11,y0,x0+56,y1,-1) then
                        begin
                          SetTextStyle(SYS16x32,0,0);
                          OutTextXY(x0+11,y0+46{918},IntToStr(hour,2,0)+':');
                          if not OverlapWin(x0,y0+45,x1,y1,-1) then
                             begin
                               SetTextStyle(font,0,0);
                               OutTextXY(x0 + (x1-x0-length(s0)*8) div 2,y0+57,s0);
                               OutTextXY(x0 + (x1-x0-length(str)*8) div 2,y0+57,str);
                               hh:= h
                             end;
                        end;
                  {$ENDIF}
                  {$IFDEF BGI}
                     if not OverlapWin(x0+16,y0,x0+58,y1,-1) then
                        begin
                          SetTextStyle(SmallFont{TriplexFont},HorizDir, 8);
                          FillWin(x0+16,y0+11,x0+57,y0+11+TextHeight('H'),0);
                          SetTextStyle(SmallFont{TriplexFont},HorizDir, 8);
                          Write_ (x0+16,y0+11{918},IntToStr(hour,2,0),clON);
                          OutTextXY(x0+48,y0+11{918},':');
                          if not OverlapWin(x0,y0+45,x1,y1,-1) then
                             begin
                               SetTextStyle(DefaultFont, HorizDir, 1);
                               WriteStr (x0 + (x1-x0-length(s0)*8) div 2,y0+48,s0,clON,0);
                               OutTextXY(x0 + (x1-x0-length(str)*8) div 2,y0+48,str);
                               hh:= h
                             end;
                        end;
                  {$ENDIF}
                 end;
              if m<>-1 then
                 begin
                   SetColor(clON);
                  {$IFDEF SPEA}
                     if not OverlapWin(x0+57,y0,x0+92,y1,-1) then
                        begin
                          SetTextStyle(SYS16x32,0,0);
                          OutTextXY(x0+57,y0+46{918},IntToStr(min,2,0));
                          mm:= m
                        end;
                  {$ENDIF}
                  {$IFDEF BGI}
                     if not OverlapWin(x0+58,y0,x0+93,y1,-1) then
                        begin
                          SetTextStyle(SmallFont{TriplexFont},HorizDir, 8);
                          FillWin(x0+58,y0+11,x0+92,y0+11+TextHeight('H'),0);
                          Write_(x0+58,y0+11{918},IntToStr(min,2,0),clON);
                          mm:= m
                        end;
                  {$ENDIF}
                 end;
              if s<>-1 then
                 begin
                   SetColor(clON);
                  {$IFDEF SPEA}
                     if not OverlapWin(x0+93,y0,x1,y1,-1) then
                        begin
                          SetTextStyle(SYS12x20,0,0);
                          OutTextXY(x0+93,y0+34{930},IntToStr(sec,2,0));
                          ss:= s
                        end;
                  {$ENDIF}
                  {$IFDEF BGI}
                     if not OverlapWin(x0+94,y0,x1,y1,-1) then
                        begin
                          SetTextStyle(SmallFont{TriplexFont},HorizDir, 7{1});
                          FillWin(x0+92,y0+9,x0+94+TextWidth('00'),y0+11+TextHeight('H'),0);
                          Write_(x0+94,y0+11,IntToStr(sec,2,0),clON);
                          ss:= s
                        end;
                  {$ENDIF}
                 end;
            {$IFDEF SPEA} SetTextStyle(font,0,0) {$ENDIF}
            {$IFDEF BGI}
               { ! Nasledujeuce prepnutie odalokuje z pamate Triplex Font,
                   ktory zbytocne zabera hafo miesta...

               SetTextStyle(SmallFont,   HorizDir, 1);
               }
               SetTextStyle(DefaultFont, HorizDir, 1)
            {$ENDIF}
            end

         else
       {$ENDIF}
           begin
             if h<>-1 then
                begin
                  WriteStr(x0+7,y0+5,
                           InsChar(DelChar(DateToStr(day,month, year,1,'.'),[' ']),10,' ',1),
                           clCLOCK2{$IFNDEF EGAVGA}-3{$ENDIF},0
                          );
                  WriteStr(x0+xh,y0+5,IntToStr(h,2,0), clCLOCK1,0);
                  WriteStr(x0+x_-1,y0+4,':', clCLOCK2,0);
                  hh:= h
                end;
             if m<>-1 then
                begin
                  WriteStr(x0+xm,y0+5,IntToStr(m,2,0),clCLOCK1,0);
                  mm:= m
                end;
             if s<>-1 then
                begin
                  WriteStr(x0+xs,y0+5,IntToStr(s,2,0),clCLOCK2,0);
                  ss:= s
                end
           end
     end;


 {$IFDEF TRENAZER}

   procedure TClock.zastav;
       begin
         time_en:= false;
         rp:= year; mp:= month; dp:= day; hp:= hour; np:= min; sp:= sec
       end;

   procedure TClock.pust;
       begin
         if time_en then Exit;
         time_en:= true;
         SetDatem(rp,mp,dp);
         SetTimem(hp,np,sp)
       end;

 {$ENDIF}

 procedure TClock.Check;
     var   new_time: bool;
           i: word;
           dt: real;
     begin
      {$IFDEF TRENAZER}
        if not time_en then Exit;
      {$ENDIF}

       if nastavDatum then
          begin
            dt:=   DTtoSec(novyDatum.rok,novyDatum.mes,novyDatum.den, novyDatum.h,novyDatum.m,novyDatum.s)
                 - DTtoSec(Year,Month,Day, hour,min,sec);
            ZMENIL_SA_CAS_SPAT:= dt < 59.0;
            ZMENIL_SA_CAS:= Abs(dt) > 59.0;
            SetTimem(novyDatum.h,novyDatum.m,novyDatum.s);
            SetDatem(novyDatum.rok,novyDatum.mes,novyDatum.den)
          end;

       new_time:= (absTime_) or (nastavDatum);
       GetTimem(hour,min,sec);
       if (hour <> hh) or (new_time) then
          begin
            GetDatem(Year,Month,Day {$IFNDEF CMOS_TIME},i {$ENDIF});
            GetTimem(hour,min,sec)
          end;

       if (sec<>ss) or (min<>mm) or (hour<>hh) or (new_time) then
          begin
            Vypis(-1,-1,sec);
            if (hour <> hh) or (new_time) then
                begin
                  Vypis(hour,min,-1);
                  if (not new_time) and (sec=00) and (CASOVE_ZNAMENIE) then Beep4
                end
            else if (min <> mm) then
                    begin
                      Vypis(-1,min,-1)
                    end;

            set_absTime
          end;
     end;


{ ------------------------------------------- }

 procedure internal_UTC; far;
     var   s: string;
     begin
       if UTC_SYNCHRONIZE then
          begin
            nastavDatum:= true;
            {$IFDEF ARCHIVE_PROGRAM_ERR}
             s:= DateToStr2(day,month,year)+TimeToStr2 (hour,min,sec,'.','ú');
            {$ENDIF}
            if (Clock<>nil) then Clock^.Check;
            nastavDatum:= false;
            {$IFDEF ARCHIVE_PROGRAM_ERR}
             _write_err_log(s+'->'+DateToStr2(day,month,year)+TimeToStr2(hour,min,sec,'.','ú'));
            {$ENDIF}
          end
       else nastavDatum:= false
     end;


 var  SaveMain0 : TProc;

 procedure Medene_Hodinky; far;
     begin
       if @SaveMain0<>nil then SaveMain0;
       Clock^.Check;
       if nastavDatum then int_UTC;
     end;

 procedure HODINY_init(_Owner: PGroup; x,y: int);
     begin
       Clock:= New(PClock,Init(_Owner, x,y));
       SaveMain0:= ACheckProcesses0;
       ACheckProcesses0:= Medene_Hodinky
     end;


begin
  int_UTC:= internal_UTC;
end.  { Hodiny }
