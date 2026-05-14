function new_editor(_items,_znakov: byte; _text : byte): PForms;
     var   i     : int;
           ch    : PChars;  { Zmene z Pbytes ... }
           itemd : PForms;
     begin
       _items:= minimum(_items,max_size_Form);
       GetMem(ch,_znakov+1);
       FillChar(ch^,_znakov,ord(' '));
       ch^[_znakov]:= #0;
       GetMem(itemd,_items*sizeof(TForm));
       FillChar(itemd^,_items*sizeof(TForm),0);
       for i:= 0 to _items-1 do with itemd^[i] do
           begin
             item := StrNew(ch^);
             legal:= @setABCcs_;
             skip := @setNil;
             dx:= 5; dy:= 5+(i)*10; color:= _text
           end;
       FreeMem(ch,_znakov+1);
       new_editor:= itemd
     end;

procedure disp_editor(itemd: PForms; items: byte);
    var   i  : int;
    begin
      items:= minimum(items,max_size_Form);
      for i:= 0 to items-1 do StrDispose(itemd^[i].item);
      FreeMem(itemd,items*sizeof(TForm))
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TEditor                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

var ed_bg : byte;

procedure TEditor_image(x0,y0,x1,y1: int);
    begin
      on_off(x0,y0,x1,y1,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall, btOFF);
      FillWin(x0+2,y0+2,x1-2,y1-2,ed_bg)
    end;

constructor TEditor.Init(_Owner: PGroup;  var _x,_y, _mode: int; _cmXXXX: word;
                         _title: string;
                         _itemd: PForms;
                         _items,_znakov: byte;
                         _bg,_text, _abg,_atext: byte;

                         _inc_dx,_inc_dy : int;
                         _init_buttons,

                         _adr_var,
                         _disp_proc,
                         _init_form,
                         _check_func,
                         _done_form,
                         _handle_event : pointer;

                         _copy,_clear, _pole_en : bool;

                         _hlpXXX: Pchar
                        );
      var   i  : int;
            ch : Pbytes;
      begin
        ed_bg:= _bg;

        items := minimum(_items,max_size_Form);
        znakov:= minimum(_znakov,max_length_Form);

        alloc:= _itemd=nil;
        if alloc then itemd:= new_editor(_items,_znakov, _text)
        else itemd:= _itemd;

        inherited Init(_Owner, _x,_y,_mode, kbCtrlEnter,_cmXXXX,_title,
                       itemd,items,
                       _bg,_text, _abg,_atext, 0,_inc_dx,_inc_dy, 0, _init_buttons, 0,0, 0,0,
                       _adr_var, _init_form,_check_func,_done_form, @Teditor_image,_handle_event,
                       _copy,_clear, _pole_en,
                       _hlpXXX
                      );

        disp_proc:= _disp_proc;
        preskoc:= 0
      end; { Init }


destructor TEditor.Done;
     var   i : int;
     begin
       inherited Done;
       if alloc then disp_editor(itemd, items)
     end;


procedure TEditor.form_init(var x,y: int; dx,dy: int;
                            _kbHot: char; _cmXXXX: word;_title: string;
                            _tit : byte;  _inc_dx,_inc_dy: int
                           );
    begin
      inherited form_init(x,y, dx-dx_AForm+20,dy, _kbHot,_cmXXXX, _title, _tit,_inc_dx,_inc_dy);
      {if init_buttons<>nil then Tproc_p(init_buttons)(@Self)}
    end;


function TEditor.AcceptedKey(key: char): bool;
   begin
     AcceptedKey:= true;
     prev_ind:= ind;
     case key of
       kbEnter     : begin
                       Next(1);
                       itemv^[ind].i:= 0
                     end;

       kbHome      : with itemv^[ind] do i:= _lo;
       kbEnd       : last_char; {with itemv^[ind] do i:= _hi;}
       kbCtrlPgUp  : begin
                       Next(-ind);
                       itemv^[ind].i:= 0
                     end;
       kbCtrlPgDn  : begin
                       Next(items-ind-1);
                       itemv^[ind].i:= itemv^[ind]._hi
                     end;
       kbShiftTab,
       kbCtrlLeft  : FindLeftText;
       kbTab,
       kbCtrlRight : FindRightText;

       kbCtrlHome  : ;
       kbCtrlEnd   : ;

       else
       AcceptedKey:= inherited AcceptedKey(key)
     end;
   end; { TAForm.AcceptedKey }


procedure TEditor.WriteKey(key: char);
    begin
      with itemv^[ind] do
       begin
         if ins then with itemd^[ind] do Move(item[i],item[i+1],_hi-i);
         itemd^[ind].item[i]:= key;
         if itemv^[ind].i < itemv^[ind]._hi then MoveRight(1)
         else begin
                MoveRight(1);
                itemv^[ind].i:= 0
              end;
       end
    end;


{
  umozni pohyb kurzora po stranke; pri prechode na novy riadok neodskaukuje na posledny znak
}
procedure TEditor.Next(di: int);
    begin
      inherited Next(di);
      itemv^[ind].i:= itemv^[prev_ind].i
    end;


procedure TEditor.FindRightText;
    var   pom: int;
    begin
      pom:= ind;
      with itemv^[ind] do with itemd^[ind] do
        begin
          oi:= i;
          while (i < StrLen(item)) and (item[i]<>' ') do Inc(i);
          while (i < StrLen(item)) and (item[i]=' ') do Inc(i);
          if (i >= StrLen(item)) then
             begin
               i:= oi;
               if ind<items-1 then
                  begin
                    Next(1);
                    itemv^[ind].i:= 0;
                    if itemd^[ind].item[0]=' ' then FindRightText
                  end
             end
        end;
      prev_ind:= pom
    end;


procedure TEditor.FindLeftText;
    var   pom: int;
    begin
      pom:= ind;
      with itemv^[ind] do with itemd^[ind] do
        begin
          oi:= i;
          dec(i);
          while (i >= 0) and (item[i]=' ') do dec(i);
          if (i<0) then
             begin
               i:= oi;
               if ind>0 then
                  begin
                    Next(-1);
                    itemv^[ind].i:= itemv^[ind]._hi;
                    if itemd^[ind].item[itemv^[ind]._hi]=' ' then FindLeftText
                  end
             end
          else begin
                 while (i >= 0) and (item[i]<>' ') do dec(i);
                 if item[i+1]<>' ' then inc(i)
               end
        end;
      prev_ind:= pom
    end;