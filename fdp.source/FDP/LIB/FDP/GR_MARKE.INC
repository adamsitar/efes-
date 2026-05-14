{ -----------------
   Mark10y
  -----------------
}

destructor TMark10.Done;
  begin
    if ZozText<>nil then Dispose(ZozText,Done);
    if GP<>nil then Dispose(GP,Done)
  end;


procedure TMark10.readGrOb(var _InF: file);
    var   PB    : TGBod;
          PT    : PGText;
          Zs,Zd : TZdZs;
          veta  : ch255;
          i,pom : int;
          res   : word;
    begin
      inherited readGrOb(_InF);
      ZozText:= nil;
      BlockRead(_InF,pocet,SizeOf(pocet),res);

      if pocet>=1 then
         begin
           ZozText:= New(PZozText,Init);
           pom:= 0;
           repeat
             new(PT);

             BlockRead(_InF,Zd, Sizeof(TZdZs),res);
             BlockRead(_InF,Zs, Sizeof(TZdZs),res);
             i:= 0;
             repeat
               BlockRead(_InF,veta[i],SizeOf(char),res);
               inc(i)
             until (veta[i-1]=#0) or (i>=255);

             ZdZs_xy(Zd,Zs, PB.X,PB.Y);
             PT^.X:= PB.X; PT^.Y:= PB.Y; PT^.Ts:= 0;
             PT^.vet:= StrNew(veta);

             ZozText^.PridejNaKonec(PT);
             inc(pom)
           until pom >= pocet;
         end
   end;


{$IFDEF DRAW}

  procedure _write_mark_text(X,Y,dx,dy: int; vet: pchar; _mark_8x8: bool);
      begin
        if not mark_txt then Exit;
        if _mark_8x8 then WriteClippedText(X+2+dx,Y+2+dy,StrPas(vet))
        else F6x4(X+3+dx,Y+9+dy,StrPas(vet))
      end;

  procedure TMark10._draw_(X,Y: long; P: pointer);
      begin
        MoveTo(X-3,Y); LineTo(X+3,Y);
        MoveTo(X,Y-3); LineTo(X,Y+3);
        _write_mark_text(X,Y,0,0, PGText(P)^.vet,mark_8x8)
      end;


  procedure TMark10.Draw;
      var   PT  : PGText;
            PB  : TGBod;
            X,Y : long;
      begin
        if ZozText=nil then Exit;

        SetColor(farba);
        ZozText^.JdiNaZacatek;
        repeat
          PT:= ZozText^.DejAktPrvek;
          PB.X:= PT^.X; PB.Y:= PT^.Y;
          BodXY(@PB, X,Y);
          _draw_(X,Y, PT)
        until ZozText^.JdiNaDalsi_
      end;

   {
   procedure TMark11._draw_(X,Y: long; P: pointer);
       begin
         Line(X-2,Y-2,X-2,Y+2); Line(X-2,Y+2,X+2,Y+2);
         Line(X+2,Y+2,X+2,Y-2); Line(X+2,Y-2,X-2,Y-2);
         Line(X,Y-2,X,Y-4);     Line(X,Y+2,X,Y+4);
         Line(X+2,Y,X+4,Y);     Line(X-2,Y,X-4,Y);

         _write_mark_text(X,Y,0,PGText(P)^.vet)
       end;
   }
{$ENDIF}


{ -----------------
   Mark13
  -----------------
}

procedure RW_Mark13(RW: byte; var f: File; var Zd,Zs: TZdZs; var Ts: int; var veta : ch255);
    var   res  : word;
          i    : int;
    begin
      _BlockRW(RW,f, Zd,sizeof(TZdZs),res);
      _BlockRW(RW,f, Zs,sizeof(TZdZs),res);
      _BlockRW(RW,f, Ts,sizeof(Ts),   res);
      i:= 0;
      if RW=0 then
         repeat
           BlockRead(f,veta[i],SizeOf(char),res);
           inc(i)
         until (veta[i-1]=NULL) or (i>=255)
      else while i<=StrLen(veta) do
             begin
               BlockWrite(f,veta[i],SizeOf(char),res);
               inc(i)
             end
    end;


procedure TMark13.readGrOb(var _InF: file);
    var   PB    : TGBod;
          PT    : PGText;
          Zs,Zd : TZdZs;
          veta  : ch255;
          res   : word;
          pom   : int;
    begin
      TGrOb.readGrOb(_InF);
      ZozText:= nil;
      BlockRead(_InF,pocet,SizeOf(pocet),res);

      if pocet>=1 then
         begin
           ZozText:= New(PZozText,Init);
           pom:= 0;
           repeat
             new(PT);

             RW_Mark13(0, _InF, Zd,Zs, PT^.Ts, veta);
             ZdZs_xy(Zd,Zs, PB.X,PB.Y);
             PT^.X := PB.X; PT^.Y := PB.Y;
             PT^.vet := StrNew(veta);
             ZozText^.PridejNaKonec(PT);
             inc(pom)
           until pom >= pocet
         end
   end;


{$IFDEF DRAW}

  procedure LetM(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_Mlet]);
        Line(X+1,Y,X+4,Y); Line(X-1,Y,X-4,Y);
        Line(X,Y+1,X,Y+4); Line(X,Y-1,X,Y-4);
        _write_mark_text(X,Y,-strlen(vet)*8,-11,vet,mark_8x8)   {+3,-3}
      end; { LetM }

  procedure LetA(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_Alet]);
        Line(X+1,Y,X+2,Y); Line(X-1,Y,X-2,Y);
        Line(X,Y+1,X,Y+2); Line(X,Y-1,X,Y-2);
        _write_mark_text(X,Y,-strlen(vet)*8,-11,vet,mark_8x8)                    {+3,-3}
      end; { LetA }

  procedure LetC(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_Clet]);
        Line(X+1,Y,X+4,Y); Line(X-1,Y,X-4,Y);
        Line(X,Y+1,X,Y+4); Line(X,Y-1,X,Y-4);
        _write_mark_text(X,Y,0,-11,vet,true{mark_8x8})  {+4,+8}
      end; { LetM }



  procedure _OB(X,Y: int);
      begin
        Line(X-1,Y,X+1,Y); Line(X,Y-1,X,Y+1)
      end;

  procedure OB(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_OB]);
        Line(X-1,Y,X+1,Y); Line(X,Y-1,X,Y+1);
        _write_mark_text(X,Y,0,-2,vet,mark_8x8)   {+3,-2}
      end;

  procedure SB(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_OB]);
        Line(X-1,Y,X+1,Y); Line(X,Y-1,X,Y+1);
        _write_mark_text(X,Y,0,2,vet,mark_8x8)
      end;


  const _3 : array[1..8 ] of int = (2,1, 0,-1, -2,1, 2,1);        {5,11}
        _4 : array[1..10] of int = (3,3, 3,-3, -3,-3, -3,3, 3,3); {5,11}
       {_6 : array[1..14] of int = (3,1, 1,-2, -1,-2, -3,1, -1,3, 1,3, 3,1); 5,11}


  procedure REP1(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_REP1]);
        if mark_typ then _drawpoly(X,Y,SYMpalette[sym_REP1], @_3,4)
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)   {+3,-2}
      end;

  procedure REP2(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_REP2]);
        if mark_typ then _fillpoly(X,Y,SYMpalette[sym_REP1], @_3,4)
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)
      end;


  procedure NDB1(X,Y: int; Vet: pchar);
      var   i: int;
      begin
        setcolor(SYMpalette[sym_NDB1]);
        if mark_typ then
           begin
             _drawpoly(X,Y,SYMpalette[sym_NDB1], @_3,4);
              for i:= 0 to 1 do Circle(X,Y,3+i*2)
           end
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)   {+3,-2}
      end;

  procedure NDB2(X,Y: int; Vet: pchar);
      var   i: int;
      begin
        setcolor(SYMpalette[sym_NDB2]);
        if mark_typ then
           begin
             _fillpoly(X,Y,SYMpalette[sym_NDB1], @_3,4);
              for i:= 0 to 1 do Circle(X,Y,3+i*2)
           end
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)   {+3,-2}
      end;


  procedure VOR(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_VOR]);
        if mark_typ then
           begin
             _drawpoly(X,Y,SYMpalette[sym_REP1], @_3,4);
             Circle(X,Y,10)
           end
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)
      end;


  procedure VOR_DME1(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_VOR_DME1]);
        if mark_typ then
           begin
             _drawpoly(X,Y,SYMpalette[sym_VOR_DME1], @_3,4);
             _drawpoly(X,Y,SYMpalette[sym_VOR_DME1], @_4,5);
             Circle(X,Y,10)
           end
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)
      end;

  procedure VOR_DME2(X,Y: int; Vet: pchar);
      begin
        setcolor(SYMpalette[sym_VOR_DME2]);
        if mark_typ then
           begin
             _fillpoly(X,Y,SYMpalette[sym_VOR_DME1], @_3,4);
             _drawpoly(X,Y,SYMpalette[sym_VOR_DME1], @_4,5);
             Circle(X,Y,10)
           end
        else _OB(X,Y);
        _write_mark_text(X,Y,0,0,vet,mark_8x8)
      end;


  procedure TMark13._draw_(X,Y: long; P: pointer);
      type  Tproc_draw = procedure(X,Y: int; Vet: pchar);
      var   proc : Tproc_draw;
      begin
        if MAPSCROLL or (PGText(P)^.Ts<0) then Exit;
        proc:= OB;

        case PGText(P)^.Ts of
          sym_CLet     : proc:= LetC;
          sym_MLet     : proc:= LetM;
          sym_ALet     : proc:= LetA;

          sym_NONE,
          sym_REPORT   : proc:= OB;
          sym_SECTOR   : proc:= SB;

          sym_REP1     : proc:= REP1;
          sym_REP2     : proc:= REP2;

          sym_NDB1     : proc:= NDB1;
          sym_NDB2     : proc:= NDB2;

          sym_VOR      : proc:= VOR;
          sym_VOR_DME1 : proc:= VOR_DME1;
          sym_VOR_DME2 : proc:= VOR_DME2
        end;

        setcolor(SYMpalette[PGText(P)^.Ts]);
        proc(X,Y, PGText(P)^.vet)
      end;
{$ENDIF}
