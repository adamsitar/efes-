
 procedure ext_init_buttons_StaViewer (p_help: PHelp); far;
     begin
       if p_help^.handler_owner<>nil then PHelpViewer(p_help^.handler_owner)^.initialize_buttons(p_help);
     end;

 function  ext_handle_StaViewer (var _Event: TEvent; p_help: PHelp; Owner: PHelpViewer; data: pointer): bool; far;
    begin
      ext_handle_StaViewer:= true;
      if p_help^.handler_owner<>nil then PHelpViewer(p_help^.handler_owner)^.HandleEvent(_Event);
    end;


 constructor THelpViewer.Init(_fn,_title: string;
                              _p_archiv: PSFunc_s; _p_export: pointer; _d_title: bool;
                              _hlpXXX: pchar
                             );
       begin
         inherited Init(nil);

         fn:= ''; fnn:= _fn; hlpXXX:= _hlpXXX;

         p_archiv:= _p_archiv;
         p_export:= _p_export;
         d_title := _d_title;

         title:= _title;
         btZ:= nil; btA:= nil; btE:= nil;

         p_keys:= nil;
         top_keys:= -1;
         pos_keys:= 0;

         kluc:= '';
       end;


 procedure THelpViewer.read_keys;
     var   t: text;
           s: string;
           i: int;
     begin
       top_keys:= -1;
       pos_keys:= 0;
       if FExists(fn)=0 then
          begin
            Assign(t,fn); Reset(t);
            while not Eof(t) do
              begin
                readln(t,s);
                if (s<>'') and (s[1]=hlp_SOH) and (s[length(s)]=hlp_EOH) then inc(top_keys);
              end;
            if (top_keys>-1) and (AllocMem(pointer(p_keys),(1+top_keys)*sizeof(pchar))) then
               begin
                 Reset(t); i:= 0;
                 while (not Eof(t)) and (i<=top_keys) do
                   begin
                     readln(t,s);
                     if (s<>'') and (s[1]=hlp_SOH) and (s[length(s)]=hlp_EOH) then
                        begin
                          p_keys^[i]:= strpasnew(copy(s,2,length(s)-2));
                          inc(i)
                        end;
                   end;
               end
            else top_keys:= -1;
            close(t);
          end;
     end;

 procedure THelpViewer.release_keys;
     var   i: int;
     begin
       if (top_keys>-1) then
          begin
            for i:= 0 to top_keys do strdispose(p_keys^[i]);
            DeallocMem(pointer(p_keys),(1+top_keys)*sizeof(pchar));
            top_keys:= -1;
            pos_keys:= 0
          end;
     end;


 procedure THelpViewer.initialize_buttons(p_help: PHelp);
     var   bt  : PDialogButton;
           bti : PFButton;
           xt,yt, c : int;
           kbHot : char;
     begin
       c:= 0;

      {$IFDEF PRN}
       p_help^.Win^.get_btXY(1,c, xt,yt);
       bt:=   New(PDialogButton,Init(p_help^.Win, xt,yt,
                  GetAltCode(get_HotKey(kbHot,titPRINT)),cmPrint,titPRINT,
                  icKey,icText)
                 );
       inc(c);
      {$ENDIF}

       if p_export<>nil then
          begin
            p_help^.Win^.get_btXY(1,c, xt,yt);
            btE:=  New(PDialogButton,Init(p_help^.Win, xt,yt,
                       GetAltCode(get_HotKey(kbHot,titEXPORT)),cmExport,titEXPORT,
                       icKey,icText)
                      );
            inc(c);
          end;

       xt:= p_help^.Win^.x1-dbtDXoff-dbtWIDTH;
       if p_archiv<>nil then
          begin
            btA:= New(PDialogButton, Init(p_help^.Win, xt,yt,
                     GetAltCode(get_HotKey(kbHot,titARCHIV)),cmArchiv,titARCHIV,
                     icKey,icText)
                    );

            dec(xt,dbtWIDTH+dbtDXoff);
          end;

       if top_keys>1 then
          begin
            btZ:= New(PDialogButton, Init(p_help^.Win, xt,yt,
                     GetAltCode(get_HotKey(kbHot,titZOBRAZ)),cmZobraz,titZOBRAZ,
                     icKey,icText)
                    );

            dec(xt,dbtDXoff+2*dbtDX);
            {if pos_keys>0 then}
               begin
                 bti:= New(PFButton, Init(p_help^.Win, xt-dbtDX*2,yt,10,dbtHEIGHT, '<', cmPrev, '~<~', 1,
                                          icKey,icText,clBUTTON_COLOR)
                                         );
                 bti^.kbAltHot:= kbAltLeft;
               end;

            {if pos_keys<top_keys then}
               begin
                 bti:= New(PFButton, Init(p_help^.Win, xt+dbtDX,yt,10,dbtHEIGHT, '>', cmNext, '~>~', 1,
                                          icKey,icText,clBUTTON_COLOR)
                                         );
                 bti^.kbAltHot:= kbAltRight;
               end;

            inc(xt,20);
            inc(c);
          end;
     end;


 procedure  THelpViewer.HandleEvent (var _Event: TEvent);
     var    M : PWinMenu;
            E : TEvent;
            i,j : int;

     begin
       inherited HandleEvent (_Event);

       case _Event.What of

         evCommand, evBroadcast:

           case _Event.Command of

             {cmPrint : Exit; -> otecko potlaci }

             cmExport : ;

             cmPrev   : if (top_keys>-1) and (pos_keys>0) then
                           begin
                             dec(pos_keys);
                             SetCommand(_Event,cmClose)
                           end
                        else ClearEvent(_Event);

             cmNext   : if (top_keys>-1) and (pos_keys<top_keys) then
                           begin
                             inc(pos_keys);
                             SetCommand(_Event,cmClose)
                           end
                        else ClearEvent(_Event);

             cmZobraz : if (top_keys>-1) then
                           begin
                             M:= WinMenu(' '+titZOBRAZ+' ',nil,nil);
                             j:= 0; for i:= 0 to top_keys do M^.AddItem(Item(' '+hk(j)+strpas(p_keys^[i])+' ',cmOTHER+i,nil));
                             if btZ <>nil then M^.MoveRel(btZ^.x0+10-M^.x0,btZ^.y0+30-M^.y0);
                             M^.Run(E);
                             Dispose(M, Done);
                             i:= 0; while (i<=top_keys) and (not isCommand(E,cmOTHER+i)) do inc(i);
                             if (i<=top_keys) then
                                begin
                                  pos_keys:= i;
                                  SetCommand(_Event,cmClose)
                                end
                             else ClearEvent(_Event)
                           end
                        else ClearEvent(_Event);

             cmArchiv : if p_archiv<>nil then
                           begin
                             fnn:= TSFunc_s(p_archiv)(fn);
                             if (fnn<>'') and (fnn<>fn) then SetCommand(_Event,cmClose)
                             else begin
                                    ClearEvent(_Event);
                                    fnn:= fn
                                  end;
                           end
                        else ClearEvent(_Event);
           end

       end;
     end;


 procedure THelpViewer.Run(_Event: TEvent);
     var   p_help : PHelp;
           bres : bool;
           sd : string;
     begin
       read_keys;
       repeat
         if fn<>fnn then
            begin
              fn:= fnn;
              release_keys;
              read_keys;
            end;
         if (top_keys>-1) then kluc:= strpas(p_keys^[pos_keys]);
         if d_title then sd:= decode_date_fn(fn)
         else sd:= '';

         p_help:= New(PHelp,Init(fn,false,hlpXXX));
         p_help^.handler_owner:= @Self;
         p_help^.dxb:= 0; p_help^.dyb:= btHEIGHT+10;
         p_help^.init_buttons:= @ext_init_buttons_StaViewer;
         p_help^.handler_buttons:= @ext_handle_StaViewer;
         p_help^.help(kluc,cut_(title)+sd);
         Dispose(p_help);
       until (top_keys=-1) or ((kluc=strpas(p_keys^[pos_keys])) and (fn=fnn));
       release_keys
     end;



 procedure HelpViewer(_fn,_title: string;
                      _p_archiv: PSFunc_s; _p_export: pointer; _d_title: bool;
                      _hlpXXX: pchar);
     var   v: PHelpViewer;
           _Event: TEvent;
     begin
       v:= New(PHelpViewer,Init(_fn,_title, _p_archiv,_p_export, _d_title, _hlpXXX));
       v^.Run(_Event);
       Dispose(v,Done);
     end;
