{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   odoslanie a rozoslanie
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function send_PLN(FPL: PPLN; adr: TNETadr; wait: bool): bool;
    var   kod    : TNETtyp;
          p_code : pointer;
    begin
      kod:= spr_PLN;
      p_code:= @code_PLN;
      {$IFDEF DATA_BIN}
       if NETtype(adr) in [FDP0,FDP0NX] then
          begin
            kod:= spr0_PLN;
            p_code:= @code0_PLN
          end;
      {$ENDIF}
      send_PLN:= NETres(NETsend_data
                     (adr,
                      kod, FPL,p_code,@codekey_PLN,@FPL^.rec,
                      true,inf_PLN,nil, wait,false, net_flag_NIL
                     ))
    end;

 function distribute_PLN(FPL: PPLN; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var   bres: bool;
    begin
      {$IFDEF DATA_BIN}
       bres:= NETdistribute_data
                    (
                     [FDP0,FDP0NX],sw,nd,
                     spr0_PLN,FPL,@code0_PLN,@codekey_PLN,@FPL^.rec,
                     true,inf_PLN,nil, false,false,net_flag_NIL
                    );
      {$ELSE}
       bres:= true;
      {$ENDIF}
      distribute_PLN:= NETdistribute_data
                   (
                    [FDP],sw,nd,
                    spr_PLN,FPL,@code_PLN,@codekey_PLN,@FPL^.rec,
                    true,inf_PLN,nil, false,false,net_flag_NIL
                   ) and bres
    end;



{ -------------------
   EXT - koordinacia
  -------------------
}
(*
 function  spracovanie_PLN_EXT(przn : TPLN_spracovanie): TPLN_spracovanie;
    begin
      if rozosielat_PLN_EXT then przn:= przn or rozosli_PLN_EXT;
      spracovanie_PLN_EXT:= przn
    end;

 procedure coordinate_PLN (FPL: PPLN;
                            src: fdp_src; dst: set_fdp_src;
                            zmena, zmeneny: bool
                           );
     var   head: Thead_ICAO;
           stat: string;
     begin
      {$IFDEF EXTERNAL_NET}
       if is_KRL(FPL) then Exit;

       {if zmena then zmeneny:= zmeneny_mFPL(FPL,false);}

       stat:= FPL^.stat;
       {if __is_stat(stat,cnst_acc) then head:= hd_ABI
       else} if __is_stat(stat,cnst_stat_dep) then head:= hd_ACT
       else if pos(cnst_stat_arr,stat)>0 then head:= hd_ARR
       else if get_poz(stat)<=poz_COORDINATED then
            begin
              if         (cnst_cnl=stat)        then head:= hd_CNL
              else if pos(cnst_dla,stat)>0      then head:= hd_DLA
              {este nie je - else if _zmeneny or (pos(cnst_chg,stat)>0) then head:= hd_CHG}
              else if pos(cnst_sended,stat)>0   then head:= hd_FPL
            end;

       fdp_co_ordinate_procedure (src,dst, spr_FPLM,head, zmeneny,FPL^);
      {$ENDIF}
     end;
*)

{ --------------
   NET+EXT
  --------------
}
 function _odosli_PLN (FPL: PPLN; _src: fdp_src): bool;
    begin
      _odosli_PLN:= false;
      distribute_PLN (FPL,[],[]);
      {coordinate_PLN (FPL,_src,[],false,true);}
    end;

 procedure odosli_PLN (FPL: PPLN);
    begin
      _odosli_PLN (FPL,letvis);
    end;


