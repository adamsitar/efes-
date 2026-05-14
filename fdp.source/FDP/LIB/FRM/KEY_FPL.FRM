 procedure init_buttons_key(form: PFormular);
     var   bt : PButton;
           xt,yt, xp,yp: int;
           ch : char;
     begin
       if (form<>nil) and (form^.Win<>nil) then
          begin
            form^.Win^.get_btXY(1,0, xt,yt);
            if form^.btList<>nil then
               begin
                 xp:= form^.btList^.x0;
                 yp:= form^.btList^.y0;
                 form^.btList^.MoveRel(xt-xp,yt-yp);
                 xt:= xp; yt:= yp;
                 inc(yt,5);
               end;
            bt:= New(PDialogButton,Init(form^.Win, xt,yt,
                                  GetAltCode(get_HotKey(ch,titVSETKY)),
                                  form^.Win^.cmXXXX, titVSETKY,
                                  icKey,icText)
                                 );
          end;
     end;


{ vyziadanie identifikacie,
  je zakodovana sposobom ako kluc
}
 type  P_item_key_fpl = ^T_item_key_fpl;
       T_item_key_fpl = record
         key   : string;
         empty : bool
       end;


 function check_key_fpl(form: PFormular; data: P_item_key_fpl): bool; far;
    var   res,dat,let : string;
          date : Tdate;
          ires : int;
    label X;
    begin
      res:= ''; ires:= -1;

      data^.key:= form^._it(i_key_fpl_7a);
      if (cut_(data^.key)='') and (not data^.empty) then
         begin
           ires:= l4_err(a_7a,'',i_key_fpl_7a,7, res);
           goto X
         end;

      let:= form^._it(i_key_fpl_13a);

      init_date (date,year,month,day);
      if form^.items>size_key_rpl then
         begin
           dat:= form^._it(i_key_fpl_dat);
           if cut_(dat)<>'' then
              begin
                if not decode_l4_date_r (dat,date,true) then ires:= l4_err(a_L4,dat,i_key_fpl_dat,err_l4444_date, res)
                else if     ((form^.adr_par=nil) or ((form^.adr_par<>nil) and (not bool(form^.adr_par^))))
                        and (dateToSec(date.r,date.m,date.d)+secDAY<dateToSec(year,month,day)) then
                            ires:= l4_err(a_L4,dat,i_key_fpl_dat,err_l4444_date_not_actual, res);
                if (res<>'') then goto X
              end
         end;

      data^.key:= codekey_fpl(data^.key,let,date);
      check_key_fpl:= true;
      Exit;

      X : if (res<>'') then form^.errorS(ires,res);
      check_key_fpl:= false;
    end;


 function  formular_key_fpl(tit: string; _13a: PListDesc;
                            empty,date,all,arch: bool;
                            var key: string
                           ): bool;

    const  f     : Tcentr = (x: initX; y: initY; m: 1);
    var    form  : PFormular;
           Ev    : TEvent;
           data  : T_item_key_fpl;
           p,p2  : pointer;
           r     : int;
    begin
      data.key:= '';
      data.empty:= empty;
      if all then p2:= @init_buttons_key else p2:= nil;
      p:= form_key_fpl[i_key_fpl_13a].lst;
      if _13a<>nil then form_key_fpl[i_key_fpl_13a].lst:= _13a;
      if date then r:= size_key_fpl else r:= size_key_rpl;
      form:= New(PFormular,Init(nil, f.x,f.y,f.m, kbCtrlEnter,cmOK,
                 tit, @form_key_fpl,r, 0,0,0,0, 0, 100, 0,0,p2,0,0,0,0,
                 @data,nil,@check_key_fpl,nil,nil,true,false,false,hlp_FPLi_vyber)
                );
      form_key_fpl[i_key_fpl_13a].lst:= p;
      form^.adr_par:= @arch;
      form^.upcas:= true;
      form^.copy_back:= true;
      form^.RunLocalFunc(Ev,INFO_SELECT);
      formular_key_fpl:= form^.corr_res;
      Dispose(form,Done);
      key:= data.key
    end;
