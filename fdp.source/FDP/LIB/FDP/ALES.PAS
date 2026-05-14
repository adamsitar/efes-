(*-------------------------------------------------------------------*)
(* ALES                                                              *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit ALES;

interface


     uses   TypeDef;


     {$I ales.h}

     procedure ALES_LOGO(x,y: int);
     procedure LOGO;



implementation


uses  Crt,
      mouse, str0, sets,
      {$I unit_gr.h}, {$IFDEF SPEA} SPEA, {$ENDIF}
      Body, _NET, FDP_func;


procedure ALES_LOGO(x,y: int);
   type   PolygonType = array[1..4] of PointType;
   const  T1: PolygonType = ((x:  0; y:-10), (x:-70; y:-20), (x:-20; y:-35), (x:  0; y:-10));
          T2: PolygonType = ((x:-50; y:  0), (x: 64; y:  0), (x:-11; y:-20), (x:-50; y:  0));
          T3: PolygonType = ((x: -5; y: -6), (x: 30; y: 30), (x: 10; y:-25), (x: -5; y: -6));
   var    i: int;
   begin
     for i:= 1 to 4 do
         begin
           inc(T1[i].x,x); inc(T1[i].y,y);
           inc(T2[i].x,x); inc(T2[i].y,y);
           inc(T3[i].x,x); inc(T3[i].y,y);
         end;
     setcolor(red);
     SetFillStyle(SolidFill, Red);
     {$IFDEF BGI}
       PieSlice(x,y, 0, 180, 50);
     {$ELSE}
       SPbcolor(Red);
       SParc(0, x,MaxY-y, x-50,MaxY-y, x+50,MaxY-y);
     {$ENDIF}
     setcolor(lightblue);
     SetFillStyle(SolidFill, white);
     FillPoly(4, T1);
     FillPoly(4, T2);
     FillPoly(4, T3);
   end;


{$IFDEF BGI}

  procedure LOGO;
      var   F256: Tpaleta;
            i   : int;
            s   : string;
            GM  : TGraphMode;
      begin
        s:= 'ALESKE/ATC          ';

       {$IFDEF FDP_OPL}
         {$IFDEF AIRBASE}
           titKDE:= 'LSRLP '+airbase;
         {$ENDIF}
         {$IFDEF MACC}
            titKDE:= 'MACC';
         {$ENDIF}
         {$IFDEF SAR}
            titKDE:= 'SAR';
         {$ENDIF}
         {$IFDEF SERVER}
           titKDE:= 'server';
         {$ENDIF}
         {$IFDEF BRIDGE}
           titKDE:= 'bridge';
         {$ENDIF}
         {$IFDEF PVO}
           titKDE:= 'PVO';
         {$ENDIF}
       {$ENDIF}

        GM:= GraphMode; set_GrMode(_VGA); GraphMode:= GM;
       {$IFDEF EGAVGA}
        FillWin(120,138,520,397,blue);
       {$ELSE}
        for i:= 0  to  211 do set_RGBcolor(F256[i+32],0, 0, 30+i);
        set_RGBcolor(F256[243], 0, (65-48)*12, (65-48)*12+50);
        set_RGBcolors(F256, 32,213);
        FillWin(120,138,520,162,32);
        for i:= 32 to 235 do FillWin(120,130+i,520,130+i+1,i); {FillWin(140,120+242,500,120+242+20,i);}
       {$ENDIF}

        ALES_LOGO(420,328);
                                                               { 190 }

        SetTextStyle(7,HorizDir, 4);
        if length(titFDP)>16 then SetTextStyle(7,HorizDir, 3);

        SetTextJustify(CenterText, CenterText);
        SetColor(0);   OutTextXY(321,176,titFDP);              { 157 }
        SetColor(243); OutTextXY(319,174,titFDP);              { 153 }

        SetTextStyle(7,HorizDir, 3);
       {$IFDEF FDP_OPL}
        s:= titKDE+',  '+titVER;
        SetColor(0);   OutTextXY(321,233,s);   {OutTextXY(253,225,VER);}
        SetColor(243); OutTextXY(319,231,s);   {OutTextXY(250,223,VER);}
       {$ENDIF}
       {$IFDEF FDP_EDD}
        SetColor(0);   OutTextXY(321,233,{titSPC+}titFOR);
        SetColor(243); OutTextXY(319,231,{titSPC+}titFOR);
       {$ENDIF}
        SetTextJustify(LeftText, TopText);
        SetTextStyle(DefaultFont, HorizDir, 1);
        SetColor(black);
        OutTextXY(187,347,titCR);
        {Circle(270,351,5);}
        SetColor(white);
        OutTextXY(185,346,titCR)
        {Circle(268,350,5);}
       { IFNDEF IPX
           Delay(2000)
          ENDIF}
      end;

{$ENDIF}


{$IFDEF SPEA}

  procedure LOGO;
      var   F256: Tpaleta;
            GM  : TGraphMode;
            i   : int;
            s   : string;
      begin
        s:= 'ALESKE/ATC          ';

        (*
        for i:= 0  to  211 do set_RGBcolor(F256[i+32],0, 0, 30+i);
        set_RGBcolor(F256[243], 0, (65-48)*12, (65-48)*12+50);
        set_RGBcolors(F256, 32,213);

        m_cl;
        FillWin(340,138,800,162,32);
        for i:= 32 to 235 do FillWin(340,130+i,800,130+i+1,i); {FillWin(140,120+242,500,120+242+20,i);}

        ALES_LOGO(720,328);

        SetTextStyle(SYS16x32 ,HorizDir, 1);
        SetColor(0);   OutTextXY(157,176,titFDP);               { 240 }
        SetColor(243); OutTextXY(153,173,titFDP);               { 240 }
        SetTextStyle(7,HorizDir, 3);
        SetTextJustify(CenterText, CenterText);
        {$IFDEF AIRBASE}
          SetColor(0);   OutTextXY(321,233,titKDE+' '+titVER);             {OutTextXY(253,225,VER);}
          SetColor(243); OutTextXY(319,231,titKDE+' '+titVER);             {OutTextXY(250,223,VER);}
        {$ENDIF}
        {$IFDEF MACC}
          SetColor(0);   OutTextXY(321,233,titKDE+' '+titVER);
          SetColor(243); OutTextXY(319,231,titKDE+' '+titVER);
        {$ENDIF}
        {$IFDEF SERVER}
          SetColor(0);   OutTextXY(321,233,titKDE+' '+titVER);
          SetColor(243); OutTextXY(319,231,titKDE+' '+titVER);
        {$ENDIF}
        {$IFDEF BRIDGE}
          SetColor(0);   OutTextXY(321,233,titKDE+' '+titVER);
          SetColor(243); OutTextXY(319,231,titKDE+' '+titVER);
        {$ENDIF}                                             { 288 }
        {X25address}
        SetTextJustify(LeftText, TopText);
        SetTextStyle(DefaultFont, HorizDir, 1);
        SetColor(black);
        OutTextXY(187,347,titCR);
        Circle(270,351,5);
        SetColor(white);
        OutTextXY(185,346,titCR);
        Circle(268,350,5);
        SetTextStyle(STDxFNT,1,1);
        m_st
        *)
      end;

{$ENDIF}

end.