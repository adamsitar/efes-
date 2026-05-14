(*-------------------------------------------------------------------*)
(* LETVIS FDP - SSR codes...                                         *)
(* (c) Ales Kosice 1995  (ab),                                       *)
(* teraz je uz 1997,                                                 *)
(* a teraz 1999 - prerobene uplne                                    *)
(*                 - dodzanie casoveho limitu,                       *)
(*                 - kontrola duplicity ssr kodov i na serveri       *)
(*-------------------------------------------------------------------*)
{
  Podla ICAO sa SSR kody pridavaju podla zoznamu kodov pre dany FIR.
  Kazdy kod sa potom nesmie pouzit stanovenu dobu po jeho prideleni.

  1. Mnozina pouzitelnych kodov ssr sa nacita z cfg subora.
     Po kontrole spravnosti zadania sa aktualizuje subor so zaznamami
     o poslednom pouziti kodov (vytvori sa novy)

  2. Pri zadavani kodu ssr sa ponukne bud mnozina moznych kodov
     alebo prvy volny/najstarsie pouzity kod. Ak nie je volna
     kapacita kodov, ponukne nepouzity kod s neuplynutym
     timeoutom.

     Pri potvrdzovani planu sa skontroluje, ci kod nie je pouzity
     inym lietadlom a ci bola dodrzana nastavena lehota.

     Spravny plan sa zaradi (a odosle).

  3. FDP server kontroluje dorucene spravy o letoch na zmenu povodne
     prideleneho kodu a nasledny konflikt s inym planom. Ak je najdeny,
     potom sa odosle hlasenie o tom na pracovnu stanicu pridelivsiu
     konfliktny kod a na nom sa indikuje ssr conflict.

     Prijem spravy o lete tiez sposobi prehladanie zaznamov o
     konflikte ssr a odmazanie povodnej spravy.

  Zakladom spracovania SSR su funkcie :

  - get_ssr    : string;  vrati prvy mozny kod kod ssr
  - ssr_list   : string;  porovna tabulku moznych ssr
  - ssr_in_use : bool;    vrati, ci je aktivovany let s takymto ssr
}

{$I comp.h}
{$I comp_fdp.h}


unit _SSR;


interface

    uses   TypeDef, Arrays,
           io, DB, Archiv, Report, Edit,
           NET_def,
           FIR_def, _L4_def, _FDP_def, _FPL_def;


    {$I _ssr_cnst.h}

    function is_ssr (ssr: string; uvd: bool; var res: string): bool;


    {$IFDEF SSR_MANAGEMENT}

     const  max_ssr_records = 600;

     type  { zaznam o poslednom pouziti kodu ssr
           }
            t_ssr_user   = (ssr_user, ssr_atca,uvd_atca, ssr_mil,uvd_mil);

            p_ssr_record = ^t_ssr_record;
            t_ssr_record = record
              code   : string[kod_rbs_SSR];      { kod ssr/palubne cislo }
              {fir    : string[kod_FIR+kod_ACC];  udaj o fir, pre ktory je povoleny }
              user   : t_ssr_user;
              last   : real;                    { posledne pouzitie }
              flight : pchar;                   { posledny let - KLUC }
            end;

            t_ssr_records = array[0..max_ssr_records-1] of p_ssr_record;
            p_ssr_records = ^t_ssr_records;


     type   PO_SSRs = ^O_SSRs;
            O_SSRs  = object(TArray)
              ssr_a : p_ssr_records;

              constructor Init;
              function    najdi(code: string): int;
            end;

     const  SSRs : PO_SSRs = nil;


     function  _is_ssr_used (last: real): int;
     function  _ssr_in_use  (flight1,flight2: string; last1: real): int;
     function  ssr_in_use   (code: string; flight: string): int;
     function  ssr_configured (code: string; mil: bool{; var res: string}): int;

     procedure ssr_save  (code: string; flight: string; last: real; stat: string);
     procedure ssr_zrus  (code: string);


     function  zarad_ssr (flight,ssr,ssrp : string;
                          exi  : real;
                          stat : string;

                          zaradit : bool;
                          var res : string;
                          err : pstring
                         ): int;

     function  list_ssr   (x,y: int; mil: bool; var res: string): string;
     function  assign_ssr (mil: bool; var res: string): string;

     procedure list_of_used_ssr;

     function  check_filled_ssr (FPLp,FPLn: pointer;
                                 ssrp, ssr_,ssr0 : string;
                                 var ssr: string;
                                 var res: string
                                ): bool;

     function  form_init_ssr (form: PAForm; ind: int): bool;


     procedure decodeERR_SSR (error: string; var ires: int; var code,flight,res: string);
     procedure _pkt_SSR_ERR_REC (const pkt: TNETpkt);
     procedure _pkt_SSR_ERR_COR (const pkt: TNETpkt);
    {$ENDIF}



implementation

uses  bios, str0, keyb, msg, mess, math, mouse, utime, _check,
      {$I unit_gr.h},
      help_def, Help, Lists, Dialog,
      Kody;


{ kontrola spravnosti zadania kodu ssr
  - na dlzku
  - na cislice
  - na oktalove cislo
}
 function is_ssr (ssr: string; uvd: bool; var res: string): bool;
    var   i,ires : int;
          c : long;
    begin
      ires:= 0; res:= '';
      ssr:= cut_(ssr);
      if (length(ssr)=kod_rbs_SSR) then
        begin
          i:= 1; while (i<kod_rbs_SSR) and (ssr[i] in set_rbs_SSR) do inc(i);
          if (i<>kod_rbs_SSR) then ires:= l4_err(a_SSR,ssr,0,err_ssr_octal,res)
        end
      else if uvd and (length(ssr)=kod_uvd_BN) then
        begin
          val(ssr,c,i);
          if i>0 then ires:= l4_err(a_SSR,ssr,0,err_ssr_number, res)
        end
      else ires:= l4_err(a_SSR,ssr,0,err_ssr_invalid, res);
      is_ssr:= res=''
    end;


{$IFDEF SSR_MANAGEMENT}
 {$I _ssr.cod}
 {$I _ssr.inc}
 {$I _ssr_.inc}
 {$I _ssr_obj.inc}
 {$I _ssr_vyp.inc}
 {$I _ssr_errors.inc}
 {$I _ssr_functions.inc}
 { I _rep_ssr.inc}         { -> FDP_REP kvoli referenciam na dalsie fcie }
{$ENDIF}

{$IFDEF SSR_MANAGEMENT}
begin
  init_ssr;
{$ENDIF}
end.
