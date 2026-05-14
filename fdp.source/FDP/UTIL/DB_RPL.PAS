{$I comp.h}

uses bios, typedef, math, str0, io, db, dos, utime, keyb, crt,
     _l4_def, archiv, fir_def, bod_def, body, kody,
     _FDP_def, _FPL_def, NET_def, _MTK_2,
     _RPL, _L4_func;


{$I arc_format.inc}         { Kontrola integrity archivnych suborov }

type   PRPL0 = ^DRPL0;
       DRPL0 = record

         val  : char;                        { "+" pre plati, "-" pre neplati }

         dat0 : string[kod_DATE];            { zaciatok                       }
         dat1 : string[kod_DATE];            { koniec platnosti               }

         week : array[1..7] of char;         { platnost v tyzdni              }

         _7a  : string[kod_9];               { identifikacia lietadla         }
         _9   : string[kod_7];               { typ lietadla                   }

         _13  : string[kod_AP+kod_TIME];     { letisko odletu a cas odletu    }
         _15  : pchar;                       { trat                           }
         _16  : string[kod_AP+kod_TIME];     { letisko urcenia, doba letu     }

         _18  : pchar;                       { ine informacie                 }
       end;

procedure  disp_RPL0 (RPL: PRPL0);
    begin
      with RPL^ do
        begin
          StrDispose(_15);
          StrDispose(_18);
        end
    end;

const  db0_RPL_RIADKOV = 4;

function val_to_db (c: char): char; begin if c=rpl_off then c:= 'X'; val_to_db:= c end;
function db_to_val (c: char): char; begin if c='X' then c:= rpl_off; db_to_val:= c end;
function decode_i(s: string; p: pchar): pchar; begin decode_i:= StrNPCopy(p, cut_(copy(s,2,length(s)-2)), true, true) end;


procedure decodeDB0_RPL(buff: PDB_buff; RP0: PRPL0; desc: PDB_head); far;
    var   s,t: string;
          i: int;
    begin
      with RP0^ do
        begin
          s:= DBstr_to_str(buff^[0]);

          val:= db_to_val(getchar(getstr(s,1,odd_ICAO)));

          dat0:= getstr(s,2,odd_ICAO);
          dat1:= getstr(s,3,odd_ICAO);

          t:= getstr(s,4,odd_ICAO);
          for i:= 1 to 7 do week[i]:= db_to_val(t[i]);

          _7a := cut_(getstr(s,5,odd_ICAO));
          _9  := cut_(getstr(s,6,odd_ICAO));
          _13 := cut_(getstr(s,7,odd_ICAO));
          _16 := cut_(getstr(s,8,odd_ICAO));

          _15:= decode_i(DBstr_to_str(buff^[1]),_15);
          _15:= decode_i(DBstr_to_str(buff^[2]),_15);

          _18:= decode_i(DBstr_to_str(buff^[3]),_18);
          {_18:= decodeDB_p(DBstr_to_str(buff^[4]),_18);}
        end;
    end;

procedure decode0_key_RPL(s: string; RP0: PRPL0);
    begin
      fillchar(RP0^,sizeof(RP0^),0);
      with RP0^ do
        begin
          _7a:= getstr(s,1,odd_ICAO);
          _13:= getstr(s,2,odd_ICAO);
          {GetDateStr(dat0.r,dat0.m,dat0.d, getstr(s,2,[icao_ARR]), false);}
        end
    end;


{ ---------------------
   EXT/IFPS
  ---------------------

0 990325 DEST: UKBVZRZX
0 990325 SNDR: UKKKZDZX
1 RPL                990328 991025      UKKKZDZX
2 990329 991025 1000000 AEW101     B732   UKBB 0330 UKHH 0040
3            BULAP A137 MATEG
2 990330 991030 0200060 AEW101     B732   UKBB 0400 UKHH 0040
3            BULAP A137 MATEG
.
.
.
}

{ I _RPL_plan.cod}
{$I IFPS_RPL.cod}        { ext driver pre dekodovanie PLN, nove fcie    }


procedure RPL0_to_RPL(const RP0: DRPL0; var RPL: DRPL);
    var   s: string;
          h,m, h_,m_: byte;
          b1,b2,b3: bool;
          i: int;
    begin
      fillchar(RPL,sizeof(RPL),0);

      RPL.val  := RP0.val;
      RPL.zac  := RP0.dat0;
      RPL.kon  := RP0.dat1;
      for i:= 1 to 7 do RPL.dni[i]:= RP0.week[i];

      RPL._7a := RP0._7a;
      RPL._7x := ' ';

      decode_l4_9(RP0._9, s,RPL._9b,RPL._9c);

      decode_l4_13_ (RP0._13, RPL._13a, h,m, h_,m_, RPL._13b,s, b1,b2,b3);
      decode_l4_16_ (RP0._16, h,m, RPL._16a,RPL._16b, h,m,h,m, s, b1,b2,b3);

      RPL._15:= strnew(RP0._15);
      RPL._18:= strnew(RP0._18);
    end;


var  dbf : text;

function znova_uloz_RPL0(RP0: PRPL0; p: pointer): byte; far;
   var   RPL : DRPL;
         i   : int;
   begin
     RPL0_to_RPL(RP0^,RPL);
     writeln(dbf,code_IFPS_RPL_FLIGHT_INFO (RPL));
     for i:= 1 to get_data_lines_i_ (RPL._15) do writeln(dbf,code_IFPS_RPL_ROUTE (RPL,i));
     for i:= 1 to get_data_lines_i_ (RPL._18) do writeln(dbf,code_IFPS_RPL_REMARK(RPL,i));
     disp_RPL(@RPL);
     znova_uloz_RPL0:= do_item__NEXT
   end;

procedure kontrola_archivu_RPL(fnn: string);
    var   fn  : string;
          RPL : DRPL0;
    begin
      assign(dbf,fnn);
      rewrite(dbf);
      writeln(dbf,code_IFPS_HEADER_DEST (''));
      writeln(dbf,code_IFPS_HEADER_SNDR (''));
      writeln(dbf,code_IFPS_RPL_HEADER);

      konverzia_archivu(pathRPL,'*',
                        @znova_uloz_RPL0,sizeof(RPL),@disp_RPL0,
                        db0_RPL_RIADKOV,@decodeDB0_RPL
                       );

      writeln(dbf,code_IFPS_RPL_TRAIL);
      close(dbf);
    end;


begin
  kontrola_archivu_RPL(FIR_adr+'.rpl');

  writeln;
  writeln('LETVIS FDP utility to transformate RPL''s databases format.');
  writeln('Copyright by ALES (c) 1989-1999.');
end.

{comp.h pre "db_ukbb"}

{$DEFINE DEBUG}
{$DEFINE POKUS}

{$DEFINE UK}
{$DEFINE UKBB}
{$DEFINE ENGLISH}

{$DEFINE BGI}

{$I comp_exe.h}


{$DEFINE RLP}

{$DEFINE FDP}        {$DEFINE RLP}
{$DEFINE ATCA}       {$DEFINE RLP}
{$DEFINE ACC}

{$DEFINE UKBB}
{$DEFINE KIEV}

{$DEFINE RUSSIAN}
{$DEFINE A36YKA}

{$DEFINE L4444M}
{$DEFINE DATA_OB}
{$DEFINE GOST}
{$DEFINE TSGA}


{$DEFINE FPL4}
{$DEFINE FDR}
{$DEFINE RPL}
{$DEFINE FPL0}
{$DEFINE FPLC_L}
{ DEFINE FPLM_L}


{$DEFINE DATA_BIN}
{$DEFINE DB_BIN}
{$DEFINE NET}
{$DEFINE RDP}


{$I comp_net.h}
{$I comp_ext.h}
{$I comp_fdp.h}

