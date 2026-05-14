{ -------------------------------------------------------- }
{ Okna pre BGI                                             }
{ -------------------------------------------------------- }
{
  zaznam o parametroch okna:
}
const WinReg : PWinReg = nil;
      Wins   : int =  0;

{$IFDEF BGI}

   const WinHDD     : int    = -1;
         ind_WinHDD : Pbytes = nil;
         top_WinHDD : int    = -1;

   function  new_WinHDD: int;
      var    _ind_WinHDD: Pbytes;
             ind,i : int;
             res   : bool;
      begin
        ind:= -1; res:= false;
        while not res do
          begin
            inc(ind);
            res:= true;
            i:= 0;
            while (res) and (i<=top_WinHDD) do
              begin
                res:= ind_WinHDD^[i] <> ind;
                inc(i)
              end
          end;

        inc(top_WinHDD);
        GetMem(_ind_WinHDD,sizeof(byte)*(top_WinHDD+1));
        Move(ind_WinHDD^,_ind_WinHDD^,sizeof(byte)*(top_WinHDD));
        if (ind_WinHDD<>nil) then FreeMem(ind_WinHDD,sizeof(byte)*(top_WinHDD));
        ind_WinHDD:= _ind_WinHDD;

        ind_WinHDD^[top_WinHDD]:= ind;
        new_WinHDD:= ind
      end;


   procedure disp_WinHDD(name: string);
      var    i,j, ind,code : int;
             _ind_WinHDD   : Pbytes;
      begin
        if (ind_WinHDD=nil) then Exit;

        i:= pos(nameSaveWin,name);
        name:= copy(name,i,length(name)-i-3);
        name:= copy(name,length(nameSaveWin)+1,length(name)-length(nameSaveWin));
        Val(name, ind,code);

        i:= 0;
        while (i<=top_WinHDD) and (ind_WinHDD^[i]<>ind) do inc(i);
        if (i>top_WinHDD) then exit;

        if top_WinHDD>0 then
           begin
             GetMem(_ind_WinHDD,sizeof(byte)*(top_WinHDD));
             Move(ind_WinHDD^[0],_ind_WinHDD^[0],i);
             Move(ind_WinHDD^[i+1],_ind_WinHDD^[i],top_WinHDD-i);
           end
        else _ind_WinHDD:= nil;
        FreeMem(ind_WinHDD,sizeof(byte)*(top_WinHDD+1));
        Dec(top_WinHDD);
        ind_WinHDD:= _ind_WinHDD
      end;

{$ENDIF}


{ -------------------------------------------------------- }

{ ---------------------
   obnova obrazovky
  --------------------- }
{
  restore ... obnovit podklad
  dealloc ... odalokovat
}
function RestSubWin(var win: PWin; restore,dealloc: bool): bool;
   var   f   : file;
         s   : string;
         pom : pointer;
         res : int;
   label X;
   begin
     RestSubWin:= true;
     if win=nil then Exit;

     {$IFDEF BGI}
       if win^.size <= 0 then Exit;
     {$ENDIF}
     with win^ do
       begin
         if next<>nil then RestSubWin:= RestSubWin(next, restore,dealloc);
         {$IFDEF BGI}
           pom:= p;
           s:= StrPas(name);
           if (s<>'') and restore then
              begin
                if not ReadFile(pom,size,s) then goto X; { Exit }
              end;
         {$ENDIF}
         if restore then
            begin
             {$IFDEF BGI}
               {SetWriteMode(MiscCommand+SetGetImageReadWrite);
               SetWriteMode(GetImageMode+ForeMoveWrite);}
               PutImage(x0,y0,pom^,{CopyPut}NormalPut);
               {SetWriteMode(0);}
             {$ENDIF}
             {$IFDEF SPEA}
               if p>=0 then SPboxrest(p, x0,MaxY-y1);
             {$ENDIF}
            end;
         {$IFDEF BGI}
           if (pom<>p) and (pom<>nil) then FreeMem(pom,size);
         {$ENDIF}
         if dealloc then
            begin
             {$IFDEF BGI}
              if s<>'' then
                 begin
                 X: disp_WinHDD(s);
                    Dec(WinHDD);
                    DelFile(s);
                    StrDispose(name)
                 end;
              if p<>nil then FreeMem(p,size)
             {$ENDIF}
             {$IFDEF SPEA}
              if p>=0 then SPboxfree(p)
             {$ENDIF}
            end
       end;
     if dealloc then
        begin
          Dispose(win); win:= nil
        end
   end;

function RestWin(var _WinReg: PWinReg; restore,dealloc: bool): bool;
   var   W     : PWinReg;
         b,b2  : bool;
         xl,yl : int;
   begin
     RestWin:= false;
     if _WinReg = nil then Exit;

     m_off(b, xl,yl);

     W:= _WinReg;
     with W^ do
       begin
         RestSubWin(win, restore,dealloc);
         _WinReg:= prev
       end;
     if dealloc then
        begin
          b2:= W=_WinReg;
          Dispose(W);
          if b2 then _WinReg:= nil
        end;
     RestWin:= true;

     m_on(b, xl,yl)
   end;


{ ---------------------
   uchovanie obrazovky
  --------------------- }
{
  uchova parametre okna so suradnicami _x0,_y0,_x1,_y1:
}
function SaveSubWin(_x0,_y0,_x1,_y1: int;
                    var index: int; pocet: int;
                    var win: PWin
                   ): bool;
   var   f    : file;
         s    : string;
         bres : bool;
         dy, res,height : int;
   begin
     SaveSubWin:= false;
     win:= nil;
     if (index>pocet) then begin SaveSubWin:= true; Exit end;
     if (maxavail<minWinHeap) or (pocet=0) then Exit;

     bres:= false;
     New(win); fillchar(win^,sizeof(win^),0);
     with win^ do
      begin
        { vypocet suradnic ukladanej plochy }
        dy:= (_y1 - _y0 + 1) div pocet;
        x0:= _x0; x1:= _x1;
        y0:= _y0 + dy*index; if index<>0 then inc(y0,1);
        y1:= Minimum(y0+dy,_y1);

        {$IFDEF BGI}
          size:= ImageSize(x0,y0,x1,y1);
          { urcenie miesta, kam sa uklada }
          if (not SaveWinMem) or (MaxAvail < minSaveWin__heap_size*1000) then
             begin
               inc(WinHDD);
               { kontrola na miesto na RAM disku }
               if {(driveSaveWin<>0) and} (DiskFree(driveSaveWin)>size) then s:= pathSaveWin else s:= '';
               s:= s+nameSaveWin+IntToStr(new_WinHDD,3,0)+'.'+extSaveWin;
               name:= StrPasNew(s)
             end
          else begin s:= ''; name:= '' end;
          { uchovanie do pamate }
          GetMem(p,size);

          {SetWriteMode(MiscCommand+SetGetImageReadWrite); SetWriteMode(GetImageMode+ForeMoveWrite);}
          SetWriteMode(0);
          GetImage(x0,y0,x1,y1,p^);
          {SetWriteMode(0);}

          if s<>'' then
             begin
               Assign(f,s); Rewrite(f,1);
               BlockWrite(f,p^,size,res);
               Close(f);
               FreeMem(p,size); p:= nil
             end;

          bres:= true;
        {$ENDIF}

        {$IFDEF SPEA}
          p:= SPboxsave(x0,MaxY-y1,x1,MaxY-y0,height,0);
          if p>=0 then bres:= true;
        {$ENDIF}

        { dalsi pan na holenie ? }
        next:= nil;
        if bres then
           if (y1<_y1) then
              begin
                inc(index);
                if SaveSubWin(x0,_y0,x1,_y1, index, pocet, next) then SaveSubWin:= true
              end
          else SaveSubWin:= true
      end
   end;


function SaveWin(_x0,_y0,_x1,_y1: int; var _WinReg: PWinReg): bool;
   var   Wp : PWinReg;
         W  : TWinReg;
         sw : PWin;
         dy,i, pocet : int;
         b     : bool;
         xl,yl : int;
         size,wsize : word;
   begin
     SaveWin:= false;

     m_off(b, xl,yl);

     { vypocet poctu ukladanych subokien }
     i:= 0; wsize:= minimum($A000,MaxAvail div 5);
     {$IFDEF BGI}
       repeat
         Inc(i);
         dy:= (_y1 - _y0 + 1) div i;
         size:= ImageSize(_x0,0,_x1,dy)
       until (size>0) and (size<=wsize);
     {$ENDIF}
     pocet:= maximum(i,1); i:= 0;

     if (maxavail>minWinHeap) then
       { inicializacia ukladanych subokien }
        if SaveSubWin(_x0,_y0,_x1,_y1, i,pocet, W.win) then
           begin { ulozenie okna }
             W.prev  := _WinReg;
             New(Wp);
             Wp^     := W;   { Move(W,Wp^,SizeOf(TWinReg)); }
             Wp^.tmp := Wp;  { ukazuje na seba }
             Wp^.desc:= Wins;
             _WinReg := Wp;
             SaveWin := true
           end
        else RestSubWin(W.win, true,true);

     m_on(b, xl,yl);
   end; { SaveWin }



{ ------------------------------
  volane fcie window managmentu
  ------------------------------ }
{
  otvori okno so suradnicami _x0,_y0,_x1,_y1:
   - uchova obsah pod,
   - vytvori tien pod presahujuci prave okraje dx a dy
}
function OpenWin(x0,y0,x1,y1, dx,dy: int; fill: bool): int;
   begin
     {$IFDEF DISPLAY_ZHASNI}
        {$IFNDEF SERVER}
           Rozsviet;
        {$ENDIF}
     {$ENDIF}
     if not SaveWin(x0,y0,x1+dx,y1+dy, WinReg) then OpenWin:= -1
     else begin
            if fill then FillWin(x0+dx,y0+dy,x1+dx,y1+dy,Black);
            inc(Wins);
            OpenWin:= WinReg^.desc
          end
   end; { OpenWin }


{
zatvori najvrchnejsie okno
}
procedure CloseWin;
    begin
      if RestWin(WinReg, true,true) then dec(Wins)
    end; { CloseWin }


procedure WinXY(const win: PWin; var _x0,_y0,_x1,_y1: int);
    var   p : PWin;
    begin
      _x0:= win^.x0; _x1:= win^.x1; _y0:= win^.y0; _y1:= win^.y1;
      p:= win^.next;
      while p<>nil do begin _y1:= p^.y1; p:= p^.next end
    end;


function MoveWin(_x0,_y0,_x1,_y1: int; _x01,_y01: int): bool;
   var   _WinReg: PWinReg;
         p : PWin;
   begin
     _WinReg:= nil;
     if SaveWin(_x0,_y0,_x1,_y1, _WinReg) then
        begin
          MoveWin:= true;
          p:= _WinReg^.win;
          while p<>nil do
            begin
              inc(p^.x0, _x01-_x0); inc(p^.y0, _y01-_y0);
              inc(p^.x1, _x01-_x0); inc(p^.y1, _y01-_y0);
              p:= p^.next
            end;
          RestWin(_WinReg, true,true)
        end
     else MoveWin:= false
   end;
