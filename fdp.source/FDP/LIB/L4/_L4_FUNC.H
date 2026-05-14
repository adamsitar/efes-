    type  Tcode_l4_data   = function (item: pointer; cislo: string): pchar;
          Pcode_l4_data   = ^Tcode_l4_data;

          Tdecode_l4_data = function (data: pchars; size: TNETdlz; var data): string;
          Pdecode_l4_data = ^Tdecode_l4_data;


    function   decode_code_to_hd (kod: TNETtyp): Thead_ICAO;
    function   code_hd_to_code   (hd: Thead_ICAO): TNETtyp;

    function   frame_l4_pkt(var data: pchars; var size: TNETdlz; var res: string): bool; { Posunie hranice ! }
    function   init_pole_to_print (var s: array of string; max,poc: int; pole: pchar; _end: bool): int;


    type  Tkey_fpl = record
            _7a  : string[kod_7a];
            _13a : string[kod_SP];
            _D   : TDate
          end;

          Pkey_fpl = ^Tkey_fpl;


    const   pos_key_7a   = 1;
            pos_key_13a  = 2;
            pos_key_DATE = 3;

    function   codekey_fpl   (_7a,_13a: string; _D: TDate): string;
    procedure  decodekey_fpl (s: string; var _7a,_13a: string; var _D: TDate);
