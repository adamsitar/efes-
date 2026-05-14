const  SIZE_frm_DVZ  =  11;

       i_kym   = 0;
       i_dat   = 1;
       i_zac   = 2;
       i_kon   = 3;
       i_cas   = 4;
       i_poz   = 5; i_pozs = 2;
       i_odo   = 7; i_odos = 2;
       i_zab   = 9; i_zabs = 2;


const  Form_DVZ: array [0..SIZE_frm_DVZ-1] of TForm =
            (
             ( item : '   1';
               title: tit_dvz_kym;
               lst : @fnMLet; pos: 1; legal: @setABC; skip : @setNil;
               dx:123; dy:12; font:0; color: 0
             ),
             ( item : '     2';
               title: tit_dvz_date;
               lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
               dx:185; dy:12; font:0; color: 0
             ),
             ( item : '  : 3';
               title: tit_dvz_od;
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:255; dy:12; font:0; color: 0
             ),
             ( item : '  : 4';
               title: tit_dvz_do;
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:320; dy:12; font:0; color: 0
             ),
             ( item : '  : 5';
               title: tit_dvz_vyh;
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:435; dy:12; font:0; color: 0
             ),
             ( item : '                                                          6';
               title: tit_dvz_poz;
               lst : nil; pos: 1; legal: @set_19; skip : @setNil;
               dx:10; dy:32; font:0; color: 0
             ),
             ( item : '                                                          7';
               title: tit_dvz_poz;
               lst : nil; pos: 1; legal: @set_19; skip : @setNil;
               dx:10; dy:42; font:0; color: 0
             ),
             ( item : '                                                          8';
               title: tit_dvz_odo;
               lst : nil; pos: 1; legal: @set_19; skip : @setNil;
               dx:10; dy:59; font:0; color: 0
             ),
             ( item : '                                                          9';
               title: tit_dvz_odo;
               lst : nil; pos: 1; legal: @set_19; skip : @setNil;
               dx:10; dy:69; font:0; color: 0
             ),
             ( item : '                                                         10';
               title: tit_dvz_zab;
               lst : nil; pos: 1; legal: @set_19; skip : @setNil;
               dx:10; dy:89; font:0; color: 0
             ),
             ( item : '                                                         11';
               title: tit_dvz_zab;
               lst : nil; pos: 1; legal: @set_19; skip : @setNil;
               dx:10; dy:99; font:0; color: 0
             )
            );


type   PDVZform = ^TDVZform;
       TDVZform = object(TFDP_AForm)
         vlastna: bool;
       end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ DIVERZIE                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

procedure _DVZ_init(form: PDVZform; DVZ: PDVZ); far;
    var   h,m,s : byte;
          t : string;
          i : int;
    begin
      if (DVZ<>nil) and (DVZ^.kym<>'') then with form^ do
         begin
           form^._in(i_kym,DVZ^.kym);

           if (PDVZform(form)^.arch) then form^._in(i_dat,' ')
           else form^._in(i_dat,code_l4_date(DVZ^.date));

           if (cut_(DVZ^.zac)<>'') and (GetTimeStr(h,m,s,DVZ^.zac)) then t:= TimeToStr(h,m,':')
           else t:= cnst_TIME;
           form^._in(i_zac,t);

           if (cut_(DVZ^.kon)<>'') and (GetTimeStr(h,m,s,DVZ^.kon)) then t:= TimeToStr(h,m,':')
           else t:= cnst_TIME;
           form^._in(i_kon,t);

           if (cut_(DVZ^.od)<>'') and (GetTimeStr(h,m,s,DVZ^.od)) then t:= TimeToStr(h,m,':')
           else t:= cnst_TIME;
           form^._in(i_cas,t);

           form^.init_pole(i_poz, DVZ^.poziadavka);
           form^.init_pole(i_odo, DVZ^.odoslanie);
           form^.init_pole(i_zab, DVZ^.zabezpecenie)
         end;

      if     (PDVZform(form)^.arch) { netypicke pretypovanie... }
         or  ((DVZ=nil) or (cut_(DVZ^.kym)='') or _plan_pre(DVZ^.pre)) then
         for i:= i_zab to i_zab+i_zabs-1 do form^.itemd^[i].legal:= @setNil
      else for i:= i_kym to i_zab-1 do form^.itemd^[i].legal:= @setNil;

      if (form^.adr_data<>nil) and (not form^.arch) then
         begin
           form^.itemd^[i_kym].legal:= @setNil;
           form^.itemd^[i_dat].legal:= @setNil;
         end
      else if cut_(form^._it(i_kym))='' then
              begin
                form^._in(i_dat,code_l4_date_(year,month,day));
                form^._in(i_zac, cnst_time);
                form^._in(i_kon, cnst_time);
                form^._in(i_cas, cnst_time);
              end;
    end;


procedure _DVZ_image(x0,y0,x1,y1: int); far;
    var   bp: bool; xlm,ylm: int;
    begin
      m_off (bp, xlm,ylm);
      BGIgraph .button(x0,y0,x1,y1, clBUTTON_COLOR+1, btSmall, btOFF);
      on_off(x0+4,y0+26,x1-4,y1-4, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btON);
      SetTextStyle(SmallFont, HorizDir,4);
      setcolor(cl_data-2);
      OutTextXY(x0+12,y0+9,tit_diverzia_);
      SetTextStyle(DefaultFont, HorizDir,0);

      SetColor(clBUTTON_COLOR+clBUTTON_LIGHT);
      Line(x0+5, y0+53, x1-5, y0+53);
      Line(x0+5, y0+81, x1-5, y0+81);

      SetColor(clBUTTON_COLOR+clBUTTON_DARK);
      Line(x0+5, y0+54, x1-5, y0+54);
      Line(x0+5, y0+84, x1-5, y0+84);
      m_on (bp, xlm,ylm);
    end;


function _DVZ_check_plan(DVZ: PDVZ; var res: string): int; far;
   var   ires, i : int;
         h,m,b : byte;
   label X;
   begin
     res:= ''; ires:= 0;
     with DVZ^ do
       begin
         if (kym='') or (kym=pre) or (is_NETadr(adr_airbase(kym))=-1) then
            begin ires:= l4_err(a_OPL,'',i_kym,err_OPL_dvz_letisko, res); goto X end;

         if (cut_(zac)='') or (not GetTimeStr(h,m,b,zac)) then
            begin l4_err(a_L4,zac,i_zac,err_l4444_time, res); goto X end;

         if (cut_(kon)='') or (not GetTimeStr(h,m,b,kon)) then
            begin l4_err(a_L4,kon,i_kon,err_l4444_time, res); goto X end;
       end;
     X: _DVZ_check_plan:= ires
   end;


function _DVZ_read_plan (form: PAForm; DVZ: PDVZ): bool; far;
   begin
     disp_DVZ(DVZ);
     _DVZ_read_plan:= true;

     with DVZ^ do
       begin
         kym:= form^._it(i_kym);
         zac:= delchar(form^._it_(i_zac),[':']);
         kon:= delchar(form^._it_(i_kon),[':']);
         od:= delchar(form^._it_(i_cas),[':']);
         form^.read_pole(i_poz,poziadavka);
         form^.read_pole(i_odo,odoslanie);
         form^.read_pole(i_zab,zabezpecenie);
       end;
   end;


function _DVZ_check (form: PDVZform; DVZ: PDVZ): bool; far;
   var   ires  : int;
         res,s : string;
         datum : bool;

   label X;
   begin
     _DVZ_read_plan(form,DVZ);
     res:= ''; ires:= -1;

     if form^.vlastna then
        begin
          ires:= _DVZ_check_plan(DVZ,res);
          if res<>'' then goto X;

          s:= cut_(form^._it_i(i_dat));
          if (s<>'') then
             if decode_l4_date (s,DVZ^.date) then form^.is_date:= true
             else begin ires:= l4_err(a_L4,'',i_dat,err_l4444_date, res); goto X end;

          if (DVZ^.dap.rok=0) then
             datum_init(DVZ^.dap, day,month,year, hour,min,sec);

          if (pos(cnst_dvz_zac,DVZ^.stat)<>0) and (cut_(DVZ^.od)='') then
             DVZ^.od:= code_l4_utc(hour,min);

          if (DVZ^.stat=cnst_sended) and posliZiadostDVZ then
              DVZ^.stat:= cnst_dvz_req;
        end
     else begin
            if (pos(cnst_dvz_alr,DVZ^.stat)<>0) and (cut_(DVZ^.vystraha)='') then DVZ^.vystraha:= code_l4_utc(hour,min)
            else DVZ^.vystraha:= ''
          end;

     _DVZ_check:= true;
     Exit;

     X: _DVZ_check:= false;
        form^.ErrorS(ires, res);
        if datum then fillchar(DVZ^.date,sizeof(DVZ^.date),0);
        disp_DVZ(DVZ)
   end;


function _DVZ_date(DVZ: PDVZ; p: pointer; date: PDate): bool; far;
   begin
     if date<>nil then DVZ^.date:= date^;
     _DVZ_date:= true
   end;



function  formular_DVZ(DVZi: PDVZ; _uloz,_arch,_vlastna: bool; _stat, _title: string): bool;
   const  f    : Tcentr = (x: initX; y: initY; m: 1);
   var    form : PDVZform;
          E    : TEvent;
          DVZ  : TDVZ;
          i    : int;
          _novy: bool;
          _p_date : pointer;

   begin
     fillchar(DVZ,sizeof(TDVZ),0);

     _novy:= (DVZi=nil) or (_arch);
     if not _novy then
        begin
          new_DVZ(DVZi,@DVZ);   { MILUJEM LESNU VONU, PATU A CUCORIEDKU !!! Brrrruno}
          if _stat<>'' then DVZ.stat:= _stat
          else DVZ.stat:= DVZi^.stat;
          DVZ.stat:= del_stat(DVZ.stat, cnst_CNL);
          _p_date:= nil
        end
     else begin
            {if (DVZi<>nil) and _arch then new_DVZ(DVZi,@DVZ);}
            DVZ.pre := this_airbase;
            if posliZiadostDVZ then DVZ.stat:= cnst_dvz_req
            else DVZ.stat:= cnst_disk;
            if _arch then fillchar(DVZ.date,sizeof(DVZ.date),0);
            fillchar(DVZ.dap,sizeof(DVZ.dap),0);
            _p_date:= @_DVZ_date
          end;

     form:= New(PDVZform,Init(f.x,f.y, f.m, _title,
                @Form_DVZ,SIZE_frm_DVZ,
                0,1, 0,0, 0,0,

                @_DVZ_init, @_DVZ_image,@_DVZ_check,nil,
                @DVZ, DVZi, @DVZ.rec, letvis, DVZ.stat,

                _novy, sizeof(TDVZ),nil,nil,nil,nil,
                _p_date,nil,@zarad_DVZ,@disp_DVZ,

                true,false,true
                {$IFDEF ODOSLI_ULOZ}, (not posliZiadostDVZ) and (_uloz or _novy) {$ENDIF}
                {$IFDEF SKRY_OKNA}, false {$ENDIF}
                {$IFDEF STATISTIKA_OPL}, nil{p_info_STA_DVZ} {$ENDIF}
                ));

     form^.upcas:= false;
     form^.arch:= _arch and (DVZi<>nil);
     _uloz:= _uloz or (pos(cnst_disk,DVZ.stat)<>0);
     form^.vlastna:= _vlastna;

     form^.RunLocalFunc(E,nil);
     formular_DVZ:= form^.corr_res;
     Dispose(form,Done);

     disp_DVZ(@DVZ)
   end;
