(*-------------------------------------------------------------------*)
(* LETVIS LIS - MAPY 2.0  Dynamicky obojsmerny zoznam,  aj Fill      *)
(* (c) Ales Kosice 1993,6 Igor, ab                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ [1] Objekt Mapa naplneni polozku menu "MAPYmenu" pre spracovanie map,
      ak bola externe inicializovana... v procedure nacitania map "read_maps"...
      Dalsie fcie doplni Mapa pri volani Init cez "MAPYfill".

  [2] Pri zobrazovani map pre Zamestnania/Priestory sa moze stat, ze jedna
      mapa je priradena viacejkrat. Vtedy su dve moznosti: bud ju viacejkrat
      zapnut a odlisit jej instancie klucom zhodnym s klucom planu, alebo
      zapinat jednu len inkrementovanim poctu.
      Najprv bol pouzity druhy variant. Setri pamat, alebo nie je bezpecny
      z hladiska prepinania stavu map a vypoctov nad nimi, preto je pouzita
      prva moznost.
}

{$X+,I-,S-,P-}


unit Mapy;


interface


    uses  TypeDef,
          keyb, dyn_zoz,
          graph_h, graph, SVGA,
          Events, Objects, Views, Button, Menus,
          FIR_def, _L4_def, ZemSur, Bod_def,
          MapyDef, GrPrim;



    {$IFDEF MAPY}

      {$I mdef_mnu.h}    { menu }
      {$I map_cnst.h}
      {$I map_def.h}     { TMapa, TCopyMapa, TNextMapa }
      {$I map_title.h}


      const  btMapydXY: TRegion = (x0:0;y0:0;x1:0;y1:0);   { oblast, kde sa moze pohybovat oknami }
             Mapa : PMapa = nil;

      procedure show_targets; far;
      procedure hide_targets; far;

      const     p_show_targets: TProc = show_targets;
                p_hide_targets: TProc = hide_targets;


      function  MAPYmenu_init(title: string): PSubmenu;

      procedure MAPY_init(_Owner     : PGroup;
                          _p_mapy_en : pointer;
                          _p_ciele   : pointer; { Tproc_b  }
                          _p_handle  : pointer; { Tproc_vE }
                          _p_cursor  : pointer  { Tproc    }
                         );


      procedure zobraz_trat(tit: string; _OBs: POBxys; _bodov : int; dx,dy: int; cl: byte);


      procedure formular_Rozsah;
      procedure formular_Priestor;


      function _handle_event_MAPY (var _Event: TEvent; O: PObject; FPL: pointer): bool;

    {$ENDIF}




implementation

uses  DOS, IO, BIOS, _Check,
      keyb_int, str0, mouse, sets, math, mess,
      BGIgraph, BGItext,
      CMs, CM, Dialog, help_def, Help, Edit, Lists, App,
      Msg, FDP_Msg,
      {$IFDEF LIS} Okna, Formular, {$ENDIF}
      ParStr, _FDP_def;



{$IFDEF MAPY}

  const adrMapaPoint : PMapa = nil;

  procedure _BodXY_(Bod: PGBod; var X,Y: long);
      begin
        if adrMapaPoint<>nil then with adrMapaPoint^ do
           begin
             Point(Bod^.X,Bod^.Y);
             X:= Txx;
             Y:= Tyy
           end
      end;


  type TMapNames  = array[0..MAX_ARRAY_SIZE div SizeOf(TMapNaz)] of TMapNaz;
       PTMapNames = ^TMapNames;

  function read_map_names_cfg (fn : string; var names: PTMapNames; var poc: int): bool; forward;


  {$I mapy_0.inc}     { Init, Done, View... }
  {$I mapy_cfg.inc}   { cfg ... }
  {$I mapy_1.inc}     { menu }
  {$I mapy_4.inc}     { vypocty }
  {$I mapy_5.inc}     { draw }
  {$I mapy_7.inc}     { handle }
  {$I mapy_8.inc}     { aktualizacia symbolov, podla text suborov }
  {$I mapy_9.inc}     { zapinanie priestorov       }
  {$I mapy_10.inc}    { MAPY_init                  }


  {$I mapy_21.inc}    { Objekt TCopyMapa           }
  {$I mapy_22.inc}    {        TNextMapa           }

  {$I mapy.frm}

  {$I mapy_handle.inc}


begin
 write('Initializing maps... ');

 PRTY0:= read_cfg_bool(MAPscfg, cfg_PRTY0, PRTY0);
 MARKED_SYM:= read_cfg_bool(MAPscfg, cfg_MARKED_SYM, MARKED_SYM);

 BodXY:= _BodXY_;

 MAP_update;
 SYM_update;

 writeln('Done.')
{$ENDIF}
end.