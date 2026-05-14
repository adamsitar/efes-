    type  PMapData = PTMapOb;
          TMapData = TMapOb;


        { ------------------------------------- }
        { TMapa                                 }
        { ------------------------------------- }

    type  PMapa = ^TMapa;
          TMapa = object(TView)

           { Zoznam map, symbolov, ... _____________________________________ }

             zMapy     : PZozMap;  { Mapy a symboly                          }

             zTrate    : PZozMap;  { Trate aktivnych letov                   }
             zTrat     : PZozMap;  { Trate pre vykreslenie v prehlade        }


           { Zobrazenie cielov ... _________________________________________ }

             p_mapy_en : pointer;
             p_ciele   : pointer;  { TProc_b - zobrazenie ciela              }
             p_handle  : pointer;  { TProc_vE - akcia pri kliknuti           }
             p_cursor  : pointer;  { Tproc - zmena kurzora nad ...           }
             p_mapy    : pointer;  { bool^ - je dovovolene vykreslenie map ? }

           { Parametre pohladu na mapu ... _________________________________ }

             Rozsah, Xvystred,Yvystred   : real;

             Txx,Tyy                     : long;
             dTyy, dK1,dK2               : int;
             Ys1,Ys2, Xs1,Xs2, Kon1,Kon2 : real;
             dcXvystred,dcYvystred       : real;

             {$IFDEF LIS}
               xc,yc     : int;     { suradnice pre cross          }
               Zac, InsP : bool;    { prem. pre zac.ciary a insert }
             {$ENDIF}

             map_init    : bool;



           { inicializacne ---------------- }
             constructor Init(_Owner : PGroup;

                              _p_mapy_en : pointer;
                              _p_ciele   : pointer; { Tproc_b  }
                              _p_handle  : pointer; { Tproc_vE }
                              _p_cursor  : pointer  { Tproc }
                             );

             private
             procedure   done_maps(var _ZozMap: PZozMap);
             public
             destructor  Done; virtual;


           { View ------------------------- }
             function    inView(x,y: int): bool; virtual;
             procedure   m_shape; virtual;
             procedure   ActiveOn;  virtual;
             procedure   ActiveOff; virtual;
             procedure   reinit_(_mode: TGraphMode); virtual;


           { nacitanie -------------------- }
             public

             procedure   save_cfg_fn (fn: string);
             procedure   read_cfg_fn (fn: string);

             procedure   save_user_cfg (fn: string);
             function    load_user_cfg (fn: string): bool;


           { vypocty ---------------------- }
             private
             procedure   Centr;
             procedure   Stred(XXstr,YYstr: real);

             public
             procedure   Point(X1z,Y1z: real);
             procedure   InvPoint (var X1z,Y1z: real);
             procedure   InvPoint_(_Txx,_Tyy: real; var X1z,Y1z: real);


           { kreslenie mapy --------------- }
             private
            {$IFDEF MAPY_1.0}
             procedure   mapa_draw(_Data : PMapData);
             procedure   mapa_fill(_Data : PMapData);
            {$ENDIF}

             public
             procedure   Mapa     (_Data : PMapData);
             procedure   Symbol   (_Data : PMapData);

             private
             procedure   kresli_mapy(_ZozMap : PZozMap);
             public
             procedure   uvolni_data (PData: PMapData);
             procedure   nacitaj_data(PData: PMapData);
             procedure   pracuj_s_pamatou;

             procedure   kresli(_map_init: bool);
             procedure   Draw; virtual;


           { obsluha   }
             procedure   GetEvent(var _Event: TEvent); virtual;
             private
             procedure   nastav_rozsah(key: char);
             public
             procedure   handle_target(var _Event: TEvent); virtual;
             procedure   HandleEvent  (var _Event: TEvent); virtual;


           { nastavenie parametrov -------- }
             procedure   Centruj;
             procedure   Vystred;


           { pridanie/zrusenie mapy trate - }
             function    zapni_trat (_ZozMap: PZozMap;
                                     _Trat: POBxys; _bodov: int; _MapNaz: string;
                                     _MapCl: byte
                                    ): PMapData;
             procedure   vypni_trat (_ZozMap: PZozMap; _Map: PMapData);


             function    zapni_mapu (N: string;
                                     p_GrOb,v_GrOb: pointer;
                                     key: string; typ: word; mapf: TGRPfill;
                                     PIS: bool
                                    ): PMapData;
             function    vypni_mapu (N,key: string; PIS: bool): bool;

            {$IFDEF LIS}
             {$I ed_map.h}
            {$ENDIF}
          end;


        { ------------------------------------- }
        { TCopyMapa                             }
        { ------------------------------------- }
    type  PCopyMapa = ^TCopyMapa;
          TCopyMapa = object(TMapa)
             OMapa : PMapa;
             cfg   : string[12];

             constructor Init(_Owner: PGroup; x,y,dx,dy: int; _OMapa: PMapa; _cfg: string);
             destructor  Done; virtual;
             procedure   reinit_(_mode: TGraphMode); virtual;  { prepnutie do ineho modu }

             procedure   handle_target(var _Event: TEvent); virtual;
          end;



        { ------------------------------------- }
        { TNextMapa                             }
        { ------------------------------------- }
    type  PNextMapa = ^TNextMapa;
          TNextMapa = object(TWindow)
             CM: PCopyMapa;

             constructor Init(_Owner: PGroup;
                              x,y, dx,dy: int; _title: string;
                              _OMapa: PMapa; _cfg: string
                             );
             procedure   Image; virtual;
          end;
