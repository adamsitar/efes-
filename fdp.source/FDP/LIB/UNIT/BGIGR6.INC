{
  Vrati pocet otvorenych okien riadenych BGIgr a Views
}

const WinHidden: bool = false;

function OpenWins: byte;
   begin
     OpenWins:= Wins
   end;

function OverlapWin(_x0,_y0,_x1,_y1: int; SelfWinDesc: int): bool;
   var   x0,y0,x1,y1: int;
         W: PWinReg;
         r: bool;
   begin
     r:= false;
     W:= WinReg;
     if (W<>nil) and ((SelfWinDesc=-1) or (SelfWinDesc<W^.desc)) then { lezi pod }
        while (not r) and (W<>nil) do
          begin
            WinXY(W^.win, x0,y0,x1,y1);
            r:=     (W^.desc<>SelfWinDesc)
                and (    ( ((_x0<=x0) and (x0<=_x1)) or ((_x0<=x1) and (x1<=_x1)) ) { prekryvaju sa   }
                      or ( ((_x0<=x0) and (x1<=_x1)) or ((x0<=_x0) and (_x1<=x1)) ) { jedno cez druhe }
                    )
                and
                    (    ( ((_y0<=y0) and (y0<=_y1)) or ((_y0<=y1) and (y1<=_y1)) )
                      or ( ((_y0<=y0) and (y1<=_y1)) or ((y0<=_y0) and (_y1<=y1)) ) { jedno cez druhe }
                    );
            if not r then W:= W^.prev
          end;
     OverlapWin:= r
   end;



{ ----------------------------------------------------------- }

{
  Fcia by mal skryt vsetky otvorene okna
  a obnovit ich povodny podklad.
  V pripade uspechu vrati true.
}

function skry_okno(var T,TempWinReg: PWinReg): bool;
   var   _x0,_y0,_x1,_y1 : int;
         r : bool;
   begin
     WinXY(T^.win, _x0,_y0,_x1,_y1);
     r:= SaveWin(_x0,_y0,_x1,_y1, TempWinReg);
     TempWinReg^.tmp:= T;
     if r then RestWin(T, true,false);
     skry_okno:= r
   end;

function skry_okna(var TempWinReg: PWinReg; zostane: int): bool;
   var   T : PWinReg;
         okien: int;
   begin
     TempWinReg:= nil; okien:= Wins;
     if WinHidden or (okien=zostane) then skry_okna:= true
     else begin
          {
            Skryje okna od najvrchnejsieho az pos spodne.
            V TempWinReg su usporiadane opacne ako vo WinReg.
          }
            T:= WinReg;
            while (T<>nil) and (okien>zostane) do
              if skry_okno(T,TempWinReg) then dec(okien)
              else begin
                     obnov_okna(TempWinReg, false);
                     break
                   end;
            WinHidden:= (T=nil) or (TempWinReg<>nil) or (okien=zostane);
            skry_okna:= WinHidden
          end
   end;


function vypis_do_okna(x0,y0,x1,y1: int; var TempWinReg: PWinReg; SelfWinDesc: int; zostane: int): bool;
   var   r: bool;
   begin
     TempWinReg:= nil;
     if OverlapWin(x0,y0,x1,y1,SelfWinDesc) then r:= SKRYVANIE and skry_okna(TempWinReg, zostane)
     else r:= true;
     vypis_do_okna:= r
   end;


function obnov_okno(var TempWinReg: PWinReg; novy_obsah: bool): bool;
   var   _x0,_y0,_x1,_y1 : int;
         N : PWinReg;
         W : PWin;
         r : bool;
   begin
     N:= nil; r:= true;
     if novy_obsah then
        begin
        { a) nacita obsah pod oknom }
          WinXY(TempWinReg^.tmp^.win, _x0,_y0,_x1,_y1);
          r:= SaveWin(_x0,_y0,_x1,_y1, N);
        { b) odalokuje stary podklad vykresleneho okna a prepise ho novym }
          if r then
             begin
             { prepisanie stareho novym podkladom }
               W:= TempWinReg^.tmp^.win;
               TempWinReg^.tmp^.win:= N^.win; { novy -> stary }
               N^.win:= W;                    { stary -> novy }
               RestWin(N,false,true)          { odalokovanie starieho podkladu }
             end
        end;
   { c) obnovi vykreslene okno }
     RestWin(TempWinReg,true,true);
     obnov_okno:= r
   end;

procedure obnov_okna(var TempWinReg: PWinReg; novy_obsah: bool);
   begin
     if TempWinReg<>nil then WinHidden:= false;
     while TempWinReg<>nil do obnov_okno(TempWinReg, novy_obsah)
   end;
