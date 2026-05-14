          { ------------------- }
          { velkost stripu      }
          { ------------------- }
    type    T_strip    = (mini_strip,short_strip,full_strip);
    const   miniSTRIP  : T_strip = {$IFDEF EDD} short_strip {$ELSE} full_strip {$ENDIF};
            lineSTRIP  : bool = false;


    {var     bminiSTRIP : bool;}
    const   ionSTRIP   : bool = {$IFDEF FPLC_ION} true {$ELSE} false {$ENDIF}; { zobrazenie I-O-N vysky }
            STRIP_MMI_menu : bool = {$IFDEF UKBB} false {$ELSE} false {$ENDIF};

          { ------------------- }
          { smer letu           }
          { ------------------- }
    const   dir_cwest   = '<';
            dir_ceast   = '>';
            poc_dir     = 8;

    type    Ts_dir      = (dir_no, dir_west,dir_east, dir_in,dir_inp,dir_out, dir_fpm,dir_fpo);
    
    const   cl_dir      : array[0..1,dir_west..dir_fpo] of byte =
                          {$IFDEF UKBB}
                           (
                            (55,63, clGRa,LightRed, 59, 51, 41),
                            (52,62, clGR7,     Red, 57, 48, 37)
                           );
                          {$ELSE}
                           (
                            (LightRed, clGRa, clGRd {35}, 55, 59, 51, 41),
                            (     Red, clGR8, clGRb {39}, 53, 57, 48, 37)
                           );
                          {$ENDIF}
            ch_dir      : array[dir_no..dir_fpo] of char =
                          (' ', dir_cwest,dir_ceast, '*', '+', '-', 'M','F');

    const   STRIP_DIR   : bool = true;
            STRIP_DIR_  : array[dir_west..dir_fpo] of bool =
                          (true, true, false,false,false, true,true);



          { ------------------- }
          { rozmery civ. stripu }
          { ------------------- }

    const   dx_mstrip = {$IFNDEF EDD_20} {222} 225 {$ELSE} 285 {$ENDIF};  { short strip }
            dx_sstrip = {$IFNDEF EDD_20} {306} 309 {$ELSE} 390 {$ENDIF};  { mini strip  }
            dx_fstrip = {$IFNDEF EDD_20} {470} 475 {$ELSE} 598 {$ENDIF};  { full strip  }

            dx_strip_ : array[low(T_strip)..high(T_strip)] of int =
                         (dx_mstrip,dx_sstrip,dx_fstrip);

            dy_strip2 = {$IFNDEF EDD_20} 35 {$ELSE} 42 {$ENDIF};
            dy_strip_ : array[false..true] of int =
                         (dy_strip2, {$IFNDEF EDD_20} 18 {$ELSE} 21 {$ENDIF});

            dx_header = {$IFNDEF EDD_20} 112 {$ELSE} 122 {$ENDIF};        { velkost pola stripu pre identifikaciu }



          { --------------------------------- }
          { pomocne premenne pre vypis stripu }
          { --------------------------------- }

    const
          {$IFDEF SPEA}
            dyh   = 16+dy_ed;
            dyt0  = 11+dy_ed; { 8x16 } { suradnice pre vypis casti Trat }
            dyt1  = 28+dy_ed; { 8x16 }
            dyt01 =  9+dy_ed; { 8x16 }
            dyt02 = 19+dy_ed; { 8x8  }
            dyt03 = 29+dy_ed; { 8x8  }

            dy0   = 12+dy_ed; { 8x16 v hornom riadku  }
            dy1   = 31+dy_ed; { 8x16 v spodnom riadku }  { bolo 31 }
            dy01  = 6 +dy_ed; { 8x8 v hornom riadku   }
            dy02  = 18+dy_ed; { 8x8 v strednom riadku }
            dy03  = 29+dy_ed; { 8x8 v spodnom riadku  }

            dy1l  = 2;
          {$ENDIF}

          {$IFDEF BGI}
           {$IFNDEF EDD_20}
             dyh   =  7;
             dyt0  =  9; { 8x16 } { suradnice pre vypis casti Trat }
             dyt1  = 18; { 8x16 }
             dyt01 =  5; { 8x8  }
             dyt02 = 14; { 8x8  }
             dyt03 = 24; { 8x8  }

             dy0   =  8; { 8x16 v hornom riadku  }
             dy1   = 24; { 8x16 v spodnom riadku }  { bolo 31 }
             dy01  =  4; { 8x8 v hornom riadku   }
             dy02  = 14; { 8x8 v strednom riadku }
             dy03  = 24; { 8x8 v spodnom riadku  }
           {$ELSE}
             dyh   = 16;
             dyt0  =  9; { 8x16 } { suradnice pre vypis casti Trat }
             dyt1  = 24; { 8x16 }
             dyt01 =  9; { 8x8  }
             dyt02 = 19; { 8x8  }
             dyt03 = 29; { 8x8  }

             dy0   =  8; { 8x16 v hornom riadku  }
             dy1   = 27; { 8x16 v spodnom riadku }  { bolo 31 }
             dy01  =  7; { 8x8 v hornom riadku   }
             dy02  = 17; { 8x8 v strednom riadku }
             dy03  = 29; { 8x8 v spodnom riadku  }
           {$ENDIF}

            dy1l  = 2;
          {$ENDIF}



    type  Tpocet_znakov = array[low(T_strip)..high(T_strip)] of byte;
          Ppocet_znakov = ^Tpocet_znakov;


    procedure strip_lines (x,y: int; pocet_znakov: Ppocet_znakov; p1,p2: pchar);
    procedure strip_pozn  (x,y: int; pocet_znakov: Ppocet_znakov; p: pchar);
    procedure strip_frame (_x,_y, _dx,_dy: int; c1,c2: byte);
    function  is_plani___ (p: pchar; m,r,k: int): bool;

    function  _is_mini_strip(m: T_strip): T_strip;
    function  dx_sc_strip(m: T_strip): int;
    function  dy_sc_strip: int;
