{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TFDPform                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

procedure TFDP_AForm.init_buttons(x,y: int);
    var   bt1 : PButton;
          bt2 : PbtCancel;
          bti : PTextIcon;
          xt,yt, yi : int;
          kbht : char;
    begin
      inherited init_buttons(x,y);

      pos_RPL:= 0;
      if rpl or (save_rpl_proc<>nil) then
         begin
           Win^.get_btXY(xp_btRPL,0, xt,yt);
           btRPL:= New(PTextIcon,Init(Win, xt,yt, 60,4, GetAltCode(get_HotKey(kbht,titVZOR)), cmVLOZ_VZOR, titVZOR, @IcList))
         end
      else btRPL:= nil;

      if (btList<>nil) and (btList^.ObjectType=obj_another) then
         begin
           Win^.get_btXY(xp_btList,0, xt,yi);
           btList^.Init(Win, xt,yi);
           btList^.bk0:= clBUTTON_COLOR
         end;

      bt1:= nil;
      bt2:= nil;

      Win^.btTitle^.cmXXXX:= cmNil;
      Win^.btTitle^.kbAct:= kbNoKey;
      Win^.btTitle^.kbHot:= kbNoKey;
      Win^.btTitle^.kbAltHot:= kbNoKey;
      {Win^.btTitle^.cmXXXX:= cmODOSLI_PLAN;}

      if dole=1 then inc(bt_y);
      {$IFDEF ODOSLI_ULOZ}
       {if (send_proc<>nil) then}
          begin
            Win^.get_btXY(dole,bt_y, xt,yt);
            bt1:= New(PTextIcon,Init(Win, xt,yt, 60,5, GetAltCode(get_HotKey(kbht,titSEND)),cmODOSLI_PLAN,titSEND,@icYes));
            bt1^.kbAltHot:= kbCtrlEnter;
            inc(bt_y)
          end;

       if uloz {and (save_proc<>nil)} then
          begin
            Win^.get_btXY(dole,bt_y, xt,yt);
            btUloz:= New(PTextIcon,Init(Win,xt,yt,60,4,GetAltCode(get_HotKey(kbht,titSAVE)),cmULOZ_PLAN,titSAVE,@icList));
            inc(bt_y)
          end
       else btUloz:= nil;

       if {uloz and} (save_rpl_proc<>nil) then
          begin
            Win^.get_btXY(dole,bt_y, xt,yt);
            bt1:= New(PTextIcon,Init(Win,xt,yt,60,4,GetAltCode(get_HotKey(kbht,titSAVErpl)),cmULOZ_VZOR,titSAVErpl,@icList));
            inc(bt_y)
          end;

       Win^.get_btXY(dole,bt_y, xt,yt);
       bt2:= New(PbtCancel,Init(Win,xt,yt));
       inc(bt_y);

      {$ELSE}
       Win^.get_btXY(dole,0, xt,yt);
       bt1:= New(PbtOK, Init(Win,xt,yt, kbCtrlEnter));
       inc(bt_y);

       Win^.get_btXY(dole,bt_y, xt,yt);
       bt2:= New(PbtCancel,Init(Win,xt,yt));
       inc(bt_y);
      {$ENDIF}


      off_y:= 5;
      (*{$IFDEF STATISTIKA_OPL}
       if (not is_rqst) {and (statistika_proc<>nil)} then
          begin
            Win^.get_btXY(0,bt_y, xt,yt);
            bt1:= New(PDialogButton,Init(Win, xt,yt+off_y,
                      GetAltCode(get_HotKey(kbht,titSTATIS)),cm_PRIEBEZNA_DENNA_STATISTIKA,titSTATIS,
                      icKey,icText));
            inc(bt_y)
          end;
      {$ENDIF}*)

      btOk:= bt1;
      btCa:= bt2;
    end;


constructor TFDP_AForm.Init(var _x,_y,  _mode: int; _title: string;

                            _itemd: PForms; _items: byte;

                            _dole : byte;         { kam spinace umiestnit }
                            _tit  : byte;         { vypisovat title pre item ked, tak a ako ? }
                            _inc_dx,_inc_dy,      { len ak title = 1 (bude sa vypisovat dole) }
                            _dx_h,_dy_h: int;

                            _init_form,           { inicializacia dat   }
                            _image_form: pointer; { vykreslenie ciar    }
                            _check_func: pointer; { kontrola regularity }

                            _hlpXXX : Pchar;      { ukazovatel na help  }

                            _adr_var   : pointer;
                            _adr_data  : pointer; { adresa premennej s povodnymi datami }

                            _rec       : Pplan_rec;
                            _src       : fdp_src;
                            _stat      : string;

                            _novy      : bool;
                            _data_size : word;
                            _code_key  : PSFunc_p;
                            _read_orig : PIFunc_sp;
                            _is_data,
                            _chg_data  : PPLAN_zmeneny;

                            _date_proc,           { zadanie datumu TBFunc_p3(p,c,d: pointer) }
                            _save_rpl_proc,       { ulozenie rpl Tproc_p(p: pointer)    }
                            _zarad_proc,
                            _disp_proc: pointer;

                            _copy,_clear,_pole_en: bool

                            {$IFDEF ODOSLI_ULOZ};
                             _uloz : bool         { ma sa zobrazit btUloz ? }
                            {$ENDIF}
                            {$IFDEF SKRY_OKNA};
                             _skry : bool         { skry formular pri ukonceni editacie }
                            {$ENDIF}

                            { specializovane fcie
                            }
                            {$IFDEF STATISTIKA_OPL};
                              _statistika_proc : pointer
                            {$ENDIF}
                           );

      begin
        rpl:= false;
        {$IFDEF ODOSLI_ULOZ} uloz:= _uloz; {$ENDIF}
        {$IFDEF SKRY_OKNA} skry:= _skry;   {$ENDIF}

        bt_y:= 0;
        {$IFDEF ODOSLI_ULOZ} btUloz:= nil; {$ENDIF} { Pre istotu, ak niekto nezavola inherited form_init }
        btRPL:= nil;
        RPL_scroll_init ('',nil,0,nil,nil,0,nil,0,0,nil);

        date_proc:= _date_proc;
        save_rpl_proc:= _save_rpl_proc;
        zarad_proc:= _zarad_proc;
        {$IFDEF STATISTIKA_OPL};
         statistika_proc:= _statistika_proc;
        {$ENDIF}

        inherited Init(nil,  _x,_y,_mode,  kbCtrlEnter, cmOK,
                       _title, _itemd, _items,
                       clBUTTON_COLOR,cfText,clGR1,cfActT,
                       _dole,_tit, _inc_dx,_inc_dy,nil, _dx_h,_dy_h, 0,0,
                       _adr_var,_adr_data, _rec,
                       _novy,
                       _data_size, _code_key, _read_orig, _is_data, _chg_data,
                       _init_form, _check_func, nil {_done_form},
                       _image_form, nil{_handle_event},
                       _hlpXXX,
                       _copy,_clear,_pole_en
                      );

        disp_proc:= _disp_proc;

        if btRPL<>nil then btRPL^.visible:= false{_pos=pos_RPL};

        ins       := _novy;
        ins_date  := true;
        p_is_date := nil;

        src       := _src;
        stat      := _stat;

        arch      := false{_arch};
        posli     := true;

        ClearEvent(res_ev);
        command:= cmOK;
      end;


procedure TFDP_AForm.init_formular; { inicializacia formulara  }
    begin
      arch:= arch and (adr_data<>nil);
      if clear and (init_form<>nil) then
         if (adr_data<>nil) then Tproc_p2(init_form)(@Self,adr_data)
         else Tproc_p2(init_form)(@Self,adr_var)
      else if clear_list then clear_form(itemd,items,nil)
    end;


procedure TFDP_AForm.draw_buttons;
    begin
      if (btRPL<>nil) and (ind<>pos_RPL) and (btRPL^.visible) then
         begin
           btRPL^.hide;
           if (btList<>nil) and (btList^.visible) then
              begin
                btList^.hide;
                btList^.MoveRel(-dbtWIDTH-dbtDX,0);
                btList^.Draw
              end
         end;
      inherited draw_buttons;
      if (btRPL<>nil) and (ind = pos_RPL) and (not btRPL^.visible) then
         begin
           btRPL^.show;
           if (btList<>nil) and (btList^.visible) then
              begin
                btList^.MoveRel(dbtWIDTH+dbtDX,0);
                btList^.Draw
              end
         end
    end;

{ V checkom je vela goto, ale musel som narychlo rozbit
  povodnu fciu HandleEvent
}
function TFDP_AForm.check_date(var _Event: TEvent): bool;

    function _check_date(ppl_en: bool): bool;
       var   date   : TDate;
             p_date : PDate;
             xd,yd  : int;
       begin
         _check_date:= true;
         p_date:= nil;

         {$IFDEF PPL}
          { zadanie datumu platnosti planu, ak nie je
            co sa nastavi is_date, alebo by mohli byt
            definovate smerniky na datum...
          }
           if (date_proc<>nil) and ppl_en and novy and (not is_date) then
              begin
               {$IFDEF ODOSLI_ULOZ}
                if btUloz<>nil then begin xd:= btUloz^.x0; yd:= btUloz^.y0 end
                else
               {$ENDIF}
                begin xd:= x0+10; yd:= y0 end;

                if     (ins_date)
                   and (   (p_is_date=nil)
                        or ((p_is_date<>nil) and TBFunc_p(p_is_date)(adr_var))
                       ) then
                   begin
                     if not formular_DATUM(date, xd,yd+20,tit_dayPLAN) then
                        begin
                          _check_date:= false;
                          Exit
                        end
                     else p_date:= @date
                   end
              end;
         {$ENDIF}

         if date_proc<>nil then _check_date:= TBfunc_p3(date_proc)(adr_var,adr_data,p_date)
       end;

   var   is_to_close: bool;
   label F;

   begin
     check_date:= false;
     corr_res:= false;
     is_to_close:= false;
     if (not viewer) then
        begin
          is_to_close:= true;
          case res_ev.Command of
            cmOK          : if not _check_date(false) then goto F;
            cmODOSLI_PLAN : if not _check_date(true)  then goto F;
            cmULOZ_PLAN   : if not _check_date(true)  then goto F;
            else is_to_close:= false;
          end;
        end
     else if isCommand(res_ev,cmOK) then is_to_close:= true;
     if is_to_close then
        begin
          _Event:= res_ev;
          cmXXXX:= _Event.Command
        end;
     corr_res:= true;
     check_date:= true;
     F: ClearEvent(_Event)
   end;


function TFDP_AForm.call_check_func(var _Event: TEvent): bool;
   var   res : bool;
   begin
     res_ev:= _Event;
     is_date:= false;  { vo formulari bol zadany datum, uz sa nan nepytam... }
     res:=     TAForm.call_check_func(_Event)
           and check_date(_Event)
           and check_data_not_chg(res_ev);
     call_check_func:= res
   end;


procedure TFDP_AForm.HandleEvent(var _Event: TEvent);
    var   res, b : bool;
    label X;

    begin
      inherited HandleEvent(_Event);

      if      ((_Event.What and evMessage) <> 0)
          and (   (_Event.Command = cmODOSLI_PLAN)
               or (_Event.Command = cmULOZ_PLAN)
               or (_Event.Command = cmULOZ_VZOR)
               or (_Event.Command = cmOK)
              )
        then
         begin
           command:= _Event.Command;
           if (viewer) or (command=cmULOZ_PLAN) then posli:= false
           else posli:= true;
           if not posli then stat:= cnst_disk
           else if (stat=cnst_disk) then stat:= cnst_sended;
           res:= call_check_func(_Event);
           if res then
              begin
                if (not viewer) then
                   begin
                     case res_ev.Command of
                       cmULOZ_VZOR  :
                         begin
                           if (save_rpl_proc<>nil) then proc__adr_var(save_rpl_proc,adr_var);
                           {Say2(msgINFO,msgDATA_SAVED);}
                           corr_res:= false;
                         end;
                     end;
                   end;
              end
           else if (disp_proc<>nil) then proc__adr_var(disp_proc,adr_var);

           ClearEvent(_Event)
         end

      else if (_Event.What and evMessage) <> 0 then
         begin
           case _Event.Command of
             cmVLOZ_VZOR : init_formular_RPL;

             {$IFDEF STATISTIKA_OPL}
              cm_PRIEBEZNA_DENNA_STATISTIKA : if statistika_proc<>nil then TProc(statistika_proc);
             {$ENDIF}

             else Exit;
           end;

           ClearEvent(_Event)
         end;

    end; { TFDP_AForm.HandleEvent }



procedure TFDP_AForm.RunLocalFunc(var _Event: TEvent; Info: PChar);
    begin
      if Info=nil then Info:= FDPFormLocalMenu;
      inherited RunLocalFunc(_Event, Info)
    end;


function TFDP_AForm.EndState(var _Event: TEvent): bool;
   begin
     EndState:=    ((corr_res) and (cmXXXX=res_ev.Command))
                or TGroup.EndState(_Event)
                or is_cancel
   end;


{ Aby nebolo potrebne skryvat okna pri radeni na obrazovku, az na koniec
}
procedure TFDP_AForm.DoneApp;
    begin
      if (not viewer) and corr_res then
         begin
           if zarad_proc<>nil then TPLAN_zarad(zarad_proc)(adr_var,stat,posli,src);
           {if (save_proc<>nil) then proc__adr_var(save_proc,adr_var);
           if (add_proc<>nil) then proc__adr_var(add_proc,adr_var);
           if (posli) and (send_proc<>nil) then proc__adr_var(send_proc,adr_var);}
         end;
      if disp_proc<>nil then proc__adr_var(disp_proc,adr_var)
    end;



{ Spracovanie databazy RPL
}
procedure TFDP_AForm.RPL_scroll_init
                (_tit_RPL    : string;     { hlavicka v ponuke }
                 _p_fn_RPL   : pointer;    { funkcia, ktora vrati nazov rpl-subora }

                 _item_size  : word;
                 _new_item,_format_item : pointer;

                 _db_riadkov : byte;
                 _decode_db  : pointer;

                 _dx_item,_dy_item : int;
                 _draw_item  : pointer
                );
    begin
      tit_RPL:= _tit_RPL;
      p_fn_RPL:= _p_fn_RPL;

      item_size:= _item_size;
      new_item:= _new_item;
      format_item:= _format_item;

      db_riadkov:= _db_riadkov;
      decode_db:= _decode_db;

      dx_item:= _dx_item;
      dy_item:= _dy_item;
      draw_item:= _draw_item
    end;


function initialize_RPL(sc: PScroller; p: pointer; form: PFDP_AForm): bool; far;
   var   temp: pointer;
   begin
     initialize_rpl:= true;
     if form=nil then Exit;

     temp:= form^.adr_data;
     form^.adr_data:= p;
     form^.arch:= true;
     form^.init_formular;
     form^.adr_data:= temp
   end;

procedure TFDP_AForm.init_formular_RPL;
    begin
      if (p_fn_RPL=nil) or (item_size=0) or (db_riadkov=0) or (decode_db=nil) then Exit;
      scroll_DB (tit_RPL, false,false,
                 max_form_rpls,item_size,
                 new_item,format_item,disp_proc,nil,
                 nil,nil,nil,nil,nil,
                 true, nil, nil,
                 _TBFunc_p2,@initialize_RPL, @Self,
                 TSFunc(p_fn_RPL),nil,nil,
                 db_riadkov,decode_db,nil,
                 dx_item, dy_item, draw_item,
                 0,0,nil,nil,nil,
                 nil, nil
               );
      Draw
    end;


{ Vracia, ci datum bol (predtym alebo nacitanim z poznamky)
  inicializovany
}
function TFDP_AForm.decode_DATE(it18: int; var date: TDate; var res: string; var ires: int): bool;
   var   s: string;
         p1,p2: pchar;
         bres: bool;
   label X;
   begin
     decode_DATE:= false;
     read_pole (it18,p1);
     p2:= l4line(p1);
     s:= cut_(_item_18_(p2,rmk_DATE,-1));
     strdispose(p2);
     strdispose(p1);

     if     (not novy) and (date.r<>0)
        and (    (s<>code_l4_date_r(date.d,date.m,true))
             and (s<>code_l4_date(date))
            ) then
        begin
        { plan uz ma priradeny datum platnosti
        } if s<>'' then ires:= l4_err(a_L4,s,it18,err_l4444_date_duplicite , res);
          goto X
        end;

     if s='' then
        begin
          init_date(date, year,month,day);
          goto X
        end;

     if pos('.',s)>0 then bres:= GetDateStr(date.r,date.m,date.d,s,false)
     else bres:= decode_l4_date_r(s,date,true);
     if bres {GetDateStr(date.r,date.m,date.d, s, false)} then
       if DateToSec(date.r,date.m,date.d) >= DateToSec(Year,Month,Day) then
          begin
            is_date:= true;
          end
       else ires:= l4_err(a_L4,s,it18,err_l4444_date_not_actual, res)
     else ires:= l4_err(a_L4,s,it18,err_l4444_date, res);

     X: decode_DATE:= (res='') and (ires<0)
   end;


function TFDP_AForm.decode_DATUM(it18: int; var datum: TDatum; var res: string; var ires: int): bool;
   var   date: TDate;
   begin
     init_date  (date,datum.rok,datum.mes,datum.den);
     decode_DATUM:= decode_DATE(it18,date,res,ires);
     datum.rok:= date.r; datum.mes:= date.m; datum.den:= date.d
   end;


function TFDP_AForm.assign_DATE(var rok: word; var mes,den: byte; h,m,s: byte): bool;
   begin
     assign_DATE:= false;
     if rok<>0 then Exit;

     den:= day; mes:= month; rok:= year;
     assign_DATE:= true;
     if     (DTtoSec(rok,mes,den, h,m,s) < DTtoSec(year,month,day, hour,min,sec))
        and (Ask2(msgVERIPHY,askNotActual,'',White,clBUTTON_COLOR,waitASK*18)= ansAno)
        then NextDate(rok,mes,den)
   end;


procedure TFDP_AForm.get_stat (var _stat: string; var _command: word);
    begin
      _stat:= stat;
      _command:= command
    end;

procedure TFDP_AForm.set_stat (_stat: string);
    begin
      stat:= _stat;
    end;

