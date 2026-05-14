{ -------------------------
   ADRESA TLG
  -------------------------
}
 { Formular ma ako prve pole pole adries form_TLGadr !
 }

 procedure image_TLG(x0,y0,x1,y1: int); far;
     begin
       image_TLGadr(x0,y0,x1,y1);
     end;


 constructor OTLGi_form.Init(_tit : string; var f : Tcentr;
                             _head: string; _n_a : string;
                             _form_ADR : PForms; _size_ADR: int;
                             _form_XXX : PForms; _size_XXX: int;
                             _first_pos: int;
                             _adr_var: pointer;
                             _init_form, _check_func, _done_form, _image_form: pointer;
                             _inc_dy : int; _hlpXXX: Pchar
                            );
       var   _kbHot: char;
       begin
         head:= _head; prty:= ''; adr:= ''; data:= nil;

         init_itemd (_form_ADR,_size_ADR, _form_XXX,_size_XXX);
         if {(_size_ADR+_size_XXX) * 10} graphmode>_VGA then dole:= 0 else dole:= 1;
         if _image_form=nil then _image_form:= @image_TLG;
         inherited Init(nil, f.x,f.y,f.m,
                        kbCtrlEnter,cmOK, _tit,
                        itemd,items,
                        0,0,0,0,
                        dole,1,
                        0,_inc_dy,nil,
                        0,0,
                        0,0,
                        _adr_var, _init_form, _check_func, _done_form,
                        _image_form,
                        false,false,true,
                        _hlpXXX
                       );
         first_pos:= o_f+_first_pos;
         n_a:= _n_a; if n_a='' then n_a:= icao_ARR;
         upcas:= true;

         if btOK<>nil then with btOk^ do
            begin
              new_title(' '+titSEND+' ',false);
              kbAltHot:= GetAltCode(get_HotKey(_kbHot,titSEND))
            end;
       end;


 destructor OTLGi_form.Done;
      begin
        copy_form(@itemd^[0],p_form_ADR,i_form_ADR);
        copy_form(@itemd^[i_form_ADR],p_form_XXX,i_form_XXX);
        inherited Done;
        if itemd<>nil then disp_form(itemd,items);
        if data<>nil then strdispose(data)
      end;


 procedure OTLGi_form.init_tlg_adr;
     begin
       _tlg.init_tlg_adr(head,@Self,i_tlg_prty)
     end;

 procedure OTLGi_form.init_tlg_data;
     begin
       if p_form_XXX<>nil then copy_form(p_form_XXX,@itemd^[o_f],i_form_XXX)
     end;


{ vytvorenie formulara pre spojenim dvoch existujucich frmTLG a tlgMSG
}
 procedure OTLGi_form.init_itemd (_form_ADR : PForms; _size_ADR: int;
                                  _form_XXX : PForms; _size_XXX: int
                                 );
     var   i : int;
           s : string;

     begin
       if _form_ADR<>nil then
          begin
            p_form_ADR:= _form_ADR;
            i_form_ADR:= _size_ADR;
          end
       else begin
              p_form_ADR:= @form_TLGadr;
              i_form_ADR:= size_TLGadr;
            end;
       p_form_XXX:= _form_XXX;
       i_form_XXX:= _size_XXX;

       items:= i_form_ADR + i_form_XXX;
       itemd:= alloc_form (items);
       o_f:= i_form_ADR;

       acpy_form(@p_form_ADR^[0], @itemd^[0],   i_form_ADR);
       acpy_form(@p_form_XXX^[0], @itemd^[o_f], i_form_XXX);

       for i:= 0 to i_form_XXX-1 do inc(itemd^[o_f+i].dy,dy_TLGadr)
     end;


 procedure OTLGi_form.form_init (var x,y: int; dx,dy: int;
                                 _kbHot: char; _cmXXXX: word; _title: string;
                                 _tit : byte;  _inc_dx,_inc_dy: int
                                );
     var   xt,yt, yi,c : int;
     begin
       inherited form_init(x,y, dx,dy, _kbHot,_cmXXXX,_title,_tit,_inc_dx,_inc_dy);

      {$IFDEF A36YKA}
       Win^.get_btXY(1,0, xt,yt);
       if btA36=nil then
          begin
            btA36:= New(PDialogButton,Init(Win, Win^.x1-dbtWIDTH-(xt-Win^.x0),yt,kbAltA,cmA36YKA,titA36,icKey,icText));
            btA36^.click:= ord(false);
            btA36^.stat:= TbtStat(is_kblayout);
          end;
      {$ENDIF}
     end;


 { ---------------
   Naplnenie
   ---------------
 }
  procedure OTLGi_form.init_formular;
      begin
        init_tlg_adr;
        init_tlg_data
      end;



 { ---------------
   Spracovanie
   ---------------
 }
 function OTLGi_form._read_tlg_prty(var _prty: string; var _res: string; var _ires: int): string;
    begin
      _prty:= cut_(_it(i_tlg_prty));
      if is_mtkprty(_prty+icao_NXIT+icao_ARR)='' then _ires:= l4_err(a_TLG,_prty, i_tlg_prty,2, _res);
      if _prty='' then _ires:= l4_err(a_TLG,'',i_tlg_prty,1, _res);
      _read_tlg_prty:= _res
    end;


 function OTLGi_form._read_tlg_adr(size_adr: int; var _adr: string; var _res: string; var _ires: int): string;
    var   i,al,ires : int;
    begin
      al:= 0;
      for i:= i_tlg_adr to size_adr-1 do
          begin
            ires:= _check_mtk_adr (cut_(_it(i)), _adr,al,false,0,_res);
            if ires<>-1 then break
            {s:= cut_(_it(i));
            if (s<>'') then
               for j:= 1 to getstritems(s,[icao_NXIT]) do
                 begin
                   a:= getstr(s,j,[icao_NXIT]);
                   if (length(a)<_MTK_ADR_lo) or (length(a)>_MTK_ADR_hi) then
                      begin
                        _ires:= l4_err(a_TLG,a, i_tlg_adr,4, _res);
                        goto X
                      end;
                   if a<>'' then
                      begin
                        if _adr<>'' then a:= icao_NXIT+a;
                        _adr:= _adr+a;
                      end;
                   inc(al,length(a))
                 end;}
          end;
      {if al=0 then _ires:= l4_err(a_TLG,'',i_tlg_adr,3, _res);}
      {xxif al>_MTK_ADR_ar then l4_err(a_TLG,'',5,5, _res);}
      if _res='' then ires:= _check_mtk_adr ('', _adr,al,true,0,_res);
      if ires<>-1 then _ires:= i_tlg_adr;

      _read_tlg_adr:= _res
    end;


 function OTLGi_form.read_tlg_adr(size_adr: int; var _prty,_adr: string; var _res: string; var _ires: int): string;
    begin
      _prty:= ''; _adr:= '';
      read_tlg_adr:= msg_NO_ADR;
      _res:= '';

     { a) priorita
     } _res:= _read_tlg_prty(_prty,_res,_ires);

     { b) nacitanie adries
     } if _res='' then _res:= _read_tlg_adr(size_adr,_adr,_res,_ires);

      read_tlg_adr:= _res
    end;


 function OTLGi_form._read_formular_data (var res: string; var ires: int): string;
    var   a,s,t : string; p: char;
          i : int;
    begin
     (* b) nacitanie dat do pola

      i:= o_f; p:= ' ';
      while i<items do
        begin
          s:= _it(i); t:= cut_(s);
          if s<>'' then p:= s[length(s)] else p:= ' ';
          if (i>=o_f) then
             begin
               if (is_polex(i,i+1) or is_poley(i,i+1)) then a:= n_a
               else if t<>'' then a:= icao_ARR
               else a:= '';
               if      (a=icao_ARR)
                   and (    ((strlen(data)>0) and (data[strlen(data)-1]=icao_ARR))
                         or ((t<>'') and (t[length(t)]=icao_ARR))
                       ) then a:= '';
             end
          else a:= '';
          data:= StrNPCopy(data,s+a,true,true);
          inc(i)
        end;
      *)

      _read_formular_data:= ''
    end;

 function OTLGi_form.read_formular_data (var res: string; var ires: int): string;
    begin
      if data<>nil then strdispose(data);
      read_formular_data:= _read_formular_data(res,ires)
    end;


 function OTLGi_form.read_formular(var res: string; var ires: int): string;
    begin
      if data<>nil then StrDispose(data);

      res:= read_tlg_adr({@Self,}o_f, prty,adr, res,ires);
      if res='' then res:= read_formular_data(res,ires);

      read_formular:= res
    end;


 function OTLGi_form.check_formular_data(var res: string; var ires: int): string;
    begin
      check_formular_data:= ''
    end;


 function OTLGi_form.send_formular(var res: string; var ires: int): string;
    begin
      send_formular:= _proc_send_TLG (prty,adr,head, @data[0],strlen(data))
    end;


 function OTLGi_form.check_formular: bool;
    var   res: string; ires: int;
    begin
      res:= ''; ires:= -1;

      if read_formular (res,ires)='' then
         if check_formular_data (res,ires)='' then
            if data<>nil then res:= send_formular (res,ires);

      if res<>'' then
         if ires<0 then Err2('',res)
         else ErrorS(ires,res);

      check_formular:= res=''
    end;
