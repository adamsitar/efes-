
  procedure display_status_bgu(bgu: byte);
      var   i : int;
            b : bool;
      begin
        b:= false;
        for i:= lo_MPUadr to hi_MPUadr do
          if MPUs^[i].bgu=bgu then b:= b or (MPUs^[i].st<>0);
        btBGUi[bgu]^.visibility(b)
      end;


   {
     posledny stav MPU
   }
   function  write_MPUstatus(adr: byte; var f: text; title,stat : bool): bool;
       var   i : byte;
       begin
         if (adr<lo_MPUadr) or (adr>hi_MPUadr)  then Exit;

         if     (MPUs^[adr].bgu in [lo_BGUadr..hi_BGUadr])
            and ((stat) or (MPUs^[adr].st<>0)) then
            begin
              if title then
                 begin
                   writeln(f,' ');
                   writeln(f,'----------------------');
                   writeln(f,' ÅÉì ¸.'+cstr(MPUs^[adr].bgu,1)+' / åèì ¸.'+cstr(adr,1));
                   writeln(f,'----------------------');
                 end;

              writeln(f,' ˛ '+ByteToHex(MPUs^[adr].st)+' - '+BGU_MPUstat(MPUs^[adr].st)+'  ');
              writeln(f,' ˛ ÅÉì status (BUS0 = '+ByteToHex(MPUs^[adr].bus0)+')  '); {writeln(f,'    - ');}
              writeln(f,' ˛ åèì status (BUS1 = '+ByteToHex(MPUs^[adr].bus1)+', BUS2 = '+ByteToHex(MPUs^[adr].bus2)+')  ');

              if MPUs^[adr].bus1<>NOBGU then
                 for i:= 0 to 7 do
                     if ((MPUs^[adr].bus1 and (1 shl i)) <> 0) and (BUS1res[i]<>nil) then
                        writeln(f,'    - '+strpas(BUS1res[i])+'  ');

              if MPUs^[adr].bus2<>NOBGU then
                 for i:= 0 to 7 do
                     if ((MPUs^[adr].bus2 and (1 shl i)) <> 0) and (BUS2res[i]<>nil) then
                        writeln(f,'    - '+strpas(BUS2res[i])+'  ');

              writeln(f,' ');
              write_MPUstatus:= true
            end
         else write_MPUstatus:= false {writeln(f,' ˛ Not configured.'};
       end;


  procedure BGUstatus(bgu: int);
      const FN = 'BPU.tmp';
      var   f : text;
            i : int;
            b : bool;
      begin
        Assign(f,pathTMP+FN); Rewrite(f);
        b:= false;
        for i:= lo_MPUadr to hi_MPUadr do
          if MPUs^[i].bgu=bgu then
             begin
               b:= write_MPUstatus(i, f, true,false) or b
             end;
        Close(f);
        if b then _info(pathTMP+FN,'Last status of ÅÉì ¸'+cstr(bgu,1));
        DelFile(pathTMP+FN)
      end;


  procedure MPUstatus(adr: byte);
      const FN = 'MPU.tmp';
      var   f : text;
      begin
        Assign(f,pathTMP+FN); Rewrite(f);
        writeln(f);
        write_MPUstatus(adr, f, false,true);
        writeln(f);
        Close(f);
        _info(pathTMP+FN,'Last status of åèì ¸'+cstr(adr,1));
        DelFile(pathTMP+FN)
      end;

  {
    posledny stav MPUs
  }
  procedure MPUsstatus;
      const FN  = 'MPUs.tmp';
      var   f   : text;
            adr : byte;
      begin
        Assign(f,pathTMP+FN); Rewrite(f);
        writeln(f);
        for adr:= lo_MPUadr to hi_MPUadr do
            if MPUs^[adr].bgu<>NOBGU then
               begin
                 writeln(f,'---------------------');
                 writeln(f,' åèì ¸.'+cstr(adr,1));
                 writeln(f,'---------------------');
                 write_MPUstatus(adr, f, false,true);
                 writeln(f)
               end;
        Close(f);
        _info(pathTMP+FN,'Last status of åèì');
        DelFile(pathTMP+FN)
      end;


   function adr_check(form: PSingleForm; s: Pstring): bool; far;
      var   res   : bool;
            adr,k : int;
            u     : string;
      begin
        res:= s_check(form,s) and (cut_(s^)<>'');
        if res then
           begin
             if not (s^[1] in setDig+['$']) then s^:= '$'+s^;
             val(cut_(s^),adr,k);
             res:= (k=0) and (adr>=lo_MPUadr) and (adr<=hi_MPUadr)
           end;
        if not res then
           begin
             u:= 'Invalid MPU address. ('+ByteToHex(lo_MPUadr)+'..'+ByteToHex(hi_MPUadr)+')'#0;
             PosErr(form^.x0,form^.y0, @u[1]);
           end;
        adr_check:= res
      end;


  const MPUmsg = 'TEST of MPU ¸';

  function MPUi(var MPUind: string; var adr,ind: int): int;
     var   k: int;
     begin
       MPUi:= -1; adr:= -1; ind:= -1;
       if formular_s(MPUind,2, MPUmsg+'...',nil,1,@setABC,@setNil,2,nil{@adr_check},false,true) then
          begin
            ind:= is_NETadr(MPUind);
            if ind<0 then
               begin
                 val(MPUind,adr,k);
                 if    (adr<0)
                    or (adr<lo_MPUadr)
                    or (adr>hi_MPUadr)
                    or (not (MPUs^[adr].bgu in [lo_BGUadr..hi_BGUadr]))
                       then
                    begin
                      Say2(msgMESS,'MPU ¸'+MPUind+' not configured.');
                      Exit
                    end;
                 ind:= 0; while (ind<NODEpoc) and (NODEs^[ind].desc.ai<>adr) do inc(ind);
               end
            else adr:= NODEs^[ind].desc.ai;
          end;
       MPUi:= adr
     end;

  procedure MPUtesti(MPUind: string; adr,ind: int; s : string);
      var   res : byte;
      begin
        res:= MPUprint(adr);
        if s<>'' then s:= MPUind+'/'+s else s:= MPUind;
        if res<>0 then
           begin
             if Ask2(msgMESS,MPUmsg+s+' did not passed. Do you want see MPU status ?','',clGRe,Red, 1000)=ansAno then
                MPUstatus(adr);
           end
        else Say2(msgACCEPT,MPUmsg+s+' passed.')
      end;


  procedure MPUtest_strip;
      var   MPUind,s : string;
            adr,ind: int;
      begin
        if MPUi(MPUind,adr,ind)>-1 then
           begin
             MPUclear (adr);
             if ind<NODEpoc then
                begin
                  if strpos(NODEs^[ind].desc.inf,nd_MIL)<>nil then
                     begin
                       MPUwrite (adr, 0,0, '      ! MIL             ! BOD1B BOD2A BOD1A BOD3A ');
                       MPUwrite (adr, 0,1, '      ! 43245        IM ! 1220  1230  1250  1330  ');
                       MPUwrite (adr, 0,2, '      ! A34562          ! ----------------------- ');
                       MPUwrite (adr, 0,3, '      ! S0800+    K0450 ! UEEE  +S0500            ');
                       MPUwrite (adr, 0,4, 'S0760 ! 02MI21/L+    SD ! UKBB  +02MI23/L     MIL ');
                     end
                  else begin
                         MPUwrite (adr, 0,0, '    < ! SPEED BIRD      ! TEST  TEST  TEST  TEST  ');
                         MPUwrite (adr, 0,1, '      ! BAW3252     VIP ! 1220  1220  1220  1220  ');
                         MPUwrite (adr, 0,2, '      ! A7111           ! ----------- S0930 ----- ');
                         MPUwrite (adr, 0,3, '      ! S0800     K0450 ! UEEE                    ');
                         MPUwrite (adr, 0,4, 'S0860 ! B797/M     SC/F ! UKBB                 K1 ');
                       end;
                  s:= getPstr(NODEs^[ind].desc.name,1,[' ']);
                  MPUwrite (adr, 48-length(s)+1,4, s)
                end
             else begin
                    MPUwrite (adr, 0,0, '--------------------------------------------------');
                    MPUwrite (adr, 0,1, '! MPU TEST/åèì íÖëí ');
                    MPUwrite (adr, 0,2, '! MPU N.'+MPUind);
                    MPUwrite (adr, 0,3, '! '+DateToStr2(day,month,year)+'/'+TimeToStr(hour,min,':'));
                    MPUwrite (adr, 0,4, '--------------------------------------------------');
                    s:= ''
                  end;
             MPUtesti(MPUind, adr,ind, s)
           end
      end;


  function write_txt(text_adr: pointer; i: int; s: string): string; far;
     begin
       move(TMPUbuff(text_adr^)[i],s[1],MAX_ZNAK_MPU);
       s[0]:= chr(MAX_ZNAK_MPU);
       write_txt:= s
     end;

  function read_txt(text_adr: pointer; i: int; s: string): string; far;
     begin
       s:= inschar(s,MAX_ZNAK_MPU,' ',1);
       move(s[1],TMPUbuff(text_adr^)[i],MAX_ZNAK_MPU)
     end;


  procedure init_editor_bt(E: PEditors);
      var   bt1: PbtOk;
            bt2: PbtCancel;
            bt3: PDialogButton;
            xt,yt, yi,c : int;
      begin
        with E^ do
          begin
            Win^.get_btXY(1,0, xt,yt);
            bt1:= New(PbtOK, Init(Win,xt,yt, kbCtrlEnter));

            Win^.get_btXY(1,1, xt,yt);
            bt2:= New(PbtCancel,Init(Win,xt,yt));
          end;
      end;


  var test_buff : TMPUbuff;

  procedure MPUtest_text;
      const  f    : Tcentr = (x: initX; y: initY; m: 1);
      var    form : PEditors;
             E    : TEvent;
             MPUind,s  : string;
             adr,ind,i : int;
             pbuff : pointer;
      begin
        if MPUi(MPUind,adr,ind)>-1 then
           begin
             pbuff:= @test_buff;
             form:= New(PEditors,Init(
                        nil, f.x,f.y,f.m, cmOK, 'TEXT OF TEST',
                        false,
                        nil, MAX_RDK_MPU,MAX_ZNAK_MPU,MAX_RDK_MPU,
                        @write_txt,@read_txt,
                        pbuff,0,0, false,false,
                        [],[],''{kbNL},
                        nil,
                        0,dbtHEIGHT+10,
                        @init_editor_bt,nil,nil,nil,{_init_buttons,_handle_buttons,_handler_owner,_handler_data,}
                        clBUTTON_COLOR,clgre, 0,clgre, clBUTTON_COLOR,help.cl_tx,
                        nil)
                       );
             form^.upcas:= true;
             form^.Run(E);
             if form^.corr_res then
                begin
                  for i:= 0 to MAX_RDK_MPU-1 do
                    begin
                      s[0]:= chr(MAX_ZNAK_MPU);
                      move(test_buff[i][0],s[1],MAX_ZNAK_MPU);
                      MPUwrite (adr, 0,i, s)
                    end;
                  MPUtesti(MPUind, adr,ind,getPstr(NODEs^[ind].desc.name,1,[' ']));
                end;
             Dispose(form,Done)
           end
      end;
