{ תתתתתתתתתתתתתתתתתתתתתתתתת
   (c) ALES 1997,  Kosice
  תתתתתתתתתתתתתתתתתתתתתתתתת

}

{$I comp.h}


unit _RPL;


interface


    uses   typedef,
           db, sets,
           {$I unit_gr.h},
           {$I unit_net.h},
           {$I unit_oop.h}, Lists,
           _L4_def, _MTK_2,
           FIR_def, ZemSur, Bod_def, Body,
           {$I unit_map.h},
           _FDP_def, _FPL_def,
           _FPL4;


    {$IFDEF RPL}
     { I _RPL_cnst.h}        { v module FDP_def }
     {$I IFPS_RPL.h}         { definicia externeho formatu podla Doc. IFPS_MAN }

     {$I _RPL_title.h}
     {$I _RPL_arrays.h}
     {$I _RPL_fr.h}
     {$I _RPL_plan.h}

     {$I _RPL_functions.h}

     function   _handle_event_RPL (var _Event: TEvent; O: PObject; RPL: PRPL): bool;
    {$ENDIF}


implementation

uses  dos,bios,_check,keyb,math,mem,io,str0,mouse,utime,mess,msg,sort,prnt,
      Vypocty,
      _L4_func,
      FDP_msg, FDP_scrl, FDP_func,
      Archiv, form_SYS, FDP_fun3;


{$IFDEF RPL}

 const    fn_RPLupdated    = pathRPL+ 'RPL-FPL' +ext_kod; { vysledok poslednej inicializacie fpl }
          fn_RPLext_copy   = pathRPL+ 'RPL-COPY'+ext_kod; { pracovny subor s kopiou ext-txt-rpl }
          fn_RPLext_kod    = pathRPL+ 'RPL-EXT' +ext_kod; { stav spracovania ext-txt-rpl }
          fn_RPLext_err    = pathRPL+ 'RPL-ERR' +ext_kod; { stav spracovania ext-txt-rpl }
          fn_RPLext_src    = pathRPL+ 'RPL-SRC' +ext_kod; { posledny zdroj ext-txt-rpl }

 const    p_rpl_dbscroller : PScrollDB_FDP = nil;

 function _handle_event_RPL_sc (var _Event: TEvent; O: PObject;
                                RPL: PRPL;
                                sc: PScroller
                               ): bool; far; forward;


 {$I _RPL_plan.cod}
 {$I _RPL_plan.vyp}        { obsahuje konverzie medzi RPL a FPL4 }
 {$I _RPL_plan.inc}
 {$I _RPL_plan.drw}
 {$I _RPL_plan.prn}

 {$I _RPL_functions.inc}
 {$I _RPLs_spracovanie.inc}

 {$IFDEF PROCESS_RPL}
  {$I IFPS_RPL.cod}        { ext driver pre dekodovanie PLN, nove fcie    }
  { I TSGA_RPL.cod}        { ext driver pre dekodovanie PLN, povodne fcie }
  {$I _RPL_driver.inc}

  {$I _RPL3.inc}           { CHG,BRK,CNT... aktualizacia }
 {$ENDIF}

 {$I _RPL_check.inc}

 {$I _RPL_ihandle.inc}
 {$I _RPL_prehlad.inc}
 {$I _RPL_handle.inc}


begin
  inicializacia;
{$ENDIF}
end.