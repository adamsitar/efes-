           procedure   SaveMapOrSymbol(_Data : PMapData);
           procedure   FarbaMap(coho : int);

          { begin of EditMap.pas }
          { Vytvorenie novej mapy, CTR, TMA, ... }
           procedure   NewMapa(aky : int);
           procedure   NovaMapa;

           { Editacia mapy }
           procedure   EditujMapu(_por : int);
           function    MousePositionChanged : bool;
           procedure   PrepocetZS;
           procedure   Select_Point(_Key : Char);
           procedure   Writecross;
           procedure   Cross;
           Procedure   DrawInsVect;
           Function    Ins_point_to_tabs:bool;
           procedure   Delete_point;
           procedure   Zaciatok_ciary;
           procedure   Insert_point;
           procedure   Kruhovy_obluk;
           procedure   Vytvor_obmedz_lst;
           procedure   TypMapy(_MapSym : bool);
           procedure   Rozdelit_Ciaru;

          { end of EditMap.pas }

          { obsluha   }
           procedure   Idle(var _Event: TEvent); virtual;
