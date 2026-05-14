{ ========================

   FPL4 pre RPL a FPL4

  תתתתתתתתתתתתתתתתתתתתתתתת
}

 const yt_btList = 4;
       yt_btSSR  = 5;


 constructor T_FPL4_form.Init(var _x,_y, _mode: int; _tit : string;
                              _itemd: PForms; _items: byte; _o_f: byte;            { offset }

                              _init_form,             { inicializacia dat   }
                              _image_form : pointer;  { vykreslenie ciar    }
                              _check_func : pointer;  { kontrola regularity }

                              _adr_var    : pointer;  { adresa premennej, kam nacitat data    }
                              _adr_data   : pointer;  { adresa premennej s povodnymi datami }

                              _rec  : Pplan_rec;
                              _src  : fdp_src;
                              _stat : string;

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

                              _hlpXXX: Pchar         { ukazovatel na help  }
                             );
       begin
         bt_pos:= 1;
         {btSSR:= nil;}

         inherited Init (_x,_y, _mode, _tit,
                         _itemd, _items,

                         0,1, 0,0, 0,0,

                         _init_form,_image_form,_check_func,

                         _hlpXXX,

                         _adr_var, _adr_data,
                         _rec,_src,_stat,

                         _novy,
                         _data_size,
                         _code_key, _read_orig,
                         _is_data,_chg_data,

                         _date_proc,_save_rpl_proc,
                         _zarad_proc,
                         _disp_proc,

                         true,false,true

                         {$IFDEF ODOSLI_ULOZ}, true {$ENDIF}
                         {$IFDEF SKRY_OKNA}, true {$ENDIF}
                         {$IFDEF STATISTIKA_OPL}, nil {$ENDIF}
                        );

         {copy_back:= false;}
         upcas:= true;
         pole_set:= @set_NXT;

         o_f:= _o_f;
         f_7a:= -1; f_7b:= -1; f_13a:= -1; f_15c:= -1
       end;


 procedure T_FPL4_form.HandleEvent(var _Event: TEvent);
     var   xt,yt,i : int;
           trat,_1,_n,res,s : string;
           is : bool;
           rte   : POBxys;
           bodov : int;
     begin
       inherited HandleEvent(_Event);
       if (_Event.What and evMessage) <> 0 then
          begin
            case _Event.Command of

              cm_OB          : RunList(@fnNDB,1,true,nil,nil,nil);

              cm_ATS         : RunList(@fnRTE,1,true,nil,nil,nil);

              cm_RTE         : if (f_15c<>-1) then
                               begin
                                 trat:= _it(o_f+f_15c);
                                 i:= getstritems(trat,[icao_NXIT]);
                                 is:= false;
                                 if (i=2) then
                                    begin
                                      is:= _prirad_trat_FPL4(getstr(trat,1,[icao_NXIT]),getstr(trat,2,[icao_NXIT]),s,trat,nil);
                                      if not is then i:= 1
                                    end;
                                 if not is then
                                    begin
                                      _n:= ''; if i<>1 then _1:= ''
                                      else if i=1 then _1:= getstr(trat,1,[icao_NXIT])
                                      else begin
                                             _1:= getstr(trat,1,[icao_NXIT]);
                                             _n:= getstr(trat,getstritems(trat,[icao_NXIT]),[icao_NXIT]);
                                           end;
                                      trat:= prirad_trat_FPL4(x0+itemd^[ind].dx,y0+itemd^[ind].dy+10,_1,_n,nil,rte,bodov,res);
                                      dealloc_FDRrte(rte,bodov);
                                    end;
                                 if trat<>'' then
                                    begin
                                      for i:= 0 to max_FPL4_15_r_hi-1 do
                                        begin
                                          clear_item_i(o_f+f_15c+i);
                                          writeitem(o_f+f_15c+i)
                                        end;
                                      GoToPos(o_f+f_15c);
                                      first_char_i(ind);
                                      vloz_text(trat)
                                    end
                               end;


              cm_DECODE_TRAT : if not display_decoded_data (res,i) then ErrorS(i,res);

              cm_ACTIVITY    : RunList (@fn_15,1,true,nil,nil,nil);

              cm_xDATA       : begin
                                 Win^.get_btXY(0,yt_btList, xt,yt);
                                 _list_AIP(xt-170,yt)
                               end;

              cmPrint        : ;

              else Exit
            end;
            ClearEvent(_Event)
          end
     end;


 procedure T_FPL4_form.form_init(var x,y: int; dx,dy: int;
                               _kbHot: char; _cmXXXX: word; _title: string;
                               _tit : byte;  _inc_dx,_inc_dy: int
                              );
     var   bt1 : PButton;
           bt2 : PbtCancel;
           xt,yt, yi,c : int;

     begin
       inherited form_init(x,y, dx,dy, _kbHot,_cmXXXX,_title,_tit,_inc_dx,_inc_dy);

       {$IFDEF A36YKA}
        Win^.get_btXY(1,0, xt,yt);
        xt:= Win^.x1-dbtWIDTH-(xt-Win^.x0);
        btA36:= New(PDialogButton,Init(Win, xt,yt,kbAltA,cmA36YKA,titA36,icKey,icText));
        btA36^.click:= ord(false);
        btA36^.stat:= TbtStat(is_kblayout);
       {$ENDIF}

       if (btList<>nil) and (btList^.ObjectType=obj_another) then
          begin
            Win^.get_btXY(1,0, xt,yi);
            btList^.Init(Win, xt,yi);
            btList^.bk0:= clBUTTON_COLOR
          end;

       Win^.get_btXY(1,bt_pos, xt,yt);
       btOB := New(PButton,Init(Win, xt,yt, length(titNDBVOR) shl 3,dbtHEIGHT,
                                GetAltCode(get_HotKey(_kbHot,titNDBVOR)),cm_OB,titNDBVOR, 1,icKey,icText)
                               );
       btOB^.visible:= false;
       btOB^.bk0:= clBUTTON_COLOR;
       xt:= btOB^.x1+4;
       inc(bt_pos);

       btATS:= New(PButton,Init(Win, xt,yt, length(titATSrte) shl 3,dbtHEIGHT,
                                GetAltCode(get_HotKey(_kbHot,titATSrte)),cm_ATS,titATSrte, 1,icKey,icText)
                               );
       btATS^.visible:= false;
       btATS^.bk0:= clBUTTON_COLOR;
       xt:= btATS^.x1+4;
       inc(bt_pos);

       btRTE:= New(PButton,Init(Win, xt,yt, length(titREGrte) shl 3,dbtHEIGHT,
                                GetAltCode(get_HotKey(_kbHot,titREGrte)),cm_RTE,titREGrte, 1,icKey,icText)
                               );
       btRTE^.visible:= false;
       btRTE^.bk0:= clBUTTON_COLOR;
       xt:= btRTE^.x1+4;
       inc(bt_pos);


       Win^.get_btXY(0,3, xt,yt);
       bt1 := New(PDialogButton,Init(Win, xt,yt,
                                GetAltCode(get_HotKey(_kbHot,titDECODE)), cm_DECODE_TRAT, titDECODE, icKey,icText)
                               );

       Win^.get_btXY(0,4, xt,yt);
       bt1 := New(PDialogButton,Init(Win, xt,yt,
                                GetAltCode(get_HotKey(_kbHot,mnu_AIP)), cm_xDATA, mnu_AIP, icKey,icText)
                               );
     end;


 procedure T_FPL4_form.draw_buttons;
     begin
       {if (btSSR<>nil) and (not (ind in[o_f+f_7a+1..o_f+f_7a+2])) then btSSR^.visibility(false);}

       if (not (ind in[o_f+f_15c..o_f+f_15c+max_FPL4_15_r_hi-1])) then
          begin
            btOB^.hide; btATS^.hide; btRTE^.hide; {btACT^.hide}
          end;

       inherited draw_buttons;

       {if (ind in[o_f+f_7a+1..o_f+f_7b+2]) and (btSSR<>nil) then btSSR^.visibility(true);}

       if (ind in[o_f+f_15c..o_f+f_15c+max_FPL4_15_r_hi-1]) and (not btOB^.visible) then
          begin
            btOB^.show; btATS^.show; btRTE^.show; {btACT^.show}
          end
     end;


 function T_FPL4_form.display_decoded_data (var res: string; var ires: int): bool;
    begin
      display_decoded_data:= true
    end;
