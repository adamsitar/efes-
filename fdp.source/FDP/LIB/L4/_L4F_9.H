     const  tit_9b_HEADER = '#HEADER#';

            tit_9b_CODE   = 'CODE';
            tit_9b_ICAO   = 'ICAO';
            tit_9b_WTC    = 'WTC';
            tit_9b_CAT    = 'CAT';
            tit_9b_ICNR   = 'ICNR';
            tit_9b_NR     = 'NR';
            tit_9b_SPEED  = 'SPEED';
            tit_9b_FL     = 'FL';
            tit_9b_NAME   = 'AIRCRAFT';
            tit_9b_RMK    = 'RMK';


     type   PList_9b_icao = ^TList_9b_icao;
            TList_9b_icao = object(TList)
              p_code,p_icao,p_wtc,p_cat,p_speed,p_fl,p_name,p_rmk: int;

              constructor Init(_lst: PListDesc; _fn: string; _init: bool);

              function  read_header (line,prev: string): bool; virtual;
              function  data_write  (i: int): string; virtual;

              function  find (_type: string; var line: string; var ind: int): int;

              function  _data_item (s: string; zac,kon: int): string;

              function  _code  (s: string): string; virtual;
              function  _icao  (s: string): string; virtual;
              function  _wtc   (s: string): string; virtual;
              function  _cat   (s: string): string; virtual;
              function  _speed_(s: string): string;
              function  _speed (s: string;
                                var rych: single; var rych_: char;
                                var minkmh,maxkmh: single
                               ): string; virtual;
              function  _fl_   (s: string): string;
              function  _fl    (s: string;
                                var vys: word; var vys_: char;
                                var minS,maxS: word
                               ): string; virtual;
              function  _name  (s: string): string; virtual;
              function  _rmk   (s: string): string; virtual;

             {$IFDEF DEBUG}
              procedure item_test (s: string); virtual;
             {$ENDIF}
            end;


            PList_9b_ine = ^TList_9b_ine;
            TList_9b_ine = object(TList_9b_icao)
              function  data_write (i: int): string; virtual;
            end;

            PList_9b_mil = ^TList_9b_mil;
            TList_9b_mil = object(TList_9b_ine)
              function  _mil (s: string): bool;
            end;


     const  lst_9bICAO : PList_9b_icao = nil;
            lst_9bZZZZ : PList_9b_ine  = nil;   { prevodna tabulka kvoli chybam }
            lst_9bTSGA : PList_9b_ine  = nil;
            lst_9bMIL  : PList_9b_mil  = nil;


     function  _code_9abc_by8643  (var _9: string; _9a,_9b,_9c: string; _lst: PList_9b_icao; _zzzz: bool): string;
     function  _code_9MIL_by8643  (var _9: string): string;
     function  _code_9TSGA_by8643 (var _9: string): string;

     function  _code_9_by8643_    (var _9: string; _afil_9: bool; var err9b,err9c: bool): string;
     function  _code_9_by8643     (var _9: string; _zzzz: bool): string;
     function  _check_9_by8643    (var _9: string; var res: string; _ever,_zzzz: bool): int;

     function  _9b_data  (var _9: string; is_icao: bool): string;
     function  _9c_data  (_9b: string): string;

     function  _9b_rychvys   (_9: string; is_icao: bool;
                              var rych: single; var rych_: char; var minkmh,maxkmh: single;
                              var vys: word; var vys_: char; var minS,maxS: word
                             ): bool;

     function  _rychvys_rozsah
                     (rmkh: single; vS: word;
                      minr,maxr: single;
                      minv,maxv: word;
                      var res  : string;
                      var ires : int
                     ): bool;

     function  _9_rychvys_rozsah
                     (_9 : string;
                      rmkh: single; vS: word;
                      var res  : string;
                      var ires : int
                     ): bool;

     function  _9b_rychvys_fl
                    (var typ: string;
                     trat, b0,bl: string;
                     var ry: single; var ry_: char;
                     var v: word; var v_: char
                    ): bool;


     function  _15ab_to_9 (_9,_15ab: string): string;
