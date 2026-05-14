type PNI = ^TNI;
     TNI = record
       N   : PNETnodes;
       pkt : long;
       ack : long;
       max : long;
       mem : long;
     end;

{IFDEF NODES100}

 (*{$I ..\lib\mnu\_nodes.mnu}

 function alloc_NODEmenu: PWinMenu;
    const max_items = maxNODES;
    var   NODEmenu  : PWinMenu;
          NODEitems : array[0..max_items-1] of PItem;
          items,i   : int;
          nl,actual : bool;
          cond      : string;

    begin
      alloc_NODEmenu:= nil;
      NODEmenu:= OptMenu_S(NSTAT_,nil,cmNODES_NASTAVENIE,(MaxY-100) div 20,nil);
      _NODESTAT_init(NODEmenu);
      alloc_NODEmenu:= NODEmenu;
    end;


 function _handle_NODE: bool; far;
    var   NODEmenu : PWinMenu;
          E : TEvent;
          x,y : int;
    begin
      _handle_NODE:= false;

      NODEmenu:= alloc_NODEmenu;
      if NODEmenu=nil then Exit;
      NODEmenu^.Centre;
      NODEmenu^.Run(E);
      {if ((E.What and evMessage)<>0) then _handle_event_NODE(E,sc,NODE);}
      Dispose(NODEmenu, Done)
    end;


 procedure NODEs_info(uplna: bool);
     begin
       {_handle_NODE}
     end;

 *)

{ELSE}

 procedure _trasy0(x0,y0,x1,y1: int; NI: PNI); far;
     var    i: int;
     begin
       bgigraph.button(x0,y0,x1,y1,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF},btSmall,btON);
       for i:= 0 to NODEpoc-1 do with NI^.N^[i].desc do
           begin
             Write_(x0+dx_ed+10, y0+dy_ed+10+i*12,strpas(name), clGRc);
             if NI^.N^[i].stat.TrasaOK then icYes(x1-17, y0+i*12+8)
             else icNo(x1-21, y0+i*12+5)
           end;
     end;

 function _check0(I: PInfo; NI: PNI): bool; far;
    var    j,x1,y0: int;
           b : bool;
           TempWinReg : PWinReg;
    begin
      _check0:= false;
      x1:= I^.x1-dx_Window_text; y0:= I^.y0+dy_Window_text;

      b:= false;
      for j:= 0 to NODEpoc-1 do if (NI^.N^[j].stat.TrasaOK <> NODEs^[j].stat.TrasaOK) then
          begin
            b:= true;
            break
          end;
      if not b then exit;
      if not vypis_do_okna(I^.x0+dx_Window_text,y0,x1,I^.y1-dy_Window_text, TempWinReg,1,1) then Exit;

      for j:= 0 to minimum(15,NODEpoc)-1 do if (NI^.N^[j].stat.TrasaOK <> NODEs^[j].stat.TrasaOK) then
          begin
            NI^.N^[j].stat.TrasaOK:= NODEs^[j].stat.TrasaOK;
            WriteStr(x1+dx_ed-21,y0+dy_ed+10+j*12,'  ',
                     clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF},clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF}
                    );
            if NI^.N^[j].stat.TrasaOK then icYes(x1-17, y0+j*12+8)
            else icNo(x1-21, y0+j*12+5)
          end;

      obnov_okna(TempWinReg, true)
    end;


 procedure _trasy(x0,y0,x1,y1: int; NI: PNI); far;
     const  s: array[false..true] of char = ('.','*');
     var    i,c: int;
     begin
       bgigraph.button(x0,y0,x1,y1,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF},btSmall,btON);
       for i:= 0 to NODEpoc-1 do with NI^.N^[i].desc do
           begin
             Write_(x0+dx_ed+10, y0+dy_ed+10+i*12,strpas(name), clGRc);
             if NI^.N^[i].stat.TrasaOK then
                begin
                  icYes(x1-41, y0+i*12+8);
                  c:= cyan
                end
             else begin
                    icNo(x1-45, y0+i*12+5);
                    c:= red
                  end;
             Write_(x1+dx_ed-20,y0+10+dy_ed+i*12,s[NI^.N^[i].stat.semaphor],c)
           end;

       inc(x0,dx_ed+10); inc(y1,dy_ed);
       Write_   (x0, y1-58,'Pkt', clGRb);
       OutTextXY(x0, y1-46,'Ack');
       OutTextXY(x0, y1-34,'MaxAvail');
       OutTextXY(x0, y1-22,'MemAvail');

       inc(x1,dx_ed);
       WriteStr (x1-58, y1-58,IntToStr(NI^.pkt,4,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF});
       WriteStr (x1-58, y1-46,IntToStr(NI^.ack,4,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF});
       WriteStr (x1-60, y1-34,IntToStr(NI^.max,6,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF});
       WriteStr (x1-60, y1-22,IntToStr(NI^.mem,6,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF})
     end;



 function _check_trasy0(I: PInfo; NI: PNI): bool; far;
    const  s : array[false..true] of char = ('.','*');
    var    j,c, x1,y0,y1: int;
           b : bool;
           TempWinReg : PWinReg;
    begin
      _check_trasy0:= false;
      x1:= I^.x1-dx_Window_text; y0:= I^.y0+dy_Window_text; y1:= I^.y1-dy_Window_text;

      b:= false;
      for j:= 0 to NODEpoc-1 do
        if    (NI^.N^[j].stat.TrasaOK  <> NODEs^[j].stat.TrasaOK )
           or (NI^.N^[j].stat.semaphor <> NODEs^[j].stat.semaphor) then
              begin
                b:= true;
                break
              end;

      if (not b) or (not vypis_do_okna(I^.x0,I^.y0,I^.x1,I^.y1, TempWinReg,1,1)) then Exit;

      for j:= 0 to NODEpoc-1 do
        if    (NI^.N^[j].stat.TrasaOK  <> NODEs^[j].stat.TrasaOK )
           or (NI^.N^[j].stat.semaphor <> NODEs^[j].stat.semaphor) then
              begin
                NI^.N^[j].stat.TrasaOK := NODEs^[j].stat.TrasaOK;
                NI^.N^[j].stat.semaphor:= NODEs^[j].stat.semaphor;
                WriteStr(x1+dx_ed-45, y0+dy_ed+10+j*12,'     ',
                         clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF},clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF}
                        );
                if NI^.N^[j].stat.TrasaOK then
                    begin
                      icYes(x1-41, y0+j*12+8);
                      c:= cyan
                    end
                 else begin
                        icNo(x1-45, y0+j*12+5);
                        c:= red
                      end;
                 Write_(x1+dx_ed-20,y0+dy_ed+10+j*12,s[NI^.N^[j].stat.semaphor], c)
              end;

      obnov_okna(TempWinReg, true)
    end;

 function _check_trasy(I: PInfo; NI: PNI): bool; far;
    const  s : array[false..true] of char = ('.','*');
    var    j,c, x1,y0,y1: int;
           b : bool;
           TempWinReg : PWinReg;
    begin
      _check_trasy:= false;
      _check_trasy0(I,NI);

      x1:= I^.x1-dx_Window_text; y0:= I^.y0+dy_Window_text; y1:= I^.y1-dy_Window_text;

      b:=    (NI^.pkt<>NET^.top+1)
          or (NI^.ack<>NETack^.top+1)
          or (NI^.max<>maxavail)
          or (NI^.mem<>memavail);

      if (not b) or (not vypis_do_okna(I^.x0,I^.y0,I^.x1,I^.y1, TempWinReg,1,1)) then Exit;

      if (NI^.pkt<>NET^.top+1) then
         begin
           NI^.pkt:= NET^.top+1;
           WriteStr (x1+dx_ed- 58, y1+dy_ed-58,IntToStr(NI^.pkt,4,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF})
         end;

      if (NI^.ack<>NETack^.top+1) then
         begin
           NI^.ack:= NETack^.top+1;
           WriteStr (x1+dx_ed- 58, y1+dy_ed-46,IntToStr(NI^.ack,4,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF})
         end;

      if (NI^.max<>maxavail) then
         begin
           NI^.max:= maxavail;
           WriteStr (x1+dx_ed- 60, y1+dy_ed-34,IntToStr(NI^.max,6,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF})
         end;

      if (NI^.mem<>memavail) then
         begin
           NI^.mem:= memavail;
           WriteStr (x1+dx_ed- 60, y1+dy_ed-22,IntToStr(NI^.mem,6,0), clGRd,clBUTTON_COLOR{$IFNDEF EGAVGA}-1{$ENDIF})
         end;

      obnov_okna(TempWinReg, true)
    end;


 var   I  : PInfo;
       NI : PNI;

 procedure NODEs_info_check0; far;
     var   b: bool;
     begin
       b:= SKRYVANIE; SKRYVANIE:= true;
       _check_trasy0(I, NI);
       SKRYVANIE:= b
     end;

 procedure NODEs_info_check; far;
     var   b: bool;
     begin
       b:= SKRYVANIE; SKRYVANIE:= true;
       _check_trasy(I, NI);
       SKRYVANIE:= b
     end;

 procedure NODEs_info(uplna: bool);
     var   E   : TEvent;
           j,m,k : int;
           p   : pointer;
           b   : bool;
     begin
       New(NI);
       GetMem(NI^.N,sizeof(TNETnode)*NODEpoc);
       m:= SizeOf(TNETadr);

       k:= NODEpoc;
       for j:= 0 to NODEpoc-1 do
           begin
             NI^.N^[j]:= NODEs^[j];
             if m<StrLen(NODEs^[j].desc.name) then m:= StrLen(NODEs^[j].desc.name)
           end;

       if {$IFDEF BACKUP}
             {$IFDEF BACKUP_ACTIVE_2_NET}
                true
             {$ELSE}
                (not SERVERstatus)
             {$ENDIF}
          {$ELSE} {$IFDEF MASTER}
             {$IFDEF BACKUP_ACTIVE_2_NET}
               (not BACKUPstatus)
             {$ELSE}
               true
             {$ENDIF}
          {$ELSE}
             true
          {$ENDIF} {$ENDIF}
          then
       else k:= 1;


       NI^.pkt:= 99999; NI^.ack:= 99999;
       NI^.max:= 0; NI^.mem:= 0;
       if uplna then p:= @_trasy else p:= @_trasy0;
       I:= New(PInfo,Init(msgLAST,'', p, NI,
                          (m+2)*10+10+ord(uplna)*50,NODEpoc*12+ord(uplna)*68,
                          nil,0,0,0, nil,nil,
                          -1,nil,nil, -1,nil,nil)
                         );
       for j:= 0 to NODEpoc-1 do NETsend_msg (NODEs^[j].desc.adr, spr_HEARTBEAT, nil,0, true,net_flag_SEND);
       b:= info_INIT; info_INIT:= false;
       if uplna then
          begin
            I^.check:= @_check_trasy;
            ADiagnose:= NODEs_info_check;
          end
       else begin
              I^.check:= @_check_trasy0;
              ADiagnose:= NODEs_info_check0;
          end;
       NODE_WIN:= true;
       I^.Run(E);
       NODE_WIN:= false;
       ADiagnose:= nil;
       Dispose(I,Done);
       FreeMem(NI^.N,sizeof(TNETnode)*NODEpoc);
       Dispose(NI)
     end;

{ENDIF}
