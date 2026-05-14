 const  path_RPL_SOURCE : string = {$IFDEF DEBUG} '\xe\*.rpl';
                                   {$ELSE}        'a:\*.rpl';
                                   {$ENDIF}


 type   TlastEXT = record
          fn  : string;    { datum posledneho dna s fpl spracovanymi z rpl }
          pos : int;       { posledna pozicia }
          s   : string;    { posledny riadok }
        end;


 const  lastEXT : TlastEXT = (fn:''; pos:0);


 procedure zapis_chybu_txt_rpl(RPL: DRPL; res: string);
     var   t: text;
           s: string;
           i,p: int;
     begin
       Assign(t,fn_RPLext_err);
       if Exists(fn_RPLext_err)<>0 then
          begin
            Rewrite(t);
            writeln(t)
          end
       else Append(t);
       if RPL._7a<>'' then
          begin
            s:= RPL._7a+'-'+RPL._13a;
            writeln(t,rightchar('',length(s),'-'));
            writeln(t,s);
            writeln(t,rightchar('',length(s),'-'));
          end;
       while res<>'' do
         begin
           p:= 80; while (p>0) and (res[p]<>' ') do dec(p);
           if p=0 then p:= 78;
           s:= copy(res,1,p);
           res:= copy(res,p+1,length(res)-p);
           writeln(t,' '+s);
         end;
       writeln(t,kbNL);
       Close(t);
     end;


 procedure init_txt_rpl_butt (sc: PScrollWin); far;
    var   bt1   : PDialogButton;
          c, xt,yt : int;
          _kbHot : char;
    begin
     {$IFDEF PRN} c:= 1; init_sc_butt1(sc);
     {$ELSE}      c:= 0;
     {$ENDIF}
      sc^.Win^.get_btXY(1,c, xt,yt);
      bt1:= New(PDialogButton,Init(sc^.Win, xt,yt,GetAltCode(get_HotKey(_kbHot,titBACKUP)),cmBackup,titBACKUP,icKey,icText));
      inc(c);
      sc^.Win^.get_btXY(1,c, xt,yt);
      bt1:= New(PDialogButton,Init(sc^.Win, xt,yt,GetAltCode(get_HotKey(_kbHot,titDEL)),cmDelete,titDEL,icKey,icText));
    end;

 function  handle_txt_rpl_butt (var Ev : TEvent;
                                H : PHelp;
                                O : pointer;
                                P : pointer
                               ): bool; far;
    var    i: int;
    begin
      _handle_info_p (Ev,H,O,P);
      if Ev.what=evNothing then Exit;

      case Ev.What of
        evCommand, evBroadcast:
          case Ev.Command of
            cmBackup : begin
                         BackupFile(fn_RPLext_err);
                         ClearEvent(Ev,H)
                       end;
            cmDelete : begin
                         DelFile(fn_RPLext_err);
                         is_RPLDBERR:= false;
                         SetCommand(Ev,H,cmClose)
                       end;
            else Exit
          end
        else Exit
      end;

      
    end;

 procedure zobraz_chyby_txt_rpl;
     var   time: long;
           dt: DateTime;
           s: string;
     begin
       if not is_RPLDBERR then Exit;
       time:= _GetFTime(fn_RPLext_err);
       UnpackTime(time,dt);
       s:= tit_ext_err+' ('+DateToStr2 (dt.day,dt.month,dt.year)+')';
       _infoh(fn_RPLext_err, s, 0,0,0,btHEIGHT+10,@init_txt_rpl_butt,@handle_txt_rpl_butt,nil,hlp_PREHLAD_RPL_ERR);
     end;


{ ziskanie nazvu subora
}

 function  read_txt_rpls: string;
     var   sc : PScrollDIR;
           Ev : TEvent;
           fn : string;
           res : bool;
           t  : text;
     begin
       read_txt_rpls:= '';
       fn:= path_RPL_SOURCE;
       res:= false;
       while not res do
         begin
           if not formular_s (fn,20, tit_RPL_SOURCE,nil,0,@setFN,@setNil,0,nil,false,true,true,nil) then Exit;
           path_RPL_SOURCE:= fn;
           {if (pos(fn_all,fn)>0) then break;}
           res:= FExists(fn)=0;
           if not res then Err2('',msgFILES_NOT_FOUND+' ('+fn+')')
         end;

       if (GetNmbOfFiles(fn)>1) or (pos(fn_all,fn)>0) then
          begin
            FSplit(fn,sDir,sName,sExt);
            fn:= scroll_DIR(sDir,sName+sExt, msgFSELECT, '',
                            nil,nil,false,0,
                            nil,0,nil,
                            nil
                           );

            if FExists(fn)=0 then path_RPL_SOURCE:= fn;
          end;

       {if poc>1 then
          begin
            FSplit(path_RPL_SOURCE,D,N,E);   scroll
            sc:= New(PScrollDIR,Init(D,N+E, tit_RPL_COPY,'',nil,false,0,@comp_dir_name,0,@_read_txt_rpls,nil));
            sc^.RunLocalFunc(_Event,SCROLL_NC);
            Dispose(sc,Done)
          end
       else if poc=1 then _read_txt_rpls(path_RPL_SOURCE)
       else Say2(msgSORRY,'There are no RPL files...');
       read_txt_rpls:= poc}

       if fn<>'' then
          begin
            assign(t,fn_RPLext_src); rewrite(t);
            writeln(t,path_RPL_SOURCE);
            close(t);
          end;

       read_txt_rpls:= fn;
     end;


 function format_txt_rpl(fn: string): bool;
    begin
      format_txt_rpl:= is_IFPS_RPL_FILE(fn);
    end;


 type  p_ext_data = ^type_ext_data;
       type_ext_data = record
         t   : text;
         pos : int;
         s   : string;    { posledny riadok }
         oprava : bool;
       end;


{ fcia pre dekodovanie jedneho zaznmu rpl podla formatu ifps...
}
 procedure _bck_rpls(extp,extn: string);
     var   di : SearchRec;
           D  : DirStr;
           N  : NameStr;
           E  : ExtStr;
     begin
       InfoCakaj(msgWAITING,msgCOPY);
       if extp[1]<>'.' then extp:= '.'+extp;
       FindFirst(pathRPL+'*'+extp,Archive,di);
       if extn[1]<>'.' then extn:= '.'+extn;
       while (DosError=0) do
         begin
           FSplit(di.name,D,N,E);
           RenFile (pathRPL+di.name,pathRPL+N+extn);
           FindNext(di)
         end;
       InfoCakaj_zatvor
     end;


 function _spracovavany_ext_rpl (RPL,RPLp: PRPL): bool; far;
    begin
      _spracovavany_ext_rpl:=     ((RPL^._7a)=(RPLp^._7a))
                              and ((RPL^._13a)=(RPLp^._13a))
                              and (memcomp (@RPL^.dni,@RPLp^.dni,sizeof(RPL^.dni)))
    end;

 function _spracuj_ext_rpl (data: p_ext_data; o: PProcess): bool; far;
    var   RPL,RPLp : DRPL;
          bres, is2,is3,is4 : bool;
          res : string;
          ires : int;
          check_par: word;

    function read_data: bool;
       var   s: string;
       begin
         data^.s:= '';
         if Eof(data^.t) then Exit;
         readln(data^.t,data^.s);
         inc(data^.pos);
         if o<>nil then o^.new_item(cut_(data^.s));
       end;

    begin
      fillchar(RPL,sizeof(RPL),0);

      is2:= false;
      while (not Eof(data^.t)) and (not is2) do
        begin
          is2:= is_IFPS_RPL_FLIGHT_INFO(data^.s);
          if is2 then decode_IFPS_RPL_FLIGHT_INFO(data^.s,RPL)
          else read_data;
        end;

      read_data;

      if is_IFPS_RPL_ROUTE(data^.s) then
         begin
           is3:= true;
           RPL._15:= strpasnew(decode_IFPS_RPL_ROUTE(data^.s));
           while read_data and is_IFPS_RPL_ROUTE(data^.s) do
              RPL._15:= strnpcopy (RPL._15,icao_NXIT+decode_IFPS_RPL_ROUTE(data^.s),true,true);
         end;

      if is_IFPS_RPL_REMARKS(data^.s) then
         begin
           is4:= true;
           RPL._18:= strpasnew(decode_IFPS_RPL_REMARKS(data^.s));
           while read_data and is_IFPS_RPL_REMARKS(data^.s) do
              RPL._18:= strnpcopy (RPL._15,icao_NXIT+decode_IFPS_RPL_REMARKS(data^.s),true,true);
         end;

      bres:= is2 and is3;
      check_par:= cm_zarad_RPL or cm_decode_RPL_FPL4;
      if bres then
         begin
           if data^.oprava then
              begin
              { najdi povodny, aby sa zistili hodnoty kluca...
              } fillchar(RPLp,sizeof(RPLp),0);
                if DB_prehladaj(@_spracovavany_ext_rpl,
                                @RPL,@RPLp,@disp_RPL,
                                get_RPLfn(@RPL),db_RPL_RIADKOV,
                                @decodeDB_RPLF_rpl,nil,false,''
                               ) > -1
                   then
                     begin
                      { klucove udaje neboli volanim fcie "disp_RPL" v DB_prehladaj odmazane
                      }
                        RPL._7x:= RPLp._7x
                     end
                 else check_par:= check_par or cm_check_RPL_KEY;
              end
            else check_par:= check_par or cm_check_RPL_KEY;
           _zarad_RPL (@RPL, check_par, rpl_ERR, user, res,ires);
         end;
      if {((rpl_ERR) or (rpl_ERR_write)) and} (res<>'') then zapis_chybu_txt_rpl(RPL,res);
      disp_RPL(@RPL);

      _spracuj_ext_rpl:= Eof(data^.t) or is_IFPS_TRAILER(data^.s);
    end;


 procedure decode_txt_rpl(fn: string; dokonci,oprav,backup: bool);
     var   res  : string;
           ires : int;
           data : type_ext_data;
           f  : file of TlastEXT;
           is : bool;
           i : int;
     label X;
     begin
       if (not dokonci) or oprav then
          begin
           { overenie formatu
           }
            if fn='' then Exit;
            if Exists(fn)<>0 then begin Err2('',msgFILES_NOT_FOUND+' ('+fn+')'); Exit end;
            if not format_txt_rpl(fn) then begin Err2('',msgF_INVALID_FORMAT+' ('+fn+')'); Exit end;

           { zalohovanie
           }
            l4_err(a_RPL,'',0,ask_rpl_backup,res);
            if     (not oprav) and backup
               and (GetNmbOfFiles(pathRPL+fn_all+'.'+extRPL)>1)
               and ((res='') or (Ask2(msgVERIPHY,res,titNO,White,clBUTTON_COLOR,waitASK*18)=ansAno)) then
               begin
                 del(pathRPL+'*.'+extRPP);
                 _bck_rpls(extRPL,extRPP);
               end;

           { prekopirovanie na disk, kvoli rychlejsiemu spracovaniu
           }
            if fn<>fn_RPLext_copy then
               begin
                 ires:= backupfile_(fn,fn_RPLext_copy);
                 if ires<>0 then
                    begin
                      Err2('',ErrorMessage(ires,fn));
                      Exit
                    end;
               end;

            DelFile(fn_RPLext_err);
          end
       else begin
              fn:= fn_RPLext_copy;
              if Exists(fn)<>0 then
                 begin
                   {Err2(msgFILES_NOT_FOUND+' ('+fn+')');}
                   is:= true;
                   goto X
                 end;
            end;

      { overenie, ci posledna inicializacia prebehla do konca,
        ak nie, potom nastavenie sa na prislusnu poziciu subora
      }
       if (not oprav) and (dokonci and (Exists(fn_RPLext_kod)=0)) then
          begin
            assign(f,fn_RPLext_kod);
            reset(f);
            read(f,lastEXT);
            close(f);
          end
       else begin
              lastEXT.fn:= fn;
              lastEXT.pos:= 0;
            end;

      { nacitanie poloziek
      }
       fillchar(data,sizeof(data),0);
       assign(data.t,fn_RPLext_copy);
       reset(data.t);
       data.pos:= lastEXT.pos;
       data.oprava:= oprav;
       i:= 0; while (i<data.pos) and (not (Eof(data.t) or is_IFPS_TRAILER(data.s))) do
         begin
           readln(data.t,data.s);
           inc(i);
         end;

      { spracovanie
      }
       if not (Eof(data.t) or is_IFPS_TRAILER(data.s)) then
          begin
            InfoProcess (tit_ext_to_rpl+':',titDLA,'ÿ',line_ext_rpl,@_spracuj_ext_rpl,@data);
          end;

      { overenie, ci bol dosiahnuty koniec subora,
        ak nie zapisanie cfg subotra o poslednom
        stave operacie
      }
       is:= Eof(data.t) or is_IFPS_TRAILER(data.s);
       close(data.t);

       X:

       is_RPLDBERR:= Exists(fn_RPLext_err)=0;
       if is then
         begin
           DelFile(fn_RPLext_copy);
           DelFile(fn_RPLext_kod);
           is_RPLDB:= false;
           zobraz_chyby_txt_rpl;
         end
       else begin
              lastEXT.fn:= fn;
              lastEXT.pos:= data.pos;
              lastEXT.s:= data.s;
              assign(f,fn_RPLext_kod);
              rewrite(f);
              write(f,lastEXT);
              close(f);
              is_RPLDB:= true
            end;
     end;
