   {$IFDEF SECTORS}

     type   PSECTOR = ^TSECTOR;
            TSECTOR = record
              meno         : pchar;

              nazov        : string[NAME]; { nazov mapy sektora, neskor mozno suradnice, z ktorych sa mapa vygeneruje }
              mapa         : PMapy;

              vys_0,
              vys_1        : word;         { vyska v [S]     }

              is           : bool;         { je zapnuty ?    }
              sec          : byte;         { parametere      }

             {$IFDEF EDD}
              tablet       : string[NAME]
             {$ENDIF}
            end;

            TSECTORs = array[0..max_SECTORs-1] of PSECTOR;
            PSECTORs = ^TSECTORs;


     const  SECTORs    : PSECTORs = nil;
            nSEC       : byte = 0;

            (*SECTOR_EN : bool = {$IFDEF EDD} false {$ELSE} true {$ENDIF};*)
            S_UPDATE   : real = 0;   { cas zmeny rozdelenia sektorov,
                                       sposobi opatovny prepocet
                                       platnosti na sektore
                                     }


     type       Tproc_sector_chg = procedure (nS: mask_SECTORs; _draw: bool);
     procedure  sector_chg (nS: mask_sectors; _draw: bool); far;
     const      proc_sector_chg : Tproc_sector_chg = sector_chg;


     type  { Funkcia pre zistenie polohy na trati v definovanom case

             a) Funkcia ma vratit true, ak urcila polohu bodu,
                a false, ak na trati sa nachadza neznamy bod,
                s vynimkou letiska startu/pristatia.
             b) ak v case T sa nenachadza na trati, vrati x=0,y=0
           }

            TFunc_Txy = function (plan: pointer; T: real; var X,Y: real): bool;


     function  cez_sektor     ( x0,y0 : real; v0: word; v0_: char;
                                x1,y1 : real; v1: word; v1_: char;
                                var x,y: real
                              ): bool;

     function  v_sektore      (x0,y0 : real; vys0: word; vys0_: char;
                               x1,y1 : real; vys1: word; vys1_: char
                              ): bool;

     {function  let_v_sektore  (plan: pointer; func: TFunc_Txy; T0,T1: real): bool;}
     function  let_cez_sektor (trat: pointer; bodov: int;
                               trat_x,trat_y: PRFunc_p; vys_S: PWFunc_p
                              ): bool;

     function  vyska_v_sektore (x,y: real; v: word; v_: char; xi,yi: real): bool;

   {$ENDIF}
