     { ---------------------------------------------- }
     { Graficky Objekt - zakladne graficke primitivum }
     { ---------------------------------------------- }

      type   TtypGRP  = byte;
             TparGP   = byte;
             TGPpocet = word;

      type   TGRPfill     = (_draw_,_fill_,_act_);
      const  GRPprty_act_ = +1; { offset priority _act_ivovaneho GRP }

             cl_GRP_act_   : byte = clGR8;  cfg_cl_GRP_act_ = 'GRP_ACT_';

      type   PTGrOb = ^TGrOb;         { vseobecne graficke primitivum }
             TGrOb  = object

               kod     : TtypGRP;     { kod       grafic. primitiva   }

                                      { parametre pre zobrazenie prim }
                                      { ----------------------------- }
               fill_en : bool;
               fill    : TGRPfill;    { 0-nie, 1-ano, 2-fill a oramuj }

               prior,                 { priorita  grafic. primitiva   }
               farba,                 { farba     grafic. primitiva   }
               typc    : TparGP;       { typ ciary grafic. primitiva   }
                                      { UPOZORNENIE : prior, farba, typc sa uz nevyuzivaju
                                        na tento ciel, zatial nemaju zvlastne pouzitie
                                      }

               GP      : PTGrOb;      { smernik na dalsie graf. prim  }


               constructor Init   (_kod : TtypGRP; var _InF : file; _farba,_typc: TparGP);
               constructor Define (_kod : TtypGRP; p: pointer; _farba,_typc: TparGP);
               destructor  Done; virtual;

               procedure   readGrOb   (var _InF : file); virtual;
               procedure   writeGrOb  (var _OuF : file; _header: bool); virtual;

               procedure   DefineGrOb (p: pointer); virtual;
               procedure   setGrObPar (_prior,_farba,_typc: int);
               procedure   setGP      (_GP: PTGrOb);

               function    is_in      (_zd, _zs : TZdZs): bool; virtual;
               function    patri      (_zd, _zs : TZdZs): bool;


               function    is_cut     (zdA,zsA,zdB,zsB: TZdZs;
                                       var in1,in2, is1,is2: bool;
                                       var zd1,zs1, zd2,zs2: TZdZs
                                      ): bool; virtual;
               function    priesecnik (zdA,zsA,zdB,zsB: TZdZs;
                                       var in1,in2, is1,is2: bool;
                                       var zd1,zs1, zd2,zs2: TZdZs
                                      ): bool;

               {$IFDEF DRAW}
                 procedure   set_fill (_fill: TGRPfill);

                 procedure   mapa_draw; virtual;
                 procedure   mapa_fill; virtual;
                 procedure   draw; virtual;
                 procedure   kresli;
               {$ENDIF}
             end;




     { ----------------------------------- }
     { jednotlive graficke primitiva       }
     { ----------------------------------- }

      type { '1' obycajny polygon  }
             PTPoly = ^TPoly;
             TPoly  = object(TGrOb)
               pocet      : TGPpocet;
               ZozBod     : PZozBod;
               Bmax, Bmin : TgBod; { doplnene koli regularite 9.5.95 }

               destructor  Done; virtual;

               procedure   readGrOb  (var _InF : file); virtual;
               procedure   writeGrOb (var _OuF : file; _header: bool); virtual;

               function    is_in  (_zd, _zs : TZdZs) : bool; virtual;
               function    is_cut (zdA,zsA,zdB,zsB: TZdZs;
                                   var in1,in2, is1,is2: bool;
                                   var zd1,zs1, zd2,zs2: TZdZs
                                  ): bool; virtual;

               {$IFDEF DRAW}
                 procedure   mapa_draw; virtual;
                 procedure   mapa_fill; virtual;
               {$ENDIF}
             end;


      type { uzivatelom definovany ... }
             PTTPoly = ^TTPoly;
             TTPoly  = object(TPoly)
               constructor Init(_Trat: POBxys; _pocet: int; _MapCl: byte);
             end;



           { '2' fillovany polygon }
      const  max_FillPoly = 1000;         { maximalny pocet bodov pre fillovany polygon }

      type   PTFillPoly = ^TFillPoly;
             TFillPoly  = object(TPoly)
               procedure   readGrOb(var _InF : file); virtual;
             end;


           { '3' kruhovy vysek }
      type   PTKrVys = ^TKrVys;
             TKrVys  = object(TGrOb)
               stred   : TgBod;        { stred }
               r       : long;        { polomer }
               a21,a22 : word;        { pociat. a konc. azimut }

               procedure   readGrOb(var _InF : file); virtual;

               function    is_in_ (x,y: real): bool; virtual;
               function    is_in  (_zd, _zs : TZdZs) : bool; virtual;
               function    is_cut (zdA,zsA,zdB,zsB: TZdZs;
                                   var in1,in2, is1,is2: bool;
                                   var zd1,zs1, zd2,zs2: TZdZs
                                  ): bool; virtual;

               {$IFDEF DRAW}
                 procedure   mapa_draw; virtual;
                 procedure   mapa_fill; virtual;
               {$ENDIF}
             end;


           { '4' fillovany kruhovy vysek }
      type   PTFillKrVys = ^TFillKrVys;
             TFillKrVys  = object(TKrVys)
               procedure   readGrOb(var _InF : file); virtual;
             end;


           { '5' kruznica }
      type   PUserKruz = ^TUserKruz;
             TUserKruz = record
               prior ,
               farba ,
               typc  : TparGP;
               X,Y   : real;
               R     : long
             end;


      type   PTKruz = ^TKruz;
             TKruz  = object(TGrOb)
               stred  : TgBod;        { stred }
               r      : long;        { polomer }

               procedure   readGrOb(var _InF : file); virtual;
               procedure   DefineGrOb(p: pointer); virtual;

               function    is_in  (_zd, _zs : TZdZs): bool; virtual;
               function    is_cut (zdA,zsA,zdB,zsB: TZdZs;
                                   var in1,in2, is1,is2: bool;
                                   var zd1,zs1, zd2,zs2: TZdZs
                                  ): bool; virtual;


               {$IFDEF DRAW}
                 procedure   mapa_draw; virtual;
                 procedure   mapa_fill; virtual;
               {$ENDIF}
             end;


           { '6' fillovana kruznica }
      type   PTFillKruz = ^TFillKruz;
             TFillKruz  = object(TKruz)
               procedure   readGrOb(var _InF : file); virtual;
             end;


           { '7' sustava kruznic }
      type   PTSusKruz = ^TSusKruz;
             TSusKruz  = object(TGrOb)
               stred  : TgBod;        { stred }
               delr   : long;        { prirastok polomeru }
               N      : word;        { pocet prirastkov }

               procedure   readGrOb(var _InF : file); virtual;

               {$IFDEF DRAW}
                 procedure   draw; virtual;
               {$ENDIF}
             end;


           { '8' sustava azimutov }
      type   PTSusAzim = ^TSusAzim;
             TSusAzim  = object(TGrOb)
               stred : TgBod;         { stred     }
               r     : long;         { polomer   }
               delA  : word;         { prirastok }

               procedure   readGrOb(var _InF : file); virtual;

               {$IFDEF DRAW}
                 procedure   draw; virtual;
               {$ENDIF}
             end;


           { '9' stvorcova siet }
      type   PTStSiet = ^TStSiet;
             TStSiet  = object(TGrOb)
               ldr     : TgBod;       { lavy dolny roh }
               delX,Nx,              { prirastok a pocet prirastkov v osi X }
               delY,Ny : word;       { prirastok a pocet prirastkov v osi Y }

               procedure   readGrOb(var _InF : file); virtual;

               {$IFDEF DRAW}
                 procedure   draw; virtual;
               {$ENDIF}
             end;


      type   PTMark10 = ^TMark10;
             TMark10  = object(TGrOb)
              {typm    : byte;}
               pocet   : TGPpocet;
               ZozText : PZozText;

               destructor  Done; virtual;
               procedure   readGrOb(var _InF : file); virtual;

               {$IFDEF DRAW}
                 procedure   _draw_(X,Y: long; P: pointer); virtual;
                 procedure   draw; virtual;
               {$ENDIF}
             end;


      type   PTMark11 = ^TMark11;
             TMark11  = object(TMark10)
             end;




      type   PTMark13 = ^TMark13;
             TMark13  = object(TMark10)
               procedure   readGrOb(var _InF : file); virtual;

               {$IFDEF DRAW}
                 procedure   _draw_(X,Y: long; P: pointer); virtual;
               {$ENDIF}
             end;



      procedure RW_Poly  (RW: byte; var f: File; var Zd,Zs: TZdZs);
      procedure RW_Mark13(RW: byte; var f: File; var Zd,Zs: TZdZs; var Ts: int; var veta : ch255);
