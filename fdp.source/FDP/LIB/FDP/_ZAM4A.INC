{ -------------------------------
  handlery
}

function alloc_ZAMmenu(ZAM: PZAM; _plan,_arch: bool): PWinMenu;
   const max_items = 20;
   var   ZAMmenu   : PWinMenu;
         ZAMitems  : array[0..max_items-1] of PItem;
         items,i   : int;
         nl,b1,b2  : bool;
         cond      : string;
         limit,rdat: real;

   begin
      m_set_shape(HODINY);

      ZAMmenu := WinMenu(' '+ZAM^.kod+' ',nil,nil);

      limit := DateToSec(ZAM^.zac.rok,ZAM^.zac.mes,ZAM^.zac.den);
      rdat  := DateToSec(year,month,day);
      items := 0;

      {$IFDEF PROCESS_ZAM}
       if (not _arch) and (ZAM^.poz<poz_HANGAR) {and (limit>=rdat)} then
          begin

            if _is_SEND(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_SEND, cmZAMsend, nil);
                 inc(items)
               end;

            if _is_CHG(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_CHG_, cmZAMzme, nil);
                 inc(items)
               end;

            if _is_CNL(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_CNL_, cmZAMzru, nil);
                 inc(items)
               end;

            if _is_DEP(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_DEP_, cmZAMzac, nil);
                 inc(items)
               end;

            if _is_BRK(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_BRK_, cmZAMpre, nil);
                 inc(items)
               end;

            if _is_CNT(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_CNT_, cmZAMpok, nil);
                 inc(items)
               end;

            if _is_ARR(ZAM,nil) then
               begin
                 ZAMitems[items]:= Item(tit_ARR_, cmZAMkon, nil);
                 inc(items)
               end;

            if _is_LETOV(ZAM,nil) then
               begin
                 if items>0 then
                    begin
                      ZAMitems[items]:= NewLine2(0,nil);
                      inc(items);
                    end;
                 ZAMitems[items]:= Item(tit_LETOV_, cmZAMlet, nil);
                 inc(items)
               end
          end;
      {$ENDIF}

      b1:=    {is_plani___(ZAM^.pozn, max_ZAM_pozn_r_hi,max_ZAM_pozn_rm,-1)
           or} pis_STRIP_ZAM;
      b2:= b1
             {$IFDEF PRN} or true {$ENDIF}
             {$IFDEF PROCESS_ZAM} or true {$ENDIF}
           ;

      nl:= false;
      if b2 and (items>0) then
         begin
           ZAMitems[items]:= NewLine2(0,nil);
           inc(items);
           nl:= true
         end;
      i:= items;

      if b1 then
         begin
           ZAMitems[items]:= Item(tit_VIEW, cmZAMview, nil);
           inc(items);
         end;

      {$IFDEF PRN}
        ZAMitems[items]:= Item(tit_PRINT, cmZAMprint, nil);
        inc(items);
      {$ENDIF}

      {$IFDEF PROCESS_ZAM}
        if items>i then
           begin
             ZAMitems[items]:= NewLine(nil);
             inc(items);
           end;

        ZAMitems[items]:= Item(tit_COPY, cmZAM, nil);
        inc(items);
      {$ENDIF}

      if items=0 then begin Dispose(ZAMmenu,Done); ZAMmenu:= nil end
      else for i:= 0 to items-1 do ZAMmenu^.AddItem(ZAMitems[i]);
      alloc_ZAMmenu:= ZAMmenu;

      m_restore_shape
   end;


function _handle_ZAM(sc: PScroller; ZAM: PZAM; _arch: bool): bool; far;
   var   ZAMmenu   : PWinMenu;
         E         : TEvent;
         x,y       : int;
         res       : bool;
   begin
     _handle_ZAM:= false;

     ZAMmenu:= alloc_ZAMmenu(ZAM,true,_arch);
     if ZAMmenu=nil then Exit;
     sc_menu_xy(sc, x,y, 0,0);
     ZAMmenu^.MoveRel(x+10-ZAMmenu^.x0,y+30-ZAMmenu^.y0);
     ZAMmenu^.Run(E);
     if ((E.What and evMessage)<>0) then _handle_event_ZAM(E,sc,ZAM);
     Dispose(ZAMmenu, Done)
   end;


function handle_ZAM(sc: PScroller; ZAM: PZAM): bool; far;
   begin
     handle_ZAM:= _handle_ZAM(sc, ZAM, false)
   end;

function handle_ZAM_ARCH(sc: PScroller; ZAM: PZAM): bool; far;
   begin
     handle_ZAM_ARCH:= _handle_ZAM(sc, ZAM, true)
   end;


function handle_ZAM_object(var Ev: TEvent; sc: PScrollInd; ZAM: PZAM; PLAN: PPLAN): bool; far;
   begin
     handle_ZAM_object:= _handle_ZAM(sc, ZAM, false)
   end;


function handle_ZAM_strip(iFPL: PSTRIP; ZAM: PZAM; sc: PScroller; var E: TEvent; dx,dy: int): bool; far;
   begin
     handle_ZAM_strip:= false;
     {$IFDEF TABLET_ZAM}
       info_ZAM(ZAM,tit_info_ZAM+' '+ZAM^.kod)
     {$ENDIF}
   end;