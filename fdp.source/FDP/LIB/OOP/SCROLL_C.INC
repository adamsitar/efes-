{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ OScrollStream                                            €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
function OScrollStream.streamFN: string;
   begin
     if (DataOb<>nil) and (DataOb^<>nil) then streamFN:= PObject(DataOb^)^.streamFN
     else streamFN:= inherited streamFN
   end;

function OScrollStream.streamTXT: bool;
   begin
     if (DataOb<>nil) and (DataOb^<>nil) then streamTXT:= PObject(DataOb^)^.streamTXT
     else streamTXT:= inherited streamTXT
   end;



{
 - scroluje/listuje
 - funguje ako okno/hlavna cast obrazovky
 - FN -> prehliadany FN, getFNprev/next...
   pamata si poziciiu FNpoz v subore...
   nacitane 3 stranky, ak sa dostaneme na koniec disp/renew
 - save... getFN... -> nahratie prijatej spravy
}
procedure OScrollStream.init_win(_title: string; x,y, dx,dy: int;
                                 _kbHot: char; _cmXXXX: word
                                );
    begin
      win:= nil;
      if is_win then inherited init_win(_title, x,y, dx,dy, _kbHot, _cmXXXX)
      else begin
             XY(x,y,dx,dy);
             sb^.visible:= false
           end
    end;

constructor OScrollStream.Init(_Owner  : PGroup;
                               _DataOb : PPObject;

                               _title  : string;

                               _x,_y, _item_dx : int;
                               _dxi,_dyi, _medzera : int; _bg : byte;
                               _page : int;
                               {_pos_en,} _sb_sam, _sb_vzdy : bool;

                               _dxb,_dyb : int;
                               _init_buttons,_handle_buttons : pointer;
                               _handler_owner : PObject;

                               _cl_SEND,_cl_REC: byte;

                               {_handler_type : TScrollAct_handler_type;
                               _handler      : pointer;
                               _handler_par  : pointer;}

                               _is_win     : bool;
                               _is_browser : bool;

                               _hlpXXX : Pchar
                              );

      begin
        DataOb:= _DataOb;
        strs.Init;

        is_win:= _is_win; {_title<>'';}
        is_browser:= _is_browser;
        is_scroll:= true;
        is_txt_stream:= true;
        is_to_init:= false;
        is_to_changed:= false;

        dxp:= 0; dyp:= 0;

        fn:= ''; fillchar(fa,sizeof(fa),0); fi:= 0;

        inherited Init(_Owner,
                       _title,

                       nil,nil,nil,nil, {@str,@ftop-nemoze int<>long, @is_fchg,nil,}

                       _x,_y, _item_dx,dy_ch,
                       _dxi,_dyi, _medzera, _bg,
                       nil, {_item_list}
                       _page,
                       false, _sb_sam, _sb_vzdy,

                       _dxb,_dyb,
                       _init_buttons,_handle_buttons,_handler_owner,
                       kbCtrlEnter, cmDefault
                      );

        ObjectType:= obj_view_active;
        za_posl_en:= true; prepis_en:= true; sort_en:= false; {scroll_en:= true;}
        sb^.za_posl_en:= true; {scroll_en:= true;}
        dxioff:= 2; dyioff:= 1;
        cl_SEND:= _cl_SEND;
        cl_REC:= _cl_REC;
        hlpXXX:= _hlpXXX;
      end;

destructor OScrollStream.Done;
     begin
       inherited Done;
       strs.Done
     end;

function OScrollStream.state: bool;
   begin
     {$IFDEF NOEMS}
      state:= strs.strm<>nil
     {$ELSE}
      state:= strs.is_ems
     {$ENDIF}
   end;


procedure OScrollStream.ReInit(x,y,dx,dy : int);
    var   pg: int;
    begin
      if is_win then inherited ReInit(x,y,dx,dy)
      else begin
             XY(x0,y0,dx,dy);
             MoveRel(x-x0,y-y0);
             sb^.ReInit(x1-MEDZERA__SCROLLER__SCROLL_BAR-SCROLL_BAR__SIRKA,y0,SCROLL_BAR__SIRKA,y1-y0);
             item_dx:= x1-x0-dxi*2-dxioff;
             if sb^.visible then dec(item_dx,MEDZERA__SCROLLER__SCROLL_BAR-SCROLL_BAR__SIRKA);

             if (dx<>dxp) or (dy<>dyp) then
                begin
                  pg:= ((MaxY-(dyb+2*dyi+btmdXY.y0+btmdXY.y1)) div (item_dy+medzera))-1;
                  top:= get_top;
                  pos:= top;
                  lo:= N(top-10);
                  hi:= lo+pg;
                  {disp_data}
                end;
             dxp:= dx; dyp:= dy
           end;
    end;


procedure OScrollStream._active(_active_: bool);
    const cl: array[false..true] of byte = (clGR6,clGR3);
    begin
      active:= _active_;
      SetColor(cl[active]);
      Rectangle(x0,y0,x1,y1)
    end;


procedure OScrollStream.ActiveOn;
    begin
      _active(true)
    end;

procedure OScrollStream.ActiveOff;
    begin
      _active(false)
    end;


procedure OScrollStream.Draw;
    begin
      inherited Draw;
      if not is_win then _active(active);
      {is_to_init:= true}
    end;

procedure OScrollStream.item_list_proc(i, x,y: int; b: bool);
    var   s  : string;
          cl : byte;
    begin
     {$IFDEF BGI} FillWin(x-2,y-2,x+item_dx-2,y+item_dy, bg); {$ENDIF}
      s:= copy(strs.read(i),1, minimum(item_dx,x1-x0) div dx_ch);
     { A co ked viacero prudov ?
     }
           if s[10]=archERR       then cl:= cl_ERR
      else if s[10]=archMESS      then cl:= cl_MESS
      else if s[10]=archSYS       then cl:= cl_SYS
      {else if s[11]=archREC       then cl:= cl_REC
      else if s[12]=archSEND      then cl:= cl_SEND}
      else                             cl:= cl_DATA;

      {case  s[10] of
        archERR       :  cl:= cl_ERR
        archMESS      :  cl:= cl_MESS
        archSYS       :  cl:= cl_SYS
        arch_PKT_REC  :  cl:= cl_REC
        arch_PKT_SEND :  cl:= cl_SEND;
        else cl:= cl_DATA
      end;}
      SetColor(cl);
      OutTextXY(x,y, s)
    end;


(*procedure OScrollStream.HandleEvent(var _Event: TEvent);
    var   _lo,_hi, _pos,_top, _cez, pg : int;
          fnn: string; D: DirStr; N: NameStr; E: ExtStr;
          Dir: PDir; Attr: word; var Files: int;
    label X;

    begin
      if not active then Exit;

      if (_Event.What=evKeyDown) and is_scroll_key(_Event.key) then
         begin

           if (not is_scroll) and (hi>=top) and (_Event.key=kbEnd) then
              begin
                set_scrollable;
                ClearEvent(_Event);
                Exit;
                {goto X}
              end;

           _lo:= lo; _hi:= hi; _pos:= pos; _top:= top;
           set_scroll_par(_Event.Key, _lo,_hi,_pos,_top, _cez, pos_en, smer, za_posl_en,false);

           if      is_browser
              and (   ((pos=0) and (_cez<0))
                   or ((fn<>streamFN) and (pos=top) and (_cez>0))
                  ) then
              begin
                {
                if Ask2(msgMESS,MPUmsg+MPUind+' did not passed. Do you want see MPU status ?','',clGRe,Red, 1000)
                   =ansAno then
                }
                if fn='' then
                   { natiahnutie predchadzajuceho subora, ak aktualny je prazdny
                   } fn:= streamFN;
                FSplit(fn, D,N,E);
                fnn:= dalsi_subor(D,'*'+E, N+E, _cez);
                if (_cez=1) and (D+fnn=fn) and (fn<>streamFN) then
                   begin
                   { natiahnutie nasledujuce prazdneho subora, ak je aktualny
                   }
                     fnn:= streamFN;
                     FSplit(fnn, D,N,E);
                     fnn:= N+E
                   end;
                if (D+fnn<>fn) and (fnn<>'') then
                   begin
                     is_scroll:= false;
                     disp_data;
                     fn:= D+fnn; _Exists(fn,ReadOnly+Hidden+SysFile+Archive,fa);
                     new_data;
                     pg:= hi-lo;
                     if _cez<0 then lo:= top-pg else lo:= 0;
                     if lo<0 then lo:= 0;
                     hi:= lo+pg; pos:= top;
                     List
                   end;
                ClearEvent(_Event);
                Exit
              end
           else begin
                  is_scroll:=     (fn=streamFN)
                              and (   (_Event.key=kbEnd)
                                   or ((top<=hi) and (_Event.key=kbDown))
                                  )
                end

           (X: is_scroll:=     (fn=streamFN)
                          and (   (_Event.key=kbEnd)
                               or ((top<=hi) {and (_Event.key=kbDown)})
                              );
              ClearEvent(_Event)
           )
         end

      else inherited HandleEvent(_Event);
    end;
*)
procedure OScrollStream.HandleEvent(var _Event: TEvent);
    var   _lo,_hi, _pos,_top, _cez, pg : int;
          fnn: string; D: DirStr; N: NameStr; E: ExtStr;
          Dir: PDir; Attr: word; var Files: int;
    begin
      if not active then Exit;

      if (_Event.What=evKeyDown) and is_scroll_key(_Event.key) then
         begin

           if (not is_scroll) and (hi>=top) and (_Event.key=kbEnd) then
              begin
                set_scrollable;
                ClearEvent(_Event);
                Exit
              end;

           _lo:= lo; _hi:= hi; _pos:= pos; _top:= top;
           set_scroll_par(_Event.Key, _lo,_hi,_pos,_top, _cez, pos_en, smer, za_posl_en,false);

           if      is_browser
              and (   ((pos=0) and (_cez<0))
                   or ((fn<>streamFN) and (pos=top) and (_cez>0))
                  ) then
              begin
                {
                if Ask2(msgMESS,MPUmsg+MPUind+' did not passed. Do you want see MPU status ?','',clGRe,Red, waitASK*18)
                   =ansAno then
                }
                if fn='' then
                   { natiahnutie predchadzajuceho subora, ak aktualny je prazdny
                   } fn:= streamFN;
                FSplit(fn, D,N,E);
                fnn:= dalsi_subor(D,'*'+E, N+E, _cez);
                if (_cez=1) and (D+fnn=fn) and (fn<>streamFN) then
                   begin
                   { natiahnutie nasledujuce prazdneho subora, ak je aktualny
                   }
                     fnn:= streamFN;
                     FSplit(fnn, D,N,E);
                     fnn:= N+E
                   end;
                if (D+fnn<>fn) and (fnn<>'') then
                   begin
                     is_scroll:= false;
                     disp_data;
                     fn:= D+fnn; _Exists(fn,ReadOnly+Hidden+SysFile+Archive,fa);
                     new_data;
                     pg:= hi-lo;
                     if _cez<0 then lo:= top-pg else lo:= 0;
                     if lo<0 then lo:= 0;
                     hi:= lo+pg; pos:= top;
                     List
                   end;
                ClearEvent(_Event);
                Exit
              end
           else begin
                  is_scroll:=     (fn=streamFN)
                              and (   (_Event.key=kbEnd)
                                   or ((top<=hi) and (_Event.key=kbDown))
                                  )
                end
         end;

      inherited HandleEvent(_Event);
    end;

{
  Trosku komplikovanejsi mechanizmus :

   - v pamati su natiahnute data subora fn (nazov): fa (atributy), fi (items)
   - pakety/data posielane do vypisu sa
        a) ak je v pamati subor, do ktoreho sa i zapisuje :
             - zaradi sa prvok so subora i pamate
             - if is_scroll ... zobrazuje sa obsah noveho subora
               else         ... ostava zachovany povodny obsah, nastavi
                                sa priznak prepisu stranky
                                top_prev:= -1 -> znova List
        b) nacitania subora : po povoleni is_scroll sa kontroluje fn<>fnn
                              a nasledne reinicializuje obsah pamate

   - ak je is_scroll = false -> neaktualizuje sa,
     az po nastaveni na_scroll sa kontroluje nazov suboru


}
procedure OScrollStream.Idle(var _Event: TEvent);
    begin
      if is_changed or ((is_scroll) and (top<>top_prev)) then List
      else Prekreslit
    end;


function OScrollStream.get_top: int;
   begin
     get_top:= strs.items-1
   end;

function OScrollStream.is_changed: bool;
   var   fnn  : string;
         fan  : SearchRec;
         res  : bool;
   begin
     res:= is_to_changed;
     if (not res) and ({is_to_init and} is_scroll) then
        begin
          fnn:= streamFN;
          res:= (fnn<>'') and (fnn<>fn) and (_Exists(fnn,ReadOnly+Hidden+SysFile+Archive,fan)=0);
          if res then
             begin
               fn:= fnn; move(fa,fan,sizeof(fan));
               is_to_changed:= true
             end
        end
     {else if is_to_init_};
     is_to_init:= false;
     is_changed:= res
   end;


procedure OScrollStream.set_scrollable;
    begin
      is_scroll:= true;
      disp_data;
      fn:= streamFN;
      new_data;
      List
    end;


procedure OScrollStream.add_data(s: string);
    begin
      strs.add(s);
      top:= get_top;
      pos:= top;
      inc(fi)
    end;

procedure OScrollStream.new_data;
    var   res : bool;
          fT  : text;
          s   : string;

          fS  : file of byte;
          p,d : pointer;
          c   : byte;

          i,j,k,l,m,r,z,q,x : long;
          pg  : int;

    const offS = 2+1+2+1+2+1+1+1; {'12:23˙45 > '}

    begin
      InfoCakaj(msgWAITING,'Initializing listing items.');

      is_to_changed:= false;
      disp_data;
      is_txt_stream:= streamTXT;

      if _Exists(fn,ReadOnly+Hidden+SysFile+Archive,fa)=0 then

         if is_txt_stream then
            begin
            { nacitanie txt subora
            }
              Assign(fT,fn); Reset(fT);
              while (not Eof(fT)) and (fi<=high(hi)) do
                begin
                  readln(fT,s);
                  add_data(s);
                  if fi div 20 = 0 then CheckProcesses0
                end;
              Close(fT)
            end
         else begin
              { nacitanie stream subora
              }
               Assign(fS,fn); Reset(fS);
               z:= FilePos(fS);
               while not Eof(fS) do
                 begin
                   read(fS,c);
                   if c=ord(kbLF) then
                      begin
                        k:= FilePos(fS)-1;
                        Seek(fS,z);
                        GetMem(p,k-z+1);
                        i:= 0; while i<=k-z do
                          begin
                            read(fS,pbytes(p)^[i]);
                            inc(i)
                          end;
                        i:= 0;
                        {
                        if soc<>' ' then
                           begin
                             while (i<=k-z) and (pchars(p)^[i]<>soc) do inc(i);
                           end;
                        }
                        {inc(i,offS);}
                        x:= k-z-i+1;
                        if     (pchars(p)^[0]<>';')    { - // - poznamky }
                           and (x>2) then              { eliminovanie prazdneho riadku }
                               begin
                                 for j:= 0 to x-2 do pchars(p)^[j]:= cNL__to_NL(pchars(p)^[j]);
                                 d:= @(pchars(p)^[i]);
                                 m:= get_str_items(d,x-2,setNL);
                                 for l:= 1 to m do
                                   begin
                                     s:= get_str(d,x-2,l,setNL,sizeof(s)-1);
                                     if l>1 then s:= inschar('',offS,' ',1)+s;
                                     add_data(s);
                                     if fi div 20 = 0 then CheckProcesses0
                                   end;
                                 {s:= ''; add_data(s)}
                               end;
                        FreeMem(p,k-z+1);
                        z:= k+1;
                        Seek(fS,z);
                        {s:= ''; add_data(s)}
                      end
                 end;
               Close(fS)
              end;

      s:= ''; add_data(s);
      top:= get_top;
      pg:= hi-lo;
      pos:= top;
      lo:= N(top-10);
      hi:= lo+pg;

      ResetIOError;
      InfoCakaj_zatvor
    end;

procedure OScrollStream.disp_data;
    begin
      strs.truncate(0);
      fi:= 0
    end;

{
}
procedure OScrollStream.fwrite_data (data: pchars; size: word;
                                     prompt,message: string;
                                     is_utc,is_tab,is_nl: bool
                                    );
    var   rdk,poc, i : int;
          s,t,u, fnn : string;
          fT         : text;
          p          : pointer;

    procedure fwrite(fnn,s: string);
        begin
        { vypis do subora
        } {$IFNDEF DEMO}
            if is_txt_stream and (fnn<>'') then writeln(fT,s);
          {$ENDIF}

        { vypis na obrazovku
        } if fnn=fn then { spracovavany subor je identicky s tym, co je v pamati }
             begin
               add_data(s);
               if is_scroll then Scroll { vypis na obrazovku }
               else top_prev:= -1
             end
        end;

    begin
      
      is_txt_stream:= streamTXT;
      fnn:= streamFN;
      if is_txt_stream and (fnn<>'') then
         begin
           vytvor_novy_subor(fnn);
           Assign(fT,fnn); Append(fT)
         end;

      if prompt='' then is_utc:= false;
      if is_utc then u:= TimeToStr2(hour,min,sec,':','˙') else u:= '';
      u:= u+' '+prompt;
      if is_tab then t:= InsChar('',length(u), ' ',0)
      else begin
             fwrite(fnn, u);
             t:= ''
           end;
      if message<>'' then
         begin
           if size<>0 then message:= message+' '+get_str(data,size,1,[kbLF,kbCR],sizeof(string)-1)+'...';
           data:= @message[1];
           size:= length(message)
         end;

      if (fnn<>'') and (not is_txt_stream) then
         begin
          {$IFNDEF DEMO}
           getmem(p,size);
           if size>0 then
              begin
                move(data^,pchars(p)^,size);
                for i:= 0 to size-1 do pchars(p)^[i]:= cNL_to_NL_(pchars(p)^[i])
              end;
           archive_data('',fnn,pbytes(p),size,prompt,is_utc,false);
           freemem(p,size)
          {$ENDIF}
         end;

      i:= 0; rdk:= 0; poc:= get_str_items(data,size,[kbLF,kbCR]);
      while (i<size) and (rdk<poc) do
        begin
          inc(rdk);
          s:= get_str(data,size,rdk,[kbLF,kbCR],sizeof(s)-1);
          if rdk<>1 then s:= t+s else s:= u+s;
          fwrite(fnn,s);
          {if fi<hi(fi) then inc(fi)}
        end;
      if is_txt_stream and (fnn<>'') then
         begin
           Close(fT); ResetIOError
         end;

      if is_nl then fwrite_nl;
    end;


procedure OScrollStream.fwrite_nl;
    var   fT      : text;
          fB      : file of char;
          fnn,s   : string;
          sz      : long;
          c1,c2   : char;
          i       : int;

    begin
      is_txt_stream:= streamTXT;
      fnn:= streamFN;
      if (Exists(fnn)=0) and (fnn<>'') then
         begin
          {$IFNDEF DEMO}
           if is_txt_stream then
              begin
                Assign(fT,fnn);
                Append(fT);
                writeln(fT,'');
                Close(fT)
              end
           else begin
                  Assign(fB,fnn); Reset(fB);
                  sz:= FileSize(fB);
                  if sz>2 then
                     begin
                       Seek(fB,sz-2);
                       read(fB,c1); read(fB,c2)
                     end;
                  if (sz>2) and (c1=kbCR) and (c2=kbLF) then sz:= sz-2;
                  Seek(fB,sz);
                  s:= ' '+kbCR_+kbLF_+' '+kbNL;
                  for i:= 1 to length(s) do write(fB,s[i]);
                  Close(fB)
                end
          {$ENDIF}
         end;
      s:= ''; add_data(s);
      if is_scroll then Scroll { vypis na obrazovku }
      else top_prev:= -1;
      ResetIOError
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ OScrollStreamViewer                                      €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

function OViewerStreamFile.streamFN: string;
   begin
     streamFN:= fnv
   end;

function OViewerStreamFile.streamTXT: bool;
   begin
     streamTXT:= is_txt_stream
   end;


constructor OViewerStreamFile.Init

               (_Owner  : PGroup;

                _title  : string;
                _fnv    : string;
                _is_txt_stream : bool;

                _item_dx  : int;
                _page     : int;
                _dxb,_dyb : int;
                _init_buttons,_handle_buttons,_handler_owner : pointer;

                _cl_SEND,_cl_REC: byte;

                _is_browser : bool;

                _hlpXXX : Pchar
               );

      begin
        inherited Init (_Owner, nil,
                        _title,
                        0,0, (_item_dx+12)*dx_ch, 2,2,4,0, _page,
                        true,true,
                        _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,
                        _cl_SEND,_cl_REC,
                        true,_is_browser,
                        _hlpXXX
                       );
        vtitle:= _title;
        fnv:= _fnv;
        is_txt_stream:= _is_txt_stream;
        prepis_en:= false;

        Centre
      end;


procedure OViewerStreamFile.new_data;
    var   title : string;
    begin
      inherited new_data;
      title:= vtitle;
      if @OViewerStreamFile_decode_fn_date<>nil then title:= title+' ('+OViewerStreamFile_decode_fn_date(fn)+')';
      win^.btTitle^.new_title(title,true);
      {win^.btTitle^.draw}
    end;
