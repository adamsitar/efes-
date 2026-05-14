{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TFormular                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{
  ddx a ddy oznacuju zvacsenie formulara oproti
  vypocitanej sirke a dlzke
}
constructor TFormular.Init(_Owner: PGroup;
                           var _x,_y, _mode: int;
                           _kbHot: char; _cmXXXX: word; _title: string;
                           _itemd: PForms; _items: byte;
                           _bg,_text{,_form},_abg,_atext: byte;

                           _dole: byte;      { kam spinace umiestnit }
                           _tit : byte;      { vypisovat title pre item ked, tak a ako ? }
                           _inc_dx,_inc_dy: int;  { len ak title = 1 (bude sa vypisovat dole) }
                           _init_buttons : pointer;

                           _dx_h, _dy_h: int;
                           _htext, _hbg: byte;

                           _adr_var: pointer;
                           _init_form, _check_func, _done_form: pointer;
                           _image_form: pointer;

                           _copy,_clear, _pole_en : bool;

                           _hlpXXX: Pchar
                           );
      begin
        inherited Init(_Owner, _x,_y, _mode, _kbHot,_cmXXXX,_title,
                       _itemd, _items,
                       _bg,_text, _abg,_atext,
                       _dole,_tit,_inc_dx,_inc_dy,_init_buttons, _dx_h,_dy_h,_htext,_hbg,
                       _adr_var,
                       _init_form, _check_func, _done_form,
                       _image_form, nil,
                       _copy,_clear, _pole_en,
                       _hlpXXX
                       );
      end; { TFormular.Init }


{
 vytvorenie okna podkladu a vypocet vlastnych suradnic x,y
}
procedure TFormular.form_init(var x,y: int; dx,dy: int;
                              _kbHot: char; _cmXXXX: word; _title: string;
                              _tit : byte;  _inc_dx,_inc_dy: int
                             );
    var   _dx,_dy, _x0,_y0: int;
    begin
      dx:= dx+_inc_dx;
      dy:= dy+15+_inc_dy;

      if (btList<>nil) and (btList^.ObjectType=obj_another) then
         begin
           get_win_btXY(nil, dole,2, _x0,_y0);
           if _y0+10+btHEIGHT>=dy then inc(dy, 10+btHEIGHT);
         end;

      Win:= New(PWindows,Init(nil, x,y, dx,dy, _kbHot,_cmXXXX,_title,'', true,dole, ord(btList<>nil),true));
      x:= Win^.x0 + 10;
      y:= Win^.y0 + dbtHEIGHT + 15;

      if (btList<>nil) and (btList^.ObjectType=obj_another) then
         begin
           Win^.get_btXY(dole,2, _x0,_y0);
           btList^.Init(Win, _x0,_y0{+btHEIGHT});
           btList^.bk0:= clBUTTON_COLOR;

           Win^.get_btXY(dole,0, _x0,_y0);
           PWindows(Win)^.btOk^.MoveRel(_x0-PWindows(Win)^.btOk^.x0,_y0-PWindows(Win)^.btOk^.y0);
           btOk:= PWindows(Win)^.btOk;

           Win^.get_btXY(dole,1, _x0,_y0);
           PWindows(Win)^.btCancel^.MoveRel(_x0-PWindows(Win)^.btCancel^.x0,_y0-PWindows(Win)^.btCancel^.y0);
           btCa:= PWindows(Win)^.btCancel;
         end;

      init_buttons(x,y)
    end;
