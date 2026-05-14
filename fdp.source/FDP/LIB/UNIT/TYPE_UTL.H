    type   tick_time      = long;
           tick_counter   = word;
           p_tick_counter = ^tick_counter;


    type   TNumber = (One, All);
           TbtStat = (btOFF,btON);

    type { objektove typy }
           PPoint = ^TPoint;
           TPoint = record
             x,y: int;
           end;

           PRegion = ^TRegion;
           TRegion = record
             x0,y0,x1,y1: int
           end;

