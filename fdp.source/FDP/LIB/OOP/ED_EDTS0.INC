{ ------------------------------------------------------
  Sposob navratenia hodnoty je jeden z nasledujucich :

   -  text_rdk(text_adr,i,s): string je externa funkcia, ktora do premennej
        "text_adr" vracia "i"-ty riadok ako "s"tring
   -  text_adr je alokovane pole s maximalnym rozmerom text_size, kde budu nacitane data
   -  pri nacitani

  Pri zmenach treba dat pozor na alokaciu/dealokaciu pri init/done ->
  na rewrite_in_editor...
}

constructor TEditors.Init(_Owner : PGroup;
                          var _x,_y, _mode: int; _cmXXXX: word;
                          _title  : string;

                          _win_en : bool;           { dovolene samostatne okno ? }
                          _viewer : bool;

                          _strana : pointer; _riadkov,_znakov, _velkost_strany: int;
                          _tmp    : string;

                          _write_txt    : pointer;  { fcia pre zapis do riadkov          }
                          _read_txt     : pointer;  { fcia pre citanie/zapis do riadkov  }
                          var _text_adr : pointer;  { smernik na spracovavanu premennu   }
                          _text_len,                { dlzka vstupnych dat                }
                          _text_size  : word;       { velkost buffera vstupnych dat      }

                          _is_pchar   : bool;       { text_adr je @pchar, volanim read_from_editor       }
                          _disp_pchar : bool;       { sa odalokuje, ak disp_disp odalokuje sa i na konci }

                          _odd_rdk,_odd_slv : TCharSet; _odd_rdkr: string;

                          _check_func : pointer;

                          _dxb,_dyb       : int;
                          _init_buttons,
                          _handle_buttons : pointer;
                          _handler_owner  : PObject;
                          _handler_data   : pointer;

                          _bge,_cle, _bga,_cla, _bgv,_clv : byte;
                          _hlpXXX : Pchar
                         );
      var   d: DirStr; n: NameStr; e: ExtStr;
            i: int;
      begin
        win_en:= _win_en;
        viewer:= _viewer;
        upcas:= false;
        write_txt:= _write_txt;
        read_txt := _read_txt;
        text_size:= _text_size;
        is_pchar:= _is_pchar; disp_pchar:= _disp_pchar;
        if is_pchar then
           begin
             pchar(text_adr):= strnew(_text_adr);
             p_text_adr:= @_text_adr
           end
        else begin
               text_adr:= _text_adr;
               p_text_adr:= _text_adr
             end;
        p_text_len:= _text_len;

        odd_rdk:= _odd_rdk; odd_slv:= _odd_slv;
        odd_rdkr:= _odd_rdkr;
        check_func := _check_func;

        if _znakov<>0 then znakov:= minimum(_znakov,max_znakov_e) else znakov:= max_znakov_e;
        if znakov=0 then znakov:= max_znakov_e;
        riadkov:= minimum(_riadkov,max_riadkov_e);
        if riadkov=0 then riadkov:= max_riadkov_e;

        rdk:= 0; stl:= 0; ins:= true;

        bge:= _bge; cle:= _cle;   { pre odpamatnie farebneho odlisenia     }
        bga:= _bga; cla:= _cla;
        bgv:= _bgv; clv:= _clv;   { pri editovani/prehliadani, ak bgw<>clw }

        corr_res:= false;
        alloc:= _strana=nil;
        if alloc then strana:= alloc_stranu_editora(riadkov,znakov)
        else strana:= _strana;
        top:= _riadkov;

        {if alloc then}
           begin
             FSplit (_tmp,d,n,e);
             if e<>'' then tmp:= _tmp
             else tmp:= pathTMP+_tmp+extTMP
           end
        {else tmp:= ''};

        {$IFDEF A36YKA}
          btA36:= nil;
        {$ENDIF}

        title:= strpasnew(_title);
        inherited Init(_Owner, _title,
                       strana, @top, nil, nil,
                       _x,_y, znakov*dx_ch,dy_ch,5,5, medzera_ed,
                       {$IFDEF EGAVGA}LightGray{$ELSE}clBUTTON_COLOR+2{$ENDIF}, nil,
                       _velkost_strany, true,true,false,
                       _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,
                       kbCtrlEnter, _cmXXXX
                      );
        { scroller sa postara, aby sme vosli na obrazovku }
        dxioff:= 2; dyioff:= 1;
        item_en:= false; top:= riadkov-1;
        click_and_handle:= true;
        {za_posl_en:= _riadkov-1>hi; sb^.za_posl_en:= za_posl_en;}
        on:= btOFF; sb^.visible:= riadkov>hi-lo+1;
        hlpXXX:= _hlpXXX;
        if (Win<>nil) then with win^.btTitle^ do
          begin
            cmXXXX:= cmAboutWin;
            kbHot:= kbAltF1
          end;
        Centre;

        handler_data:= _handler_data;
        handler_end_state:= nil;
        if (handler_owner<>nil) then handler_owner^.PushObject(@Self);

        { inicializacia :
           - nacitanie z pola s definovanymi oddelovacmi riadkov...
           - zo subora
           - z doasneho subora (kde je ulozena posledna sprava)
        }
        write_in_editor;
        read_editor;
      end;


procedure TEditors.init_win(_title: string; x,y, dx,dy: int;
                            _kbHot: char; _cmXXXX: word
                           );
    begin
      if win_en then inherited init_win(_title, x,y, dx,dy, _kbHot,_cmXXXX)
      else begin
             {win:= New(PWindow,Init(@Self, x,y, dx,dyb, _kbHot, _cmXXXX, _title, true));
             win^.own_img:= true; win^.btSize:= btNorm;
             reinit_(x,y,hi-lo+1);
             Active:= true}
           end
    end;


destructor TEditors.Done;
     var   O : PObject;
     begin
       save_editor;

       inherited Done;

       if (handler_owner<>nil) then
          begin
            O:= @Self;
            handler_owner^.RemoveObject(O,false)
          end;

       if alloc then dealloc_stranu_editora(pointer(strana), riadkov,znakov);

       if is_pchar then
          begin
            if (p_text_adr<>nil) then
               if disp_pchar then strdispose(pchar(p_text_adr^))
               else if corr_res then
                       begin
                        { editovana hodnota prelezie do novej }
                         strdispose(pchar(p_text_adr^));
                         pchar(p_text_adr^):= strnew(text_adr)
                       end;
            if (text_adr<>nil) then strdispose(pchar(text_adr))
          end;

       strdispose(title)
     end;


procedure TEditors.HandleEvent(var _Event: TEvent);
    var   _rdk,_stl : int;
          k : char;
          s : string;
    begin
      if (_Event.What=evKeyDown) then
         begin
           if (_Event.key in [kbCtrlHome,kbCtrlEnd]) then k:= _Event.key else k:= NULL;
           if (not (_Event.key in [kbEnter,kbHome,kbEnd])) then inherited HandleEvent(_Event);
           if (k<>NULL) then SetKeyEvent(_Event,@Self,k);
           if AcceptedKey(_Event) then ClearEvent(_Event)
           else Exit
         end;

      {if TView.isClicked then
         begin
           _rdk:= lo+((_Event.M.y-y0-dyi-dyioff) div (item_dy+medzera))
           _stl:= ((_Event.M.x-x0-dxi-dxioff) div (item_dx))
           ClearEvent(_Event);
         end;}

      if (_Event.What<>evNothing) then inherited HandleEvent(_Event);

      if isCommand(_Event,cmScrollItemClicked) then
         begin
           if not viewer then
              begin
                move(MailBox^,_Event,SizeOf(TEvent));
                ClickedChar(_Event)
              end;
           ClearEvent(_Event)
         end;

     {$IFDEF A36YKA}
      if isCommand(_Event,cmA36YKA) then
         begin
           is_kblayout:= not is_kblayout;
           ClearEvent(_Event)
         end;
     {$ENDIF}

      if isCommand(_Event,cmAboutWin) and (Win<>nil) and (_Event.From=win^.btTitle) then
         begin
           {if strlen(title) > strlen(win^.btTitle^.title) then}
              begin
                s:= strpas(title);
                Say2(msgINFO,s);
              end;
           ClearEvent(_Event)
         end;
    end;


procedure TEditors.handle_buttons(var _Event: TEvent);
   begin
     inherited handle_buttons(_Event);
     if _Event.what=evNothing then Exit;

     case _Event.command of

       cmClose   : begin
                     SetCommand(_Event,cmCancel);
                     Exit
                   end;

       cmCancel  : Exit;

       cmPrint   : print_from_editor;

       else Exit
     end;

     ClearEvent(_Event)
   end;


{procedure TEditors.Idle;
    begin
      blikanie kurzora ...
    end;
}

procedure TEditors.Run(var _Event: TEvent);
    var   kblayout : bool;
    begin
      kblayout:= is_kblayout; is_kblayout:= false;
      {$IFDEF A36YKA}
       if btA36<>nil then
          begin
            btA36^.click:= ord(false);
            btA36^.stat:= TbtStat(is_kblayout)
          end;
      {$ENDIF}
      inherited Run(_Event);
      is_kblayout:= kblayout;
    end;


function TEditors.handle_end_state: bool;
   begin
     handle_end_state:= (handler_end_state<>nil) and TBFunc_p3(handler_end_state)(@Self,handler_owner,handler_data)
   end;


function TEditors.EndState(var _Event: TEvent): bool;
   var   res: bool;
   begin
     res:= inherited EndState(_Event);
     if res and (isCommand(_Event,cmXXXX)) then
        begin
          if (not call_check_func) or handle_end_state then
             begin
               ClearEvent(_Event);
               res:= false
             end;
          corr_res:= res
        end;
     EndState:= res
   end;


{ len preto ,ze BGI je pomala a ja este viac
}
procedure TEditors.draw_inside;
    var   b: byte;
    begin
      inherited draw_inside;
      if viewer then b:= bg else b:= bge; { Chujovo, lebo mam bordel v grafike, ale co uz teraz, 2 dni pre NextStepom? }
      fillwin(x0+5,y0+4,x1-6,y1-4, b)
    end;


{ ---------------------------------
   Indexovanie pola riadkov
}

function index_pola_s(strana: pchar; znakov: int; r,od: int; _1: bool): pchar;
   var   p: pchar;
   begin
     p:= pointer(strana);                  {   ukazuje na alokovanu adresu }
     p:= p + r*(znakov+1) + ord(_1) + od;  { = strana^[r][od+1] }
     index_pola_s:= p
   end;

function TEditors.r_s(r,od: int; _1: bool): pchar;
   begin
     r_s:= index_pola_s(strana, znakov, r,od, _1)
   end;



{ ---------------------------------
   Zapis/nacitanie z/do formulara
}

procedure TEditors.new_title(_title: string);
    begin
      strdispose(title);
      title:= strpasnew(_title);
      if (win<>nil) and (win^.btTitle<>nil) then
         begin
           win^.btTitle^.new_title(_title,true)
         end;
    end;


{
function TEditors.pocet_riadkov: word;
   begin
     if odd_rdk<>[] then pocet_riadkov:= get_str_items(pchars(text_adr),text_size,odd_rdk)
     else pocet_riadkov:= text_size div znakov
   end;
}
function  TEditors.pocet_riadkov: int;
   var    k: int;
   begin
     k:= riadkov-1; while (k>=0) and (cut_(_read_line_from_editor(k))='') do dec(k);
     pocet_riadkov:= k+1
   end;


procedure TEditors.clear_item_i(i: int);
    var   p: pchar;
    begin
      p:= r_s(i,0,false);
      p^:= chr(znakov);
      p:= p + 1;
      fillchar(p^,N(znakov),' ')
    end;

procedure TEditors.clear_items;
    var   _Ev   : TEvent;
          i,cez : int;
    begin
      stl:= 0;
      for i:= 0 to riadkov-1 do clear_item_i(i);
      set_scroll_par(kbCtrlPgUp, lo,hi, pos,top,cez, pos_en, smer, za_posl_en,false);
      {for i:= 0 to riadkov-1 do zmaz_stranu_editora(strana, znakov, i,0);
      SetKeyEvent(_Ev,@Self,kbCtrlHome);
      inherited HandleEvent(_Ev)
      }
    end;


procedure TEditors._write_line_in_editor (i: word; s: string);
    begin
      s:= cut_r(s);
      move(s[1],pchr(r_s(i,0, true))^,minimum(length(s),znakov))
    end;


procedure TEditors.__write_in_editor(_text_adr : pointer;
                                     _text_len : word
                                    );
    var   s   : string;
          i   : int;
    begin
      if _text_adr=nil then Exit;

      if write_txt<>nil then
         begin
           for i:= 0 to riadkov-1 do
             begin
               s:= TSFunc_pis(write_txt)(_text_adr,i, '');
               _write_line_in_editor(i,s)
             end
         end
      else begin
             for i:= 0 to riadkov-1 do
               begin
                 if odd_rdk<>[] then s:= get_str(pchars(_text_adr),_text_len,i+1,odd_rdk,sizeof(s)-1)
                 else begin
                        s[0]:= chr(minimum(_text_len-i*znakov,znakov));
                        move(pchars(_text_adr)^[i*znakov],s[1],ord(s[0]))
                      end;
                 _write_line_in_editor(i,s)
               end
           end;
    end;

procedure TEditors._write_in_editor(_text_adr : pointer;
                                    _text_len : word
                                   );
    begin
      clear_items;
      __write_in_editor(_text_adr,_text_len);
      is_chg:= false
    end;

procedure TEditors.write_in_editor;
    var   p : pointer;
    begin
      if is_pchar then p:= pointer(p_text_adr^) else p:= p_text_adr;
      _write_in_editor(p,p_text_len)
    end;

{
procedure TEditors.rewrite_in_editor(_text_adr : pchar;
                                     _text_len : long
                                    );
    begin
      write_in_editor(_text,adr,_text_len);
      TScroller.Draw
    end;
}

function TEditors._read_line_from_editor (i: word): string;
   var   s: string;
   begin
     move(pchr(r_s(i,0, false))^,s[0],znakov+1);
     _read_line_from_editor:= cut_r(s)
   end;


procedure TEditors.__read_from_editor;
    var   i,p : int;
          s   : string;
    begin
      if text_adr=nil then Exit;

      if read_txt<>nil then
         begin
           for i:= 0 to riadkov-1 do
             begin
               TSFunc_pis(read_txt)(text_adr,i, _read_line_from_editor(i))
             end
         end
      else if is_pchar then
              begin
                strdispose(pchar(text_adr));
                for i:= 0 to riadkov-1 do
                  begin
                    s:= _read_line_from_editor(i)+kbNL;
                    pchar(text_adr):= StrNPCopy(pchar(text_adr),s,true,true)
                  end
              end
           else begin
                  fillchar(pchars(text_adr)^,text_size,0);
                  i:= 0; p:= 0;
                  while (i<riadkov) and (p<text_size) do
                    begin
                      s:= _read_line_from_editor(i)+odd_rdkr;
                      move(s[1],pbytes(text_adr)^[p],length(s));
                      inc(p,length(s));
                      inc(i)
                    end
                end
    end;

procedure TEditors.read_from_editor;
    begin
      __read_from_editor
    end;


{ ulozenie (ne)spracovaneho obsahu editora
  do docasneho subora pre neskorsie opatovne
  obnovenie
}
procedure  TEditors.save_editor;
    var    i : int;
           t : text;
    begin
      if tmp<>'' then
         begin
         { ulozi obsah editora do docasneho subora, aby sa nestratil
         }
           vytvor_novy_subor(tmp);
           if Exists(tmp)<>0 then Exit;
           assign(t,tmp); rewrite(t);
           for i:= 0 to pocet_riadkov-1 do
             begin
               writeln(t,_read_line_from_editor(i));
             end;
           close(t)
         end
    end;


{ nacitanie posledneho spracovaneho obsahu editora,
  ak je prazdny, potom vytvornie podla vzoru : make_message
}
procedure  TEditors.read_editor;
    var    t : text;
           s : string;
           i : int;
    begin
      if pocet_riadkov>0 then Exit;

      if (tmp<>'') and (_filesize(tmp)=0) then make_message;
      if pocet_riadkov>0 then Exit;

      if Exists(tmp)<>0 then Exit;
      assign(t,tmp); reset(t);
      i:= 0; while (i<riadkov) and (not Eof(t)) do
        begin
          readln(t,s);
          _write_line_in_editor (i,s);
          inc(i)
        end;
      close(t)
    end;

procedure  TEditors.make_message;
    begin
      { Zamerne prazdne, aby mal dedic moznost
        predefinovania sposobu vyvorenia spravy/subora,
        najma ak ide o formalizovany tvar...
      }
    end;


procedure TEditors.print_from_editor;
    var   i,p : int;
          s   : string;
          res : bool;
    begin
     {$IFDEF PRN}
      if (Win<>nil) and (not print_str(PortNo,strpas(win^.btTitle^.title)+kbNL+kbNL+kbNL)) then Exit;

      i:= 0; p:= pocet_riadkov; res:= true;
      while (i<p) and res do
         begin
           res:= print_str(PortNo,_read_line_from_editor(i)+kbNL);
           inc(i)
         end;
       if res then
          begin
            i:= 0; while (i<3) and print_str(PortNo,kbNL) do inc(i)
          end
     {$ENDIF}
    end;