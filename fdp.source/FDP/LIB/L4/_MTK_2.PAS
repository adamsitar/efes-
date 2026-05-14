{ -------------------------------------------------
  MTK-2 interface pre LETVIS/FDP
  pre spracovanie sprav ICAO
  (zo siete AFTN)
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
 תתתתתתתתתתתתתתת
  (c) ALES 1996,
 תתתתתתתתתתתתתתת

}

{$I comp.h}

unit _MTK_2;


interface


     uses  TypeDef,
           IO,
           Kody{ ,NET_def};


     {$I _MTK_2_.h}
     {$I _MTK_2_priorita.h}        { Priorita }

     {$I _ITA2_definitions.h}      { ITA2 - riadiace znaky }
     {$I _IA5_definitions.h}       { IT5  - riadiace znaky }

     {$I _MTK_2_words_control.h}   { Zakazene slova v telegrame a kody }
     {$I _MTK_2_addresses.h}       { Adresy }

     {$I _MTK_2_error.h}


     function  mtkch_rus_to_lat (ch: char): char;
     function  mtks_rus_to_lat  (s: string): string;
     function  mtkp_rus_to_lat  (p: pchar; alloc: bool): pchar;


     function  inv_byte (b, bits: byte): byte;
     procedure ascii_to_mtk2bin (data: pchars; size: word;
                                 _1st_switch: bool;
                                 var bdata: pbytes; var bsize: word;
                                 bin : bool; ibits : byte
                                );
     procedure mtk2bin_to_ascii (data: pchars; size: word; bits: byte);

     function  code_MTK2_date (den,hod,min: byte): string;

     function  code_ITA2_pkt (channel : string;
                              cislo_spravy : int;
                              priorita : string;
                              adresati : pchar;
                              odosielatel : string;

                              data: pchars; size: word;

                              var pkt: pchars;  var dlz: word;

                              bin : bool;
                              ibits : byte;
                              var bpkt: pchars; var bdlz: word
                             ): bool;

     function  code_ITA2T_pkt (channel : string;
                               cislo_spravy : int;
                               priorita : string;
                               adresati : pchar;
                               odosielatel : string;

                               data: pchars; size: word;

                               var pkt: pchars; var dlz: word
                              ): bool;

     function  code_IA5_pkt  (channel : string;
                              cislo_spravy : int;
                              priorita : string;
                              adresati : pchar;
                              odosielatel : string;

                              data: pchars; size: word;

                              var pkt: pchars;  var dlz: word
                             ): bool;


implementation

uses  _Check,
       bios, keyb, sets, math, str0, mess, coms,
      _L4_def;


{$I _MTK_prty.inc}     { prty }
{$I _MTK_rus.inc}      { rus  }
{$I _MTK_bin.inc}

{$I _ITA2_pkt.inc}     { ----------------------------------------
                         Kodovanie podla ITA-2,
                         Aeronautical Telecommnucations Annex 10,
                         Volume II, July 1995 for commnunications
                         procedures and formats
                         תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                       }


{$I _ITA2T_pkt.inc}    { ----------------------------------------
                         Zjednodusene kodovanie
                         v textovom formate
                         תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                       }


{$I _IA5_pkt.inc}      { ----------------------------------------
                         Kodovanie podla IA-5,
                         Aeronautical Telecommnucations Annex 10,
                         Volume II, July 1995 for commnunications
                         procedures and formats
                         תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                       }


{$I _MTK_functions.inc}   { editor           }

end.