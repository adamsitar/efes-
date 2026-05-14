      type   TMapStat   = (map_,map_plan,map_act);

      const  st_MapStat = '';   { pre odlisenie nazvu nacitanej mapy a natvrdo zobrazenej (aktivovany) priestor }


     { ----------------------------------- }
     { Mapy                                }
     { ----------------------------------- }

      type   TMapNaz = string[sizeof(NameStr)];

           { popis mapy s grafickymi primitivami }
      type   PTMapOb = ^TMapOb;    { jedna polozka zoznamu map, definovana dalej }
             TMapOb  = record
               naz   : TMapNaz;    { nazov mapy. symbolov             }
               key   : pchar;      { kluc pre indentifikaciu mapy,
                                     ak jej nazov sa neda jednoznacne
                                     odovodit od premennej
                                   }
               plan  : bool;       { mapa zapnuta na zaklade spracovania udajov }

               typ   : word;       { typ mapy (letisko ,CTR,TMA, ...) }
                                   { spolocne parametre mapy          }

               prior : word;       { priorita pre modifikaciu         }
               ciar  : word;       { typ ciary, zatial pre cely subor podla Line style constants }
               cl    : word;       { farba pre vykreslenie            }

               kr_   : bool;       { mapa sa musi vykreslit           }
               kr    : bool;       { prepinac mapa/symbol, kreslit    }


               GP    : PTGrOb
             end;


      function    new_MapOb (naz: string; typ,prior,ciar,cl: word; zobraz,kr: bool): PTMapOb;
      procedure   dispose_MapOb (var MapOb: PTMapOb);

      procedure   mapy_pridaj_primitivum (var _MapOb: TMapOb; GP: PTGrOb; var _lastGrOb: PTGrOb);
      function    mapy_nacitaj_data      (subor: string; MapOb: PTMapOb): PTMapOb;
      function    mapy_nacitaj_subor     (subor: string; ZozMap: PZozMap; zobraz: bool): PTMapOb;

      function    mapy_najdi_a_nacitaj_data  (MapOb: PTMapOb): PTMapOb;
      function    mapy_najdi_a_nacitaj_subor (subor: string; ZozMap: PZozMap; zobraz: bool): PTMapOb;

      procedure   mapy_vytvor_subor (subor: string; tline,lprior,lcolor, fprior,fcolor, eprior,ecolor: word);
      procedure   mapy_vytvor_GP    (subor: string; kod: TtypGRP; prior,farba,typc: TparGP);

      procedure   mapy_zotried_mapy (ZozMap: PZozMap);
      procedure   mapy_set_fill (ZozMap: PZozMap; MapOb: PTMapOb; fill: TGRPfill; typ,prior: word);


      type   PMapy  = ^TMapy;
             TMapy   = object

               Mapy : PZozMap;

               constructor Init;
               constructor Init0;
               destructor  Done; virtual;

               private
               procedure   nacitaj_suradnice(var _InF: file; var _MapOb: TMapOb; var _lastGrOb: PTGrOb);
               procedure   zotried_mapy;

               public
               function    nacitaj_subor(subor: string): PTMapOb;
               function    najdi_a_nacitaj_subor(subor: string): PTMapOb;

               function    patri_zs(_Zd,_Zs: TZdZs): bool;
               function    patri_xy(x,y: real): bool;

               function    priesecnik_xy(Ax,Ay,Bx,By: real;
                                         var in1,in2, is1,is2: bool;
                                         var X1,Y1, X2,Y2: real
                                        ): bool;

               procedure   najblizsi_bod(xi,yi: real; var X,Y: real);

               {$IFDEF MAPY}
                 {procedure   kresli;}
               {$ENDIF}
             end;

