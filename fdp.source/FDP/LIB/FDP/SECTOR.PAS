{ -------------------------------------------------------------------
  ROZDELENIE SPRAV do sektorov

  (c) Ales Kosice 95, to nie je mozne, take stare (99) ?
  (ab)
  -------------------------------------------------------------------


  Pokec ku 95:
  -------------
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  - zatial sa vstupom do sektora uvazuje prvy znamy bod v sektore,
    treba doriesit vypocet casu a miesta prieniku do/zo sektora;
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  - druhezatial hovori, ze to je to zmastene napoly vseobecne
    a dozvyskuirici pouziva vypocet sektorizacie z kontrektneho
    planu

  - vypocet platnosti v sektore moze mat dve urovne :
    a) narusa riadeny sektor(y) ... prvy a posledny bod
    b) narusa viackrat alebo sa vracia ... potrebna dynamicke urcovanie platnosti


  - ak su data spracovavane i podla sektorizacie,
    musia mat priznak zaradenia do vypisu a tlace
  - modul je urceny pre spracvnaie dat vo svojom sektore

  - problem BORAT (len dotknutia sa rohu sektora som vyriesiel zatial posunitim ZSboratu)

  - nedoriesny problem pretnutia rohu sektora ... po vzdialenost S_IN_KM


  Pokec ku 99:
  -------------
  - nacitanie suradnic riadenych oblasti (letisk), ak sa v subore
    s jeho suradnicami nachadza nazov mapy "SEC"
    a vyskove rozmedzie "ALT"

}

{$I comp.h}


unit Sector;


interface


    uses   TypeDef,
           IO, NET_def, FIR_def,
           {$I unit_map.h},
           Bod_def, Body;


    type   mask_SECTORs = word;


    const  PathToSEC : string[40] = PathToMAPs+'SECTORS\';

           SECcfg       = 'sector'+ext_ini;

           cfg_SECTORs  = 'SECTORS';
           cfg_SECTOR   = 'SECTOR';
           cfg_SEC      = 'SEC';
           cfg_ALT      = 'ALT';

           ps_NALTSEC   = 'NALTSEC';
           check_ALTSEC : bool = true;

           max_SECTORs  = 8*sizeof(mask_SECTORs);
           SECTORm      : mask_SECTORs = 0;


    type   TsectorOB = record
             nazov  : string[8];
             mapa   : PMapy;
             v0,v1  : word;   { v [S] }
           end;
           PsectorOB = ^TsectorOB;


          {$IFDEF FDR}
    const  FIRmap : PMapy = nil;
          {$ENDIF}

    function _cez_sektor(mapa: PMapy; nazov: string; v0s,v1s: word;
                         x0,y0 : real; v0: word; v0_: char;
                         x1,y1 : real; v1: word; v1_: char;
                         var x,y : real;
                         var err: bool
                        ): bool;


    function _trat_cez_sektor
                        (mapa: PMapy; nazov: string; v0s,v1s: word;
                         trat: pointer; bodov: int;
                         p_xyvys: P_suradnice_a_vyska_trate;
                         var err: bool
                        ): bool;


    function _trat_mimo_hranice_sektora
                        (mapa: PMapy; nazov: string;
                         trat: pointer; bodov: int;
                         p_xyvys: P_suradnice_a_vyska_trate;
                         var err: bool
                        ): bool;


    function _trat_cez_priestor
                        (nazov: string; c0,c1: real; v0s,v1s: word;
                         trat: pointer; bodov: int;
                         p_casxyvys: P_cas_suradnice_a_vyska_trate;
                         sprava: bool; var err: bool
                        ): bool;


    {$I sectors.h}



implementation

 uses  BIOS, str0, msg, mess, math, parstr,
       Objects, Dialog, App, CM,
       FDP_msg,
       _L4_def, _MTK_2, Vypocty;


 {$I sector.vyp}
 {$I sector.inc}
 {$I sectors.inc}

 var  SaveExit : pointer;

 procedure done_SECTOR;
     begin
       ExitProc:= SaveExit;
       odalokovanie_oblasti_riadenia;
       {$IFDEF SECTORS}
         odalokovanie_sektorov_riadenia;
       {$ENDIF}
       {$IFDEF FDR}
        if FIRmap<>nil then Dispose(FIRmap,Done);
       {$ENDIF}
     end;

 procedure init_SECTOR;
     var   s: string;
           nl: bool;
     begin
       nl:= false;
       write('Initializing sectors... ');
       SaveExit:= ExitProc;
       ExitProc:= @done_SECTOR;

      { nacitanie mapy FIR kvoli testovaniu FPL4
      }
       {$IFDEF FDR}
        FIRmap:= New(PMapy,Init);
        if FIRmap^.najdi_a_nacitaj_subor(PathToSEC+FIR_adr)=nil then
           begin
             s:= l4str(read_cfg_str_(SYSTEMcfg,cfg_SECTORs,PathToSEC));
             if s[length(s)]<>'\' then s:= s+'\';
             if FIRmap^.najdi_a_nacitaj_subor(s+FIR_adr)<>nil then PathToSEC:= s
             else begin
                    s:= PathToMAPs;
                    if FIRmap^.najdi_a_nacitaj_subor(s+FIR_adr)<>nil then PathToSEC:= s
                    else begin
                           {l4_err(a_15c,FIR_adr,i_15c,err_15c_firmap_notfound,s);}
                           MessError('Map of controlled area ('+FIR_adr+') has been not found.',true,nl);
                           Dispose(FIRmap,Done);
                           FIRmap:= nil
                         end
                  end;
           end;
       {$ENDIF}

      { nacitanie sektorov
      }
       {$IFDEF SECTORS}
        PathToSEC:= uni_str(read_cfg_str_(SECcfg, cfg_SECTORs, PathToSEC));
        if PathToSEC[length(PathToSEC)]<>'\' then PathToSEC:= PathToSEC+'\';
        check_ALTSEC:= is_ParamStr(ps_NALTSEC)='';
        nacitanie_sektorov_riadenia;
       {$ENDIF}

       nacitanie_oblasti_riadenia;
       if nl then writeln;
       writeln('Done.')
     end;


begin
 init_SECTOR;
end.