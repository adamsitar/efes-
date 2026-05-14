
 procedure init_help;
     var   ftI,ftC,ftH: text;
           r,s,t: string;
           i: int;
           bres: bool;
     begin
       write('Initializing help contents...');

       if     (Exists(fn_hlp_exe)=0)
          and (Exists(fn_hlpI_exe)=0)
          and (   (Exists(fn_hlpC_exe)<>0)
               or (_GetFTime(fn_hlpC_exe)<=_GetFTime(fn_hlp_exe))
               or (_GetFTime(fn_hlpC_exe)<=_GetFTime(fn_hlpI_exe))
              ) then
          begin
            assign(ftH,fn_hlp_exe);  reset(ftH);
            assign(ftI,fn_hlpI_exe); reset(ftI);
            assign(ftC,fn_hlpC_exe); rewrite(ftC);
            readln(ftI,r);
            while not Eof(ftI) do
              begin
                t:= cut_(r);
                bres:= true;
                if (t<>'') and (t[1]<>';') then
                   begin
                     reset(ftH); bres:= false;
                     while (not Eof(ftH)) and (not bres) do
                       begin
                         readln(ftH,s);
                         bres:= system.pos(hlp_SOH+t+hlp_EOH,s)>0;
                       end;
                     if bres then
                        begin
                          s:= cut_(getstr(s,2,[hlp_EOH]));
                          i:= 1; while (i<length(r)) and (r[i]=' ') do inc(i);
                          r:= rightchar('',i,' ') + s;
                          bres:= cut_(r)<>'';
                          if bres then r:= rightchar(r,70,' ') + '     ;'+t
                        end
                   end
                else begin
                       bres:= true;
                     end;
                if bres then writeln(ftC,r);
                readln(ftI,r);
              end;
            close(ftC);
            close(ftI);
            close(ftH);
          end;

       writeln(' Done.');
     end;


 constructor THelpIndex.Init;
       begin
         inherited Init(fn_hlpC_exe,true,nil{_hlpXXX});
         {$IFDEF PRN}
          dyb:= btHEIGHT+10;
          init_buttons:= @init_sc_butt1;
         {$ENDIF}

         is_pos_en:= true;
         item_en:= true;
         is_comment:= false;
         is_comment0:= true;
         comment_en:= true;
         item_dy:= 10;
       end;

 procedure  THelpIndex.HandleEvent (var _Event: TEvent);
     var    t,s: string;
            fT: text;
            bres: bool;
     begin
       inherited HandleEvent (_Event);
       if    isCommand(_Event,cmScrollItemClicked)
          or isCommand(_Event,cmScrollItemEntered)
          or isCommand(_Event,cmOK) then
          begin
            if pos>=0 then t:= cut_(get(pos));
            if t<>'' then
               begin
                 Assign(fT,fn); Reset(fT); bres:= false;
                 while (not Eof(fT)) and (not bres) do
                   begin
                     readln(fT,s);
                     if t=cut_(getstr(s,1,[';'])) then
                        begin
                          bres:= true;
                          t:= cut_(getstr(s,2,[';']))
                        end;
                   end;
                 Close(fT);
                 if bres then _help_(t,'')
               end;
            ClearEvent(_Event);
          end;
     end;

 procedure _help_index;
     var   h: PHelpIndex;
     begin
       h:= New(PHelpIndex,Init);
       h^.help('','Help index'); { vykona i done }
       Dispose(h);
     end;
