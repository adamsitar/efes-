{$IFDEF FLI_COORDINATION}

 const size_FLI = 13;
       form_FLI : array [0..size_FLI-1] of TForm =

         (( item : 'FLI-'; title : tit_3;
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:10; dy:10; font:0; color: white
          ),

          ( {$IFDEF GOST}item : '7a      '{$ELSE}item : '7a     '{$ENDIF};
            title : _l4_def.tit_7a;
            lst : nil; pos : 1; legal : @setABC; skip : @setNil;
            dx:46; dy:10; font:0; color: white{clGRe}
          ),


          ( item : '92  '; title : tit_9b;
            lst : @fn_9b; pos : 1; legal : @setABC ; skip : @setNil;
            dx:114; dy:10; font:0; color:0
          ),


          ( item : '13 1'; title : tit_13a;
            lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
            dx:156; dy:10; font:0; color:0
          ),

          ( item : '16 1'; title : tit_16a;
            lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
            dx:192; dy:10; font:0; color:0
          ),


          ( item : '14 1 '; title : tit_14a;
            lst : @fnFLI; pos : 1; legal : @setABC;  skip : @set_NXT;
            dx:235; dy:10; font:0; color:0
          ),
          ( item : '14 2'; title : tit_14b;
            lst : nil; pos : 1; legal : @setCisl_;   skip : @setNil;
            dx:277; dy:10; font:0; color:0
          ),
          ( item : '14  4'; title : tit_14d;
            lst : @fnAlt; pos : 1; legal : @setABC;  skip : @setNil;
            dx:311; dy:10; font:0; color:0
          ),
          ( item : '5';      title : tit_14e;
            lst : @fnAlt_ab; pos : 1; legal : @set_alt_;  skip : @setNil;
            dx:352; dy:10; font:0; color:0
          ),


          ( item : 'REG/'; title : '';
            lst : nil; pos : 1; legal : @setNil; skip : @setNil;
            dx:365{48}; dy:10; font:0; color: 0
          ),
          ( item : '18 1      '; title : _l4_def.tit_FREG;
            lst : nil; pos : 1; legal : @set_MTK_2abc; skip : @setNil;
            dx:399{80}; dy:10; font:0; color: 0
          ),


          ( item : 'DATE/'; title : '';
            lst : nil; pos : 1; legal : @setNil; skip : @setNXTPISM;
            dx:487{175}; dy:10; font:0; color: 0
          ),
          ( item : '18 2'; title : _l4_def.tit_FDATE+' [ddmm]';
            lst : nil; pos : 1; legal :    @setDig; skip : @setNXTPISM;
            dx:529{217}; dy:10; font:0; color: 0
          )
         );



 type   PFLIform = ^TFLIform;
        TFLIform = object(OTLGi_form)

          FPL : DcFPL;
          novy : bool;

          constructor Init (_tit  : string; var f : Tcentr;
                            _head : string;
                            _FPLi : PDcFPL;
                            _form_XXX : PForms; _size_XXX: int;
                            _first_pos: int; _image_form: pointer
                           );
          destructor  Done; virtual;

          procedure   init_formular_data; virtual;
          procedure   init_formular; virtual;

          function    read_formular_data(var res: string; var ires: int): string; virtual;
        end;



 procedure image_FLI (x0,y0,x1,y1: int); far;
     begin
       image_TLG (x0,y0,x1,y1);
     end;

 constructor TFLIform.Init (_tit : string; var f : Tcentr;
                            _head : string;
                            _FPLi : PDcFPL;

                            _form_XXX : PForms; _size_XXX: int;
                            _first_pos: int; _image_form: pointer
                           );

       begin
         head:= _head;
         novy:= _FPLi=nil;
         new_cFPL(_FPLi,@FPL);
         if _image_form=nil then _image_form:= @image_FLI;

         inherited Init (FPL.idn+' - '+_tit, f,
                         _head, '',
                         @form_TLGadr,size_TLGadr,
                         _form_XXX, _size_XXX, _first_pos,
                         nil,nil,nil,nil,_image_form, {_adr_var,_init_form,_check_func,_done_form,}
                         10, hlp_cFPL_FLI
                        );
       end;

 destructor TFLIform.Done;
      begin
        disp_cFPL(@FPL);
        inherited Done;
      end;


 procedure TFLIform.init_formular_data;
     var   s,t,u,r   : string;
           h,m,h_,m_ : byte;
           fli  : byte;
           reg  : string;
           FP4 : DFPL4;
     begin
       reg:= '';
       if read_FPL4(codekey_fpl(FPL.idn,FPL.start.kod,FPL.date), @FP4)>=0 then
          begin
            reg:= _item_18(FP4._18,rmk_REG,1);
            disp_FPL4(@FP4)
          end;

       with FPL do if cut_(idn)<>'' then
         begin

          { _7a }
           _in(o_f+1,idn);
           itemd^[o_f+1].legal:= nil;

          { _9 }
           decode_l4_9 (typ, s,t,u);
           _in(o_f+2,t);

          { _13 }
           _in(o_f+3,start.kod);
           if cut_(start.kod)<>'' then itemd^[o_f+3].legal:= nil;

          { _16 }
           _in(o_f+4,prist.kod);

          { _14 }
           fli:= FPL.przn[p_fli];
           if fli>=FPL.bodov then fli:= 0;
           if fli<FPL.bodov then
              begin
                _in(o_f+5, trat[fli].kod);
                _in(o_f+6, code_l4_utc (trat[fli].h,trat[fli].m));
                _in(o_f+7, code_l4_vys (trat[fli].vys,vysOB));
                _in(o_f+8, trat[fli].vysab);
              end;

          { _REG }
           _in(o_f+10, _item_18(@reg[1],rmk_REG,1));
         end;

      _in(o_f+12,code_l4_date_r(day,month,false))
    end;

 procedure TFLIform.init_formular;
     begin
       if cut_(FPL.idn)='' then first_pos:= 1+o_f
       else ins:= false;
       inherited init_formular;
       init_formular_data;
     end;


 function TFLIform.read_formular_data(var res: string; var ires: int): string;
    var   s,t,u: string;
          i: int;
          d,m,ss: byte;
          v: word; v_: char;
    label X;

    begin
      ires:= -1; res:= '';
      strdispose(data);

      data:= strpasnew(_it(o_f+0));

     { _7a }
      s:= _it(o_f+1);
      if cut_(s)='' then begin ires:= l4_err(a_7a,'', o_f+1,err_7a_missing, res); goto X end;
      if novy then FPL.idn:= s;
      data:= StrNPCopy(data,s,true,true);

     { _9b }
      s:= delchar(_it(o_f+2),[icao_NXT]);
      if cut_(s)='' then begin ires:= l4_err(a_9b,'', o_f+2,1, res); goto X end;
      if cut_(FPL.typ)='' then FPL.typ:= s;
      data:= StrNPCopy(data,icao_ARR+s,true,true);

     { _13a }
      s:= _it(o_f+3);
      if cut_(s)='' then ires:= l4_err(a_13a,'', o_f+3,3, res)
      else if length(s)<>kod_AP then ires:= l4_err(a_13a,'',o_f+3,err_13a_neznamy, res);
      if res<>'' then
         begin
           itemd^[o_f+3].legal:= @setPism_;
           goto X
         end;
      if (FPL.start.kod='') or novy then FPL.start.kod:= s;
      data:= StrNPCopy(data,icao_ARR+s,true,true);

     { _16a }
      s:= _it(o_f+4);
      if cut_(s)='' then ires:= l4_err(a_16a,'', o_f+4,3, res)
      else if length(s)<>kod_AP then ires:= l4_err(a_16a,'',o_f+4,err_16a_neznamy, res);
      if res<>'' then goto X;
      FPL.prist.kod:= s;
      data:= StrNPCopy(data,icao_ARR+s,true,true);

     { _14 }
      s:= _it(o_f+5);
      if cut_(s)='' then ires:= l4_err(a_TLG,'', o_f+5,10, res);
      if res<>'' then goto X
      else if novy then FPL.trat[0].kod:= s;

      t:= _it(o_f+6);
      if (cut_(t)='') or (length(t)<>kod_TIME) or (not GetTimeStr(d,m,ss, t)) then
         begin
           ires:= l4_err(a_TLG,'', o_f+6,12, res);
           goto X
         end
      else if novy then begin FPL.trat[0].h:= d; FPL.trat[0].m:= m; end;


      data:= StrNPCopy(data,icao_ARR+s+{icao_NXT+}t,true,true);

      s:= cut_(_it(o_f+7));
      t:= cut_(_it(o_f+8));
      if not decode_l4_vys(s, v,v_) then
         begin
           ires:= l4_err(a_14c,t,i_14c,0, res);
           goto X
         end
      else if novy then
              begin
                FPL.vys:= _vys_OB(v,v_);
                FPL.trat[0].vys:= FPL.vys;
              end;

      data:= StrNPCopy(data,cut_(icao_ARR+s+t),true,true);

     { REG/, DAT/ }
      s:= _it(o_f+10);
      t:= _it(o_f+12);
      if strlen(data)+length(s+t)>MTK_2_LINE{-20} then s:= s+kbNL;
      if (t='') or (not GetDateStr(v,m,d, t, false)) then
         begin
           ires:= l4_err(a_TLG,'', o_f+12,11, res);
           goto X
         end
      else if novy then init_date(FPL.date, v,m,d);

      s:= icao_ARR+rmk_REG +icao_NXT + s + icao_ARR+rmk_DATE+icao_NXT+t;
      data:= StrNPCopy(data,s,true,true);

      if novy then format_cFPL(@FPL);

      X: read_formular_data:= res
    end;



{ ---------------
  Volanie
  ---------------
}
 function  formular_FLI(FPL: PDcFPL): bool;
    const  f     : Tcentr = (x: initX; y: initY; m: 1);
    var    form  : PFLIform;
           Ev    : TEvent;

           {FPL0,}FPLi : DFPLC;
           tit,key : string;
           novy : bool;
           i    : int;

    begin
      formular_FLI:= false;
      {if (FPL<>nil) and (FPL^.przn[p_fli]>=FPL^.bodov) then Exit;}

      novy:= FPL=nil;
      key:= codekey_FPLC(FPL);

      tit:= tit_fpl_fli;
      form:= New(PFLIform,Init(tit,f, ht_FLI, FPL, @form_FLI,size_FLI, 2, nil));
      form^.RunLocalFunc(Ev,FDPFormLocalMenu);
      formular_FLI:= form^.corr_res;

      if form^.corr_res then
         begin
           FPL:= find_FPLCa(key);

           if update_FPLC_by_FLI then
              begin
              { Kontrola, ci boli zmenene niektore dolezite parametre,
                ak bolo zmenene letisko startu, zmazanie a oprava...
              }
                if (FPL<>nil) then
                   begin
                     new_cFPL(FPL,@FPLi);
                     if FPLi.typ<>form^.FPL.typ then begin novy:= true; FPLi.typ:= form^.FPL.typ end;
                     if FPLi.prist.kod<>form^.FPL.prist.kod then begin novy:= true; FPLi.prist.kod:= form^.FPL.prist.kod end;
                     if FPLi.start.kod<>form^.FPL.start.kod then
                        begin
                          novy:= true;
                          tit:= FPLi.stt;
                          if delete_FPLC_by_FLI then _zarad_FPLc(@FPLi,hd_CNL,true,[],letvis,'',true,false,false, nil,false);
                          FPLi.stt:= tit;
                          FPLi.start.kod:= form^.FPL.start.kod;
                        end;
                     disp_cFPL(@form^.FPL);
                     form^.FPL:= FPLi
                   end
              end;

             { Zapamatanie parametrov spracovania
               Ak rucne posielane fli je na nasledujuce ocakavane fli,
               automaticky sa uz neodosle. Ak nie, program spracovava
               fli podla vypocitanej postupnosti
             }
              tit:= form^._it(form^.o_f+5);
              if novy then
                 begin
                   if update_FPLC_by_FLI then
                      begin
                        _nastav_przn_fli(@form^.FPL,tit);
                        zarad_FPLc(@form^.FPL,hd_EST,true,letvis)
                      end
                 end
              else if FPL<>nil then
                     begin
                       novy:= FPL^.trat[FPL^.przn[p_fli]].kod=tit;
                       _nastav_przn_fli(FPL,tit);
                       _odoslane_FLI(FPL,false,novy,true)
                     end
         end;

      Dispose(form,Done)
    end;
{$ENDIF}
