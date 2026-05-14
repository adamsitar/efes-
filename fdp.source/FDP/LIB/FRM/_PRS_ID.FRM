 const  {$IFDEF SLOVAK}
          tit_area = 'K¢d priestoru       :';
          tit_dat  = 'Schv lenie [rr]mmdd :';
        {$ENDIF}

        {$IFDEF CZECH}
          tit_area = 'K¢d prostoru       :';
          tit_dat  = 'Schv len¡ [rr]mmdd :';
        {$ENDIF}

        {$IFDEF ENGLISH}
          tit_area = 'Area code         :';
          tit_dat  = 'Approval [yy]mmdd :';
        {$ENDIF}


        size_key_prs   = 4;

        i_key_prs_area = 1;
        i_key_prs_date = 3;


        form_key_prs : array [0..size_key_prs-1] of TForm =

          (( item : tit_area; title : tit_area;
             lst : nil; pos: 1; legal: @setNil;   skip : @setNil;
             dx:10; dy:10; font:0; color: white
           ),
           ( item : '       1'; title : tit_area;
             lst : @fnAREA; pos: 1; legal: @setABC;   skip : @setNil;
             dx:190; dy:10; font:0; color: white
           ),

           ( item : tit_dat; title: tit_dat;
             lst : nil; pos: -1; legal: @setNil;  skip : @setNil;
             dx:10; dy:25; font:0; color: 0
           ),
           ( item : '3     '; title: tit_dat;
             lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
             dx:190; dy:25; font:0; color: 0
           )
          );


 type  P_item_key_prs = ^T_item_key_prs;
       T_item_key_prs = record
         key   : TPRS_key;
         empty : bool
       end;

 function check_key_prs(form: PAForm; data: P_item_key_prs): bool; far;
    var   res,s : string;
          date  : Tdate;
          ires  : int;
    label X;
    begin
      res:= ''; ires:= -1;

      data^.key.kod:= _unique_area_code(form^._it(i_key_prs_area));
      if (cut_(data^.key.kod)='') and (not data^.empty) then
         begin
           ires:= l4_err(a_FUA,'',i_key_prs_area,0, res);
           goto X
         end;

      s:= form^._it(i_key_prs_date);
      init_date (date,year,month,day);
      if cut_(s)<>'' then
         begin
           if not decode_l4_date_r (s, date,true) then ires:= l4_err(a_L4,s,i_key_prs_date,err_l4444_date, res)
           else if     ((form^.adr_par=nil) or ((form^.adr_par<>nil) and (not bool(form^.adr_par^))))
                   and (dateToSec(date.r,date.m,date.d)+secDAY < dateToSec(year,month,day)) then
                       ires:= l4_err(a_L4,s,i_key_prs_date,err_l4444_date_not_actual, res);
           if (res<>'') then goto X
         end;

      {$IFDEF AIRBASE}
       data^.key.let:= airbase;
      {$ENDIF}

      check_key_prs:= true;
      Exit;

      X : if (res<>'') then form^.errorS(ires,res);
      check_key_prs:= false;
    end;

 function  formular_key_prs(tit: string;
                            _area: PListDesc;
                            empty,arch: bool;
                            var key: TPRS_key
                           ): bool;

    const  f     : Tcentr = (x: initX; y: initY; m: 1);
    var    form  : PFormular;
           Ev    : TEvent;
           data  : T_item_key_prs;
           p     : pointer;
    begin
      data.key:= key;
      data.empty:= empty;
      p:= form_key_prs[i_key_prs_area].lst;
      if _area<>nil then form_key_prs[i_key_prs_area].lst:= _area;
      form_key_prs[i_key_prs_area].lst:= @fn_13aM;
      form:= New(PFormular,Init(nil, f.x,f.y,f.m, kbCtrlEnter,cmOK,
                 tit, @form_key_prs,size_key_prs, 0,0,0,0, 0, 100, 0,0,@init_buttons_key,0,0,0,0,
                 @data,nil,@check_key_prs,nil,nil,true,false,false,nil)
                );
      form_key_prs[i_key_prs_area].lst:= p;
      form^.adr_par:= @arch;
      form^.upcas:= true;
      form^.copy_back:= true;
      form^.RunLocalFunc(Ev,INFO_SELECT);
      formular_key_prs:= form^.corr_res;
      Dispose(form,Done);
      key:= data.key
    end;