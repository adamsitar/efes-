(*-------------------------------------------------------------------*)
(* LETVIS FDP 4.0                                                    *)
(* (c) Ales Kosice 1993,96 (ab)                                      *)
(* Datove definicie                                                  *)
(*-------------------------------------------------------------------*)

{
  VYSTRAHA:  Pri upravach do buducnosti nie je bezpecne pracovat
  =========  so smernikami na data, ale s ich kopiami, alebo odkazom
             na ne - var -, pretoze pri ich viacnasobnom spracovani
             moze dojst ku ich odalokovaniu v jednej funckii, nahrade
             novymi a zaroven praci s nimi v dalsej...
             Preto je bezpecne "poridit si kopii dat" a byt opatrny
             pri praci s premennymi poiter, pchar i v samotnej datovej
             strukture...

             Pri kodovani dat sa robi MOVE ktory PREDPOKLADA, ze DLZKA
             buffera DB = sizeof(string)-1 ...  ......................

             Vyska civilneho stripu sa uklada v altS, premenna vys_ obsahuje
             priznak A,B -> pozor pri vypise...


  DOSLEDOK:  Procedury, v ktorych je cakacia slucka by si mali definovat
  =========  buffery. To sa tyka najma save_... a distribute_...
             Zatial je to zabezpecene necistym riesenim, pre kazdu fciu
             zvlast.


  Najprv poznamka na dalsi rozvoj
  -------------------------------
  PREROBIT NA OBJEKT FDP_DATA a zdedene plany, inak si vnasam vela chyb ...


  Konvencia v oznacovani:
  -----------------------
    iden : vyznamna polozka
    iden_: doplnkova polozka;

  Pri rozosielani sa posielaju data na vsetky stanice z users.cfg,
  ktore maju ich priznak uvedeny, okrem servera, ten dostava data
  len volanim prikazy send.

  Poznamky:
  ---------

    - funkcie pre dekodovanie paketu musia na zaciatku premennu vynulovat

    - Pred tym, ako zacnem plnit polozky planu, vynulovat ho. (off.h...)
      Pri vypocte trate cas pristatia: 00.00 ...?

    - Vypocty poloh su velmi komplikovane - anachronizmus.
      Zmenime to pri zjednocovani struktur mFPL a cFPL.

    - Pre EDD : ak by som chcel distribuovat plany z prop_win,
                treba upravit dekodovanie potvrdzovania...

    - Idealne by bolo prepracovat vsetky data do dedica jedneho objektu.
      Nemam domyslene, ako odovzdavat adresy typov objektov, preto su
      data reprezentovane proceduralne.

  Pri spracovani planov a ich naslednom rozoslani sa na server odosiela
  zvlast, ku podriadenym staniciam odosielaju funkciou distribute.

}

{$I comp.h}
{$I comp_fdp.h}

{ Pokec je dole }


unit _FPL_def;


interface

    uses    TypeDef,
            {$I unit_gr.h},
            {$I unit_net.h},
            keyb, DB, utime, dyn_zoz,
            Scroll, Lists,
            FIR_def, Bod_def, Body,
            _L4_def, _FDP_def,
            {$I unit_map.h}
            ;


    {$I _FPL_cn.h}          { konstanty      }
    {$I _FPL_cl.h}          { farby cielov   }
    {$I _FPL_sec.h}
    {$I _FPL_var.h}
    {$I _FPL_cfg.h}         {                }


    const {RDP_SECTOR_nd  : TRTRadr = 0;
           RDP_SECTOR_adr : TNETadr = '';
           accept_EDD = $FF;
          }
           sector_RDP   : TRTRadr = 0;
           sector_RDPnd : int = -1;



    {$I _FPL0drw.h}         { fcie }

    {$IFDEF FPL0}
     function  is_AREA_FPL0 (kod,bod_trate: string; var Ai: TpArea; var ires: int): bool;

     procedure decode_bod_trate(ptrat: pchar; pbod,pbodov: int;
                                bod_trate: string;

                                var Trat: TOBxys; var bodov: int;
                                var S,T,D: real;
                                var irych: single; var irych_: char;
                                var ivys : word; var ivys_ : char;
                                var lvys : word; var lvys_ : char; { posledne udaje o vyske }

                                vojensky_plan : bool;
                                err_exit : bool;    { ukonci pri chybe }

                                vynechaj_oat : bool;
                                var _OAT : bool;

                                var res: string
                               );

     function  _decode_FPL0_15

                         (_15 : pchar;

                           var start,prist: TAP;
                           var Trat: TOBxys; var bodov: int;

                           var rych : single; var rych_: char;
                           var vys  : word ; var vys_ : char;

                           date : TDate;

                           vojensky_plan  : bool;
                           vynechaj_oat   : bool;

                           err_exit       : bool;   { ukonci pri chybe                    }

                           uplna_trat     : bool;   { i so startom a pristatim            }
                           prist_prepocet : bool    { prepocet casu pristatia podla trate }
                         ): string;
    {$ENDIF}


    function  fl_dir_alt (vys_: char; vys: word): char;



implementation

uses  mem, str0, sets, math, mouse, mess, {$IFDEF PRN} prnt, {$ENDIF}
      DOS, IO, BIOS, COMs,
      Dialog,
      Vypocty, Archiv,
      FDP_msg,
      _MTK_2,
      FDP_func;


{$I _FPL0.drw}
{$IFDEF FPL0}
 {$I _FPL0.vyp}
{$ENDIF}

{
  najde oznacenie smeru letu podla priradenej hladiny
}
function fl_dir_alt(vys_: char; vys: word): char;
   var   vyss : string;
         i : int;
         m : long;
   begin
     m:= get_altM (vys_,vys);
     vyss:= _get_line(code_l4_vys(MtoS(m),altS),@fnAlt,[],1,lst_cely_riadok);
     if vyss='' then vyss:= _get_line(code_l4_vys(MtoFL(m),altFL),@fnAlt,[],1,lst_cely_riadok);
     vyss:= getstr(vyss,3,setKomen+[icao_NXIT]);
     if (vyss='') or (not (vyss[1] in [dir_cwest,dir_ceast])) then vyss:= ' ';
     fl_dir_alt:= vyss[1]
   end;

begin
 {$IFDEF MAPY}
   OBNOVENIE_CIELOV:= Limit(read_cfg_word(SYSTEMcfg,cfg_TARGET_REFRESH,OBNOVENIE_CIELOV), 5,60, 0);
 {$ENDIF}
end.