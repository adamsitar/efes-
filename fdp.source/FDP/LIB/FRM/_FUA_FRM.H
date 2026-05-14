{$IFDEF PROCESS_FUA}

 { Poznamky :

   - Format by bol elegantny, ak by hlavicka bola rozdelena
     na polozky a polia A - F ako jedno spolocne alebo oddelene
     polia poloziek. Aby som nemusel upravovat objekty typu Edit,
     zatial je to vsetko v editore.


   - Editor pre spravu AUP/UUP obsahuje tlacidla Posli a Uloz,
     pricom Uloz je aktivovane len vtedz ak sprava nebola este
     odoslana (src=null).

   - Rozsah editovaneho pola vychadza z predpokladu, ze sprava
     ma byt odosielana prostrednictvom AFTN,
     ale umoznuje neohraniceny rozsah spravy a teda
     jej cislo je stale 001

   - kontroluje sa spravnost vyplnenia poli podla
      - datumu uvedeneho v hlavicke zodpoveda dnu vydania spravy
        (AUP D-1, UUP D)
      - predpisu

   - datum platnosti spravy je urceny v jej hlavicke

   - odoslanie spravy je indikovane existenciou pola rec,
     pre AFTN plati ... co ?

 }

 const  strana_AUPed  = 40;
        riadkov_AUPed = MTK_2_PAGE;
        znakov_AUPed  = MTK_2_LINE;


 type   PAUPed = ^TAUPed;
        TAUPed = object(TTxtFileEditor)

          typ  : TNETtyp;
          head : string [kod_HEAD];
          path : string [80];


          constructor Init(var _x,_y, _mode: int;

                           _title  : string;
                           _viewer : bool;

                           _fn,_tmp,_ini : string;

                           _typ  : TNETtyp;
                           _head : string;
                           _path : string;

                           _hlpXXX : Pchar
                          );

          procedure   initialize_buttons; virtual;
          procedure   handle_buttons (var _Event: TEvent); virtual;

          function    check_file (check_all: bool; var fnn: string; {var val: TDate;} var adr: string): bool;

          {function    _call_check_func: bool; virtual;}
          {procedure   make_message; virtual;}

          {function    is_to_send: bool; virtual;
          function    is_to_save: bool; virtual;}

          {function    validity(var d: TDate): bool; virtual;
          function    regularity: bool; virtual;}
        end;


 type   PUUPed = ^TUUPed;
        TUUPed = object(TAUPed)
          {function    validity(var d: TDate): bool; virtual;}
        end;


{$ENDIF}