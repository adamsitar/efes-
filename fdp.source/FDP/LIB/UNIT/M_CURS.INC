const Kurzory : array[MYS..High(TMCursor)] of Tbyte16x16
                = (
                   {$IFDEF SPEA}
                    ((0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0),
                     (0,0,0,0,0,5,5,5,5,5,0,0,0,0,0,0),
                     (0,0,5,5,0,5,5,5,5,5,0,0,0,0,0,0),
                     (0,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0),
                     (5,5,5,5,5,5,5,5,5,0,5,0,0,0,5,0),
                     (5,5,5,5,5,5,5,0,5,5,5,5,0,0,5,0),
                     (0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5),
                     (0,0,5,5,5,0,5,5,5,5,5,5,5,0,5,0),
                     (0,0,0,0,0,0,0,5,5,5,0,0,0,0,5,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),
                    {$ELSE}
                    ((0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0),
                     (0,0,0,0,0,5,5,5,5,5,0,0,0,0,0,0),
                     (0,0,5,5,0,5,5,5,5,5,0,0,0,0,0,0),
                     (0,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0),
                     (5,5,5,5,5,5,5,5,5,2,5,0,0,0,5,0),
                     (5,5,5,5,5,5,5,2,5,5,5,5,0,0,5,0),
                     (0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5),
                     (0,0,5,5,5,0,5,5,5,5,5,5,5,0,5,0),
                     (0,0,0,0,0,0,0,5,5,5,0,0,0,0,5,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),
                    {$ENDIF}

                    ((0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0),
                     (0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
                     (0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0),
                     (0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
                     (0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0),
                     (0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
                     (0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),

                    ((0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0),
                     (0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0),
                     (0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1),
                     (0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1),
                     (0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1),
                     (0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1),
                     (0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1),
                     (0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),

                    ((0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0),
                     (0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0),
                     (0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,1,0,4,4,4,4,4,0,1,0,0,0,0),
                     (0,0,0,0,1,0,4,4,4,0,1,0,0,0,0,0),
                     (0,0,0,0,0,1,0,4,0,1,0,0,0,0,0,0),
                     (0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0),
                     (0,0,0,0,0,1,0,4,0,1,0,0,0,0,0,0),
                     (0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0),
                     (0,0,0,1,0,0,0,4,0,0,0,1,0,0,0,0),
                     (0,0,0,1,0,0,4,4,4,0,0,1,0,0,0,0),
                     (0,0,1,0,0,4,4,4,4,4,0,0,1,0,0,0),
                     (0,0,1,0,4,4,4,4,4,4,4,0,1,0,0,0),
                     (0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0)),


                    ((0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),


                    ((0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0),
                     (0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),


                    ((0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0),
                     (0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0),
                     (0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0),
                     (0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)),

                    ((0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                     (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0))
                   );



{ --------------------------------------------------- }
{  inicializacia                                      }
{ --------------------------------------------------- }

const last_mx: int = High(int);
      last_my: int = High(int);


{
  PO a P budem musiet alokovat vzdy pri prepinani kurzora
}

{$IFDEF BGI}

  var     m_cur    : array[MYS..High(TMCursor)] of pointer;  { pointer na preddefinovany kurzor }
          m_size   : array[MYS..High(TMCursor)] of word;     { velkost kurzora }
          _CurSize : word;

          PC,PO : ^Tbyte16x16;

  procedure PolozObr(x,y: int; Obr: Tbyte16x16);
      const c: array[0..5] of byte = (black,clWHITE,red,brown,yellow,clGRa);
      var   i,j: int;
      begin
        for i:= 0 to 15 do
            for j:= 0 to 15 do PutPixel(x+j,y+i,c[Obr[i,j]])
      end;

{$ENDIF}


{$IFDEF SPEA}

  const   andmask : andxor = ($FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,
                              $FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF,$FFFF
                             );

  const   PO : int = -1;

  var     m_cur   : array[MYS..High(TMCursor)] of andxor;
  const   m_col   : array[MYS..High(TMCursor)] of byte = (clGRa,white,white,yellow,white,white,white,white);
    
  {$IFOPT R+} {$DEFINE RPLUS} {$R-} {$ENDIF}

  procedure init_m_cur(kurzor: Tbyte16x16; var m_curi: andxor);
      var   i,j : int;
            c   : word;
      begin
        for i:= 0 to $F do
            begin
              m_curi[i]:= 0;
              for j:= $F downto 0 do
                  if kurzor[i,j]<>0 then m_curi[i]:= m_curi[i] + ( 1 shl ($F-j) )
            end
      end;

  {$IFDEF IPLUS} {$R+} {$ENDIF}

{$ENDIF}


procedure init__m_cursors;
    const x = 100; y = 100;
    var   i : TMCursor;
          res,height : int;
    begin

      {$IFDEF BGI}
         _CurSize := ImageSize(x,y,x+15,y+15);
         GetMem(PC,_CurSize);   { pracovny   }
         GetMem(PO,_CurSize);   { odpamatany }
         SetWriteMode(MiscCommand+SetGetImageReadOnly); { DEFINOVANIE TVARU KURZORA }
      {$ENDIF}
      {$IFDEF SPEA}
         {SetWriteMode(NormalPut);}
      {$ENDIF}

      for i:= MYS to High(TMCursor) do
        begin

         {$IFDEF BGI}
           m_size[i]:= ImageSize(x,y,x+15,y+15); { neskor parametre pre velkost mysi }
           GetMem(m_cur[i],m_size[i]);
           GetImage(x,y,x+15,y+15,PC^);          { odpamatanie podkladu }
           PolozObr(x,y, Kurzory[i]);            { vykreslenie }
         {$ENDIF}


         {$IFDEF BGI}
           GetImage(x,y,x+15,y+15,m_cur[i]^);    { nacitanie tvaru kurzora }
           PutImage(x,y,PC^,CopyPut);            { obnova podkladu }
           {SetWriteMode(MiscCommand+SetGetImageReadOnly);
           GetImage(x,y,x+15,y+15,PO^);}
         {$ENDIF}

         {$IFDEF SPEA}
           {m_cur[i]:= SPboxsave(x,MaxY-(y+15),x+15,MaxY-y,height,0);}
           init_m_cur(Kurzory[i], m_cur[i]);
         {$ENDIF}

        end;

      {$IFDEF BGI}
         SetWriteMode(0);
      {$ENDIF}
      {$IFDEF SPEA}
         {SetWriteMode(NormalPut);}
         mouse_status.curs:= MYS;
         spircurs(0,16,andmask,m_cur[MYS],16,16,0,0,0,0,m_col[MYS],0);
      {$ENDIF}
      ClearDevice
    end;  { init__m_cursors }


procedure done__m_cursors;
    var   i: TMCursor;
    begin
     {$IFDEF BGI}
        for i:= MYS to High(TMCursor) do FreeMem(m_cur[i],m_size[i]);
        FreeMem(PO,_CurSize);   { odpamatany }
        FreeMem(PC,_CurSize);   { pracovny   }
     {$ENDIF}
     {IFDEF SPEA
        for i:= MYS to High(TMCursor) do
            begin
              SPboxfree(m_cur[i])
            end
     ENDIF}
    end;



{ -------------------------------------------------- }
{  zobrazenie mysi                                   }
{ -------------------------------------------------- }

{
  osetrenie, aby putimage a getimage nebrali obrazok za plochou obrazovky
}

procedure nepust_mys_za_okraj; { lebo prejde dolava }
    begin
      m_enabled:= false;
      with mouse_status.stat do
        begin
        {$IFDEF BGI}
          if (x>MaxX-15) then set_xy(Limit(x, 0,MaxX-15, 0),y)
        {$ENDIF}
        {$IFDEF SPEA}
          if (y>MaxY-15) then set_xy(x,Limit(y, 0,MaxY-15, 0));
        {$ENDIF}
        end;
      m_enabled:= true
    end;


procedure m_hide;
    begin
      if (is_mouse=0) or (not (m_kresli and m_enabled and m_visible)) then Exit;

      {$IFDEF BGI}
        SetWriteMode(MiscCommand+SetGetImageReadWrite);
        SetWriteMode(GetImageMode+ForeMoveWrite);
        PutImage(last_mx,last_my, PO^, CopyPut);
        SetWriteMode(MiscCommand+2);
      {$ENDIF}

      {$IFDEF SPEA}
         {if PO>-1 then
            begin
              SPboxrest(PO, last_mx,MaxY-(last_my+15));
              SPboxfree(PO);
              PO:= -1
            end;}
          SPcrcurs;
      {$ENDIF}

     {last_mx:= High(int); last_my:= High(int);}
      m_visible:= false
    end;


procedure m_show;
    var   height : int;
    begin
      if (is_mouse=0) or (not (m_kresli and m_enabled)) or (m_visible) then Exit;

      {$IFDEF BGI}
        SetWriteMode(MiscCommand+SetGetImageReadWrite);
        SetWriteMode(GetImageMode+ForeMoveWrite);
      {$ENDIF}

      {$IFDEF SPEA}
         {if PO>-1 then
            begin
              SPboxrest(PO, last_mx,MaxY-(last_my+15));
              SPboxfree(PO);
              PO:= -1;
            end;}
          SPcrcurs;
      {$ENDIF}

      nepust_mys_za_okraj;
      last_mx:= mouse_status.stat.x;
      last_my:= mouse_status.stat.y;

      {$IFDEF BGI}
        Move(m_cur[mouse_status.curs]^,PC^,m_size[mouse_status.curs]); { PI^->P^  }
        GetImage(last_mx,last_my,last_mx+15,last_my+15,PC^);           { P^ ->... }
        Move(PC^,PO^,m_size[mouse_status.curs]);                       { P^ ->PO^ }

        SetWriteMode(MiscCommand+2);
      {$ENDIF}

      {$IFDEF SPEA}
         {
         PO:= SPboxsave(last_mx,MaxY-(last_my+15),last_mx+15,MaxY-last_my,height,0);
         SetWriteMode(AndPut);
         SPboxrest(m_cur[mouse_status.curs], last_mx,MaxY-(last_my+15));
         SetWriteMode(NormalPut);
         }
         SPdrcurs(last_mx,MaxY-(last_my+15));
      {$ENDIF}

      m_visible:= true;
      m_shape
    end;


procedure m_put;
    var   x,y, height : int;
    begin
      if (is_mouse=0) or (not ({mys_kresli and} m_enabled and m_visible)) then Exit;

      x:= mouse_status.stat.x + Moff[mouse_status.curs].x;
      y:= mouse_status.stat.y + Moff[mouse_status.curs].y;

      if (x=last_mx) and (y=last_my) then Exit;

      {$IFDEF SPEA}
         {if PO>-1 then
            begin
              SPboxrest(PO, last_mx,MaxY-(last_my+15));
              SPboxfree(PO);
            end;}
          SPcrcurs;
      {$ENDIF}

      nepust_mys_za_okraj;
      x:= mouse_status.stat.x;
      y:= mouse_status.stat.y;

      {$IFDEF BGI}
        SetWriteMode(MiscCommand+SetGetImageReadWrite);
        SetWriteMode(GetImageMode+ForeMoveWrite);

        Move(m_cur[mouse_status.curs]^,PC^,m_size[mouse_status.curs]); { PI^->P^  }
        PutImage(last_mx,last_my,PO^,CopyPut); { PO^ ->... obnovi stary podklad  }
        GetImage(x,y,x+15,y+15,PC^);           { ... -> P^ precita podklad a polozi kurzor }
        Move(PC^,PO^,_CurSize);                { P^  -> PO^ }

        SetWriteMode(MiscCommand+2);
      {$ENDIF}

      {$IFDEF SPEA}
         {
         PO:= SPboxsave(x,MaxY-(y+15),x+15,MaxY-y,height,0);
         SetWriteMode(AndPut);
         SPboxrest(m_cur[mouse_status.curs], x,MaxY-(y+15));
         SetWriteMode(NormalPut);
         }
         SPdrcurs(x,MaxY-(y+15));
      {$ENDIF}

      last_mx:= x;
      last_my:= y;
      m_shape
    end;


{
 nastavenie noveho tvaru kurzora
}
procedure m_cursor(Cursor: TMCursor);
    var   reg: Registers;
          m  : bool;
          x,y: int;
    begin
      if    (is_mouse=0)
         or (mouse_status.curs = Cursor)
         or (not ({mys_kresli and} m_enabled and m_visible)) then Exit;
      m_hide;
      mouse_status.curs:= Cursor;
      {$IFDEF SPEA}
         spircurs(0,16,andmask,m_cur[Cursor],16,16,0,0,0,0,m_col[Cursor],0);
      {$ENDIF}
      m_show
    end;

