{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ SCHOPNOSTI                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

const  i_kod   = 0;
       i_date  = 1;
       i_stav  = 2;
       i_TQGO  = 4;
       i_TQGO_ = 5;
       i_TQGOc = 6;
       i_MQGO  = 7;
       i_MQGO_ = 8;
       i_MQGOc = 9;

       SIZE_frm_QGO = 10;

       set_QGO : TCharSet = [' ','-','0'..'9','A'..'Z'];


const  Form_QGO: array [0..SIZE_frm_QGO-1] of TForm =
            (
             ( item : '   0';
               title: 'k¢d letiska';
               lst : @fn_13aM; pos: 1; legal: @setABC; skip : @setNil;
               dx:10; dy:10; font:0; color: 0
             ),
             ( item : '     1';
               title: 'd†tum platnosti';
               lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
               dx:60; dy:10; font:0; color: 0
             ),
             ( item : '                                                               0';
               title: 'stav prostriedkov letiska';
               lst : nil; pos: -1; legal: @setABCcs_; skip : @setNil;
               dx:10; dy:27; font:0; color: 0
             ),
             ( item : '                                                               1';
               title: 'stav prostriedkov letiska';
               lst : nil; pos: -1; legal: @setABCcs_; skip : @setNil;
               dx:10; dy:37; font:0; color: 0
             ),

             ( item : '         2';
               title: 'TQGO';
               lst : @fnTQGO; pos: 1; legal: @set_QGO; skip : @setNil;
               dx:10; dy:57; font:0; color: 0
             ),
             ( item : '                                        3';
               title: 'pozn†mky';
               lst : nil; pos: -1; legal: @set_19; skip : @setNil;
               dx:111; dy:57; font:0; color: 0
             ),
             ( item : '1 :  '; title: 'áas vyhl†senia TQGO';
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:471; dy:57; font:0; color: 0
             ),

             ( item : '         5';
               title: 'MQGO';
               lst : @fnMQGO; pos: -1; legal: @set_QGO; skip : @setNil;
               dx:10; dy:71; font:1; color: 0
             ),
             ( item : '                                        6';
               title: 'pozn†mky';
               lst : nil; pos: -1; legal: @set_19; skip : @setNil;
               dx:111; dy:71; font:0; color: 0
             ),
             ( item : '2 :  '; title: 'áas vyhl†senia MQGO';
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:471; dy:71; font:0; color: 0
             )
            );


type  POQGOfrm = ^OQGOfrm;
      OQGOfrm  = object(TFDP_AForm)
        procedure draw_buttons; virtual;
      end;


procedure _QGO_init(form: PFDP_AForm; QGO: PQGO); far;
    var   t: string;
          h,m,s: byte;
    begin
      if (form^.adr_data<>nil) then with PQGO(form^.adr_data)^ do
         begin
           form^._in(i_kod,kod);
           form^._in(i_date,code_l4_date(date));

           form^.init_pole(i_stav,stav);

           form^._in(i_TQGO,TQGO);
           form^._in(i_TQGO_,strpas(TQGO_));
           if (cut_(TQGOc)<>'') and (GetTimeStr(h,m,s,TQGOc)) then t:= TimeToStr(h,m,':')
           else t:= cnst_TIME;
           form^._in(i_TQGOc,t);

           form^._in(i_MQGO,MQGO);
           form^._in(i_MQGO_,strpas(MQGO_));
           if (cut_(MQGOc)<>'') and (GetTimeStr(h,m,s,MQGOc)) then t:= TimeToStr(h,m,':')
           else t:= cnst_TIME;
           form^._in(i_MQGOc,t);
         end
      else begin
            {$IFDEF AIRBASE}
              if cut_(form^._it(i_kod))='' then form^._in(i_kod,this_airbase);
            {$ENDIF}
           end;

      if (form^.adr_data<>nil) and (not form^.arch) then
         begin
           form^.itemd^[i_kod].legal:= @setNil;
           form^.itemd^[i_date].legal:= @setNil
         end
      else form^._in(i_date,code_l4_date_(year,month,day))
    end;

procedure _QGO_image(x0,y0,x1,y1: int); far;
    var   bp: bool; xlm,ylm: int;
    begin
      m_off (bp, xlm,ylm);
      BGIgraph.button(x0,y0,x1,y1, clBUTTON_COLOR+1, btSmall, btOFF);
      on_off(x0+3,y0+3,x1-3,y1-12, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btOFF);
      on_off(x0+4,y0+4,x1-4,y1-13, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btON);
      _lineho(x0+5,x1-5,y0+21, clBUTTON_COLOR+1);
      _lineho(x0+5,x1-5,y0+49, clBUTTON_COLOR+1);
      {_lineho(x0+7,x1-7,y0+65, clBUTTON_COLOR+1);}
      _linevo(x0+99 ,y0+50,y1-13, clBUTTON_COLOR+1);
      _linevo(x0+445,y0+50,y1-13, clBUTTON_COLOR+1);
      m_on (bp, xlm,ylm)
    end;


function _QGO_check(form: PFDP_AForm; QGO: PQGO): bool; far;
   var   h,m,b : byte;
         i,r,k : int;
         ires  : int;
         res,s : string;
         datum : bool;

   label X;

   begin
     disp_QGO(QGO);
     res:= ''; ires:= 0; datum:= false;

     with QGO^ do
       begin
         kod:= form^._it_i(i_kod);
         if cut_(kod)='' then ires:= l4_err(a_OPL,'',i_kod,err_OPL_chyba_letisko, res);
         {$IFDEF AIRBASE}
          if res='' then if not _plan_pre_pracovisko(QGO) then ires:= l4_err(a_OPL,kod,i_kod,err_OPL_neopravnene_letisko,res);
         {$ENDIF}
         if res<>'' then goto X;

         form^.read_pole(i_stav,stav);

         TQGO  := form^._it(i_TQGO);
         TQGO_ := strpasnew(form^._it_i(i_TQGO_));
         {if cut_(TQGO)<>'' then
            begin}
              TQGOc:= delchar(form^._it_(i_TQGOc),[':']);
              if (cut_(TQGOc)<>'') and (not GetTimeStr(h,m,b,TQGOc)) then
                 begin
                   l4_err(a_L4,TQGOc,i_TQGOc,err_l4444_time, res);
                   goto X
                 end;
            {end
         else TQGOc:= ''};

         MQGO  := form^._it(i_MQGO);
         MQGO_ := strpasnew(form^._it_i(i_MQGO_));
         {if cut_(MQGO)<>'' then
            begin}
              MQGOc := delchar(form^._it_(i_MQGOc),[':']);
              if (cut_(MQGOc)<>'') and (not GetTimeStr(h,m,b,MQGOc)) then
                 begin
                   l4_err(a_L4,MQGOc,i_MQGOc,err_l4444_time, res);
                   goto X
                 end;
            {end
         else MQGOc:= ''};

         (*{$IFDEF FDP_OPL} datum:= form^.decode_DATUM (i_pozn0, ZAM^.zac, res,ires);
         {$ELSE}          datum:= assign_DATE (zac.rok,zac.mes,zac.den, zac.h,zac.m,zac.s);
         {$ENDIF}*)
         {datum:= form^.assign_DATE (date.r,date.m,date.d, hour,min,sec);}

         s:= cut_(form^._it_i(i_date));
         if (s<>'') then
            if decode_l4_date (s,QGO^.date) then form^.is_date:= true
            else begin
                   ires:= l4_err(a_L4,'',i_date,err_l4444_date, res);
                   goto X
                 end;
         if QGO^.dap.rok=0 then datum_init(QGO^.dap, day,month,year, hour,min,sec);

         _QGO_check:= true;
         Exit;

         X: _QGO_check:= false;
            form^.ErrorS(ires, res);
            disp_QGO(QGO);
       end;
   end;


function _QGO_date(QGO: PQGO; p: pointer; date: PDate): bool; far;
   begin
    { nepotrebujem kontrolovat na ziaden konflikt planu;
      mozno, ci nie je vyhlasene zamestanie...
    }
     if date<>nil then QGO^.date:= date^;
     _QGO_date:= true
   end;


procedure OQGOfrm.draw_buttons;
    begin
      upcas:= not (ind in[i_TQGO,i_MQGO]);
      inherited draw_buttons;
      upcas:= (ind in[i_TQGO,i_MQGO]);
    end;


function  formular_QGO(QGOi: PQGO; _uloz,_arch: bool): bool;
   const  f    : Tcentr = (x: initX; y: initY; m: 1);

   var    form : POQGOfrm;
          E    : TEvent;
          QGO  : TQGO;
          cis  : int;
          _novy   : bool;
          _p_date,_p_uloz_rpl : pointer;

   begin
     fillchar(QGO,sizeof(TQGO),0);

     _novy:= (QGOi=nil) or (_arch);
     if not _novy then
        begin
          new_QGO(QGOi,@QGO);
          QGO.stat:= del_cnl_stat(QGO.stat);
          {QGO.kod := QGOi^.kod;
          QGO.date:= QGOi^.date;
          QGO.stat:= QGOi^.stat;}
          _p_date:= nil
        end
     else begin
            {$IFDEF AIRBASE} QGO.kod := this_airbase;
            {$ENDIF}
            QGO.stat:= cnst_disk;
            _p_date:= @_QGO_date
          end;

     _p_uloz_rpl:= nil;
     {$IFDEF PROCESS_RPL} {$IFDEF OPL} _p_uloz_rpl:= @save_QGO_RPL; {$ENDIF} {$ENDIF}

     form:= New(POQGOfrm,Init(f.x,f.y, f.m, tit_schopnost+' '+QGO.kod,
                @Form_QGO,SIZE_frm_QGO,
                0,1, 0,0, 0,0,

                @_QGO_init,@_QGO_image,@_QGO_check, nil,
                @QGO, QGOi, @QGO.rec, letvis, QGO.stat,

                _novy, sizeof(TQGO),nil,nil,nil,nil,
                _p_date,_p_uloz_rpl,
                @zarad_QGO, @disp_QGO,

                true,false,true
                {$IFDEF ODOSLI_ULOZ}, _uloz or _novy {$ENDIF}
                {$IFDEF SKRY_OKNA}, false {$ENDIF}
                {$IFDEF STATISTIKA_OPL}, nil{p_info_STA_QGO} {$ENDIF}
                ));

     if form^.save_rpl_proc<>nil then
        begin
          form^.RPL_scroll_init (tit_PLANvzor,@get_dbQGO_RPLfn,
                           sizeof(TQGO),@new_QGO,@format_QGO,
                           db_QGO_RIADKOV,@decodeDB_QGO,
                           dx_QGO, dy_QGO, @plan_QGO
                          );
        end;

     form^.upcas:= false;
     form^.arch:= _arch and (QGOi<>nil);

     form^.RunLocalFunc(E,nil);
     formular_QGO:= form^.corr_res;
     Dispose(form,Done);

     disp_QGO(@QGO)
   end;

