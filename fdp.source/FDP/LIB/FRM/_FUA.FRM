{$IFDEF PROCESS_FUA}

 constructor TAUPed.Init (var _x,_y, _mode: int;

                          _title  : string;
                          _viewer : bool;

                          _fn,_tmp,_ini : string; { posledny spracovany subor; vzor, ak posledny spracovany subor nie je }

                           _typ  : TNETtyp;
                           _head : string;
                           _path : string;

                          _hlpXXX : Pchar
                         );
       var   dx: int;
       begin
         if (graphmode>_VGA) and (not _viewer) then dx:= dbtWIDTH+10 else dx:= 0;

         inherited Init (nil, _x,_y, _mode, cmDefault{_cmXXXX}, _title,
                         true,_viewer,
                         nil, riadkov_AUPed,znakov_AUPed,strana_AUPed,
                         _fn,_tmp,_ini,
                         [],[icao_NXIT],'',
                         nil, { check_func, riesi to vlastny handler }
                         dx,dbtHEIGHT+10,nil,nil,MainApp,nil,
                         clBUTTON_COLOR,clgre,0,clgre, clBUTTON_COLOR,hlp_cl_tx,
                         _hlpXXX
                        );
         upcas:= true;

         typ := _typ;
         head:= _head;
         path:= _path;
       end;


 procedure TAUPed.initialize_buttons;
     var   bt1 : PTextIcon;
           bt2 : PbtTCancel;
           bt3 : PDialogButton;
           xt,yt, cx,cy, dole : int;
           pc: pbyte;
           _kbHot: char;
     begin
       if (win=nil) then Exit;

       cy:= 0; cx:= 0;
       if graphmode>_VGA then begin dole:= 0; pc:= @cx end
       else begin dole:= 1; pc:=@cy end;

       if not viewer then
          begin
            {if is_to_save then}
               begin
                 Win^.get_btXY(dole,pc^, xt,yt);
                 bt3:= New(PDialogButton,Init(Win, xt,yt,
                           GetAltCode(get_HotKey(_kbHot,titSAVE)),
                           cmULOZ_PLAN,titSAVE,icKey,icText)
                          );
                 inc(pc^)
               end;

            {if is_to_send then}
               begin
                 Win^.get_btXY(dole,pc^, xt,yt);
                 bt3:= New(PDialogButton,Init(Win, xt,yt,
                           GetAltCode(get_HotKey(_kbHot,titSEND)),
                           cmODOSLI_PLAN,titSEND,icKey,icText)
                           );
                 bt3^.kbAltHot:= kbCtrlEnter;
                 inc(pc^)
               end;

            Win^.get_btXY(dole,pc^, xt,yt);
            bt2:= New(PbtCancel,Init(Win,xt,yt));
            inc(pc^,2);

            {$IFDEF PRN}
             if (win<>nil) then
                begin
                  Win^.get_btXY(dole,pc^, xt,yt);
                  bt3:= New(PDialogButton,Init(Win, xt,yt,
                            GetAltCode(get_HotKey(_kbHot,titPRINT)),
                            cmPrint,titPRINT,icKey,icText)
                           );
                  inc(pc^);
                end;
            {$ENDIF}

            if dole=1 then inc(cy);
            if FExists(strpas(ini))=0 then
               begin
                 Win^.get_btXY(1,cy, xt,yt);
                 bt3:= New(PDialogButton,Init(Win, xt,yt,
                           GetAltCode(get_HotKey(_kbHot,titVZOR)),
                           cmVLOZ_VZOR,titVZOR,icKey,icText)
                          );
                 inc(cy);
               end;
          end;

     end;


 procedure TAUPed.handle_buttons(var _Event: TEvent);
     var   fnn : string;
           adr : string;
     begin
       inherited handle_buttons(_Event);
       if _Event.what=evNothing then Exit;

       case _Event.command of

         cmCancel       : Exit;

         {cmEditRefresh : if _is_icao_editor_refresh(Ev, E,O, hd^,data) then
                                _icao_editor_reload (E,O,hd^,data);
         }

         cmVLOZ_VZOR    : begin
                           clear_items;
                           delfile(tmp);
                           copyfile(strpas(ini),tmp);
                           read_editor;
                           pos_prev:= -1;
                           List
                         end;

         cmULOZ_PLAN   : begin
                           save_editor;   { ulozenie do pracovneho subora }
                           if check_file (false,fnn,adr) then
                              begin
                                _up_zarad (tmp,fnn{_get_db_up_dfn(val,path,head)},head,typ,false,letvis);
                                SetCommand(_Event,cmCancel);
                                Exit
                              end
                         end;

         cmODOSLI_PLAN : begin
                           save_editor;   { ulozenie do pracovneho subora }
                           if check_file (true,fnn,adr) then
                              begin
                                _up_fil_time(tmp,code_MTK2_date(day, hour,min));  { zapis casu o odoslani }
                                _up_zarad (tmp,fnn{_get_db_up_dfn(val,path,head)},head,typ,true,letvis);
                                SetCommand(_Event,cmCancel);
                                Exit
                              end
                         end;

         else Exit
       end;

       ClearEvent(_Event)
     end;


 function  TAUPed.check_file (check_all: bool; var fnn: string; {val: TDate;} var adr: string): bool;
     var   res,_up,cis,ref : string;
           zac,kon : TDatum;
           val : TDate;
           bres : bool;
     label X;
     begin
     { kontrola na uvedenie vsetkych poloziek
     }
       bres:= _up_check (tmp,nil,head, _up,cis,ref, adr,zac,kon, val, check_all,head,res);
       if res<>'' then
          begin
            Err2(msgERR,res);
            goto X
          end;

      { kontrola na prepisanie subora
      }
       fnn:= _get_db_up_dfn(val, path,cis);
       if ((fn=nil) or ({(fn<>nil) and} (strpas(fn)<>fnn))) and (FExists(fnn)=0) then
          begin
            bres:= Ask2(msgWARNING, inf_plan+' '+inf_exist+' '+ask_prepisat,'',White,clBUTTON_COLOR,waitASK*18)=ansAno;
          end;

       X: check_file:= bres and (res='')
     end;


(*{ Neviem, co toto malo znamenat
}
 function ioff(fn0 : string): int;
    var   o : int;
          s : string;
    begin
      s:= __read_cfg(fn0,key_fua_type,1);
      o:= pos(key_fua_type,s);
      if o>0 then
         begin
           inc(o,length(key_fua_type));
           while (o<length(s)) and (s[o]=' ') do inc(o)
         end;
      ioff:= o
    end;

 function iset(source, identf, adds: string; ioff: int): string;
    var   o : int;
    begin
      o:= pos(identf,uni_str(source));
      {
      if (o>0) {and copy(uni_str(source),1,length(identf)) = identf} then
         begin
           source:= inschar('',N(o-1),' ',true) + identf;
           source:= inschar(source,N(ioff-length(source)),' ',true) + adds
         end;
      }
      iset:= source
    end;
*)

(*
 procedure  TAUPed.make_message;
     var    f1,f2 : text;
            s : string;
            o : int;
     begin
       if FExists(TxtFile^.fn0)<>0 then Exit;

       vytvor_novy_subor(TxtFile^.fn);
       {o:= ioff(fn0);}

       assign(f1,TxtFile^.fn0); reset(f1);
       assign(f2,TxtFile^.fn);  rewrite(f2);
       while not Eof(f1) do
         begin
           readln(f1,s);

           { nastavenie datumu platnosti }
           if pos(ident,uni_str(source)) copy(uni_str(s),1,length(key_fua_fil_time)) = key_fua_fil_time then
              s:= key_fua_fil_time

           { nastavenie casu a datumu podania spravy }
           if pos()

               key_fua_fil_time
               key_fua_val_period

           writeln(f2,s)
         end;
       close(f2);
       close(f1)
     end;
*)

 {function TAUPed._call_check_func: bool;
    begin
      if (text_adr<>nil) and (check_func<>nil) then _call_check_func:= regularity
      else _call_check_func:= true
    end;


 function TAUPed.is_to_send: bool;
    begin
      is_to_send:= true
    end;

 function TAUPed.is_to_save: bool;
    begin
      is_to_save:= true
    end;}


 {function TAUPed.validity(var d: TDate): bool;
    var   b : bool;
    begin
      b:= false;
      validity:= b
    end;

 function TAUPed.regularity: bool;
    var   b : bool;
    begin
      b:= false;
      regularity:= b
    end;
 }

{$ENDIF}
