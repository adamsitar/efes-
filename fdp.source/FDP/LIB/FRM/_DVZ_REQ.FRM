{ ---------------------------------
   SPRACOVANIE ZIADOSTI O DIVERZIU
  ---------------------------------
}

 type  PREQ_DVZ = ^TREQ_DVZ;
       TREQ_DVZ = object(TFDP_AForm)
         procedure  init_buttons (x,y: int); virtual;
         procedure  handle_rqst (_rqst_res: Trqst); virtual;
       end;


 procedure TREQ_DVZ.init_buttons(x,y: int);
     var   bt1: PDialogButton;
           xt,yt, yi: int;
           _kbHot: char;
           DVZp : PDVZ;
     begin
       Win^.get_btXY(1,0, xt,yi);
       if (btList<>nil) and (btList^.ObjectType=obj_another) then btList^.Init(Win, xt,yi);

       Win^.get_btXY(0,0, xt,yt);
       bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titYES)),cmREQ_ACK,titYES,icKey,icText));

       Win^.get_btXY(0,1, xt,yt);
       bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titNO)), cmREQ_DCL,titNO,icKey,icText));

       DVZp:= PDVZ(adr_data);
       if (DVZp<>nil) and (pos(cnst_active,DVZp^.stat)=0) then { aktivovanie nie je mozne odlozit }
          begin
            Win^.get_btXY(0,3, xt,yt);
            bt1:= New(PDialogButton,Init(Win, xt,yt, GetAltCode(get_HotKey(_kbHot,titDLA)),cmREQ_DLA,titDLA, icKey,icText))
          end
     end;


 procedure TREQ_DVZ.handle_rqst(_rqst_res: Trqst);
     var   DVZ : PDVZ;
     begin
       DVZ:= PDVZ(adr_var);

       case _rqst_res of
         dla : zarad_DVZ(DVZ,cnst_prop+cnst_prop,false,letvis);
         ack,
         dcl : begin
                 if pos(cnst_active,DVZ^.stat)<>0 then
                      if _rqst_res=ack then DVZ^.stat:= cnst_dvz_zaa
                      else DVZ^.stat:= cnst_dvz_zad
                 else if _rqst_res=ack then DVZ^.stat:= cnst_acc
                      else DVZ^.stat:= cnst_dvz_dec;

                 zarad_DVZ(DVZ, cnst_read + DVZ^.stat, true, letvis);
                 {DVZ^.stat:= delchar(DVZ^.stat,[cnst_prop,cnst_read])
                 zarad_DVZ(DVZ, cnst_read + DVZ^.stat, false, letvis);}
               end
          else Exit
        end;
     end;


 function _REQ_DVZ_check(form: PREQ_DVZ; DVZ: PDVZ): bool; far;
    begin
      _REQ_DVZ_check:= _DVZ_read_plan (form,DVZ)
    end;


 function  formular_so_ziadostou_o_DVZ
              (DVZi: PDVZ;
               _beep: bool
              ): bool;

    const  f    : Tcentr = (x: initX; y: initY; m: 1);
    var    form : PREQ_DVZ;
           E    : TEvent;
           DVZ,DVZp : TDVZ;
           tit  : string;
    begin
      new_DVZ(DVZi,@DVZ);
      new_DVZ(DVZi,@DVZp);

      if pos(cnst_active,DVZi^.stat)<>0
         then tit:= tit_dvz_vyslanie+DVZ.pre+rep_ku+DVZ.kym+'.'
         else tit:= tit_dvz_schvalenie+DVZ.pre+rep_na+DVZ.kym+'.';

      form:= New(PREQ_DVZ, Init(f.x,f.y, f.m, tit,
                 @Form_DVZ, SIZE_frm_DVZ,
                 0,1, 0,0, 0,0,

                 @_DVZ_init,@_DVZ_image,@_REQ_DVZ_check,nil,
                 @DVZ, @DVZp, @DVZ.rec, letvis, DVZ.stat,
                 false, sizeof(TDVZ),nil,nil,nil,nil,
                 nil, nil,
                 nil{@zarad_DVZ->spravi handle_rqst},@disp_DVZ,

                 true,false,true
                 {$IFDEF ODOSLI_ULOZ}, false {$ENDIF}
                 {$IFDEF SKRY_OKNA}, false {$ENDIF}
                 {$IFDEF STATISTIKA_OPL}, nil {$ENDIF}
                 ));

      form^.beeping:= _beep or _ziadost_o_DVZ(nil,DVZi);
      form^.upcas:= false;
      form^.is_rqst:= true;

      form^.RunLocalFunc(E,REQ_DVZ_LocalMenu);
      formular_so_ziadostou_o_DVZ:= form^.corr_res;
      Dispose(form,Done);

      disp_DVZ(@DVZp);
      disp_DVZ(@DVZ)
    end;


 function  formular_pre_spracovanie_DVZ
              (DVZi: PDVZ;
               _beep: bool;
               _stat, _tit: string
              ): bool;

    const  f    : Tcentr = (x: initX; y: initY; m: 1);
    var    form : PREQ_DVZ;
           E    : TEvent;
           DVZ,DVZp : TDVZ;

    begin
      fillchar(DVZ,sizeof(TDVZ),0);
      new_DVZ(DVZi,@DVZ);
      new_DVZ(DVZi,@DVZp);

      if cut_(_stat)<>'' then DVZ.stat:= _stat;

      form:= New(PREQ_DVZ,Init(f.x,f.y,f.m, _tit,
                 @Form_DVZ,SIZE_frm_DVZ,
                 0,1, 0,0, 0,0,

                 @_DVZ_init,@_DVZ_image,@_REQ_DVZ_check,nil,
                 @DVZ, @DVZp, @DVZ.rec, letvis, DVZ.stat,
                 false, sizeof(TDVZ),nil,nil,nil,nil,
                 nil, nil,
                 @zarad_DVZ,@disp_DVZ,

                 true,false,true
                 {$IFDEF ODOSLI_ULOZ}, false {$ENDIF}
                 {$IFDEF SKRY_OKNA}, false {$ENDIF}
                 {$IFDEF STATISTIKA_OPL}, nil {$ENDIF}
                 ));

      form^.beeping:= _beep;
      form^.upcas:= false;

      form^.RunLocalFunc(E,nil);
      formular_pre_spracovanie_DVZ:= form^.corr_res;
      Dispose(form,Done);

      disp_DVZ(@DVZ)
    end;
